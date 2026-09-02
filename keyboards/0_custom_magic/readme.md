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
Hold both Shift keys simultaneously to toggle between `_BASE` (ergonomic) and `_QWERTY`. The combo works with either:

- the tap-dance Shift pair on `_BASE` / `_FN` (`TD_LSFT` + `TD_RSFT`)
- the plain Shift pair on `_QWERTY` (`KC_LSFT` + `KC_RSFT`)

Each toggle also sends **Win+Space** to switch the OS IME in sync with the selected layout. A layer-indicator LED (GP17) turns on while `_QWERTY` is active.

### QWERTY suspension
While `_QWERTY` is selected, only the following keys temporarily reveal `_BASE` for the duration of the hold:

- `KC_LCTL`
- `KC_LALT`
- `TEMP_EN`
- the tap-dance Ctrl / Alt keys when they are reached through `_FN` or the revealed `_BASE`

This keeps Ctrl/Alt shortcuts on the same physical keys as `_BASE` while typing on `_QWERTY`.

`MO(_FN)` does **not** suspend `_QWERTY` by itself, and Shift keys never reveal `_BASE`.

### Tap-dance modifiers
Four modifier keys use tap-dance for extended gestures when `_BASE` is the selected layout:

| Key | Single tap | Single hold | Double tap | Double hold |
|-----|-----------|-------------|------------|-------------|
| `TD_LSFT` | Send `LSFT` | Hold `LSFT` | Send `LSFT` twice | Hold `LALT`+`LSFT` |
| `TD_RSFT` | Send `RSFT` | Hold `RSFT` | Send `RSFT` twice | Hold `LALT`+`RSFT` |
| `TD_LALT` | Send `LALT` | Hold `LALT` | Send `LALT` twice | Hold `LALT`+`RCTL` |
| `TD_RCTL` | Send `RCTL` | Hold `RCTL` | Send `RCTL` twice | Hold `RSFT`+`RCTL` |

When `_QWERTY` is selected, tap dance is bypassed for these keys: they behave as immediate plain modifiers instead. The Ctrl / Alt variants still temporarily reveal `_BASE` for shortcuts; the Shift variants remain plain Shift.

### TEMP_EN (temporary English IME)
Available as the innermost key on the right half of row 5 (the Z/N row, second-to-last row) in `_QWERTY`. On press it sends **Win+Space** to ask the OS to switch the IME to English, then reveals `_BASE` (ergonomic English layout) for the duration of the hold. On release it restores `_QWERTY` and sends **Win+Space** again to revert the IME.

### Arrow string macros
Two keys on the `_FN` layer send multi-character arrow strings:

| Key | Output |
|-----|--------|
| `FN` + `I` | `=>` (fat arrow) |
| `FN` + `N` | `->` (thin arrow) |

### Tap-dance toggle
The `_FN` layer includes a dedicated toggle key that switches the custom tap-dance modifier behavior on or off. When disabled, the modifier keys on `_BASE` act like plain held/tapped modifiers instead of the custom combo gestures. On `_QWERTY`, these keys are already forced to behave as plain modifiers.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
