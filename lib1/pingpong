#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    //When I wrote this file, I was a noob, so the readability is a bit poor
    int p[2];   //child write parent receive
    int p1[2];  //opposite of the previous
    char buf[4]; //receive ping or pong
    pipe(p);  
    pipe(p1);
    char buff[4];
    int pid = fork();
    if (pid == 0)
    {
        close(p1[1]); 
        close(p[0]);
        read(p1[0], buf, sizeof(buf));
        close(p1[0]);
        printf("%d: received %s\n", getpid(), buf);
        write(p[1], "pong", 4);  // send pong to parent
        close(p[1]); //close 
        exit(0);
    }
    else
    {
        close(p1[0]);
        close(p[1]);
        write(p1[1], "ping", 4);
        close(p1[1]);
        read(p[0], buff, sizeof(buff));
        close(p[0]);
        printf("%d: received %s\n", getpid(), buff);
        // wait(0);
        exit(0);
    }
}
