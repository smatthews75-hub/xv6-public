// writenote: tulis isi ke /notes/tugas.txt.
//   writenote          -> isi "HELLO WORLD" (11 byte, tanpa newline)
//   writenote <kata>   -> isi <kata>
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  char *text = "HELLO WORLD";
  int fd, n, len;

  if(argc > 1)
    text = argv[1];
  len = strlen(text);

  // fs.img dibuat ulang setiap UPROGS berubah, jadi /notes bisa hilang.
  // Kalau /notes sudah ada, mkdir cuma gagal dan tidak apa-apa.
  mkdir("/notes");

  // xv6 tidak punya O_TRUNC: hapus file lama supaya sisa isi lama
  // tidak tertinggal kalau isi baru lebih pendek.
  unlink("/notes/tugas.txt");

  fd = open("/notes/tugas.txt", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf(2, "writenote: tidak bisa membuat /notes/tugas.txt\n");
    exit();
  }

  n = write(fd, text, len);
  close(fd);

  if(n != len){
    printf(2, "writenote: write gagal\n");
    exit();
  }
  printf(1, "writenote: %d byte ditulis ke /notes/tugas.txt lewat fd %d\n", n, fd);
  exit();
}
