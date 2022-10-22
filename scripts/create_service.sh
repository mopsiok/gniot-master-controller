#!/bin/sh
IP=${1:-192.168.0.234}
scp scripts/master-controller.service pi@$IP:~/
ssh pi@$IP
# then, execute:
# sudo mv ~/master-controller.service /etc/systemd/system/
# sudo chown -R root:root /etc/systemd/system/master-controller.service
# sudo systemctl daemon-reload
# sudo systemctl enable master-controller.service