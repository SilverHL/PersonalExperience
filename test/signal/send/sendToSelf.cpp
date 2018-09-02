#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <memory.h>
#include <cstdlib>

void new_op(int, siginfo_t *, void *);

int main(int argc, char **argv)
{
    struct sigaction act;
    union sigval mysigval;
    int sig;
    pid_t pid;
    char data[10];
    memset(data, 0, sizeof(data));
    for (int i = 0; i < 5; i++)
        data[i] = '2';

    mysigval.sival_ptr = data;
    sig = atoi(argv[1]);
    pid = getpid();

    sigemptyset(&act.sa_mask);
    act.sa_sigaction = new_op;
    act.sa_flags = SA_SIGINFO;
    if (sigaction(sig, &act, NULL) < 0)
    {
        std::cout << "install sig error\n";
    }
    while (1)
    {
        sleep(2);
        std::cout << "wait for the signal\n" ;
        sigqueue(pid, sig, mysigval);
    }
}

void new_op(int signum, siginfo_t* info, void *myact)
{
    int i;
    for (i = 0; i < 5; i++)
        std::cout << (*( (char*)((*info).si_ptr)+i ));
    std::cout << "handle signal " << signum << " over";
}
