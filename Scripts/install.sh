#!/bin/bash

# Build the application using cmake and make
cmake $PWD/ .
make -j $(nproc) install

# Assuming the executable file is named 'app'
# Copy the executable to ~/dev/usr_app
if [ ! -d "$HOME/dev/usr_app" ]; then
  mkdir -p "$HOME/dev/usr_app"
fi
sudo cp $PWD/bin/DS3231 $HOME/dev/usr_app
sudo chmod a+x $HOME/dev/usr_app/DS3231

echo "DS3231 installed successfully"
