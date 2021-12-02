#include <iostream>

const int NUM_ARGS = 2;

/**
 * Main program entry point.
 * @param argc: number of arguments given
 * @param argv: value of arguments (array)
 * @return
 */
int main(int argc, char const *argv[]) {
    if (argc < NUM_ARGS){
        std::string a = argv[0];
        std::cout << "Missing filename argument.\n" << std::endl;
        std::cout << "Correct usage:\n" + a + " <filename>" << std::endl;
        return 0;
    }
    if (argc > NUM_ARGS){
        std::string a = argv[0];
        std::cout << "Too many arguments.\nPlease only specifcy one filename." << std::endl;
        std::cout << "Correct usage:\n" + a + " <filename>" << std::endl;
        return 0;
    }
    std::string file = argv[1];
    // pass file name to wav file reader
}