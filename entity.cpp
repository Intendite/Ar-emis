// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// entity.cpp v1.3

#include "entity.h"

//=============================================================================
// constructor
//=============================================================================
Entity::Entity() : Image()
{
	radius = 1.0;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 1.0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	active = true;                  // the entity is active
	collisionType = entityNS::CIRCLE;
	health = 100;
}

//=============================================================================
// Initialize the Entity.
// Pre: *gamePtr = pointer to Game object
//      width = width of Image in pixels  (0 = use full texture width)
//      height = height of Image in pixels (0 = use full texture height)
//      ncols = number of columns in texture (1 to n) (0 same as 1)
//      *textureM = pointer to TextureManager object
// Post: returns true if successful, false if failed
//=============================================================================
bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	input = gamePtr->getInput();                // the input system
	audio = gamePtr->getAudio();                // the audio system
	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

//=============================================================================
// activate the entity
//=============================================================================
void Entity::activate()
{
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Entity::update(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Image::update(frameTime);
}

//=============================================================================
// ai (artificial intelligence)
// typically called once per frame
// performs ai calculations, ent is passed for interaction
//=============================================================================
void Entity::ai(float frameTime, Entity &ent)
{}

//=============================================================================
// Perform collision detection between this entity and the other Entity.
// Each entity must use a single collision type. Complex shapes that require
// multiple collision types may be done by treating each part as a separate
// entity.
// Typically called once per frame.
// The collision types: CIRCLE, BOX, or ROTATED_BOX.
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collidesWith(Entity &ent, VECTOR2 &collisionVector)
{
	// if either entity is not active then no collision may occcur
	if (!active || !ent.getActive())
		return false;

	// If both entities are CIRCLE collision
	if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
		return collideCircle(ent, collisionVector);
	else    // one of the entities is a circle
		if (collisionType == entityNS::CIRCLE)  // if this entity uses CIRCLE collision
		{
			// Check for collision from other box with our circle
			bool collide = ent.collideRotatedBoxCircle(*this, collisionVector);
			// Put the collision vector in the proper direction
			collisionVector *= -1;              // reverse collision vector
			return collide;
		}
		else    // the other entity uses CIRCLE collision
			return collideRotatedBoxCircle(ent, collisionVector);
	return false;
}

//=============================================================================
// Circular collision detection method
// Called by collision(), default collision detection method
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collideCircle(Entity &ent, VECTOR2 &collisionVector)
{
	// difference between centers
	distSquared = *getCenter() - *ent.getCenter();
	distSquared.x = distSquared.x * distSquared.x;      // difference squared
	distSquared.y = distSquared.y * distSquared.y;

	// Calculate the sum of the radii (adjusted for scale)
	sumRadiiSquared = (radius*getScale()) + (ent.radius*ent.getScale());
	sumRadiiSquared *= sumRadiiSquared;                 // square it

														// if entities are colliding
	if (distSquared.x + distSquared.y <= sumRadiiSquared)
	{
		// set collision vector
		collisionVector = *ent.getCenter() - *getCenter();
		return true;
	}
	return false;   // not colliding
}

//=============================================================================
// Projects other box onto this edge01 and edge03.
// Called by collideRotatedBox()
// Post: returns true if projections overlap, false otherwise
//=============================================================================
bool Entity::projectionsOverlap(Entity &ent)
{
	float projection, min01, max01, min03, max03;

	// project other box onto edge01
	projection = graphics->Vector2Dot(&edge01, ent.getCorner(0)); // project corner 0
	min01 = projection;
	max01 = projection;
	// for each remaining corner
	for (int c = 1; c<4; c++)
	{
		// project corner onto edge01
		projection = graphics->Vector2Dot(&edge01, ent.getCorner(c));
		if (projection < min01)
			min01 = projection;
		else if (projection > max01)
			max01 = projection;
	}
	if (min01 > edge01Max || max01 < edge01Min) // if projections do not overlap
		return false;                       // no collision is possible

											// project other box onto edge03
	projection = graphics->Vector2Dot(&edge03, ent.getCorner(0)); // project corner 0
	min03 = projection;
	max03 = projection;
	// for each remaining corner
	for (int c = 1; c<4; c++)
	{
		// project corner onto edge03
		projection = graphics->Vector2Dot(&edge03, ent.getCorner(c));
		if (projection < min03)
			min03 = projection;
		else if (projection > max03)
			max03 = projection;
	}
	if (min03 > edge03Max || max03 < edge03Min) // if projections do not overlap
		return false;                       // no collision is possible

	return true;                            // projections overlap
}

//=============================================================================
// The box corner is checked for collision with circle using a distance check.
// Called by collideRotatedBoxCircle()
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector)
{
	distSquared = corner - *ent.getCenter();            // corner - circle
	distSquared.x = distSquared.x * distSquared.x;      // difference squared
	distSquared.y = distSquared.y * distSquared.y;

	// Calculate the sum of the radii, then square it
	sumRadiiSquared = ent.getRadius()*ent.getScale();   // (0 + circleR)
	sumRadiiSquared *= sumRadiiSquared;                 // square it

														// if corner and circle are colliding
	if (distSquared.x + distSquared.y <= sumRadiiSquared)
	{
		// set collision vector
		collisionVector = *ent.getCenter() - corner;
		return true;
	}
	return false;
}

//=============================================================================
// Is this Entity outside the specified rectangle
// Post: returns true if outside rect, false otherwise
//=============================================================================
bool Entity::outsideRect(RECT rect)
{
	if (spriteData.x + spriteData.width*getScale() < rect.left ||
		spriteData.x > rect.right ||
		spriteData.y + spriteData.height*getScale() < rect.top ||
		spriteData.y > rect.bottom)
		return true;
	return false;
}

//=============================================================================
// damage
// This entity has been damaged by a weapon.
// Override this function in the inheriting class.
//=============================================================================
void Entity::damage(int weapon)
{}

//=============================================================================
// Entity bounces after collision with another entity
//=============================================================================
void Entity::bounce(VECTOR2 &collisionVector, Entity &ent)
{
	VECTOR2 Vdiff = ent.getVelocity() - velocity;
	VECTOR2 cUV = collisionVector;              // collision unit vector
	Graphics::Vector2Normalize(&cUV);
	float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
	float massRatio = 2.0f;
	if (getMass() != 0)
		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));

	// If entities are already moving apart then bounce must
	// have been previously called and they are still colliding.
	// Move entities apart along collisionVector
	if (cUVdotVdiff > 0)
	{
		setX(getX() - cUV.x * massRatio);
		setY(getY() - cUV.y * massRatio);
	}
	else
		deltaV += ((massRatio * cUVdotVdiff) * cUV);
}
