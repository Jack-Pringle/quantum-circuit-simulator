#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>

struct Instruction {
    private:
        std::string name;
        int target;
        std::vector<int> controls;

    public:
        Instruction(const std::string&, int);
        Instruction(const std::string&, int, const std::vector<int>&);

        std::string getName() const;
        int getTarget() const;
        std::vector<int> getControls() const;
};

class Circuit {
    private:
        std::vector<Instruction> instructions;
        int qubits = 0;
    public:
        Circuit();
        Circuit(int);

        void addInstruction (const Instruction&);

        int getQubits() const;
        const Instruction& getInstruction(int) const;
        int getInstructionCount() const;
};

Circuit createCircuit();

#endif