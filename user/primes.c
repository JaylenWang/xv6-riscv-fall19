#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int fd[2];
void fun(int fd_in)
{
    int pid;
    int buf, p = 0;
    while(read(fd_in, &buf, 4) == 4) {
        // sleep(10);
        p = buf;
        printf("prime %d\n", p);

        if(pipe(fd) != 0){
            printf("primes: pipe() failed\n");
            exit();
        }
        pid = fork();
        if(pid == 0){
            close(fd[1]);
            fd_in = fd[0];
            continue;
        }
        else if(pid > 0){
            close(fd[0]);
            close(1);
            while(read(fd_in, &buf, 4) == 4){
                if(buf % p != 0){
                    // if(p == 17)
                    //     printf("    write %d\n", buf);
                    write(fd[1], &buf, sizeof(int));
                }
            }
            close(fd[1]);
            // printf("done %d\n", p);
            wait();
            break ;
        }
        else{
            printf("fail to fork when prime = %d\n", p);
            break;
        }
    }
    // the write-side of the pipe is closed, EOF
    close(fd_in);

    return ;
}

int main(int argc, char *argv[])
{
    int i;
    // close(0);
    // close(2);

    if(pipe(fd) != 0){
        printf("primes: pipe() failed\n");
        exit();
    }

    if(fork() == 0){
        close(fd[1]);
        fun(fd[0]);
        exit();
    }
    else{
        close(fd[0]);
        close(1);
        for(i = 2; i <= 35; ++i){
            write(fd[1], &i, sizeof(int));
        }
        close(fd[1]);
        wait();
    }

    exit();
}