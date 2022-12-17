//bankers algorithm

#include <stdio.h>
#define N 10

int need[N][N], available[N], allocated[N][N], max[N][N], req[N], n, m, sequence[N], z=0;

int safety()                            //resource == m  process == n
{
    int work[m], finish[n], flag=0, process=0;
    for(int i=0; i<n; i++)
    {
        finish[i] = 0;
    }
    for(int i=0; i<m; i++)
    {
        work[i] = available[i];
    }
    for(int l=0; l<n; l++)
    {
        for(int i=0; i<n; i++)
        {
            if(finish[i] == 0)
            {
                flag =0;
                for(int j=0; j<m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        flag =1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    sequence[z++] = i;
                    for(int y=0; y<m; y++)
                    {
                        work[y] += allocated[i][y];
                        finish[i] = 1;
                    }
                }
            }
        }
    }
    for(int x=0; x<n;x++)
    {
        if(finish[x] != 1)
            return 0;
    }
    return 1;
}

void request(int r)
{
    for(int i=0; i<m; i++)
    {
        if(req[i] > need[r][i])
        {
            printf("cannot grant request since request is greater than need\n");
            return;
        }
    }
    for(int i=0; i<m; i++)
    {
        allocated[r][i] += req[i];
        need[r][i] -= req[i];
        available[i] -= req[i];
    }
    int s = safety();
    if(s == 1)
    {
        printf("request granted!!\n");
        printf("The safe sequence is :\n");
        for(int i=0; i<z; i++)
        {
            if(i < z-1)
                printf("p%i --> ", sequence[i]);
            else
                printf("p%i \n", sequence[i]);
        }
    }
    else
    {
        printf("request cannot be granted now\n");
        for(int i=0; i<m; i++)
        {
            allocated[r][i] -= req[i];
            need[r][i] += req[i];
            available[i] += req[i];
        }
    }
}

int main()
{
    // here process and resource number starts from 0

    int p;
    printf("Enter no. of processess and resources : ");
    scanf("%i %i", &n, &m);
    printf("enter max requirments of processess\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%i", &max[i][j]);
        }
    }
    printf("enter no. of each resource allocated\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%i", &allocated[i][j]);
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    printf("Enter available of each resource\n");
    for(int j=0;j<m;j++)
    {
        scanf("%i", &available[j]);
    }
    printf("enter process no. that want to request : ");
    scanf("%i", &p);
    printf("Enter request of each resource\n");
    for(int j=0;j<m;j++)
    {
        scanf("%i", &req[j]);
    }
    request(p);
}