#include <complex>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "circuit.h"
#include "constants.h"
#include "gates.h"
#include "helpers.h"
#include "simulate.h"

int main() {
    // get circuit with ordered instructions
    Circuit circuit = createCircuit();
    if (circuit.getQubits() == 0) {
        return 1;
    }

    // get gate map for instruction execution
    const std::unordered_map<std::string, mapFunc>& gates = getGateMap();

    // simulate circuit
    std::vector<std::complex<double>> state = simulate(circuit, gates);

    displayOutputDistribution(state, circuit.getQubits());

    // collapse final state
    std::cout << "Collapsed State: " << indexToBinString(collapse(state), circuit.getQubits()) << std::endl;
}