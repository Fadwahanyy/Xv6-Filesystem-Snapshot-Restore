#include "kernel/types.h"
#include "user/user.h"

int main() {
  printf("About to call restore syscall...\n");
  snapshot_restore();
  printf("Restore syscall finished.\n");
  exit(0);
}

