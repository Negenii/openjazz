
/**
 *
 * @file openfpga.h
 *
 * Part of the OpenJazz project
 *
 * @par Licence:
 * Copyright (c) 2026 OpenJazz contributors
 *
 * OpenJazz is distributed under the terms of
 * the GNU General Public License, version 2.0
 *
 */


#ifndef _OPENFPGA_H
#define _OPENFPGA_H

#include "platform_interface.h"

#ifdef OPENFPGA

/* openfpgaOS: bare-metal RISC-V runtime on Analogue Pocket / MiSTer.
   Device uses SDL2 via the SDK's compatibility shim. */

// Audio config
#define SOUND_FREQ 24000
#define SOUND_SAMPLES 1024
#define MUSIC_SETTINGS 0 // Low

// Keyboard config
#define NO_KEYBOARD_CFG

// Video config: the Pocket's panel is 1600x1440 (10:9), and 320x288 fills
// it at an exact 5x integer scale with square pixels.
#define DEFAULT_SCREEN_WIDTH 320
#define DEFAULT_SCREEN_HEIGHT 288
#define FULLSCREEN_ONLY
#define NO_RESIZE

// Input: the SDK shim reports the pad as keyboard events
// (up/down/left/right -> arrows, A -> LCTRL, B -> SPACE, X -> LALT,
//  Y -> LSHIFT, L1 -> COMMA, R1 -> PERIOD, SELECT -> TAB, START -> ESCAPE)
#define DEFAULT_KEY_JUMP    (SDLK_SPACE)   // B
#define DEFAULT_KEY_SWIM    (SDLK_SPACE)   // B
#define DEFAULT_KEY_FIRE    (SDLK_LCTRL)   // A
#define DEFAULT_KEY_CHANGE  (SDLK_LALT)    // X
#define DEFAULT_KEY_ENTER   (SDLK_LCTRL)   // A
#define DEFAULT_KEY_ESCAPE  (SDLK_ESCAPE)  // START
#define DEFAULT_KEY_STATS   (SDLK_TAB)     // SELECT
#define DEFAULT_KEY_PAUSE   (SDLK_LSHIFT)  // Y
#define DEFAULT_KEY_YES     (SDLK_LCTRL)   // A
#define DEFAULT_KEY_NO      (SDLK_SPACE)   // B
#define DEFAULT_KEY_BLASTER (SDLK_COMMA)   // L1
#define DEFAULT_KEY_TOASTER (SDLK_PERIOD)  // R1

class OpenfpgaPlatform final : public IPlatform {
	public:
		void AddGamePaths() override;

		void ErrorNoDatafiles() override;
};

#endif

#endif
