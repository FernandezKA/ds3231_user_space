/**
 * @file DS3231.h
 * @author FernandezKA (fernandes.kir@yandex.ru)
 * @brief
 * @version 0.1
 * @date 2024-01-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <cstdint>
#include <string>
#include <ctime>

/**
 * @class DS3231
 * @brief Class to interface with the DS3231 Real-Time Clock on Linux systems.
 *
 * This class provides access to the functionality of the DS3231 RTC chip via
 * I2C communication. It allows for setting and getting the current time,
 * reading the temperature, and controlling the alarms.
 */
class DS3231 {
public:
  explicit DS3231(const std::string& i2c_bus_path);
  ~DS3231();

  bool setTime(const std::tm &time);
  bool getTime(std::tm &time);
  float getTemperature();
  bool setAlarm1(const std::tm &time, uint8_t mode);
  bool setAlarm2(const std::tm &time, uint8_t mode);
  bool clearAlarmFlags();
  bool initialize();

private:
  int i2c_bus_fd; // File descriptor for the I2C bus
  bool readRegister(uint8_t reg, uint8_t *buf, size_t buf_size);
  bool writeRegister(uint8_t reg, uint8_t val);
  bool write(const uint8_t *data, size_t data_size);
  // Constants related to the DS3231 chip
  static constexpr uint8_t DS3231_ADDRESS = 0x68;
  static constexpr uint8_t DS3231_REG_TIME = 0x00;
  static constexpr uint8_t DS3231_REG_SEC = 0x00;
  static constexpr uint8_t DS3231_REG_MIN = 0x01;
  static constexpr uint8_t DS3231_REG_HOUR = 0x02;
  static constexpr uint8_t DS3231_REG_DAY = 0x03;
  static constexpr uint8_t DS3231_REG_DATE = 0x04;
  static constexpr uint8_t DS3231_REG_MONTH = 0x05;
  static constexpr uint8_t DS3231_REG_YEAR = 0x06;
  static constexpr uint8_t DS3231_REG_ALARM1 = 0x07;
  static constexpr uint8_t DS3231_REG_ALARM2 = 0x0B;
  static constexpr uint8_t DS3231_REG_CONTROL = 0x0E;
  static constexpr uint8_t DS3231_REG_STATUS = 0x0F;
  static constexpr uint8_t DS3231_REG_TEMP = 0x11;

  // Helper functions
  inline uint8_t decToBcd(uint8_t dec) const;
  inline uint8_t bcdToDec(uint8_t bcd) const;
};
