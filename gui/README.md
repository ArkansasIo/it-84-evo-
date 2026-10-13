# TI-84 Evo-Inspired GUI (Preview)

This folder provides a local browser GUI shell for the C++23 calculator project. It is deliberately separate from the native C++ target, so the core remains dependency-free.

## Launch
Open `index.html` in a modern browser, or serve the repository root with a static file server:

```bash
python -m http.server 8080
```

Then open `http://localhost:8080/gui/`.

## Included
- Responsive graphing-calculator dashboard with keypad, history, graph plot, settings, and a BASIC-like program editor.
- Safe expression evaluator in JavaScript for the GUI preview; it does not execute arbitrary JavaScript.
- Local settings/history persistence using browser local storage.
- Export/import JSON workspace for expressions and settings.

## Integration status
This is a self-contained **GUI preview** and does not call the C++ core yet. The production integration path is to expose a small JSON API via a native IPC bridge or local loopback service, then route calculate/graph/program operations to `ti84core`. Never expose a loopback API without strict origin checks and a local-only bind.

No proprietary TI firmware, BIOS/CMOS dump, ROM image, or copied assets are bundled. Settings, memory images, and example programs are original project data.
