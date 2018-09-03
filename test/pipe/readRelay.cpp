#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <memory.h>
#include <signal.h>

void pipe_handler(int signo, siginfo_t *info, void *)
{
    if (signo & SIGPIPE)
        std::cout << "SIGPIPE";
}
int main()
{
    struct sigaction act;
    act.sa_flags |= SIGPIPE;
    act.sa_sigaction = pipe_handler;

    sigaction(SIGPIPE, &act, NULL);
    int pipe_fd[2];
    pid_t pid;
    char r_buf[4];
    char *w_buf;
    int writenum;
    int cmd;

    memset(r_buf, 0, sizeof(r_buf));
    
    if (pipe(pipe_fd) < 0)
    {
        std::cout << "pipe create error\n";
        return -1;
    }

    if ((pid = fork()) == 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        sleep(10);
        exit(0);
    }
    else if (pid > 0)
    {
        sleep(1);
        close(pipe_fd[0]);
        w_buf = "111";
        if ((writenum = write(pipe_fd[1], w_buf, 4)) == -1)
            std::cout << "write to pipe error\n";
        else 
            std::cout << "the bytes write to pipe is " << writenum;
        close(pipe_fd[1]);
    }
    else 
    {
        std::cout << "fork error\n" ;
        return -1;
    }

    

}
