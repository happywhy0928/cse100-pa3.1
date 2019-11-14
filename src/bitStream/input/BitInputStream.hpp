/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: header file for BitinputStream
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/**
 * use given istream to read bit for uncompress
 */
class BitInputStream {
  private:
    char buf;     // one byte buffer of bits
    int nbits;    // number of bits have been writen to buf
    istream& in;  // reference to the input stream to use

  public:
    /**
     * Contructor: initialize a BitInputStream that used given istream for
     * output
     */
    explicit BitInputStream(istream& is) : in(is), buf(0), nbits(0){};

    /**
     * Fills the one byte buffer from input stream
     */
    void fill();

    /**
     * Reads the next bit from the bit buffer. Fills the buffer with next byte
     * from input stream if all the bits have already been read. return: 0 if
     * bit read is 0, and return 1 if bit read is 1.
     */
    unsigned int readBit();
};

#endif