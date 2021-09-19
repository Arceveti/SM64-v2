#pragma once

#include <PR/ultratypes.h>

struct LevelCommand;

extern LevelScript level_script_entry[];
#ifdef USE_EXT_RAM
extern LevelScript level_script_entry_error_screen[];
#endif

struct LevelCommand *level_script_execute(struct LevelCommand *cmd);
