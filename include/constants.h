#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <complex>
#include <cstddef>
#include <functional>
#include <string>
#include <utility>

using mapFunc = std::function<std::pair<std::complex<double>, std::complex<double>>(std::complex<double>, std::complex<double>)>;

const std::size_t MAX_QUBITS = 20;

const double ROOT_TWO = 1.4142135623730951;

const double NOISE_THRESHOLD = 1e-5;

const std::string CIRCUIT_PATH = "../circuits/";

#endif