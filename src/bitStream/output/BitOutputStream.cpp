/**
 * TODO: file header
 *
 * Author:
 */
#include "BitOutputStream.hpp"

/* TODO */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();

    buf = nbits = 0;
}

/* TODO */
void BitOutputStream::writeBit(int i) {
    if (nbits == 8) {
        flush();
    }
    int check = i << (8 - nbits - 1);
    buf = buf | check;
    nbits++;
}
