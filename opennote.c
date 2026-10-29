// opennote: buka /notes/tugas.txt yang sudah ada, lalu tutup lagi.
// Siapkan file-nya dulu dengan writenote.
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
  int fd = open("/notes/tugas.txt", O_RDONLY);

  if(fd < 0){
    printf(2, "opennote: /notes/tugas.txt belum ada (jalankan writenote dulu)\n");
    exit();
  }
  printf(1, "opennote: fd = %d\n", fd);
  close(fd);
  exit();
}
