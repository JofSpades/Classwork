#include "types.h"
#include "stat.h"
#include "syscall.h"
#include "user.h"

int main(){
    int time = uptime();
    time /= 100;
    int hours = time / 3600;
    int minutes = time / 60;
    int seconds = time - (hours * 3600) - (minutes * 60);
    printf(1, "current uptime is: %d:%d:%d\n", hours, minutes, seconds);
    exit();
    return 0;
}
