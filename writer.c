#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>


int open_fifo(char *device_name) {
  int fd;

  if ((fd = open(device_name, O_WRONLY)) < 0){
    fprintf(stderr, "error open. open (%s) = %d\n", device_name, errno);
    return -1;
  }

  return fd;
}


int main(int argc, char **argv) {
  int fd;
  char buf[10];
  int c = 0;

  fd = open_fifo("/home/ikeda/aaa");
  if (fd < 0)
    return 1;
  while (1) {
    sprintf(buf, "c=%d\n", c++);
    write(fd, buf, strlen(buf));
    sleep(1);
  }
  return 0;
}
