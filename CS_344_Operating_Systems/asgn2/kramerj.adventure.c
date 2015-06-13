// Programmer: Joseph Kramer
// DATE: 5-3-15


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MAX_CONNECTIONS_ADD_TO_FILE 5
#define MAX_CONNECTIONS 6

// Struct to hold connection names
typedef struct Connections {
    char connect_room[256];
} Connections;

// Struct to hold info on rooms, plus one rooms entire connections and 
// importantly it's size
typedef struct ROOM {
    char name[256];
    int connect_id;
    int size;
    Connections Connected[6];
} ROOM;

// Structs to hold the paths
typedef struct TRACK {
    char track_path[256];    
} TRACK;

// Struct to track the path taken by the user
typedef struct PATH {
    TRACK find[500];
    int steps;
} PATH;

// GLOBALS HERE
ROOM Rooms[MAX_CONNECTIONS];
PATH pathTaken;


///###############################################################################################
///########################## FUNCTION TO CREATE RANDOM NUMBERS ###########################
//###############################################################################################
// Description: This code will cycle through an array of 10 randomly generated numbers. It will keep
//				cycling until there is not a repeated random number. It will then place the array into
//				the passed in reference to random_nums array.
// Why:			This is done to ensure that all rooms and displays to users are random.
// Sources: 	http://stackoverflow.com/questions/1608181/unique-random-numbers-in-an-integer-array-in-the-c-programming-language
//				http://www.tutorialspoint.com/c_standard_library/c_function_srand.htm
void randomGen(int random_nums[]) {
    
    int array[10];
    int x, p;
    int count;
    int i = 0;

    // This initializes the random number generator
    srand(time(NULL));
    
    // Loads the array
    for (count = 0; count < 10; count++)
        array[count] = rand() % 10 ;
    
    // Cycles through making sure numbers are 0-9
    while (i < 10) {
        int r = rand() % 10;
        
        for (x = 0; x < i; x++)
            if (array[x] == r)
                break;
        
        if (x == i)
            array[i++] = r;
    }
    
	// Places random numbers into random_num array
    for (p = 0; p < 10; p++)
        random_nums[p] = * (array + p);
}


//###############################################################################################
///########################## FUNCTION TO DELAY TIME###########################
//###############################################################################################
// Description: This code is here to force the CPU to perform a loop and thereby allow more time to pass
//				This done solely for the sake of the randomGen function, because when randomGen gets 
//				called multiple times in a row, the numbers are not random because the random function
//				is calculated off of time. That is why this function forces the CPU to run 2 large loops
//				and thereby allows the internal time to increase and therefore seed a new number into
//				the random function
// Why:			I needed a way to pause the and I couldn't find a function to simply pause, so I made 
//				a loop that causes it run for a few seconds, similar to a a a loop
// Sources:		http://www.programmingsimplified.com/c/dos.h/delay
void delayTime(){
	int x, p;
	// These two for loops are only here to cause a delay and therefore allow for better random
	// numbers. I do this because my random function is based on  srand(time(NULL)) and I need to 
	// delay the time in-order to get more randomized numbers. 
    for ( x = 1 ; x <= 32767 ; x++ )
        for ( p = 1 ; p <= 32767 ; p++ )
        {}
}

///###############################################################################################
///######################## FUNCTION TO CHOOSE THE POSSIBLE ROOM NAMES ##########################
//###############################################################################################
// Description:	This hard codes the room names into the array possible_room_names
// Why:			The assignment specifically stated to do this so we can load the names into a file
//				and then into memory.
void createPossibleRoomNames(char **possible_room_names) {
    
     possible_room_names[0] = "Kitten";
     possible_room_names[1] = "Puppy";
     possible_room_names[2] = "TA's";
     possible_room_names[3] = "Snow";
     possible_room_names[4] = "SUMMER";
     possible_room_names[5] = "Radio";
     possible_room_names[6] = "Montana";
     possible_room_names[7] = "FAMILY";
     possible_room_names[8] = "MOONS";
     possible_room_names[9] = "rain";
 
}

///###############################################################################################
///############################# FUNCTION TO CREATE FILE DIRECTORY ##############################
//###############################################################################################
// Description:	This function is designed to create the directory with the passed in reference of
//				dirName. It will then grab the current session PID and to be used in the directory
//				name creation. When it's complete it will create ./kramerj.room.pid#/
// Why:			The assignment specifically called for a directory like this to be made with the PID
//				I decided to code it this way, because I could concisely form this process into a function
void creatNewDirectory(char dirName[]) {
    
    int pid = 0;
    pid = getpid(); // This gets the PID
    char str[50];
    sprintf(str, "%d", pid); // This copies the integer pid into a string
    
    // This code will create the kramerj.room.pid#
    strcpy(dirName, "./kramerj.rooms.");
    strcat(dirName, str);
    strcpy(str, "/");
    strcat(dirName, str); // this offically creates ./kramerj.room.pid#/
    
    mkdir(dirName, ACCESSPERMS);    
}

///###############################################################################################
///########################### FUNCTION TO WRITE ROOM NAME TO FILE ############################
//###############################################################################################
// Description: This write the passed in file_name as the actual file name. It will open the previously
// 				created directory, so all the files can be created in it.
// Why:			This is an assignment acquirement to have all files created in a directory. I decided
//				to make separate the code into a function because it gets called many times.
void writeRoomNameToFile(char *file_name, char dirName[]) {
    
    chdir(dirName);
    FILE * fp;
    fp = fopen(file_name, "w+");
    fputs("ROOM NAME: ", fp);
    fputs(file_name, fp);
    fputs("\n", fp);
    
    fclose(fp);
}


///###############################################################################################
///#################### FUNCTION TO READ IN CONNECTIONS FROM THE FILE  ############################
//###############################################################################################
// Description:	This will read in the file name array, the index from the calling functions calling for-loop,
//				the the file pos of from the calling function. It will then update the file pos pointer
//				to the "CONNECTION" section and read in the data form there. The purpose here is to update
//				the Room struct the idea of this function is turn Rooms[i].Connected[j].connect_room,
//				into usable data.
// Why:			I designed this this way to utilize the calling for-loop to add data into the struct. I needed
//				to keep Room[i] steady as I looped through Connected[j. Therefore I built this function around
//				the fact that it was called by another function that was called by a for-loop. This allowed means
//				to have control over the i index and loop through with a j index.
void readInConnectionsFromFile(char *fname, int i, int pos) {
    
    FILE * fp;
    fp = fopen(fname, "r");
    fseek(fp, pos, SEEK_SET); // sets the file pointer to beginning of "Connections" in the file
    
    // junk holds garbage data and connection holds the connections between files.
    char junk2[15], connection[100];
    int j;
    for (j = 0; j < MAX_CONNECTIONS_ADD_TO_FILE; j++) {
        fgets(junk2, sizeof junk2, fp); /* expect string like "title: TITLE WITH SPACES" */
        fgets(connection, sizeof connection, fp); /* expect string like "title: TITLE WITH SPACES" */
        strcpy(Rooms[i].Connected[j].connect_room, connection); // This works
    }
    fclose(fp);
}


///################################################################################################
///################### FUNCTION TO READ IN DATA FROM THE FILE AND SET THE NAME #####################
//################################################################################################
// Description:	This will read in the file name array and the passed in index of i. The purpose is
//				to use i from the calling for-loop as the anchor to the struct that is being manipulated
//				i.e. if i=0, then Room[0].name = "some_name" and this cycles through updating the name
//				and the conenct_id. Which is used to like and ID in a database, to simply attach a unique
//				number to the name.
// Why: 		This is designed this way because I wanted to enter data into the structs via
//				a loop and I need a way to make sure Room[i] was completely done, before moving onto
//				the next. It is more prevalent in the function readInConnectionsFromFile
void readInDataFromFile(char * fname, int i) {
    
    FILE * fp;
    int pos; // file pointer
    fp = fopen(fname, "r");
    
    //// GETS THE NAME
    char junk1[12], name[100];
    fgets(junk1, sizeof junk1, fp); // reads in the data I don't need from the file
    fgets(name, sizeof name, fp); // reads in data I need from the file
    pos = ftell(fp);
    strcpy(Rooms[i].name, name); // This works
    
    // This is to track where in the order this struct is.
    // 0 is obviously the first and MAX_CONNECTIONS is the last
    Rooms[i].connect_id = (i);
    
    fclose(fp);
    readInConnectionsFromFile(fname, i, pos);
}


///###############################################################################################
///########### FUNCTION TO CYCLE THROUGH FILE AND VERIFY IF READY TO APPENED A CONNECTION ##########
//###############################################################################################
// Description:	This function will cycle through a file to look for the passed in room name. If it doesn't
//				find the name, then it will return a -1 meaning this room_to_find varaible can be added
//				as a connection. Otherwise if it finds the connection it will return a 0 and nothing will
//				be added.
// Why:			I needed a way to search the file to see if the room I needed to find was in the string
//				then I could take that info and decide to write the data to the file or not.
int searchInFile(char *fname, char **room_to_find) {
    
    FILE *fp;
    int find_result = 0;
    char temp[512];
    int connection_counter = 0;
    
    // If can't open file, print return -1
    if ((fp = fopen(fname, "r")) == NULL)
        return (-1);
    
    // this code searches for the line the word is on...
    while (fgets(temp, 512, fp) != NULL) {
        connection_counter++;
        // This loads entire file line into the temp array
        if ((strstr(temp, room_to_find[0])) != NULL) {
            //Close the file if still open.
            if (fp)
                fclose(fp);
            return (-1); // return zero only if string is found
        }
    }
    
    if (find_result == 0)
        return (connection_counter);
    
    //Close the file if still open.
    if (fp)
        fclose(fp);
    
    return (-1);
}


///###############################################################################################
///########################## FUNCTION TO WRITE CONNECTIONS TO THE FILE ###########################
//###############################################################################################
// Description: This function will read in the the verified file and room_name from the searchInFile function.
// 				From there it simply opens the file name. Appends the connection_couter which has been
//				incremented each time a new connection has been made. This allows the file to be written such as:
//				CONNECTION 1 ... CONNECTION 4..
// Why:			This was the most efficient way I could think of write to the file. I would first verify
//				if the connection already existed and if it didn't then I would add it. I would keep adding
//				connections until MAX_CONNECTIONS was reached.
void appendConnectionsToFile(char *file_name, char **room_to_find, int connection_counter, int i) {
    
    char str[50]; // Used as a holder
    sprintf(str, "%d", connection_counter); // This copies the integer connection_counter into a string
    FILE * fp3;
    fp3 = fopen(file_name, "a+");
    fputs("CONNECTION ", fp3);
    
    fputs(str, fp3);
    fputs(": ", fp3);
    fputs(room_to_find[0], fp3);
    fputs("\n", fp3);
    fclose(fp3);
}


///###############################################################################################
///################### FUNCTION IS USED TO ASSIST IN ADDING CONNECTIONS ######################
//###############################################################################################
// Description: This is more of a helper function it is designed around a for-loop to make sure
//				appendConnectionsToFile is given the correct data to append the files with and to 
//				verify that if a connection is given on one file, then it must check if that same connection
//				is on the other file; and if not, then add it. It has a connection counter so it can keep 
//				track of the connections made and make sure it is appended to the file in the form of room size. 
// Why:			I needed a way to prepare the data for the appendConnectionsToFile function. This
//				function is the hub for taking the choosen_room_names and the room_to_find, calling
//				the searchInFile function and then from there calls the appendConnectionsToFile. This
//				functions handles the management of that process.
void addConnectionsManager(char **chosen_room_names, char **room_to_find) {
    
    int i, j, p;
    int connection_counter = 0;
    int random_nums[9];
    
    // This is here to hold the selected connection rooms and baseline room. 
    char **chosen_room_names_i_holder = malloc(500 * sizeof(char * ));
    char **room_to_find_holder_j_holder = malloc(500 * sizeof(char * ));
    char **transfer_temp_holder = malloc(500 * sizeof(char * ));    
    
	// creates the size of the strings   
    for (i = 0; i < 9; i++) {
        chosen_room_names_i_holder = malloc(500 * sizeof(char * ));
        room_to_find_holder_j_holder = malloc(500 * sizeof(char * ));
        transfer_temp_holder = malloc(500 * sizeof(char * ));        
    }
    
    int new_rand[4];
    int random_connections_amount;
    
    // This for-loop will add connections between the files.
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        connection_counter = 0;
		delayTime();
        randomGen(random_nums);
        
        //First we need to create a random num for connections 3 - 4        
        int h = 0;
        for (p = 0; p < 10; p++) {
            if ((random_nums[p] < 5 &&  random_nums[p] > 2)) {
                new_rand[h] = random_nums[p];
                h++;
            }
        }        
        /// End create random num
        
        //NOW I NEED TO ADD THE FIRST CONNECITON
		// This codes loads a random number form the array. 
        random_connections_amount = new_rand[1];      
        
        for (j = 0; j < random_connections_amount; j++) {
            // I hard coded room_to_find to [0] because all I need is just a holder
            room_to_find_holder_j_holder[0] = chosen_room_names[j];
            chosen_room_names_i_holder[0] = chosen_room_names[i];
            
            //Entering the search function
            connection_counter = 0;
            // Using choosen_room_names[i] because I am searching the original file.
            connection_counter = searchInFile(chosen_room_names_i_holder[0], room_to_find_holder_j_holder);
            
            // If not equal to zero that means a connection can be added
            if (connection_counter != -1) {
				// The connection counter is also used in determining the size of each room. 
				// The number of connections == the size of the room. 
                Rooms[i].size = connection_counter;
                appendConnectionsToFile(chosen_room_names_i_holder[0], room_to_find_holder_j_holder, connection_counter, i);                
            }
            
            //FLIP FLOP TIME!!!
			// This block of code flips the room_to_find_holder_j_holder and chosen_room_names_i_holder around
			// so it can be re-ran through the same functions, but this time opposite. I do this, so that when I 
			// I add a connection from the above code, it would now flip that connection around and see if the other
			// room is connected and if it isn't then add the connection. 
            transfer_temp_holder[0] = room_to_find_holder_j_holder[0];
            room_to_find_holder_j_holder[0] = chosen_room_names_i_holder[0]; // this flips
            chosen_room_names_i_holder[0] = transfer_temp_holder[0];
            connection_counter = 0;
            //END FLIP FLOP TIME
			
			// These final lines of code add connections to rooms and increment room sizes. 
            connection_counter = searchInFile(chosen_room_names_i_holder[0], room_to_find_holder_j_holder);
               
            // If not equal to zero that means a connection can be added
            if (connection_counter != -1) {
                Rooms[j].size = connection_counter;
                appendConnectionsToFile(chosen_room_names_i_holder[0], room_to_find_holder_j_holder, connection_counter, i);
            }            
        }
    }
}


///###############################################################################################
///####################### FUNCTION TO ADD ROOM TYPE: START, MID, END ###########################
//###############################################################################################
// Description: This function will append to the end of the file the type of file it is, such as
//				START_ROOM or END_ROOM. This function uses the passed in file name to open the file and
//				and the calling loop functions index to place it into the appropriate file. For example
//				since the choosen_room_names is an array I know where the start_room can be. I'll make it
//				choosen_room_names[0] and the end_room will be choosen_room_names[MAX_CONNECTIONS-1]
// Why:			I wanted to easily loop through and add all assignment required data as easily and as
//				efficiently as possible. I thought that utilizing arrays and loops to control their potions
//				I would know their ultimate position and would make manipulating them easier.
void appendStartAndEndToFile(char *file_name, int i) {
    FILE * fp3;
    fp3 = fopen(file_name, "a+");
    
    if (i == 0)
        fputs("ROOM TYPE: START_ROOM\n", fp3);
    else if (i == MAX_CONNECTIONS - 1)
        fputs("ROOM TYPE: END_ROOM\n", fp3);
    else
        fputs("ROOM TYPE: MID_ROOM\n", fp3);
    fclose(fp3);
}


///###############################################################################################
///####################### FUNCTION USED AS AN INITIAL DISPLAY ###########################
//###############################################################################################
// Description: This function gives the initial display. It's called initial because it's hard coded to
//				display the START_ROOM first which is Room[0].names. So the point here is to display
//				the beginning choices to the user
// Why:			I needed a way to beginning the display to the user and because I have designed the program to
//				to place START_ROOM room in the same spot all the time, it made sense to just hard code
//				array location 0 and display from there
void initialDisplayToUser() {
    printf("CURRENT LOCATION: %s", Rooms[0].name);
    printf("POSSIBLE CONNECTIONS: ");
    int size = Rooms[0].size;
    int new_rand[10];
    
    int i, j;
    char temp[256];
    char space[256];
    char comma[256];
    strcpy(space, " ");
    strcpy(comma, ",");
    
    // **************** BEGIN RE-RANDOMIZE ***************************
	// this code will randomly generate the display of rooms to the user
    int random_nums[10];
    randomGen(random_nums);
    
    int h = 0;
    int p;
    for (p = 0; p < 10; p++) {
        if (random_nums[p] < size) {
            new_rand[h] = random_nums[p];
            h++;
        }
    }
	//*********** END RE-RANDOMIZE *********************
	
    for (i = 0, j = 0; i < Rooms[0].size; i++) {
        // Reads in the name only
        if (i == 0) {
            strcpy(temp, Rooms[j].Connected[new_rand[i]].connect_room);
            temp[strlen(temp) - 1] = '\0';
            strcat(temp, comma);
            strcat(temp, space);
        }
        // Reads in the very end
        else if (i == (Rooms[0].size -1)) {
            strcat(temp, Rooms[j].Connected[new_rand[i]].connect_room);
            temp[strlen(temp) - 1] = '\0';
        }
        // Reads in all the connections.
        else {
            strcat(temp, Rooms[j].Connected[new_rand[i]].connect_room);
            temp[strlen(temp) - 1] = '\0';
            strcat(temp, comma);
            strcat(temp, space);
        }
    }
    printf("%s", temp);
    printf(".\n");
}


///###############################################################################################
///####################### FUNCTION USED TO FIND MATCHING ROOMS ###########################
//###############################################################################################
// Description: This function will take in user entered in room via temp and will then compare it
//				to all the room names in the Rooms struct until it finds the room. It will then return
//				the id which is the array location or it will return a -1 indicating it did not find it.
// Why:			I designed it like this because I needed a simple way to cycle through the struct and
//				compare the user entered data to the struct name data.
int searchForMatchingRoom(char *temp) {
    int i;
    for (i = 0; i < MAX_CONNECTIONS_ADD_TO_FILE + 1; i++)
        if (strcmp(temp, Rooms[i].name) == 0) {
            int id = Rooms[i].connect_id;
            return id;
        }
    return -1; // it did not find the searched item
}


///###############################################################################################
///################### FUNCTION IS USED TO DISPLAY ROOM NAME AND CONNECTION# ######################
//###############################################################################################
// Description: This function is used to display the room name and all the connections each time the
//				user successfully enters a name that exists in the game. The function is designed around
//				and id which is just a location in an array, but it allows for a great way to track
//				where the user is at and what to display.
// Why:			I needed function to work with my logic from the main calling function. So that once
//				the data was verified it could bounce down my if-statement logic and now matter where
//				it landed it would always call this function. Making it easy to code, plus I could use
//				the id system to track where I need to print to screen via the Rooms struct.
void displayRoomOptionsToUser(int id) {
    
    printf("\nCURRENT LOCATION: %s", Rooms[id].name);
    printf("POSSIBLE CONNECTIONS: ");
    int i;
    char temp[256];
    char space[256];
    char comma[256];
    strcpy(space, " ");
    strcpy(comma, ",");    
    
    // **************** BEGIN RE-RANDOMIZE ***************************
    // this code will randomly generate the display of rooms to the user
    int random_nums[10];
    randomGen(random_nums);
    int new_rand[10];
    int h = 0;
    int p;
    int size = Rooms[id].size;
    // This for-loop is designed to cycle through the random_nums array and place digits between
    // 0 and 5 in the new_rand array. This ensures that ever time the display function is called
    // the room order will be random.
    for (p = 0; p < 10; p++) {
        if (random_nums[p] < size) {
            new_rand[h] = random_nums[p];
            h++;
        }
    }
    //*********** END RE-RANDOMIZE *********************
    
    for (i = 0; i < Rooms[id].size; i++) {
        // Reads in the name only
        if (i == 0) {
            strcpy(temp, Rooms[id].Connected[new_rand[i]].connect_room);
            temp[strlen(temp) - 1] = '\0';
            strcat(temp, comma);
            strcat(temp, space);
        }
        // Reads in the very end
        else if (i == (Rooms[id].size - 1)) {
            strcat(temp, Rooms[id].Connected[new_rand[i]].connect_room);
            temp[strlen(temp) - 1] = '\0';
        }
        // Reads in all the connections.
        else {
            strcat(temp, Rooms[id].Connected[new_rand[i]].connect_room);
            temp[strlen(temp) - 1] = '\0';
            strcat(temp, comma);
            strcat(temp, space);
        }
    }
    printf("%s", temp);
    printf(".\n");
}


///###############################################################################################
///################ FUNCTION IS USED TO MANAGE ALL DISPLAY TO USER PROCESSES #####################
//###############################################################################################
// Description: This function is designed to handle all processes to the user. It will call and
//				manage all display functions. It's built with loops in mind, as my whole program is,
//				to cycle through what the user entered and if it matches what's in the structs. It
//				process reading in the users input, searching the input for a match, taking the
//				returned match data and through a series of if statements it will determine if
//				the user entered data is the END_ROOM, the room they are already in, or if it's a new
//				room and it should re-call displayRoomOptionsToUser again.
// Why:			I made this to clean up the main() function. It also made the code more readable and easier
//				to understand when it is broken into section.  I designed it as a master function so
//				I could manage all other process through here. It is designed to be a central hub for displaying
//				data to the user and processing display logic.
void masterDisplayProcessManager(){
    
	// First display to the user. Basically the START_ROOM
    initialDisplayToUser();
	
    char temp[256];
    int doneFlag = 0; // when equal to zero the user found the end_event
    int firstRun = 0; // this is to track when the user inputs a wrong room name
    int previous_foundIt = 0;
    int path_track_counter = 0;
    int i;
    
    while (doneFlag != 1) {
        printf("WHERE TO? > ");
        fgets(temp, 255, stdin);
        int foundIt = searchForMatchingRoom(temp);
        
        // If foundIt == MAX_CONNECTIONS-1 then the user selected the END_ROOM
        if (foundIt == (MAX_CONNECTIONS - 1)) {
            
            // Copy in the room name into the tracker.
            strcpy(pathTaken.find[path_track_counter].track_path, temp);
            path_track_counter++;
            
            printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
            printf("YOU TOOK %i STEPS. YOUR PATH TO VICTORY WAS: \n", path_track_counter);
            
            for (i = 0; i < path_track_counter; i++)
                printf("%s", pathTaken.find[i].track_path);
            
            exit(0);
        }
        
        if (foundIt >= 0) {
            // means the user selected the room they are in and it should not be counted in their steps
            // because how can you walk into a room you're already in? Philosophy 101.. umm no thanks I'll pass!
            if (firstRun == 0 && foundIt == 0) {
                firstRun++;
                previous_foundIt = foundIt;
                displayRoomOptionsToUser(foundIt);
            }
            // Making sure it's not the room the user is already in
            else if (foundIt == previous_foundIt) {
                previous_foundIt = foundIt;
                firstRun++;
                displayRoomOptionsToUser(foundIt);
            }
            // If logic made it here, means the user entered in the correct room_name
            else {
                previous_foundIt = foundIt;
                firstRun++;
                displayRoomOptionsToUser(foundIt);
                // This will add the users chosen path into the pathTaken struct.
                strcpy(pathTaken.find[path_track_counter].track_path, temp);
                path_track_counter++;
            }
        }
        // Found it returned a -1 and now it's here in the logic.
        else {
            printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
            
            // This is used only if the user enters in wrong info on the initial display
            // of choices.
            if (firstRun == 0)
                displayRoomOptionsToUser(0); // this will just re-display the original info
            
            // This is used if the user entered in a wrong choice and it's not the inital
            // display. It will display their selections again, by passing in the
            // previous_foundIt, which holds the location to the their current room.
            else {
                displayRoomOptionsToUser(previous_foundIt);
                firstRun++;
            }
        }
    }
}


///###############################################################################################
///################################### MAIN FUNCITON ############################################
//###############################################################################################
// Description: This is the master calling function. It calls and directs the entire program. At first
// 				it sets variables and declares their sizes. From there it creates the room names, write the rooms names,
// 				creates the connections, and creates the events to file. Then it calls for the file data to be loaded into
// 				structs. Form there the struct data is read to the user and the final masterDisplayProcessManager handles
// 				all process to the user. 
// Why:			The simplest way for me write a program is to have main only used for calling other functions 
// 				and preparing variables. It can't always be like that, but it makes it easier to manage when it is. 
int main() {
    char dirName[256];
    int random_nums[9];
    creatNewDirectory(dirName); // Creates the new directory for the files
	delayTime();
    randomGen(random_nums);  // Creates random numbers and loads them into random_nums
    
    // Code to create a string for the possible room names.
    char **possible_room_names = malloc(500 * sizeof(char * ));
    char **chosen_room_names = malloc(500 * sizeof(char * ));
    char **room_to_find = malloc(500 * sizeof(char * ));
    
    // creates the size of the strings
    int i = 0;
    for (i = 0; i < 9; i++) {
        possible_room_names[i] = malloc((500) * sizeof(char));
        chosen_room_names[i] = malloc((500) * sizeof(char));
        room_to_find[i] = malloc((500) * sizeof(char));
    }
    
    // This function loads the rooms names into the possible_room_names array
    createPossibleRoomNames(possible_room_names);
    
    // This for-loop will write the files names according to the random numbers
    // it will also place the chosen names in chosen_room_names arary
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        chosen_room_names[i] = (char * ) strdup(possible_room_names[random_nums[i]]);
        writeRoomNameToFile(chosen_room_names[i], dirName);
    }
    
    // The proceeding code creates and appends the connections to the files. It is based
    // off of for-loops because after storing the random numbers and creating the
    // initial files off of those random numbers, I now know the file names and their
    // location, so I can logically cycle through and add in the connections based
    // off of their location according to the randomly generated number. For example:
    // the first randomly generated number may be 5, but it's stored at random_nums[0]
    // and because of that I know all the file locations.
    // This code will cycle through each file and append CONNECTIONS and then at the end
    // re-cycle through to add START, MID, and END.  
    
    // This function will help add connections between files.
    addConnectionsManager(chosen_room_names, room_to_find);
    
    // This for-loop will cycle through the choosen_room_names and append START
    // if int i == 0  and MID if i == 1 to (MAX_CONNECTIONS-2) and END if
    // i == (MAX_CONNECTIONS-1)
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        appendStartAndEndToFile(chosen_room_names[i], i);
    }
    
    // This code uses the rooms struct and then loops through 6 times
    // to create memory space for the name and events
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        // passing choosen_room_names for each file that needs to be opened and
        // read in, plus passing the i, because it is used for the for-loop to enter
        // in the connections to the struct.
        readInDataFromFile(chosen_room_names[i], i);
    }
    
    // The code underneath is commented out, but saved because it can display the exact exit strategy and
    // it helped with debugging
    /*
     for (i = 0; i < MAX_CONNECTIONS; i++) {
     printf("The connections are Rooms[%i].name = %s and connect_id = %i\n", i, Rooms[i].name, Rooms[i].connect_id);
     }
     */
    
    // At this point in the program, all the files have been created and loaded into
    // the struct data structure. From here it will interact with the user, by calling
    // the masterDisplayProcessManager function.
    masterDisplayProcessManager();
}







































