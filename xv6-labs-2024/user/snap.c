#include "kernel/types.h"
#include "user/user.h"

int main() {
  snapshot_create();
  printf("Snapshot created!\n");
  exit(0);
}
