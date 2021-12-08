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

int main(){
    
    char menuChoice = '1';

    while (menuChoice!='0') {

        printStartMenu();

        std::cin >> menuChoice;
        //input = 1; // Disabled input for testing, re-enable when done developing
        //std::cout << "1" << std::endl; // To visually simualte selecting "1". Delete when done
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
    std::cout << "[1] Echo\n[2] Gain\n[3] Normalization\n[0] Exit to start" <<std::endl;

}

void handleMenu1(){//Executes when user chooses option 1 from main menu

    std::string filename;
    char menuChoice = '1';

    std::cout << "Please enter a .wav filename: " << std::endl;
    //std::cin >> filename;
    filename = "yes-16-bit-mono.wav"; // Filename explicitly defined for testing, re-enable when done developing
    std::cout << filename << std::endl; // To visually simualte typing a filename. Delete when done

    std::cout << std::endl;
    
    // Check file validity
    if(Reader::read_file(filename)) std::cout << "File successfully opened." << std::endl;
    else
    {
        std::cout << "There was an error opening the file" << std::endl;
        exit(0); // Currently just exits the program, maybe change later to keep the rpogram running
    }

    wav_header audiofile_header = Reader::read_header(filename); //Read the header of the file
    if(Reader::check_header(audiofile_header))
    {
        std::cout << "WAV successfully file identified.\n" << std::endl;
    }
    else
    {
        std::cout << "There was an error identifying the filetype." << std::endl;
        exit(0); // Currently just exits the program, maybe change later to keep the rpogram running
    }
    // Assuming we make it here, we now have audiofile_header of type wav_header. It is the header data of the specified file.

    // Print header metadata
    printMetaData(audiofile_header);
    std::cout << std::endl;

    //[function to open file, store its contents in memory, then close it]
    wav_body audiofile_body = Wav::readBodyData(audiofile_header, filename);
    // At this point in the program you now have audiofile_body which contains a vector of ints represtning each byte of a single channel.
    // That vector is monoChannel_sounData. Access is using audiofile_body.monoChannel_sounData.at(i)
    // Presumbably you would pass a wav_body object to whatever calss your using for your effects. In the end there will be two vectors, the second one caled steroChannel_soundData;

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

void processAudio(int type, wav_body audiofile_body)
{   
    char filename[1024];
    std::cout << "Please specify a name for output audio file: ";
    std::cin >> filename;

    switch(type)
    {
        case 1:
            //Echo echo;
            //echo.process(data);
            std::cout << "Vector data: ";
            std::cout << audiofile_body.monoChannel_sounData.at(0) << std::endl;

            Wav::writeAudiofile(audiofile_body, filename);
            break;
        case 2:
            //Gain gain;
            //gain.process(data);
            break;
        case 3:
            //Normalizer normalizer;
            //normalizer.process(data);
            break;
    }
}

void printMetaData(wav_header header){

    std::cout << "File Metadata:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Wav Size: " << header.wav_size << std::endl;
    std::cout << "# Channels: " << header.num_channels << std::endl;
    std::cout << "Sample Rate: " << header.sample_rate << std::endl;
    std::cout << "Bit Depth: " << header.bit_depth << std::endl;

}
