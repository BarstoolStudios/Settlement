#include "Main/WorldState.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"
#include "Util/GLMath.h"

WorldState::WorldState() {

	player = new Player();

	terrain = new Terrain(*player);
}

WorldState::~WorldState() {
	delete player;
	delete terrain;
}

void WorldState::draw(Camera& camera, Sun& sun) {

	terrain->draw(camera, sun);

}

void WorldState::update(GameTimer& timer) {

	player->update(*terrain, timer);

	terrain->update(*player);

}

void WorldState::addTree(Vector2f pos) {
	terrain->addTree(pos);
}

void WorldState::addPlayerSettlement(float radius) {
	if(!player->getSettlement()) {
		terrain->addPlayerSettlement(*player, radius);
	}
}