FROM asuri/ctf-xinetd:1.0.1
MAINTAINER Yibai Zhang <xm1994@gmail.com>


RUN  sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
RUN  apt-get clean

RUN apt-get update && apt-get install -y libc6-i386
# Clean up example file
RUN rm -fr /etc/xinetd.d/*
RUN apt-get install python3 python3-pip

# Add prerequest files
RUN useradd -U -m ctf && mkdir -p /home/ctf

# Get web3 and run flag sender
RUN cd /home/ctf && mkdir .pip && echo "[global]\nindex-url = https://pypi.tuna.tsinghua.edu.cn/simple/\n" > /home/ctf/.pip/pip.conf
RUN pip3 install web3
ADD dist/spy_event_then_sendflag.py /home/ctf/spy_event_then_sendflag.py
RUN nohup python3 spy_event_then_sendflag.py &

# Ensure file privileges are correct
# RUN chmod 755 /home/ctf/pwn \
#     && chmod 444 /home/ctf/flag


# ENV CTF_PORT 20000
# EXPOSE 20000