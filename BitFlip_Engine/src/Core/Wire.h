#pragma once

#include "Types.h"

// ─────────────────────────────────────────────────────────────────────────────
// Wire
// Directed signal carrier between one output pin and one input pin.
// Supports both single bit (width=1) and bus (width>1) signals.
// Circuit owns all Wire instances. Gates hold only WireIds.
// ─────────────────────────────────────────────────────────────────────────────

struct Wire {
    WireId      id       = WireId::Invalid;
    uint32_t    value    = 0;                   // bit 0 for single, all bits for bus
    int         width    = 1;                   // 1 = single bit, >1 = bus
    SignalState state    = SignalState::Floating;
    bool        dirty    = false;

    // Endpoints — IDs only, no raw pointers
    GateId  fromGate = GateId::Invalid;
    int     fromPin  = -1;
    GateId  toGate   = GateId::Invalid;
    int     toPin    = -1;

    // ── Helpers ───────────────────────────────────────────────────────────────
    bool isConnected() const;
    bool isHigh()      const;
    bool isBus()       const;
    bool getBit(int n) const;
};