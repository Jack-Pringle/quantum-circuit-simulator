#ifndef HELPERS_H
#define HELPERS_H

#include <string>

std::string indexToBinString(std::size_t, int);
std::string stringToUpper(std::string);
void displayOutputDistribution(const std::vector<std::complex<double>>&, int);

#endif