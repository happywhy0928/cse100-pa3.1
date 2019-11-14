/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: the implementation file of HCTree
 */
#include "HCTree.hpp"
#include <queue>
#include <stack>
#define MAX_BIT 8
#define ASCII_VALUE 256
/**
 * Destructor of the HCTree
 */
HCTree::~HCTree() { deleteAll(root); }
/**
 * use the huffman algorithm to build the tree
 * freqs is a vector of ints that freqs[i] is the frequency of occurence
 * of byte i correspond to ascii table
 * Para: freqs -  the frequency vector to build the tree
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> sets;
    // create the vector first to access each char Node which freq > 0
    for (unsigned int i = 0; i < freqs.size(); i++) {
        if (freqs[i] > 0) {
            HCNode* temp = new HCNode(freqs[i], i, 0, 0, 0);
            leaves[i] = temp;
            sets.push(temp);
        }
    }
    HCNode* parent = nullptr;
    HCNode* right = nullptr;
    HCNode* left = nullptr;
    HCNode* temp = nullptr;

    // specify case when only have one kind of character
    if (sets.size() == 1) {
        left = sets.top();
        sets.pop();
        right = new HCNode(0, left->symbol, 0, 0, 0);
        parent = new HCNode((left->count), left->symbol, left, right, 0);
        left->p = parent;
        sets.push(parent);
    }
    // case when have more than one kind of character
    while (sets.size() > 1) {
        // get the two nodes with least freq
        left = sets.top();
        sets.pop();
        right = sets.top();
        sets.pop();
        // check if the count equal or not to check the priority to build tree
        if (left->count == right->count) {
            parent = new HCNode((left->count) + (right->count), left->symbol,
                                left, right, 0);
        } else {
            parent = new HCNode((left->count) + (right->count), right->symbol,
                                left, right, 0);
        }

        right->p = parent;
        left->p = parent;

        sets.push(parent);
    }
    // the node left is the root of the tree
    root = sets.top();
    root->p = nullptr;
}

/**
 * write to the given BitOutputStream to code the specific symbol
 * Param: symbol- the current symbol to code
 *        out - the BitOutputStream to write
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    HCNode* curr = leaves[symbol];
    stack<bool> result;
    // try to find the path to root and record
    while (curr != nullptr && curr->p != nullptr) {
        if (curr->p->c0 == curr) {
            result.push(0);
        } else {
            result.push(1);
        }
        curr = curr->p;
    }
    while (!result.empty()) {
        int temp = result.top();
        out.writeBit(temp);
        result.pop();
    }
}

/**
 * write to the given ostream to code the specific symbol
 * Param: symbol- the current symbol to code
 *        out - the ostream to write
 */
void HCTree::encode(byte symbol, ostream& out) const {
    HCNode* curr = leaves[symbol];
    stack<int> result;

    // find the path to the root and record
    while (curr != nullptr && curr->p != nullptr) {
        if (curr->p->c0 == curr) {
            result.push(0);
        } else {
            result.push(1);
        }
        curr = curr->p;
    }
    while (!result.empty()) {
        out << result.top();
        result.pop();
    }
}

/**
 * return the symbol coded in the sequence of bits from the istream
 * para: in-the istream to read
 * Return: return the corresponding byte
 */
byte HCTree::decode(BitInputStream& in) const {
    // start from root
    HCNode* curr = root;
    bool input;
    while (curr->c0 != nullptr && curr->c1 != nullptr) {
        input = in.readBit();
        if (input == 0) {
            curr = curr->c0;
        } else if (input == 1) {
            curr = curr->c1;
        }
    }
    return curr->symbol;
}

/**
 * decode the symbol coded in sequency of bits from istream
 * para: in-the istream to read
 * Return: return the corresponding byte
 */
byte HCTree::decode(istream& in) const {
    HCNode* curr = root;
    byte input;
    while (curr->c0 != nullptr && curr->c1 != nullptr) {
        input = in.get();
        if (input == '0') {
            curr = curr->c0;
        } else if (input == '1') {
            curr = curr->c1;
        } else {
            return -1;
        }
    }
    return curr->symbol;
}
/**
 *  helper method to delete all the nodes recursively
 *  para: node the current node to delete its subtree
 */
void HCTree::deleteAll(HCNode* node) {
    // recursive call
    if (node->c0) {
        deleteAll(node->c0);
    }
    if (node->c1) {
        deleteAll(node->c1);
    }
    delete node;
}
/**
 * write the header
 * para: out the outputstream(ostream) to record
 * Citation: from the piazza post and sunday's info session
 */
void HCTree::writeHeader(BitOutputStream& out) { helperForwrite(root, out); }
/**
 * Helper method to write the tree structure in the header
 * Para: node the current node to record
 *       out the outputstream(ostream) to record the structure
 * Citation: from the piazza post and sunday's info session
 */
void HCTree::helperForwrite(HCNode* node, BitOutputStream& out) {
    // write for the child node
    if (node->c0 == nullptr && node->c1 == nullptr) {
        out.writeBit(1);
        byte symbol = node->symbol;
        for (unsigned int i = 0; i < MAX_BIT; i++) {
            byte temp = symbol << i;
            out.writeBit(temp >> MAX_BIT - 1);
        }
    }
    // write 0 for other node
    else {
        out.writeBit(0);
        helperForwrite(node->c0, out);
        helperForwrite(node->c1, out);
    }
}
/**
 * Reader the header the build the entire tree from the header
 * Para: in is the inputstream(istream) to read the header
 * Citation: from the piazza post and sunday's info session
 */
void HCTree::readHeader(BitInputStream& in) { root = helperForRead(in); }
/**
 * Helper method to read the header and build the node from the header
 * Para: in is the inputstream to read the header
 * Return the current node and build correspond according to the header
 * Citation: from the piazza post and sunday's info session
 */
HCNode* HCTree::helperForRead(BitInputStream& in) {
    // create the parent node if read 0
    if (in.readBit() == 0) {
        HCNode* left = helperForRead(in);
        HCNode* right = helperForRead(in);
        HCNode* root = new HCNode(0, left->symbol);
        left->p = root;
        right->p = root;
        root->c0 = left;
        root->c1 = right;
        return root;
    }
    // create the child node if read 1
    else {
        byte temp = 0;
        for (unsigned int i = 0; i < MAX_BIT; i++) {
            byte temp1 = in.readBit() << (MAX_BIT - i - 1);
            temp = temp | temp1;
        }
        return new HCNode(0, temp);
    }
}