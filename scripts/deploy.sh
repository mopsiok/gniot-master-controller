#!/bin/sh
IP=${1:-192.168.0.234}
scp build/src/master_controller pi@$IP:~/playground/