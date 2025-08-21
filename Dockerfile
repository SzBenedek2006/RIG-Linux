# This is the official Dockerfile for RIG-Linux.
FROM debian:13

ENV REPO=https://github.com/SzBenedek2006/RIG-Linux.git

RUN apt update -y && apt install -y git build-essential gcc-i686-linux-gnu gcc-aarch64-linux-gnu gcc-arm-linux-gnueabihf gcc-riscv64-linux-gnu
