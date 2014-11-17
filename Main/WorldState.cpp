#include "Main/WorldState.h"
#include "Main/Camera.h"
#include "Terrain/Sun.h"

WorldState::WorldState() {

	player = new Player();

	trees = new std::list<Tree>();

	settlements = new std::list<Settlement>();
}

void WorldState::draw(Camera& camera, Sun& sun) {

	for(auto& tree : *trees)
		tree.draw(camera, sun);

		for(auto& settlement : *settlements)
			settlement.draw(camera, sun);



}