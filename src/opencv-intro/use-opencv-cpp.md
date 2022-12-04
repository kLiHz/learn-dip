# 使用 OpenCV 的 C++ 接口

之前说到，推荐使用 CMake 进行 C++ 项目的构建管理工具。

在使用时可能还需要为 CMake 传入正确的参数，比如，使用 vcpkg 需要指定工具链文件的路径，使用 Windows 上的预构建版本则需要指定 OpenCV 的路径。具体操作将会在下文介绍。

## 不同工具链需要进行的配置

### vcpkg

在 CMake 配置过程中，需要将 vcpkg 目录下的 *scripts/buildsystems/vcpkg.cmake* 文件路径，作为 `CMAKE_TOOLCHAIN_FILE` 变量传入，这样 CMake 就可以识别到该 vcpkg 实例中安装的包了。

比如，假设 vcpkg 的目录位于 *C:/dev/vcpkg/*, 则需要在 IDE 中 CMake 相关设置的 "Configure Args" 中添加下列命令行参数选项:

```
-DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake
```

如果使用命令行界面，则可以采用类似如下的命令：

```
cmake \
    -B [build directory] \
    -S . \
    -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg]/scripts/buildsystems/vcpkg.cmake"
```

### 预构建版本 (Windows)

可以在 [OpenCV 对应 GitHub 仓库的 Release](https://github.com/opencv/opencv/releases) 中, 下载到适用于 64 位 Windows 的 OpenCV 预构建版本.

本文写作时, 最新的预构建版本发布为 *opencv-4.6.0-vc14_vc15.exe*, 为一个可执行的自解压程序.

需要注意的是, 虽然文件名提示该发布构建时使用的 Visual Studio 版本为 `vc14` 和 `vc15`, 但由于 Visual Studio 2015 以及之后的版本均保证二进制兼容性 (参见
[C++ binary compatibility between Visual Studio versions - Microsoft Learn](https://learn.microsoft.com/en-us/cpp/porting/binary-compat-2015-2017)),
因此仍能搭配新版本的 Visual Studio 工具链使用.

下载后完成后运行该程序, 选择解压路径, 程序会将文件解压到选择路径的 *opencv* 目录下. 比如指定提取路径为 *D:/softwares/*, 则提取完成后文件将位于 *D:/softwares/opencv/* 目录下.

由于预构建版本中提供的 *OpenCVConfig.cmake* 文件链接动态库时使用的是相对路径, 为了构建出的程序能够寻找到对应的动态库, 进而正常执行, 我们还需要将对应库文件的路径添加到 `PATH` 环境变量中, 或者把文件复制到构建出的可执行文件所在的目录下.

这里我们使用 `vc15` 的构建版本, 则二进制文件所在的目录为 *D:/softwares/opencv/build/x64/vc15/bin* (若将 *D:/softwares/opencv/build/x64/vc15* 称作 `OPENCV_DIR`, 则二进制文件目录即为其下的 *bin* 目录).

预构建版本中将所有的库打包成了一个后缀为 *world* 的 DLL, 即 *opencv\_world460.dll* 和 *opencv\_world460d.dll*. 除此之外还有一些其它的 DLL 库文件, 这里暂不介绍. 文件名中的数字表示版本号, 末尾的 `d` 表示为 Debug 版本, 否则则为 Relase 版本. 文件名后缀为 *.pdb* 的文件为对应的调试信息文件. 文件后缀为 *.exe* 的文件为实用程序.

如果是在开发机器上, 则将上述提到的 `bin` 目录添加进 PATH 环境变量即可 (如果更新 OpenCV 则需要记得更新环境变量).

如果是将构建好的程序分享给别人使用, 则建议将对应的 *.dll* 和 *.pdb* 文件一同打包 (如果是 Debug 版本, 记得使用文件名带 `d` 的文件).

如前文所说, 在开发过程中建议使用 CMake, 则在 CMake 的配置阶段将 OpenCV 的安装路径下的 `lib` 目录作为 `OpenCV_DIR` 变量传入, CMake 就可以识别到安装的 OpenCV 了.

可以将参数写入 IDE 的构建工具选项：

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

除此之外，也可以使用 `set()` 命令在 CMakeLists.txt 文件中显式指明路径，或者让 CMake 的 `find_package` 命令在指定目录下查找。

## CMakeLists.txt

在如上述配置好 OpenCV 后，只需要在 `CMakeLists.txt` 中使用 `find_package(OpenCV REQUIRED)` 即可引入需要的安装包。

一个完整的 CMakeLists.txt 文件类似如下：

```cmake
project(CMAKE_OPENCV_TEST)
cmake_minimum_required(VERSION 3.13)

find_package(OpenCV REQUIRED)
message("${OpenCV_DIR}")

add_executable(main "hello.cpp")
target_link_libraries(main ${OpenCV_LIBS})
```
