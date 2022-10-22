FROM ubuntu:latest

RUN apt-get update && \
    apt-get upgrade -y
RUN apt-get install -y wget unrar cmake openssh-client
RUN cd /opt/ && \
    wget -O cross-pi-gcc.rar https://github.com/JsBergbau/GCC-cross-compiler-for-Raspberry-PI-Zero-W/releases/download/cross-pi-gcc_gcc-10.1_glibc-2.28_binutils-2.31_Buster/cross-pi-gcc_gcc-10.1_glibc-2.28_binutils-2.31_Buster.rar && \
    unrar x cross-pi-gcc.rar && \
    tar -xvf cross-pi-gcc.tar && \
    rm cross-pi-gcc.tar cross-pi-gcc.rar
ENV PATH "/opt/cross-pi-gcc/bin:/opt/cross-pi-gcc/libexec/gcc/arm-linux-gnueabihf/10.1.0:$PATH"