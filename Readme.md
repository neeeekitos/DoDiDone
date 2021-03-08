Docker install and image pull

Debian:
- Install Docker : https://docs.docker.com/engine/install/debian/
- Create account on Docker Hub : https://docs.docker.com/docker-hub/

- Run following : `xhost +`

- Login into your Docker account : `sudo docker login`
- (*) Pull docker image for e-chess : `sudo docker pull coderon98/e-chess:beta`
- (**) Build docker container and runs it : `sudo docker run -it --name e-chess -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro coderon98/e-chess:beta`

- Rerun (*) each time docker-files are updated
- Rerun `sudo docker rm e-chess && sudo docker run -it --name e-chess -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro coderon98/e-chess:beta` each time you want to launch the app (remove container and rebuild it)

##GUI ON MAC

1. Install XQuartz via brew

$ brew cask install xquartz

2. Logout and login of your Mac to activate XQuartz as default X11 server

3. Start XQuartz

$ open -a XQuartz

4. Go to Security Settings and ensure that "Allow connections from network clients" is on

![image](https://user-images.githubusercontent.com/57397713/110298714-30f4d980-7ff5-11eb-8ba6-90549537e0d0.png)

5. $ defaults write org.xquartz.X11 enable_iglx -bool true

6. Restart your Mac and start XQuartz again`

$ open -a XQuartz

7. Check if XQuartz is setup and running correctly

$ ps aux | grep Xquartz

8. Ensure that XQuartz is running similar to this: `/opt/X11/bin/Xquartz :0 -listen tcp

:0 means the display is running on display port 0 Important is that its not saying –nolisten tcp which would block any X11 forwarding to the X11 display.

9. Allow X11 forwarding via xhost

$ xhost +

This allows any client to connect. If you have security concerns you can append an IP address for a whitelist mechanism. You will always have to run `xhost + after a restart of X11 as this is not a persistent setting``

Time to test X11 forwarding`

10. Pull the following docker container, set the DISPLAY env and run it...

$ docker pull sshipway/xclock
$ ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
$ docker run -it --name e-chess -e DISPLAY=$ip:0 -v /tmp/.X11-unix:/tmp/.X11-unix:ro coderon98/e-chess:beta
