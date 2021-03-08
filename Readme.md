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


