# Stable Marriage Solver

A professional C++ application for generating and analyzing Stable Marriage Problem (SMP) matrices. This tool includes multiple search algorithms and analysis features to explore stable matchings.

## Features

- **Random Sample Calculation:** Generate random preference matrices and calculate their stable matchings.
- **Search Algorithms:** 
  - **Hill Climbing:** Optimize matrices to find high numbers of stable matchings.
  - **Best First Search:** Heuristic-based search for optimal matrices.
- **Specialized Matrices:** Support for Latin and Pseudo-Latin matrices.
- **Matrix Manipulation:** Automated tools for dropping elements or increasing matrix size ($n+1$).

## Prerequisites

To build and run this project, you need:
* A C++17 compatible compiler (e.g., MSVC on Windows, GCC, or Clang)
* [CMake](https://cmake.org/download/) (version 3.10 or higher)

## How to Build and Run

Run the automated build script for your platform:

- **Windows (Command Prompt):** Double-click `build_and_run.bat` or run `build_and_run.bat` in your terminal.
- **Windows (PowerShell):** Run `.\build_and_run.ps1` in your terminal.
- **Mac/Linux:** Run `chmod +x build_and_run.sh` once to grant permission, then `./build_and_run.sh`.

## Project Structure

This project follows an industry-standard C++ directory layout:
- `include/StableMarriage/`: Public header files (Interfaces).
- `src/`: Implementation files (.cpp).
- `CMakeLists.txt`: Cross-platform build configuration.
- `build/`: Automated output directory for compiled artifacts.

## License

This project is provided as-is for educational and research purposes.
