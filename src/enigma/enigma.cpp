//
// Created by boole on 7/4/22.
//

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include "tools/tools.h"
#include "components/reflector.h"
#include "components/rotor.h"
#include "components/plugboard.h"


const std::unordered_map<std::string, rotor*> rotorChoices = {{"I", new rotor("EKMFLGDQVZNTOWYHXUSPAIBRCJ", "R")},
                                                             {"II", new rotor("AJDKSIRUXBLHWTMCQGZNPYFVOE", "F")},
                                                             {"III", new rotor("BDFHJLCPRTXVZNYEIWGAKMUSQO", "W")},
                                                             {"IV", new rotor("ESOVPZJAYQUIRHXLNFTGKDCMWB", "K")},
                                                             {"V", new rotor("VZBRGITYUPSDNHLXAWMJQOFECK","A")},
                                                             {"VI", new rotor("JPGVOUMFYQBENHZRDKASXLICTW", "AN")},
                                                             {"VII", new rotor("NZJHGRCXMYSWBOUFAIVLPEKQDT", "AN")},
                                                             {"VIII", new rotor("FKQHTLXOCBJSPDZRAMEWNIUYGV", "AN")}};

const std::unordered_map<std::string, reflector*> reflectorChoices = {{"A", new reflector("EJMZALYXVBWFCRQUONTSPIKHGD")},
                                                                     {"B", new reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT")},
                                                                     {"C", new reflector("FVPJIAOYEDRZXWGCTKUQSBNMHL")}};

class setting {

public:
    static std::string rotors() {
        std::vector<std::string> choices = tools::split("I II III IV V VI VII VIII", ' ');

        std::string out;
        for(int i=1; i<=3; i++) {
            int idx = tools::random_int(0, (uint8_t)choices.size()-1);
            out += choices[idx] + " ";
            choices.erase(choices.begin()+idx);
        }
        out.pop_back();

        return out;
    }

    static std::string reflector() {
        std::string choices[3] = {"A", "B", "C"};
        return choices[tools::random_int(0, (uint8_t)choices->length()-1)];
    }

    static std::string ringSettings() {
        std::string out;
        for(int i=1; i<=3; i++) {
            std::string setting = std::to_string(tools::random_int(1, 26));
            setting.insert(setting.begin(), 2 - setting.size(), '0');
            out += setting + " ";
        }
        out.pop_back();
        return out;
    }

    static std::string groundSettings() {
        std::string out;
        for(int i=0; i<3; i++) {
            int c = tools::random_int(65, 90);
            char setting = (char)c;
            out += setting; out += " ";
        }
        out.pop_back();
        return out;
    }

    static std::string plugs() {
        std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::vector<char> choices(alphabet.begin(), alphabet.end());

        std::vector<std::string> pairs(10);
        for(int i=1; i<=10; i++) {
            std::string pair;

            int firstPair = tools::random_int(0, (uint8_t)choices.size()-1);
            pair += choices[firstPair];
            choices.erase(choices.begin()+firstPair);

            int secondPair = tools::random_int(0, (uint8_t)choices.size()-1);
            pair += choices[secondPair];
            choices.erase(choices.begin()+secondPair);

            pairs.push_back(pair);
        }
        sort(pairs.begin(), pairs.end());

        return tools::join(pairs, " ");
    }

};

class enigma {

    std::vector<rotor>* rotors;
    reflector* eReflector;
    plugboard* ePlugboard;

public:
    enigma(const std::string& wiring, const std::string& pairs) {
        this->eReflector = reflectorChoices.at(wiring);
        this->rotors = new std::vector<rotor>;
        this->ePlugboard = new class plugboard();
        for(std::string pair : tools::split(pairs, ' '))
            this->ePlugboard->connect(pair[0], pair[1]);
    }

    void addRotor(const std::string& rotor) {
        this->rotors->push_back(*rotorChoices.at(rotor));
    }

    void setRings(std::vector<std::string> rings) {
        for(int i=0; i<rotors->size(); i++)
            this->rotors->at(i).ring = std::stoi(rings[i]);
    }

    void setTops(std::vector<std::string> ground) {
        for(int i=0; i<rotors->size(); i++)
            this->rotors->at(i).top = ground[i].at(0);
    }

    void step() {
        int idx = (uint8_t)rotors->size()-1;
        while(idx >= 0) {
            char top = rotors->at(idx).top;
            rotors->at(idx).top = (char)((top-65+1)%26+65);
            if(rotors->at(idx).isNotch(top)) idx--;
            else {
                if(idx > 0) {
                    if(rotors->at(idx-1).isNotch(rotor::offset(rotors->at(idx-1).top, 1))) idx--;
                    else break;
                }
                else break;
            }
        }
    }

    char performRotorCycle(char current) {
        int idx = (uint8_t)rotors->size()-1;

        // cycle through rotors normally
        while (idx >= 0) {
            rotor rotor = rotors->at(idx);
            current = rotor::offset(current, (int)(rotor.top-65));
            current = rotor.output(current, rotor.ring);
            current = rotor::offset(current, (int)(65-rotor.top));
            idx--;
        }

        // follow through reflector and back to rotors
        current = eReflector->output(current);

        // cycle through rotors in reverse
        idx = 0;
        while (idx < rotors->size()) {
            rotor rotor = rotors->at(idx);
            current = rotor::offset(current, (int)(rotor.top-65));
            current = rotor.output(current, rotor.ring);
            current = rotor::offset(current, (int)(65-rotor.top));
            idx++;
        }

        return current;
    }

    char cycle(char current) {
        if(current == 32) return current;

        step();

        current = ePlugboard->output(current);
        current = performRotorCycle(current);
        current = ePlugboard->output(current);

        return current;
    }

    std::string encrypt(const std::string& message) {
        std::string cypher;
        for(char current : message) cypher += cycle(current);
        return cypher;
    }

};

bool isValidInput(std::string in) {
    return std::all_of(in.begin(), in.end(), [](char c){ return (c>=65 && c<=90) || c==32; });
}

int main() {

    // freopen("output/components.txt", "w", stdout);

    std::cout << "\n" << "Enigma Machine Daily Key Settings" << std::endl;

    time_t base = std::time(nullptr);
    struct tm* tm = localtime(&base);

    std::string rotors = setting::rotors();
    std::string ring = setting::ringSettings();
    std::string plugs = setting::plugs();
    std::string reflector = setting::reflector();
    std::string ground = setting::groundSettings();

    std::cout << asctime(tm) << std::endl;
    std::cout << "Rotor Wheel Order:     " << rotors << std::endl;
    std::cout << "Ring Settings:         " << ring << std::endl;
    std::cout << "Plugboard Connections: " << plugs << std::endl;
    std::cout << "Reflector Wiring:      Reflector " << reflector << " (" << reflectorChoices.at(reflector)->getOutput() << ")" << std::endl;
    std::cout << "Ground Settings:       " << ground << std::endl;

    while(true) {
        std::cout << "\nEnter message to encrypt: ";
        std::string message;
        std::getline(std::cin, message);
        transform(message.begin(), message.end(), message.begin(), ::toupper);

        if(!isValidInput(message)) {
            std::cout << "Invalid Input! Try again.." << std::endl;
            continue;
        }

        enigma* machine = new enigma(reflector, plugs);
        for(const std::string& rotor : tools::split(rotors, ' ')) machine->addRotor(rotor);
        machine->setRings(tools::split(ring, ' '));
        machine->setTops(tools::split(ground, ' '));

        std::cout << "Encrypted Message: " << machine->encrypt(message) << std::endl;

        break;
    }

    return 0;
}