// opennote: buka /notes/tugas.txt yang sudah ada, lalu tutup lagi.
// Siapkan file-nya dulu dengan writenote.
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
  int fd1 = open("/notes/tugas.txt", O_RDONLY);

  if(fd1 < 0){
    printf(2, "#1 opennote: /notes/tugas.txt belum ada (jalankan writenote dulu)\n");
    exit();
  }
  printf(1, "#1 opennote: fd = %d\n", fd1);

  int fd2 = open("/notes/tugas.txt", O_RDONLY);

  if(fd2< 0){
    printf(2, "#2 opennote: /notes/tugas.txt belum ada (jalankan writenote dulu)\n");
    exit();
  }
  printf(1, "#2 opennote: fd = %d\n", fd2);

  close(fd1);
  close(fd2);
  exit();
}
