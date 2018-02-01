// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// flowerPower.cpp v1.0
// flowerPower is the class we create.

#include "Artemis.h"
using namespace ArtemisNS;

//=============================================================================
// Constructor
//=============================================================================
Artemis::Artemis()
{
	mapX = 0;
	menuOn = true;
}

//=============================================================================
// Destructor
//=============================================================================
Artemis::~Artemis()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// initializes the game
//=============================================================================
void Artemis::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// menu texture
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	// map textures
	if (!tileTextures.initialize(graphics, TILE_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile textures"));

	// object textures
	if (!objectTextures.initialize(graphics, OBJECT_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing object textures"));

	// menu image
	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	// tile image
	if (!tile.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, &tileTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
	tile.setFrames(0, 0);
	tile.setCurrentFrame(0);

	// butterfly
	if (!butterfly.initialize(this, butterflyNS::WIDTH, butterflyNS::HEIGHT, butterflyNS::TEXTURE_COLS, &objectTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing butterfly"));
	butterfly.setFrames(butterflyNS::FLYING_START_FRAME, butterflyNS::FLYING_END_FRAME);
	butterfly.setCurrentFrame(butterflyNS::FLYING_START_FRAME);
	butterfly.setColorFilter(SETCOLOR_ARGB(255, 230, 230, 255));   // light blue, used for shield and torpedo
	butterfly.setMass(butterflyNS::MASS);
	// Start butterfly in center
	butterfly.setX(GAME_WIDTH / 2 - butterflyNS::WIDTH);
	butterfly.setY(GAME_HEIGHT / 2 - butterflyNS::HEIGHT);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Artemis::update()
{
	float butterflyX;

	if (menuOn)
	{
		if (input->anyKeyPressed())
		{
			menuOn = false;
			input->clearAll();
		}
	}

	butterfly.update(frameTime);        // fly the butterfly

	butterflyX = butterfly.getX();
	if (butterflyX < 0)                  // if butterfly off screen left
	{
		mapX -= butterfly.getVelocity().x * frameTime;  // scroll map right
		butterfly.setX(0);              // put butterfly at left edge
	}
	// if butterfly off screen right
	else if (butterflyX > GAME_WIDTH - butterfly.getWidth())
	{
		mapX -= butterfly.getVelocity().x * frameTime;  // scroll map left
														// put butterfly at right edge
		butterfly.setX((float)(GAME_WIDTH - butterfly.getWidth()));
	}

	if (mapX > 0)    // if map past left edge
	{
		mapX = 0;   // stop at left edge of map
		butterfly.setVelocityX(0);  // stop butterfly
	}
	// if map past right edge
	else if (mapX < (-MAP_WIDTH * TEXTURE_SIZE) + GAME_WIDTH)
	{
		// stop at right edge of map
		mapX = (-MAP_WIDTH * TEXTURE_SIZE) + GAME_WIDTH;
		butterfly.setVelocityX(0);  // stop butterfly
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Artemis::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Artemis::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Artemis::render()
{
	graphics->spriteBegin();

	for (int row = 0; row<MAP_HEIGHT; row++)       // for each row of map
	{
		tile.setY((float)(row*TEXTURE_SIZE)); // set tile Y
		for (int col = 0; col<MAP_WIDTH; col++)    // for each column of map
		{
			if (tileMap[row][col] >= 0)          // if tile present
			{
				tile.setCurrentFrame(tileMap[row][col]);    // set tile texture
				tile.setX((float)(col*TEXTURE_SIZE) + mapX);   // set tile X
															   // if tile on screen
				if (tile.getX() > -TEXTURE_SIZE && tile.getX() < GAME_WIDTH)
					tile.draw();                // draw tile
			}
		}
	}

	// draw butterfly
	butterfly.draw();

	if (menuOn)
		menu.draw();

	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Artemis::releaseAll()
{
	menuTexture.onLostDevice();
	tileTextures.onLostDevice();
	objectTextures.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Artemis::resetAll()
{
	tileTextures.onResetDevice();
	objectTextures.onResetDevice();
	menuTexture.onResetDevice();

	Game::resetAll();
	return;
}
