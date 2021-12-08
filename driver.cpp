#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "wave_header.h"
#include "wave_body.h"
#include "reader.h"
#include "wav.h"
#include "echo.h"
#include "gain.h"
#include "normalizer.h"

void printStartMenu();
void printProcessorMenu();
void handleMenu1();
void printMetaData(wav_header header);
void processAudio(int type, wav_body audiofile_body);

/**
 * Main application entry point.
 * 
 * Displays the start menu and prompts the user for input.
 * 
 */
int main(){

    char menuChoice = '1';

    while (menuChoice!='0') {

        printStartMenu();

        std::cin >> menuChoice;
        std::cout << std::endl;

        switch(menuChoice){

            case '1':
                handleMenu1();
                break;
            case '0':
                exit(1);
                break;
            default:
                std::cout << "Please select an option from the menu\n" << std::endl;

        }
    }
}

//Prints the Start Menu
void printStartMenu(){

    std::cout << "Welcome\nPlease select an option:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[1] Open a .WAV file" << std::endl;
    std::cout << "[0] Exit the program" << std::endl;

}

//Prints the Processor Selection Menu
void printProcessorMenu(){

    //std::cout << "Processor Menu\n" << std::endl;
    std::cout << "Please select a processor:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[1] Echo\n[2] Gain\n[3] Normalization\n[0] Exit to start" <<std::endl;

}

//Executes when user chooses option 1 from main menu
void handleMenu1(){

    std::string filename;
    char menuChoice = '1';

    std::cout << "Please enter a .wav filename: " << std::endl;
    std::cin >> filename;
    std::cout << std::endl;

    if(filename == "1") filename = "yes-8-bit-mono.wav";
    else if(filename == "2") filename = "yes-16-bit-mono.wav";
    else if(filename == "3") filename = "stereo-16-bit.wav";
    std::cout << filename << std::endl;

    // Check file validity
    if(Reader::read_file(filename)) std::cout << "File successfully opened." << std::endl;
    else
    {
        std::cout << "There was an error opening the file" << std::endl;
        exit(0); // Currently just exits the program, maybe change later to keep the rpogram running
    }

    //Read the header of the file
    wav_header audiofile_header = Reader::read_header(filename);

    if(Reader::check_header(audiofile_header))
    {
        std::cout << "WAV successfully file identified.\n" << std::endl;
    }
    else
    {
        std::cout << "There was an error identifying the filetype." << std::endl;
        exit(0); // Currently just exits the program, maybe change later to keep the rpogram running
    }

    // Print header metadata
    printMetaData(audiofile_header);

    //Read information from the file and store it as a wav_body audiofile_body
    wav_body audiofile_body = Wav::readBodyData(audiofile_header, filename);

    //Handle Processor Menu
    while(menuChoice!='0'){

        printProcessorMenu();

        std::cin >> menuChoice;

        switch(menuChoice){
            
            case '1':
                processAudio(1, audiofile_body);
                menuChoice = '0';
                break;
            case '2':
                processAudio(2, audiofile_body);
                menuChoice = '0';
                break;
            case '3':
                processAudio(3, audiofile_body);
                menuChoice = '0';
                break;
            case '0':
                menuChoice = '0';
                break;
            default:
                std::cout << "Please select an option from the menu\n" << std::endl;

        }
    }
}

//Prompts user for output file name. Applies requested processor then saves a .wav file.
void processAudio(int type, wav_body audiofile_body)
{   
    char filename[1024];
    std::cout << "Please specify a name for output audio file: ";
    std::cin >> filename;

    switch(type)
    {
        case 1:
            Echo::process(audiofile_body.monoChannel_sounData);
            Wav::writeAudiofile(audiofile_body, filename);
            break;
        case 2:
            Gain::process(audiofile_body.monoChannel_sounData);
            Wav::writeAudiofile(audiofile_body, filename);
            break;
        case 3:
            Normalizer::process(audiofile_body.monoChannel_sounData);
            Wav::writeAudiofile(audiofile_body, filename);
            break;
    }
}

//Prints file metadata information
void printMetaData(wav_header header){

    std::cout << "File Metadata:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Wav Size: " << header.wav_size << std::endl;
    std::cout << "# Channels: " << header.num_channels << std::endl;
    std::cout << "Sample Rate: " << header.sample_rate << std::endl;
    std::cout << "Bit Depth: " << header.bit_depth << std::endl << std::endl;

}
