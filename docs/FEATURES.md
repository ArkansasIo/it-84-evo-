# Feature inventory

## Implemented source modules
- Numeric expression parser, arithmetic precedence, named numeric variables and constants `pi` / `e`.
- Common real-valued trigonometric, inverse-trigonometric, logarithmic, exponential, square-root, absolute, floor and ceiling functions.
- Graph sampling over a validated x/y window; invalid samples are represented as gaps.
- Matrix multiplication, determinant, transpose, inverse, and reduced row-echelon form.
- Descriptive statistics, sample standard deviation, linear regression.
- Central-difference derivative, composite Simpson integration and bracketed bisection root finding.
- Versioned key/value persistence.
- Restricted BASIC-like `LET` and `PRINT` interpreter.
- Terminal shell, key definitions, RGBA framebuffer, menu state, input/history/screen session model.
- CMake test targets and GitHub Actions workflow.

## Foundations, not finished end-user features
- Keypad layout is a data definition, not a physical or clickable UI.
- Framebuffer stores pixels but does not yet draw text, fonts, or a calculator skin.
- Session and menu classes provide state only; no SDL/Qt renderer is wired.
- Angle mode is not applied by the expression evaluator.
- Numerical algorithms are general-purpose approximations and require domain-aware callers.

## Not implemented yet
- Full graphical UI, virtual clickable keypad, pixel-perfect screen, table/trace/pan/zoom controls.
- Complex-number parser and expression arithmetic.
- Complete TI-BASIC dialect with branching, loops, program editor and debugger.
- Probability distributions, hypothesis testing and additional regression models.
- Symbolic algebra/calculus, robust equation solver beyond bisection, device-level compatibility or link cable protocol.
- Proprietary firmware or ROM emulation.
