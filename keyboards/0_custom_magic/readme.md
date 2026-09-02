# 0_custom (first)

*A custom 6×16 ergonomic keyboard with dual-layout hot-switching, tap-dance modifiers, and an IME toggle key.*

* Keyboard Maintainer: [s. galiamov](https://github.com/sgaliamov)
* Hardware Supported: Pro Micro RP2040, hand-wired 6×16 matrix (96 keys)
* Hardware Availability: Hand-wired / custom build

Make example for this keyboard (after setting up your build environment):

    make 0_custom_magic:default

Flashing example for this keyboard:

    make 0_custom_magic:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Layers

| # | Name | Description |
|---|------|-------------|
| 0 | `_BASE` | Ergonomic default layout |
| 1 | `_QWERTY` | Standard QWERTY layout |
| 2 | `_FN` | Function / numpad / media layer (accessed via `MO(_FN)`) |

## Behavior

### Dual-layout hot-switching
Hold both Shift keys simultaneously (`KC_LSFT` + `TD_RSFT`) to toggle between `_BASE` (ergonomic) and `_QWERTY`. Each toggle also sends **Win+Space** to switch the OS IME in sync with the active layout. A layer-indicator LED (GP17) turns on while `_QWERTY` is active.

### QWERTY suspension
While `_QWERTY` is active, holding `MO(_FN)` or any tap-dance modifier **temporarily suspends** `_QWERTY` (reverts to `_BASE`) so that shortcuts and function keys resolve to ergonomic key positions. The layer is restored automatically when all holding keys are released. Multiple simultaneous holders are tracked with a reference counter so the last one to release triggers the restore.

### Tap-dance modifiers
Three modifier keys on the right-hand side use tap-dance for extended gestures:

| Key | Single tap | Single hold | Double tap | Double hold |
|-----|-----------|-------------|------------|-------------|
| `TD_RSFT` | Send `RSFT` | Hold `RSFT` | Send `RSFT` twice | Hold `LALT`+`RSFT` |
| `TD_LALT` | Send `LALT` | Hold `LALT` | Send `LALT` twice | Hold `LALT`+`RCTL` |
| `TD_RCTL` | Send `RCTL` | Hold `RCTL` | Send `RCTL` twice | Hold `RSFT`+`RCTL` |

All hold gestures also trigger QWERTY suspension (see above).

### TEMP_EN (temporary English IME)
Available as the innermost key on the right half of row 5 (the Z/N row, second-to-last row) in `_QWERTY`. On press it sends **Win+Space** to ask the OS to switch the IME to English, then suspends `_QWERTY` so `_BASE` (ergonomic English layout) is active for the duration of the hold. On release it restores `_QWERTY` and sends **Win+Space** again to revert the IME. Shift is intentionally *not* suspended by this key so that capitalised characters still work correctly for the active language.

### Arrow string macros
Two keys on the `_FN` layer send multi-character arrow strings:

| Key | Output |
|-----|--------|
| `FN` + `I` | `=>` (fat arrow) |
| `FN` + `N` | `->` (thin arrow) |

### Tap-dance toggle
The `_FN` layer includes a dedicated toggle key that switches the custom tap-dance modifier behavior on or off. When disabled, the modifier keys act like plain held/tapped modifiers instead of the custom combo gestures.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
