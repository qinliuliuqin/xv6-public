# Summary
Codebase: [xv6-public](https://github.com/mit-pdos/xv6-public) \
Experiments: [CSE 306 labs](https://www.cs.unc.edu/~porter/courses/cse306/s16/labs.html) \
All experiments were conducted based on the codebase above. \
May 5th, Qin Liu \

# How to test?
```
$ git clone git@github.com:qinliuliuqin/xv6-public.git
$ cd xv6-public
```

To test Lab 1 (system call): 
```
$ git checkout lab1
$ make; make qemu-nox 
$ wolfietest
```
To test Lab 2 (copy-on-write): 
```
$ git checkout lab2
$ make; make qemu-nox 
$ cowtest1; cowtest2; cowtest3
```

To test Lab 3 (lottery scheduling): 
```
$ git checkout lab3
$ make; make qemu-nox 
$ nicetest; randomtest; lotterytest1; lotterytest2; lotterytest3
```

To test Lab 4 (fast file system): 
```
$ git checkout lab4
$ make; make qemu-nox 
$ ffstest1; ffstest2; ffstest3
```
For more information about the test, please refer to the comment of the code.


# References
[xv6 book](https://pdos.csail.mit.edu/6.828/2020/xv6/book-riscv-rev1.pdf) \
[Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/) \
[xv6 Joon Lim](https://github.com/joonlim/xv6) \
[Exploring xv6](https://www.youtube.com/watch?v=ktkAlbcoz7o) \
[xv6 demo](https://www.youtube.com/watch?v=5E0T2H_lMZI)
