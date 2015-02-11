This is how to get up and running with a PalmOS 2.0 development environment


Make sure to install [docker](http://docker.io)

Then `docker build` will create a fresh image of debian sarge with all the utilities and sdk to build your own palm pilot software.

To test that it works, `cd example && make && exit` in the docker shell.

Copy the newly build program to your current folder with `docker cp jedahan/palmos:/root/example/hello.prc .`

Now, copy to whatever palm emulator you want to run, and see if it works!
