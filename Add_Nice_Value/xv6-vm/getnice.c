#include "types.h" //20163080
#include "stat.h" //20163080
#include "user.h" //20163080

int //20163080
main(int argc, char const *argv[]) //20163080
{ //20163080
    int pid; //20163080
    int nice; //20163080
    pid = 0; //20163080
    nice = 0; //20163080

    if(argc < 2) //20163080
    { //20163080
        printf(2, "Usage: pid\n"); //20163080
        exit(); //20163080
    } //20163080

    if(atoi(argv[1]) < 1) //20163080
    { //20163080
        printf(2, "invalid pid!\n"); //20163080
        exit(); //20163080
    } //20163080
    pid = atoi(argv[1]); //20163080
    nice = getnice(pid); //20163080

    if(nice == -1) //20163080
    { //20163080
        printf(2, "invalid pid!\n"); //20163080
        exit(); //20163080
    } //20163080

    printf(1,"pid : %d    nice : %d\n", pid, nice); //20163080
    exit(); //20163080
} //20163080