#include "tree.h"

#include <cassert>

int main() {
  tree_t tree(2);
  tree.set(1, 42);
  tree.set(2,24);
  tree.set(3, 122);
  tree.set(4, 345);
  tree.set(5, 75);
  tree.set(6,86);
  tree.set(7,100);
  auto v = tree.get(3);
  auto x = tree.get(5);
  auto y = tree.get(6);
  assert(v == 122);
  assert(x == 75);
  assert(y == 86);
  tree.remove(4);
  tree.remove(5);
  tree.remove(6);

  return 0;
}
