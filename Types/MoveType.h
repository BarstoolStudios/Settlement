/******************************************************************************\
* File: MoveType.h
*
* Author: Josh Taylor
*
* Description: Defines different types of movement states
*
* Dev Note: Should probably move to a types.h file for possible additions of
*           other types.
\******************************************************************************/

#ifndef MOVETYPE_H
#define MOVETYPE_H

enum MoveType {
	UNDEFINED, NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHEAST,
	SOUTHWEST, SPRINT, WALK, RUN, JUMP, NO_MOVE
};

#endif // MOVETYPE_H