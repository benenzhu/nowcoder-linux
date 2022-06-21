#include "malloc.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("ccat /proc/%d/maps\n", getpid());
  getchar();
  void *addr = malloc(1); // mmap
  printf("look at addr %x for 1 malloc \n", addr);
  void *addr2 = malloc(256 * 1024); // mmap
  printf("look at addr %x for 256k malloc\n", addr2);
  getchar();
  free(addr);
  free(addr2);
  printf("free & look at heap\n");
  getchar();
  return 0;
}
