#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
//must to reference ls.c if you want to complete the case
void find(char *path, char *targetfile);
char *
fmtname(char *path)  //format string , if size < DIRSIZ will add spaces
{
    static char buf[DIRSIZ + 1];
    char *p;

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
    return buf;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(2, "error input!");
    }
    find(argv[1], argv[2]);
    exit(0);
}

void find(char *path, char *targetfile)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    char buf_path[DIRSIZ + 1];
    char buf_target[DIRSIZ + 1];
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:

        strcpy(buf_path, fmtname(path));
        strcpy(buf_target, fmtname(targetfile));
        if (strcmp(buf_path, buf_target) == 0)
            printf("%s\n", path);
        break;
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("ls: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0 || strcmp(".", de.name) == 0 || strcmp("..", de.name) == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (stat(buf, &st) < 0)
            {
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            find(buf, targetfile);
        }
        break;
    }
    close(fd);
}
