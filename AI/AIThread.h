#ifndef AITHREAD_H
#define AITHREAD_H

class AIThread;

#include <thread>
#include <Main/WorldState.h>

class AIThread {

	std::thread runner;

	WorldState* worldState;

	void villagerAI();

	void settlementAI();

	void AILoop();

	static void staticAILoop(void* o) {
		static_cast<AIThread*>(o)->AILoop();
	}

public:
	AIThread(WorldState* worldState);

};

#endif // AITHREAD_H