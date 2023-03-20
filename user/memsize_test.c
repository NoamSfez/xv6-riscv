#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void print(const char *s)
{
    write(1, s, strlen(s));
}

void memsize_test(void)
{

    print("memsize test\n");

    // step1: print
    int currSize = memsize();
    printf("%d\n", currSize);

    // step2: malloc
    void *addr = malloc(20000);

    // step3: print
    currSize = memsize();
    printf("%d\n", currSize);

    // step4: free
    free(addr);

    // step5: print
    currSize = memsize();
    printf("%d\n", currSize);

    print("memsize test OK\n");
}

int main(void)
{
    memsize_test();
    exit(0);
}