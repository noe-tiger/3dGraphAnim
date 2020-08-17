# 3D Graphics & Animation Coursework

This project was done during a coursework in final year MSc,  
Before this project i never tried to use OpenGL and the last C++ project i worked on was almost one year ago.

## Installation
Make sure you have CMake and Conan installed

install CMake : [Download](https://cmake.org/install/)  
install conan : `pip install conan` with python3

if conan fails, try to add the remote with this command
```
conan remote add <REMOTE> https://api.bintray.com/conanbincrafters/public-conan

```

### Linux
```
  > bash bld
```
if the command fails, you can execute theses commands
```
  > mkdir build
  > cd build
  > conan install .. --build=missing
  > cmake .. -G “Unix Makefiles”
  > cmake --build .
```

### Windows
You need to have Visual Studio installed  
you may also need to replace the Visual Studio version depending on the one installed on your computer
```
  > mkdir build
  > cd build
  > conan install .. -s build_type=Debug --build=missing
  > cmake .. -G "Visual Studio 16 2019" <- replace with your version
  > cmake --build .
```

## commands to execute

then execute the binary file located at :
```
  /build/bin/tetris-binary.exe
```

## Author

[Noé TIGER](noe.tiger192@gmail.com)
