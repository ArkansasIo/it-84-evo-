# Roadmap

## Numerical core
- [x] C++23/CMake project and expression parser
- [x] Graph sampling API
- [x] Matrix multiply, determinant, transpose, inverse and RREF
- [x] Summary statistics and linear regression
- [x] Derivative, Simpson integration and bisection root solver
- [x] Complex helper functions and normal/binomial probability helpers
- [x] Versioned memory and restricted BASIC-like runtime

## Calculator behavior
- [ ] Wire degree/radian mode into trig functions
- [ ] Integrate complex numbers into expression parsing/evaluation
- [ ] Add probability distributions, confidence intervals and hypothesis tests
- [ ] Expand list/matrix editing and regression families
- [ ] Extend the safe program runtime with bounded loops and conditional statements

## GUI preview
- [x] Responsive browser GUI shell
- [x] Keypad and expression history
- [x] Local graph plot with configurable window
- [x] Restricted BASIC-like editor preview
- [x] Angle-mode and precision preferences
- [x] Workspace JSON import/export
- [ ] Replace preview math with calls into the native C++ core

## Native graphical front end
- [ ] Add a desktop UI toolkit target (Qt 6 recommended for native UI; WebView for HTML reuse)
- [ ] Add typed JSON API with validation for calculator, graph, memory, settings, and program calls
- [ ] Text/font drawing and calculator shell
- [ ] Trace cursor, pan/zoom, graph table and multiple plotted functions
- [ ] Integration and end-to-end GUI tests

## Quality
- [x] GitHub Actions CMake build/test workflow
- [ ] Verify latest CI is green
- [ ] Sanitizer and parser/file-loader fuzz builds
- [ ] MSVC/GCC/Clang matrix and numerical benchmarks

## Emulator boundary
This repository currently targets calculator software, not a cycle-accurate hardware emulator. Hardware emulation would require documented architecture details, CPU/peripheral models, keypad/display timing, and legally sourced or user-supplied firmware images. No TI BIOS/CMOS or ROM dump is included.
