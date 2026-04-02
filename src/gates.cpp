#include <complex>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "circuit.h"
#include "constants.h"
#include "gates.h" 

const std::unordered_map<std::string, mapFunc>& getGateMap() {
    static const std::unordered_map<std::string, mapFunc> gateMap = []() {
        std::unordered_map<std::string, mapFunc> gate;

        // PAULI GATES
        gate["X"] = gate["CNOT"] = gate["XDAG"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair(b, a); 
        };
        gate["Y"] = gate["YDAG"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair(b * std::complex<double>(0, -1), a * std::complex<double>(0, 1)); 
        };
        gate["Z"] = gate["ZDAG"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair(a, -b); 
        };

        // CLIFFORD GATES
        gate["H"] = gate["HDAG"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair((a+b)/ROOT_TWO, (a-b)/ROOT_TWO); 
        };
        gate["T"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair(a, b * (1.0 / ROOT_TWO + std::complex<double>(0, 1) / ROOT_TWO)); 
        };
        gate["TDAG"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair(a, b * (1.0 / ROOT_TWO - std::complex<double>(0, 1) / ROOT_TWO)); 
        };
        gate["S"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair(a, b * std::complex<double>(0, 1)); 
        };
        gate["SDAG"] = [](std::complex<double> a, std::complex<double> b) { 
            return std::make_pair(a, b * std::complex<double>(0, -1));  
        };

        return gate;
    }();

    return gateMap;
}

const std::unordered_map<std::string, std::function<std::vector<Instruction>(Instruction)>> decompositions = {
    {"SWAP", [](const Instruction& instruction) {
        int q1 = instruction.getTarget();
        int q2 = instruction.getControls()[0];

        return std::vector<Instruction> {
            {"CNOT", q1, {q2}},
            {"CNOT", q2, {q1}},
            {"CNOT", q1, {q2}}
        };
    }},
    {"TOFFOLI", [](const Instruction& instruction) {
        int t = instruction.getTarget();
        std::vector<int> controls = instruction.getControls();
        int c1 = controls[0];
        int c2 = controls[1];

        return std::vector<Instruction> {
            {"H", t},
            {"CNOT", t, {c2}},
            {"TDAG", t},
            {"CNOT", t, {c1}},
            {"T", t},
            {"CNOT", t, {c2}},
            {"TDAG", t},
            {"CNOT", t, {c1}},
            {"T", t},
            {"T", c2},
            {"H", t},
            {"CNOT", c2, {c1}},
            {"TDAG", c2},
            {"T", c1},
            {"CNOT", c2, {c1}}
        };
    }}
};

const std::unordered_set<std::string> COMMANDS = {
    "X",
    "XDAG",
    "Y",
    "YDAG",
    "Z",
    "ZDAG",
    "H",
    "HDAG",
    "T",
    "TDAG",
    "S",
    "SDAG",
    "CNOT",
    "TOFFOLI",
    "SWAP"
};

const std::unordered_set<std::string> ONE_CONTROL = {
    "CNOT",
    "SWAP"
};

const std::unordered_set<std::string> TWO_CONTROL = {
    "TOFFOLI"
};