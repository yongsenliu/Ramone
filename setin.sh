#!/usr/bin/bash
clear
echo "Starting emulator......"
cd Code/InputHandler && g++ InputHandler.cpp src/InputHandlerSource.cpp ../libSocketCan/src/socketcan.cpp -Linclude -L../libSocketCan/include -lncurses  && ./a.out


