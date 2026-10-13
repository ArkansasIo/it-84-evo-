(() => {
  "use strict";
  const $ = (id) => document.getElementById(id);
  const state = { angle: "RAD", precision: 10, persist: true, history: [], ans: 0, lastGraph: "sin(x)" };
  const storageKey = "ti84evo-gui-preview-v1";
  const functions = {
    sin: Math.sin, cos: Math.cos, tan: Math.tan,
    asin: Math.asin, acos: Math.acos, atan: Math.atan,
    sqrt: Math.sqrt, abs: Math.abs, ln: Math.log, log: Math.log10,
    exp: Math.exp, floor: Math.floor, ceil: Math.ceil, round: Math.round,
    min: Math.min, max: Math.max
  };

  function setError(message = "") { $("errorDisplay").textContent = message; }
  function format(value) {
    if (!Number.isFinite(value)) return "Undefined";
    return Number(value.toPrecision(state.precision)).toString();
  }
  function normalize(source) {
    return source.trim().replace(/×/g, "*").replace(/÷/g, "/")
      .replace(/π/g, "pi").replace(/−/g, "-").replace(/\^/g, "**");
  }

  // Small recursive-descent parser: no eval/Function, property access, or arbitrary JS.
  function evaluate(source, variables = {}) {
    const input = normalize(source);
    if (!input) throw new Error("Enter an expression first.");
    if (input.length > 500) throw new Error("Expression is too long.");
    let pos = 0;
    const skip = () => { while (/\s/.test(input[pos] || "") && pos < input.length) pos++; };
    const eat = (token) => {
      skip();
      if (input.slice(pos, pos + token.length) === token) { pos += token.length; return true; }
      return false;
    };
    const expect = (token) => { if (!eat(token)) throw new Error("Expected '" + token + "' at position " + (pos + 1)); };
    function expression() {
      let value = term();
      while (true) {
        if (eat("+")) value += term();
        else if (eat("-")) value -= term();
        else return value;
      }
    }
    function term() {
      let value = unary();
      while (true) {
        if (eat("*")) value *= unary();
        else if (eat("/")) { const divisor = unary(); if (divisor === 0) throw new Error("Division by zero."); value /= divisor; }
        else if (eat("%")) { const divisor = unary(); if (divisor === 0) throw new Error("Division by zero."); value %= divisor; }
        else return value;
      }
    }
    function unary() {
      if (eat("+")) return unary();
      if (eat("-")) return -unary();
      return power();
    }
    function power() {
      let value = primary();
      if (eat("**") || eat("^")) value = Math.pow(value, unary());
      return value;
    }
    function primary() {
      skip();
      if (eat("(")) { const v = expression(); expect(")"); return v; }
      const rest = input.slice(pos);
      const number = rest.match(/^(?:\d+\.?\d*|\.\d+)(?:e[+-]?\d+)?/i);
      if (number) { pos += number[0].length; return Number(number[0]); }
      const identifier = rest.match(/^[A-Za-z_][A-Za-z_0-9]*/);
      if (identifier) {
        pos += identifier[0].length;
        const name = identifier[0], lower = name.toLowerCase();
        if (lower === "pi") return Math.PI;
        if (lower === "e") return Math.E;
        if (lower === "ans") return state.ans;
        if (Object.prototype.hasOwnProperty.call(variables, name)) return variables[name];
        if (Object.prototype.hasOwnProperty.call(variables, lower)) return variables[lower];
        if (Object.prototype.hasOwnProperty.call(functions, lower)) {
          expect("(");
          const args = [expression()];
          while (eat(",")) args.push(expression());
          expect(")");
          if ((lower === "min" || lower === "max") ? args.length < 1 : args.length !== 1)
            throw new Error("Wrong argument count for " + name + ".");
          const adjusted = args.slice();
          if (state.angle === "DEG" && ["sin", "cos", "tan"].includes(lower)) adjusted[0] *= Math.PI / 180;
          const result = functions[lower](...adjusted);
          return state.angle === "DEG" && ["asin", "acos", "atan"].includes(lower) ? result * 180 / Math.PI : result;
        }
        if (lower === "x" && Object.prototype.hasOwnProperty.call(variables, "x")) return variables.x;
        throw new Error("Unknown variable or function: " + name);
      }
      throw new Error("Unexpected token at position " + (pos + 1));
    }
    const result = expression();
    skip();
    if (pos !== input.length) throw new Error("Unexpected input at position " + (pos + 1));
    if (typeof result !== "number" || !Number.isFinite(result)) throw new Error("Result is not a finite real number.");
    return result;
  }

  function record(expression, value) {
    state.ans = value;
    state.history.unshift({ expression, result: format(value), at: new Date().toISOString() });
    state.history = state.history.slice(0, 100);
    renderHistory();
    persist();
  }
  function calculate(expression = $("expressionInput").value) {
    setError();
    try {
      const result = evaluate(expression);
      $("expressionInput").value = expression;
      $("expressionDisplay").textContent = expression;
      $("resultDisplay").textContent = format(result);
      record(expression, result);
      return result;
    } catch (error) {
      $("expressionDisplay").textContent = expression || "0";
      $("resultDisplay").textContent = "Error";
      setError(error.message || String(error));
      return null;
    }
  }
  function renderHistory() {
    $("historyCount").textContent = state.history.length + (state.history.length === 1 ? " entry" : " entries");
    const host = $("historyList");
    host.replaceChildren();
    if (!state.history.length) {
      const empty = document.createElement("div");
      empty.className = "empty-state";
      empty.textContent = "Your calculations will appear here.";
      host.append(empty);
      return;
    }
    state.history.slice(0, 12).forEach((entry) => {
      const button = document.createElement("button");
      button.className = "history-entry";
      const left = document.createElement("span");
      const expr = document.createElement("span");
      const result = document.createElement("span");
      const time = document.createElement("small");
      expr.className = "h-expr";
      expr.textContent = entry.expression;
      result.className = "h-result";
      result.textContent = "= " + entry.result;
      time.textContent = new Date(entry.at).toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" });
      left.append(expr, result);
      button.append(left, time);
      button.addEventListener("click", () => { $("expressionInput").value = entry.expression; $("expressionInput").focus(); });
      host.append(button);
    });
  }

  function niceStep(raw) {
    const power = Math.pow(10, Math.floor(Math.log10(Math.max(raw, 1e-9))));
    const n = raw / power;
    return (n < 1.5 ? 1 : n < 3.5 ? 2 : n < 7.5 ? 5 : 10) * power;
  }
  function drawGraph(canvas, source, bounds) {
    if (!canvas) return;
    const ctx = canvas.getContext("2d"), width = canvas.width, height = canvas.height;
    const { xMin, xMax, yMin, yMax } = bounds;
    ctx.clearRect(0, 0, width, height);
    ctx.fillStyle = "#0b1420"; ctx.fillRect(0, 0, width, height);
    const px = x => (x - xMin) / (xMax - xMin) * width;
    const py = y => height - (y - yMin) / (yMax - yMin) * height;
    const xStep = niceStep((xMax - xMin) / 8), yStep = niceStep((yMax - yMin) / 6);
    ctx.lineWidth = 1; ctx.strokeStyle = "#203247"; ctx.beginPath();
    for (let x = Math.ceil(xMin / xStep) * xStep; x <= xMax; x += xStep) { ctx.moveTo(px(x), 0); ctx.lineTo(px(x), height); }
    for (let y = Math.ceil(yMin / yStep) * yStep; y <= yMax; y += yStep) { ctx.moveTo(0, py(y)); ctx.lineTo(width, py(y)); }
    ctx.stroke();
    ctx.strokeStyle = "#657b92"; ctx.lineWidth = 1.3; ctx.beginPath();
    if (xMin <= 0 && xMax >= 0) { ctx.moveTo(px(0), 0); ctx.lineTo(px(0), height); }
    if (yMin <= 0 && yMax >= 0) { ctx.moveTo(0, py(0)); ctx.lineTo(width, py(0)); }
    ctx.stroke();
    ctx.fillStyle = "#90a4bb"; ctx.font = "12px monospace";
    if (yMin <= 0 && yMax >= 0) for (let x = Math.ceil(xMin / xStep) * xStep; x <= xMax; x += xStep) if (Math.abs(x) > 1e-9) ctx.fillText(String(+x.toPrecision(4)), Math.min(width - 35, Math.max(2, px(x) + 4)), Math.min(height - 4, Math.max(12, py(0) + 14)));
    if (xMin <= 0 && xMax >= 0) for (let y = Math.ceil(yMin / yStep) * yStep; y <= yMax; y += yStep) if (Math.abs(y) > 1e-9) ctx.fillText(String(+y.toPrecision(4)), Math.min(width - 35, Math.max(2, px(0) + 5)), Math.min(height - 4, Math.max(12, py(y) - 4)));
    ctx.strokeStyle = "#6de0c0"; ctx.lineWidth = 2.4; ctx.beginPath();
    let started = false, previousY = null;
    const samples = Math.min(width * 2, 2400);
    for (let i = 0; i <= samples; i++) {
      const x = xMin + (xMax - xMin) * i / samples;
      let y;
      try { y = evaluate(source, { x }); } catch { started = false; previousY = null; continue; }
      if (y < yMin - 10 * (yMax - yMin) || y > yMax + 10 * (yMax - yMin)) { started = false; previousY = null; continue; }
      const Y = py(y);
      if (!started || previousY === null || Math.abs(Y - previousY) > height * .7) { ctx.moveTo(px(x), Y); started = true; }
      else ctx.lineTo(px(x), Y);
      previousY = Y;
    }
    ctx.stroke();
  }
  function getBounds() {
    return { xMin: Number($("xMin").value), xMax: Number($("xMax").value), yMin: Number($("yMin").value), yMax: Number($("yMax").value) };
  }
  function updatePlots(expression = state.lastGraph) {
    state.lastGraph = expression;
    drawGraph($("miniGraph"), expression, { xMin: -10, xMax: 10, yMin: -2, yMax: 2 });
    drawGraph($("mainGraph"), $("graphExpression").value || expression, getBounds());
    $("plotExpression").textContent = expression;
  }
  function navigate(view) {
    document.querySelectorAll(".view").forEach(el => el.classList.toggle("hidden", el.id !== "view-" + view));
    document.querySelectorAll(".nav").forEach(el => el.classList.toggle("active", el.dataset.view === view));
    if (view === "graph") updatePlots();
  }
  function persist() {
    if (!state.persist) return;
    try { localStorage.setItem(storageKey, JSON.stringify({ angle: state.angle, precision: state.precision, persist: state.persist, history: state.history, ans: state.ans, lastGraph: state.lastGraph })); } catch {}
  }
  function updateControls() {
    $("angleMode").value = state.angle;
    $("angleChip").textContent = state.angle;
    $("modeLabel").textContent = state.angle + " · FLOAT";
    $("precision").value = String(state.precision);
    $("persist").checked = state.persist;
    $("graphExpression").value = state.lastGraph;
  }
  function load() {
    try {
      const saved = JSON.parse(localStorage.getItem(storageKey) || "null");
      if (saved && typeof saved === "object") {
        state.angle = saved.angle === "DEG" ? "DEG" : "RAD";
        state.precision = [6, 10, 14].includes(Number(saved.precision)) ? Number(saved.precision) : 10;
        state.persist = saved.persist !== false;
        state.history = Array.isArray(saved.history) ? saved.history.filter(e => e && typeof e.expression === "string" && typeof e.result === "string").slice(0, 100) : [];
        state.ans = Number(saved.ans) || 0;
        state.lastGraph = typeof saved.lastGraph === "string" ? saved.lastGraph : "sin(x)";
      }
    } catch {}
    updateControls();
  }
  function exportWorkspace() {
    const payload = { format: "ti84evo-gui-workspace", version: 1, settings: { angle: state.angle, precision: state.precision, persist: state.persist }, history: state.history, ans: state.ans, lastGraph: state.lastGraph, program: $("programSource").value };
    const url = URL.createObjectURL(new Blob([JSON.stringify(payload, null, 2)], { type: "application/json" }));
    const link = document.createElement("a"); link.href = url; link.download = "ti84evo-workspace.json"; link.click(); URL.revokeObjectURL(url);
  }
  function importWorkspace(file) {
    const reader = new FileReader();
    reader.onload = () => {
      try {
        const data = JSON.parse(String(reader.result));
        if (data.format !== "ti84evo-gui-workspace" || data.version !== 1) throw new Error("Unsupported workspace format.");
        const settings = data.settings || {};
        state.angle = settings.angle === "DEG" ? "DEG" : "RAD";
        state.precision = [6, 10, 14].includes(Number(settings.precision)) ? Number(settings.precision) : 10;
        state.persist = settings.persist !== false;
        state.history = Array.isArray(data.history) ? data.history.filter(e => e && typeof e.expression === "string" && typeof e.result === "string").slice(0, 100) : [];
        state.ans = Number(data.ans) || 0;
        state.lastGraph = typeof data.lastGraph === "string" ? data.lastGraph : "sin(x)";
        if (typeof data.program === "string") $("programSource").value = data.program;
        updateControls(); renderHistory(); updatePlots(); persist();
      } catch (error) { alert("Import failed: " + error.message); }
    };
    reader.readAsText(file);
  }
  function runProgram() {
    const lines = $("programSource").value.split(/\r?\n/), variables = {}, output = [];
    let ended = false;
    for (let i = 0; i < lines.length && i < 1000; i++) {
      const line = lines[i].trim().replace(/^\d+\s*/, "");
      if (!line || line.startsWith("'") || /^REM\s/i.test(line)) continue;
      if (/^END$/i.test(line)) { ended = true; break; }
      let match = line.match(/^PRINT\s+(.+)$/i);
      if (match) {
        const value = match[1].trim(), quoted = value.match(/^"(.*)"$/);
        try { output.push(quoted ? quoted[1] : format(evaluate(value, variables))); }
        catch (error) { output.push("Line " + (i + 1) + ": " + error.message); $("programStatus").textContent = "ERROR"; $("programOutput").textContent = output.join("\n"); return; }
      } else if ((match = line.match(/^LET\s+([A-Za-z][A-Za-z0-9_]*)\s*=\s*(.+)$/i))) {
        try { variables[match[1]] = evaluate(match[2], variables); }
        catch (error) { output.push("Line " + (i + 1) + ": " + error.message); $("programStatus").textContent = "ERROR"; $("programOutput").textContent = output.join("\n"); return; }
      } else {
        output.push("Line " + (i + 1) + ": Unsupported statement"); $("programStatus").textContent = "ERROR"; $("programOutput").textContent = output.join("\n"); return;
      }
    }
    $("programStatus").textContent = "DONE";
    $("programOutput").textContent = output.join("\n") || "(no output)";
    if (!ended && lines.length > 1000) $("programOutput").textContent += "\n\n[Stopped after 1000 lines]";
  }

  $("calcForm").addEventListener("submit", event => { event.preventDefault(); if (calculate() !== null) updatePlots(); });
  $("keypad").addEventListener("click", event => {
    const button = event.target.closest("button"); if (!button) return;
    const input = $("expressionInput");
    if (button.dataset.key) { input.value += button.dataset.key; input.focus(); }
    else if (button.dataset.action === "clear") { input.value = ""; $("expressionDisplay").textContent = "0"; $("resultDisplay").textContent = "Ready"; setError(); input.focus(); }
    else if (button.dataset.action === "backspace") { input.value = input.value.slice(0, -1); input.focus(); }
    else if (button.dataset.action === "equals" && calculate() !== null) updatePlots();
  });
  document.querySelectorAll("[data-view]").forEach(button => button.addEventListener("click", () => navigate(button.dataset.view)));
  document.querySelectorAll("[data-navigate]").forEach(button => button.addEventListener("click", () => navigate(button.dataset.navigate)));
  $("clearHistory").addEventListener("click", () => { state.history = []; renderHistory(); persist(); });
  $("graphForm").addEventListener("submit", event => {
    event.preventDefault();
    const b = getBounds();
    if (!(Number.isFinite(b.xMin) && Number.isFinite(b.xMax) && Number.isFinite(b.yMin) && Number.isFinite(b.yMax) && b.xMin < b.xMax && b.yMin < b.yMax)) { $("graphMessage").textContent = "Invalid graph bounds."; return; }
    const expression = $("graphExpression").value.trim();
    try { evaluate(expression, { x: 0 }); state.lastGraph = expression; updatePlots(expression); $("graphMessage").textContent = "Plotted y = " + expression + " (" + state.angle + ")"; persist(); }
    catch (error) { $("graphMessage").textContent = "Plot error: " + error.message; }
  });
  $("angleMode").addEventListener("change", event => { state.angle = event.target.value; updateControls(); persist(); updatePlots(); });
  $("precision").addEventListener("change", event => { state.precision = Number(event.target.value); persist(); });
  $("persist").addEventListener("change", event => { state.persist = event.target.checked; if (state.persist) persist(); else localStorage.removeItem(storageKey); });
  $("resetSettings").addEventListener("click", () => {
    if (!confirm("Reset saved settings and history?")) return;
    Object.assign(state, { angle: "RAD", precision: 10, persist: true, history: [], ans: 0, lastGraph: "sin(x)" });
    updateControls(); renderHistory(); updatePlots(); persist();
  });
  $("exportBtn").addEventListener("click", exportWorkspace);
  $("importFile").addEventListener("change", event => { if (event.target.files[0]) importWorkspace(event.target.files[0]); event.target.value = ""; });
  $("runProgram").addEventListener("click", runProgram);
  load(); renderHistory(); updatePlots(); $("graphMessage").textContent = "Graph is rendered locally in your browser.";
})();