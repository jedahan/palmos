# PalmOS development

This is how to get up and running with a PalmOS 2.0 development environment

[Install docker](https://docs.docker.com/installation/#installation)

    sudo apt-get install -y docker

Pull the latest palmos development image, which contains debian sarge + the palm 3.5 sdk and compilers

    docker pull jedahan/palmos:latest

Edit a string in the resource file *src/example/hello.rcp*

    sed -e "s|Mobile World|$USER|" -i src/example/hello.rcp

Compile a new *hello.rcp*

    make

Copy to your favorite emulator (I prefer [PHEM](https://play.google.com/store/apps/details?id=com.perpendox.phem) for android), or hotsync to a real palm pilot

    sudo adb push src/example/hello.prc /sdcard/phem/card

If you are interested in how I built the images, check out the readmes on [jedahan/debian-sarge](https://registry.hub.docker.com/u/jedahan/debian-sarge/) and [jedahan/palmos](https://registry.hub.docker.com/u/jedahan/palmos/)
