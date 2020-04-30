/*
 ============================================================================
 Name        : House.v
 Author      :
 Version     :
 Copyright   :
 Description :  Logic of the program is to enable an individual to move around the room of a floor within a house
                Furthermore, if there are any windows, the individual may act on the window position
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef HOUSE_H_
#include "House.h"
#endif

#ifndef SRC_DEBUG_H_
#include "debug.h"
#endif

//Text for the movements within the floor
char *direction_names[4] = {"North", "South", "West", "East"};
//Text for the type of room
char *room_names[7] = {"The entrance", "The livingroom", "The kitchen", "The garden","The bedroom","The bathroom","The doorstep"};
//Text for the type of floor
char floor_name[] = "Ground floor";
//Text for window position
char *wposition_names[2] = { "Open", "Closed"};


/*
 * Function:  houseGetRoom
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   house:
 *   roomNumber:
 *
 *  Returns:
 *  	ROOM*:
 */
ROOM* houseGetRoom(HOUSE *house, int roomNumber){
	if (debug == TRUE) {
		printf("     ==DEBUG: Harvesting room #%i from house '%s'\n", roomNumber,house->name);
	}
	ROOM *room;
	FLOOR *floor;
	floor  = house->niveau;
	if ((roomNumber< NUMBER_ROOMS) && (roomNumber< floor->actualRoomSize)) {
		room = floor->pieces[roomNumber];
		if (debug == TRUE) {
			printf("     ==DEBUG: Found room \'%s\'\n", room->name);
		}
		return room;
	} else {
		return NULL;
	}
}

/*
 * Function:  roomGetWindow
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   room:
 *   direction:
 *
 *  Returns:
 *  	WINDOW*:
 */
WINDOW* roomGetWindow(ROOM *room, DIRECTION direction) {
	WINDOW * windows;
	char *dir;
	if (debug == TRUE) {
		dir = direction_names[direction];
		printf("     ==DEBUG: Harvesting window \'%s\' from room '%s'\n", dir,room->name);
	}
	windows = room->fenetres[direction];
	return windows;
}

/*
 * Function:  roomViewDoors
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   house:
 *   actualLocation:
 *
 *  Returns:
 *  	nothing
 */
void roomViewDoors(HOUSE *house, ROOM *actualLocation){
	DOOR *door;
	ROOM *doorRoom;
	bool previousTxt = FALSE;
	printf("***********************************************************************************************\n");
	printf("The possible door(s) in \'%s\' are :\n",actualLocation->name);
	door = actualLocation->portes[NORTH];
	if (door != NULL) {
		doorRoom= door->room;
		printf("%s (%s)",direction_names[NORTH],doorRoom->name);
		previousTxt = TRUE;

	}

	door = actualLocation->portes[SOUTH];
	if (door != NULL) {
		if (previousTxt == TRUE) {
			printf(", ");
		}
		doorRoom= door->room;
		printf("%s (%s)",direction_names[SOUTH],doorRoom->name);
		previousTxt = TRUE;
	}

	door = actualLocation->portes[WEST];
	if (door != NULL) {
		if (previousTxt == TRUE) {
			printf(", ");
		}
		doorRoom= door->room;
		printf("%s (%s)",direction_names[WEST],doorRoom->name);
		previousTxt = TRUE;
	}

	door = actualLocation->portes[EAST];
	if (door != NULL) {
		if (previousTxt == TRUE) {
			printf(", ");
		}
		doorRoom= door->room;
		printf("%s (%s)",direction_names[EAST],doorRoom->name);
	}
	printf("\n***********************************************************************************************\n");
}

/*
 * Function:  roomViewWindows
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   roomViewWindows:
 *
 *  Returns:
 *  	nothing
 */
void roomViewWindows(ROOM *roomViewWindows){
	WINDOW *window;
	WINDOW_POSITION *windowPosition;
	bool previousTxt = FALSE;
	printf("***********************************************************************************************\n");
	printf("The position(s) of the possible windows(s) in \'%s\' are :\n",roomViewWindows->name);
	window = roomViewWindows->fenetres[NORTH];
	if (window != NULL) {
		windowPosition = &(window->statut);
		printf("%s (%s)",direction_names[NORTH], wposition_names[*windowPosition]);
		previousTxt = TRUE;
	}

	window = roomViewWindows->fenetres[SOUTH];
	if (window != NULL) {
		windowPosition = &(window->statut);
		if (previousTxt == TRUE) {
			printf(", ");
		}
		printf("%s (%s)",direction_names[SOUTH], wposition_names[*windowPosition]);
		previousTxt = TRUE;
	}

	window = roomViewWindows->fenetres[WEST];
	if (window != NULL) {
		windowPosition = &(window->statut);
		if (previousTxt == TRUE) {
			printf(", ");
		}
		printf("%s (%s)",direction_names[WEST], wposition_names[*windowPosition]);
		previousTxt = TRUE;
	}

	window = roomViewWindows->fenetres[EAST];
	if (window != NULL) {
		windowPosition = &(window->statut);
		if (previousTxt == TRUE) {
			printf(", ");
		}
		printf("%s (%s)",direction_names[EAST], wposition_names[*windowPosition]);
	}
	printf("\n***********************************************************************************************\n");

}

/*
 * Function:  switchWindowPositon
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   window:
 *
 *  Returns:
 *  	nothing
 */
void switchWindowPositon(WINDOW *window) {
	WINDOW_POSITION *statut;
	statut = &(window->statut);
	if (*statut == OPEN) {
		*statut = CLOSED;
		if (debug == TRUE) {
			printf("     ==DEBUG: Window position switched to \'%s\'\n",wposition_names[CLOSED]);
		}
	} else if (*statut == CLOSED) {
		*statut = OPEN;
		if (debug == TRUE) {
			printf("     ==DEBUG: Window position switched to \'%s\'\n",wposition_names[OPEN]);
		}
	}
}

/*
 * Function:  setWindowPosition
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   window:
 *   position:
 *
 *  Returns:
 *  	nothing
 */
void setWindowPosition(WINDOW *window, WINDOW_POSITION position) {
	WINDOW_POSITION *statut;
	WINDOW_POSITION oldStatus;
	statut = &(window->statut);
	oldStatus = *statut;

	if (position == OPEN) {
		*statut = OPEN;
		if (debug == TRUE) {
			if (oldStatus != OPEN) {
				printf("     ==DEBUG: Window position set to \'%s\'\n",wposition_names[OPEN]);
			} else if (oldStatus == OPEN) {
				printf("     ==DEBUG: Window position already set to \'%s\'\n",wposition_names[OPEN]);
			}
		}
	} else if (position == CLOSED) {
		*statut = CLOSED;
		if (debug == TRUE) {
			if (oldStatus != CLOSED) {
				printf("     ==DEBUG: Window position set to \'%s\'\n",wposition_names[CLOSED]);
			} else if (oldStatus == CLOSED) {
				printf("     ==DEBUG: Window position already set to \'%s\'\n",wposition_names[CLOSED]);
			}
		}
	}
}

/*
 * Function:  checkWindowPresence
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   location:
 *   direction:
 *
 *  Returns:
 *  	EXIT_FAILURE ...
 *  	EXIT_SUCCESS ...
 */
int checkWindowPresence(ROOM *location, DIRECTION direction) {
	WINDOW *window;
	window =location->fenetres[direction];
	if (debug == TRUE) {
		printf("     ==DEBUG: Checking presence of window \'%s\' in room \'%s\'\n",direction_names[direction], location->name);
	}

	if (window == NULL) {
		if (debug == TRUE) {
			printf("     ==DEBUG: Window \'%s\' not found in room \'%s\'\n",direction_names[direction], location->name);
		}
		return EXIT_FAILURE;
	}
	if (debug == TRUE) {
		printf("     ==DEBUG: Window \'%s\' found in room \'%s\'\n",direction_names[direction], location->name);
	}
	return EXIT_SUCCESS;
}

/*
 * Function:  moveToDirection
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   house:
 *   individual:
 *   direction
 *
 *  Returns:
 *  	EXIT_FAILURE ...
 *  	EXIT_SUCCESS ...
 */
int moveToDirection(HOUSE *house, PERSON *individual, DIRECTION direction) {
	ROOM *currentRoom, *nextRoom;
	DOOR *targetedDoor;
	currentRoom = individual->position;

	switch (direction) {

		case NORTH: {
			targetedDoor = currentRoom->portes[NORTH];
			if (targetedDoor == NULL) {
				return EXIT_FAILURE;
			}
			nextRoom = targetedDoor->room;
		}
		break;

		case SOUTH: {
			targetedDoor = currentRoom->portes[SOUTH];
			if (targetedDoor == NULL) {
				return EXIT_FAILURE;
			}
			nextRoom = targetedDoor->room;
		}
		break;

		case WEST: {
			targetedDoor = currentRoom->portes[WEST];
			if (targetedDoor == NULL) {
				return EXIT_FAILURE;
			}
			nextRoom = targetedDoor->room;
		}
		break;

		case EAST: {
			targetedDoor =currentRoom->portes[EAST];
			if (targetedDoor == NULL) {
				return EXIT_FAILURE;
			}
			nextRoom = targetedDoor->room;
		}
		break;
	}
	individual->position = nextRoom;
	return EXIT_SUCCESS;
}
