/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: program to encode the files
 */
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
 * add pseudo compression with ascii encoding and naive header
 *  we first go through the file and then count each char and then go to code
 * everything in outFileName
 */
void pseudoCompression(string inFileName, string outFileName) {
    ifstream inputFile;
    ofstream compressFile;
    vector<byte> content;
    vector<unsigned int> freqs(ASCII_VALUE, 0);
    int temp = 0;
    byte next;
    compressFile.open(outFileName);
    inputFile.open(inFileName);

    // check if the inFileName is empty or not
    FileUtils check;
    bool emptyFile = check.isEmptyFile(inFileName);
    if (emptyFile == true) {
        inputFile.close();
        compressFile.close();
    } else {
        int numberOfSymbols = 0;
        inputFile.seekg(0, ios::beg);
        // start to go through the char and count each char
        while (!inputFile.eof()) {
            next = inputFile.get();
            if (inputFile.eof()) {
                break;
            }
            if (freqs[next] == 0) {
                numberOfSymbols++;
            }
            content.push_back(next);
            int tempCount = freqs[next];
            freqs[next] = tempCount + 1;
        }
        // record the freq for each char in each correponding line
        for (int index = 0; index < 256; index++) {
            temp = freqs[index];
            compressFile << temp << endl;
        }
        // build the tree according to the freqs vector
        HCTree currTree;
        currTree.build(freqs);
        // start to encode and record in the compressFile
        for (unsigned int index = 0; index < content.size(); index++) {
            next = content[index];
            currTree.encode(next, compressFile);
        }
        inputFile.close();
        compressFile.close();
    }
}

/**
 *  True compression with bitwise i/o and small header (final)
 * the quoted part is for the original header part
 * the unquoted part is to optimize the header
 * we first go through the file and then count each char and then build the tree
 * then we use the helper method to record the tree structure
 * then we encode each symbol in the file
 */
void trueCompression(string inFileName, string outFileName) {
    ifstream inputFile;
    ofstream compressFile;
    vector<byte> content;
    vector<unsigned int> freqs(ASCII_VALUE, 0);
    int temp = 0;
    int total = 0;
    byte next;
    compressFile.open(outFileName);
    inputFile.open(inFileName, ios::binary);
    // check if the inFileName is empty or not
    FileUtils check;
    BitOutputStream encodeFile(compressFile);
    bool emptyFile = check.isEmptyFile(inFileName);
    if (emptyFile == true) {
        inputFile.close();
        compressFile.close();
    } else {
        int numberOfSymbols = 0;
        // start to go through the char and count each char
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
        // record the tree structure by the helper method
        currTree.writeHeader(encodeFile);
        encodeFile.flush();
        // record the total number of char to future decompress
        compressFile << total << endl;
        // start to encode each symbol
        for (unsigned int index = 0; index < content.size(); index++) {
            next = content[index];
            currTree.encode(next, encodeFile);
        }
        encodeFile.flush();
        inputFile.close();
        compressFile.close();
    }
}

/**  Main program that runs the compress
 * citation: using the code from the PA illustration directly
 */
int main(int argc, char* argv[]) {
    // define options object with program description and help message
    // from discussion  and pa illustration
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
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
        pseudoCompression(inFileName, outFileName);
    } else {
        trueCompression(inFileName, outFileName);
    }
    return 0;
}
/*
//checkpoint
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