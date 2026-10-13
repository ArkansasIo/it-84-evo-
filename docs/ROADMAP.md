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

## Graphical front end
- [x] RGBA framebuffer
- [x] Key identity/layout and expression input mapping
- [x] Menu and calculator session state
- [x] Framebuffer graph/grid/axis renderer
- [ ] SDL2 or Qt window and event loop
- [ ] Text/font drawing and calculator shell
- [ ] Clickable keypad, menus, settings and dialogs
- [ ] Trace cursor, pan/zoom, graph table and multiple plotted functions

## Quality
- [x] GitHub Actions CMake build/test workflow
- [ ] Verify latest CI is green
- [ ] Sanitizer and parser/file-loader fuzz builds
- [ ] MSVC/GCC/Clang matrix and numerical benchmarks
