#include <DS3231.h> 
#include <SysTime.h>
#include <iostream> 
#include <string> 

int main(){
    DS3231 rtc("/dev/i2c-0");
    SystemTimeUpdater SysTime;
    std::tm time;
    rtc.getTime(time);
    SysTime.getSystemTime(time);
    std::cout << "Time: " << std::asctime(&time) << std::endl;
    return 0;
}