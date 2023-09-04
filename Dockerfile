# FROM i386/debian
ARG BASE_IMAGE=lordmilko/i686-elf-tools:latest
FROM $BASE_IMAGE
MAINTAINER Amanuel Bogale <abogale2@gmail.com>


WORKDIR /work


RUN apt-get update && apt-get install -y locales && rm -rf /var/lib/apt/lists/* \
	&& localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8

# Install sudo
RUN apt-get update && apt-get install -y sudo

# # Install required packages
RUN apt-get install nasm


# Copy all the files from the host machine to the container
COPY . .


# Build your project
RUN make

# Start your application or execute other commands as needed
CMD ["/bin/bash"]
