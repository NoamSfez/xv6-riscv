#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    long long x = 1;
    printf("looper is running\n");
    for (long i = 1; i < 9999999; i++)
    {
        x += i;
    }
    printf("\n,jfl %ld\n", x);
    if (x % 3 == 1)
        return 1;
    return 0;
}