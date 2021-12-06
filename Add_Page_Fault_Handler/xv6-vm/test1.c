#include "types.h" // 20163080
#include "stat.h" // 20163080
#include "user.h" // 20163080

int // 20163080
main(int argc, char **argv) // 20163080
{ // 20163080
    int before, after; // 20163080
    int pid; // 20163080

    printf(1, "TEST1: "); // 20163080
    before = freemem(); // 20163080
    pid = fork(); // 20163080
    if(pid == 0) // 20163080
    { // 20163080
        after = freemem(); // 20163080
        if(before - after == 68) // 20163080
            printf(1, "OK\n"); // 20163080
        else // 20163080
            printf(1, "WRONG\n"); // 20163080
        exit(); // 20163080
    } // 20163080
    else // 20163080
    { // 20163080
        wait(); // 20163080
    } // 20163080
    exit(); // 20163080
} // 20163080