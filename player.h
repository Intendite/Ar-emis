#ifndef _BUTTERFLY_H
#define _BUTTERFLY_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace PlayerNS
{
	const int WIDTH = 128;
	const int HEIGHT = 128;
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 6 - HEIGHT;
	const int   EDGE_TOP = -60;             // For BOX and ROTATE_BOX collison.
	const int   EDGE_BOTTOM = 60;           // "   relative to center
	const int   EDGE_LEFT = -60;            // "
	const int   EDGE_RIGHT = 60;
	const float SPEED = 50;
	const int   TEXTURE_COLS = 4;			// texture has 8 columns
	const int   MOVING_START_FRAME = 0;     // animation starting frame
	const int   MOVING_END_FRAME = 7;       // animation ending frame
	const float MOVING_ANIMATION_DELAY = 0.1f;
}

class Player : public Entity
{
private:
	POINT mouseCursor;
	float distX;
	float distY;

public:
	// constructor
	Player();

	//inherited member functions
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
							TextureManager *textureM);
	void update(float frameTime);
	void repair();
};
