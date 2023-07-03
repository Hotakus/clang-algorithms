# Hotakus' Clang Algorithms

contains some useful algorithms adn data structures, and can help you 
develop.

---

## Directory Structure

Click links below to see details and API.

- **[Algorithms](./src/algorithms) - ([Details](./src/README.md))**: Some algorithms may be useful.
- **[Data Structures](./src/data_structures) - ([Details](./src/README.md))**: Some useful data structures. 
- **[Katas](./src/katas) - ([Details](./src/katas/README.md))**: Some katas or tricks may be useful , such as MSE, LCS, Big Num problems.
- **[Questions](./src/questions) - ([Details](./src/questions/README.md))**: Some miscellaneous questions that may be unuseful in CodeWars .
- **[CMakeLists.txt](CMakeLists.txt)**: Compiles project to static libraries, and you can run 'main' in bin to test functions.

---

## How to use directly this project?

Nice problem, and easy to use.  

You must fetch the repo to your project folder. and then, in `CmakeLists.txt` of your project (not this project),
add these codes below:
```cmake
add_subdirectory(./clang-algorithms/)
add_executable(your_project_name main.c)
target_link_libraries(your_project_name hca)
```
And then, in your `main.c`:
```c
#include <stdio.h>
int main() {
    printf("Welcome to use Hotakus' clang algorithms!!!\n")
    hca_test();     // do test for some functions of hca.
    hash_test();    // Hash table test
    return 0;
}
```

---

## Just compile


```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCW_KATA_ARM=0
make
```

and you can see the definition `-DCW_KATA_ARM=0`, this option is for ARM(or Embedded System)
you can open [CMakeLists.txt](CMakeLists.txt) and find "CW_KATA_ARM", change options in it.
and run in "build" folder👇:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCW_KATA_ARM=1
make
```
OK, all libs were compiled and move to "lib" folder in root path.

---