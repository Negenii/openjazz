
/**
 *
 * @file openfpga.cpp
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

#include "openfpga.h"

#ifdef OPENFPGA

#include "io/file.h"
#include "io/log.h"
#include "util.h"

#include <stdio.h>
#include <unistd.h>

#ifndef OF_PC
extern "C" {
#include "of_file.h"
#include "of_interact.h"
#include "of_mount.h"
#include "of_video.h"
}

namespace {
	// Instance JSON binds openjazz_N.sav to save slots 10..14; OpenJazz opens
	// SAVE.0..SAVE.3 and openjazz.cfg by bare name, so alias them here.
	const struct { unsigned slot; const char* name; } saveBindings[] = {
		{10, "SAVE.0"}, {11, "SAVE.1"}, {12, "SAVE.2"}, {13, "SAVE.3"},
		{14, "openjazz.cfg"}
	};
}
#endif

void OpenfpgaPlatform::AddGamePaths() {
#ifdef OF_PC
	// Desktop build: game data in ./jazz/, config and saves in cwd
	gamePaths.add(createString("jazz" OJ_DIR_SEP_STR), PATH_TYPE_SYSTEM|PATH_TYPE_GAME);
#else
	for (auto& b : saveBindings)
		of_file_slot_register(b.slot, b.name);

	if (of_iso_mount("jazz.iso", "/jazz") == 0) {
		gamePaths.add(createString("/jazz/"), PATH_TYPE_SYSTEM|PATH_TYPE_GAME);
	} else {
		LOG_ERROR("Could not mount jazz.iso");
	}
#endif
	// Config and saves: bare file names, resolved by the slot registry on
	// hardware and by cwd on desktop. main.cpp adds "" as GAME|CONFIG|TEMP
	// later, but has_temp would enable the HTML logfile; we only want CONFIG.
	gamePaths.add(createString(""), PATH_TYPE_CONFIG);
}

/* Core-menu option "Aspect Ratio": 0 = fullscreen 10:9 (320x288),
 * 1 = original 4:3 (320x200). of_interact_get() takes the variable's
 * position in interact.json's "variables" array (0-based), not its "id"
 * field; interact.json currently declares 6 variables ahead of this one
 * (Enable Analogizer, SNAC Adapter, SNAC Controller Assignment, Analogizer
 * Video Out, Video H Offset, Video V Offset), so Aspect Ratio is index 6.
 * Read once: the Pocket applies menu changes on core reload, and the
 * engine queries the height on every video reset. */
int OpenfpgaPlatform::screenHeight() {
#ifdef OF_PC
	return 288;
#else
	static int height;
	if (!height) height = (of_interact_get(6) & 1) ? 200 : 288;
	return height;
#endif
}

void OpenfpgaPlatform::ErrorNoDatafiles() {
#ifndef OF_PC
	of_video_set_display_mode(2);
#endif
	printf("\n\n   OpenJazz: game data not found.\n"
	       "   Put jazz.iso (built with tools/mkjazz.sh from your\n"
	       "   Jazz Jackrabbit files) into Assets/openjazz/common/\n");
	sleep(10);
}

#endif
