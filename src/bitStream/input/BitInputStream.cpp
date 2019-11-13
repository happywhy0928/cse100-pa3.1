/**
 * TODO: file header
 *
 * Author:
 */
#include "BitInputStream.hpp"
#include <iostream>
using namespace std;

/* TODO */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 8;
}

/* TODO */
unsigned int BitInputStream::readBit() {
    if (nbits == 0) {
        fill();
    }
    int check = 1 << (nbits - 1);
    check = buf & check;

    nbits--;
    if (check != 0) {
        return 1;
    } else {
        return 0;
    }
}