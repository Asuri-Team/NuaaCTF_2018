#!/bin/bash
su ctf -c "nohup python /home/ctf/run.py >/dev/null 2>&1 &"
/etc/init.d/ssh start -D
