#include <iostream>

#include "waveheader.h"

void printStartMenu();
void printProcessorMenu();
void handleMenu1();
void printMetaData(const wav_header *header);

int main(){

    printStartMenu();
    
    int input = 0;

    char filename[64];

    std::cin >> input;

    switch(input){

        case 1:
            
            handleMenu1();
            break;

        case 0:
            exit;

    }

}

void printStartMenu(){

    std::cout << "Welcome\n\nPlease select an option:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[1] Apply a processor to a .wav file" << std::endl;
    std::cout << "[0] Exit the program" << std::endl;

}

void printProcessorMenu(){

    std::cout << "Processor Menu\n" << std::endl;
    std::cout << "Please select a processor:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[1] Echo\n[2] Gain\n[3] Normalization\n[0] Exit the program" <<std::endl;

}

void handleMenu1(){//Executes when user chooses option 1 from main menu

    char filename[128];
    char input;

    std::cout << "Please enter a .wav filename: " << std::endl;
    std::cin >> filename;

    //Wav wavReader

    //[function to check/open file, store its contents in memory, then close it]

    std::cout << "File successfully opened." << std::endl;
    
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