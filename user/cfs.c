

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char *long_to_str(uint64 num)
{
    int isNegative = 0;
    char *strNum;
    int i, j, temp;
    long remainder;

    if (num == 0)
    {
        strNum = (char *)malloc(sizeof(char) * 2);
        strNum[0] = '0';
        strNum[1] = '\0';
        return strNum;
    }

    if (num < 0)
    {
        isNegative = 1;
        num *= -1;
    }

    remainder = num;
    i = 0;

    while (remainder != 0)
    {
        remainder /= 10;
        i++;
    }

    strNum = (char *)malloc(sizeof(char) * (i + isNegative + 1));
    j = i + isNegative - 1;

    while (num != 0)
    {
        temp = num % 10;
        strNum[j--] = temp + '0';
        num /= 10;
    }

    if (isNegative)
    {
        strNum[j] = '-';
    }

    strNum[i + isNegative] = '\0';

    return strNum;
}

char *make_msg(uint64 pid, uint64 priority, uint64 rtime, uint64 stime, uint64 retime)
{
    char *str = (char *)malloc(55 + 5 * sizeof(uint64));
    char *str1 = "pid: ";
    char *str2 = " - priority: ";
    char *str3 = " - rtime: ";
    char *str4 = " - stime: ";
    char *str5 = " - retime: ";
    int offset = 0;

    memcpy(str, str1, strlen(str1));
    offset += strlen(str1);
    memcpy(str + offset, long_to_str(pid), strlen(long_to_str(pid)));
    offset += strlen(long_to_str(pid));
    memcpy(str + offset, str2, strlen(str2));
    offset += strlen(str2);
    memcpy(str + offset, long_to_str(priority), strlen(long_to_str(priority)));
    offset += strlen(long_to_str(priority));
    memcpy(str + offset, str3, strlen(str3));
    offset += strlen(str3);
    memcpy(str + offset, long_to_str(rtime), strlen(long_to_str(rtime)));
    offset += strlen(long_to_str(rtime));
    memcpy(str + offset, str4, strlen(str4));
    offset += strlen(str4);
    memcpy(str + offset, long_to_str(stime), strlen(long_to_str(stime)));
    offset += strlen(long_to_str(stime));
    memcpy(str + offset, str5, strlen(str5));
    offset += strlen(str5);
    memcpy(str + offset, long_to_str(retime), strlen(long_to_str(retime)));
    offset += strlen(long_to_str(retime));
    // char *end = (char *)malloc(1);
    //  memset();
    memcpy(str + offset, "\0", 1);
    return str;
}

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

        free
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