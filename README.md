# Quantum Circuit Simulator

## Requirements
C++17 Compatible Compiler
CMake 3.10 or higher

## Build Instructions
Run the following commands from the root directory:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running the Simulator
After building, run the following command from the build directory:
```bash
./simulator
```

When prompted for a circuit file name, ensure the file is located in the circuits directory
For example:
```
../circuits/bell_pair.txt
```

## Circuit Formatting
Circuits files are text files.

Each line is formatted as follows:
```
instruction target_qubit control_q1,control_q2,...
```

For example, here is '''bell_pair.txt\'''
```
H 0
CNOT 1 0
```

## Supported Gates
The following are a list of supported gates (note: CNOT and SWAP require exactly 1 control, TOFFOLI requires exactly 2 controls)
X, Y, Z, H, T, TDAG, S, SDAG, SWAP, CNOT, TOFFOLI
