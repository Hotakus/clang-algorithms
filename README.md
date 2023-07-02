# Codewars-c

Containing some my codewars' code and some utile algorithms.

---

## Directory Structure

Click links below to see details.

- **[Basic algorithm](./src/algorithms)**: contains some base algorithms such as chain or sort etc.
- **[Katas](./src/katas)**: contains some katas to solve designated problem.
- **[Questions](./src/questions)**: some miscellaneous questions in CodeWars.
- **[CMakeLists.txt](CMakeLists.txt)**: compiles project to static libraries, and you can run 'main' in bin to test functions.

---

## How to use this project?

Nice problem.  
First, compile the project:
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

Now, copy all libs to your own project.  
Oh, don't forget copy each "include" folder in "src" folder to your project.

And if you want, you can run main in "bin" folder to test all functions of this project.
