#include <iostream>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

#define FIFO_SERVER "./fifoserver"

using std::cout;

int main(int argc, char *argv[])
{
    char r_buf[4096*2];
    int fd;
    int r_size;
    r_size = atoi(argv[1]);
    cout << " required real read bytes " << r_size << std::endl;
    memset(r_buf, 0, sizeof(r_buf));
    fd = open(FIFO_SERVER, O_RDONLY, 0);
}
