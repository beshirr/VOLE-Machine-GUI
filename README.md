# Vole Machine Simulator

## Table of Contents

- [About](#about)
- [Features](#features)
- [Screenshots](#screenshots)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Running the Simulator](#running-the-simulator)
  - [Interface Overview](#interface-overview)
- [How to Use](#how-to-use)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Contact](#contact)


---

## About

The **Vole Machine Simulator** is a graphical simulator built with Qt for simulating the operations of a simple CPU. It allows users to load instructions, view and edit memory, view register states, and perform operations like fetch, decode, and execute. This tool is designed for educational purposes to help understand basic CPU functioning and OOP principles.

## Features

- **Memory Management**: Visual representation of memory cells, supporting hex, binary, and integer views.
- **Register Management**: Display and management of registers with detailed formats.
- **Instruction Execution**: Load, decode, fetch, and execute instructions with step-by-step control.
- **Manual Instruction Fetching**: You don't have to fetch instructions from memory you can add it manually and decode and execute it. 
- **User Interface**: Intuitive Qt-based GUI with a dedicated `How to Use` window for user guidance.
- **Cross-Platform**: Runs on Windows, macOS, and Linux.

## Screenshots

![Screenshot 2024-11-06 145526](https://github.com/user-attachments/assets/7ee1a0df-5f39-4604-987f-8de691dd0adc)

## Getting Started

### Prerequisites

- **Qt**: This project requires Qt (version 5 or later).
- **C++ Compiler**: A compatible C++ compiler.
- **CMake** (optional): If using CMake as the build system.

### Installation

1. **Clone the Repository**
   ```bash
   git clone [https://github.com/your-username/vole-machine-simulator.git](https://github.com/beshirr/VOLE-Machine-Simulator.git)
   cd vole-machine-simulator
2. **Build the project**
- Ensure that CMake and Qt are installed
- Create a build directory
   ```bash
   mkdir build && cd build
- Run CMake
  ```bash
  cmake ..
- Compile the project
  ```bash
  make
3. **Run the Application**
   ```bash
   ./vole-machine-simulator
### Windows-Specific Instructions
For Windows, ensure you have the Qt development tools installed and build the project using Qt Creator. CMake configuration should detect the necessary libraries automatically.

## How to use
1. **Load Instruction File**: Use the Open Instruction File button to load a Vole machine code file in .txt format.
2. **Fetch and Decode**: Click Fetch to load the instruction into the Instruction Register, followed by Decode to parse it.
3. **Execute**: Use Execute to run the decoded instruction, updating memory and registers.
4. **Control Execution**: Run one cycle with Run One Cycle or execute continuously with Run Until Halt.
5. **Reset and Clear**: Reset the program counter or clear memory and registers as needed.

## Project Structure
```
vole-machine-simulator/
├── src/
│   ├── mainwindow.cpp       # Main GUI logic
│   ├── cpu.cpp              # Core CPU simulation
│   ├── memory.cpp           # Memory management
│   ├── alu.cpp              # Arithmetic and Logic Unit (ALU)
│   └── instruction.cpp      # Instruction management and decoding
├── include/
│   ├── mainwindow.h         # MainWindow header
│   ├── cpu.h                # CPU class header
│   ├── memory.h             # Memory class header
│   └── alu.h                # ALU class header
├── resources/
│   ├── icons/               # Program icons
│   └── help/                # Help documentation
└── README.md
```
## Contributing
To contribute, please fork the repository, make your changes, and submit a pull request. Make sure to follow the project's coding style and include relevant documentation.

## Contact
### Authors
- **Youssef Ahmed Beshir**: https://github.com/beshirr
- **Zeyad Mohamed Arafat**: https://github.com/ZeyadArafat
- **Moaz Mohamed Soliman**: https://github.com/moaaz-mohamedd

   
