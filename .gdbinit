set height unlimited
set pagination off
set confirm off

#set trace-commands on
#set print inferior-events on

set sysroot /

directory ~/staging/glibc-2.31
directory ~/staging/glibc-2.31/elf
directory ~/staging/glibc-2.31/nptl
directory ~/staging/glibc-2.31/dlfcn
directory ~/staging/glibc-2.31/misc
directory ~/staging/glibc-2.31/csu
directory ~/staging/glibc-2.31/ctype
directory ~/staging/glibc-2.31/stdlib
directory ~/staging/glibc-2.31/sysdeps
directory ~/staging/gcc-10-10.5.0/src/libsanitizer/tsan

br main

set mem inaccessible-by-default off
set detach-on-fork off
#set detach-on-fork on
#set follow-fork-mode parent
set follow-fork-mode child
#set follow-exec-mode new
set follow-exec-mode same


#catch fork

#Links:
#  - https://sourceware.org/gdb/onlinedocs/gdb/Forks.html
#  - https://sourceware.org/gdb/onlinedocs/gdb/Inferiors-and-Programs.html
