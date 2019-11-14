/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: implementation for BitOutputStream
 */
#include "BitOutputStream.hpp"
#define MAX_BIT 8
/**
 * Sends the buffer to the output stream, and then clear the buffer to allow
 * further use
 */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    // reset the buffer
    buf = nbits = 0;
}

/**
 * Writes the least significant bit of the given int to the bit buffer. Flushes
 * the buffer first if it is full
 * first check if the buffer is full or not (full
 * then flush) Para: i - an integer either 1 or 0
 */
void BitOutputStream::writeBit(int i) {
    // check the buffer is full or not
    if (nbits == MAX_BIT) {
        flush();
    }
    int check = i << (MAX_BIT - nbits - 1);
    // combine the buffer
    buf = buf | check;
    // increment the nbits to keep track when is full
    nbits++;
}
