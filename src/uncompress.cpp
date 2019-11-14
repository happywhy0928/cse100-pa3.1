/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: program to decode the files
 */
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define ASCII_VALUE 256
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

/**
 * Pseudo decompression with ascii encoding and naive header (checkpoint)
 * first we get the freq in each line and then build the tree to decode the
 * corresponding symbol
 */
void pseudoDecompression(string inFileName, string outFileName) {
    ifstream compressFile;
    ofstream result;
    vector<unsigned int> freqs(ASCII_VALUE, 0);
    int freq = 0;
    byte read;
    compressFile.open(inFileName);

    int i = 0;
    int numElement = 0;
    // get the freq for each char in ascii table
    while (compressFile >> freq) {
        if (freq != 0) {
            numElement++;
        }
        freqs[i] = freq;
        freq = 0;
        i++;
        if (i > ASCII_VALUE - 1) {
            break;
        }
    }
    // the compressed file is empty
    if (numElement == 0) {
        result.open(outFileName);
        result.close();
    }
    // the compressed file is not empty
    else {
        read = compressFile.get();
        HCTree temp;
        temp.build(freqs);
        result.open(outFileName);
        while (1) {
            // start to decode
            read = temp.decode(compressFile);
            if (compressFile.eof()) {
                break;
            }
            // record each symbol
            result << read;
        }
    }
    result.close();
    compressFile.close();
}

/**
 * True decompression with bitwise i/o and small header (final)
 * first use helper method to read the header to build the tree and then to
 * decode the corresponding symbol the quoted part is for the naive part without
 * optimization the header the unquoted part is for the final part after
 * optimize the header
 */
void trueDecompression(string inFileName, string outFileName) {
    ifstream compressFile;
    ofstream result;
    vector<unsigned int> freqs(ASCII_VALUE, 0);
    int freq = 0;
    byte read;
    compressFile.open(inFileName);
    BitInputStream decodeFile(compressFile);
    result.open(outFileName);
    int i = 0;
    int numElement = 0;
    // check if the compressed file is empty or not
    FileUtils check;
    bool emptyFile = check.isEmptyFile(inFileName);
    if (emptyFile == true) {
        result.close();
    } else {
        HCTree temp;
        // build the tree by reading the header
        temp.readHeader(decodeFile);
        int total = 0;
        // get the total number of symbols and know when to stop reading
        compressFile >> total;
        read = compressFile.get();
        decodeFile.fill();
        // start to decode by the tree before
        for (int i = 0; i < total; i++) {
            read = temp.decode(decodeFile);
            result << read;
        }
        result.close();
    }
    compressFile.close();
    // for the naive part without optimize the header
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
}

/**  Main program that runs the uncompress
 * citation: using the code from the PA illustration directly
 */
int main(int argc, char* argv[]) {
    // define options object with program description and help message
    // from discussion  and pa illustration
    cxxopts::Options options("./uncompress",
                             "Uncompresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");
    // define variable in which to store the parsed options
    // from discussion  and pa illustration
    bool isAsciiOutput = false;
    string inFileName, outFileName;
    // define which options exist, in which variable they should be stored
    // and their corresponding help message
    // from discussion  and pa illustration
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");

    // define which options are require positional argument
    // from discussion  and pa illustration
    options.parse_positional({"input", "output"});
    // parse the command line options the user passed into the program
    // from discussion and pa illustration
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
//checkpoint part
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