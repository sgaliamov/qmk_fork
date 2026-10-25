// Copyright 2026 s. galiamov (@sgaliamov)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// PWM slice 0 drives GP17 (channel B) for the layer-indicator LED.
#undef RP_PWM_USE_PWM0
#define RP_PWM_USE_PWM0 TRUE
