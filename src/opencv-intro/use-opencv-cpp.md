# 使用 OpenCV 的 C++ 接口

之前说到，推荐使用 CMake 进行 C++ 项目的构建管理工具。

在如上述文章安装好 OpenCV 后，只需要在 `CMakeLists.txt` 中使用 `find_package(OpenCV REQUIRED)` 即可引入需要的安装包。

> 在使用时可能还需要为 CMake 传入正确的参数，比如，使用 vcpkg 需要指定工具链的路径，使用 Windows 上的预构建版本则需要指定 OpenCV 的路径。具体操作将会在下文介绍。

一个完整的 CMakeLists.txt 文件类似如下：

```cmake
project(CMAKE_OPENCV_TEST)
cmake_minimum_required(VERSION 3.13)

find_package(OpenCV REQUIRED)
message("${OpenCV_DIR}")

add_executable(main "hello.cpp")
target_link_libraries(main ${OpenCV_LIBS})
```

## vcpkg

在 CMake 配置过程中，需要将 vcpkg 目录下的 `scripts/buildsystems/vcpkg.cmake` 文件路径，作为 `CMAKE_TOOLCHAIN_FILE` 变量传入，这样 CMake 就可以识别到该 vcpkg 实例中安装的包了。

比如，假设 vcpkg 的目录位于 `C:/dev/vcpkg/`，则需要在 CMake 的“Configure Args”中添加：

```
-DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake
```

这个选项通常可以在 IDE 的构建选项中找到。如果使用命令行界面，则可以采用类似如下的命令：

```
cmake \
    -B [build directory] \
    -S . \
    -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg]/scripts/buildsystems/vcpkg.cmake"
```

## 预构建版本（Windows）

在 CMake 的配置阶段将 OpenCV 的安装路径作为 `OpenCV_DIR` 变量传入，CMake 就可以识别到安装的 OpenCV 了。

假设安装目录为 `D:\softwares\opencv\`。可以将参数写入 IDE 的构建工具选项：

```
-DOpenCV_DIR=D:/softwares/opencv/build/x64/vc15/lib
```

也可以使用命令行界面进行 CMake 的 Configure 过程：

```
cmake \
    -B [build directory] \
    -S . \
    -DOpenCV_DIR="D:/softwares/opencv/build/x64/vc15/lib"
```

除此之外，也可以使用 `set()` 命令在 CMakeLists.txt 文件中显式指明路径，或者让 CMake 的 `find_package` 在指定目录下查找。

