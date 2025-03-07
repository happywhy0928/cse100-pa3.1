/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: unit test for BitInputStream
 */
#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "BitOutputStream.hpp"

using namespace std;
using namespace testing;
// simple test
TEST(BitOutputStreamTests, SIMPLE_TEST) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.flush();

    string bitsStr = "10000000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}