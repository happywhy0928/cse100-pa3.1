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
}
TEST_F(ComplexHCTreeFixture, TEST_ENCODE1) {
    ostringstream os;
    tree1.encode('Z', os);
    ASSERT_EQ(os.str(), "111");
}
TEST_F(ComplexHCTreeFixture, TEST_ENCODE2) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "0010");
}
TEST_F(ComplexHCTreeFixture, TEST_ENCODE3) {
    ostringstream os;
    tree1.encode('G', os);
    ASSERT_EQ(os.str(), "10");
}
TEST_F(ComplexHCTreeFixture, TEST_DECODE1) {
    istringstream is("10");
    ASSERT_EQ(tree1.decode(is), 'G');
}
TEST_F(ComplexHCTreeFixture, TEST_DECODE2) {
    istringstream is("0010");
    ASSERT_EQ(tree1.decode(is), 'A');
}
TEST_F(SingleHCTreeFixture, TEST_ENCODE4) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "0");
}
TEST_F(SingleHCTreeFixture, TEST_DECODE3) {
    istringstream is("0");
    ASSERT_EQ(tree1.decode(is), 'A');
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
TEST_F(DoubleHCTreeFixture, TEST_ENCODE4) {
    ostringstream os;
    tree1.encode('A', os);
    ASSERT_EQ(os.str(), "1");
}
TEST_F(DoubleHCTreeFixture, TEST_ENCODE5) {
    ostringstream os;
    tree1.encode('B', os);
    ASSERT_EQ(os.str(), "0");
}
TEST_F(DoubleHCTreeFixture, TEST_DECODE4) {
    istringstream is("1");
    ASSERT_EQ(tree1.decode(is), 'A');
}
TEST_F(DoubleHCTreeFixture, TEST_DECODE5) {
    istringstream is("0");
    ASSERT_EQ(tree1.decode(is), 'B');
}