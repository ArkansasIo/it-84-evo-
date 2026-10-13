# Contributing

## Workflow
1. Create a focused branch and keep changes small.
2. Define APIs under `include/ti84` and implement them under `src`.
3. Register source files and test targets in `CMakeLists.txt`.
4. Add tests for valid results and invalid inputs.
5. Update README, feature inventory and roadmap.
6. Run CMake configure, build and CTest before opening a pull request.

## Coding expectations
- Use C++23 and standard-library facilities unless a dependency is justified.
- Keep the math core independent of UI frameworks.
- Validate public input and use `Result<T>` for expected failures.
- Avoid global mutable state and unsafe execution of calculator programs.
- Do not add proprietary firmware, ROM dumps, keys, or copyrighted device assets.

## Local verification
```bash
cmake --preset release
cmake --build --preset release
ctest --preset release
```
