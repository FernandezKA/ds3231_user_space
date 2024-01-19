#!/bin/bash
# Check if the init.d directory exists and create if not
if [ ! -d "/etc/init.d" ]; then
  sudo mkdir /etc/init.d
fi

# Create the init.d service script
SERVICE_NAME="ds3231_service"
SERVICE_PATH="/etc/init.d/$SERVICE_NAME"

# Writing the service script
cat << EOF | sudo tee $SERVICE_PATH
#!/bin/sh
### BEGIN INIT INFO
# Provides:          DS3231
# Required-Start:    \$remote_fs \$syslog
# Required-Stop:     \$remote_fs \$syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start DS3231 at boot time
# Description:       Enable service provided by DS3231.
### END INIT INFO

case "\$1" in
  start)
    echo "Starting DS3231"
    sudo $HOME/dev/usr_app/DS3231 update
    ;;
  stop)
    echo "Stopping DS3231"
    # Add stop command or script if necessary
    ;;
  *)
    echo "Usage: /etc/init.d/$SERVICE_NAME {start|stop}"
    exit 1
    ;;
esac

exit 0
EOF

# Make the service script executable
sudo chmod +x $SERVICE_PATH

# Add the service to the default runlevels
sudo update-rc.d $SERVICE_NAME defaults

echo "$SERVICE_NAME has been added to system startup"
