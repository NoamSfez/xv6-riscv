

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main()
{
    int pid1 = fork();
    if (pid1 == 0)
    {
        set_cfs_priority(0);
        sleep(10);
        for (int i = 0; i < 1000000; i++)
        {
            if (i % 100000 == 0)
            {
                sleep(10);
            }
        }
        uint64 pid = getpid();
        unsigned long *priority = (uint64 *)(malloc(sizeof(uint64)));
        unsigned long *rtime = (uint64 *)(malloc(sizeof(uint64)));
        unsigned long *stime = (uint64 *)(malloc(sizeof(uint64)));
        unsigned long *retime = (uint64 *)(malloc(sizeof(uint64)));

        get_cfs_stats(pid, (unsigned long)priority, (unsigned long)rtime, (unsigned long)stime, (unsigned long)retime);
        printf("pid: %d - priority: %d - rtime: %d - stime: %d - retime: %d\n", pid, *priority, *rtime, *stime, *retime);

        free(priority);
        free(rtime);
        free(stime);
        free(retime);
    }
    else
    {
        int pid2 = fork();
        if (pid2 == 0)
        {
            set_cfs_priority(1);
            sleep(25);
            for (int i = 0; i < 1000000; i++)
            {
                if (i % 100000 == 0)
                {
                    sleep(10);
                }
            }
            uint64 pid = getpid();
            unsigned long *priority = (uint64 *)(malloc(sizeof(uint64)));
            unsigned long *rtime = (uint64 *)(malloc(sizeof(uint64)));
            unsigned long *stime = (uint64 *)(malloc(sizeof(uint64)));
            unsigned long *retime = (uint64 *)(malloc(sizeof(uint64)));

            get_cfs_stats(pid, (unsigned long)priority, (unsigned long)rtime, (unsigned long)stime, (unsigned long)retime);
            printf("pid: %d - priority: %d - rtime: %d - stime: %d - retime: %d\n", pid, *priority, *rtime, *stime, *retime);

            free(priority);
            free(rtime);
            free(stime);
            free(retime);
        }
        else
        {
            int pid3 = fork();
            if (pid3 == 0)
            {
                set_cfs_priority(2);
                sleep(40);
                for (int i = 0; i < 1000000; i++)
                {
                    if (i % 100000 == 0)
                    {
                        sleep(10);
                    }
                }
                uint64 pid = getpid();
                unsigned long *priority = (uint64 *)(malloc(sizeof(uint64)));
                unsigned long *rtime = (uint64 *)(malloc(sizeof(uint64)));
                unsigned long *stime = (uint64 *)(malloc(sizeof(uint64)));
                unsigned long *retime = (uint64 *)(malloc(sizeof(uint64)));

                get_cfs_stats(pid, (unsigned long)priority, (unsigned long)rtime, (unsigned long)stime, (unsigned long)retime);
                printf("pid: %d - priority: %d - rtime: %d - stime: %d - retime: %d\n", pid, *priority, *rtime, *stime, *retime);

                free(priority);
                free(rtime);
                free(stime);
                free(retime);
            }
            else
            {
                wait(0, 0);
                wait(0, 0);
                wait(0, 0);
            }
        }
    }
    exit(0, "");
}