# master-controller

## Quick startup

```bash
# Running docker container (it will build at first run)
docker-compose up -d

# Running console inside docker environment
docker exec -it rpi-master-controller bash

# Building RPI application and linux unit tests
docker exec -it rpi-master-controller ./scripts/build.sh release
docker exec -it rpi-master-controller ./scripts/build.sh test

# Sending built RPI application to given host
docker exec -it rpi-master-controller ./scripts/deploy.sh IP_ADDRESS

# Creating service to run at startup - run, then execute commands described in the comments
docker exec -it rpi-master-controller ./scripts/create_service.sh IP_ADDRESS

# All the scripts can be run via remote bash session or via docker commands as above.

```