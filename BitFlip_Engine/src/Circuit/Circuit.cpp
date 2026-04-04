#include "Circuit.h"
#include <stdexcept>

// ── ID allocation ─────────────────────────────────────────────────────────────

GateId Circuit::allocGateId() {
    auto id = m_nextGateId;
    m_nextGateId = static_cast<GateId>(static_cast<uint32_t>(m_nextGateId) + 1);
    return id;
}

WireId Circuit::allocWireId() {
    auto id = m_nextWireId;
    m_nextWireId = static_cast<WireId>(static_cast<uint32_t>(m_nextWireId) + 1);
    return id;
}

// ── Gate management ───────────────────────────────────────────────────────────

GateId Circuit::addGate(std::unique_ptr<Gate> gate) {
    // TODO — allocate ID, store gate, init output states, return ID
}

std::vector<WireId> Circuit::removeGate(GateId id) {
    // TODO — find gate, disconnect all its wires, erase gate, return removed wire IDs
}

Gate* Circuit::gate(GateId id) {
    // TODO
}

const Gate* Circuit::gate(GateId id) const {
    // TODO
}

bool Circuit::hasGate(GateId id) const {
    // TODO
}

std::vector<GateId> Circuit::allGateIds() const {
    // TODO
}

std::vector<GateId> Circuit::sequentialGates() const {
    // TODO — return IDs where gate->isSequential() == true
}

// ── Wire management ───────────────────────────────────────────────────────────

WireId Circuit::connect(GateId fromGate, int fromPin, GateId toGate, int toPin, int width) {
    // TODO — validate both gates exist, allocate wire, register on both endpoints, return ID
}

void Circuit::disconnect(WireId id) {
    // TODO — find wire, unregister from both endpoints, erase wire
}

Wire* Circuit::wire(WireId id) {
    // TODO
}

const Wire* Circuit::wire(WireId id) const {
    // TODO
}

bool Circuit::hasWire(WireId id) const {
    // TODO
}

std::vector<WireId> Circuit::allWireIds() const {
    // TODO
}

// ── Signal access ─────────────────────────────────────────────────────────────

void Circuit::setWireValue(WireId id, uint32_t value, SignalState state) {
    // TODO
}

uint32_t Circuit::getWireValue(WireId id) const {
    // TODO
}

SignalState Circuit::getWireState(WireId id) const {
    // TODO
}

std::vector<SignalState> Circuit::resolveInputs(GateId id) const {
    // TODO — for each input pin, read connected wire state
    // return Floating for unconnected pins
}

std::vector<SignalState> Circuit::currentOutputs(GateId id) const {
    // TODO — return m_outputStates[id]
}

void Circuit::setOutputs(GateId id, const std::vector<SignalState>& outputs) {
    // TODO — write to m_outputStates[id]
}