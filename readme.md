SoftRayTracer

中文版说明[点击这里](readme_cn.md)


![CMake](https://img.shields.io/badge/CMake-v3.16-green)
![C++](https://img.shields.io/badge/C++-17-green)
![lodepng](https://img.shields.io/badge/lodepng-blue)
![assimp](https://img.shields.io/badge/assimp-5.4.3-blue)
![powitacq](https://img.shields.io/badge/powitacq-blue)

**This is a soft ray tracing renderer based on the Monte Carlo algorithm.(It doesn't use any third-party rendering APIs.)**

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

4.then an .exe file named `ray_tracer.exe` will be generated in the `bin` folder.

5.after running the program, an image named "img.png" will be created which represents the rendering result.

6.you can change the scene by changing the code in config.cpp.

eg:

    SceneType configScene = SceneType::ROOM_TEAPOT;


Click to see the rendered image seperately:  
- [SceneType::ROOM_SIMPLE](/document/simple_room.png)  
  [![img](/document/preview/simple_room.png)](/document/simple_room.png)  
- [SceneType::ROOM_SIMPLE_BUNNY](/document/simple_room_bunny.png)  
  [![img](/document/preview/simple_room_bunny.png)](/document/simple_room_bunny.png)  
- [SceneType::ROOM_COMPLEX_BUNNY](/document/complex_room_bunny.png)  
  [![img](/document/preview/complex_room_bunny.png)](/document/complex_room_bunny.png)  
- [SceneType::ROOM_TEAPOT](/document/room_teapot.png)  
  [![img](/document/preview/room_teapot.png)](/document/room_teapot.png)  
- [SceneType::ROOM_MATERIAL_BALLS](/document/room_material_balls.png)  
  [![img](/document/preview/room_material_balls.png)](/document/room_material_balls.png)
- [SceneType::ROOM_NORMAL_MAP](/document/room_normal_map.png)  
  [![img](/document/preview/room_normal_map.png)](/document/room_normal_map.png)  



7.Because the rendering process is time-consuming, you can change the resolution and sampler number of the image by changing the value `resolutionScale` and `configSamplersPerPixel` in `config.cpp`.

eg: 
    
    
    int resolutionScale = 16;//this is slow but with more resolution
    int configSamplersPerPixel = 10;//this is slow but with more samplers
---
    int resolutionScale = 2;//this is fast but with less resolution
    int configSamplersPerPixel = 1;//this is fast but with less samplers



you can get some details in the `document` folder.(in progressing...)

reference: https://pbr-book.org/4ed/contents

---
![img](document/sample_0.png)
---
![img](document/sample_1.png)
---
![img](document/sample_4.png)
---