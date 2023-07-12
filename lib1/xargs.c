#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#define max_arg_len 100
#define max_arg 32
#define stdin 0
int main(int argc, char *argv[])
{
    int i;
    int arg_index = 0;
    char buf, arg[max_arg_len], *args[max_arg];
    if (argc < 2)
    {
        fprintf(2, "input error\n");
    }
    for (i = 1; i < argc; i++)
    {
        args[i - 1] = argv[i];
    }
    int n;

    while ((n = read(stdin, &buf, sizeof(char))) > 0) // for exery '\n' , exec(33line) will execute once;
    {
        if (buf == '\n')
        {
            arg[arg_index] = 0;
            // printf("%s", arg);
            if (fork() == 0)
            {
                args[argc - 1] = arg;
                args[argc] = 0;
                exec(args[0], args);
                exit(0);
            }
            else
            {
                wait(0);
                arg_index = 0;
            }
        }
        else
        {
            arg[arg_index] = buf;
            arg_index++;
        }
    }
    exit(0);
    return 0;
}
