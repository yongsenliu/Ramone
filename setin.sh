#!/usr/bin/bash
clear
echo "Starting emulator......"
cd Code/InputHandler && g++ main.cpp src/InputHandler.cpp ../libSocketCan/src/socketcan.cpp -Linclude -L../libSocketCan/include -lncurses  && ./a.out


