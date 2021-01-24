#pragma once
#include "Collision.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recA.y + recA.h >= recB.y &&
		recB.x + recB.w >= recA.x &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}
	return false;
}