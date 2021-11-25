#!/bin/bash
clear
echo "Starting emulator......"
cd Code/Emulator && g++ Emulator.cpp src/EmulatorSource.cpp ../libSocketCan/src/socketcan.cpp -lpthread && ./a.out
