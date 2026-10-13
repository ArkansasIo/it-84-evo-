# TI-84 Evo-Inspired Calculator Clone (C++23)

An original modular graphing-calculator software project. No proprietary firmware, ROM dumps, or copied assets are included.

## Current source modules

- Numeric expression parser with precedence, named variables, `pi`/`e`, and common real-valued functions.
- Interactive terminal shell for expressions, variables, graph sampling, summary statistics, memory save/load, and restricted BASIC-like programs.
- Graph sampling with discontinuity gaps, plus a backend-independent framebuffer graph renderer.
- Matrix multiplication, determinant, transpose, inverse and reduced row-echelon form.
- Descriptive statistics, sample standard deviation and linear regression.
- Finite-difference derivative, composite Simpson integration and bracketed bisection root finding.
- Complex-number helper operations and normal/binomial probability functions.
- Keypad layout and input mapping, RGBA framebuffer, menu selection, calculator session/history model.
- CMake tests and GitHub Actions build/test workflow.

## Build — Windows (Visual Studio 2022)

Install the Desktop development with C++ workload and CMake support.

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\ti84evo.exe
```

## Build — Linux/macOS

Requires CMake 3.20+ and a C++23 compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/ti84evo
```

## Console commands

- `:help` — help
- `:let A = 12/3` — define variable
- `:vars` — list variables
- `:graph sin(x)` — sample a function
- `:stats 2,4,6,8` — descriptive statistics
- `:save memory.mem` / `:load memory.mem` — memory persistence
- `:run examples/demo.bas` — run limited BASIC-like source
- `:quit` — exit

## Project layout

```text
include/ti84/core/       expression parser, calculator facade, Result
include/ti84/graph/      graph sampling API
include/ti84/math/       matrices, numerical methods, complex and probability helpers
include/ti84/storage/    versioned memory persistence
include/ti84/program/    restricted BASIC-like runtime
include/ti84/ui/         keypad, framebuffer, menu, session, graph renderer
src/                     implementation modules and terminal frontend
tests/                   core, UI/math, renderer, probability/complex tests
examples/                sample BASIC-like program
docs/                    architecture, feature inventory, roadmap, development, UI design
.github/workflows/       build/test CI
```

## Limitations

This is not yet a complete graphical or cycle-accurate hardware emulator. The renderer can draw sampled curves to an in-memory framebuffer, but there is no finished desktop window, font/text renderer, clickable virtual calculator skin, full TI-BASIC dialect, complex-number expression parser, symbolic algebra, or device link protocol. Angle-mode conversion is declared but not wired into expression evaluation.

## Security and license

The BASIC-like runtime supports a limited set of statements and does not execute shell commands or native code. Original project code is MIT licensed. This independent project is not affiliated with or endorsed by Texas Instruments.
