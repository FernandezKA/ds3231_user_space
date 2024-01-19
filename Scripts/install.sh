#!/bin/bash

# Build the application using cmake and make
cmake $PWD/ .
make -j $(nproc) install

# Make 'install.sh' executable
sudo chmod a+x $PWD/Scripts/install.sh

# Assuming the executable file is named 'app'
# Copy the executable to ~/dev/usr_app
if [ ! -d "$HOME/dev/usr_app" ]; then
  # Create 'usr_app' directory if it doesn't exist
  mkdir -p "$HOME/dev/usr_app"
fi

# Copy 'DS3231' executable to 'usr_app' directory
sudo cp $PWD/bin/DS3231 $HOME/dev/usr_app
sudo chmod a+x $HOME/dev/usr_app/DS3231

# Print success message
echo "DS3231 installed successfully"