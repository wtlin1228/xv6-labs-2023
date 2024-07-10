# xv6-labs-2023

## Lab1: Utilities

-   [x] Boot xv6 (easy)
-   [x] sleep (easy) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/079fcd5a718fb2182828cf6d36335600e7ec5e48)
-   [x] pingpong (easy) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/87daa146e65a6c3b4eda0e6f14d6d1496d2fa543)
-   [x] primes (moderate)/(hard) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/13d003dfe9c6c0482caac6455d42bfdfdf90cebd)
-   [x] find (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/6b81837aee3ce9e9b6a30c275ad9a5865bc0d247)
-   [x] xargs (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/3d1defdc48c883d1a7a172c9ecd2ab5fce310b83)

## Lab2: System Calls

-   [x] using gdb (easy) - [link](https://github.com/wtlin1228/xv6-labs-2023/blob/syscall/answers-syscall.txt)
-   [x] system call tracing (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/a2e6bcd1d5bcc8abcfda32737275ab0954dbf589)
-   [x] sysinfo (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/e94e2441b7ec81b64d55faaef1d305649498c810)

## Lab3: Page Tables

-   [x] Speed up system calls (easy) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/3e4a79ecc90d9e4b8c46f49f1f78805849872c67)
-   [x] Print a page table (easy) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/419eea2543ea20eeddb4f5824724fa17a8f8bd22)
-   [x] Detect which pages have been accessed (hard) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/bd54d6ffe47fc11bde527e7228726796e59630fb) 

## Lab4: Traps

-   [x] RISC-V assembly (easy) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/c6d2ab1b6cbeb8af8f2944f5c6946619ba989d97)
-   [x] Backtrace (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/b53e2396d4edff7943ee9f75d33ec56890c6d197)
-   [x] Alarm (hard) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/085e5257ba88b0257c6c600b222306a370a7e7ab)

## Lab5: Copy-on-Write Fork for xv6

-   [x] Implement copy-on-write fork (hard) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/2ee393191bca07bc4b8e38845cd8dd319b40e2dd)

## Lab6: Multithreading

-   [x] Uthread: switching between threads (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/9a6b37309b8bac510614db6334d3604d191084fc)
-   [x] Using threads (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/0ecb5da4f806f0d05cd3e575f02958eb09f84442)
-   [x] Barrier (moderate) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/4dcde2a7a7c755c3c507c66b87312c971dab679c)

## Lab7: Networking

-   [x] Your Job (hard) - [link](https://github.com/wtlin1228/xv6-labs-2023/commit/80fc27f0361f88ad08ec3725f48dc01765088877)


# Note

## Trap

```
SH
  write()
  ecall ◄────────────────────────────┐  
    │                                │
    │                                │
────┼────────────────────────────────┼────── 
    │                                │
    ▼                                │
 uservec ------ trampoline ------ userret()
    │                                ▲
    ▼                                │     
 usertrap()                    usertrapret()
    │                                ▲
    ▼                                │
 syscall() ──────────────────────────┘
    │    
    ▼
 sys_write()
```

`ecall` does:

1. set mode from user to supervisor
2. save the `$pc` to `$sepc`
3. save trampoline page to `$pc` (through jumping to `$stvec`)

## Page Faults

Using page faults, we change the `va -> pa` mapping from static to dynamic(lazy).

Some optimztion features leveraging page faults:

- copy-on-write fork
- lazy allocation
- demand paging
- paging to disk
- automatically extending stacks
- memory-mapped files

## Thread

In xv6:

- each CPU has a scheduler thread
- each user process has a user thread and a kernel thread
- timer interrupts and sleep will yield the CPU


# GNU Debugger

https://sourceware.org/gdb/current/onlinedocs/gdb.html/

## QEMU

- `control + A then C`: open the qemu console
- `info mem`: print the complete page table

## Layout

- `tui enable`
- `layout asm`
- `layout reg`
- `layout src`
- `layout split`

## Breakpoint

- `b <target>`
- `b <target> if <condition>`
- `info breakpoints`
- `watch <target>`: break when target changes

## Register

- `info reg`

## Focus

- `focus asm`
- `focus reg`
- `focus src`
- `focus cmd`

## Stack Frame

- `info frame`
- `info args`
- `info locals`
- `backtrace`
- `frame <number>`: go to frame #number, then can use `info frame`

## Print

- `print *argv`: print the first argument
- `print *argv@2`: print the first two arguments
- `print *argv@argc`: print the whole argument array
- `print/<format> <target>`

format:

- x: Hexadecimal
- d: Decimal
- u: Unsigned decimal
- o: Octal
- t: Binary
- a: Address
- c: Character
- f: Floating point
- s: String
- i: Instruction (machine code)

## Memory Examination

- `x/<unit of memory><format> <target>`: `x/2c $a0` means to examine 2 bytes, interpreting each byte as a character

format:

- b (byte): 1 unit = 1 byte
- h (halfword): 1 unit = 2 bytes
- w (word): 1 unit = 4 bytes
- g (giant word): 1 unit = 8 bytes
- c (character): 1 unit = 1 byte
- s (string): Each unit is a null-terminated string
- i (instruction): 1 unit = size of an instruction (architecture-dependent)

# xv6

xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6). xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)). See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Silas Boyd-Wickizer, Anton Burtsev, carlclone, Ian
Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed, Asami Doi,
eyalz800, Nelson Elhage, Saar Ettinger, Alice Ferrazzi, Nathaniel
Filardo, flespark, Peter Froehlich, Yakir Goaron, Shivam Handa, Matt
Harvey, Bryan Henry, jaichenhengjie, Jim Huang, Matúš Jókay, John
Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95, Wolfgang Keller,
Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim Kolontsov, Austin
Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu, Yandong Mao, Matan
Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark Morrissey, mtasm, Joel
Nider, Hayato Ohhashi, OptimisticSide, Harry Porter, Greg Price, Jude
Rich, segfault, Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya
Shigemitsu, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Rafael Ubal,
Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez, Keiichi Watanabe,
Nicolas Wolovick, wxdao, Grant Wu, Jindong Zhang, Icenowy Zheng,
ZhUyU1997, and Zou Chang Wei.

The code in the files that constitute xv6 is
Copyright 2006-2022 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu). The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu. Once they are installed, and in your shell
search path, you can run "make qemu".
