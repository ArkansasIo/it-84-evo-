# TI-84 Evo-Inspired Calculator Clone (C++23)

Original, modular graphing-calculator software. No proprietary firmware, ROM dumps, or copied assets are included.

## Current modules

- Numeric expression parser, constants, variables, and common single-argument functions.
- Interactive terminal shell with expressions, variables, graph sampling, statistics, memory save/load and restricted BASIC-like programs.
- Graph sampling API with discontinuity gaps.
- Matrix multiply/determinant plus transpose, inverse, and reduced row-echelon form.
- Summary statistics, linear regression, finite-difference derivative, Simpson integration, and bisection root solver.
- UI foundations: key identity/layout, RGBA framebuffer, menu selection state, calculator screen/input/history session.
- Dependency-free unit tests and GitHub Actions CI.

## Build on Windows

Install Visual Studio 2022 with the Desktop development with C++ workload and CMake support.

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\ti84evo.exe
```

## Build on Linux/macOS

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

## Layout

```text
include/ti84/core/       expression parser, calculator facade, Result
include/ti84/graph/      graph window and sampling API
include/ti84/math/       matrices, matrix operations, statistics, numerical methods
include/ti84/storage/    versioned memory persistence
include/ti84/program/    restricted BASIC-like runtime
include/ti84/ui/         keypad definitions, framebuffer, menu, session state
src/                     implementations and terminal frontend
tests/                   core and UI/math tests
examples/                sample BASIC-like program
docs/                    architecture, features, roadmap, development
.github/workflows/       CMake build/test CI
```

## Honest limitations

This is not yet a complete graphical or cycle-accurate hardware emulator. The keypad and framebuffer are UI abstractions; there is no finished GUI renderer, pixel-perfect shell, complete TI-BASIC dialect, complex-number expression support, symbolic algebra, device link protocol, or proprietary device compatibility. Degree-mode conversion is declared in settings but not yet wired into expression evaluation.

## Security and licensing

The BASIC-like runtime supports only a limited set of statements and does not execute shell commands or native code. Original project code is MIT licensed; see `LICENSE`. The project is independent and not affiliated with Texas Instruments.
