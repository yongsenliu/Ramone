#sudo apt-get install libsdl2-dev libsdl2-image-dev can-utils  

sudo modprobe can
sudo modprobe vcan

sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

sudo ip link add dev vcan1 type vcan
sudo ip link set up vcan1

cd Code

g++ main.cpp src/InputHandler.cpp ../libSocketCan/src/socketcan.cpp -Linclude -L../libSocketCan/include -lncurses  && ./a.out

cd Emulator

g++ main.cpp src/emulator.cpp ../libSocketCan/src/socketcan.cpp -lpthread && ./a.out

#./icsim vcan1
