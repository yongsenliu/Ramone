#!/bin/bash
clear
echo "Starting avic......"
cd Code/avic/build && cmake .. && make && ./avic -c vcan1