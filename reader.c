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
  int ret;

  signal(SIGPIPE, SIG_IGN);

  ret = mkfifo(device_name,S_IRWXU|S_IRWXG|S_IRWXO);
  if (ret<0 && errno!=EEXIST) {
    fprintf(stderr, "error mkinfo = %d\n", errno);
    return -1;
  }

  if ((fd = open(device_name, O_RDONLY)) < 0){
    fprintf(stderr, "error open. open (%s) = %d\n", device_name, errno);
    return -1;
  }

  return fd;
}


int gfd;
char *gdevice_name;
void close_fifo()
{
  close(gfd);
  unlink(gdevice_name);
}


static void handler(int sig)
{
  close_fifo();
  exit(0);
}

int main(int argc, char **argv) {
  char buf[10];
  int count;

  gdevice_name = "/home/ikeda/aaa";
  gfd = open_fifo(gdevice_name);
  if (gfd < 0)
    return 1;

  signal(SIGINT, handler);

  while (1) {
    count=read(gfd, buf, sizeof(buf));
    if (count < 0)
      break;
    write(STDOUT_FILENO, buf, count);
  }

  close_fifo();

  return 0;
}
