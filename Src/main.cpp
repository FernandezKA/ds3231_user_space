#include <DS3231.h>
#include <SysTime.h>
#include <iostream>

// Function declarations
void printHelpMessage();

int main(int argc, char *argv[]) {
  std::string default_i2c_device = "/dev/i2c-0";

  if (argc != 2 && argc != 3) {
    printHelpMessage();
    return 0;
  }

  std::string i2c_device = (argc < 3) ? default_i2c_device : std::string(argv[2]);

  DS3231 rtc(i2c_device);
  SystemTimeUpdater sysTime;
  std::tm time;

  std::string command(argv[1]);
  if (command == "read") {
    rtc.getTime(time);
    std::cout << "Time on RTC: " << std::asctime(&time) << std::endl;
  } else if (command == "write") {
    sysTime.getSystemTime(time);
    rtc.setTime(time);
    rtc.getTime(time);
    std::cout << "Time on RTC: " << std::asctime(&time) << std::endl;
  } else if (command == "update") {
    rtc.getTime(time);
    sysTime.setSystemTime(time);
  } else if (command == "temperature") {
    std::cout << "Temperature: " << rtc.getTemperature() << std::endl;
  } else if (command == "help") {
    printHelpMessage();
  } else {
    std::cout << "Invalid command" << std::endl;
  }

  return 0;
}

/**
 * Prints the help message with the available commands.
 */
void printHelpMessage() {
  std::cout << "Usage: ./DS3231 <command> [i2c-device-path]" << std::endl;
  std::cout << "Available commands:\n"
            << "read - read time from RTC\n"
            << "write - write time to RTC\n"
            << "update - update system time with RTC time\n"
            << "temperature - read temperature from ds3231\n"
            << "help - print available commands\n"
            << "Example: ./DS3231 read /dev/i2c-0" << std::endl;
}