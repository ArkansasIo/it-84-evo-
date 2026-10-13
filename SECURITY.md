# Security policy

## Scope
This project is an independent calculator software foundation. The limited program runtime must remain sandboxed: calculator statements must not execute shell commands, load native code, or access arbitrary files.

## Reporting
Report suspected security issues privately to the repository owner before publishing exploit details. Include the affected commit, a concise reproduction, expected behavior, and observed behavior.

## Data handling
Memory files are untrusted input. Enforce size limits, validate formats before replacing live state, and never treat stored values as executable content.
