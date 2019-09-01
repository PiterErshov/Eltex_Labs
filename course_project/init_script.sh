#!/bin/bash

cd server/
make
cd ..
cd client_1/
make
cd ..
cd client_2/
make

cd ..

xterm -e './server/server 10.180.13.21 1111 2222 3333 4444' &

xterm -e './client_1/client_1 1111 10.180.13.21 2 message1' &
xterm -e './client_1/client_1 1112 10.180.13.21 2 message2' &
xterm -e './client_1/client_1 1113 10.180.13.21 2 message3' &

xterm -e './client_2/client_2 2222 10.180.13.21' &
xterm -e './client_2/client_2 2223 10.180.13.21' &
xterm -e './client_2/client_2 2224 10.180.13.21' &


