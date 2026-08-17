# 0_custom (first)

*A custom 6×16 ergonomic keyboard with function, numpad, media, and text-macro keys.*

* Keyboard Maintainer: [s. galiamov](https://github.com/sgaliamov)
* Hardware Supported: Pro Micro RP2040, hand-wired 6×16 matrix (96 keys)
* Hardware Availability: Hand-wired / custom build

Make example for this keyboard (after setting up your build environment):

    make 0_custom_qwerty:default

Flashing example for this keyboard:

    make 0_custom_qwerty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Layers

| # | Name | Description |
|---|------|-------------|
| 0 | `_BASE` | Ergonomic default layout |
| 1 | `_FN` | Function / numpad / media layer (accessed via `MO(_FN)`) |

## Behavior

### Arrow string macros
Two keys on the `_FN` layer send multi-character arrow strings:

| Key | Output |
|-----|--------|
| `ARROW_FAT` | `=>` (fat arrow) |
| `ARROW_THIN` | `->` (thin arrow) |

### Swapped quote key

`QUOT_SWAP` sends `"` without Shift and `'` with Shift.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
