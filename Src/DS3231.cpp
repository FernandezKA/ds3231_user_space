/**
 * @file DS3231.cpp
 * @author FernandezKA (fernandes.kir@yandex.ru)
 * @brief
 * @version 0.1
 * @date 2024-01-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <DS3231.h>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

/**
 * Constructor for the DS3231 class.
 *
 * @param i2c_bus_path the path of the I2C bus to open
 *
 * @throws std::cerr if there is an error opening the I2C bus or setting the I2C
 * address
 */
DS3231::DS3231(const char *i2c_bus_path) {
  // Open the I2C bus
  i2c_bus_fd = open(i2c_bus_path, O_RDWR);
  if (i2c_bus_fd < 0) {
    std::cerr << "Error opening I2C bus" << std::endl;
  } else {
    // Set the I2C slave address
    if (ioctl(i2c_bus_fd, I2C_SLAVE, DS3231_ADDRESS) < 0) {
      std::cerr << "Error setting I2C address" << std::endl;
      close(i2c_bus_fd);
      i2c_bus_fd = -1;
    }
  }
}

/**
 * Destructor for the DS3231 class.
 *
 * @throws None.
 */
DS3231::~DS3231() {
  if (i2c_bus_fd >= 0) {
    close(i2c_bus_fd);
    i2c_bus_fd = -1;
  }
}

/**
 * Sets the time on the DS3231 RTC module.
 *
 * @param time A reference to a std::tm object representing the time to be set.
 *
 * @return True if the time was set successfully, false otherwise.
 *
 * @throws None.
 */
bool DS3231::setTime(const std::tm &time) {
  uint8_t timeData[7];
  timeData[0] = decToBcd(time.tm_sec);
  timeData[1] = decToBcd(time.tm_min);
  timeData[2] = decToBcd(time.tm_hour);
  timeData[3] = decToBcd(time.tm_wday + 1); // Day of week, 1-7
  timeData[4] = decToBcd(time.tm_mday);
  timeData[5] = decToBcd(time.tm_mon + 1); // Months are zero-based in std::tm
  timeData[6] = decToBcd(time.tm_year - 100); // Years since 1900

  return writeRegister(DS3231_REG_TIME, timeData, sizeof(timeData));
}

/**
 * Reads the time from DS3231 and fills the provided std::tm structure.
 *
 * @param time a reference to the std::tm structure to fill with the time
 *
 * @return true if the time is successfully read and filled, false otherwise
 *
 * @throws None
 */
bool DS3231::getTime(std::tm &time) const {
  // Read time from DS3231 and fill std::tm structure
  uint8_t timeData[7];
  if (!readRegister(DS3231_REG_TIME, timeData, sizeof(timeData))) {
    return false;
  }

  time.tm_sec = bcdToDec(timeData[0]);
  time.tm_min = bcdToDec(timeData[1]);
  time.tm_hour = bcdToDec(timeData[2]);
  time.tm_wday = bcdToDec(timeData[3]) - 1; // Day of week, 0-6
  time.tm_mday = bcdToDec(timeData[4]);
  time.tm_mon = bcdToDec(timeData[5]) - 1; // Months are zero-based in std::tm
  time.tm_year = bcdToDec(timeData[6]) + 100; // Years since 1900

  return true;
}

/**
 * Get the temperature from the DS3231.
 *
 * @return the temperature in degrees Celsius.
 *
 * @throws None if the temperature reading is successful.
 */
float DS3231::getTemperature() const {
  // Read temperature from DS3231
  uint8_t tempData[2];
  if (!readRegister(DS3231_REG_TEMP, tempData, sizeof(tempData))) {
    return 0.0f; // Failure to read temperature
  }

  // Combine the MSB and LSB into a 16-bit value and convert to temperature
  int16_t rawTemp = (tempData[0] << 8) | tempData[1];
  return rawTemp / 256.0f;
}

bool DS3231::setAlarm1(const std::tm &time, uint8_t mode) {
  // Set alarm 1 on DS3231
  // This function should be implemented to set alarm 1 on the DS3231
  return false; // Placeholder return value
}

bool DS3231::setAlarm2(const std::tm &time, uint8_t mode) {
  // Set alarm 2 on DS3231
  // This function should be implemented to set alarm 2 on the DS3231
  return false; // Placeholder return value
}

bool DS3231::clearAlarmFlags() {
  // Clear alarm flags on DS3231
  // This function should be implemented to clear alarm flags on the DS3231
  return false; // Placeholder return value
}

bool DS3231::initialize() {
  // Initialize the DS3231
  // This function should be implemented to initialize the DS3231
  return false; // Placeholder return value
}

/**
 * Read a register from the DS3231.
 *
 * @param reg the register to read
 * @param buf a pointer to the buffer to store the read data
 * @param buf_size the size of the buffer
 *
 * @return true if the read operation is successful, false otherwise
 *
 * @throws None
 */
bool DS3231::readRegister(uint8_t reg, uint8_t *buf, size_t buf_size) const {
  // Read a register from the DS3231
  if (ioctl(i2c_bus_fd, I2C_SLAVE, DS3231_ADDRESS) < 0) {
    perror("Failed to acquire bus access and/or talk to slave.\n");
    return false;
  }

  uint8_t buffer[1] = {reg};
  if (write(i2c_bus_fd, buffer, 1) != 1) {
    perror("Failed to write register address to the i2c bus.\n");
    return false;
  }

  if (read(i2c_bus_fd, buf, buf_size) != static_cast<ssize_t>(buf_size)) {
    perror("Failed to read from the i2c bus.\n");
    return false;
  }

  return true;
}

/**
 * Convert a binary-coded decimal (BCD) value to a decimal value.
 *
 * @param bcd The BCD value to convert.
 *
 * @return The decimal value.
 */
uint8_t DS3231::bcdToDec(uint8_t bcd) const {
  return (bcd / 16 * 10) + (bcd % 16);
}

/**
 * Converts a decimal number to binary-coded decimal (BCD).
 *
 * @param dec The decimal number to be converted.
 *
 * @return The binary-coded decimal representation of the decimal number.
 */
uint8_t DS3231::decToBcd(uint8_t dec) const {
  return (dec / 10 * 16) + (dec % 10);
}

/**
 * Write data to a register in the DS3231.
 *
 * @param reg the register to write to
 * @param data a pointer to the data to write
 * @param data_size the size of the data to write
 *
 * @return true if the write was successful, false otherwise
 *
 * @throws None
 */
bool DS3231::writeRegister(uint8_t reg, const uint8_t *data, size_t data_size) {
  // Write to a register in the DS3231
  if (ioctl(i2c_bus_fd, I2C_SLAVE, DS3231_ADDRESS) < 0) {
    perror("Failed to acquire bus access and/or talk to slave.\n");
    return false;
  }

  if (write(i2c_bus_fd, data, data_size) != static_cast<ssize_t>(data_size)) {
    perror("Failed to write to the i2c bus.\n");
    return false;
  }

  return true;
}
