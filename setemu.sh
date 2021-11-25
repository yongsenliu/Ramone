#!/bin/bash
clear
echo "Starting emulator......"
cd Code/Emulator && g++ main.cpp src/emulator.cpp ../libSocketCan/src/socketcan.cpp -lpthread && ./a.out
