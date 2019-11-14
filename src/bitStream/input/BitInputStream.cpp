/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: implementation for BitinputStream
 */
#include "BitInputStream.hpp"
#include <iostream>
using namespace std;
#define MAX_BIT 8

/**
 * Fills the one byte buffer from input stream
 */
void BitInputStream::fill() {
    buf = in.get();
    nbits = MAX_BIT;
}

/**
 * Reads the next bit from the bit buffer. Fills the buffer with next byte from
 * input stream if all the bits have already been read.
 * return: 0 if bit read is 0, and return 1 if bit read is 1.
 */
unsigned int BitInputStream::readBit() {
    // fills the buffer if all bits have been read
    if (nbits == 0) {
        fill();
    }
    // read the next bit
    int check = 1 << (nbits - 1);
    check = buf & check;
    // keep track when all the bits are read if nbits equal to 0
    nbits--;
    if (check != 0) {
        return 1;
    } else {
        return 0;
    }
}