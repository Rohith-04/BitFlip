#include "Gate.h"
#include <stdexcept>

Gate::Gate(GateId id, GateType type, int inputCount, int outputCount)
    : m_id(id)
    , m_type(type)
    , m_inputWires(inputCount,  WireId::Invalid)
    , m_outputWires(outputCount, WireId::Invalid)
{}

void Gate::connectInput(int pin, WireId wire) {
    // TODO — validate pin range, set m_inputWires[pin]
}

void Gate::connectOutput(int pin, WireId wire) {
    // TODO — validate pin range, set m_outputWires[pin]
}

void Gate::disconnectInput(int pin) {
    // TODO — validate pin range, set m_inputWires[pin] = WireId::Invalid
}

void Gate::disconnectOutput(int pin) {
    // TODO — validate pin range, set m_outputWires[pin] = WireId::Invalid
}

WireId Gate::inputWire(int pin) const {
    // TODO — validate pin range, return m_inputWires[pin]
}

WireId Gate::outputWire(int pin) const {
    // TODO — validate pin range, return m_outputWires[pin]
}