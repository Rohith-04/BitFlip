#pragma once

#include "Types.h"
#include <vector>
#include <string>

// ─────────────────────────────────────────────────────────────────────────────
// Gate (Abstract Base)
// All logic gates inherit from this.
// No Qt. No rendering. No position. Pure logic only.
//
// Combinational gates implement evaluate().
// Sequential gates implement evaluateNext() + commit() instead.
// ─────────────────────────────────────────────────────────────────────────────

class Gate {
public:
    Gate(GateId id, GateType type, int inputCount, int outputCount);
    virtual ~Gate() = default;

    Gate(const Gate&)            = delete;
    Gate& operator=(const Gate&) = delete;
    Gate(Gate&&)                 = default;
    Gate& operator=(Gate&&)      = default;

    // ── Identity ──────────────────────────────────────────────────────────────
    GateId   id()          const { return m_id;   }
    GateType type()        const { return m_type; }
    int      inputCount()  const { return static_cast<int>(m_inputWires.size());  }
    int      outputCount() const { return static_cast<int>(m_outputWires.size()); }

    // ── Wire connectivity ─────────────────────────────────────────────────────
    void   connectInput  (int pin, WireId wire);
    void   connectOutput (int pin, WireId wire);
    void   disconnectInput  (int pin);
    void   disconnectOutput (int pin);
    WireId inputWire  (int pin) const;
    WireId outputWire (int pin) const;
    const std::vector<WireId>& allInputWires()  const { return m_inputWires;  }
    const std::vector<WireId>& allOutputWires() const { return m_outputWires; }

    // ── Evaluation ────────────────────────────────────────────────────────────
    // Combinational — returns true if output changed
    virtual bool evaluate(const std::vector<SignalState>& inputs,
                          std::vector<SignalState>&       outputs) = 0;

    // Sequential — two phase
    virtual void evaluateNext(const std::vector<SignalState>& inputs) {}
    virtual bool commit(std::vector<SignalState>& outputs) { return false; }

    virtual bool isSequential() const { return false; }
    virtual bool supportsBus()  const { return false; }

    virtual std::string name() const = 0;

protected:
    GateId               m_id;
    GateType             m_type;
    std::vector<WireId>  m_inputWires;
    std::vector<WireId>  m_outputWires;
};