### Compiling project
#### Windows
1. Download project source code and unzip it
2. Download and install c++ compiler (MSVC, MinGW, clang or other)
3. Download and install [make](https://gnuwin32.sourceforge.net/packages/make.htm)
4. Download and intall [cmake](https://cmake.org/download/)
5. Move to the project folder and run `make`

#### Linux (Ubuntu)
1. Download project source code
```shell
$ git clone https://github.com/LiWinDom/raytracing
$ cd raycasting
```
2. Install c++ compiler (g++, clang or other)
```shell
$ sudo apt -y install g++
```
3. Install all project dependencies
```shell
$ sudo apt -y install \
    build-essential python3 make cmake bison flex \
    libffi-dev libgmp-dev libxml2-dev libgdk-pixbuf2.0-dev libcairo2-dev \
    libpango1.0-dev fonts-lyx gtk-doc-tools ghostscript
    libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev \
    libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libdrm-dev libgbm-dev
```

Executables will be in `./bin/Release/`

### Running
```shell
$ cd ./bin/Release/
$ ./Raycasting-Linux ../../example.json --width 1280 --height 720 --noWindow
```
Continue rendering after program close
```shell
$ ./Raycasting-Linux ./latest.rts --noWindow
```