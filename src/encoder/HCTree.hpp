/**
 * TODO: file header
 *
 * Author:
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** TODO: class header */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

    void deleteAll(HCNode* node);
    void helperForwrite(HCNode* node, BitOutputStream& out);

    HCNode* helperForRead(BitInputStream& in);

  public:
    /* TODO: add function header and implement */
    HCTree() {
        root = nullptr;
        leaves = vector<HCNode*>(256, (HCNode*)0);
    }

    /* TODO: add function header */
    ~HCTree();

    /* TODO: add function header */
    void build(const vector<unsigned int>& freqs);

    /* TODO: add function header */
    void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header */
    void encode(byte symbol, ostream& out) const;

    /* TODO: add function header */
    byte decode(BitInputStream& in) const;

    /* TODO: add function header */
    byte decode(istream& in) const;
    void writeHeader(BitOutputStream& out);

    void readHeader(BitInputStream& in);
};

#endif  // HCTREE_HPP
