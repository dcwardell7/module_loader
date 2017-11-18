#Module Loader
Dynamically loads shared objects at runtime

##Getting started
Currently only verified on Ubuntu16.04 and G++ 5.4
1. Build the library ```make```
2. Build and run the test program ```make test```

##Motivation
Shared objects (so) permit linking at runtime which provides
1. Loose coupling between the libraries and the executable
2. Improved compilation time with modular builds
4. Smaller executables via library selection at runtime

##Usage
Check the ```test/``` and ```makefile``` for an example on how to:
1. write and generate shared objects
2. use ```sil::ModuleLoader``` in your code

##Swag
Notice the use of the [Pimple pattern](https://marcmutz.wordpress.com/translated-articles/pimp-my-pimpl-reloaded/) in ```include/sil/module_loader.hpp``` to hide implementation details and eliminate include chaining.

##Feedback
I appreciate any feedback and helpful hints on how to improve.

##Contributing
Pull requests are welcome
