#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    if (!fork()) {
        usleep(1000);

        printf("I'm an orphan with PID %d My parent was %d\n", getpid(), getppid());

        if (!fork())
            printf("I'm a zombie with PID %d\n", getpid());
        else
            sleep(10);
    } else
        printf("I'm the parent (%d)\n", getpid());

    return 0;
}

