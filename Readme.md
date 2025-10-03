Ubuntu (Cmake, ninja, clang)
---

```console
sudo apt install freeglut3-dev cmake clang ninja-build mesa-utils mesa-common-dev libglew-dev libegl1-mesa-dev libgles2-mesa-dev
cd casino_test
cmake -B build.linux -G Ninja . && cd build.linux
cmake --build .
cp ../res/* .
./CasinoTest
```

Windows (Cmake, MSVC 2022)
---

```console
cd casino_test
cmake -B build.win -G "Visual Studio 17 2022" . && cd build.win
cmake --build .
copy ..\res\* Debug && cd Debug
CasinoTest.exe
```
