/**
 * TODO: file header
 *
 * Author:
 */
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    ifstream compressFile;
    ofstream result;
    vector<unsigned int> freqs(256, 0);
    int freq = 0;
    byte read;
    compressFile.open(inFileName);

    int i = 0;
    int numElement = 0;

    while (compressFile >> freq) {
        if (freq != 0) {
            numElement++;
        }
        freqs[i] = freq;
        freq = 0;
        i++;
        if (i > 255) {
            break;
        }
    }
    // cout << "12345" << endl;
    if (numElement == 0) {
        result.open(outFileName);
        result.close();
        //   cout << "1234" << endl;
    } else {
        read = compressFile.get();
        HCTree temp;
        temp.build(freqs);
        result.open(outFileName);
        //   cout << "12" << endl;
        while (1) {
            read = temp.decode(compressFile);
            if (compressFile.eof()) {
                break;
            }
            //    cout<<read <<endl;
            result << read;
        }
        //   cout << "123" << endl;
    }
    result.close();
    compressFile.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {
    ifstream compressFile;
    ofstream result;
    vector<unsigned int> freqs(256, 0);
    int freq = 0;
    byte read;
    compressFile.open(inFileName);
    BitInputStream decodeFile(compressFile);
    result.open(outFileName);
    int i = 0;
    int numElement = 0;
    // int total = 0;
    /* for the origin version with optimize the header
    while (compressFile >> freq) {
        if (freq != 0) {
            numElement++;
        }
        freqs[i] = freq;
        total += freq;
        freq = 0;
        i++;
        if (i > 255) {
            break;
        }
    } */
    /*
    if (numElement == 0) {
        result.close();
    } else { */

    //    read = compressFile.get();
    HCTree temp;
    temp.readHeader(decodeFile);
    int total = 0;
    compressFile >> total;
    read = compressFile.get();
    decodeFile.fill();
    //   temp.build(freqs);

    for (int i = 0; i < total; i++) {
        read = temp.decode(decodeFile);
        result << read;
    }
    result.close();
    // }
    compressFile.close();
}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./uncompress",
                             "Uncompresses files using Huffman Encoding");
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
        pseudoDecompression(inFileName, outFileName);
    } else {
        trueDecompression(inFileName, outFileName);
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
    pseudoDecompression(inputfile, outputfile);
    return 0;
}
*/