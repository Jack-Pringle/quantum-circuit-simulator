#ifndef GATES_H
#define GATES_H

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "constants.h"
#include "circuit.h"

const std::unordered_map<std::string, mapFunc>& getGateMap();
extern const std::unordered_map<std::string, std::function<std::vector<Instruction>(Instruction)>> decompositions;
extern const std::unordered_set<std::string> COMMANDS;
extern const std::unordered_set<std::string> ONE_CONTROL;
extern const std::unordered_set<std::string> TWO_CONTROL;

#endif