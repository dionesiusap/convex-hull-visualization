# CONVEX HULL VISUALIZER
Solving convex hull problem for a set of points using quick hull algorithm and visualizing the result in a window.

## Getting Started
### Contents
This project contains source codes and libraries which are located in `source` directory. Below is the directory tree of this project.
```
convex-hull-visualization/
├── source/
|   ├── visualizer/
|   |   ├── visualizer.hpp
|   |   ├── visualizer.cpp
|   |   └── CMakeLists.txt
|   ├── cvxhull.cpp
|   └── gltest.cpp
├── CMakeLists.txt
└── build.sh
```
### Installation
For first installation, execute `build.sh`. In command line, type in the following command:
```
$ chmod +x build.sh
$ ./build.sh
```
The first command will change the permission so that the script can be executed. The second command will execute `build.sh`.  
What `build.sh` does is basically creating `build` directory, creating Makefiles for the source codes, and compiling the program in that directory using `make`.  

## Usage
This project consists of 2 drivers, `cvxhull.cpp` and `gltest.cpp`. `cvxhull.cpp` is used to solve and visualize convex hull problem for a set of points and `gltest.cpp` is used to test OpenGL library API.
### gltest
To execute the program, in `build` directory, type in the following command in command line:
```
$ ./gltest
```
This will create a window. Type `ctrl+C` in command line to destroy the window and close the program.
### cvxhull
The `cvxhull` executable takes 0 or 1 parameter with the execution. If 1 parameter is given, it will take the parameter as the number of points that will be generated. If 0 parameter is given, user will be prompted to input the number of points that will be generated.  
To execute the program, in `build` directory, type in the following command in command line:
```
$ ./cvxhull
```
for 0 parameters or
```
$ ./cvxhull n #replace n with any integer > 0
```
The execution will create a window visualizing the convex hull solution. Press `esc` while the window is active or `ctrl+C` in command line to destroy the window and close the program.
### Program Runtime Example
An example of program runtime.
```
$ ./cvxhull 10
POINTS:
1. (-86,-76)
2. (60,-70)
3. (-97,-35)
4. (61,61)
5. (80,35)
6. (100,19)
7. (70,-83)
8. (-94,73)
9. (-35,59)
10. (-60,-57)

EDGES OF CONVEX HULL POLYGON: 
1. {(-94,73),(-97,-35)}
2. {(61,61),(-94,73)}
3. {(61,61),(100,19)}
4. {(-86,-76),(70,-83)}
5. {(-86,-76),(-97,-35)}
6. {(70,-83),(100,19)}

Execution time: 0.066 ms
```
