#pragma once

#include <functional>
#include <iostream>
#include <stdint.h>
#include <vector>

// ── ID Types ──────────────────────────────────────────────────────────────────

enum class GateId : uint32_t { Invalid = 0 };
enum class WireId : uint32_t { Invalid = 0 };
enum class NodeId : uint32_t { Invalid = 0 };
enum class BlockDefId : uint32_t { Invalid = 0 };

// ── Gate Types
// ────────────────────────────────────────────────────────────────
enum class GateType {
  NOT,
  AND,
  OR,
  XOR,
  NAND,
  NOR,
  XNOR,
  MUX,
  DEMUX,
  TRI_STATE_BUFFER
};

// ── Node Types ────────────────────────────────────────────────────────────────
enum class NodeType {
  INPUT,
  OUTPUT,
  CLOCK,
  CONSTANT,
  BUS_SPLITTER,
  BUS_MERGER,
  PROBE,
  NUMBER_DISPLAY,
  SEVEN_SEG
};

// ── Signal State ──────────────────────────────────────────────────────────────
enum class SignalState : uint8_t {
  Low = 0,
  High = 1,
  Floating = 2, // unconnected input
  HighZ = 3,    // tri-state buffer when disabled
  Error = 4     // bus conflict
};

// ── Helpers ───────────────────────────────────────────────────────────────────
inline bool toLogic(SignalState s) { return s == SignalState::High; }
inline SignalState fromLogic(bool v) {
  return v ? SignalState::High : SignalState::Low;
}

// ── ChangeSet ─────────────────────────────────────────────────────────────────
struct ChangeSet {
  std::vector<GateId> addedGates;
  std::vector<GateId> removedGates;
  std::vector<NodeId> addedNodes;
  std::vector<NodeId> removedNodes;
  std::vector<WireId> addedWires;
  std::vector<WireId> removedWires;
  std::vector<WireId> changedWires;
  bool clockTicked = false;

  bool empty() const {
    return addedGates.empty() && removedGates.empty() && addedNodes.empty() &&
           removedNodes.empty() && addedWires.empty() && removedWires.empty() &&
           changedWires.empty() && !clockTicked;
  }

  void clear() {
    addedGates.clear();
    removedGates.clear();
    addedNodes.clear();
    removedNodes.clear();
    addedWires.clear();
    removedWires.clear();
    changedWires.clear();
    clockTicked = false;
  }
};

using ChangeCallback = std::function<void(const ChangeSet &)>;
