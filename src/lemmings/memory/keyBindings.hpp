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

    //Transforma el evento de tecla a un string
    std::string InEvenToCh(EngineIO::InputEvent tecla){
        switch (tecla)
        {
        case EngineIO::InputEvent::RIGHT: return "R-Arrow";
        case EngineIO::InputEvent::LEFT: return "L-Arrow";
        case EngineIO::InputEvent::UP: return "U-Arrow";
        case EngineIO::InputEvent::DOWN: return "D-Arrow";
        case EngineIO::InputEvent::BACKSPACE: return "BackSpace";
        case EngineIO::InputEvent::TAB: return "TAB";
        case EngineIO::InputEvent::ENTER: return "ENTER";
        case EngineIO::InputEvent::ESC: return "ESC";
        case EngineIO::InputEvent::SHIFT: return "SHIFT";
        case EngineIO::InputEvent::CTRL: return "CTRL";
        case EngineIO::InputEvent::ALT: return "ALT";
        case EngineIO::InputEvent::SPACE: return "SPACE";
        case EngineIO::InputEvent::_1: return "1";
        case EngineIO::InputEvent::_2: return "2";
        case EngineIO::InputEvent::_3: return "3";
        case EngineIO::InputEvent::_4: return "4";
        case EngineIO::InputEvent::_5: return "5";
        case EngineIO::InputEvent::_6: return "6";
        case EngineIO::InputEvent::_7: return "7";
        case EngineIO::InputEvent::_8: return "8";
        case EngineIO::InputEvent::_9: return "9";
        case EngineIO::InputEvent::_0: return "0";
        case EngineIO::InputEvent::DEL: return "DEL";
        case EngineIO::InputEvent::F1: return "F1";
        case EngineIO::InputEvent::F2: return "F2";
        case EngineIO::InputEvent::F3: return "F3";
        case EngineIO::InputEvent::F4: return "F4";
        case EngineIO::InputEvent::F5: return "F5";
        case EngineIO::InputEvent::F6: return "F6";
        case EngineIO::InputEvent::F7: return "F7";
        case EngineIO::InputEvent::F8: return "F8";
        case EngineIO::InputEvent::F9: return "F9";
        case EngineIO::InputEvent::F10: return "F10";
        case EngineIO::InputEvent::F11: return "F11";
        case EngineIO::InputEvent::F12: return "F12";
        case EngineIO::InputEvent::NUM_SLASH: return "N-SLASH";
        case EngineIO::InputEvent::NUM_ASTERISK: return "N-ASTERISK";
        case EngineIO::InputEvent::NUM_MINUS: return "N-MINUS";
        case EngineIO::InputEvent::NUM_PLUS: return "N-PLUS";
        case EngineIO::InputEvent::NUM_ENTER: return "N-ENTER";
        case EngineIO::InputEvent::NUM_1: return "NUM-1";
        case EngineIO::InputEvent::NUM_2: return "NUM-2";
        case EngineIO::InputEvent::NUM_3: return "NUM-3";
        case EngineIO::InputEvent::NUM_4: return "NUM-4";
        case EngineIO::InputEvent::NUM_5: return "NUM-5";
        case EngineIO::InputEvent::NUM_6: return "NUM-6";
        case EngineIO::InputEvent::NUM_7: return "NUM-7";
        case EngineIO::InputEvent::NUM_8: return "NUM-8";
        case EngineIO::InputEvent::NUM_9: return "NUM-9";
        case EngineIO::InputEvent::NUM_0: return "NUM-0";
        case EngineIO::InputEvent::NUM_POINT: return "NUM-POINT";
        default:
            std::string res = "unknow";
            if( ((int)tecla >= (int)'A' && (int)tecla <= (int)'Z') || ((int)tecla >= (int)'a' && (int)tecla <= (int)'z') )
            {
                res = "";
                res +=(char)tecla;
            } 
            return res;
        }
        /*
        NONE = 0,
        RIGHT = 1,
        LEFT = 2,
        UP = 3,
        DOWN = 4,
        BACKSPACE = 8,
        case EngineIO::InputEvent::TAB = 9,
        case EngineIO::InputEvent::ENTER = 13,
        MOUSE_HOVER = 16,
        MOUSE_LEFT = 17,
        MOUSE_MIDDLE = 18,
        MOUSE_RIGHT = 19,
        MOUSE_SCROLL_UP = 20,
        MOUSE_SCROLL_DOWN = 21,
        case EngineIO::InputEvent::ESC = 27,
        case EngineIO::InputEvent::SHIFT = 28,
        case EngineIO::InputEvent::CTRL = 29,
        case EngineIO::InputEvent::ALT = 30,
        case EngineIO::InputEvent::SPACE = 32,
        case EngineIO::InputEvent::_1 = 49,
        case EngineIO::InputEvent::_2 = 50,
        case EngineIO::InputEvent::_3 = 51,
        case EngineIO::InputEvent::_4 = 52,
        case EngineIO::InputEvent::_5 = 53,
        case EngineIO::InputEvent::_6 = 54,
        case EngineIO::InputEvent::_7 = 55,
        case EngineIO::InputEvent::_8 = 56,
        case EngineIO::InputEvent::_9 = 57,
        case EngineIO::InputEvent::_0 = 48,
        W = 119,
        A = 97,
        S = 115,
        D = 100,
        case EngineIO::InputEvent::DEL = 127,
        case EngineIO::InputEvent::F1 = 256,
        case EngineIO::InputEvent::F2 = 257,
        case EngineIO::InputEvent::F3 = 258,
        case EngineIO::InputEvent::F4 = 259,
        case EngineIO::InputEvent::F5 = 260,
        case EngineIO::InputEvent::F6 = 261,
        case EngineIO::InputEvent::F7 = 262,
        case EngineIO::InputEvent::F8 = 263,
        case EngineIO::InputEvent::F9 = 264,
        case EngineIO::InputEvent::F10 = 265,
        case EngineIO::InputEvent::F11 = 266,
        case EngineIO::InputEvent::F12 = 267,
        case EngineIO::InputEvent::NUM_SLASH = 268,
        case EngineIO::InputEvent::NUM_ASTERISK = 269,
        case EngineIO::InputEvent::NUM_MINUS = 270,
        case EngineIO::InputEvent::NUM_PLUS = 271,
        case EngineIO::InputEvent::NUM_ENTER = 272,
        case EngineIO::InputEvent::NUM_1 = 273,
        case EngineIO::InputEvent::NUM_2 = 274,
        case EngineIO::InputEvent::NUM_3 = 275,
        case EngineIO::InputEvent::NUM_4 = 276,
        case EngineIO::InputEvent::NUM_5 = 277,
        case EngineIO::InputEvent::NUM_6 = 278,
        case EngineIO::InputEvent::NUM_7 = 279,
        case EngineIO::InputEvent::NUM_8 = 280,
        case EngineIO::InputEvent::NUM_9 = 281,
        case EngineIO::InputEvent::NUM_0 = 282,
        case EngineIO::InputEvent::NUM_POINT = 283

        EngineIO::InputEvent::RIGHT
        */
    }
};

#endif // LEMMINGS_KEYBINDINGS