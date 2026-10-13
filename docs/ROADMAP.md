# Roadmap

## Phase 1 — numerical foundation
- [x] C++23 and CMake project
- [x] Expression parser and variables
- [x] Graph sampling API
- [x] Matrix multiply and determinant
- [x] Matrix transpose, inverse and RREF
- [x] Summary statistics and linear regression
- [x] Numerical derivative, Simpson integration and bisection
- [x] Versioned memory persistence
- [x] Restricted BASIC-like runtime
- [x] Core and UI/math tests

## Phase 2 — calculator behavior
- [ ] Apply degree/radian mode to trig functions
- [ ] Complex number type and complex expression support
- [ ] List editor, probability distributions and hypothesis tests
- [ ] Additional regressions and matrix/vector operations
- [ ] Error recovery and expression history persistence
- [ ] Extend programming runtime with safe branching and loops plus execution budgets

## Phase 3 — graphical front end
- [x] RGBA framebuffer foundation
- [x] Key identity/layout definitions
- [x] Menu and session state models
- [ ] SDL2 or Qt renderer target
- [ ] Draw text, fonts, screen chrome and keypad
- [ ] Mouse/touch and keyboard key events
- [ ] Graph rendering, trace cursor, pan/zoom and table
- [ ] Settings and modal menu navigation

## Phase 4 — quality
- [x] GitHub Actions configure/build/test workflow
- [ ] Verify CI green on GitHub Actions
- [ ] Sanitizer and parser/file-loader fuzz builds
- [ ] Numerical error analysis and benchmarks
- [ ] Cross-platform MSVC, GCC and Clang test matrix
