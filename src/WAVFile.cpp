#include "WAVFile.h"

bool WAVFile::load(const std::string& filename) {

    std::ifstream file(filename, std::ios::binary);
   
   if(!file){

        std::cerr << "Error! Could not open the file :(" << std::endl;
        return false;
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
    
    std::vector<int16_t> audioData(wavHeader.dataSize / 2); // 16-bit PCM -> 2 bytes per sample

    // Starts from byte 44 and reads the data to the calculated data size
    file.read(reinterpret_cast<char*>(audioData.data()), wavHeader.dataSize);

    return true;
}

void WAVFile::getInfo() const {
    std::cout << "WAV File Info:\n";
    std::cout << "Channels: " << header.numChannels << "\n";
    std::cout << "Sample Rate: " << header.sampleRate << " Hz\n";
    std::cout << "Bits Per Sample: " << header.bitsPerSample << "\n";
    std::cout << "Data Size: " << header.dataSize << " bytes\n";
}
