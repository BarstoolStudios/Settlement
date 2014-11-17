/******************************************************************************\
* File: AIThread.cpp
*
* Author: Josh Taylor
*
* Header: AIThread.h
*
* Description: Creates AI Thread to run concurrently with
*              Drawing Thread (Main Thread).
\******************************************************************************/

#include "AI/AIThread.h"

AIThread::AIThread(WorldState* worldState) 
:
	runner(&AIThread::staticAILoop, this),
	worldState(worldState)
{}

void AIThread::AILoop() {
	settlementAI();
	villagerAI();
}

void AIThread::settlementAI() {

}

void AIThread::villagerAI() {

}