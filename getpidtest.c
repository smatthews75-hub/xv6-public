#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int pid = getpid();
    printf(1, "getpidtest: pid = %d\n", pid);
    exit();
}