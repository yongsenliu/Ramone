#!/bin/bash
clear

cd ..
cd build

gnome-terminal --title=Emulator --geometry 130x7+850+1000 -- ./bin/Emulator
gnome-terminal -- ./bin/avic -c vcan1
gnome-terminal --title=InputHandler --geometry 70x10+50+1000 -- ./bin/InputHandler
