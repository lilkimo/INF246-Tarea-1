#include <stdio.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    printf("Hello, World!");
    int ret;
    ret = mkdir("quetal",S_IRUSR);
    return 0;
}