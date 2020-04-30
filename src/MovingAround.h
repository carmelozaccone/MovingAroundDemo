/*
 ============================================================================
 Name        : MovingAround.h
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#ifndef MOVINGAROUND_H_
#define MOVINGAROUND_H_

//Software Details
static const char PROGRAM_AUTHOR[] = "IPgeek";
static const char PROGRAM_NAME[] = "Moving Around the floor";
static const int PROGRAM_VERSION = 1;
char EXECUTABLE_NAME[] = "";

//Commands for the executable arguments
#define EXEC_HELP  	 'h'
#define EXEC_VERSION 'v'
#define EXEC_DEBUG 'd'

//Command to Quit the Software
#define QUIT 'Q'
#define HELP 'H'
#define LOCATION 'L'
#define CDOORS 'D'

//Information functions
void printVersion();
void printUsage();
void printHelp();
void printError(char msg[]);
int checkCmdLineParam(char *argv[]);


#endif /* MOVINGAROUND_H_ */
