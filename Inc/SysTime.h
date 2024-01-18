/**
 * @file SysTime.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <ctime>

class SystemTimeUpdater {
public:
  SystemTimeUpdater() = default;
  ~SystemTimeUpdater() = default;

  // Sets the system time to the specified std::tm time structure
  static bool setSystemTime(const std::tm &newTime) {
    struct timespec spec;
    spec.tv_sec = std::mktime(const_cast<std::tm *>(&newTime));
    spec.tv_nsec = 0;

    // Set the system time
    return clock_settime(CLOCK_REALTIME, &spec) == 0;
  }

  // Retrieves the current system time into a std::tm time structure
  static bool getSystemTime(std::tm &currentTime) {
    struct timespec spec;
    if (clock_gettime(CLOCK_REALTIME, &spec) != 0) {
      return false;
    }

    // Convert time_t to tm structure
    std::time_t tt = spec.tv_sec;
    if (localtime_r(&tt, &currentTime) == nullptr) {
      return false;
    }

    return true;
  }
};
