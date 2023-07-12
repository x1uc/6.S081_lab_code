#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "please input 2 argment\n");
        exit(1);
    }
    int cnt = atoi(argv[1]);
    sleep(cnt);
    exit(0);
}
