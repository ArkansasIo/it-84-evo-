(() => {
  "use strict";
  const $ = (id) => document.getElementById(id);
  const state = { angle: "RAD", precision: 10, persist: true, history: [], ans: 0, lastGraph: "sin(x)" };
  const STORAGE_KEY = "ti84evo-gui-preview-v1";
  const safeFunctions = {
    sin: Math.sin, cos: Math.cos, tan: Math.tan, asin: Math.asin, acos: Math.acos, atan: Math.atan,
    sqrt: Math.sqrt, abs: Math.abs, ln: Math.log, log: Math.log10, exp: Math.exp,
    floor: Math.floor, ceil: Math.ceil, round: Math.round, min: Math.min, max: Math.max
  };
  function setError(message = "") { $("errorDisplay").textContent = message; }
  function normalizeExpression(source) {
    return source.trim().replace(/×/g, "*").replace(/÷/g, "/").replace(/π/g, "pi").replace(/−/g, "-").replace(/\^/g, "**");
  }
  function evaluate(source, vars = {}) {
    const raw = normalizeExpression(source);
    if (!raw) throw new Error("Enter an expression first.");
    if (raw.length > 500) throw new Error("Expression is too long (maximum 500 characters).");
    // Token whitelist: evaluation runs a generated expression containing only numbers, operators,
    // parentheses, commas, and allow-listed identifiers. No property access or arbitrary code.
    const identifierPattern = /[A-Za-z_][A-Za-z_0-9]*/g;
    const converted = raw.replace(identifierPattern, (name) => {
      const lower = name.toLowerCase();
      if (lower === "pi") return String(Math.PI);
      if (lower === "e") return String(Math.E);
      if (lower === "ans") return String(state.ans);
      if (Object.prototype.hasOwnProperty.call(vars, name)) return String(vars[name]);
      if (Object.prototype.hasOwnProperty.call(vars, lower)) return String(vars[lower]);
      if (Object.prototype.hasOwnProperty.call(safeFunctions, lower)) return lower;
      if (lower === "x") return "x";
      throw new Error("Unknown variable or function: " + name);
    });
    if (/[^0-9+\-*/%.(),\sA-Za-z_]/.test(converted)) throw new Error("Unsupported character in expression.");
    if (/(^|[^A-Za-z_])(?:window|document|globalThis|constructor|prototype|__proto__)([^A-Za-z_]|$)/i.test(converted)) throw new Error("Identifier is not allowed.");
    const identifiers = converted.match(/[A-Za-z_][A-Za-z_0-9]*/g) || [];
    const allowed = new Set([...Object.keys(safeFunctions), "x"]);
    for (const id of identifiers) if (!allowed.has(id)) throw new Error("Unsupported identifier: " + id);
    // A parser-like constrained function is used only after lexical validation, with an explicit environment.
    const names = [...Object.keys(safeFunctions), "x"];
    const values = [...Object.values(safeFunctions), vars.x ?? 0];
    const fn = new Function(...names, '"use strict"; return (' + converted + ');');
    const value = fn(...values);
    if (typeof value !== "number" || !Number.isFinite(value)) throw new Error("Result is not a finite real number.");
    return value;
  }
  function format(value) {
    if (!Number.isFinite(value)) return "Undefined";
    return Number(value.toPrecision(state.precision)).toString();
  }
  function toRadians(v) { return state.angle === "DEG" ? v * Math.PI / 180 : v; }
  function displayEvaluate(source, vars = {}) {
    // Convert simple trig calls in degree mode before invoking the safe numeric evaluator.
    if (state.angle === "DEG") {
      source = source.replace(/\b(sin|cos|tan)\s*\(\s*([^()]+)\s*\)/gi, (all, name, arg) => name + "((" + arg + ")*pi/180)");
      // inverse trig returns radians internally; TI-style degree conversion for top-level inverse calls.
      source = source.replace(/\b(a(?:sin|cos|tan))\s*\(/gi, "($1(").replace(/\b(asin|acos|atan)\(([^()]+)\)/gi, "($1($2)*180/pi)");
    }
    return evaluate(source, vars);
  }
  function record(expr, result) {
    state.ans = result;
    state.history.unshift({ expr, result: format(result), at: new Date().toISOString() });
    state.history = state.history.slice(0, 100);
    renderHistory(); persist();
  }
  function runCalculation(expr = $("expressionInput").value) {
    setError();
    try {
      const result = displayEvaluate(expr);
      $("expressionInput").value = expr;
      $("expressionDisplay").textContent = expr;
      $("resultDisplay").textContent = format(result);
      record(expr, result);
      return result;
    } catch (err) {
      $("expressionDisplay").textContent = expr || "0";
      $("resultDisplay").textContent = "Error";
      setError(err.message || String(err));
      return null;
    }
  }
  function renderHistory() {
    $("historyCount").textContent = state.history.length + (state.history.length === 1 ? " entry" : " entries");
    const host = $("historyList");
    host.replaceChildren();
    if (!state.history.length) { host.innerHTML = '<div class="empty-state">Your calculations will appear here.</div>'; return; }
    state.history.slice(0, 12).forEach((entry) => {
      const button = document.createElement("button");
      button.className = "history-entry";
      const left = document.createElement("span");
      const expr = document.createElement("span"); expr.className = "h-expr"; expr.textContent = entry.expr;
      const result = document.createElement("span"); result.className = "h-result"; result.textContent = "= " + entry.result;
      left.append(expr, result);
      const date = document.createElement("small"); date.textContent = new Date(entry.at).toLocaleTimeString([], {hour:"2-digit",minute:"2-digit"});
      button.append(left, date);
      button.addEventListener("click", () => { $("expressionInput").value = entry.expr; $("expressionInput").focus(); });
      host.append(button);
    });
  }
  function drawGraph(canvas, expr, windowBounds) {
    if (!canvas) return;
    const ctx = canvas.getContext("2d");
    const w = canvas.width, h = canvas.height;
    const { xMin, xMax, yMin, yMax } = windowBounds;
    ctx.clearRect(0, 0, w, h);
    ctx.fillStyle = "#0b1420"; ctx.fillRect(0,0,w,h);
    const px = (x) => (x - xMin) / (xMax - xMin) * w;
    const py = (y) => h - (y - yMin) / (yMax - yMin) * h;
    ctx.lineWidth = 1; ctx.strokeStyle = "#203247"; ctx.fillStyle = "#7c91a9"; ctx.font = "12px monospace";
    const xStep = niceStep((xMax-xMin)/8), yStep = niceStep((yMax-yMin)/6);
    ctx.beginPath();
    for (let x = Math.ceil(xMin/xStep)*xStep; x <= xMax; x += xStep) { const X=px(x); ctx.moveTo(X,0);ctx.lineTo(X,h); }
    for (let y = Math.ceil(yMin/yStep)*yStep; y <= yMax; y += yStep) { const Y=py(y);ctx.moveTo(0,Y);ctx.lineTo(w,Y); }
    ctx.stroke();
    ctx.strokeStyle="#657b92";ctx.lineWidth=1.4;ctx.beginPath();
    if(xMin<=0&&xMax>=0){ctx.moveTo(px(0),0);ctx.lineTo(px(0),h)}
    if(yMin<=0&&yMax>=0){ctx.moveTo(0,py(0));ctx.lineTo(w,py(0))}
    ctx.stroke();
    ctx.fillStyle="#90a4bb";
    if(yMin<=0&&yMax>=0) for(let x=Math.ceil(xMin/xStep)*xStep;x<=xMax;x+=xStep){if(Math.abs(x)>1e-8)ctx.fillText(String(Number(x.toPrecision(4))),Math.min(w-35,Math.max(2,px(x)+4)),Math.min(h-4,Math.max(12,py(0)+14)))}
    if(xMin<=0&&xMax>=0) for(let y=Math.ceil(yMin/yStep)*yStep;y<=yMax;y+=yStep){if(Math.abs(y)>1e-8)ctx.fillText(String(Number(y.toPrecision(4))),Math.min(w-35,Math.max(2,px(0)+5)),Math.min(h-4,Math.max(12,py(y)-4)))}
    ctx.strokeStyle="#6de0c0";ctx.lineWidth=2.4;ctx.beginPath();let started=false, prevY=null;
    for(let i=0;i<=Math.min(w*2,2400);i++){
      const x=xMin+(xMax-xMin)*i/Math.min(w*2,2400);let y;
      try{y=displayEvaluate(expr,{x})}catch{started=false;prevY=null;continue}
      if(!Number.isFinite(y)||y<yMin-10*(yMax-yMin)||y>yMax+10*(yMax-yMin)){started=false;prevY=null;continue}
      const Y=py(y);
      if(!started||prevY===null||Math.abs(Y-prevY)>h*.7){ctx.moveTo(px(x),Y);started=true}else ctx.lineTo(px(x),Y);
      prevY=Y;
    }
    ctx.stroke();
  }
  function niceStep(raw) { const p=Math.pow(10,Math.floor(Math.log10(Math.max(raw,1e-9))));const n=raw/p;return (n<1.5?1:n<3.5?2:n<7.5?5:10)*p; }
  function currentBounds(prefix = "") {
    const val = (id, fallback) => { const n=Number($(prefix+id).value); return Number.isFinite(n)?n:fallback; };
    return {xMin:val("xMin",-10),xMax:val("xMax",10),yMin:val("yMin",-2),yMax:val("yMax",2)};
  }
  function updatePlots(expr = state.lastGraph) {
    state.lastGraph = expr;
    drawGraph($("miniGraph"), expr, {xMin:-10,xMax:10,yMin:-2,yMax:2});
    drawGraph($("mainGraph"), $("graphExpression")?.value || expr, currentBounds());
    $("plotExpression").textContent = expr;
  }
  function navigate(view) {
    document.querySelectorAll(".view").forEach((el) => el.classList.toggle("hidden", el.id !== "view-"+view));
    document.querySelectorAll(".nav").forEach((el) => el.classList.toggle("active", el.dataset.view === view));
    if (view === "graph") updatePlots();
  }
  function persist() {
    if (!state.persist) return;
    try { localStorage.setItem(STORAGE_KEY, JSON.stringify({angle:state.angle,precision:state.precision,persist:state.persist,history:state.history,ans:state.ans,lastGraph:state.lastGraph})); } catch {}
  }
  function load() {
    try {
      const saved=JSON.parse(localStorage.getItem(STORAGE_KEY)||"null");
      if(saved&&typeof saved==="object"){state.angle=saved.angle==="DEG"?"DEG":"RAD";state.precision=[6,10,14].includes(Number(saved.precision))?Number(saved.precision):10;state.persist=saved.persist!==false;state.history=Array.isArray(saved.history)?saved.history.filter(x=>x&&typeof x.expr==="string"&&typeof x.result==="string").slice(0,100):[];state.ans=Number(saved.ans)||0;state.lastGraph=typeof saved.lastGraph==="string"?saved.lastGraph:"sin(x)";}
    } catch {}
    $("angleMode").value=state.angle;$("angleChip").textContent=state.angle;$("modeLabel").textContent=state.angle+" · FLOAT";$("precision").value=String(state.precision);$("persist").checked=state.persist;$("graphExpression").value=state.lastGraph;
  }
  function exportWorkspace() {
    const payload={format:"ti84evo-gui-workspace",version:1,settings:{angle:state.angle,precision:state.precision,persist:state.persist},history:state.history,ans:state.ans,lastGraph:state.lastGraph,program:$("programSource").value};
    const blob=new Blob([JSON.stringify(payload,null,2)],{type:"application/json"});
    const url=URL.createObjectURL(blob);const a=document.createElement("a");a.href=url;a.download="ti84evo-workspace.json";a.click();URL.revokeObjectURL(url);
  }
  function importWorkspace(file) {
    const reader=new FileReader();
    reader.onload=()=>{try{const d=JSON.parse(String(reader.result));if(d.format!=="ti84evo-gui-workspace"||d.version!==1)throw new Error("Unsupported workspace format.");
      const s=d.settings||{};state.angle=s.angle==="DEG"?"DEG":"RAD";state.precision=[6,10,14].includes(Number(s.precision))?Number(s.precision):10;state.persist=s.persist!==false;state.history=Array.isArray(d.history)?d.history.filter(x=>x&&typeof x.expr==="string"&&typeof x.result==="string").slice(0,100):[];state.ans=Number(d.ans)||0;state.lastGraph=typeof d.lastGraph==="string"?d.lastGraph:"sin(x)";if(typeof d.program==="string")$("programSource").value=d.program;loadControls();renderHistory();updatePlots();persist();}catch(e){alert("Could not import workspace: "+e.message)}};
    reader.readAsText(file);
  }
  function loadControls(){ $("angleMode").value=state.angle;$("angleChip").textContent=state.angle;$("modeLabel").textContent=state.angle+" · FLOAT";$("precision").value=String(state.precision);$("persist").checked=state.persist;$("graphExpression").value=state.lastGraph; }
  function runProgram() {
    const lines=$("programSource").value.split(/\r?\n/);const vars={};const output=[];let ended=false;
    for(let i=0;i<lines.length&&i<1000;i++){
      let line=lines[i].trim().replace(/^\d+\s*/,"");if(!line||line.startsWith("'")||line.startsWith("REM "))continue;
      if(/^END$/i.test(line)){ended=true;break}
      let m=line.match(/^PRINT\s+(.+)$/i);
      if(m){let value=m[1].trim();const quoted=value.match(/^"(.*)"$/);try{output.push(quoted?quoted[1]:format(displayEvaluate(value,vars)))}catch(e){output.push("Line "+(i+1)+": "+e.message);$("programStatus").textContent="ERROR";$("programOutput").textContent=output.join("\n");return}}
      else if((m=line.match(/^LET\s+([A-Za-z][A-Za-z0-9_]*)\s*=\s*(.+)$/i))){try{vars[m[1]]=displayEvaluate(m[2],vars)}catch(e){output.push("Line "+(i+1)+": "+e.message);$("programStatus").textContent="ERROR";$("programOutput").textContent=output.join("\n");return}}
      else {output.push("Line "+(i+1)+": Unsupported statement");$("programStatus").textContent="ERROR";$("programOutput").textContent=output.join("\n");return}
    }
    $("programStatus").textContent="DONE";$("programOutput").textContent=output.join("\n")||"(no output)";if(!ended) $("programOutput").textContent+="\n\n[Preview stopped at end of source]";
  }
  $("calcForm").addEventListener("submit",(e)=>{e.preventDefault();const result=runCalculation();if(result!==null)updatePlots(state.lastGraph);});
  $("keypad").addEventListener("click",(e)=>{const b=e.target.closest("button");if(!b)return;const input=$("expressionInput");if(b.dataset.key){input.value+=b.dataset.key;input.focus()}else if(b.dataset.action==="clear"){input.value="";$("expressionDisplay").textContent="0";$("resultDisplay").textContent="Ready";setError();input.focus()}else if(b.dataset.action==="backspace"){input.value=input.value.slice(0,-1);input.focus()}else if(b.dataset.action==="equals"){const v=runCalculation();if(v!==null)updatePlots(state.lastGraph)}});
  document.querySelectorAll("[data-view]").forEach(b=>b.addEventListener("click",()=>navigate(b.dataset.view)));
  document.querySelectorAll("[data-navigate]").forEach(b=>b.addEventListener("click",()=>navigate(b.dataset.navigate)));
  $("clearHistory").addEventListener("click",()=>{state.history=[];renderHistory();persist()});
  $("graphForm").addEventListener("submit",(e)=>{e.preventDefault();const b=currentBounds();if(!(b.xMin<b.xMax&&b.yMin<b.yMax)){ $("graphMessage").textContent="Bounds invalid: each minimum must be less than its maximum.";return }const expr=$("graphExpression").value.trim();try{displayEvaluate(expr,{x:0});state.lastGraph=expr;updatePlots(expr);$("graphMessage").textContent="Plotted y = "+expr+" · "+(state.angle==="DEG"?"degrees":"radians");persist()}catch(err){$("graphMessage").textContent="Plot error: "+err.message}});
  $("angleMode").addEventListener("change",(e)=>{state.angle=e.target.value;loadControls();persist();updatePlots()});
  $("precision").addEventListener("change",(e)=>{state.precision=Number(e.target.value);persist()});
  $("persist").addEventListener("change",(e)=>{state.persist=e.target.checked;if(state.persist)persist();else localStorage.removeItem(STORAGE_KEY)});
  $("resetSettings").addEventListener("click",()=>{if(!confirm("Reset saved settings and history?"))return;state.angle="RAD";state.precision=10;state.persist=true;state.history=[];state.ans=0;state.lastGraph="sin(x)";loadControls();renderHistory();updatePlots();persist()});
  $("exportBtn").addEventListener("click",exportWorkspace);
  $("importFile").addEventListener("change",(e)=>{if(e.target.files[0])importWorkspace(e.target.files[0]);e.target.value=""});
  $("runProgram").addEventListener("click",runProgram);
  load();renderHistory();updatePlots();$("graphMessage").textContent="Graph is rendered locally in your browser.";
})();