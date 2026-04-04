#pragma once

#include "Core/Types.h"
#include "Circuit/Circuit.h"
#include <queue>

// ─────────────────────────────────────────────────────────────────────────────
// Propagator
// Event-driven BFS propagation across combinational logic.
// Skips sequential gates entirely — ClockDomain handles those.
// ─────────────────────────────────────────────────────────────────────────────

class Propagator {
public:
    static constexpr int MAX_ITERATIONS = 100'000;

    explicit Propagator(Circuit& circuit) : m_circuit(circuit) {}

    // Enqueue a gate for re-evaluation
    void enqueue(GateId id);

    // Run BFS until stable or loop detected
    void propagate(ChangeSet& changeSet);

    // Drive an input gate to a value and propagate
    void driveInput(GateId inputGate, uint32_t value, int width, ChangeSet& changeSet);

    bool hadLoop() const { return m_loopDetected; }

private:
    Circuit&           m_circuit;
    std::queue<GateId> m_queue;
    bool               m_loopDetected = false;

    void evaluateGate(GateId id, ChangeSet& changeSet);
};