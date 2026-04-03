#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "circuit.h"
#include "constants.h"
#include "helpers.h"
#include "gates.h"

Instruction::Instruction(const std::string& name, int target) {
    this->name = name;
    this->target = target;
}

Instruction::Instruction(const std::string& name, int target, const std::vector<int>& controls) {
    this->name = name;
    this->target = target;
    this->controls = controls;
}

std::string Instruction::getName() const {return name;}
int Instruction::getTarget() const {return target;}
std::vector<int> Instruction::getControls() const {return controls;}



Circuit::Circuit() {}
Circuit::Circuit(int qubits) {
    if(qubits <= MAX_QUBITS) {
        this->qubits = qubits;
    }
}

// add instructions, decomposing high level instructions
void Circuit::addInstruction (const Instruction& instruction) {
    auto decomp = decompositions.find(instruction.getName());

    if (decomp != decompositions.end()) {
        for (const Instruction& inst : decomp->second(instruction)) {
            // handles recursive decomposition
            addInstruction(inst);
        }
    }
    else {
        instructions.push_back(instruction);
    }
}

int Circuit::getQubits() const {return qubits;}
const Instruction& Circuit::getInstruction(int index) const {return instructions[index];}
int Circuit::getInstructionCount() const {return instructions.size();}



Circuit createCircuit() {
    std::string filename;
    std::cout << "Enter Circuit Filename: ";
    std::getline(std::cin, filename);

    filename = CIRCUIT_PATH + filename;

    std::ifstream f(filename);
    if (f.is_open()) {        
        int maxQubits = 0;
        std::vector<Instruction> instructions;

        // read file lines
        int lineNumber = 0;
        std::string line;
        while (std::getline(f, line)) {
            lineNumber += 1;

            // remove comments
            size_t hash = line.find('#');
            if (hash != std::string::npos) {
                line = line.substr(0, hash);
            }
            
            // read line words
            std::stringstream ss(line);
            std::vector<std::string> words;
            std::string word;
            while (ss >> word) {
                words.push_back(stringToUpper(word));
            }

            if (words.empty()) continue;

            // check arg count
            int args = words.size() - 1;
            if (args < 1) {
                std::cerr << "Insufficient arguments at line " << lineNumber << ".\n";
                return Circuit();
            }
            if (args > 2) {
                std::cerr << "Excess arguments at line " << lineNumber << ".\n";
                return Circuit();
            }

            // get target
            int target;
            try {
                target = std::stoi(words[1]);
                if (maxQubits < target + 1) maxQubits = target + 1;
            }
            catch(...) {
                std::cerr << "Argument 1 invalid at line " << lineNumber << ".\n";
                return Circuit();
            }
            
            // get controls
            std::vector<int> controls;
            if(args == 2) {
                try {
                    std::stringstream ss(words[2]);
                    std::string c;
                    while(std::getline(ss, c, ',')) {
                        int control = std::stoi(c);

                        if (target == control) {
                            std::cerr << "Control matches target at line " << lineNumber << ".\n";
                            return Circuit();
                        }

                        if (std::find(controls.begin(), controls.end(), control) != controls.end()) {
                            std::cerr << "Duplicate control at line " << lineNumber << ".\n";
                            return Circuit();
                        }

                        controls.push_back(control);
                        if (maxQubits < control + 1) maxQubits = control + 1;
                    }
                }
                catch(...) {
                    std::cerr << "Argument 2 invalid at line " << lineNumber << ".\n";
                    return Circuit();
                }
            }

            // process command
            std::string command = words[0];
            bool badArgs = false;

            if (COMMANDS.count(command)) {
                // check control count
                if(ONE_CONTROL.count(command)) {
                    if (args != 2 || controls.size() != 1) {
                        badArgs = true;
                    }
                }
                else if(TWO_CONTROL.count(command)) {
                    if (args != 2 || controls.size() != 2) {
                        badArgs = true;
                    }
                }
                // allow any gate to be single controlled (but not required)
                else {
                    if (args == 2) {
                        if (controls.size() != 1) {
                            badArgs = true;
                        }
                    }
                }

                if (badArgs) {
                    std::cerr << "Incompatible arguments at line " << lineNumber << ".\n";
                    return Circuit();
                }
                
                if (!controls.empty()) {
                    instructions.push_back(Instruction(command, target, controls));
                }
                else {
                    instructions.push_back(Instruction(command, target));
                }
            }
            else {
                std::cerr << "Command not recognized at line " << lineNumber << ".\n";
                return Circuit();
            } 
        }

        if (maxQubits > MAX_QUBITS) {
            std::cerr << "Qubit requirement exceeds allowed maximum.\n";
            return Circuit();
        }

        Circuit circuit = Circuit(maxQubits);

        for(int i = 0; i < instructions.size(); i++) {
            circuit.addInstruction(instructions[i]);
        }

        return circuit;
    }
    else {
        std::cerr << "File could not be opened.\n";
        return Circuit();
    }
}
