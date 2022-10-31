#include <iostream>
#include "BigInt.h"

int main() {
    BigInt object1("-999999999999999999");
    BigInt object2("-999999999");
    object1 -= object2;
    std::cout << object1;
    return 0;
}