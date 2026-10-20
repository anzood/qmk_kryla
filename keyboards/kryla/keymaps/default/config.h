// Copyright 2026 Anzood
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Timings follow the ZMK config (lintilla-zmk)
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 200
#define QUICK_TAP_TERM_PER_KEY
// ZMK "hold-preferred" for mt/lt/hyp; smod keys opt out (tap-preferred)
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Sticky mods are forgotten after 1.5 s
#define ONESHOT_TIMEOUT 1500

#define OLED_TIMEOUT 60000
