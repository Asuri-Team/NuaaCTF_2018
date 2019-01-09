FROM phusion/baseimage

RUN apt-get update && \
    apt-get install python python-pip -y && \
    pip install flask flask_sqlalchemy flask_migrate -i https://pypi.tuna.tsinghua.edu.cn/simple && \
    rm -rf /var/lib/apt/lists/*

RUN groupadd ctf && \
    useradd -g ctf ctf -m && \
    password=$(openssl passwd -1 -salt 'abcdefg' '123456') && \
    sed -i 's/^ctf:!/ctf:'$password'/g' /etc/shadow

WORKDIR /home/ctf
COPY ./xk .
RUN chown -R ctf:ctf . && \
    chmod -R 750 .

ADD ./start_xk.sh /etc/my_init.d/
RUN chmod u+x /etc/my_init.d/start_xk.sh