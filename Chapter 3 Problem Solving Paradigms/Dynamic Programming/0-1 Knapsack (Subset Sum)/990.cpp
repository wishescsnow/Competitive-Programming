#include <stdio.h>
#include <string.h>

#define T 1005
#define N 35

struct Treasure
{
    int depth, time, value;
}treasure[N];

int c[T];
bool p[N][T];

int main()
{
    int t, w, n, count, cas = 0;
    while(~scanf("%d %d", &t, &w))
    {
        if(cas) puts("");
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
        {
            int depth, value;
            scanf("%d %d", &depth, &value);
            treasure[i].depth = depth;
            treasure[i].time = 3 * depth * w;
            treasure[i].value = value;
        }

        memset(c, 0, sizeof(c));
        memset(p, 0, sizeof(p));

        for(int i = n; i; i--)
        for(int j = t; j >= treasure[i].time; j--)
        {
            if(c[j] < c[j - treasure[i].time] + treasure[i].value)
            {
                c[j] = c[j - treasure[i].time] + treasure[i].value;
                p[i][j] = 1;
            }
        }

        printf("%d\n", c[t]);
        count = 0;

        for(int i = 1, j = t; i <= n; i++)
            if(p[i][j])
            {
                count++;
                j -= treasure[i].time;
            }

        printf("%d\n", count);

        for(int i = 1, j = t; i <= n; i++)
            if(p[i][j])
            {
                printf("%d %d\n", treasure[i].depth, treasure[i].value);
                j -= treasure[i].time;
            }
        cas++;
    }
    return 0;
}
