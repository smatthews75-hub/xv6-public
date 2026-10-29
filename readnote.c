// readnote: baca /notes/tugas.txt 5 byte per read, seperti di slide.
// Jalankan writenote dulu supaya file-nya ada.
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define CHUNK 5

int
main(void)
{
  char buf[CHUNK];  // tidak ada ruang untuk '\0': read memang tidak menambahkannya
  int fd, n, i, k, offset;

  fd = open("/notes/tugas.txt", O_RDONLY);
  if(fd < 0){
    printf(2, "readnote: tidak bisa membuka /notes/tugas.txt (jalankan writenote dulu)\n");
    exit();
  }
  printf(1, "open -> fd %d\n", fd);

  // xv6 tidak punya lseek, jadi offset dihitung sendiri dari nilai kembali read.
  offset = 0;
  for(k = 1; ; k++){
    n = read(fd, buf, CHUNK);
    if(n < 0){
      printf(2, "readnote: read gagal\n");
      break;
    }
    if(n == 0){
      printf(1, "read #%d: n = 0, end of file\n", k);
      break;
    }
    // buf bukan string C, jadi cetak tepat n byte satu per satu.
    printf(1, "read #%d: n = %d, offset %d -> %d, buf = [", k, n, offset, offset + n);
    for(i = 0; i < n; i++)
      printf(1, "%c", buf[i]);
    printf(1, "]\n");
    offset += n;
  }

  close(fd);
  exit();
}
