
# Point
This is a project in which i created a program that would simulate the organization of virtual memory in running
process. 
This was done through creating dynamic doubly linked list for storing integers.

Refer below for futher info

# Important information
If you just want to see the most recent code base, go to /src/previous_steps/step4.c -- this is the most recent build,
without any optional headers that are used within /src/step4.c

If you want to run /src/step4.c then you will have to build this through xmake. or comment out some headers.


# Tree :
```alanguagelanguagelanguagelanguage

.
├── build
│   └── linux
│       └── x86_64
│           ├── step_1
│           │   ├── debug
│           │   │   └──simulation
│           │   ├── release
│           │   │   └──simulation
│           │   └── valgrind
│           │       └──simulation
│           ├── step_2
│           │   ├── debug
│           │   │   └──simulation
│           │   ├── release
│           │   │   └──simulation
│           │   └── valgrind
│           │       └──simulation
│           ├── step_3
│           │   ├── debug
│           │   │   └──simulation
│           │   ├── release
│           │   │   └──simulation
│           │   └── valgrind
│           │       └──simulation
│           └── step_4
│               ├── debug
│               │   └──simulation
│               ├── release
│               │   └──simulation
│               └── valgrind
│                   └──simulation
├── config
│   ├── minimal.lua
│   └── sample.lua
├── helper
│   └── log.c
│       ├── LICENSE
│       ├── README.md
│       └── src
│           ├── liblog.a
│           ├── log.c
│           ├── log.h
│           └── log.o
├── main.pdf
├── readme.md
├── src
│   ├── include
│   │   └── step4.h
│   ├── previous_steps
│   │   ├── step1
│   │   │   ├── a.out
│   │   │   ├── step1.c
│   │   │   └── step1.h
│   │   ├── step2
│   │   │   ├── a.out
│   │   │   ├── step2.c
│   │   │   └── step2.h
│   │   ├── step3
│   │   │   ├── a.out
│   │   │   ├── step3.c
│   │   │   └── step3.h
│   │   ├── step4
│   │   │   ├── step4
│   │   │   └── step4.c
│   │   └── temp_folder
│   │       └── step1.c
│   ├── step4.c
│   └── test
│       └── dummy_test
└── xmake.lua

```

# No Xmake, and just want to run the code?

I understand that xmake might not be avaliable to everyone, or just that your test systems might not have it:

####  Solution   :

. I have made an easy way of testing my work , if you are testing the  output directly, and that is through each build

. If you want to see the code for each given step that i have produced, please refer to previous steps, this can be
directly built, i.e gcc step3.c  and you can just run ./a.out and will work as everything is built in .

```o
├── src
│   ├── include
│   │   └── step4.h  -- Only for xmake and for the file step4.c (local) else ignore
│   ├── previous_steps
│   │   ├── step1
│   │   │   ├── a.out
│   │   │   ├── step1.c
│   │   │   └── step1.h
│   │   ├── step2
│   │   │   ├── a.out
│   │   │   ├── step2.c
│   │   │   └── step2.h
│   │   ├── step3
│   │   │   ├── a.out
│   │   │   ├── step3.c
│   │   │   └── step3.h
│   │   ├── step4
│   │   │   ├── step4
│   │   │   └── step4.c
│   │   └── temp_folder
│   │       └── step1.c
``````

You can test the code through these steps ^

# How to run with xmake ?

1. Ensure you have xmake installed - by running xmake it should just run - and you should have your build version
2. Lua is required, check xmake for requirments .
3. xmake and go to the build folder

```language
xmake f --mode=release || debug || valgrind
xmake
```
You can change the parameters of xmake through xmake.lua, by running xmake, you build the program and you can then go
check that within the build folder


### Some info

Why xmake ?

Im learning c++ currently and wanted to implement some process within this project, I thought it would be fun, using
a build path and having a includes and personal headers .

Sorry for the extra trouble, I hope you understand, thank you once again.
