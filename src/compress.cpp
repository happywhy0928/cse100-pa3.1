/**
 * TODO: file header
 *
 * Author:
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"
/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    ifstream inputFile;
    ofstream compressFile;
    vector<byte> content;
    vector<unsigned int> freqs(256, 0);
    int temp = 0;
    byte next;
    compressFile.open(outFileName);
    inputFile.open(inFileName);
    FileUtils check;
    bool emptyFile = check.isEmptyFile(inFileName);
    if (emptyFile == true) {
        inputFile.close();
        compressFile.close();
    } else {
        int numberOfSymbols = 0;
        inputFile.seekg(0, ios::beg);
        while (!inputFile.eof()) {
            next = inputFile.get();
            if (inputFile.eof()) {
                break;
            }
            if (freqs[next] == 0) {
                numberOfSymbols++;
            }
            content.push_back(next);
            //  cout << next << endl;
            //  cout << numberOfSymbols << endl;
            int tempCount = freqs[next];
            freqs[next] = tempCount + 1;
        }

        for (int index = 0; index < 256; index++) {
            temp = freqs[index];
            compressFile << temp << endl;
        }
        HCTree currTree;
        currTree.build(freqs);

        for (unsigned int index = 0; index < content.size(); index++) {
            next = content[index];
            //   cout << next << endl;
            currTree.encode(next, compressFile);
        }
        inputFile.close();
        compressFile.close();
    }
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {
    ifstream inputFile;
    ofstream compressFile;
    vector<byte> content;
    vector<unsigned int> freqs(256, 0);
    int temp = 0;
    int total = 0;
    byte next;
    compressFile.open(outFileName);
    inputFile.open(inFileName, ios::binary);
    FileUtils check;
    BitOutputStream encodeFile(compressFile);
    bool emptyFile = check.isEmptyFile(inFileName);
    if (emptyFile == true) {
        inputFile.close();
        compressFile.close();
    } else {
        int numberOfSymbols = 0;
        inputFile.seekg(0, ios::beg);
        while (!inputFile.eof()) {
            next = inputFile.get();
            if (inputFile.eof()) {
                break;
            }
            if (freqs[next] == 0) {
                numberOfSymbols++;
            }
            content.push_back(next);
            //  cout << next << endl;
            //  cout << numberOfSymbols << endl;
            int tempCount = freqs[next];
            freqs[next] = tempCount + 1;
            total++;
        }
        /*
        for (int index = 0; index < 256; index++) {
            temp = freqs[index];
            compressFile << temp << endl;
        }*/
        HCTree currTree;
        currTree.build(freqs);
        currTree.writeHeader(encodeFile);
        encodeFile.flush();
        compressFile << total << endl;
        for (unsigned int index = 0; index < content.size(); index++) {
            next = content[index];
            //   cout << next << endl;
            currTree.encode(next, encodeFile);
        }
        encodeFile.flush();
        inputFile.close();
        compressFile.close();
    }
}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");
    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        exit(0);
    }
    if (isAsciiOutput == true) {
        pseudoCompression(inFileName, outFileName);
    } else {
        trueCompression(inFileName, outFileName);
    }
    return 0;
}
/*
    string inputfile = "";
    string outputfile = "";
    for (int i = 1; i < argc; i++) {
        string curr = argv[i];
        if (inputfile == "") {
            FileUtils check;
            bool valid = check.isValidFile(curr);
            if (valid == true) {
                inputfile = curr;
            } else {
                return 1;
            }
        } else {
            outputfile = curr;
        }
    }
    if (inputfile == "" || outputfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        return 1;
    }

    pseudoCompression(inputfile, outputfile);
    return 0;
*/
//}