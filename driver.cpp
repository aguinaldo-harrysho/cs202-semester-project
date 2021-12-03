#include <iostream>
#include <fstream>
#include <string>
#include "wave_header.h"
#include "reader.h"
#include "wav.h"

void printStartMenu();
void printProcessorMenu();
void handleMenu1();
void printMetaData(const wav_header *header);

int main(){

    printStartMenu();
    
    int input = 0;

    char filename[64];

    //std::cin >> input;
    input = 1; // Disabled input for testing, re-enable when done developing
    std::cout << "1" << std::endl; // To visually simualte selecting "1". Delete when done
    std::cout << std::endl;

    switch(input){

        case 1:
            
            handleMenu1();
            break;

        case 0:
            exit;

    }

}

void printStartMenu(){

    std::cout << "Welcome\nPlease select an option:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[1] Open a .WAV file" << std::endl;
    std::cout << "[0] Exit the program" << std::endl;

}

void printProcessorMenu(){

    //std::cout << "Processor Menu\n" << std::endl;
    std::cout << "Please select a processor:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[1] Echo\n[2] Gain\n[3] Normalization\n[0] Exit the program" <<std::endl;

}

void handleMenu1(){//Executes when user chooses option 1 from main menu

    std::string filename;
    char input;

    std::cout << "Please enter a .wav filename: " << std::endl;
    //std::cin >> filename;
    filename = "yes-8-bit-mono.wav"; // Filename explicitly defined for testing, re-enable when done developing
    std::cout << filename << std::endl; // To visually simualte typing a filename. Delete when done

    std::cout << std::endl;
    
    // Check file validity
    if(Reader::read_file(filename)) std::cout << "File successfully opened." << std::endl;
    else
    {
        std::cout << "There was an error opening the file" << std::endl;
        exit(0); // Currently just exits the program, maybe change later to keep the rpogram running
    }
    
    if(Reader::read_header(filename)) std::cout << "WAV successfully file identified.\n" << std::endl;
    else
    {
        std::cout << "There was an error identifying the filetype." << std::endl;
        exit(0); // Currently just exits the program, maybe change later to keep the rpogram running
    }
    
    //[function to open file, store its contents in memory, then close it]
    Wav* audiofile = new Wav(filename);

    //printMetaData();

    printProcessorMenu();

    switch(input){

        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 0:
            exit;

    }


}

void printMetaData(const wav_header *header){

    std::cout << "File Metadata:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Wav Size: " << header->wav_size << std::endl;
    std::cout << "# Channels: " << header->num_channels << std::endl;
    std::cout << "Sample Rate: " << header->sample_rate << std::endl;
    std::cout << "Bit Depth: " << header->bit_depth << std::endl;

}