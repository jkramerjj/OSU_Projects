// Programmer: Joseph Kramer
// DATE: 5-24-15


#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#define CHAR_MAX 512 


// I decided to use structs again as my data structure similar to assignment #2. I must say, I'm
// glad I took the time in assignment #2 to learn structs, because it was helpful in that assignment
// and very helpful in this assignment. I use the sentinel struct as flags for the if statements and 
// the process data struct to contain parsed info, such as file names, ect. It made it much more 
// convenient to manage data. 

// This struct is the data-structure that handles boolean sentinels of what the user entered	
struct Sentinel 
{
    bool readInFile;  					// Used to indicate "<" is used
    bool writeOutFile; 					// Used to indicate ">" is used
    bool runInBackground;  				// Used to indicate if "&" is used
	int inputOutputDecision;			// Used as another sentinel where 0 is for background, 1 is for input,
										// & 2 is for output
};


// This struct is the data-structure that handles the processing and managing of data.
struct Process_Data 
{
    char initialData[CHAR_MAX];    		// Used to hold all un-processed data
    char *parsedCommand[CHAR_MAX];  	// Used to hold all parsed commands
    char *readInFileName;        		// Used to hold the filename when "<" is used
    char *writeOutFileName;      		// Used to hold the filename when ">" is used
};


///###############################################################################################
///####################### FUNCTION TO RETRIVE AND PROCESS THE STDIN ###########################
///###############################################################################################
// Description: This function will read in the users commands and store that data into the struct
// 				for initialData. From there it will remove the tailing \n and replace it with \0
// Why:			I needed a way to process what the user entered and remove the "\n". I found that 
//				taking the length of the STDIN and subtracting one was the easiest way to remove
//				the "\n"
void processSTDIN(struct Process_Data *decisionData)
{
    fgets(decisionData->initialData, CHAR_MAX, stdin);
    unsigned long len = strlen(decisionData->initialData);
    
    // This is done to remove the \n from STDIN
    if (decisionData->initialData[len-1] == '\n')
        decisionData->initialData[len-1] = '\0';
}


///###############################################################################################
///####################### FUNCTION TO PARSE AND PROCESS STDIN ###########################
///###############################################################################################
// Description: This function will parse STDIN. Initially it will look for redirection indicators. Then it
//				will search for a filename or argument commands. It is designed as a while loop, to cycle through
//				until the data has been parsed.
// Why:			I needed a way to cycle through whatever the user entered. In the real world I would have little
//				control over what a user entered, so I thought cycling through the data with a not NULL flag to exit was the
//				best idea. Granted this is an assignment and I know the test-files contents.
void parseSTDIN(struct Process_Data *decisionData, struct Sentinel *decisionSentinel)
{
    // Used where sentinel 0 is for background, 1 is for input, & 2 is for output
    decisionSentinel->inputOutputDecision = -1;	
	
    int counter = 0;		// Used to keep track of the number of parsed arguments
    char *parsedData = strtok(decisionData->initialData, " "); // Used to hold the parsed data
    while (parsedData != NULL) 
	{        
        // This block is used to determine what direction decision the user made in the shell.
        // If they wanted to input, output, or background.
        if (strcmp(parsedData, "<") == 0) 
		{
            decisionSentinel->inputOutputDecision = 1;
            decisionSentinel->readInFile = true;
        }
        else if (strcmp(parsedData, ">") == 0) 
		{
            decisionSentinel->inputOutputDecision = 2;
            decisionSentinel->writeOutFile = true;
        }
        else if (strcmp(parsedData, "&") == 0) 
		{
            decisionSentinel->inputOutputDecision = 0;
            decisionSentinel->runInBackground = true;
        }
        
        // If the logic made it here then either a filename is stored and command argument
        else 
		{            
            if(decisionSentinel->inputOutputDecision == 1)
                decisionData->readInFileName = parsedData;
            else if (decisionSentinel->inputOutputDecision == 2)
                decisionData->writeOutFileName = parsedData;
            else 
			{
                decisionData->parsedCommand[counter] = parsedData;  // Adds the parsed data
                counter++;
                decisionData->parsedCommand[counter] = NULL;  	// Used this to stop random errors.
				decisionSentinel->inputOutputDecision = 10000; 	// Set to an outrageous number to indicate that the user
																// did not just hit enter
            }
        }
        parsedData = strtok(NULL, " "); // end of whileloop cycle, used to get next data.
    }
}


///###############################################################################################
///############################ FUNCTION TO PROCESS COMMANDS ##################################
///###############################################################################################
// Description: This function will determine if the command is to write or read a file or if it
//				needs to run in the background. It will simply use the sentinels to determine if a 
//				a file needs to be written or read. Then the file descriptors are processed depending
//				on which sentinel was flagged. It process and handles file descriptor I/O. The function 
//				will then call execvp to actually execute everything. 
// Why:			This is done because I needed a centralized function to handle the redefining of standard
//				input and output streams. I also needed to handle the write and read
//				commands. From here I could create the file or read in, plus run in the background.
// 				I needed to be able to handle file descriptors, therefore the use of dup2.
// Sources:		https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/dup2.html 
void processCommand(struct Process_Data *decisionData, struct Sentinel *decisionSentinel)
{
    // Used if a file must be created and written to.
    if (decisionSentinel->writeOutFile) 
        // This is used to create / open the filename passed into the shell and to redirect it.
        dup2(open(decisionData->writeOutFileName, O_CREAT | O_WRONLY, 0755), 1);    
    
    // Used if a file must be read in.
    if (decisionSentinel->readInFile) 
        // Used to redirect the STDIN
        if (dup2(open(decisionData->readInFileName, O_RDONLY), 0) == -1) 
		{
            perror("error");
            exit(1);
        }
    
    else if (decisionSentinel->runInBackground) 
        // Used to open dev/null and redirect for STDIN
        dup2(open("/dev/null", O_RDONLY), 0);
    
    
    // Used to execute the decisionData
    // source: http://www.cs.ecu.edu/karl/4630/sum01/example1.html
    execvp(*decisionData->parsedCommand, decisionData->parsedCommand);
    
    // If the logic made it here then there was an error
    perror("error");
    exit(1);
}


///###############################################################################################
///################## FUNCTION TO PROCESS WAIT COMMANDS AND TERMINATIONS ########################
///###############################################################################################
// Description: The beginning of the function creates a status variable as was indicated via the
//				lectures to processing waitpid. Waitpid is of-course in the beginning of the function
//				for the purpose of updating the status variable and handling the foreground process.
//				From there, there are two if statements that handle if the process is ended by a
//				signal or normally.  They will create a string indicating what happened.
// Why:			I needed a way to handle the known signals I would receive. I first made the
//				"WIFSIGNALED", because I know a ^C single would be sent. Then I made the "WIFEXITED"
//				to basically handle everything else.
void signalProcessing(char *displayHolder, pid_t pid)
{
    int status = 0;
    waitpid(pid, &status, 0); 	// Used to wait for state change
    
    // Used for ending child processes via a signal.
    if (WIFSIGNALED(status)) 
	{        
        int reasonCode = WTERMSIG(status);
        //printf("\n\n\n\n ##### THE WTERMSIG REASON CODE IS ##### == %d\n\n\n\n", reasonCode);
        printf("Ended with a signal of ** %d  **\n", reasonCode);
    }
    
    // Used when everything ends normally.
    if (WIFEXITED(status)) 
	{
        int reasonCode = WEXITSTATUS(status);
        char strHolder[CHAR_MAX];
        strcpy(displayHolder, " Ended with an exit status of ** ");
        
        // This copies the integer reasonCode into a string
        sprintf(strHolder, "%d", reasonCode);
        
        strcat(displayHolder, strHolder);
        strcat(displayHolder, " ** \n");
    }    
}


///###############################################################################################
///############################### FUNCTION TO PROCESS ZOMBIES ##################################
///###############################################################################################
// Description: The purpose of this function is to end all zombie child processes. WIFSIGNALED is used 
//				to look for a signal sent into the shell and WIFEXITED is used to for normal exits. 
//				This function will constantly be ready if a signal is used, plus if a signal is not 
//				used. 
// Why:			Every-time the while cycled I needed to check if there were zombies. I used this
//				function to first check for a signal, because I knew a signal would be sent via
//				the grading script. Plus I also needed to handle zombies that were not created by
//				a signal. In the end this small block of coded handled what the assignment required,
//				because it processed zombies that were created by a signal and normally.
// Source: 		http://www.gnu.org/software/libc/manual/html_node/Process-Completion.html
void processZombies() 
{
    pid_t cpid; 	// Used to hold the child pid
    int status;
    
    // Used to gather zombies
    if ((cpid = waitpid(WAIT_ANY, &status, WNOHANG)) > 0) 
	{        
		// Used for child process via a signal 
        if (WIFSIGNALED(status)) 
		{
            int reasonCodeSignaled =  WTERMSIG(status);
            printf("Ended with a signal of ** %d ** \n", reasonCodeSignaled);
        }
        
        // This child zombie ended in a normal manner.
        if (WIFEXITED(status)) 
		{
            int reasonCodeExited = WEXITSTATUS(status);
            printf("Ended with a exit status of ** %d **\n", reasonCodeExited);
        }
    }
}


///###############################################################################################
///################################### MAIN FUNCITON ############################################
//###############################################################################################
// Description: This is the master calling function. It calls and directs the entire program. At first
// 				it sets variables and then begins the whileloop. Within the while loop is all the logic
//				to work the shell. It is essentially a series of if statements ran off of structs, that if
//				engaged will call corresponding functions.  While the loop is in existence, the shell will
//				continue, otherwise it's over.  
// Why:			I designed it this way, because it was the simplest way I could see managing the flow of a 
//				shell. Because I knew the shell could only exit with a command, I figured I would keep all 
//				logic and processing within the while loop. I then designed it to first read in, then parse,
//				then decided what to do with the parsed data. Such as run a background process or not. 
// Sources: 	http://www.linuxprogrammingblog.com/code-examples/sigaction
// Sources: 	http://www.gnu.org/software/libc/manual/html_node/Basic-Signal-Handling.html

int main(void)
{
    char displayHolder[CHAR_MAX];     			// Used to hold the status of the foreground exit
    struct Process_Data decisionData;         	// Used to process the user in-putted commands.
    struct Sentinel decisionSentinel;			// Used to process the users choices
    
    // I used the sources listed in the description to develop the fundamental building blocks
    // here to handle signal processing.
    struct sigaction defaultAction; 			// Default Action signal handler
    struct sigaction ignoreAction; 				// Ignore action signal handler
    memset (&defaultAction, '\0', sizeof(defaultAction));
    memset (&ignoreAction, '\0', sizeof(ignoreAction));
    defaultAction.sa_handler = SIG_DFL;			// Used to create a default action for the signal
    ignoreAction.sa_handler = SIG_IGN; 			// Used to ignore signals
    sigaction(SIGINT, &ignoreAction, NULL);		// Used to ignore un-wanted signals    
    
    while (1) 
	{        
        fflush(stdout);
        printf(": ");
        strcpy(decisionData.initialData, "exit"); // Used as a default measure here to make sure the program can exit
        processSTDIN(&decisionData);
        
        // Used to reset I/O sentinels before calling parseSTDIN
        decisionSentinel.writeOutFile = false;
        decisionSentinel.readInFile = false;
        decisionSentinel.runInBackground = false;
        
        // Used to parse the STDIN
        parseSTDIN(&decisionData, &decisionSentinel);
		
		// The following section of code will will go through the now parsed data and
        // decided what to do, based on what was parsed. The logic is a series of if statements
        // looking for what the assignment requested. i.e. comments, exit, cd, status, forking, ect..		
		
		// Used for "#" and if the user just enters "enter"
		if (decisionSentinel.inputOutputDecision == -1 || **decisionData.parsedCommand == '#') 
		{
			int junk=0; // this is here to move the logic along, break will not work because it jmps out of the while loop
		}
		
        // Used for "exit"
        else if (strcmp(decisionData.parsedCommand[0], "exit") == 0) 
            exit(0);
		
        // Used for "cd"
        else if (strcmp(decisionData.parsedCommand[0], "cd") == 0) 
		{            
            if(decisionData.parsedCommand[1] == NULL)
                chdir(getenv("HOME"));
            else if (chdir(decisionData.parsedCommand[1]) == -1)
                perror("cd");
        }
		
        // Used for "status".
        else if (strcmp(decisionData.parsedCommand[0], "status") == 0) 
            printf("%s", displayHolder);
		
        // Used to facilitate executing parsed decisionData via child process.
        else  
		{
            pid_t cpid;
            cpid = fork();
            
            if(cpid == 0) 
			{
                sigaction(SIGINT, &defaultAction, NULL);
                
                // Process the command from decisionData
                processCommand(&decisionData, &decisionSentinel);
            }
            else if (cpid > 0) 
			{
                // Used to display new PID
                if (decisionSentinel.runInBackground)
                    printf("The new background pid is == ** %d ** \n", cpid);
                
                // Used to wait for child process in the foreground.
                else
                    signalProcessing(displayHolder, cpid);
            }
			// If made it here, then there was an error. 
            else 
			{            
                perror("error");
                exit(1);            
            }
        }
        // Used for zombies
        processZombies();
    }
}





















