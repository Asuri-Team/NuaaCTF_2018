FROM asuri/ctf-xinetd:1.0.1
MAINTAINER Yibai Zhang <xm1994@gmail.com>


RUN  sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
RUN  apt-get clean

RUN apt-get update && apt-get install -y libc6-i386
# Clean up example file
RUN rm -fr /etc/xinetd.d/*

# Add prerequest files
RUN useradd -U -m ctf && mkdir -p /home/ctf
ADD dist/pwn /home/ctf/pwn
ADD src/flag /home/ctf/flag
ADD src/pwn.xinetd /etc/xinetd.d/pwn

# Ensure file privileges are correct
RUN chmod 755 /home/ctf/pwn \
    && chmod 444 /home/ctf/flag


ENV CTF_PORT 20000
EXPOSE 20000