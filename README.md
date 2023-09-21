# onegin
## Installation
Install folders
```
make install
```
---
Build program
```
make
```
---
Build doxygen
```
make doxybuild
```
---
Open docs
```
open doc/html/index.html
```
---
## Input and Output
Program reads info in buffer from input file, to output file.
```
./build/bin/onegin [input file] [output file]
```
Default input file: "onegin.txt".  
Default output file: "output.txt".
## What this program does?
It can sort input data in three different types

1) Alphabet sorting from beginning to end

2) Alphabet sorting from end to beginning

3) Adress sorting (to return original version)
## Sorting
Program sorts data using quick sort alghoritm
