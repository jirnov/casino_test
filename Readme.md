Ubuntu
---

sudo apt install freeglut3-dev cmake clang ninja-build mesa-utils mesa-common-dev libglew-dev libegl1-mesa-dev libgles2-mesa-dev
cd casino_test
mkdir build
cd build
cmake -G Ninja ..
