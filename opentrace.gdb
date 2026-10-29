set arch i386:x86-64
target remote localhost:26000

# simbol kernel
symbol-file kernel

# $p = proc yang sedang berjalan. proc adalah variabel __thread di %fs:(-8)
# (lihat vm.c), jadi GDB tidak bisa membaca "proc" langsung.
# hook-stop memperbarui $p setiap kali GDB berhenti.
define hook-stop
  set $p = *(struct proc **)($fs_base - 8)
end

# Semua breakpoint hanya berhenti untuk proses "opennote",
# supaya open() milik sh, init, atau writenote tidak ikut tertangkap.

# 1: sys_open, path dan omode sudah diambil dari register user
break sysfile.c:294 if (*(struct proc **)($fs_base - 8))->name[0] == 'o' && (*(struct proc **)($fs_base - 8))->name[1] == 'p'

# 2: namex, awal tiap putaran loop (skipelem baru saja memotong satu komponen)
break fs.c:608 if (*(struct proc **)($fs_base - 8))->name[0] == 'o' && (*(struct proc **)($fs_base - 8))->name[1] == 'p'

# 3: dirlookup, directory entry yang cocok ditemukan
break fs.c:515 if (*(struct proc **)($fs_base - 8))->name[0] == 'o' && (*(struct proc **)($fs_base - 8))->name[1] == 'p'

# 4: sys_open, inode target sudah dikunci (dan dibaca dari disk)
break sysfile.c:315 if (*(struct proc **)($fs_base - 8))->name[0] == 'o' && (*(struct proc **)($fs_base - 8))->name[1] == 'p'

# 5: sys_open, open-file object terisi, tepat sebelum return fd
break sysfile.c:330 if (*(struct proc **)($fs_base - 8))->name[0] == 'o' && (*(struct proc **)($fs_base - 8))->name[1] == 'p'

# 6 dan 7: sys_close, sebelum dan sesudah descriptor dilepas
break sysfile.c:99 if (*(struct proc **)($fs_base - 8))->name[0] == 'o' && (*(struct proc **)($fs_base - 8))->name[1] == 'p'
break sysfile.c:101 if (*(struct proc **)($fs_base - 8))->name[0] == 'o' && (*(struct proc **)($fs_base - 8))->name[1] == 'p'
