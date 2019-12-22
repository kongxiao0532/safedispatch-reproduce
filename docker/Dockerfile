FROM ubuntu:18.04

COPY ali_sources.list /etc/apt/sources.list
RUN apt-get update
RUN apt-get install -y ca-certificates
# Install dependencies
RUN apt-get install -y build-essential ninja-build curl unzip vim\
    autoconf automake cmake dpkg-dev file git make patch \
    libc-dev libc++-dev  \
    dirmngr gnupg2 lbzip2 wget xz-utils libtinfo5 wget
RUN wget https://github.com/llvm/llvm-project/archive/llvmorg-9.0.0.zip

COPY install.sh .
ENTRYPOINT ["/bin/sh", "./install.sh"]
