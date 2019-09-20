#!/bin/sh
arduino-cli upload -p /dev/cu.usbmodem1421301 -b arduino:avr:uno -i build/bomb_squad
