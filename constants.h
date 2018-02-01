// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Flower Power constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "artemis";
const char GAME_TITLE[] = "Ar+emis";
const bool FULLSCREEN = false;              // windowed or fullscreen
const int GAME_WIDTH = 1920;                // width of game in pixels
const int GAME_HEIGHT = 1080;                // height of game in pixels

											// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;           // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;         // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;   // maximum time used in calculations
const float FULL_HEALTH = 100;
const UINT  TILE_MAP_WIDTH = 100;           // width of tile map in tiles
const UINT  TILE_MAP_HEIGHT = 20;           // height of tile map in tiles

											// graphic images
const char TILE_TEXTURES[] = "pictures\\tiles.png";         // tiles
const char OBJECT_TEXTURES[] = "pictures\\textures.png";    // objects
const char MENU_IMAGE[] = "pictures\\menu.png";     // menu texture

													// audio files required by audio.cpp
													// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\waveBank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\soundBank.xsb";

// audio cues
const char ENGINE1[] = "engine1";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY = VK_OEM_3;    // `~ key for U.S.
const UCHAR ESC_KEY = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY = VK_MENU;     // Alt key
const UCHAR ENTER_KEY = VK_RETURN;   // Enter key
const UCHAR MOVELEFT_KEY = 'A';
const UCHAR MOVERIGHT_KEY = 'D';
const UCHAR MOVEUP_KEY = 'W';
const UCHAR MOVEDOWN_KEY = 'S';

#endif

