#pragma once

#include "Core/Gate.h"

// ─────────────────────────────────────────────────────────────────────────────
// AND Gate
// ─────────────────────────────────────────────────────────────────────────────
class AndGate final : public Gate {
public:
    explicit AndGate(GateId id, int inputCount = 2)
        : Gate(id, GateType::AND, inputCount, 1) {}

    bool evaluate(const std::vector<SignalState>& inputs,
                  std::vector<SignalState>&       outputs) override;

    std::string name() const override { return "AND"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// OR Gate
// ─────────────────────────────────────────────────────────────────────────────
class OrGate final : public Gate {
public:
    explicit OrGate(GateId id, int inputCount = 2)
        : Gate(id, GateType::OR, inputCount, 1) {}

    bool evaluate(const std::vector<SignalState>& inputs,
                  std::vector<SignalState>&       outputs) override;

    std::string name() const override { return "OR"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// NOT Gate
// ─────────────────────────────────────────────────────────────────────────────
class NotGate final : public Gate {
public:
    explicit NotGate(GateId id)
        : Gate(id, GateType::NOT, 1, 1) {}

    bool evaluate(const std::vector<SignalState>& inputs,
                  std::vector<SignalState>&       outputs) override;

    std::string name() const override { return "NOT"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// NAND Gate
// ─────────────────────────────────────────────────────────────────────────────
class NandGate final : public Gate {
public:
    explicit NandGate(GateId id, int inputCount = 2)
        : Gate(id, GateType::NAND, inputCount, 1) {}

    bool evaluate(const std::vector<SignalState>& inputs,
                  std::vector<SignalState>&       outputs) override;

    std::string name() const override { return "NAND"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// NOR Gate
// ─────────────────────────────────────────────────────────────────────────────
class NorGate final : public Gate {
public:
    explicit NorGate(GateId id, int inputCount = 2)
        : Gate(id, GateType::NOR, inputCount, 1) {}

    bool evaluate(const std::vector<SignalState>& inputs,
                  std::vector<SignalState>&       outputs) override;

    std::string name() const override { return "NOR"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// XOR Gate
// ─────────────────────────────────────────────────────────────────────────────
class XorGate final : public Gate {
public:
    explicit XorGate(GateId id, int inputCount = 2)
        : Gate(id, GateType::XOR, inputCount, 1) {}

    bool evaluate(const std::vector<SignalState>& inputs,
                  std::vector<SignalState>&       outputs) override;

    std::string name() const override { return "XOR"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// XNOR Gate
// ─────────────────────────────────────────────────────────────────────────────
class XnorGate final : public Gate {
public:
    explicit XnorGate(GateId id, int inputCount = 2)
        : Gate(id, GateType::XNOR, inputCount, 1) {}

    bool evaluate(const std::vector<SignalState>& inputs,
                  std::vector<SignalState>&       outputs) override;

    std::string name() const override { return "XNOR"; }
};