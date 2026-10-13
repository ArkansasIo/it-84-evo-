# Feature inventory

## Implemented source modules
- Numeric expression parser, operator precedence, variables, constants `pi` and `e`.
- Real-valued trigonometric, inverse-trigonometric, logarithmic, exponential, square-root, absolute, floor and ceiling functions.
- Graph sampling with validated windows and discontinuity gaps.
- Matrix multiplication, determinant, transpose, inverse and reduced row-echelon form.
- Summary statistics, sample standard deviation and linear regression.
- Central-difference derivative, composite Simpson integration and bracketed bisection root finding.
- Complex number helpers: conjugate, magnitude, argument and checked division.
- Normal probability density/CDF and binomial probability mass function.
- Versioned key/value memory storage.
- Restricted BASIC-like `LET` and `PRINT` runtime.
- Terminal shell, keypad definitions/input mapping, RGBA framebuffer, menu/session state and framebuffer graph renderer.
- CMake test targets and GitHub Actions CI.

## Foundations, not complete user-facing features
- Complex helpers are not integrated into the expression parser.
- The graph renderer draws pixels but has no font/text renderer or native window.
- Keypad mapping is a state/input abstraction, not a finished clickable virtual calculator.
- Session/menu classes provide state; a full event loop and rendered UI remain future work.
- Degree-mode settings are not yet applied to trig evaluation.
- Numerical routines are approximations; callers must choose sensible tolerances and domains.

## Not implemented
- Full graphical application and pixel-accurate TI-84 Evo casing/screen.
- Complete BASIC dialect with control flow, editor and debugger.
- Symbolic algebra/calculus, broad distribution and hypothesis-test catalog.
- Hardware-level emulation, proprietary ROM or device-link compatibility.
