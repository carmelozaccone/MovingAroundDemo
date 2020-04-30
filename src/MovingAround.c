/*
 ============================================================================
 Name        : MovingAround.c
 Author      : 
 Version     :
 Copyright   : 
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef MOVINGAROUND_H_
#include "MovingAround.h"
#endif

#ifndef HOUSE_H_
#include "House.h"
#endif

#ifndef SRC_DEBUG_H_
#include "debug.h"
#endif

/*
 * Function:  printVersion
 * --------------------
 * Function does ...:
 *
 *  Input:
 *
 *  Returns:
 *
 */
void printVersion() {
	printf("--------------------------------------------------------------\n");
	printf("Your program -%s- has been written by %s\n", PROGRAM_NAME, PROGRAM_AUTHOR);
	printf("Your program version is %d\n", PROGRAM_VERSION);
	if (debug == TRUE) {
		printf("     ==DEBUG: Your execution is in debug mode\n");
	}
	if (debugVerbose == TRUE) {
		printf("     ==DEBUG: Your execution is in verbose debug mode\n");
	}
	printf("--------------------------------------------------------------\n");
}

/*
 * Function:  printUsage
 * --------------------
 * Function does ...:
 *
 *  Input:
 *
 *  Returns:
 *
 */
void printUsage() {
	printf("       =======================================================\n");
	printf("       Movement actions within the floor\n");
	printf("          North: %c\n",MOVE_NORTH);
	printf("          South: %c\n",MOVE_SOUTH);
	printf("          West : %c\n",MOVE_WEST);
	printf("          East : %c\n",MOVE_EAST);
	printf("       Movement actions for a window\n");
	printf("          Open : %c\n",ACTION_OPEN);
	printf("          Close: %c\n",ACTION_CLOSE);
	printf("          Switch: %c\n",ACTION_SWITCH);
	printf("       =======================================================\n");
}

/*
 * Function:  printHelp
 * --------------------
 * Function does ...:
 *
 *  Input:
 *
 *  Returns:
 *
 */
void printHelp() {
	printf("--------------------------------------------------------------\n");
	printf("Usages:\n");
	printf("       %s -%c    -> display this Help\n",EXECUTABLE_NAME, EXEC_HELP);
	printf("       %s -%c    -> display this executable version\n",EXECUTABLE_NAME, EXEC_VERSION);
	printf("       %s -%c    -> run this executable in debug mode\n",EXECUTABLE_NAME, EXEC_DEBUG);
	printUsage();
	printf("--------------------------------------------------------------\n");
}

/*
 * Function:  printError
 * --------------------
 * Function does ...:
 *
 *  Input:
 *  	msg:
 *
 *  Returns:
 *
 */
void printError(char msg[]) {
	printf("\n--------------------------------------------------------------\n");
	printf("Error : %s\n",msg);
	printf("--------------------------------------------------------------\n");
}

/*
 * Function:  checkCmdLineParam
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   argv:
 *
 *  Returns:
 *  	EXIT_SUCCESS:
 *  	EXIT_FAILURE:
 */
int checkCmdLineParam(char *argv[]){
	char PARAM1[] = "";
    if(sscanf(argv[1], "%s", PARAM1) != 1) {
    	printError("Argument is invalid");
        return EXIT_FAILURE;
    }

	char CMD = PARAM1[1];

	switch (CMD) {

		case EXEC_HELP: {
			printHelp();
			return EXIT_SUCCESS;
		}

		case EXEC_VERSION: {
			printVersion();
			return EXIT_SUCCESS;
		}

		case EXEC_DEBUG: {
			//set execution to debug mode
			debug = TRUE;
			printf("     ==DEBUG: Activation of debug mode\n");
			return EXIT_SUCCESS;
		}
		break;

		default: {
			char msg[] = "Unrecognized option \"";
			char cmd[3];
			cmd[0]=CMD;
			cmd[1]='\"';
			cmd[2]='\0';
			strcat(msg,cmd);
			printError(msg);
			return EXIT_FAILURE;
		}
	}
}

/*
 * Function:  main
 * --------------------
 * Function does ...:
 *
 *  Input:
 *   argc:
 *   argv:
 *
 *  Returns:
 *  	EXIT_SUCCESS:
 *  	EXIT_FAILURE:
 */
int main(int argc, char *argv[]) {
//to unbuffer the debug if run within an IDE
//	setbuf(stdout, NULL);
//	setbuf(stdin, NULL);
	debug = FALSE;
	debugVerbose = FALSE;

	//Define the executable name from the current .exe filename
    sscanf(argv[0], "%s", EXECUTABLE_NAME);

	//Are there any argument for the software execution
	if (argc > 1) {
		int result;
		result = checkCmdLineParam(argv);
		//If debug argument was found, we do not exit the program
		if (debug == FALSE) {
			return result;
		}
	}

	//We do our business
	printf("We do our business\n\n");
	//We create the environment
	PERSON individual;
	HOUSE house;
	ROOM *startLocation;

	if (debug == TRUE) {
		printf("    ==DEBUG: Starting to create the house\n");
	}
	//Our House has by factory one single Floor Maximum
	FLOOR floor;
	//Our current house has 7 rooms
	ROOM garden,bedroom, kitchen, bathroom, entrance, livingRoom, doorStep;
	//Some rooms have access to other rooms thru doors
	DOOR dgarden_s,dbedroom_s, dkitchen_n, dkitchen_s,dbathroom_e,dentrance_n,dentrance_s,dentrance_w, dentrance_e, dlivingRoom_n,dlivingRoom_w,ddoorstep_n;
	//Some rooms have a windows view
	WINDOW wbedroom_n,wkitchen_e,wbathroom_s,wlivingRoom_s, wlivingRoom_e;

	//our current implementation only support 1 floor
	house.niveau = &floor;
	char tmpNameHouse[50];
	strcpy(tmpNameHouse,"House of ");
	strcat(tmpNameHouse, PROGRAM_AUTHOR);
	house.name = tmpNameHouse;
	if (debug == TRUE) {
		printf("     ==DEBUG: House name is \'%s\'\n", house.name);
	}
	//we setup the floor
	floor.name = floor_name;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating floor %s\n", floor.name);
	}
	//our current implementation support only one floor
	//we have setup 7 rooms on the floor
	floor.actualRoomSize = 7;
	floor.pieces[0] = &garden;
	floor.pieces[1] = &bedroom;
	floor.pieces[2] = &kitchen;
	floor.pieces[3] = &bathroom;
	floor.pieces[4] = &entrance;
	floor.pieces[5] = &livingRoom;
	floor.pieces[6] = &doorStep;

	//the text representing the door direction
	char *dir;
	//We setup the garden
	garden.name = room_names[GARDEN];
	garden.id=0;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating room %s with id #%i\n", garden.name,garden.id);
	}
	//setup the doors
	dgarden_s.roomId = &(kitchen.id);
	dgarden_s.room   = &kitchen;
	if (debug == TRUE) {
		dir = direction_names[SOUTH];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[ENTRANCE], room_names[KITCHEN]);
	}
	//assign the doors to a direction
	garden.portes[NORTH] = NULL;
	garden.portes[SOUTH] = &dgarden_s;
	garden.portes[WEST] = NULL;
	garden.portes[EAST] = NULL;
	//setup the windows
	garden.fenetres[NORTH] = NULL;
	garden.fenetres[SOUTH] = NULL;
	garden.fenetres[WEST] = NULL;
	garden.fenetres[EAST] = NULL;

	//We setup the bedroom
	bedroom.name = room_names[BEDROOM];
	bedroom.id =1;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating room \'%s\' with id #%i\n", bedroom.name,bedroom.id);
	}
	//setup the doors
	dbedroom_s.roomId = &(entrance.id);
	dbedroom_s.room   = &entrance;
	if (debug == TRUE) {
		dir = direction_names[NORTH];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[BEDROOM], room_names[ENTRANCE]);
	}
	//assign the doors to a direction
	bedroom.portes[NORTH] = NULL;
	bedroom.portes[SOUTH] = &dbedroom_s;
	bedroom.portes[WEST] = NULL;
	bedroom.portes[EAST] = NULL;
	//setup the windows
	wbedroom_n.statut = OPEN;
	//assign the window to a direction
	bedroom.fenetres[NORTH] = &wbedroom_n;
	bedroom.fenetres[SOUTH] = NULL;
	bedroom.fenetres[WEST] = NULL;
	bedroom.fenetres[EAST] = NULL;
	if (debug == TRUE) {
		dir = direction_names[NORTH];
		printf("        ==DEBUG: Creating window \'%s\' for room \'%s\'\n", dir, room_names[BEDROOM]);
	}
	//We setup the kitchen
	kitchen.name = room_names[KITCHEN];
	kitchen.id =2;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating room \'%s\' with id #%i\n", kitchen.name,kitchen.id);
	}
	//setup the doors
	dkitchen_n.roomId = &(garden.id);
	dkitchen_n.room   = &garden;
	dkitchen_s.roomId = &(livingRoom.id);
	dkitchen_s.room   = &livingRoom;
	if (debug == TRUE) {
		dir = direction_names[NORTH];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[KITCHEN], room_names[GARDEN]);
		dir = direction_names[SOUTH];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[KITCHEN], room_names[LIVINGROOM]);
	}
	//assign the doors to a direction
	kitchen.portes[NORTH] = &dkitchen_n;
	kitchen.portes[SOUTH] = &dkitchen_s;
	kitchen.portes[WEST] = NULL;
	kitchen.portes[EAST] = NULL;
	//setup the windows
	wkitchen_e.statut = OPEN;
	//assign the window to a direction
	kitchen.fenetres[NORTH] = NULL;
	kitchen.fenetres[SOUTH] = NULL;
	kitchen.fenetres[WEST] = NULL;
	kitchen.fenetres[EAST] = &wkitchen_e;
	if (debug == TRUE) {
		dir = direction_names[EAST];
		printf("        ==DEBUG: Creating window \'%s\' for room \'%s\'\n", dir, room_names[KITCHEN]);
	}
	//We setup the bathroom
	bathroom.name = room_names[BATHROOM];
	bathroom.id=3;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating room \'%s\' with id #%i\n", bathroom.name,bathroom.id);
	}
	//setup the doors
	dbathroom_e.roomId = &(entrance.id);
	dbathroom_e.room   = &entrance;
	if (debug == TRUE) {
		dir = direction_names[EAST];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[BATHROOM], room_names[ENTRANCE]);
	}
	//assign the doors to a direction
	bathroom.portes[NORTH] = NULL;
	bathroom.portes[SOUTH] = NULL;
	bathroom.portes[WEST]  = NULL;
	bathroom.portes[EAST]  = &dbathroom_e;
	//setup the windows
	wbathroom_s.statut = OPEN;
	//assign the window to a direction
	bathroom.fenetres[NORTH] = NULL;
	bathroom.fenetres[SOUTH] = &wbathroom_s;
	bathroom.fenetres[WEST] = NULL;
	bathroom.fenetres[EAST] = NULL;
	if (debug == TRUE) {
		dir = direction_names[SOUTH];
		printf("        ==DEBUG: Creating window \'%s\' for room \'%s\'\n", dir, room_names[BATHROOM]);
	}
	//We setup the entrance
	entrance.name = room_names[ENTRANCE];
	entrance.id = 4;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating room \'%s\' with id #%i\n", entrance.name,entrance.id);
	}
	//setup the doors
	dentrance_n.roomId = &(bedroom.id);
	dentrance_n.room   = &bedroom;
	dentrance_s.roomId = &(doorStep.id);
	dentrance_s.room   = &doorStep;
	dentrance_w.roomId = &(bathroom.id);
	dentrance_w.room   = &bathroom;
	dentrance_e.roomId = &(livingRoom.id);
	dentrance_e.room   = &livingRoom;
	if (debug == TRUE) {
		dir = direction_names[NORTH];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[ENTRANCE], room_names[BEDROOM]);
		dir = direction_names[SOUTH];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[ENTRANCE], room_names[DOORSTEP]);
		dir = direction_names[WEST];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[ENTRANCE], room_names[BATHROOM]);
		dir = direction_names[EAST];
		printf("        ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[ENTRANCE], room_names[LIVINGROOM]);
	}
	//assign the doors to a direction
	entrance.portes[NORTH] = &dentrance_n;
	entrance.portes[SOUTH] = &dentrance_s;
	entrance.portes[WEST]  = &dentrance_w;
	entrance.portes[EAST]  = &dentrance_e;
	//setup the windows
	entrance.fenetres[NORTH] = NULL;
	entrance.fenetres[SOUTH] = NULL;
	entrance.fenetres[WEST] = NULL;
	entrance.fenetres[EAST] = NULL;

	//We setup the livingRoom
	livingRoom.name = room_names[LIVINGROOM];
	livingRoom.id = 5;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating room \'%s\' with id #%i\n", livingRoom.name,livingRoom.id);
	}
	//setup the doors
	dlivingRoom_n.roomId = &(kitchen.id);
	dlivingRoom_n.room   = &kitchen;
	dlivingRoom_w.roomId = &(entrance.id);
	dlivingRoom_w.room   = &entrance;
	if (debug == TRUE) {
		dir = direction_names[NORTH];
		printf("       ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[LIVINGROOM], room_names[KITCHEN]);
		dir = direction_names[WEST];
		printf("       ==DEBUG: Creating door \'%s\' for room \'%s\' to the room \'%s\'\n", dir, room_names[LIVINGROOM], room_names[ENTRANCE]);
	}
	//assign the doors to a direction
	livingRoom.portes[NORTH] = &dlivingRoom_n;
	livingRoom.portes[SOUTH] = NULL;
	livingRoom.portes[WEST]  = &dlivingRoom_w;
	livingRoom.portes[EAST]  = NULL;
	//setup the windows
	wlivingRoom_s.statut = OPEN;
	wlivingRoom_e.statut = OPEN;
	//assign the window to a direction
	livingRoom.fenetres[NORTH] = NULL;
	livingRoom.fenetres[SOUTH] = &wlivingRoom_s;
	livingRoom.fenetres[WEST] = NULL;
	livingRoom.fenetres[EAST] = &wlivingRoom_e;
	if (debug == TRUE) {
		dir = direction_names[SOUTH];
		printf("        ==DEBUG: Creating window \'%s\' for room \'%s\'\n", dir, room_names[LIVINGROOM]);
		dir = direction_names[EAST];
		printf("        ==DEBUG: Creating window \'%s\' for room \'%s\'\n", dir, room_names[LIVINGROOM]);
	}
	//We setup the doorStep;
	doorStep.name = room_names[DOORSTEP];
	doorStep.id = 6;
	if (debug == TRUE) {
		printf("     ==DEBUG: Creating room \'%s\' with id #%i\n", doorStep.name,doorStep.id);
	}
	//setup the doors
	ddoorstep_n.roomId = &(entrance.id);
	ddoorstep_n.room   = &entrance;
	//assign the doors to a direction
	doorStep.portes[NORTH] = &ddoorstep_n;
	doorStep.portes[SOUTH] = NULL;
	doorStep.portes[WEST]  = NULL;
	doorStep.portes[EAST]  = NULL;
	if (debug == TRUE) {
		dir = direction_names[NORTH];
		printf("       ==DEBUG: Creating door \'%s\' for room %s\n", dir, room_names[ENTRANCE]);
	}
	//setup the windows
	doorStep.fenetres[NORTH] = NULL;
	doorStep.fenetres[SOUTH] = NULL;
	doorStep.fenetres[WEST] = NULL;
	doorStep.fenetres[EAST] = NULL;

	if (debug == TRUE) {
		printf("   ==DEBUG: House created\n");
	}

	int initialRoomId;
	//our actual house architecture is composed of 9 rooms
	//4 is the entrance (see house design schema)
	initialRoomId=4;
	startLocation = houseGetRoom(&house, initialRoomId);

	if (debug == TRUE) {
		printf("   ==DEBUG: Starting to create the individual\n");
	}

	char namePerson[50];
	strcpy(namePerson,"");
	strcat(namePerson, PROGRAM_AUTHOR);
	individual.name 	= namePerson;
	individual.position = startLocation;

	if (debug == TRUE) {
		printf("     ==DEBUG: Individual \'%s\' placed in room \'%s\'\n",individual.name, startLocation->name);
	}

	if (debug == TRUE) {
		printf("   ==DEBUG: Individual created\n");
	}
	//-----------------
	printf("Individual starting room position is \"%s\"\n", startLocation->name);

	bool CONTINUE = TRUE;
	DIRECTION mymovement;
	char mymove;
	bool moveCMD = FALSE;

	while (CONTINUE) {

		//We ask the user for a movement direction
		printf("What is your movement ? (H Movement help, L Show location, D View door(s), Q exit) ?");
		scanf("%c", &mymove);

		// <== remove newline
		getchar();
		//Get the Uppercase char
		mymove = toupper(mymove);
		switch (mymove) {

			//Movements command
			case MOVE_NORTH:
			{
				moveCMD = TRUE;
				mymovement = NORTH;
			}
			break;

			case MOVE_SOUTH: {
				moveCMD = TRUE;
				mymovement = SOUTH;
			}
			break;

			case MOVE_WEST: {
				moveCMD = TRUE;
				mymovement = WEST;
			}
			break;

			case MOVE_EAST: {
				moveCMD = TRUE;
				mymovement = EAST;
			}
			break;

			//Ask command help
			case HELP: {
				moveCMD = FALSE;
				printf("\n");
				printUsage();
			}
			break;

			//Ask local position
			case LOCATION: {
				moveCMD = FALSE;
				ROOM *actualLocation;
				actualLocation = individual.position;
				printf("\"%s\"'s position in the house \'%s\' is the room \"%s\"\n", individual.name, house.name, actualLocation->name);

			}
			break;

			//Ask current doors
			case CDOORS: {
				moveCMD = FALSE;
				ROOM *actualLocation;
				actualLocation = individual.position;
				roomViewDoors(&house, actualLocation);
			}
			break;

			//Program exit command
			case QUIT: {
				moveCMD = FALSE;
				printf("Stopping the business\n");
				CONTINUE = FALSE;
			}
			break;

			default: {
				moveCMD = FALSE;
				char msg[] = "Unrecognized command \"";
				char cmd[3];
				cmd[0]=mymove;
				cmd[1]='\"';
				cmd[2]='\0';
				strcat(msg,cmd);
				printError(msg);
			}
			break;
		}

		if (moveCMD == TRUE) {
			char msg[] = "We are going to \'";
			strcat(msg, direction_names[mymovement]);
			strcat(msg,"\'\n");
			printf(msg);

			int succes;
			succes= moveToDirection(&house,&individual, mymovement);
			ROOM *location;
			location = individual.position;
			if (succes == EXIT_SUCCESS) {
				char msg[] = "Succesfull move ! There is a door.\n";
				printf(msg);
				printf("\"%s\"\'s new room position is \"%s\"\n", individual.name, location->name);
			} else {
				char msg[] = "Unuccesfull move ! There is no door.\n";
				printf(msg);
				printf("\"%s\"\'s room position is still \"%s\"\n",individual.name, location->name);

				//If there is a wall, theris maybe a windows
				succes= checkWindowPresence(location, mymovement);
				if (succes == EXIT_SUCCESS) {
					//Ask user if he would like to switch the window position
					bool CONTINUE2 = TRUE;
					char action;

					while (CONTINUE2) {
						printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						//We ask the user for window action
						printf("Do you want to change the position's state of the window ? (H Action help, W View windows(s), L Show location) ?");
						scanf("%c", &action);

						// <== remove newline
						getchar();
						//Get the Uppercase char
						action = toupper(action);
						switch (action) {

							//Action command
							case ACTION_SWITCH:	{
								WINDOW* window;
								window = roomGetWindow(location, mymovement);
								switchWindowPositon(window);
								printf("Successfully switched window \'%s\' in room \'%s\'\n",direction_names[mymovement], location->name);
								CONTINUE2 = FALSE;
							}
							break;

							case ACTION_OPEN: {
								WINDOW* window;
								window = roomGetWindow(location, mymovement);
								setWindowPosition(window, OPEN);
								printf("Successfully opened window \'%s\' in room \'%s\'\n",direction_names[mymovement], location->name);
								CONTINUE2 = FALSE;
							}
							break;

							case ACTION_CLOSE: {
								WINDOW* window;
								window = roomGetWindow(location, mymovement);
								setWindowPosition(window, CLOSED);
								printf("Successfully closed window \'%s\' in room \'%s\'\n",direction_names[mymovement], location->name);
								CONTINUE2 = FALSE;
							}
							break;

							//Ask command help
							case HELP: {
								printf("\n");
								printUsage();
							}
							break;

							//Ask local position
							case LOCATION: {
								ROOM *actualLocation;
								actualLocation = individual.position;
								printf("\"%s\"'s position in the house \'%s\' is the room \"%s\"\n", individual.name, house.name, actualLocation->name);
							}
							break;

							//Ask current window status
							case ACTION_VIEW:{
								roomViewWindows(location);
							}
							break;


							default: {
								char msg[] = "Unrecognized command \"";
								char cmd[3];
								cmd[0]=action;
								cmd[1]='\"';
								cmd[2]='\0';
								strcat(msg,cmd);
								printError(msg);
							}
							break;
						}

					}
					printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				}
			}
		}
	}
	printf("Exiting the program\n");
	printf("Goodbye");
	return EXIT_SUCCESS;
}
