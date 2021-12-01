#!/bin/bash
clear
echo "Setup vcan0 and vcan1."

sudo modprobe can
sudo modprobe vcan

sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

sudo ip link add dev vcan1 type vcan
sudo ip link set up vcan1
