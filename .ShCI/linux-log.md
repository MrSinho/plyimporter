# PlyImporter
![linux_badge](linux-status.svg)
## [Linux/Unix build logs:](https://github.com/MrSinho/ShCI)
  
```bash
$$shci call$$:
apt install -y wget gcc cmake make gdb
```

```bash
$$shci call$$:
cd PlyImporter && mkdir build && cd build && cmake .. && cmake --build .
-- The C compiler identification is GNU 11.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/mrsinho/Desktop/ShCI-implementation/bin/PlyImporter/build
[ 50%] Building C object CMakeFiles/PlyImporter.dir/PlyImporter/src/PlyImporter.c.o
[100%] Linking C static library ../bin/libPlyImporter.a
[100%] Built target PlyImporter
