#include "Propagator.h"
#include <iostream>

void Propagator::enqueue(GateId id) {
    // TODO — push to m_queue
}

void Propagator::driveInput(GateId inputGate, uint32_t value, int width, ChangeSet& changeSet) {
    // TODO
    // 1. get the output wire of inputGate
    // 2. if value unchanged, return early
    // 3. set wire value + state
    // 4. push changeSet.changedWires
    // 5. enqueue the gate on the other end of the wire
    // 6. call propagate()
}

void Propagator::propagate(ChangeSet& changeSet) {
    m_loopDetected = false;
    int iterations = 0;

    while (!m_queue.empty()) {
        if (++iterations > MAX_ITERATIONS) {
            m_loopDetected = true;
            std::cerr << "[Propagator] WARNING: combinational loop detected\n";
            while (!m_queue.empty()) m_queue.pop();
            break;
        }

        GateId id = m_queue.front();
        m_queue.pop();
        evaluateGate(id, changeSet);
    }
}

void Propagator::evaluateGate(GateId id, ChangeSet& changeSet) {
    // TODO
    // 1. get gate, skip if sequential
    // 2. resolveInputs from circuit
    // 3. get currentOutputs from circuit
    // 4. call gate->evaluate(inputs, outputs)
    // 5. if changed: write new outputs to wires, push changedWires, enqueue downstream gates
}