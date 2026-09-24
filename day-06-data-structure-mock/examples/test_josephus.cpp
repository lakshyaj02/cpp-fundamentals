#include "josephus_elim.hpp"
#include <cassert>

int main() {
    assert(josephus_elimination(1, 1) == 1);
    assert(josephus_elimination(7, 3) == 4);
    assert(josephus_elimination(5, 1) == 5);
    assert(josephus_elimination(5, 2) == 3);
    assert(josephus_elimination(0, 3) == -1);
    assert(josephus_elimination(5, 0) == -1);
}