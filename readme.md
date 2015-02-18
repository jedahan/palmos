# ZaZa

This is an app, called zaza, for bard graduate center.

You can download [the latest release](https://github.com/jedahan/palmos/archive/v0.2.0.zip) and put it on an emulator, like [phem][].

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

Copy to your favorite emulator (I prefer [phem][] for android), or hotsync to a real palm pilot

    sudo adb push src/example/hello.prc /sdcard/phem/card

If you are interested in how I built the [jedahan/debian-sarge](https://registry.hub.docker.com/u/jedahan/debian-sarge/) and [jedahan/palmos](https://registry.hub.docker.com/u/jedahan/palmos/) images, take a look at the [Makefile](Makefile).

[phem]: https://play.google.com/store/apps/details?id=com.perpendox.phem
