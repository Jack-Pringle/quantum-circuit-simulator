# Quantum Circuit Simulator

## Requirements
C++17 Compatible Compiler

CMake 3.10 or higher

## Build Instructions
Run the following commands in the root directory:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running the Simulator
After building, run with the following command in the build directory:
```bash
./simulator
```

When prompted for a circuit file name, ensure the file is located in the circuits directory

**Example:**

To use circuit
```
../circuits/bell_pair.txt
```

use this file name
```
bell_pair.txt
```

## Circuit Formatting
Circuits files are text files.

Each line is formatted as follows:
```
instruction target_qubit control_q1,control_q2,...
```

For example, here is **bell_pair.txt**
```
H 0
CNOT 1 0
```

Note: This simulator uses Little-Endian formatting. This means Qubit 0 is the least significant bit and is represented by the right-most output qubit.

## Supported Gates
The following are a list of supported gates 
```
X, Y, Z, H, T, TDAG, S, SDAG, SWAP, CNOT, TOFFOLI
```
Note: **CNOT** and **SWAP** require exactly 1 control, **TOFFOLI** requires exactly 2 controls. All other gates permit 1 control in the current implementation.
