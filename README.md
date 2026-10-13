# TI-84 Evo-Inspired Calculator Clone (C++23)

An original modular native C++23 graphing-calculator software project. It does not include proprietary firmware, ROM dumps, or copied assets.

## Current implementation

- Expression parser with operator precedence, variables, constants `pi` and `e`, and common single-argument math functions.
- Interactive terminal shell with expression evaluation, variables, graph sampling, summary statistics, memory save/load, and a sandboxed BASIC-like `LET`/`PRINT` runner.
- Graph sampling API that preserves discontinuities as NaN gaps.
- Matrix multiplication and determinant using pivoting.
- Descriptive statistics and linear regression.
- Versioned persistent key/value memory storage.
- CMake build and unit tests.

## Build (Windows / Visual Studio 2022)

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\ti84evo.exe
```

## Build (Linux / macOS)

Requires CMake 3.20+ and a C++23 compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/ti84evo
```

## Shell commands

- `:help` — command summary
- `:let A = 12/3` — define variable
- `:vars` — list variables
- `:graph sin(x)` — sample a function
- `:stats 2,4,6,8` — descriptive statistics
- `:save memory.mem` / `:load memory.mem` — save or load memory store
- `:run examples/demo.bas` — run a limited BASIC-like program
- `:quit` — exit

## Structure

```text
include/ti84/core/       expression and calculator interfaces
include/ti84/graph/      graphing API
include/ti84/math/       matrix and statistics APIs
include/ti84/storage/    persistent memory API
include/ti84/program/    restricted BASIC-like runtime API
src/app/                 terminal frontend
src/core/                expression evaluator and calculator
src/graph/               graph sampling
src/math/                matrix and statistics implementations
src/storage/             memory persistence
src/program/             BASIC-like runtime
tests/                   test suite
docs/                    architecture and roadmap
examples/                sample program
```

## Limitations

This is a working calculator-software foundation, not a cycle-accurate hardware emulator or full graphical LCD/keypad application. Degree-mode conversion, complex-number evaluation, symbolic algebra, a full TI-BASIC implementation, GUI, and device-level compatibility are not yet implemented.

## License

MIT. This is original software and is not affiliated with or endorsed by Texas Instruments.