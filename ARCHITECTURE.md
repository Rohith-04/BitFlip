# BitFlip Engine — Architecture Reference

---

## OOP Hierarchy

```
Gate  (abstract base)
├── AndGate
├── OrGate
├── NotGate
├── NandGate
├── NorGate
├── XorGate
├── TriStateBuffer
├── Mux
├── Demux
└── SequentialGate  (abstract, extends Gate)
    ├── DFlipFlop
    ├── SRFlipFlop
    ├── JKFlipFlop
    └── ClockDivider

Node  (abstract base — signal routing, no logic)
├── InputNode
├── OutputNode
├── ClockNode
├── ConstantNode
├── BusSplitter
├── BusMerger
├── ProbeNode
├── NumberDisplay
└── SevenSegDisplay

Circuit
├── owns → Gate instances (via unique_ptr)
├── owns → Node instances (via unique_ptr)
├── owns → Wire instances
└── owns → output state table per gate

Propagator
└── operates on → Circuit

ClockDomain
├── operates on → Circuit
└── uses → Propagator

EventLog
└── observes → Circuit (via Propagator notifications)

Command  (abstract base)
├── AddGateCommand
├── RemoveGateCommand
├── ConnectWireCommand
├── DisconnectWireCommand
└── SetInputCommand

CommandHistory
└── owns → Command stack (undo / redo)

Engine
├── owns → Circuit
├── owns → Propagator
├── owns → ClockDomain
├── owns → EventLog
└── owns → CommandHistory
```

---

## File Breakdown

### Core/Types.h
No class. Pure definitions used everywhere.
- `NodeId`, `WireId`, `BlockDefId` — strong enum ID types
- `GateType` — enum of all gate types including Mux, Demux, TriStateBuffer, ClockDivider
- `NodeType` — enum for non-logic nodes: Input, Output, Clock, Constant, BusSplitter, BusMerger, Probe, NumberDisplay, SevenSeg
- `SignalState` — Low, High, Floating, HighZ, Error
  - `Floating` — unconnected input, treated as Low during eval
  - `HighZ`    — driven to high impedance by a TriStateBuffer, not an error
  - `Error`    — bus conflict, two active drivers fighting on same wire
- `ChangeSet` — struct holding what changed after any simulation step
- `ChangeCallback` — std::function the UI registers to receive changes

---

### Core/Wire.h / .cpp
Plain struct. No methods beyond helpers.
- `id` — unique WireId
- `value` (uint32_t) — all bits used for bus, bit 0 only for single bit wire
- `width` — 1 for single bit, >1 for bus. Fixed at connection time, never changes.
- `state` (SignalState) — overall wire health: Low / High / Floating / HighZ / Error
- `dirty` — set when value changes, cleared after UI is notified
- `fromNode`, `fromPin`, `toNode`, `toPin` — endpoints as IDs only, no raw pointers
- `isConnected()`, `isHigh()`, `isBus()`, `getBit(int n)` helpers
- Bus conflict resolution is handled by Propagator, not the wire itself

---

### Core/Gate.h / .cpp
Abstract base class. All logic gates inherit from this.

**Responsibilities**
- Holds input and output wire ID lists
- Pin connection / disconnection
- Declares `evaluate()` pure virtual for combinational gates
- Declares `evaluateNext()` and `commit()` virtual for sequential gates

**Key methods**
- `evaluate(inputs, outputs)` — pure virtual, returns true if output changed
- `evaluateNext(inputs)` — phase 1 of tick, sequential only
- `commit(outputs)` — phase 2 of tick, sequential only, returns true if Q changed
- `isSequential()` — returns false by default, overridden by sequential gates
- `supportsBus()` — returns false by default, overridden by bus-aware gates
- `connectInput(pin, wireId)` / `connectOutput(pin, wireId)`
- `inputWire(pin)` / `outputWire(pin)`

---

### Gates/AndGate.h — XorGate.h
One file per gate. Header only, no .cpp needed.
All inherit directly from Gate.

Each gate implements only:
- Constructor — calls Gate with correct input/output pin counts
- `evaluate(inputs, outputs)` — computes boolean result, returns true if output changed
- `name()` — returns string label

No state. No members beyond what Gate provides.

---

### Gates/TriStateBuffer.h
Inherits from Gate. Single input, single output, single enable pin.

**Pins**
- Input  0 — data in
- Input  1 — enable
- Output 0 — data out (HighZ when enable is Low)

**Key behaviour**
- `evaluate()` — if enable High pass data through, if enable Low output HighZ
- `supportsBus()` — returns true, passes full uint32_t value when enabled

---

### Gates/Mux.h
Inherits from Gate. N data inputs + select lines + 1 output.

**Key behaviour**
- `evaluate()` — reads select lines as binary index, routes that input to output
- `supportsBus()` — returns true, selected input bus value passed to output
- Constructor takes inputCount and selectionBits separately

---

### Gates/Demux.h
Inherits from Gate. 1 data input + select lines + N outputs.

**Key behaviour**
- `evaluate()` — reads select lines, routes input to selected output, others go Low
- `supportsBus()` — returns true

---

### Sequential/DFlipFlop.h / .cpp
Inherits from Gate. Stateful.

**Members**
- `m_currentQ` — the live Q output
- `m_nextQ` — computed during phase 1, applied during phase 2

**Key methods**
- `evaluateNext(inputs)` — samples D input, stores in m_nextQ. Does not change output.
- `commit(outputs)` — applies m_nextQ to m_currentQ, updates Q and Q' outputs. Returns true if changed.
- `isSequential()` — returns true
- `evaluate()` — does nothing, sequential gates skip this

Same pattern applies to SRFlipFlop and JKFlipFlop with their respective logic.

---

### Sequential/ClockDivider.h / .cpp
Inherits from Gate. Stateful. Sequential.

**Members**
- `m_divideBy` — integer divisor, set at construction
- `m_counter` — internal tick counter
- `m_currentOut` — current output state, toggles when counter wraps

**Key methods**
- `evaluateNext()` — increments counter, computes whether output toggles this tick
- `commit(outputs)` — applies toggle if due, returns true if output changed
- `isSequential()` — returns true

---

### Nodes/InputNode.h / OutputNode.h / ClockNode.h / ConstantNode.h
Lightweight signal sources and sinks. Inherit from Node base, not Gate — they have no logic.

- `InputNode` — one output wire. Engine::setInput() drives it. Supports bus width.
- `OutputNode` — one input wire. Purely observational, engine reads its value for display.
- `ClockNode` — one output wire. Driven by ClockDomain on each tick, not by user.
- `ConstantNode` — one output wire. Value fixed at construction. Never changes.

---

### Nodes/BusSplitter.h / .cpp
One input bus of width N → N individual single-bit output wires.

**Key behaviour**
- Width set at construction
- `evaluate()` — reads bus input, drives each output wire with its corresponding bit
- Output pin count equals bus width

---

### Nodes/BusMerger.h / .cpp
N individual single-bit input wires → one output bus of width N.

**Key behaviour**
- Width set at construction
- `evaluate()` — reads all single-bit inputs, assembles into a uint32_t bus value
- Input pin count equals bus width

---

### Nodes/ProbeNode.h / .cpp
Sits on a wire and records its value over time. Zero effect on simulation.

**Members**
- `m_wireId` — the wire being observed
- `m_label` — user assigned name

**Key behaviour**
- Does not participate in propagation at all
- EventLog queries all ProbeNodes after each tick and records their wire values
- UI reads probe history to render waveform / timing diagram

---

### Nodes/NumberDisplay.h / .cpp
Reads a bus wire and exposes its integer value. Output only, no logic effect.

**Members**
- `m_inputWire` — connected bus wire
- `m_base` — display base: Binary, Octal, Decimal, Hex

**Key methods**
- `readValue()` — returns the uint32_t value of the connected bus wire
- Engine exposes this to UI so it can render the numeric value as a string

---

### Nodes/SevenSegDisplay.h / .cpp
Reads a bus and exposes individual segment states. Output only.

**Members**
- `m_inputWire` — connected bus wire (7-bit for direct segment drive, or 4-bit for BCD)
- `m_mode` — DirectSegment or BCD
- `m_segments[7]` — current on/off state per segment (A B C D E F G)

**Key behaviour**
- `evaluate()` — unpacks bus value into segment states based on mode
- UI reads m_segments array to render the seven segment visual
- BCD mode has internal decode table mapping 0-9 to correct segment patterns

---

### Circuit/Circuit.h / .cpp
Central ownership class. The only place gates, nodes, and wires are created and destroyed.

**Members**
- `m_gates` — unordered_map of NodeId → unique_ptr<Gate>
- `m_nodes` — unordered_map of NodeId → unique_ptr<Node>
- `m_wires` — unordered_map of WireId → Wire
- `m_outputStates` — unordered_map of NodeId → vector<SignalState>
- `m_nextNodeId`, `m_nextWireId` — ID counters

**Key methods**
- `addGate(unique_ptr<Gate>)` — takes ownership, returns NodeId
- `addNode(unique_ptr<Node>)` — takes ownership, returns NodeId
- `removeGate(NodeId)` — deletes gate and all connected wires, returns removed WireIds
- `connect(fromNode, fromPin, toNode, toPin, width)` — validates width compatibility, creates Wire, registers on both endpoints, returns WireId
- `disconnect(WireId)` — removes wire, unregisters from both endpoints
- `resolveInputs(NodeId)` — reads all input wire values for a gate, handles Floating/HighZ/Error
- `resolveBusConflict(WireId)` — called when multiple drivers share one wire, applies resolution rules
- `sequentialGates()` — returns NodeIds of all sequential elements
- `gate(NodeId)`, `wire(WireId)`, `node(NodeId)` — non-owning access

---

### Circuit/CustomBlock.h / .cpp
Represents a user-defined reusable block.

**Members**
- `m_definition` — the internal SubCircuit, always kept as source of truth
- `m_lut` — optional precomputed truth table, nullptr if not eligible
- `m_strategy` — LUT or Structural
- `m_instances` — list of NodeIds using this definition

**Key methods**
- `evaluate(inputs)` — dispatches to LUT lookup or structural propagation
- `onDefinitionChanged()` — invalidates LUT, recomputes strategy, marks all instances dirty
- `chooseStrategy()` — LUT if inputCount <= 8 AND no sequential logic AND no buses, else Structural
- `generateLUT()` — runs all 2^n input combinations through definition circuit, caches results

---

### Simulation/Propagator.h / .cpp
Event-driven BFS across combinational logic and nodes.

**Members**
- `m_circuit` — reference to Circuit
- `m_queue` — queue of NodeIds pending evaluation
- `m_loopDetected` — set true if iteration cap is hit

**Key methods**
- `enqueue(NodeId)` — adds gate or node to propagation queue
- `propagate(changeSet)` — drains queue, evaluates gates, resolves bus conflicts, updates wire values, enqueues downstream. Stops and warns if MAX_ITERATIONS hit.
- `driveInput(NodeId, uint32_t value, int width, changeSet)` — sets input node output wire and calls propagate
- `evaluateGate(NodeId, changeSet)` — internal. Resolves inputs, calls evaluate(), writes outputs, enqueues downstream.

Skips sequential gates entirely. Those are handled by ClockDomain.

---

### Simulation/ClockDomain.h / .cpp
Manages the two-phase tick for all sequential logic.

**Members**
- `m_circuit` — reference
- `m_propagator` — reference
- `m_tickCount` — running count of clock cycles
- `m_mode` — Running or Paused

**Key methods**
- `tick(changeSet)` — runs the full three phase cycle:
  - Phase 1: calls `evaluateNext()` on all sequential gates (sample only, no output change yet)
  - Phase 2: calls `commit()` on all sequential gates (apply state, update wires, enqueue downstream)
  - Phase 3: calls `propagator.propagate()` to settle combinational logic
- `reset()` — returns all sequential elements to initial state, re-propagates

---

### Simulation/EventLog.h / .cpp
Ring buffer recording wire state changes over time. Powers the waveform / timing diagram.

**Members**
- `m_entries` — ring buffer of { tickCount, WireId, uint32_t value, SignalState }
- `m_capacity` — max entries before oldest are overwritten
- `m_probes` — list of ProbeNode IDs to snapshot each tick

**Key methods**
- `record(tickCount, wireId, value, state)` — appends one entry
- `snapshotProbes(circuit, tickCount)` — called after every tick, records all probe wire values
- `queryWire(WireId, fromTick, toTick)` — returns value history for a wire, used by UI for waveform
- `clear()` — wipes all history

---

### Simulation/CommandHistory.h / .cpp
Undo / redo stack. All structural changes go through here.

**Members**
- `m_undoStack` — vector of unique_ptr<Command>
- `m_redoStack` — cleared whenever a new command is executed

**Key methods**
- `execute(unique_ptr<Command>)` — runs command, pushes to undo stack, clears redo stack
- `undo()` — pops undo stack, calls command undo(), pushes to redo stack
- `redo()` — pops redo stack, re-executes, pushes back to undo stack
- `canUndo()`, `canRedo()` — UI uses these to enable / disable buttons

**Command base**
- `execute()` — pure virtual
- `undo()` — pure virtual
- Each concrete command stores everything needed to reverse itself

---

### Simulation/Engine.h / .cpp
The single public interface. The only file Qt ever includes.

**Members**
- `m_circuit`, `m_propagator`, `m_clockDomain`, `m_eventLog`, `m_commandHistory` — all owned
- `m_changeCallback` — registered by UI

**Key methods**
- `addGate(GateType, inputCount)` — wrapped in command, fires ChangeSet
- `removeGate(NodeId)` — wrapped in command, fires ChangeSet
- `addNode(NodeType, ...)` — wrapped in command, fires ChangeSet
- `connect(fromNode, fromPin, toNode, toPin, width)` — validates width, wrapped in command, fires ChangeSet
- `disconnect(WireId)` — wrapped in command, fires ChangeSet
- `setInput(NodeId, uint32_t value, int width)` — drives input node, fires ChangeSet
- `tick()` — delegates to ClockDomain, snapshots EventLog probes, fires ChangeSet
- `undo()` / `redo()` — delegates to CommandHistory, fires ChangeSet
- `reset()` — resets all sequential state, re-propagates, fires ChangeSet
- `getWireValue(WireId)` — returns uint32_t value
- `getWireState(WireId)` — returns SignalState for UI wire coloring
- `getDisplayValue(NodeId)` — reads NumberDisplay or SevenSeg value for UI
- `getEventLog()` — UI accesses for waveform rendering
- `setChangeCallback(fn)` — UI registers here once
- `printState()` — debug dump to stdout, no Qt involved

---

## Data Flow Summary

```
User changes input
    Engine::setInput()
        CommandHistory::execute(SetInputCommand)
        Propagator::driveInput()
            sets wire value + state
            enqueues downstream gate
        Propagator::propagate()
            evaluates gates in BFS order
            resolves bus conflicts
            updates wire values and SignalState
            fills ChangeSet::changedWires
    Engine fires ChangeCallback with ChangeSet
    UI recolors wires  (green=High  grey=Low  red=Error  dim=HighZ)

Clock tick
    Engine::tick()
        ClockDomain::tick()
            Phase 1 — all sequential gates sample inputs
            Phase 2 — all sequential gates commit, enqueue downstream
            Phase 3 — Propagator settles combinational logic
            fills ChangeSet::changedWires + clockTicked
        EventLog::snapshotProbes()
    Engine fires ChangeCallback with ChangeSet
    UI recolors wires, updates waveform display, animates FF transition

Undo
    Engine::undo()
        CommandHistory::undo()
            command.undo() reverses structural change in Circuit
        Propagator re-propagates
        fills ChangeSet
    Engine fires ChangeCallback
    UI rebuilds affected scene items
```

---

## Wire Width Rules

- Width is set at `connect()` time and is immutable for that wire
- Single bit wire: `width = 1`, value uses bit 0 only
- Bus wire: `width = 2..32`, value uses all relevant bits
- Connecting wires of mismatched width is a hard error — Circuit rejects it at connect time
- BusSplitter and BusMerger are the only legal way to cross width boundaries
- TriStateBuffer, Mux, Demux all preserve the width of their data path

---

## SignalState Bus Resolution Rules

```
All drivers HighZ                  → Floating
One driver High, rest HighZ        → High
One driver Low,  rest HighZ        → Low
High + Low (any combination)       → Error  (bus conflict)
Any Floating driver on a shared bus → treated as HighZ for resolution purposes
```

---

## Rules That Must Never Break

- Gate and Node never include a Qt header
- Engine never exposes Circuit, Gate, Wire, or Node types in its public interface
- UI holds only NodeId and WireId — never raw pointers into engine memory
- Circuit is the sole owner of all gates, nodes, and wires
- Sequential gates never participate in propagation — only in tick
- Propagation always runs to completion before the next tick or input change
- All structural changes go through CommandHistory — nothing mutates Circuit directly from UI
- Wire width is validated at connection time and never assumed downstream
