/**
 * TODO: file header
 *
 * Author:
 */
#include "HCTree.hpp"
#include <queue>
#include <stack>

/* TODO */
HCTree::~HCTree() { deleteAll(root); }
/* TODO */
void HCTree::build(const vector<unsigned int>& freqs) {
    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> sets;

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

    if (sets.size() == 1) {
        left = sets.top();
        sets.pop();
        right = new HCNode(0, left->symbol, 0, 0, 0);
        parent = new HCNode((left->count), left->symbol, left, right, 0);
        left->p = parent;
        sets.push(parent);
    }
    while (sets.size() > 1) {
        left = sets.top();
        sets.pop();

        right = sets.top();
        sets.pop();
        if (left->count == right->count) {
            if (left->symbol > right->symbol) {
                parent = new HCNode((left->count) + (right->count),
                                    left->symbol, left, right, 0);
            } else {
                parent = new HCNode((left->count) + (right->count),
                                    right->symbol, left, right, 0);
            }
        } else {
            parent = new HCNode((left->count) + (right->count), right->symbol,
                                left, right, 0);
        }

        right->p = parent;
        left->p = parent;

        sets.push(parent);
    }
    root = sets.top();
    root->p = nullptr;
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    HCNode* curr = leaves[symbol];
    stack<bool> result;
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

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {
    HCNode* curr = leaves[symbol];
    stack<int> result;

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

/* TODO */
byte HCTree::decode(BitInputStream& in) const {
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

/* TODO */
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

void HCTree::deleteAll(HCNode* node) {
    if (node->c0) {
        deleteAll(node->c0);
    }
    if (node->c1) {
        deleteAll(node->c1);
    }
    delete node;
}
void HCTree::writeHeader(BitOutputStream& out) { helperForwrite(root, out); }

void HCTree::helperForwrite(HCNode* node, BitOutputStream& out) {
    if (node->c0 == nullptr && node->c1 == nullptr) {
        byte symbol = node->symbol;
        out.writeBit(1);
        for (unsigned int i = 0; i < 8; i++) {
            byte temp = symbol << i;
            out.writeBit(temp >> 8 - 1);
        }
    } else {
        out.writeBit(0);
        helperForwrite(node->c0, out);
        helperForwrite(node->c1, out);
    }
}

void HCTree::readHeader(BitInputStream& in) { root = helperForRead(in); }

HCNode* HCTree::helperForRead(BitInputStream& in) {
    if (in.readBit() == 1) {
        byte temp = 0;
        for (unsigned int i = 0; i < 8; i++) {
            // byte temp1 = is.readBit() << (8 - i - 1);
            temp = temp | (in.readBit() << (8 - i - 1));
        }
        return new HCNode(0, temp);
    } else {
        HCNode* c0 = helperForRead(in);
        HCNode* c1 = helperForRead(in);
        HCNode* root = new HCNode(0, c0->symbol);
        root->c0 = c0;
        root->c1 = c1;
        c0->p = root;
        c1->p = root;
        return root;
    }
}