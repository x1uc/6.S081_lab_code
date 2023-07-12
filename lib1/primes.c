#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define WRITE 1
#define READ 0
void dfs(int pd[])
{
    int pd1[2];
    pipe(pd1);
    close(pd[WRITE]);
    int bin;
    read(pd[READ], &bin, sizeof(int));
    if (bin == 0) 
        exit(0);
    printf("prime %d\n", bin);
    if (fork() == 0)
    {
        dfs(pd1);
    }
    else
    {
        close(pd1[READ]);
        int temp;
        while (read(pd[READ], &temp, sizeof(int)) != 0)
        {
            if (temp % bin != 0)
            {
                write(pd1[WRITE], &temp, sizeof(int));
            }
        }
        close(pd1[WRITE]);
        wait(0);
        exit(0);
    }
}
int main(int argc, char *argv[])
{
    int nums[34];
    int i;
    for (i = 2; i <= 35; i++)
    {
        nums[i - 2] = i;
    }
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        dfs(p);
    }
    else
    {
        close(p[READ]);
        write(p[WRITE], &nums, 34 * sizeof(int));
        close(p[WRITE]);
        wait(0);
    }
    exit(0);
    return 0;
}
