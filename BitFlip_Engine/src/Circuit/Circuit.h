#pragma once

#include "Core/Types.h"
#include "Core/Wire.h"
#include "Core/Gate.h"
#include <unordered_map>
#include <memory>
#include <vector>

// ─────────────────────────────────────────────────────────────────────────────
// Circuit
// Single source of truth. Owns all gates and wires.
// Nothing outside Circuit holds owning pointers — only IDs.
// ─────────────────────────────────────────────────────────────────────────────

class Circuit {
public:
    Circuit()  = default;
    ~Circuit() = default;

    Circuit(const Circuit&)            = delete;
    Circuit& operator=(const Circuit&) = delete;

    // ── Gate management ───────────────────────────────────────────────────────
    GateId              addGate(std::unique_ptr<Gate> gate);
    std::vector<WireId> removeGate(GateId id);

    Gate*       gate(GateId id);
    const Gate* gate(GateId id) const;
    bool        hasGate(GateId id) const;

    std::vector<GateId> allGateIds()      const;
    std::vector<GateId> sequentialGates() const;

    // ── Wire management ───────────────────────────────────────────────────────
    WireId connect(GateId fromGate, int fromPin, GateId toGate, int toPin, int width = 1);
    void   disconnect(WireId id);

    Wire*       wire(WireId id);
    const Wire* wire(WireId id) const;
    bool        hasWire(WireId id) const;

    std::vector<WireId> allWireIds() const;

    // ── Signal access ─────────────────────────────────────────────────────────
    void        setWireValue(WireId id, uint32_t value, SignalState state);
    uint32_t    getWireValue(WireId id) const;
    SignalState getWireState(WireId id) const;

    std::vector<SignalState> resolveInputs  (GateId id) const;
    std::vector<SignalState> currentOutputs (GateId id) const;
    void                    setOutputs      (GateId id, const std::vector<SignalState>& outputs);

    // ── Stats ─────────────────────────────────────────────────────────────────
    size_t gateCount() const { return m_gates.size(); }
    size_t wireCount() const { return m_wires.size(); }

private:
    std::unordered_map<GateId, std::unique_ptr<Gate>>      m_gates;
    std::unordered_map<WireId, Wire>                        m_wires;
    std::unordered_map<GateId, std::vector<SignalState>>    m_outputStates;

    GateId m_nextGateId { static_cast<GateId>(1) };
    WireId m_nextWireId { static_cast<WireId>(1) };

    GateId allocGateId();
    WireId allocWireId();
};