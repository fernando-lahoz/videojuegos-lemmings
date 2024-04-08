#ifndef LEMMINGS_KEYBINDINGS
#define LEMMINGS_KEYBINDINGS

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "engine/IO.hpp"

#define NUM_KEYBINDINGS 18

std::map<EngineIO::InputEvent, std::string> keyName;

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

    KeyBindings() {
        if (keyName.empty()) {
            keyName[EngineIO::InputEvent::RIGHT] = "RightArrow";
            keyName[EngineIO::InputEvent::LEFT] = "LeftArrow";
            keyName[EngineIO::InputEvent::UP] = "UpArrow";
            keyName[EngineIO::InputEvent::DOWN] = "DownArrow";
            keyName[EngineIO::InputEvent::BACKSPACE] = "BackSpace";
            keyName[EngineIO::InputEvent::TAB] = "Tab";
            keyName[EngineIO::InputEvent::ENTER] = "Enter";
            keyName[EngineIO::InputEvent::ESC] = "Esc";
            keyName[EngineIO::InputEvent::SHIFT] = "Shift";
            keyName[EngineIO::InputEvent::CTRL] = "Ctrl";
            keyName[EngineIO::InputEvent::ALT] = "Alt";
            keyName[EngineIO::InputEvent::SPACE] = "Space";
            for (int i=0; i<=9; i++)
                keyName[(EngineIO::InputEvent)(48+i)] = std::to_string(i);
            keyName[EngineIO::InputEvent::DEL] = "Del";
            for (int i=1; i<=12; i++)
                keyName[(EngineIO::InputEvent)(255+i)] = "F" + std::to_string(i);
            keyName[EngineIO::InputEvent::NUM_SLASH] = "NumSlash";
            keyName[EngineIO::InputEvent::NUM_ASTERISK] = "NumAsterisk";
            keyName[EngineIO::InputEvent::NUM_MINUS] = "NumMinus";
            keyName[EngineIO::InputEvent::NUM_PLUS] = "NumPlus";
            keyName[EngineIO::InputEvent::NUM_ENTER] = "NumEnter";
            for (int i=1; i<=9; i++)
                keyName[(EngineIO::InputEvent)(272+i)] = "Num" + std::to_string(i);
            keyName[EngineIO::InputEvent::NUM_0] = "Num0";
            keyName[EngineIO::InputEvent::NUM_POINT] = "NumPoint";
            keyName[(EngineIO::InputEvent)33] = "!";
            keyName[(EngineIO::InputEvent)34] = "Quote";
            keyName[(EngineIO::InputEvent)35] = "Hash";
            keyName[(EngineIO::InputEvent)36] = "Dollar";
            keyName[(EngineIO::InputEvent)37] = "%";
            keyName[(EngineIO::InputEvent)38] = "Amp";
            keyName[(EngineIO::InputEvent)39] = "'";
            keyName[(EngineIO::InputEvent)40] = "LeftParen";
            keyName[(EngineIO::InputEvent)41] = "RightParen";
            keyName[(EngineIO::InputEvent)42] = "Asterisk";
            keyName[(EngineIO::InputEvent)43] = "Plus";
            keyName[(EngineIO::InputEvent)44] = "Comma";
            keyName[(EngineIO::InputEvent)45] = "Dash";
            keyName[(EngineIO::InputEvent)46] = "Point";
            keyName[(EngineIO::InputEvent)47] = "Slash";
            keyName[(EngineIO::InputEvent)58] = "Colon";
            keyName[(EngineIO::InputEvent)59] = "Semicolon";
            keyName[(EngineIO::InputEvent)60] = "LessThan";
            keyName[(EngineIO::InputEvent)61] = "Equals";
            keyName[(EngineIO::InputEvent)62] = "MoreThan";
            keyName[(EngineIO::InputEvent)63] = "QuestMark";
            keyName[(EngineIO::InputEvent)64] = "At";
            keyName[(EngineIO::InputEvent)91] = "LeftSqBrck";
            keyName[(EngineIO::InputEvent)92] = "Baskslash";
            keyName[(EngineIO::InputEvent)93] = "RightSqBrck";
            keyName[(EngineIO::InputEvent)94] = "Hat";
            keyName[(EngineIO::InputEvent)95] = "LowBar";
            keyName[(EngineIO::InputEvent)96] = "Grave";
            keyName[(EngineIO::InputEvent)123] = "LeftKey";
            keyName[(EngineIO::InputEvent)124] = "VerticalBar";
            keyName[(EngineIO::InputEvent)125] = "RightKey";
            keyName[(EngineIO::InputEvent)126] = "Tilde";
            keyName[(EngineIO::InputEvent)128] = "Euro";
            keyName[(EngineIO::InputEvent)161] = "ExclOpen";
            keyName[(EngineIO::InputEvent)163] = "Pound";
            keyName[(EngineIO::InputEvent)164] = "Curren";
            keyName[(EngineIO::InputEvent)165] = "Yen";
            keyName[(EngineIO::InputEvent)168] = "Umlaut";
            keyName[(EngineIO::InputEvent)180] = "Acute";
            keyName[(EngineIO::InputEvent)172] = "Not";
            keyName[(EngineIO::InputEvent)176] = "Deg";
            keyName[(EngineIO::InputEvent)186] = "Ord";
            keyName[(EngineIO::InputEvent)191] = "QuestOpen";
            keyName[(EngineIO::InputEvent)216] = "OSlash";
            keyName[(EngineIO::InputEvent)248] = "OSlash";
            keyName[(EngineIO::InputEvent)199] = "CCedilla";
            keyName[(EngineIO::InputEvent)231] = "CCedilla";
            keyName[(EngineIO::InputEvent)209] = "NTilde";
            keyName[(EngineIO::InputEvent)241] = "NTilde";
        }
    }

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
        auto name = keyName.find(tecla);
        if (name != keyName.end())
                return name->second;
        if( (tecla >= 'A' && tecla <= 'Z') || (tecla >= 'a' && tecla <= 'z'))
                return std::string(1, (char)tecla);
        return "Unknown";
    }
};

#endif // LEMMINGS_KEYBINDINGS