#pragma once

#include "jumpman.h"
#include "bullet.h"
#include "collide.h"
#include "screen.h"


inline bool InSameScreenAsPlayer(int myScreen) {
	return myScreen == -1 || myScreen == ScreenManager::instance()->CurrentScreen();
}

template<typename B>
bool ReceiveDamageFromBullets(const B& bounds) { // returns true if collided
	for (Bullet* b : Bullet::GetAll()) {
		if (!b->alive) continue;
		if (Collide(b->bounds(), bounds)) {
			b->explode();
			return true;
		}
	}
	return false;
}

template<typename B>
bool DamagePlayerOnCollision(const B& bounds) { // returns true if collided
	JumpMan* player = JumpMan::instance();
	if (Collide(player->bounds(), bounds)) {
		if (!player->isInvencible()) {
			player->takeDamage(bounds.Center());
		}
		return true;
	}
	return false;
}
