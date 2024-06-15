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