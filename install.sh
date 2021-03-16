#!/bin/bash
xhost +
mkdir save
cd save
touch save.txt
cd ..
docker run  -e  "DISPLAY=$DISPLAY" -v "/tmp/.X11-unix:/tmp/.X11-unix:ro" \
 -v "$(pwd)/save/save.txt:/e-chess/files/backup/save.txt"  coderon98/e-chess:latest
