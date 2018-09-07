#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

using namespace std;

typedef struct 
{
    char name[4];
    int age;
} people;

int main()
{
    pid_t pid;
    people *m_map;
    
    m_map = (people*)mmap(m_map, sizeof(people) * 10, PROT_READ |  PROT_WRITE, 
                         MAP_SHARED | MAP_ANON, -1, 0);
    
    if ((pid = fork()) == 0)
    {
        sleep(10);
        for (int i = 0; i < 10; i++)
            std::cout << " name : " << (*(m_map+i)).name << " age : " 
                << (*(m_map+i)).age << "\n";

        if (munmap(m_map, sizeof(people)*10) == 0)
            std::cout << "munmap success\n";
    }
    else if (pid > 0)
    {
        char tmp = 'a';
        for (int i = 0; i < 10; i++)
        {
            memcpy((*(m_map+i)).name, &tmp, 2);
            tmp++;
            (*(m_map+i)).age = i + 20;
        }
    }
    else 
    {
        std::cout << "fork error\n";
    }
}
