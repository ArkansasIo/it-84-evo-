# UI subsystem design

The UI code uses a backend-independent framebuffer and state model.

- `Display` owns a bounded RGBA pixel buffer.
- `Keypad` declares key identities and a physical-style layout.
- `mapKeyToAction` maps supported keys into expression text or control actions.
- `Menu` tracks selection and disabled items.
- `CalculatorSession` manages screen state, expression input and a bounded history.
- `GraphRenderer` draws a basic grid, axes and sampled function series into the framebuffer.

## Renderer contract

Graph window coordinates are converted to pixel coordinates. Non-finite samples break a curve instead of connecting across discontinuities. The renderer clips pixels through the Display API and requires no external GUI dependency.

## Still needed for a complete desktop application

A platform window, event pump, font/text drawing, mouse/keyboard event wiring, resize behavior, calculator casing/keys, menu rendering and integration into an executable frontend are not yet present. SDL2 or Qt can be added as an optional frontend target without making the math library depend on it.
