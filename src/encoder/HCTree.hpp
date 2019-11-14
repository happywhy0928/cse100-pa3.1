/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: the method description file for HCTree
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"
#define ASCII_VALUE 256
using namespace std;

/**
 * Huffman Tree class
 * which build the tree according to the algorithm
 * Citation: from the piazza post and sunday's info session and discussion
 * https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
 * this URL for optimize the header
 */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

    /**
     *  helper method to delete all the nodes recursively
     *  para: node the current node to delete its subtree
     */
    void deleteAll(HCNode* node);
    /**
     * Helper method to write the tree structure in the header
     * Para: node the current node to record
     *       out the outputstream(ostream) to record the structure
     * Citation: from the piazza post and sunday's info session
     *            https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
     * this URL for optimize the header
     */
    void helperForwrite(HCNode* node, BitOutputStream& out);
    /**
     * Helper method to read the header and build the node from the header
     * Para: in is the inputstream to read the header
     * Return the current node and build correspond according to the header
     * Citation: from the piazza post and sunday's info session
     *          https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
     * this URL for optimize the header
     */
    HCNode* helperForRead(BitInputStream& in);

  public:
    /* constructor of the HCTree which create the vector for future use to each
     * char in ASCII table
     */
    HCTree() {
        root = nullptr;
        leaves = vector<HCNode*>(ASCII_VALUE, (HCNode*)0);
    }

    /**
     * Destructor of the HCTree
     */
    ~HCTree();

    /**
     * use the huffman algorithm to build the tree
     * freqs is a vector of ints that freqs[i] is the frequency of occurence
     * of byte i correspond to ascii table
     * Para: freqs -  the frequency vector to build the tree
     */
    void build(const vector<unsigned int>& freqs);

    /**
     * write to the given BitOutputStream to code the specific symbol
     * Param: symbol- the current symbol to code
     *        out - the BitOutputStream to write
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /**
     * write to the given ostream to code the specific symbol
     * Param: symbol- the current symbol to code
     *        out - the ostream to write
     */
    void encode(byte symbol, ostream& out) const;

    /**
     * return the symbol coded in the sequence of bits from the istream
     * para: in-the istream to read
     * Return: return the corresponding byte
     */
    byte decode(BitInputStream& in) const;

    /**
     * decode the symbol coded in sequency of bits from istream
     * para: in-the istream to read
     * Return: return the corresponding byte
     */
    byte decode(istream& in) const;
    /**
     * write the header
     * para: out the outputstream(ostream) to record
     * Citation: from the piazza post and sunday's info session
     *           https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
     * this URL for optimize the header
     */
    void writeHeader(BitOutputStream& out);
    /**
     * Reader the header the build the entire tree from the header
     * Para: in is the inputstream(istream) to read the header
     * Citation: from the piazza post and sunday's info session
     *          https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
     * this URL for optimize the header
     */
    void readHeader(BitInputStream& in);
};

#endif  // HCTREE_HPP
