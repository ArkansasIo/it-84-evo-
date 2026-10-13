# Architecture

The numerical core is independent of the terminal frontend and intended to support a future graphical frontend.

- `core/Expression`: numeric expression parser and evaluator.
- `core/Calculator`: facade for variables and user settings.
- `graph/GraphEngine`: samples an expression across an x-axis window.
- `math/Matrix`: checked element access, multiplication and determinant.
- `math/statistics`: summary statistics and least-squares linear regression.
- `storage/MemoryStore`: versioned persistent key/value data.
- `program/BasicRuntime`: limited BASIC-like `LET` and `PRINT` interpreter.
- `app/main.cpp`: terminal command shell.

## Extension seams

1. Add display-buffer and keypad interfaces, then a separate SDL2 or Qt frontend.
2. Wire angle-mode conversion through evaluator context.
3. Add complex numbers, vector operations, matrix inverse/RREF, distributions and numerical calculus.
4. Add key navigation/menu state machine, graph pan/zoom/trace/table views.
5. Add parser fuzzing, sanitizers and CI across MSVC, GCC, and Clang.

No proprietary firmware or ROM is required or included.
