#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"


int main(int argc, char *argv[])
{
  int i, cnt;
  char *args[MAXARG];
  static char buf[1024];
  char *p, *prev;


//   if(argc <= 1){
//     fprintf(2, "usage: \n");
//     exit(1);
//   }

  for(i = 1; i < argc; i++){
    args[i - 1] = argv[i];
  }

  while(1){
    gets(buf, sizeof(buf));
    if(buf[0] == 0) // EOF
      break;
    *strchr(buf, '\n') = '\0';
    prev = buf;
    cnt = argc - 1;
    while((p = strchr(prev, ' ')) != 0){
      *p = '\0';
      args[cnt++] = prev;
      prev = p + 1;
    }
    args[cnt++] = prev;
    args[cnt] = '\0';


    if(fork() == 0) {
      exec(args[0], args);
    }
    else {
      wait();
    }
  }

  exit();
}