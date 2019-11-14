/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: header file for BitOutputStream
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/**
 * use given ostream to write bit for compress
 */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /**
     * Contructor: initialize a BitOutputStream that used given ostream for
     * output
     */
    explicit BitOutputStream(ostream& os) : out(os), buf(0), nbits(0){};
    /**
     * Sends the buffer to the output stream, and then clear the buffer to allow
     * further use
     */
    void flush();

    /**
     * Writes the least significant bit of the given int to the bit buffer.
     * Flushes the buffer first if it is full first check if the buffer is full
     * or not (full then flush) Para: i - an integer either 1 or 0
     */
    void writeBit(int i);
};

#endif
