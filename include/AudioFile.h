#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <string>

class AudioFile {

public:
    virtual bool load(const std::string& filename) = 0;
    virtual void getInfo() const = 0;
    virtual ~AudioFile() = default;

};

#endif