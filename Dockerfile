FROM debian:latest

MAINTAINER "Rivaldo de SOUZA"


ENV DISPLAY :0
ENV DEBIAN_FRONTEND=noninteractive


RUN apt-get update -yq \
&& apt-get install apt-utils curl gnupg -yq \
&& curl -sL https://deb.nodesource.com/setup_10.x | bash \
&& apt-get install git -yq \
&& apt-get install -qqy x11-apps \
&& apt-get install cmake  -yq \
&& apt-get install libsfml-dev -yq \
&& apt-get install build-essential -yq \
&& apt-get install g++ gcc -yq \
&& apt-get install gdb -yq \
&& apt-get install rsync -yq \
&& apt-get install tar -yq \
&& apt-get install python -yq \
&& apt-get install clang -yq \
&& apt-get clean -y


RUN  git clone https://github.com/neeeekitos/e-chess.git


WORKDIR /e-chess


ENTRYPOINT ["/bin/bash"]


CMD ["./consoleLaunch.sh"]


# docker build -t e-chess:beta .
# docker run -it --rm --name e-chess -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro e-chess:beta


# docker run -d --name e-chess -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro coderon98/e-chess:beta



# docker tag e-chess:beta coderon98/e-chess:beta
# docker push coderon98/e-chess:beta
# docker pull coderon98/e-chess:beta
