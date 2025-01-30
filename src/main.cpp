#include "WAVFile.h"

int main() {

    WAVFile wav;
    if (wav.load("./test_data/one.wav")) {
        wav.getInfo();
    }

    return 0;
}