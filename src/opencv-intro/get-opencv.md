# 如何获得 OpenCV

OpenCV 是一个软件库，因此需要我们通过编程调用其接口，以使用其中的功能。

本节介绍 OpenCV 的安装。关于 OpenCV 的使用参见下一节。

## Windows

Windows 用户可以参考下面的教程。

### MSYS2

如果用户希望使用 MinGW-w64 GCC 作为编译器，可以安装 MSYS2 来配置开发环境。

MSYS2 的包管理器提供有 ffmpeg、OpenCV 等工具。得益于包管理器，这些软件的安装、使用都比较方便。

关于 MSYS2 的安装这里暂时不再赘述，详情参见 [msys2.org](https://www.msys2.org/)。

一般来说，在初次安装后可能还需要配置镜像源以便更快速地下载软件包。此外，也建议将 MSYS2 的安装目录及之后的工作目录添加进反病毒软件如 Windows Defender 的“排除项”中，以期在使用时获得更高的运行效率。

首次进入 MSYS2 后，需要先安装 MinGW-w64 64-bit 的工具链：

```console
$ pacman -S mingw-w64-x86_64-toolchain
```

> `i686` 是 32 位指令集，而 `x86_64` 是 64 位指令集（有时也称 `amd64`）。对于 64 位机，自然使用针对 64 位指令集的软件更合适。

之后，等待安装过程完成。

接下来，可以安装对应工具链适用的 OpenCV 了（事实上 MSYS2 也只有这一种）.

```console
$ pacman -S mingw-w64-x86_64-opencv
```

待安装过程结束即可。关于如何使用将在下一节介绍。

### vcpkg

如果用户使用的是微软的 MSVC，则建议搭配 [CMake](https://cmake.org/) 和 [vcpkg](https://vcpkg.io/) 使用。

vcpkg 是一款开源的、基于源代码的 C++ 依赖管理器。简单地说，用户可以使用 vcpkg 安装自己需要的 C++ 依赖。

将 vcpkg 的整个仓库克隆在本地，再执行提供的脚本，即可完成 vcpkg 的部署，详情参见 [vcpkg 仓库的 README](https://github.com/microsoft/vcpkg) 或 [网站上的说明材料](https://vcpkg.io/en/getting-started.html)。

> 无论是 vcpkg 还是之后 OpenCV 的代码，都是从 GitHub 取得的，因此可能需要用户具有相应的网络访问环境。笔者实验时，vcpkg 会**自动使用系统代理**（如果进行了相应的配置），但执行 `git clone` 可能需要在终端中**手动设置 HTTP 和 HTTPS 代理服务器地址相关的环境变量**。

vcpkg 的若干实例是互不影响的。用户可以在计算机上部署多个 vcpkg 的实例。针对其这个特性，用户可以先切换到 vcpkg 的目录下再执行命令，而不是将其添加到 PATH。

由于 vcpkg 是基于源代码的，因此在安装 OpenCV 之前，需要用户先安装微软的编译器 MSVC。

用户在终端中切换到 vcpkg 的安装目录后，执行下面命令即可安装 OpenCV：

> 笔者在实验时还发现，还需要额外安装 Visual Studio 的英语（English）语言包，才能顺利执行安装操作。

```console
PS> ./vcpkg install opencv
```

需要注意，对于 OpenCV 以及其他一些包，vcpkg 在安装时**有不同的 feature 可供选择**。可以在 [vcpkg 网站上检索包对应的信息](https://vcpkg.io/en/packages.html)，或者使用 `./vcpkg search <packagename>` 进行检索。

比如，我们可以执行下面的命令，选择需要的 feature 并进行安装：

```console
PS> ./vcpkg install opencv[core,dnn,jpeg,png,quirc,tiff,webp]
```

之后便会开始相对比较漫长的代码编译过程，可能会耗费约数十分钟或更久。同样，建议将 vcpkg 的目录添加进反病毒软件的排除项，可以加快速度。

除此之外，在 Windows 上，上述命令默认将会构建针对 x86-windows 平台的 OpenCV，我们还需要手动指定构建安装针对 x64-windows 平台的 OpenCV。

```console
opencv[core,dnn,eigen,ffmpeg,ipp,jpeg,openmp,png,qt,quirc,tiff,webp]:x64-windows
```

编译过程中会产生很多文件（如 vcpkg 目录下的 buildtrees 目录，存放构建过程中产生的文件，如果保留可能会减少下次更新时花费的时间），可能会占用十数 GB 的磁盘空间。可以根据需要删除这些中间文件。

### 预构建版本（Windows-MSVC）

也可以在 [OpenCV GitHub 仓库的 Release 页](https://github.com/opencv/opencv/releases) 下载 OpenCV 提供的预构建版本。目前为 Windows 提供的预构建版本是针对 MSVC 的，文件名类似 `opencv-<version>-vc14_vc15.exe`。

下载好 OpenCV 预构建版本后，安装在指定的目录即可，这里假设安装目录为 `D:\softwares\opencv\`。

同样，推荐使用 CMake 作为构建管理工具，具体使用方法在下一节介绍。

### Python

上述为 C++ 的安装使用。如果使用 Python，可以使用 pip 安装 OpenCV。

在配置好 Python 以及 pip 的情况下，只需要在终端中执行：

```
pip install opencv-python
```

或者

```
python -m pip install opencv-python
```

## Ubuntu

关于 Ubuntu 的软件源配置这里不作赘述。

大多数的桌面 Ubuntu 版本都可以从软件仓库获得 OpenCV。

更新软件源：

```console
$ sudo apt update 
```

安装用于开发的 OpenCV：

```console
$ sudo apt install libopencv-dev 
```

> 其他平台如 NVIDIA Jetson，虽然搭载 Ubuntu 操作系统，但是 OpenCV 的安装与此不同。可以参见其他关于 NVIDIA Jetson 的配置记录。

## macOS

先安装 XCode 命令行工具。在终端中执行：

```
xcode-select --install
```

之后可以安装 Homebrew，并使用 Homebrew 安装 OpenCV。

> 由于笔者未持有运行 macOS 的设备，因而有关 macOS 的记录尚不完善。

## 从源码编译 OpenCV

除了使用 vcpkg，用户也可以自行下载 OpenCV 的源代码，并且编译 OpenCV。这往往是在用户需要使用 opencv_contrib 中的代码时进行的工作。一般情况下，使用上述的安装方式会更为轻松。

（未完待续）
