RayTracer
---

![CMake](https://img.shields.io/badge/CMake-v3.16-green)
![C++](https://img.shields.io/badge/C++-17-green)

假设你位于该项目的根目录。

接下来:

1.创建一个名为 "build" 的新文件夹。

```
mkdir build
```

2.进入该文件夹。

```
cd build
```

3.使用 CMake 生成项目。

```
cmake ..
cmake --build .
cmake --install .
```

4.然后会在 `bin` 文件夹中生成一个名为 `ray_tracer.exe` 的可执行文件。

5.运行程序后，会生成一张名为 "img.png" 的图像，表示渲染结果。

6.你可以通过修改 `config.cpp` 中的代码来更改场景。

例如:

    SceneType configScene = SceneType::ROOM_TEAPOT;

7.由于渲染过程耗时较长，你可以通过修改 `config.cpp` 中的 `resolutionScale` 和 `configSamplersPerPixel` 来调整图像分辨率和采样数。

例如:

    int resolutionScale = 16; // 这种设置较慢但分辨率更高
    int configSamplersPerPixel = 10; // 这种设置较慢但采样更多
---
    int resolutionScale = 2; // 这种设置较快但分辨率较低
    int configSamplersPerPixel = 1; // 这种设置较快但采样较少
---

你可以在 `document` 文件夹中找到更多详细信息（正在编写中...）

参考：[pbr-book.org/4ed/contents](https://pbr-book.org/4ed/contents)

---
![img](document/sample_0.png)
---
![img](document/sample_1.png)
---
![img](document/sample_4.png)
---