/*
 ============================================================================
 Name        : House.h
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#ifndef HOUSE_H_
#define HOUSE_H_

//Defines the capacity of the present House definition
#define NUMBER_ROOMS  16

//Commands for the movements within the floor
extern char *direction_names[4];
typedef enum {
	NORTH,
	SOUTH,
	WEST,
	EAST
} DIRECTION;

#define MOVE_DIRECTIONS 4
#define MOVE_NORTH 'N'
#define MOVE_SOUTH 'S'
#define MOVE_WEST  'W'
#define MOVE_EAST  'E'

extern char *room_names[7];
typedef enum {
	ENTRANCE,
	LIVINGROOM,
	KITCHEN,
	GARDEN,
	BEDROOM,
	BATHROOM,
	DOORSTEP
} ROOM_TYPE;


//Command to switch a Windows Status
extern char *wposition_names[2];
typedef enum {
	OPEN,
	CLOSED
} WINDOW_POSITION;

#define ACTION_OPEN 'O'
#define ACTION_CLOSE 'C'
#define ACTION_SWITCH  'S'
#define ACTION_VIEW  'W'

typedef struct {
	WINDOW_POSITION statut;
} WINDOW;

//to enable the structures to reference to each other
typedef struct DOOR DOOR;
typedef struct ROOM ROOM;

struct DOOR {
	int *roomId;
	ROOM *room;
};

struct ROOM {
	int id;
	DOOR *portes[MOVE_DIRECTIONS];
	WINDOW *fenetres[MOVE_DIRECTIONS];
	char *name;
};

extern char floor_name[];

typedef struct {
	ROOM *pieces[NUMBER_ROOMS];
	//the actual number of room create in this floor
	int actualRoomSize;
	char *name;
} FLOOR;

typedef struct {
	FLOOR *niveau;
	char *name;
} HOUSE;

typedef struct {
	ROOM *position;
	char *name;
} PERSON;

ROOM* houseGetRoom(HOUSE *house, int roomNumber);
void roomViewDoors(HOUSE *house, ROOM *actualLocation);
void roomViewWindows(ROOM *actualLocation);
int moveToDirection(HOUSE *house, PERSON *individual, DIRECTION direction);
WINDOW* roomGetWindow(ROOM *room, DIRECTION direction);
void switchWindowPositon(WINDOW *window);
void setWindowPosition(WINDOW *window, WINDOW_POSITION position);
int checkWindowPresence(ROOM *location, DIRECTION direction);

#endif /* HOUSE_H_ */
