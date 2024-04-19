#ifndef LEMMING_VOLUME_ASPECT
#define LEMMING_VOLUME_ASPECT
#pragma once

#include <fstream>
#include <iostream>
#include <string>


class VolumeAndAspect
{
    uint8_t music, effect, aspect;
public:
    VolumeAndAspect() {
        readVolAspFile();
    }

    void readVolAspFile() {
        std::ifstream file("volumeAspect.conf");
        if (!file.is_open()) {
            std::cerr << "Error opening volume and aspect file. Creating it." << std::endl;
            setDefaultVolAsp();
            return;
        }

        std::string line;
        std::getline(file, line);
        music = std::stoi(line);
        std::getline(file, line);
        effect = std::stoi(line);
        std::getline(file, line);
        aspect = std::stoi(line);
        file.close();
    }

    void setDefaultVolAsp() {
        music = 100;
        effect = 100;
        aspect = 0;
        writeVolAspFile();
    }

    void writeVolAspFile() {
        std::ofstream file("volumeAspect.conf");
        file << (int)music << std::endl;
        file << (int)effect << std::endl;
        file << (int)aspect << std::endl;
        file.close();
    }

    uint8_t getMusicVol() { return music; }
    void setMusicVol(uint8_t music) { this->music = music; }
    uint8_t getEffectsVol() { return effect; }
    void setEffectsVol(uint8_t effect) { this->effect = effect; }
    uint8_t getAspect() { return aspect; }
    void setAspect(uint8_t aspect) { this->aspect = aspect; }

};

#endif // LEMMING_VOLUME_ASPECT