#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    int fd[2];
    char buf[5];

    if(pipe(fd) != 0){
        printf("ping-pong: pipe() failed\n");
        exit();
    }
    // Child
    if (fork() == 0){
        if(read(fd[0], buf, 4) != 4){
            printf("child received ping error\n");
            exit();
        }
        buf[4] = '\0';
        printf("1%s\n", buf);
        if (strcmp(buf, "ping") == 0){
            printf("%d: received %s\n", getpid(), buf);
            write(fd[1], "pong", 4);
        }
    }
    // Parent
    else {
        write(fd[1], "ping", 4);
        // printf("awake\n");
        wait();
        // printf("awake\n");
        if(read(fd[0], buf, 4) != 4){
            printf("parent received pong error\n");
            exit();
        }
        buf[4] = '\0';
        if (strcmp(buf, "pong") == 0){
            printf("%d: received %s\n", getpid(), buf);
        }
    }

    exit();
}
