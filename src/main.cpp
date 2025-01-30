#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

struct WavHeader {
    char riff[4];            
    uint32_t fileSize;       
    char wave[4];            
    char fmt[4];             
    uint32_t fmtSize;        
    uint16_t audioFormat;    
    uint16_t numChannels;    
    uint32_t sampleRate;     
    uint32_t byteRate;       
    uint16_t blockAlign;     
    uint16_t bitsPerSample;  
    char dataHeader[4];      
    uint32_t dataSize;       
};

int main(){

    // Opening file in binary mode
    std::ifstream file("./test_data/one.wav", std::ios::binary);

    if(!file){
        std::cerr << "Error! Could not open the file :(" << std::endl;
        return 1;
    }

    std::cout << "File opened!" << std::endl;

    WavHeader wavHeader;

   // Convert converts &wavHeader (a WavHeader*) into a char* (byte pointer)
   // Then reads the file to the size of the WavHeader bytes (44) 
    file.read(reinterpret_cast<char*>(&wavHeader), sizeof(WavHeader));

    // Validates that is is a WAV file
    // Specify the size as riff and wave are char
    if (std::string(wavHeader.riff, 4) != "RIFF" || std::string(wavHeader.wave, 4) != "WAVE") {
        std::cerr << "Error: Not a valid WAV file!" << std::endl;
        return 1;
    }

    std::cout << "WAV File Info:\n";
    std::cout << "Channels: " << wavHeader.numChannels << "\n";
    std::cout << "Sample Rate: " << wavHeader.sampleRate << " Hz\n";
    std::cout << "Bits Per Sample: " << wavHeader.bitsPerSample << "\n";
    std::cout << "Data Size: " << wavHeader.dataSize << " bytes\n";

    
    std::vector<int16_t> audioData(wavHeader.dataSize / 2); // 16-bit PCM -> 2 bytes per sample

    // Starts from byte 44 and reads the data to the calculated data size
    file.read(reinterpret_cast<char*>(audioData.data()), wavHeader.dataSize);

    // Print the first 20 samples
    std::cout << "First 20 samples:\n";
    for (int i = 0; i < 20; i++) {
        std::cout << audioData[i] << " ";
    }
    std::cout << std::endl;


    return 0;



}