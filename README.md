# master-controller

## RPI Zero W setup (Not validated)

1. Access your RPI SD card and edit `config.txt` file, adding:
    ```
    enable_uart=1
    ```

2. Make sure that the line below is present in `cmdline.txt`:
    ```
    console=serial0,115200 console=tty1
    ```

3. After login:
    ```
    sudo apt-get update
    sudo apt-get upgrade
    ```

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