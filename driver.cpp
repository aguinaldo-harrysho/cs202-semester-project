#include <iostream>
#include <fstream>
#include "wave_header.h"
#include "wav.cpp"

const int NUM_ARGS = 2;

/**
 * Main program entry point.
 * @param argc: number of arguments given
 * @param argv: value of arguments (array)
 * @return
 */
int main(int argc, char const *argv[]) { // Currently bypassing argument checks for the sake of testing
    // if (argc < NUM_ARGS){
    //     std::string a = argv[0];
    //     std::cout << "Missing filename argument.\n" << std::endl;
    //     std::cout << "Correct usage:\n" + a + " <filename>" << std::endl;
    //     return 0;
    // }
    // if (argc > NUM_ARGS){
    //     std::string a = argv[0];
    //     std::cout << "Too many arguments.\nPlease only specifcy one filename." << std::endl;
    //     std::cout << "Correct usage:\n" + a + " <filename>" << std::endl;
    //     return 0;
    // }
    std::string file = argv[1];
    // Pass file name to wav file reader
    readFile("yes-8-bit-mono.wav"); // Replace explicit filename with var "file"
}