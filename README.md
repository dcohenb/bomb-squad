# Bomb Squad
This is a repo for our Geekcon 2019 project - "Bomb Squad"

## Installing the `arduino-cli` on mac:
```sh
# Installing the CLI
sudo curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/local/bin sh

### RESTART THE SHELL HERE ###

# Update the local pacakges
arduino-cli core update-index

# Show all the connected boards
arduino-cli board list

# This installs the compiler for our specific board type
arduino-cli core install arduino:avr

# Install the neopixel library
arduino-cli lib install "Adafruit NeoPixel"

# Compile the sketch (and get the hex file)
arduino-cli compile -b arduino:avr:mega -o build/bomb_squad src/Bomb_Squad.ino

# Upload the sketch to the board (replace the port with the board you got from the board list)
arduino-cli upload -p /dev/cu.usbmodem1421301 -b arduino:avr:mega -i build/bomb_squad
```

glhf