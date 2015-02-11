This is how to get up and running with a PalmOS 2.0 development environment


Make sure to install [docker](http://docker.io)

Then `docker build` will get the image I made for all this - debian sarge with palmos dev tools installed.

Lets mount **src** in **jedahan/palmos:/mnt/src** , so we can just make from the container to get the prc file:

   docker run --volume=["./src:/mnt"] jedahan/palmos 

Now to compile, run

   docker run jedahan/palmos make

That's it!
