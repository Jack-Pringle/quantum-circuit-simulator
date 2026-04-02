#include <complex>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "simulate.h"
#include "circuit.h"
#include "constants.h"

std::vector<std::complex<double>> simulate(const Circuit& circuit, const std::unordered_map<std::string, mapFunc>& gates) {
    // get state size
    int qubits = circuit.getQubits();
    std::size_t stateSize = static_cast<std::size_t>(1) << qubits;
    
    // initialize state to |000...0> = [1,0,0,0,...,0]
    std::vector<std::complex<double>> state(stateSize, 0.0);
    state[0] = 1.0;

    // iterate through instructions, applying to state
    for(int inst = 0; inst < circuit.getInstructionCount(); inst++) {
        const Instruction& instruction = circuit.getInstruction(inst);

        const std::string name = instruction.getName();
        int target = instruction.getTarget();
        const std::vector<int>& controls = instruction.getControls();
        const mapFunc& gateFunction = gates.at(name);

        // qubit index pair selection (pair 0 and 1 in qubit place of index for each index)
        std::size_t blockSize =  static_cast<std::size_t>(1) << (target + 1);
        std::size_t blocks = static_cast<std::size_t>(1) << (qubits - target - 1);
        std::size_t difference = static_cast<std::size_t>(1) << target;

        for(std::size_t count = 0; count < blocks; count++) {
            for(std::size_t index = 0; index < difference; index++) {
                std::size_t first = count * blockSize + index;
                std::size_t second = first + difference;

                // dont apply change if a control exists but is 0
                // control is necessarily the same at first and second, so only first checked
                bool controlsPass = true;

                for (int control : controls) {
                    if (!((first >> control) & 1)) {
                        controlsPass = false;
                        break;
                    }
                }

                if (controlsPass) {
                    std::pair<std::complex<double>, std::complex<double>> output = gateFunction(state[first], state[second]);

                    state[first] = output.first;
                    state[second] = output.second;
                }
            }
        }
    }
    
    return state;
}

std::size_t collapse(const std::vector<std::complex<double>>& state) {
    // static to prevent seeding more than once
    static std::mt19937 generator(std::time(0)); 
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    double r = distribution(generator);
    double probability = 0.0;

    for(std::size_t index = 0; index < state.size(); index++) {
        probability += std::norm(state[index]);
        if (probability >= r) {return index;}
    }

    return state.size() - 1;
}