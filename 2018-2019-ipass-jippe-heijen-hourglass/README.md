# ipass

C++ IPASS PROJECT 2019
============================

This is the github page for the library and implementation I built this year as final assignment.

Dependencies
-----
For abstraction of communication with microcontrollers, this library uses [hwlib](http://github.com/wovo/hwlib) for it's hardware specific pins and wait functions. The included makefile is built for [BMPTK](http://github.com/wovo/bmptk).

Installation
-----
- run `cd ~; git clone htpps://github.com/wovo/installers` to install a batch file for all the software you need.
- run `cd ~/installers; chmod 777 ubuntu1;sudo ./ubuntu1` to install the software packages.
- Download the library `cd ~; git clone http://github.com/jippeheijnen/ipass`
- Now you are ready to run the project. Make sure you have an Arduino due connected to the computer.
```
Note:
You can only use other arduino models if you change the build target
in the makefiles in the/src/main and the /src/project folders.
``` 

Building the implementation
----
- For the following command you need to be in the iPass directory, `cd ~/iPass/`.
- When building the project's implementation, you should be able to just type
  `./runipass` with `hourglass`, `demo`, or `unit_test ` as argument.
  - Note that hwlib and bmptk are automatically installed into the home directory if not present.
  - The run script will try to build and upload the project automatically as well.
  
