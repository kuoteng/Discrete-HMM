# Discrete-HMM
implement the discrete HMM and related Baum-Welch algorithm and Viterbi algorithm
NTU DSP HW1
## How to use
1. compile

```sh
$ make
```

2. execute
```sh
$ ./train 10 model_init.txt seq_model_01.txt ./results/model_01.txt
$ ./train 10 model_init.txt seq_model_02.txt ./results/model_02.txt
$ ./train 10 model_init.txt seq_model_03.txt ./results/model_03.txt
$ ./train 10 model_init.txt seq_model_04.txt ./results/model_04.txt
$ ./train 10 model_init.txt seq_model_05.txt ./results/model_05.txt
$ ./test ./results/modellist.txt testing_data1.txt result1.txt
```

## environment

- content of os-release

```sh
NAME="Arch Linux"
PRETTY_NAME="Arch Linux"
ID=arch
BUILD_ID=rolling
ANSI_COLOR="0;36"
HOME_URL="https://www.archlinux.org/"
DOCUMENTATION_URL="https://wiki.archlinux.org/"
SUPPORT_URL="https://bbs.archlinux.org/"
BUG_REPORT_URL="https://bugs.archlinux.org/"
```
- `gcc -v`

```sh
使用內建 specs。
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-pc-linux-gnu/8.2.1/lto-wrapper
目的：x86_64-pc-linux-gnu
配置為：/build/gcc/src/gcc/configure --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://bugs.archlinux.org/ --enable-languages=c,c++,ada,fortran,go,lto,objc,obj-c++ --enable-shared --enable-threads=posix --enable-libmpx --with-system-zlib --with-isl --enable-__cxa_atexit --disable-libunwind-exceptions --enable-clocale=gnu --disable-libstdcxx-pch --disable-libssp --enable-gnu-unique-object --enable-linker-build-id --enable-lto --enable-plugin --enable-install-libiberty --with-linker-hash-style=gnu --enable-gnu-indirect-function --enable-multilib --disable-werror --enable-checking=release --enable-default-pie --enable-default-ssp --enable-cet=auto
執行緒模型：posix
gcc version 8.2.1 20181127 (GCC)
```

- `uname -r`

```sh
4.20.7-arch1-1-ARCH
```
## Author
Kuo Teng, Ding
## LICENSE
MIT
