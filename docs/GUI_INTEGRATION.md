# GUI Integration Plan

## Current state
The repository's native application is a C++23 terminal frontend over `ti84core`. The `gui/` folder is a self-contained browser preview that demonstrates interaction and UI structure, but it does not yet bind to the native C++ library. Its JavaScript math evaluator is explicitly a preview implementation, not a replacement for the C++ expression parser.

## Recommended production architecture
1. **Core library:** keep `ti84core` independent of platform and UI toolkits.
2. **Command service:** expose a small typed interface for evaluation, variable state, graph sampling, settings, and memory operations.
3. **Desktop adapter:** use Qt 6 Widgets/QML, SDL plus an explicit font renderer, or a WebView shell. Prefer Qt for native forms and accessibility; prefer a WebView shell when shared HTML/CSS is the priority.
4. **Serialization:** use a versioned JSON contract and validate all sizes, numeric bounds, filenames, and enum values.
5. **Testing:** keep deterministic core tests; add adapter tests and end-to-end UI smoke tests.

## Suggested API contract
Request:
```json
{"version":1,"id":"req-1","op":"calculate","expression":"sin(pi/2)","angleMode":"RAD"}
```
Success:
```json
{"version":1,"id":"req-1","ok":true,"result":1}
```
Failure:
```json
{"version":1,"id":"req-1","ok":false,"error":{"code":"EXPRESSION_ERROR","message":"..."}}
```

Operations to add incrementally:
- `calculate`: call the existing `Calculator` / `Expression` code.
- `graph`: call `GraphEngine::sample` and return bounded point arrays.
- `memory.load` / `memory.save`: use `MemoryStore`, with explicit user-selected paths in desktop mode.
- `program.run`: call `BasicRuntime` with execution limits and return structured output.
- `settings.get` / `settings.set`: serialize validated application preferences.

## Safety and reliability
- Do not load firmware or ROM files from unknown sources. This repository should use original data and documented formats.
- Do not execute generated code, shell commands, native modules, or arbitrary BASIC statements.
- A loopback bridge must bind to localhost only, reject unexpected origins, use strict request schemas, cap request size, and avoid permissive CORS.
- Keep workspace import/export schema-versioned and reject malformed input.
