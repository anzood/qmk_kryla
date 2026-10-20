# Kryla

Monoblock split keyboard with 42 keys based on Lintilla.

Revision 1 is hand-wired: YD-RP2040, USB, OLED 0.96″ 128 × 64 (SSD1306,
I²C). Matrix and pins: `docs/rev1-wiring.md` in the Kryla project.

- Matrix: 4 rows × 12 columns, `COL2ROW`.
- Keymap: port of the ZMK Lintilla keymap, fn keys moved to the thumbs.

Make example (after copying `keyboards/kryla` into `qmk_firmware`):

```bash
qmk compile -kb kryla/rev1 -km default
```

## Status LEDs

The on-board WS2812 (GP23) shows the keyboard state, highest priority
first:

| State | LED |
| --- | --- |
| Entering the bootloader with `QK_BOOT` | white |
| App or window switcher holds Cmd/Opt | blinks green |
| Sticky modifier is pending | blinks the layer color, white on DEFAULT |
| Layer other than DEFAULT | steady layer color |
| DEFAULT layer, or idle for a minute | off |

Layer colors: SYMBOLS yellow, NAV blue, NUMBERS green, FN KEYS purple,
ADJUST red. The blue LED (GP25) shows Caps Lock and blinks while the
double press of RST waits.

## Bootloader

- Double press RST on the YD-RP2040 (or hold BOOT while plugging in).
- Hold the left outer home key while plugging in (Bootmagic).
- `QK_BOOT` on the fn thumb keys in the ADJUST layer.
