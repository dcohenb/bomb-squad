#!/bin/sh
arduino-cli upload -p /dev/cu.usbmodem1441301 -b arduino:avr:mega -i build/bomb_squad
