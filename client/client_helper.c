#include "client_helper.h"

int test_flag(Player p, PlayerFlags f) {
  return (p.flags & (1 << f));
}
