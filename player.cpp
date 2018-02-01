#include "player.h"
using namespace PlayerNS;

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
	spriteData.width = WIDTH;
	spriteData.height = HEIGHT;
	spriteData.x = X;
	spriteData.y = Y;
	edge.top = EDGE_TOP;             // ROTATED_BOX collision edges
	edge.bottom = EDGE_BOTTOM;
	edge.left = EDGE_LEFT;
	edge.right = EDGE_RIGHT;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = MOVING_ANIMATION_DELAY;
	startFrame = MOVING_START_FRAME;
	endFrame = MOVING_END_FRAME;
	currentFrame = startFrame;
	radius = WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Butterfly.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);

	if (GetCursorPos(&mouseCursor))
	{
		distX = 
		// x = mouse, y = player
		// y ---- x
		if (spriteData.x < mouseCursor.x)
		{
			if (spriteData.y < mouseCursor.y)
			{
				this->setDegrees(90 - tan())
			}
			else if (spriteData.y > mouseCursor.y)
			{
				//do angles again
			}
			else;
		}
		// x ---- y
		else if (spriteData.x > mouseCursor.x)
		{
			if (spriteData.y < mouseCursor.y)
			{
				//do angles
			}
			else if (spriteData.y > mouseCursor.y)
			{
				//do angles again
			}
			else;
		}
		else;
	}
	if (input->isKeyDown(MOVEUP_KEY))
	{

	}

	if (input->isKeyDown(MOVEDOWN_KEY))
	{

	}

	if (input->isKeyDown(MOVELEFT_KEY))
	{

	}

	if (input->isKeyDown(MOVERIGHT_KEY))
	{

	}
}