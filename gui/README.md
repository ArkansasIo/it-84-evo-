# TI-84 Evo-Inspired GUI (Preview)

This folder provides a local browser GUI shell for the C++23 calculator project. It is separate from the native C++ target, so the core remains dependency-free.

## Launch
Open `index.html` in a modern browser, or serve the repository root:

```bash
python -m http.server 8080
```

Then visit `http://localhost:8080/gui/`.

## Included
- Responsive calculator dashboard with keypad, history, graph plot, settings, and a BASIC-like editor preview.
- Restricted expression evaluator for the GUI preview; it does not intentionally expose arbitrary application APIs.
- Local settings/history persistence and versioned JSON workspace import/export.

## Integration status
This is a self-contained **GUI preview**. It does not call the C++ core yet. The production integration path is a native bridge that routes evaluation and graph requests to `ti84core`.

No proprietary TI firmware, BIOS/CMOS dump, ROM image, or copied assets are bundled. This independent project is not affiliated with Texas Instruments.
