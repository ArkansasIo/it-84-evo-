# Development guide

## Adding a subsystem
1. Define a dependency-light public API under `include/ti84/<module>/`.
2. Implement it under `src/<module>/`.
3. Register the implementation in `CMakeLists.txt`.
4. Add deterministic tests with expected values and invalid-input cases.
5. Update `FEATURES.md` and `ROADMAP.md` so scaffolds are not described as finished features.

## Numerical conventions
- APIs return `Result<T>` for expected input/domain errors.
- Public algorithms should validate dimensions, finite values, iteration counts, and tolerances.
- Root finding requires a bracket with opposite signs.
- Integration uses composite Simpson's rule with an even interval count.
- Matrix inversion uses pivoted Gauss-Jordan elimination.

## UI architecture
The UI layer is intentionally independent of a rendering library. `Display` owns an RGBA framebuffer, `Keypad` defines key identities, `Menu` models selection state, and `CalculatorSession` manages input/history/screens. A future SDL2 or Qt frontend can consume these abstractions without changing the math core.

## CI
GitHub Actions configures the CMake project, builds the targets and runs CTest on pushes and pull requests to `main`.
