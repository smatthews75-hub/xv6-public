set arch i386:x86-64
target remote localhost:26000

# simbol kernel
symbol-file kernel

# simbol user program (di-link -Ttext 0x1000, lihat Makefile)
add-symbol-file _getpidtest 0x1000

# --- breakpoint 1: instruksi pertama stub getpid di user space ---
break *getpid