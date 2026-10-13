# GUI Integration Plan

## Current state
The native application is a C++23 terminal frontend over `ti84core`. The `gui/` folder is a separate browser preview and does not yet bind to the native library. Its JavaScript evaluator is a prototype, not a replacement for the C++ expression parser.

## Recommended architecture
1. Keep `ti84core` platform-independent.
2. Expose a narrow typed interface for evaluation, variables, graph sampling, settings, and memory.
3. Add a desktop adapter (Qt 6, SDL with text rendering, or a WebView shell).
4. Use a versioned JSON request/response contract and validate input sizes, paths, bounds, and enum values.
5. Preserve deterministic core tests; add adapter tests and end-to-end GUI smoke tests.

## Suggested contract
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

Implement operations incrementally: `calculate`, `graph` via `GraphEngine::sample`, `memory.load/save` via `MemoryStore`, `program.run` via `BasicRuntime`, and validated `settings.get/set`.

## Safety
- Do not include firmware or ROM images from unknown sources.
- Do not execute arbitrary code, shell commands, or unrestricted BASIC statements.
- Any local bridge must bind to loopback only, validate origins and requests, cap payload sizes, and avoid permissive CORS.
- Workspace imports must be schema-versioned and validated.
