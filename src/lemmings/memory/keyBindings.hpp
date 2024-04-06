#ifndef LEMMINGS_KEYBINDINGS
#define LEMMINGS_KEYBINDINGS

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "engine/IO.hpp"

#define NUM_KEYBINDINGS 18

class KeyBindings
{

    const EngineIO::InputEvent defaultKeyBindings[18] = {
        EngineIO::InputEvent::ENTER,
        EngineIO::charToInputEvent('1'),
        EngineIO::charToInputEvent('2'),
        EngineIO::charToInputEvent('3'),
        EngineIO::charToInputEvent('4'),
        EngineIO::charToInputEvent('5'),
        EngineIO::charToInputEvent('6'),
        EngineIO::charToInputEvent('7'),
        EngineIO::charToInputEvent('8'),
        EngineIO::charToInputEvent('9'),
        EngineIO::InputEvent::UP,
        EngineIO::InputEvent::DOWN,
        EngineIO::charToInputEvent('Q'),
        EngineIO::charToInputEvent('A'),
        EngineIO::charToInputEvent('W'),
        EngineIO::charToInputEvent('S'),
        EngineIO::InputEvent::LEFT,
        EngineIO::InputEvent::RIGHT
    };

public:

    void generateKeyBindingsFile() {
        // Create a file and write the keybindings to it.
        std::ofstream keyBindingsFile = std::ofstream("keyBindings.conf");
        for (int i = 0; i < NUM_KEYBINDINGS; i++) {
            keyBindingsFile << defaultKeyBindings[i] << std::endl;
        }
        keyBindingsFile.close();
    }

    void setKeyBindings(EngineIO::InputEvent keyBindings[]) {
        // Write the keybindings to the file.
        std::ofstream keyBindingsFile = std::ofstream("keyBindings.conf");
        for (int i = 0; i < NUM_KEYBINDINGS; i++) {
            keyBindingsFile << keyBindings[i] << std::endl;
        }
        keyBindingsFile.close();
    }

    void readKeyBindingsFile(EngineIO::InputEvent keyBindings[]) {
        // Se intenta leer el archivo.
        std::ifstream keyBindingsFile = std::ifstream("keyBindings.conf");
        // Si no existe, se crea.
        if (!keyBindingsFile.good()) {
            std::cout << "El fichero no existe, creando.\n";
            generateKeyBindingsFile();
            keyBindingsFile = std::ifstream("keyBindings.conf");
        }
        std::string line;
        int i = 0;
        while (std::getline(keyBindingsFile, line) && i < NUM_KEYBINDINGS) {
            std::cout << "Boton " << i << ": " << line << std::endl;
            keyBindings[i++] = static_cast<EngineIO::InputEvent>(std::stoi(line));
        }
        keyBindingsFile.close();
        std::cout << "Leidos " << i << " botones.\n";
        if (i < NUM_KEYBINDINGS) {
            std::cout << "Faltan botones en el archivo de configuración, creando uno nuevo.\n";
            generateKeyBindingsFile();
            readKeyBindingsFile(keyBindings);
        }
    }

};

#endif // LEMMINGS_KEYBINDINGS