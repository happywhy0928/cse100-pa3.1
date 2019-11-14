/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: unit test for HCTree
 */
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        freqs['b'] = 3;
        tree.build(freqs);
    }
};

class ComplexHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    ComplexHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['A'] = 2;
        freqs['B'] = 3;
        freqs['G'] = 12;
        freqs['I'] = 4;
        freqs['R'] = 6;
        freqs['Z'] = 7;
        freqs['\n'] = 11;
        tree1.build(freqs);
    }
};
class SingleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    SingleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['A'] = 2;
        tree1.build(freqs);
    }
};
TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("1");
    ASSERT_EQ(tree.decode(is), 'b');
    BitInputStream check(is);
    byte result = tree.decode(check);
    tree.readHeader(check);
}
TEST_F(ComplexHCTreeFixture, TEST_ENCODE1) {
    ostringstream os;
    tree1.encode('Z', os);
    ASSERT_EQ(os.str(), "111");
    BitOutputStream check(os);
    tree1.encode('Z', check);
    tree1.writeHeader(check);
}
TEST_F(ComplexHCTreeFixture, TEST_ENCODE2) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "0010");
    BitOutputStream check(os);
    tree1.encode('A', check);
    tree1.writeHeader(check);
}
TEST_F(ComplexHCTreeFixture, TEST_ENCODE3) {
    ostringstream os;
    tree1.encode('G', os);
    ASSERT_EQ(os.str(), "10");
    BitOutputStream check(os);
    tree1.encode('G', check);
    tree1.writeHeader(check);
}
TEST_F(ComplexHCTreeFixture, TEST_DECODE1) {
    istringstream is("10");
    ASSERT_EQ(tree1.decode(is), 'G');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
TEST_F(ComplexHCTreeFixture, TEST_DECODE2) {
    istringstream is("0010");
    ASSERT_EQ(tree1.decode(is), 'A');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
    istringstream is1("001010");
    tree1.readHeader(check);
    result = tree1.decode(check);
    result = tree1.decode(check);
}
TEST_F(SingleHCTreeFixture, TEST_ENCODE4) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "0");
    tree1.encode('G', os);
    BitOutputStream check(os);
    tree1.encode('A', check);
    tree1.encode('G', check);
    tree1.writeHeader(check);
}
TEST_F(SingleHCTreeFixture, TEST_DECODE3) {
    istringstream is("0");
    ASSERT_EQ(tree1.decode(is), 'A');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
class Single1HCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    Single1HCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['A'] = 2;
        tree1.build(freqs);
    }
};
TEST_F(Single1HCTreeFixture, TEST_ENCODE4) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "0");
    BitOutputStream check(os);
    tree1.encode('A', check);
    tree1.writeHeader(check);
}
TEST_F(Single1HCTreeFixture, TEST_DECODE4) {
    istringstream is("0");
    ASSERT_EQ(tree1.decode(is), 'A');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
class DoubleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    DoubleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['A'] = 2;
        freqs['B'] = 2;
        tree1.build(freqs);
    }
};
TEST_F(DoubleHCTreeFixture, TEST_ENCODE5) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "1");
    BitOutputStream check(os);
    tree1.encode('A', check);
    tree1.writeHeader(check);
}
TEST_F(DoubleHCTreeFixture, TEST_DECODE5) {
    istringstream is("1");
    ASSERT_EQ(tree1.decode(is), 'A');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
TEST_F(DoubleHCTreeFixture, TEST_ENCODE6) {
    ostringstream os;
    tree1.encode('B', os);
    ASSERT_EQ(os.str(), "0");
    BitOutputStream check(os);
    tree1.encode('B', check);
    tree1.writeHeader(check);
}
TEST_F(DoubleHCTreeFixture, TEST_DECODE6) {
    istringstream is("0");
    ASSERT_EQ(tree1.decode(is), 'B');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}

class DoubleHCTreeFixture1 : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    DoubleHCTreeFixture1() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['A'] = 2;
        freqs['B'] = 3;
        tree1.build(freqs);
    }
};
TEST_F(DoubleHCTreeFixture1, TEST_ENCODE7) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "0");
    BitOutputStream check(os);
    tree1.encode('A', check);
    tree1.writeHeader(check);
}
TEST_F(DoubleHCTreeFixture1, TEST_DECODE7) {
    istringstream is("0");
    ASSERT_EQ(tree1.decode(is), 'A');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
TEST_F(DoubleHCTreeFixture1, TEST_ENCODE8) {
    ostringstream os;
    tree1.encode('B', os);
    ASSERT_EQ(os.str(), "1");
    BitOutputStream check(os);
    tree1.encode('B', check);
    tree1.writeHeader(check);
}
TEST_F(DoubleHCTreeFixture1, TEST_DECODE8) {
    istringstream is("1");
    ASSERT_EQ(tree1.decode(is), 'B');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
class Single2HCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    Single2HCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        tree1.build(freqs);
    }
};
TEST_F(Single2HCTreeFixture, TEST_ENCODE9) {
    ostringstream os;
    tree1.encode('a', os);
    ASSERT_EQ(os.str(), "0");
    BitOutputStream check(os);
    tree1.encode('a', check);
    tree1.writeHeader(check);
}
TEST_F(Single2HCTreeFixture, TEST_DECODE9) {
    istringstream is("0");
    ASSERT_EQ(tree1.decode(is), 'a');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
class Complex5HCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    Complex5HCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 3;
        freqs['b'] = 9;
        freqs['c'] = 2;
        freqs['d'] = 4;
        freqs['e'] = 32;
        tree1.build(freqs);
    }
};
TEST_F(Complex5HCTreeFixture, TEST_ENCODE10) {
    ostringstream os;
    tree1.encode('a', os);
    ASSERT_EQ(os.str(), "0111");
    BitOutputStream check(os);
    tree1.encode('a', check);
    tree1.writeHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_ENCODE11) {
    ostringstream os;
    tree1.encode('b', os);
    ASSERT_EQ(os.str(), "00");
    BitOutputStream check(os);
    tree1.encode('b', check);
    tree1.writeHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_ENCODE12) {
    ostringstream os;
    tree1.encode('c', os);
    ASSERT_EQ(os.str(), "0110");
    BitOutputStream check(os);
    tree1.encode('c', check);
    tree1.writeHeader(check);
    tree1.encode('z', os);
    ASSERT_NE(os.str(), "0110");
}
TEST_F(Complex5HCTreeFixture, TEST_ENCODE13) {
    ostringstream os;
    tree1.encode('d', os);
    ASSERT_EQ(os.str(), "010");
    BitOutputStream check(os);
    tree1.encode('d', check);
    tree1.writeHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_ENCODE14) {
    ostringstream os;
    tree1.encode('e', os);
    ASSERT_EQ(os.str(), "1");
    BitOutputStream check(os);
    tree1.encode('e', check);
    tree1.writeHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_DECODE10) {
    istringstream is("1");
    ASSERT_EQ(tree1.decode(is), 'e');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_DECODE11) {
    istringstream is("010");
    ASSERT_EQ(tree1.decode(is), 'd');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_DECODE12) {
    istringstream is("0110");
    ASSERT_EQ(tree1.decode(is), 'c');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_DECODE13) {
    istringstream is("00");
    ASSERT_EQ(tree1.decode(is), 'b');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_DECODE14) {
    istringstream is("0111");
    ASSERT_EQ(tree1.decode(is), 'a');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
    istringstream is1("0001111");
    tree1.readHeader(check);
    result = tree1.decode(check);
    result = tree1.decode(check);
    result = tree1.decode(check);
    result = tree1.decode(check);
}
class Complex6HCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    Complex6HCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['%'] = 1;
        freqs['$'] = 1;
        freqs['@'] = 2;
        freqs['.'] = 4;
        tree1.build(freqs);
    }
};
TEST_F(Complex6HCTreeFixture, TEST_ENCODE15) {
    ostringstream os;
    tree1.encode('.', os);
    ASSERT_EQ(os.str(), "1");
    BitOutputStream check(os);
    tree1.encode('.', check);
    tree1.writeHeader(check);
}
TEST_F(Complex6HCTreeFixture, TEST_ENCODE16) {
    ostringstream os;
    tree1.encode('@', os);
    ASSERT_EQ(os.str(), "00");
    BitOutputStream check(os);
    tree1.encode('.', check);
    tree1.writeHeader(check);
}
class Single5HCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree1;

  public:
    Single5HCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['¡'] = 2;
        tree1.build(freqs);
    }
};
TEST_F(Single1HCTreeFixture, TEST_ENCODE17) {
    ostringstream os;
    tree1.encode('¡', os);
    ASSERT_NE(os.str(), "0");
    BitOutputStream check(os);
    tree1.encode('¡', check);
    tree1.writeHeader(check);
}
TEST_F(Complex5HCTreeFixture, TEST_DECODE17) {
    istringstream is("0");
    ASSERT_NE(tree1.decode(is), '¡');
    BitInputStream check(is);
    byte result = tree1.decode(check);
    tree1.readHeader(check);
}