#ifndef WAVFILE_H
#define WAVFILE_H

#include "AudioFile.h"   // Include base class
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

class WAVFile : public AudioFile {
private:
    WavHeader header;
    std::vector<int16_t> audioData;

public:
    bool load(const std::string& filename) override;
    void getInfo() const override;
};

#endif // WAVFILE_H
