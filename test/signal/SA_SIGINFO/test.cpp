#include <iostream>
#include <signal.h>

using namespace std;

void sig_handler(int sig)
{
    if (sig == SIGALRM)
        cout << "sig_handler recived" << endl;
}

void sa_handl(int sig, siginfo_t* info, void *)
{
    cout << "sa_handler reviced" << endl;
}
int main()
{
    struct sigaction act;
    act.sa_flags |= SA_SIGINFO;
    act.sa_handler = sig_handler;
    act.sa_sigaction = sa_handl;
    int ret = sigaction(SIGALRM, &act, NULL);
    
    raise(SIGALRM);
}
