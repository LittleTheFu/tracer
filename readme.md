RayTracer
---

![CMake](https://img.shields.io/badge/CMake-v3.16-green)
![C++](https://img.shields.io/badge/C++-17-green)

Suppose you are in the root directory of this project.

Then:

1.make a new folder named "build".

```
mkdir build
```

2.enter this folder.

```
cd build
```

3.generate the project with cmake.

```
cmake ..
cmake --build .
cmake --install .
```

4.then an .exe file named ray_tracer.exe will be generated in the bin folder.

5.after running the program, an image named "img.png" will be created which represents the rendering result.

6.Because the rendering process is time-consuming, you can change the resolution of the image by changing the value resolutionScale in config.cpp.

eg: 
    
    
    int resolutionScale = 16;//this is slow but with more resolution

    int resolutionScale = 2;//otherwise,the opposite



you can get some details in the document folder.(in progressing...)

reference: https://pbr-book.org/4ed/contents

---
![img](document/sample_0.png)
---
![img](document/sample_1.png)
---
![img](document/sample_4.png)
---