#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <memory.h>
#include <iostream>
#include <unistd.h>

#define FIFO_SERVER "./fifoserver"

using std::cout;

int main(int argc, char *argv[])
{
    int fd;
    char w_buf[4096*2];
    int real_num;
    memset(w_buf, 0, 4096*2);
    if ((mkfifo(FIFO_SERVER, O_CREAT | O_EXCL) < 0) && (errno != EEXIST))
        std::cout << "cannot create fifoservern";
    if (fd == -1)
        if (errno == ENXIO)
            std::cout << "open errno; no reading process\n" ;
    //设置阻塞标志
    fd = open(FIFO_SERVER, O_WRONLY, 0);
    //设置非阻塞标志
    //fd = open(FIFO_SERVER, O_WRONLY | O_NONBLOCK, 0);
    real_num = write(fd, w_buf, 2048);
    if (real_num == -1)
    {
        if (errno == EAGAIN)
            cout << "write to fifo error try later";
    }
    else 
        cout << "read number is " << real_num;

    real_num = write(fd, w_buf, 5000);
    //real_num = write(fd. w_buf, 4096)
    if (real_num == -1)
        if (errno == EAGAIN)
            cout << "try later";
}

