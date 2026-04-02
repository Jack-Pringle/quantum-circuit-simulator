#ifndef SIMULATE_H
#define SIMULATE_H

#include <complex>
#include <string>
#include <unordered_map>
#include <vector>

#include "circuit.h"
#include "constants.h"

std::vector<std::complex<double>> simulate(const Circuit&, const std::unordered_map<std::string, mapFunc>&);
std::size_t collapse(const std::vector<std::complex<double>>&);

#endif