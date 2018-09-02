#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <iostream>

void new_op(int, siginfo_t *, void *);

int main(int argc, char **argv)
{
    struct sigaction act;
    int sig;
    sig = atoi(argv[1]);

    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = new_op;

    if (sigaction(sig, &act, NULL) < 0)
    {
        std::cout << "install signal error \n";
    }

    while (1)
    {
        sleep(1);
        printf("wait for the signal\n");
    }

}

void new_op(int signum, siginfo_t *info, void *myact)
{
    printf("receive signal %d", signum);
    sleep(5);
}
