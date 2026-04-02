#include <bitset>
#include <cctype>
#include <iostream>
#include <string>

#include "constants.h"
#include "helpers.h" 

std::string indexToBinString(std::size_t index, int truncSize) {
    std::bitset<MAX_QUBITS> bin(index);
    std::string binString = bin.to_string();
    std::string truncBin = binString.substr(MAX_QUBITS - truncSize);
    return truncBin;
}

std::string stringToUpper(std::string str) {
    for (char& c : str) {
        c = std::toupper(c);
    }

    return str;
}

void displayOutputDistribution(const std::vector<std::complex<double>>& state, int qubits) {
    std::cout << "Output Distribution:\n";
    for(std::size_t i = 0; i < state.size(); i++) {
        double prob = std::norm(state[i]);
        if (prob > NOISE_THRESHOLD) {
            std::cout << indexToBinString(i, qubits) << ": " << prob << std::endl;
        }
    }
}