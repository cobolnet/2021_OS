#include "types.h" //20163080
#include "stat.h" //20163080
#include "user.h" //20163080

int //20163080
main(int argc, char const *argv[]) //20163080
{ //20163080
    int pid; //20163080
    int nice; //20163080
    int result; //20163080
    pid = 0; //20163080
    nice = 0; //20163080
    result = -1; //20163080

    if(argc < 3) //20163080
    { //20163080
        printf(2, "Usage: pid nice\n"); //20163080
        exit(); //20163080
    } //20163080

    if(atoi(argv[1]) < 1) //20163080
    { //20163080
        printf(2, "invalid pid!\n"); //20163080
        exit(); //20163080
    } //20163080
    pid = atoi(argv[1]); //20163080

    if(atoi(argv[2]) < 0) //20163080
    { //20163080
        printf(2, "invalid value!\n"); //20163080
        exit(); //20163080
    } //20163080
    nice = atoi(argv[2]); //20163080

    result = setnice(pid, nice); //20163080

    if(result == -1) //20163080
    { //20163080
        printf(2, "invalid pid or nice value!\n"); //20163080
        exit(); //20163080
    } //20163080

    printf(2, "success!\n"); //20163080
    exit(); //20163080
} //20163080