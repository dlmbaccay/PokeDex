/*********************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and applying 
the concepts learned. We have constructed the functions and their respective algorithms and corresponding 
code by ourselves. The Program was run, tested, and debugged by our own efforts. We further certify that we have 
not copied in part or whole or otherwise plagiarized the work of other students and/or persons.

DOMINIC LUIS M. BACCAY, DLSU ID#12108173
BIEN AARON C. MIRANDA, DLSU ID#12106773
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#define ENTRYMAX 150
#define NAMEMAX 21
#define DESCMAX 51

typedef char String[21]; // utilized by researchTask functions

struct pokemonstruct
{
    int entry;
    char cPokeName[NAMEMAX];
    char cPokeType;
    char cPokeDesc[DESCMAX];
    int nResearchType[5];
};

// homeMenu functions
void welcomeMenu();
void homeSelection();
void manageDataMenu();
void researchTaskMenu();

// manageData functions
int Search(char key[], int nPkCtr, struct pokemonstruct pokemon[]); // search function, strings only, checks if duplicate names are present
int addEntry(int i, struct pokemonstruct pokemon[]); // add entry function
void modifyEntry(int nPkCtr, struct pokemonstruct pokemon[]); // modify entry function
int deleteEntry(int nPkCtr, struct pokemonstruct pokemon[]);  // delete entry function
void displayEntry(int i, struct pokemonstruct pokemon[]); // utilized by modifyEntry()
void displayAllEntries(int nPkCtr, struct pokemonstruct pokemon[]); // display all entry function
void displaySearchEntry(int nPkCtr, int i, struct pokemonstruct pokemon[]); // display all search name and type entries
void searchPokeByName(int nPkCtr, struct pokemonstruct pokemon[]); // searches Pokemon by their names, or if the input is a part of their name
void searchPokeByType(int nPkCtr, struct pokemonstruct pokemon[]); // searches Pokemon by their type
void export(int nPkCtr, struct pokemonstruct pokemon[]); // exports PokeDex entries made by user in the duration of the execution
int import (int nPkCtr, struct pokemonstruct pokemon[]); // imports PokeDex entries from .txt files
int searchImport(char key[], int nPkCtr, struct pokemonstruct pokemon[]); // utilized by import(), to find index of existing entry

// researchTask functions
void researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[]); // displaying all entries (with name only)
void researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr, String sRsrchName[]); // displays entry alongside its research task types
void reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]); // Review Research Task per Pokemon
void displayResTaskType(int nRsrchCtr, String sRsrchName[]); // displays the lists of Research Task Types
void reviewResearchPerType(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]); // Review Research Task per Task Type
void updateResearchTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]); // Update Research Task
void displayEntryByResTaskType(int i, struct pokemonstruct pokemon[], int inType, String sRsrchName[]); // displays entry alongside its designated research task type

// design functions
void boxMaker(int tbLeft, int tbRight, int yTopHor, int yBotHor, int iLHor, int iRHor, int iLVer, int iRVer); // creates a box design
void gotoxy(int x, int y); // places succeeding printf() statements on inputted (x,y) coordinates
void colCyan(); //  changes color to Cyan
void colBlue(); //  changes color to Blue
void colRed(); //  changes color to Red
void colYellow(); //  changes color to Yellow
void colGreen(); //  changes color to Green
void colPurple(); //  changes color to Purple
void colReset(); //  resets color to White

// for bonus function/s
void showTopFive(int nPkCtr, struct pokemonstruct pokemon[],int nRsrchCtr, int inType, String sRsrchName[]); // displays the top pokemon entries with regards to its task type (max. of 5)
int addResearchTaskType(int nRsrchCtr, String sRsrchName[]); // adds research tasks alongside Seen and Defeated
int SearchRsrch(char key[], int nPkCtr, String sRsrchName[]); // verifies if added research task is duplicate or not

int 
main()
{
    struct pokemonstruct pokemon[ENTRYMAX]; // main struct of PokeDex
    int nPkCtr = 0; // Counter of how many pokemon are indexed && current index that has no value, will be utilized for addEntry
    int nRsrchCtr = 2; // Counter of the Research Tasks Types ~ Seen and Defeated

    String sRsrchName[5]; // for storing the name of the research tasks, maxes out at 5
    strcpy(sRsrchName[0], "Seen"); // initializing Seen
    strcpy(sRsrchName[1], "Defeated"); // initializing Defeater

    // do while variables
    char exit = 'n';
    char exitMD = 'n';
    char exitRT = 'n';
    char inputChar;
    char inputMD;
    char inputRT;

    welcomeMenu();
    
    do
    {
        homeSelection(); // choose between Manage Data and Research Tasks
        inputChar = getch();

        switch (inputChar)
        {
            case 'm':
                do
                {
                    manageDataMenu();
                    inputMD = getch();

                    switch (inputMD)
                    {
                        case 'a': // add entry
                            system ("cls");
                            nPkCtr = addEntry(nPkCtr, pokemon);
                            break;

                        case 'c': // modify entry && can't use 'm'
                            system ("cls");
                            modifyEntry(nPkCtr, pokemon);
                            break;

                        case 'd': // delete entry
                            nPkCtr = deleteEntry(nPkCtr, pokemon);
                            break;
                        
                        case 'l': // displays all entry
                            displayAllEntries(nPkCtr, pokemon);
                            break;

                        case 's': // search pokemon by name
                            system ("cls");
                            searchPokeByName(nPkCtr, pokemon);
                            break;

                        case 'p': // search pokemon by type
                            system ("cls");
                            searchPokeByType(nPkCtr, pokemon);
                            break;

                        case 'i': // import
                            system ("cls");
                            nPkCtr = import (nPkCtr, pokemon);
                            break;

                        case 'e': // export
                            system ("cls");
                            export(nPkCtr, pokemon);
                            break;

                        case 'x': // exits to homeSelection()
                            exitMD = 'y';

                        default: // reprompts manageDataMenu()
                            break;
                    }
                } while (exitMD == 'n');
                break;
            
            case 'r':
                do
                {
                    researchTaskMenu();
                    inputRT = getch();

                    switch (inputRT)
                    {
                        case 'p': // review research tasks per pokemon
                            system ("cls");
                            reviewResearchPerPokemon(nPkCtr, pokemon, nRsrchCtr, sRsrchName);
                            break;
                        
                        case 't': // review research tasks per type
                            system ("cls");
                            reviewResearchPerType(nPkCtr, pokemon, nRsrchCtr, sRsrchName);
                            break;

                        case 'u': // updates research task
                            system ("cls");
                            updateResearchTask(nPkCtr, pokemon, nRsrchCtr, sRsrchName);  
                            break;

                        case 'k':
                            system("cls");
                            nRsrchCtr = addResearchTaskType(nRsrchCtr, sRsrchName);
                            break;

                        case 'x': // exits to homeSelection()
                            exitRT = 'y';

                        default: // reprompts researchTaskMenu()
                            break;
                    }
                } while (exitRT == 'n');
                break;

            case 'x':
                exit = 'y';
                break;

        }
    } while (exit == 'n');
    
    system("cls");
    return 0;
}

/************************************************************************************************/
// HOME MENU FUNCTIONS

/*  boxMaker() is used for making box designs of which neccessary coordinates are inputted.
    @param tbLeft - the x-coordinate of the top and bottom left-pillars, for corners
    @param tbRight - the x-coordinate of the top and bottom right-pillars, for corners
    @param yTopHor - the y-coordinate of the top horizontal-figure
    @param yBotHor - the y-coordinate of the bottom horizontal-figure
    @param iLHor - the minumum of the x-coordinate of the horizontal-figures
    @param iRHor - the maximum of the x-coordinate of the horizontal-figure, of which i increments to
    @param iLVer - the minimum of the y-coordinate of the left and right vertical-figures
    @param iRVer - the maximum of the y-coordinate of the left and right vertical-figures, of which i increments to
*/
void 
boxMaker(int tbLeft, int tbRight, int yTopHor, int yBotHor, int iLHor, int iRHor, int iLVer, int iRVer)
{
    // tbLeft, tbRight, yTopHor, yBotHor, iLHor(tbleft+1), iRHor(tbRight-1), iLVer(yTopHor+1), iRVer(yBotHor-1)
    gotoxy(tbLeft, yTopHor); printf("%c", 201); // top-left '╔'
    gotoxy(tbRight, yTopHor); printf("%c", 187); // top-right '╗'
    gotoxy(tbLeft, yBotHor); printf("%c", 200); // bottom-left '╚'
    gotoxy(tbRight, yBotHor); printf("%c", 188); // bottom-right '╝'
    
    for (int i = iLHor; i <= iRHor; i++) 
    { 
        gotoxy(i, yTopHor); printf("%c", 205); // top horizontals '═'
        gotoxy(i, yBotHor); printf("%c", 205); // bottom horizontals '═'
    }

    for (int i = iLVer; i <= iRVer; i++) 
    {
        gotoxy(tbLeft, i); printf("%c", 186); // left side vertical '║'
        gotoxy(tbRight, i); printf("%c", 186); // right side vertical '║'
    }
}

/* welcomeMenu() is what greets the users upon the execustion of the file */
void 
welcomeMenu()
{
    system ("cls"); // clears the terminal screen
    colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
    gotoxy(50,5); colYellow(); printf("WELCOME TO POKEDEX!");
    gotoxy(49,7); colRed(); printf("'gotta catch 'em all!");
    gotoxy(54,9); colBlue(); printf("DEVELOPERS:");
    gotoxy(48,10); colGreen(); printf("BACCAY, Dominic Luis M.");
    gotoxy(48,11); colGreen(); printf("MIRANDA, Bien Aaron C.");
    gotoxy(46,14); colCyan(); printf("*PRESS ANY KEY TO CONTINUE*");
    getch(); // awaits user input to continue to next function
}

/* homeSelection() is what the user will utilize to navigate through the different functions of manageDate and researchTask */
void 
homeSelection()
{
    system ("cls"); // clears the terminal screen
    gotoxy(53,4); colYellow(); printf("POKEDEX HOME");
    gotoxy(33,5); colCyan(); printf("CHOOSE BETWEEN MANAGING DATA OR DOING RESEARCH TASKS");
    colRed(); boxMaker(32, 54, 7, 19, 33, 53, 8, 18);
    gotoxy(36,8); printf("MANAGE DATA [M]"); // manageData functions
    gotoxy(35,10); printf("Add");
    gotoxy(35,11); printf("Modify");
    gotoxy(35,12); printf("Delete");
    gotoxy(35,13); printf("Display Entries");
    gotoxy(35,14); printf("Search by Name");
    gotoxy(35,15); printf("Search by Type");
    gotoxy(35,16); printf("Import");
    gotoxy(35,17); printf("Export");
    colGreen(); boxMaker(63, 85, 7, 14, 64, 84, 8, 13);
    gotoxy(66,8); printf("RESEARCH TASK [R]"); // researchTask functions
    gotoxy(65,10); printf("Review per Pokemon");
    gotoxy(65,11); printf("Review per Type");
    gotoxy(65,12); printf("Update Research");
    gotoxy(65,13); printf("Add Research Task");
    colCyan(); boxMaker(63, 85, 15, 19, 64, 84, 16, 18);
    gotoxy(66,17); printf("LEAVE POKEDEX [X]");
    gotoxy(1, 22); printf(""); colReset(); // clears the cursor, to make everything look neat
}

/* manageDataMenu() contains the manageData function calls of which the user will trigger */
void 
manageDataMenu()
{
    system ("cls");
    gotoxy(54,5); colRed(); printf("MANAGE DATA");
    boxMaker(43, 75, 4, 17, 44, 74, 5, 16);
    gotoxy(48,7); printf("[A] Add");
    gotoxy(48,8); printf("[C] Modify");
    gotoxy(48,9); printf("[D] Delete");
    gotoxy(48,10); printf("[L] Display All Entries");
    gotoxy(48,11); printf("[S] Search by Name");
    gotoxy(48,12); printf("[P] Search by Type");
    gotoxy(48,13); printf("[I] Import");
    gotoxy(48,14); printf("[E] Export");
    gotoxy(48,15); printf("[X] Exit Manage Data"); colReset();
}

/* researchTaskMenu() contains the researchTask function calls of which the user will trigger */
void 
researchTaskMenu()
{
    system ("cls");
    gotoxy(53,5); colGreen(); printf("RESEARCH TASK");
    boxMaker(43, 75, 4, 14, 44, 74, 5, 13);
    gotoxy(48,7); printf("[P] Review per Pokemon");
    gotoxy(48,8); printf("[T] Review per Type");
    gotoxy(48,9); printf("[U] Update Research");
    gotoxy(48,10); printf("[K] Add Research Task");
    gotoxy(48,11); printf("[X] Exit Research Task"); colReset();
}

/************************************************************************************************/
// MANAGE DATA FUNCTIONS

/*  Search() returns 1 if Pokemon Name is a duplicate, -1 if otherwise.
    @param key[] - name user intends to add
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
int 
Search(char key[], int nPkCtr, struct pokemonstruct pokemon[]) // search function, strings only
{
   int i; // utilized by for-loop
   int found = -1; // initializes found to -1, which means there are no duplicates

   for (i = 0; i < nPkCtr; i++)
   {
      if (strcmp(key, pokemon[i].cPokeName) == 0) // when the key[] matches with an existing pokemon NAME, strcmp returns 0
         {
            found = 1; // if condition is satisfied, updates found to 1
         }
   }
   
   if (found == 1)
   {
      return 1; // returns 1 to functions that called Search(), when there is a duplicate entry
   } else
   {
      return -1; // returns 1 to functions that called Search(), when there are no duplicate entries
   }
}

/*  addEntry() returns nPkCtr, and asks the user to add a Pokemon Entry
    @param i - the entry number being triggered, nPkCtr
    @param pokemon[] - passes the pokemon struct from int main()
*/
int 
addEntry(int i, struct pokemonstruct pokemon[])
{
    char inName[NAMEMAX]; // temporarily stores name for max. 20 char validation

    if (i >= ENTRYMAX) // if nPkCtr is >= 150, no more entries can be added
    {
        colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(55, 5); printf("ADD ENTRY\n");
        colRed(); gotoxy(57, 7); printf("!!!!"); gotoxy(48, 8); printf("MAXIMUM ENTRIES REACHED");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    } 
    else // else, continute for Add Entry
    {
        colCyan(); boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
        gotoxy(55, 5); printf("ADD ENTRY");
        gotoxy(35, 7); printf("ENTER POKEMON NAME:"); 
        gotoxy(35, 8); scanf(" %[^\n]s", &inName); // inName temporarily stores Pokemon Name for validation

        if (Search(inName, i, pokemon) == 1) // checks if inName is a duplicate throught the Search(), if == 1, it is a duplicate, == -1 if otherwise
        {          
            system ("cls"); // clears screen 
            colCyan(); boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
            gotoxy(55, 5); printf("ADD ENTRY\n");
            colRed(); gotoxy(57, 7); printf("!!!!!"); gotoxy(43, 8); printf("OOPS! THIS POKEMON ALREADY EXISTS");
            colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
            getch();
        } 
        else // else, continue for Pokemon Entry
        {
            pokemon[i].entry = i + 1; // initializes entry number to match nPkCtr
            gotoxy(35, 10); printf ("FOR ENTRY #%d: \n", pokemon[i].entry);
            strcpy(pokemon[i].cPokeName, inName); // inName is now being stored into the index of the existing pokemon entry
            gotoxy(35, 12); printf("POKEMON NAME: %s \n", pokemon[i].cPokeName); // visual validation of what is stored, for user
            do {
                gotoxy(50, 14); printf ("SELECT POKEMON TYPE");
                gotoxy(39, 15); printf("[W] WATER [F] FIRE [G] GRASS [E] ELECTRIC");
                pokemon[i].cPokeType = getch(); // getch() gets w/f/g/e char for storing of pokemon type in the struct 

                if (pokemon[i].cPokeType == 'w') { // used for visual validation of what is being stored in pokemon type, but pokemon[i].cPokeType still stores w/f/g/e
                    gotoxy(47, 17); printf("POKEMON TYPE: WATER");
                }
                else if (pokemon[i].cPokeType == 'f') {
                    gotoxy(47, 17); printf("POKEMON TYPE: FIRE");
                }
                else if (pokemon[i].cPokeType == 'g') {
                    gotoxy(47, 17); printf("POKEMON TYPE: GRASS");
                }
                else if (pokemon[i].cPokeType == 'e') {
                    gotoxy(47, 17); printf("POKEMON TYPE: ELECTRIC");
                }
            } while (pokemon[i].cPokeType != 'w' && pokemon[i].cPokeType != 'f' && pokemon[i].cPokeType != 'g' && pokemon[i].cPokeType != 'e');
                        
            gotoxy(35, 19); printf("ENTER POKEMON DESCRIPTION:");
            gotoxy(35, 20); scanf(" %[^\n]s", pokemon[i].cPokeDesc);
            
            // initializes research task types of existing entry to value 0, to be updated in researchTask functions
            pokemon[i].nResearchType[0] = 0; // for seen
            pokemon[i].nResearchType[1] = 0; // for defeated
            pokemon[i].nResearchType[2] = 0; // for additional task type
            pokemon[i].nResearchType[3] = 0; // for additional task type
            pokemon[i].nResearchType[4] = 0; // for additional task type

            i++; // increments i, to be utilized by other entries
        }
    }
    return i; // returns index of pokemon entry
}

/*  modifyEntry() returns nPkCtr, and asks the user to modify a Pokemon Entry
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
void
modifyEntry(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i; // for identifying what entry to modify
    char choice; // for do-while loop
    char modify = 'y'; // for do-while loop

    char changeName[NAMEMAX]; // variable for name change
    char validName; // for do-while loop

    if (nPkCtr == 0) // will be triggered if there are no existing PokeDex entries
    {   
        colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(54, 5); printf("MODIFY ENTRY\n");
        colRed(); gotoxy(57, 7); printf("!!!!!"); gotoxy(47, 8); printf("NO ENTRIES TO MODIFY FROM");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else // otherwise, modify function will continue
    {
        do 
        {
            system ("cls");
            displayAllEntries(nPkCtr, pokemon); // displays all entries until user finds what to modify
            colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
            gotoxy(54, 5); printf("MODIFY ENTRY\n");
            gotoxy(48, 8); printf("SELECT ENTRY TO MODIFY:");
            gotoxy(48, 9);scanf(" %d", &i); // i stores the entry number for modification
        
            if (i > nPkCtr || i <= 0 ) // validates if stored entry number exceeds the Pokemon Counter or is less than 0, if yes, remprompts user
            {
                system ("cls"); colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
                gotoxy(54, 5); printf("MODIFY ENTRY\n");
                colRed(); gotoxy(49, 8); printf("ENTRY DOES NOT EXIST!"); 
                colCyan(); gotoxy(45, 11); printf("*PRESS ANY KEY TO TRY AGAIN*"); colReset();
                getch();
            }
        } while (i > nPkCtr || i <= 0 );

        i = i-1; // decrementing the entry number to match the actual index of pokemon[i].entry

        system ("cls"); gotoxy(54, 5); printf("MODIFY ENTRY\n");
        displayEntry(i, pokemon); printf("\n"); // if entry number inputted is valid, display the Entry to be modified
            
        do 
        { // asks the user what part of the entry is to be modified
            gotoxy(44, 16); printf("SELECT POKEMON DATA TO MODIFY\n"); // question
            gotoxy(44, 17); printf("[1] NAME");
            gotoxy(44, 18); printf("[2] TYPE");
            gotoxy(44, 19); printf("[3] DESCRIPTION");
            gotoxy(44, 20); printf("[X] EXIT");
            choice = getch();
            
            switch (choice) // modification of specific entry data will happen here
            {
                case '1': // NAME
                    do
                    {
                        system ("cls"); boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
                        gotoxy(54, 5); printf("MODIFY ENTRY\n");
                        gotoxy(44, 8); printf ("ENTER NEW POKEMON NAME: ");
                        gotoxy(44, 9); scanf(" %[^\n]s", &changeName); // temporarily stored the modified name
                    
                            if (Search(changeName, nPkCtr, pokemon) == 1)
                            { // verify if name change is correct
                                validName = 'n'; // not valid, reprompt
                                gotoxy(44, 11); colRed(); printf ("NAME EXISTS IN THE POKEDEX.");
                                gotoxy(44, 12); colYellow(); printf("// PRESS ANY KEY TO CONTINUE //");
                                getch();
                            }
                            else 
                            {
                                strcpy(pokemon[i].cPokeName, changeName); // no duplicates, store into the PokeDex
                                validName = 'y';
                            }
                    } while (validName == 'n');
                    
                    gotoxy(44, 11); printf("EDITED POKEMON NAME: %s\n", pokemon[i].cPokeName); // visual validation of the modified name
                    gotoxy(44, 13); printf ("DO YOU WANT TO MODIFY MORE?\n"); // asks user if they want to continue mofidying entry
                    gotoxy(44, 14); printf("[Y] Yes [X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case '2': // TYPE
                    do
                    {
                        system ("cls");
                        boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
                        gotoxy(54, 5); printf("MODIFY ENTRY\n");
                        gotoxy(48, 7); printf ("SELECT NEW POKEMON TYPE");
                        gotoxy(48, 8); printf ("[W] WATER [F] FIRE");
                        gotoxy(48, 9); printf ("[G] GRASS [E] ELECTRIC");
                        pokemon[i].cPokeType = getch(); printf("\n"); // stores the user input for the modified type

                        if (pokemon[i].cPokeType == 'w') { // visual validation of modified type, but pokemon[i].cPokeType is still w/f/g/e
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: WATER\n"); 
                        }
                        else if (pokemon[i].cPokeType == 'f') {
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: FIRE\n");
                        }
                        else if (pokemon[i].cPokeType == 'g') {
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: GRASS\n");
                        }
                        else if (pokemon[i].cPokeType == 'e') {
                            gotoxy(44, 11); printf("EDITED POKEMON TYPE: ELECTRIC\n");
                        }
                    } while (pokemon[i].cPokeType != 'w' && pokemon[i].cPokeType != 'f' && pokemon[i].cPokeType != 'g' && pokemon[i].cPokeType != 'e');
                    
                    gotoxy(44, 13); printf ("DO YOU WANT TO MODIFY MORE?\n"); // asks user if they want to continue mofidying entry
                    gotoxy(44, 14); printf("[Y] Yes [X] Exit\n");
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case '3':
                    system ("cls");

                    boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
                    gotoxy(54, 5); printf("MODIFY ENTRY\n");
                    gotoxy(34, 7); printf ("ENTER NEW DESCRIPTION:");
                    gotoxy(34, 8); scanf(" %[^\n]s", &pokemon[i].cPokeDesc);
                    gotoxy(34, 10); printf("EDITED DESCRIPTION:"); // visual validation of modified description
                    gotoxy(34, 11); printf("%s", pokemon[i].cPokeDesc);
                    gotoxy(44, 13); printf ("DO YOU WANT TO MODIFY MORE?\n"); // asks user if they want to continue mofidying entry
                    gotoxy(44, 14); printf("[Y] Yes [X] Exit\n"); 
                    modify = getch(); // asks the user for more modification and to reloop or not
                    break;

                case 'x':
                    modify = 'n'; // when triggered, exits the function
                    break;
            }
        } while (modify == 'y');
    }
}

/*  deleteEntry() returns nPkCtr, and asks the user to delete a Pokemon Entry
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
int 
deleteEntry(int nPkCtr, struct pokemonstruct pokemon[]) // Delete Entry
{
    int i,j; // i is for the actual index, j for the for loop
    char cDec; // for the do-while loop

    if (nPkCtr == 0) // if Pokemon Counter is 0, tells user there are no entries to be deleted from
    {   
        system ("cls"); colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(53, 5); printf("DELETE ENTRY\n");
        colRed(); gotoxy(56, 7); printf("!!!!!!");
        gotoxy(47, 8); printf("NO ENTRIES TO DELETE FROM");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else // otherwise, continute with DeleteEntry
    {
        do // verification if inputted entry number exists and is within the range of nPkCtr
        {
            system ("cls");
            displayAllEntries(nPkCtr, pokemon); // displays all entries for the user to choose what to delete from
            colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11); 
            gotoxy(53, 5); printf("DELETE ENTRY\n");
            gotoxy(48, 8); printf("SELECT ENTRY TO DELETE:");
            gotoxy(48, 9); scanf(" %d", &i); // i stores the entry number to be deleted

            if (i > nPkCtr || i <= 0 ) // if i is more than the nPkCtr, or is less or equal to 0, reprompt user
            {
                system ("cls"); colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
                gotoxy(53, 5); printf("DELETE ENTRY\n");
                colRed(); gotoxy(49, 8); printf("ENTRY DOES NOT EXIST!"); 
                colCyan(); gotoxy(45, 11); printf("*PRESS ANY KEY TO TRY AGAIN*"); colReset();
                getch();
            }
        } while (i > nPkCtr || i <= 0 ); // this will happen until valid number is inputted

        do // deletion verification for user
        {
            i = i-1; // i-1 to match the entry# for visual validation
            system ("cls"); gotoxy(53, 5); printf("DELETE ENTRY\n");
            displayEntry(i, pokemon); printf("\n"); // displays entry subject for deletion
            gotoxy(44, 16); printf("ENTRY #%d IS SUBJECT FOR DELETION\n", i+1);
            gotoxy(44, 18); printf("ARE YOU SURE TO DELETE ENTRY #%d?\n", i+1); // asks user if they are to delete or not
            gotoxy(44, 19); printf("[Y] YES [N] NO\n");
            cDec = getch();

            switch (cDec)
            {
                case 'y': // YES
                    
                    for (j = i; j < nPkCtr; j++)
                    {
                        // if entry is to be deleted, entries will be decremented by one, all succeeding entreis will replace one another
                        strcpy (pokemon[j].cPokeName, pokemon[j+1].cPokeName); // for name
                        pokemon[j].cPokeType = pokemon[j+1].cPokeType; // for type 
                        strcpy (pokemon[j].cPokeDesc, pokemon[j+1].cPokeDesc); // for description
                        pokemon[j].nResearchType[0] = pokemon[j+1].nResearchType[0]; // for seen
                        pokemon[j].nResearchType[1] = pokemon[j+1].nResearchType[1]; // for defeated
                        pokemon[j].nResearchType[2] = pokemon[j+1].nResearchType[2]; // for additional task type
                        pokemon[j].nResearchType[3] = pokemon[j+1].nResearchType[3]; // for additional task type
                        pokemon[j].nResearchType[4] = pokemon[j+1].nResearchType[4]; // for additional task type
                    }
                    nPkCtr--; // Pokemon Counter is decremented
                    gotoxy(44, 22); printf("Entry Deleted. PokeDex Readjusted\n");
                    gotoxy(46, 23); printf("~~PRESS ANY KEY TO CONTINUE~~\n");
                    getch();
                    break;

                case 'n':
                    gotoxy (44, 22); printf("ENTRY SUSTAINED.\n");
                    gotoxy(46, 23); printf("~~PRESS ANY KEY TO CONTINUE~~\n");
                    getch();
                    break;

                default:
                    break;
            }
         } while (cDec != 'y' && cDec != 'n');
    }
    
    return nPkCtr;
}

/*  displayEntry() is utilized by the manageData functions to verify changes made to such
    @param i - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
void 
displayEntry(int i, struct pokemonstruct pokemon[])
{
        colCyan(); boxMaker(32, 86, 4, 24, 33, 85, 5, 23);
        gotoxy(55, 7); printf("ENTRY #%d\n", pokemon[i].entry); // prints entry no.
        gotoxy(35, 9); printf("POKEMON NAME: %s\n", pokemon[i].cPokeName); // prints Pokemon Name

        // prints Pokemon Type
        if (pokemon[i].cPokeType == 'w') { 
            gotoxy(35, 11); printf("POKEMON TYPE: WATER\n");
        }
        else if (pokemon[i].cPokeType == 'f') {
            gotoxy(35, 11); printf("POKEMON TYPE: FIRE\n");
        }
        else if (pokemon[i].cPokeType == 'g') {
            gotoxy(35, 11); printf("POKEMON TYPE: GRASS\n");
        }
        else if (pokemon[i].cPokeType == 'e') {
            gotoxy(35, 11); printf("POKEMON TYPE: ELECTRIC\n");
        }
        gotoxy(35, 13); printf("POKEMON DESCRIPTION:"); // prints Pokemon Decription
        gotoxy(35, 14); printf("%s", pokemon[i].cPokeDesc);
}

/*  displaySearchEntry() displays all entries made triggered by the search functions
    @param nPkCtr - overall entries within the PokeDex
    @param i - the index of the entry being triggered
    @param pokemon[] - passes the pokemon struct from int main()
*/
void
displaySearchEntry(int nPkCtr, int i, struct pokemonstruct pokemon[])
{
        colCyan(); printf("\n || ENTRY #%d ||\n", pokemon[i].entry);
        colGreen(); printf("\n POKEMON NAME:\n");
        colYellow(); printf(" %s\n", pokemon[i].cPokeName); // prints name

                // prints type
                if (pokemon[i].cPokeType == 'w')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("WATER\n");
                }
                else if (pokemon[i].cPokeType == 'f')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("FIRE\n");
                }
                else if (pokemon[i].cPokeType == 'g')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("GRASS\n");
                }
                else if (pokemon[i].cPokeType == 'e')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("ELECTRIC\n");
                }

        colGreen(); printf("\n POKEMON DESCRIPTION:\n");
        colYellow(); printf(" %s\n", pokemon[i].cPokeDesc); // prints description

        colPurple(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
        getch();
}

/*  displayAllEntries() displays all entries made by user in a Previous-Next algorithm
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
void
displayAllEntries(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i = 0;
    char prevnext;

    if (nPkCtr == 0) 
    {
        gotoxy(1, 2); colRed(); printf("// NO ENTRIES FOUND TO DISPLAY //");
        gotoxy(1, 5); colYellow(); printf("Redirecting to Manage Data Menu... ");
        getch();
    }
    else 
    {
        if (nPkCtr == 1)
        {
            system("cls");
            gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
            gotoxy(1,3); printf(" ");
            colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
            colGreen(); printf("\n POKEMON NAME:\n");
            colYellow(); printf(" %s\n", pokemon[i].cPokeName);

                if (pokemon[i].cPokeType == 'w')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("WATER\n");
                }
                else if (pokemon[i].cPokeType == 'f')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("FIRE\n");
                }
                else if (pokemon[i].cPokeType == 'g')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("GRASS\n");
                }
                else if (pokemon[i].cPokeType == 'e')
                {
                    colGreen(); printf("\n POKEMON TYPE: ");
                    colYellow(); printf("ELECTRIC\n");
                }

            colGreen(); printf("\n POKEMON DESCRIPTION:\n");
            colYellow(); printf(" %s\n", pokemon[i].cPokeDesc);
            colPurple(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
            getch();
        }
        else if (nPkCtr > 1)
        {
            do
            {   
                if (i < 0) // when i is less than 0, it defaults to i = 0, triggered when user clicks PREVIOUS on Entry #1
                {
                    i = 0;
                }
                else if (i == nPkCtr) // when i is greater than nPkCtr, it defaults to decrementing, triggered when the user clicks NEXT on Last Entry
                {
                    i--;
                }

                system("cls"); gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n"); gotoxy(1, 5 ); printf(" ");
                colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
                colGreen(); printf("\n POKEMON NAME:\n");
                colGreen(); printf(" %s\n", pokemon[i].cPokeName); // prints name

                // prints type
                if (pokemon[i].cPokeType == 'w')
                {
                    colGreen(); printf("\n POKEMON TYPE: WATER\n");
                }
                else if (pokemon[i].cPokeType == 'f')
                {
                    colGreen(); printf("\n POKEMON TYPE: FIRE\n");
                }
                else if (pokemon[i].cPokeType == 'g')
                {
                    colGreen(); printf("\n POKEMON TYPE: GRASS\n");
                }
                else if (pokemon[i].cPokeType == 'e')
                {
                    colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
                }

                colGreen(); printf("\n POKEMON DESCRIPTION:\n");
                colGreen(); printf(" %s\n", pokemon[i].cPokeDesc); // prints description

                colCyan(); printf("\n [P] PREVIOUS [N] NEXT\n"); // prompts user if they will return to previous entry or to the next
                colCyan(); printf("\n [X] EXIT\n"); // once triggered, will exit the function
                prevnext = getch();

                switch (prevnext)
                {
                    case 'p': // previous
                        system("cls");
                        gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
                        gotoxy(1, 5 ); printf(" ");
                        i--;
                        colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
                        colGreen(); printf("\n POKEMON NAME:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeName);

                        if (pokemon[i].cPokeType == 'w')
                        {
                            colGreen(); printf("\n POKEMON TYPE: WATER\n");
                        }
                        else if (pokemon[i].cPokeType == 'f')
                        {
                            colGreen(); printf("\n POKEMON TYPE: FIRE\n");
                        }
                        else if (pokemon[i].cPokeType == 'g')
                        {
                            colGreen(); printf("\n POKEMON TYPE: GRASS\n");
                        }
                        else if (pokemon[i].cPokeType == 'e')
                        {
                            colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
                        }

                        colGreen(); printf("\n POKEMON DESCRIPTION:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeDesc);
                        break;

                    case 'n': // next
                        system("cls");
                        gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL ENTRIES //\n");
                        gotoxy(1, 5 ); printf(" ");
                        i++;
                        colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
                        colGreen(); printf("\n POKEMON NAME:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeName);

                        if (pokemon[i].cPokeType == 'w')
                        {
                            colGreen(); printf("\n POKEMON TYPE: WATER\n");
                        }
                        else if (pokemon[i].cPokeType == 'f')
                        {
                            colGreen(); printf("\n POKEMON TYPE: FIRE\n");
                        }
                        else if (pokemon[i].cPokeType == 'g')
                        {
                            colGreen(); printf("\n POKEMON TYPE: GRASS\n");
                        }
                        else if (pokemon[i].cPokeType == 'e')
                        {
                            colGreen(); printf("\n POKEMON TYPE: ELECTRIC\n");
                        }

                        colGreen(); printf("\n POKEMON DESCRIPTION:\n");
                        colGreen(); printf(" %s\n", pokemon[i].cPokeDesc);
                        break;

                    case 'x':
                        // exit
                        break;        
                }
            } while (prevnext != 'x');
        }
    }   
}

/*  searchPokeByName() asks the user of a name to be searched from the PokeDex
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
void 
searchPokeByName(int nPkCtr, struct pokemonstruct pokemon[])
{
    int j,c,i,k; // utilized by the for-loop
    int ctr = 0; // control number to count the number of scanned pokemons
    int nList[ENTRYMAX]; // sets max of nList to 150
    int inNameLen; // length of key
    char inName[NAMEMAX]; // sets max characters of inName to 20
    char sub[NAMEMAX]; //substring
    int sublen; // length of the array[word] in for loop no. 2
    int pos = 0; // iterating position
    int exist = 0; // initializing exist to 0
    int found = 0; // initializing found to 0

    colCyan(); boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
    gotoxy(49, 5); printf("SEARCH POKEMON BY NAME\n");
    gotoxy(43, 8); printf("SEARCH POKEMON NAME:");
    colCyan(); gotoxy(43, 9); scanf(" %[^\n]s", &inName);

    inNameLen = strlen(inName); // stores the length of the inName

    for (i = 0; i < nPkCtr; i++)
    {
        pos = 0; //position starts at word[0]
        sublen = strlen(pokemon[i].cPokeName); // declaring the length of the word

        for (j = 0; j <= sublen - inNameLen; j++) // for loop ng position 
        { 
            c = 0;
		    while (c < inNameLen) // substring function 
            { 
            sub[c] = pokemon[i].cPokeName[c+pos]; // B[i] is the array of words, pos ay yung position to start the copying
            c++; // iteration
   	        }
   		    sub[c] = '\0'; // while loop will stop at an empty index after the last character, put a \0 kasi needed to

            if (strcmp(sub, inName) == 0) // if substring is found
            { 
                for (k = 0; k < ctr; k++)
                {
                    if (nList[k] == i)
                    {
                        found = 1;
                    }
                }

                if (found == 0)
                {
                    nList[ctr] = i;
                    ctr++;
                    exist = 1;
                }
                found = 0; // reset                                
            }
            pos++; // position will iterate until maubos yung letters. // for loop P ends then go to the next for loop i 
        }
    }

    if (exist == 1) // for displaying the entries found
    {       
        for (i = 0; i < ctr; i++)
        {
            system("cls");
            gotoxy(1,2); colYellow (); printf("// DISPLAYING SEARCH NAME ENTRIES //\n"); gotoxy(1, 5 ); printf(" ");
            displaySearchEntry(nPkCtr, nList[i], pokemon);
        }
    }

    if (exist == 0) 
    {
        system ("cls");
        colCyan(); boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
        gotoxy(49, 5); printf("SEARCH POKEMON BY NAME\n");
        colRed(); gotoxy(56, 7); printf("!!!!!");
        gotoxy(43, 8); printf("OOPS! THIS POKEMON DOESN'T EXIST");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    
}

/*  searchPokeByType() asks the user of the pokemon type of the pokemon to be searched from the PokeDex
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
void 
searchPokeByType(int nPkCtr, struct pokemonstruct pokemon[])
{
    int i = 0;
    int exist = 0;
    char inType;

    do 
    {
        system ("cls"); colCyan(); boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
        gotoxy(49, 5); printf("SEARCH POKEMON BY TYPE\n");
        gotoxy(50, 8); colGreen(); printf("SELECT POKEMON TYPE");
        gotoxy(48, 9); colYellow(); printf("[W] WATER [F] FIRE");
        gotoxy(48, 10); colYellow(); printf("[G] GRASS [E] ELECTRIC");
        inType = getch();
    } while (inType != 'w' && inType != 'f' && inType != 'g' && inType != 'e');
    
    
    for (i = 0; i < nPkCtr; i++) // if Pokemon of intended type exists, display such
    {
        if(inType == pokemon[i].cPokeType) 
        {
            system("cls");
            gotoxy(1,2); colYellow (); printf("// DISPLAYING SEARCH BY TYPE ENTRIES //\n"); gotoxy(1, 5 ); printf(" ");
            displaySearchEntry(nPkCtr, i, pokemon);
            exist = 1;
        }
    }
        
    if (exist == 0) // if Pokemon of intended type doesn't exist
    {
        system ("cls");
        colCyan();
        boxMaker(40, 78, 4, 12, 41, 77, 5, 11);
        gotoxy(49, 5); printf("SEARCH POKEMON BY TYPE\n");

        colRed();
        gotoxy(56, 7); printf("!!!!!");
        gotoxy(43, 8); printf("OOPS! THIS POKEMON DOESN'T EXIST");
        colCyan(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
}

/*  export() creates a file outside .exe of which stores all Pokemon Entries inputted
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
void 
export(int nPkCtr, struct pokemonstruct pokemon[])
{
    char cFileName[31];
    FILE *fpointer;
    int i;

    if (nPkCtr == 0)
    {
        colCyan(); printf("// EXPORT ENTRY //\n");
        colRed(); printf("\n!! NO ENTRIES FOUND !!\n");
        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n"); 
        getch();
    }
    else
    {
        colYellow(); printf("ENTER A FILE NAME (EXCLUDE .txt): ");
        scanf(" %[^\n]s", &cFileName); // cFilename stores the user's file input without .txt

        strcat(cFileName, ".txt"); // concatenating cFileName with .txt for the code to find the intended file

        fpointer = fopen(cFileName,"w"); // opens the file, w = write, r = read, a = append
        
        for (i = 0; i < nPkCtr; i++) // writes all existing entries in the required format
        {
            // Name
            fprintf(fpointer, "Name: %s \n", pokemon[i].cPokeName);
            // Type
            if (pokemon[i].cPokeType == 'w') {
                fprintf(fpointer, "Type: Water\n");
            }
            else if (pokemon[i].cPokeType == 'f') {
                fprintf(fpointer, "Type: Fire\n");
            }
            else if (pokemon[i].cPokeType == 'g') {
                fprintf(fpointer, "Type: Grass\n");
            }
            else if (pokemon[i].cPokeType == 'e') {
                fprintf(fpointer, "Type: Electric\n");
            }
            // Description
            fprintf(fpointer, "Description: %s \n", pokemon[i].cPokeDesc);
            fprintf(fpointer, "\n");
        }
        
        fclose(fpointer); // closes the file

        colGreen(); printf("\nEXPORT SUCCESSFUL! \n");
        colCyan(); printf("\n// PRESS ANY KEY TO CONTINUE //");
        getch();
    }
}

/*  import() imports .txt files outside the .exe to be added to the PokeDex
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
    Pre-Condition: The file to be imported should be in the folder within the .exe of the program
*/
int 
import(int nPkCtr, struct pokemonstruct pokemon[])
{
    char filename[100]; // storing the import's filename w/o .txt
    FILE *fp; // declaration the file variable to be used

    char tempName[27]; // adding 6 to the original [21] to account for the "Name: " in the .txt files
    char tempType[15]; // adding 6 to the original [9] to account for the "Type: " in the .txt files
    char tempDesc[64]; // adding 13 to the original [51] to account for the "Description: " in the .txt files

    char choice; // for do-while loop
    char dupChoice; // for do-while loop
    int buffer; // only accounts for the imported (not skipped) entries
    int zeroEntry = 0; // for nPkCtr == 0
    int manyEntry = 0; // for nPkCtr > 0
    int overwrite; // for duplicate entries, ask if such imported entry is to be overwritten

    if (nPkCtr == 0)
    {
        buffer = 0; // buffer is initialized to 0, since this is the first instance of such
        do // asks user to input how many entries are to be imported from the .txt file
        {
            colCyan(); printf("// IMPORT ENTRY //\n");
            colRed(); printf("\n!! NO EXISTING ENTRIES !!\n\n");
            colCyan(); printf("HOW MANY ENTRIES WOULD YOU LIKE TO IMPORT?\nENTER VALUE: ");
            scanf(" %d", &zeroEntry);
        
            if (zeroEntry <= 0) { // if less than 0, reprompt
                colRed(); printf("\nINVALID INPUT, PLEASE RETRY\n");
            }
            else if (zeroEntry >= 151) // if greater than the maximum number of entries, reprompt
            {
                colRed(); printf("\nEXCEEDS MAXIMUM ENTRIES ALLOWED, PLEASE RETRY\n");
            }
            printf("\n");
        } while (zeroEntry <= 0 || zeroEntry >= 151);

        colYellow(); printf("\nENTER FILE NAME (EXCLUDE .txt): "); // asks user for the filename to be imported from
        scanf(" %s", &filename); 
        strcat(filename,".txt"); // concatenates the filename with .txt for the code to utilize the file

        fp = fopen(filename, "r"); // opens and reads file

        for (int i = 0; i < zeroEntry; i++)
        {
            system("cls");
            fscanf(fp, " %[^\n]s\n", &tempName); // initial reading of the first 3 lines of the imported file
            fscanf(fp, " %[^\n]s\n", &tempType);
            fscanf(fp, " %[^\n]s\n", &tempDesc);

            if (Search(&tempName[6], nPkCtr, pokemon) == -1) // if there is no duplicate
            {
                do // ask user if the imported entry as shown to them will be imported or skipped
                {
                    colCyan(); printf("\n// IMPORTED RESULTS //\n");

                    colPurple(); printf("Pokemon Name: %.20s\n", &tempName[6]);
                    colPurple(); printf("Pokemon Type: %s\n", &tempType[6]);
                    colPurple(); printf("Pokemon Description: %.50s\n", &tempDesc[13]);
                    colPurple(); printf("\n");
                    colCyan(); printf("DO YOU LIKE TO IMPORT THIS ENTRY?\n");
                    colCyan(); printf("[Y] IMPORT [N] SKIP\n");
                    choice = getch();
                } while (choice != 'y' && choice != 'n');    

                switch (choice)
                {
                    case 'y': // if yes, copy tempName[6] into the struct of the current index
                        strcpy(pokemon[buffer].cPokeName, &tempName[6]); // copies the Name
                        if ( strcmp(&tempType[6],"Water") == 0 ) // reverse of the addEntry() and modifyEntry(), converts "Water" to its 'w' counterpart in the struct, and so on.
                        {
                            pokemon[buffer].cPokeType = 'w';
                        }
                        else if ( strcmp(&tempType[6],"Fire") == 0 )
                        {
                            pokemon[buffer].cPokeType = 'f';
                        }                
                        else if ( strcmp(&tempType[6],"Grass") == 0 )
                        {
                            pokemon[buffer].cPokeType = 'g';
                        }
                        else if ( strcmp(&tempType[6],"Electric") == 0 )
                        {
                            pokemon[buffer].cPokeType = 'e';
                        }
                        strcpy(pokemon[buffer].cPokeDesc, &tempDesc[13]); // copies the imported Description into the struct of the current index
                        
                        // initializes research task types of existing entry to value 0, to be updated in researchTask functions
                        pokemon[buffer].nResearchType[0] = 0; // for seen
                        pokemon[buffer].nResearchType[1] = 0; // for defeated
                        pokemon[buffer].nResearchType[2] = 0; // for additional task type
                        pokemon[buffer].nResearchType[3] = 0; // for additional task type
                        pokemon[buffer].nResearchType[4] = 0; // for additional task type

                        buffer++; // increments buffer ~ indicating an entry has been imported
                        nPkCtr++; // increments nPkCtr ~ indiciating an entry has been made
                        pokemon[i].entry = buffer; // initializes the pokemon[i].entry of the current index to its corresponding buffer
                        colGreen(); printf("\n// IMPORT SUCCESSFUL! //\n");
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        break;
                    
                    case 'n':
                        colRed(); printf("\n// IMPORT SKIPPED! //\n"); // if skipped, no incrementation/initialization is done
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        break;
                }
                }
                else if (Search(&tempName[6], nPkCtr, pokemon) == 1) // if there is a duplicate/ pokemon already exists
                {
                    system("cls");
                    colCyan(); printf("\n// IMPORTED RESULTS //\n");
                    colRed(); printf("THIS POKEMON ALREADY EXISTS\n");

                    do // asks user if they are to overwrite the existing entry of which stores the name of the duplicate
                    {
                        colYellow(); printf("\n[Y] OVERWRITE EXISTING ENTRY\n");
                        printf("[N] SKIP EXISTING ENTRY\n"); colReset();
                        dupChoice = getch();
                    } while (dupChoice != 'y' && dupChoice != 'n');

                    switch (dupChoice)
                    {
                        case 'y': // if yes, overwrite its type and description
                            system ("cls");
                            colGreen(); printf("\n// OVERWRITING EXISTING ENTRY //\n");

                            overwrite = searchImport(&tempName[6], nPkCtr, pokemon);

                            if ( strcmp(&tempType[6],"Water") == 0 )
                            {
                                pokemon[overwrite].cPokeType = 'w';
                            }
                            else if ( strcmp(&tempType[6],"Fire") == 0 )
                            {
                                pokemon[overwrite].cPokeType = 'f';
                            }                
                            else if ( strcmp(&tempType[6],"Grass") == 0 )
                            {
                                pokemon[overwrite].cPokeType = 'g';
                            }
                            else if ( strcmp(&tempType[6],"Electric") == 0 )
                            {
                                pokemon[overwrite].cPokeType = 'e';
                            }
                            strcpy(pokemon[overwrite].cPokeDesc, &tempDesc[13]);

                            printf("\n// EXISTING ENTRY OVERWRITTEN //\n"); colReset();
                            colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                            getch();
                            system ("cls");
                            break;
                        
                        case 'n': // if no, continue
                            colRed(); printf("\n// EXISTING ENTRY SKIPPED! //\n");
                            colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                            getch();
                            system("cls");
                            break;
                    }
                }  
            }
        fclose(fp);
    }
    else if (nPkCtr > 0 && nPkCtr < 150) // if there are already existing entries in the time of import
    {
        buffer = nPkCtr; // initializes buffer to the already existing number of entries stored in nPkCtr
        do // asks user how many entries are to be imported
        {
            colCyan(); printf("// IMPORT ENTRY //\n");
            colGreen(); printf("\n!! %d EXISTING ENTRIES !!\n\n", nPkCtr);
            colCyan(); printf("HOW MANY ENTRIES WOULD YOU LIKE TO IMPORT?\nENTER VALUE: ");
            scanf(" %d", &manyEntry);
            
            if (manyEntry <= 0) // if less than 0, reprompt
            { 
                colRed(); printf("\nINVALID INPUT, PLEASE RETRY\n");
            }
            else if (manyEntry > (ENTRYMAX-nPkCtr)) // if greater than the maximum number of entries, reprompt
            {
                colRed(); printf("\nEXCEEDS MAXIMUM ENTRY ALLOWED, PLEASE RETRY\n");
            }
            printf("\n");
        } while (manyEntry <= 0 || manyEntry > (ENTRYMAX-nPkCtr));

        colYellow(); printf("\n\nENTER FILE NAME (EXCLUDE.txt): "); // asks the user of the filename of the .txt file to be imported from 
        scanf(" %s", &filename);
        strcat(filename,".txt"); // concatenates .txt to the filename inputted

        fp = fopen(filename, "r"); // opens the import file and reads it

        for (int i = 0; i < manyEntry; i++)
        {        
            system("cls");
            fscanf(fp, " %[^\n]s\n", &tempName); // initial reading of the first 3 lines of the imported file
            fscanf(fp, " %[^\n]s\n", &tempType);
            fscanf(fp, " %[^\n]s\n", &tempDesc);

            if (Search(&tempName[6], nPkCtr, pokemon) == -1) // if there is no duplicate enties (name)
            {
                do // asks user if the imported entry as shown to them shall be imported or skipped
                {
                    colCyan(); printf("\n// IMPORTED RESULTS //\n");

                    colPurple(); printf("Pokemon Name: %.20s\n", &tempName[6]);
                    colPurple(); printf("Pokemon Type: %s\n", &tempType[6]);
                    colPurple(); printf("Pokemon Description: %.50s\n", &tempDesc[13]);
                    colPurple(); printf("\n");
                
                    colCyan(); printf("DO YOU LIKE TO IMPORT THIS ENTRY?\n");
                    colCyan(); printf("[Y] IMPORT [N] SKIP\n");
                    choice = getch();

                } while (choice != 'y' && choice != 'n');    

                switch (choice)
                {
                case 'y': // if yes, place the values of the temporary variables into the struct of the current index
                    strcpy(pokemon[buffer].cPokeName, &tempName[6]);
                    if ( strcmp(&tempType[6],"Water") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'w';
                    }
                    else if ( strcmp(&tempType[6],"Fire") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'f';
                    }                
                    else if ( strcmp(&tempType[6],"Grass") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'g';
                    }
                    else if ( strcmp(&tempType[6],"Electric") == 0 )
                    {
                        pokemon[buffer].cPokeType = 'e';
                    }
                    strcpy(pokemon[buffer].cPokeDesc, &tempDesc[13]);

                    // initializes research task types of existing entry to value 0, to be updated in researchTask functions
                    pokemon[buffer].nResearchType[0] = 0; // for seen
                    pokemon[buffer].nResearchType[1] = 0; // for defeated
                    pokemon[buffer].nResearchType[2] = 0; // for additional task type
                    pokemon[buffer].nResearchType[3] = 0; // for additional task type
                    pokemon[buffer].nResearchType[4] = 0; // for additional task type

                    buffer++; // increments buffer ~ indicating an entry has been imported
                    nPkCtr++; // increments nPkCtr ~ indiciating an entry has been made
                    pokemon[i].entry = buffer; // initializes the pokemon[i].entry of the current index to its corresponding buffer
                    colGreen(); printf("\n// IMPORT SUCCESSFUL! //\n");
                    colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                    getch();
                    break;
                
                case 'n': // if no, continue on
                    colRed(); printf("\n// IMPORT SKIPPED! //\n");
                    colYellow(); printf("\n\n// PRESS ANY KEY TO CONTINUE //\n");
                    getch();
                    break;
                }
            }
            else if (Search(&tempName[6], nPkCtr, pokemon) == 1) // if there is a duplicate
            {
                system("cls");
                colCyan(); printf("\n// IMPORTED RESULTS //\n");
                colRed(); printf("THIS POKEMON ALREADY EXISTS\n");

                do // asks user if duplicate entry is to override the existing entry
                {
                    colYellow(); printf("\n[Y] OVERWRITE EXISTING ENTRY\n");
                    printf("[N] SKIP EXISTING ENTRY IMPORT\n"); colReset();
                    dupChoice = getch();
                } while (dupChoice != 'y' && dupChoice != 'n');

                switch (dupChoice)
                {
                    case 'y': // if yes, overhaul the existing entry to the imported entry's type and description
                        system ("cls");
                        colGreen(); printf("\n// OVERWRITING EXISTING ENTRY //\n");

                        overwrite = searchImport(&tempName[6], nPkCtr, pokemon);

                        if ( strcmp(&tempType[6],"Water") == 0 )
                        {
                            pokemon[overwrite].cPokeType = 'w';
                        }
                        else if ( strcmp(&tempType[6],"Fire") == 0 )
                        {
                            pokemon[overwrite].cPokeType = 'f';
                        }                
                        else if ( strcmp(&tempType[6],"Grass") == 0 )
                        {
                            pokemon[overwrite].cPokeType = 'g';
                        }
                        else if ( strcmp(&tempType[6],"Electric") == 0 )
                        {
                            pokemon[overwrite].cPokeType = 'e';
                        }
                        strcpy(pokemon[overwrite].cPokeDesc, &tempDesc[13]);

                        printf("\n// EXISTING ENTRY OVERWRITTEN //\n"); colReset();
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        system ("cls");
                        break;
                    
                    case 'n': // if no, continue
                        colRed(); printf("\n// IMPORT SKIPPED! //\n");
                        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
                        getch();
                        system("cls");
                        break;
                }
            }     
        }
        fclose(fp);
    }
    else
    {
        colCyan(); printf("// IMPORT ENTRY //\n");
        colRed(); printf("\n!! MAXIMUM ENTRIES REACHED !!\n");
        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n"); 
        getch();
    }
    return nPkCtr;
}

/*  searchImport() finds the index of the existing entry of the pokemon, utilized by import()
    @param key[] - the name of the already existing pokemon entry
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
int 
searchImport(char key[], int nPkCtr, struct pokemonstruct pokemon[])
{
    int i; // utilized by for-loop
    int found = -1; // found is initially -1, which means there is no duplicate

    for (i = 0; i < nPkCtr; i++)
    {
        if (strcmp(key, pokemon[i].cPokeName) == 0) // if the imported Name matches with an existing entry's name, return the index of such
            {
                found = i;
            }
    }
   
    return found;
}

/************************************************************************************************/
// RESEARCH TASK FUNCTIONS

/*  researchDisplayAllEntries() displays all entry names
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
*/
void 
researchDisplayAllEntries(int nPkCtr, struct pokemonstruct pokemon[]) // displaying all entries (with name only)
{
    int i = 0; // for loop
    char prevnext;

    if (nPkCtr == 0) // if there are no entries
    {  
        colYellow(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(46, 5); printf("REVIEW RESEARCH PER POKEMON\n");
        colRed(); gotoxy(57, 7); printf("!!!!!");
        gotoxy(52, 8); printf("NO ENTRIES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else if (nPkCtr > 1)// if there are existing pokemon entries, display its names and entry#
    {
        

        do
        {
            if (i < 0) // when i is less than 0, it defaults to i = 0, triggered when user clicks PREVIOUS on Entry #1
            {
                i = 0;
            }
            else if (i == nPkCtr) // when i is greater than nPkCtr, it defaults to decrementing, triggered when the user clicks NEXT on Last Entry
            {
                i--;
            }

            gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL RESEARCH ENTRIES //\n");
            gotoxy(1,3); printf(" ");

            colCyan(); printf("\n || ENTRY #%d ||\n", i+1);
            colGreen(); printf("\n POKEMON NAME: %s\n", pokemon[i].cPokeName); colReset(); 

            colCyan(); printf("\n [P] PREVIOUS [N] NEXT\n"); // prompts user if they will return to previous entry or to the next
            colCyan(); printf("\n [X] EXIT\n"); // once triggered, will exit the function
            prevnext = getch();

            switch (prevnext)
            {
            case 'p':
                system("cls");
                gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL RESEARCH ENTRIES //\n");
                gotoxy(1,3); printf(" ");
                i--;
                break;
            
            case 'n':
                system("cls");
                gotoxy(1,2); colYellow (); printf("// DISPLAYING ALL RESEARCH ENTRIES //\n");
                gotoxy(1,3); printf(" ");
                i++;
                break;

            case 'x':
                // exit
                break;
            
            default:
                break;
            }
        } while (prevnext != 'x');
    }
}

/*  researchDisplayEntry() displays all entries and their corresponding task type values
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
    @param nRsrchCtr - the research task number value
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
void 
researchDisplayEntry(int i, struct pokemonstruct pokemon[],  int nRsrchCtr, String sRsrchName[]) // displays entry alongside its research task types
{
    int j;

        colCyan(); printf("\n || ENTRY #%d ||\n", pokemon[i].entry);
        colCyan(); printf("\n POKEMON NAME: %s\n", pokemon[i].cPokeName); colReset();

        for (j = 0; j < nRsrchCtr; j++) // print all the research task types of the entry passed upon the function
        {
            switch (j)
            {
            case 0:
                colGreen(); printf(" %s: %d \n",sRsrchName[j], pokemon[i].nResearchType[j]);
                break;
            case 1:
                colRed(); printf(" %s: %d \n",sRsrchName[j], pokemon[i].nResearchType[j]);
                break;
            case 2:
                colPurple(); printf(" %s: %d \n",sRsrchName[j], pokemon[i].nResearchType[j]);
                break;
            case 3:
                colYellow(); printf(" %s: %d \n",sRsrchName[j], pokemon[i].nResearchType[j]);
                break;
            case 4:
                colBlue(); printf(" %s: %d \n",sRsrchName[j], pokemon[i].nResearchType[j]);
                break;

            default:
                break;
            }
        }
}

/*  reviewResearchPerPokemon() asks user which entry to review, then displays all of its correspondings research tasks
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
    @param nRsrchCtr - the research task number value
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
void 
reviewResearchPerPokemon(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]) // Review Research Task per Pokemon
{
    int entry; // entry is for the entry to find
    
    if (nPkCtr == 0)
    {
        colYellow();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(46, 5); printf("REVIEW RESEARCH PER POKEMON\n");

        colRed();
        gotoxy(57, 7); printf("!!!!");
        gotoxy(51, 8); printf("NO ENTRIES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else
    {
        do // if the inputted value is within the range of nPkCtr
        {   
            system ("cls"); 
            researchDisplayAllEntries(nPkCtr, pokemon); // displaying all Pokemon Entries with names

            colYellow(); boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
            gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");
            gotoxy(51, 8); printf("CHOOSE ENTRY TO REVIEW:");
            gotoxy(51, 9); scanf(" %d", &entry);

            if (entry > nPkCtr || entry <= 0 ) // if entry is invalid within the given conditions, reprompt
            {
                system("cls");
                colYellow(); boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
                gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");
                gotoxy(60, 7); colRed(); printf("OOPS!");
                gotoxy(50, 8); colRed(); printf("THIS ENTRY DOESN'T EXIST.");
                gotoxy(50, 11); colYellow(); printf("*PRESS ANY KEY TO RETRY*"); colReset();
                getch();
            }
        } while (entry > nPkCtr || entry <= 0 ); // this will happen until valid number is inputted

        system ("cls");
        printf("// REVIEW RESEARCH PER POKEMON RESULTS // \n");
        researchDisplayEntry(entry-1, pokemon, nRsrchCtr, sRsrchName); // displays the research task types of the chosen entry
        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n"); colReset();
        getch();
    }
}

/*  displayResTaskType() utilized by the researchTask functions to easily display all existing research task types
    @param nRsrchCtr - the research task number value
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
void 
displayResTaskType(int nRsrchCtr, String sRsrchName[]) // Display the lists of Research Task Types
{
    int j;

        for (j = 0; j < nRsrchCtr; j++)
        {
            switch (j)
            {
            case 0:
                gotoxy(49, 9); printf("[1] %s", sRsrchName[j]); // displays [1] SEEN
                break;
            case 1:
                gotoxy(49, 10); printf("[2] %s", sRsrchName[j]); // displays [2] DEFEATED
                break;
            case 2:
                gotoxy(49, 11); printf("[3] %s", sRsrchName[j]); // displays [3] ADDITIONAL TASK TYPE
                break;
            case 3:
                gotoxy(49, 12); printf("[4] %s", sRsrchName[j]); // displays [4] ADDITIONAL TASK TYPE
                break;
            case 4:
                gotoxy(49, 13); printf("[5] %s", sRsrchName[j]); // displays [5] ADDITIONAL TASK TYPE
                break;            
            default:
                break;
            }
        }
}

/*  reviewResearchPerType() asks user which which type to review, then displays all pokemon entries with task values > 0, corresponding to such
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
    @param nRsrchCtr - the research task number value
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
void 
reviewResearchPerType(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]) // Review Research Task per Task Type
{
    int i = 0;
    int exist = 0;
    int inType = 0;

    do // asks user to input the task type they wish to review 
    {
        system ("cls");
        colYellow(); boxMaker(46, 81, 4, 21, 47, 80, 5, 20);
        gotoxy(52, 5); printf("REVIEW RESEARCH PER TYPE");
        gotoxy(49, 8); printf ("SELECT RESEARCH TYPE TO REVIEW");
        displayResTaskType(nRsrchCtr, sRsrchName); // displays the list of existing research task types
        gotoxy (49, 15); printf("ENTER VALUE: "); 
        scanf(" %d", &inType); // stores the value inputted by user

        if (inType <= 0 || inType > nRsrchCtr) // if inType value is <= 0 and > the ResearchCounter of which maxes out at 5, reprompt
        {
            system("cls"); colYellow(); boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
            gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");
            gotoxy(60, 7); colRed(); printf("OOPS!");
            gotoxy(50, 8); colRed(); printf("THIS TYPE DOESN'T EXIST.");
            gotoxy(50, 11); colYellow(); printf("*PRESS ANY KEY TO RETRY*"); colReset();
            getch();
        }

    } while (inType <= 0 || inType > nRsrchCtr);

    inType--; // decrement inType to match the nResearchType index
    
    for (i = 0; i < nPkCtr; i++) // for displaying the entries
    {
        if(pokemon[i].nResearchType[inType] > 0) // if value is 0, do not include in the display
        {
            system("cls");
            colYellow(); printf("// REVIEW RESEARCH PER TYPE RESULTS //\n\n");
            displayEntryByResTaskType(i, pokemon, inType, sRsrchName); //display entry with the specific research task
            exist = 1; // implies that a match has been found
            colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n"); colReset();
            getch();
        }
    }
    
    if (exist == 0) // if all entries value of task type is 0
    {
        system ("cls");
        colYellow(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(47, 5); printf("REVIEW RESEARCH PER TYPE\n");
        colRed(); gotoxy(57, 7); printf("!!!!");
        gotoxy(51, 8); printf("NO MATCHES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }

    showTopFive(nPkCtr,pokemon, nRsrchCtr, inType, sRsrchName); // shows the top pokemons of a particular research type, which maxes out at 5 top entries
}

/*  displayEntryByResTaskType() display entry with the specific research task, utilized by reviewResearchPerType()
    @param pokemon[] - passes the pokemon struct from int main()
    @param inType - the index of the nRsrchCtr of which corresponds to the different task types ~ [0] Seen, [1] Defeated,[2-4] Add Research Task 
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
void 
displayEntryByResTaskType(int i, struct pokemonstruct pokemon[], int inType, String sRsrchName[]) // display entry with the specific research task
{
        colCyan(); printf(" || ENTRY NO. %d ||\n", pokemon[i].entry); // prints entry no.
        colPurple(); printf(" POKEMON NAME: %s\n", pokemon[i].cPokeName); // prints Pokemon Name

        switch (inType) // when called, displays the entry and the specific research task type being used
        {
            case 0:
                colGreen(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[i].nResearchType[inType]);
                break;
            case 1:
                colRed(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[i].nResearchType[inType]);
                break;
            case 2:
                colPurple(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[i].nResearchType[inType]);
                break;
            case 3:
                colYellow(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[i].nResearchType[inType]);
                break;
            case 4:
                colBlue(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[i].nResearchType[inType]);
                break;
            default:
                break;
        }
}

/*  updateResearchTask() updates the values of existing research task types
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
    @param nRsrchCtr - the research task number value
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
void 
updateResearchTask(int nPkCtr, struct pokemonstruct pokemon[], int nRsrchCtr, String sRsrchName[]) //Update Research Task
{
    int inType,entry,nValue;
    int i = 0;
    int exist = 0;

    do // asks user of which research task to update 
    { 
        system ("cls");
        colYellow(); boxMaker(46, 81, 4, 17, 47, 80, 5, 16);
        gotoxy(54, 5); printf("UPDATE RESEARCH TASK");
        gotoxy(49, 8); printf ("SELECT RESEARCH TYPE TO UPDATE");
        displayResTaskType(nRsrchCtr, sRsrchName); // for displaying the lists of research task type
        gotoxy (49, 15); printf("ENTER TYPE VALUE: "); scanf(" %d", &inType);

        if (inType <= 0 || inType > nRsrchCtr) // if inType value is <= 0 and > the ResearchCounter of which maxes out at 5, reprompt
        {
            system("cls");
            colYellow(); boxMaker(46, 78, 4, 12, 47, 77, 5, 11);
            gotoxy(49, 5); printf("REVIEW RESEARCH PER POKEMON");
            gotoxy(60, 7); colRed(); printf("OOPS!");
            gotoxy(50, 8); colRed(); printf("THIS TYPE DOESN'T EXIST.");
            gotoxy(50, 11); colYellow(); printf("*PRESS ANY KEY TO RETRY*"); colReset();
            getch();
        }
    } while (inType <= 0 || inType > nRsrchCtr);

    inType--; // decrement inType to match the nResearchType index
    
    if (nPkCtr == 0) // if there are no existing entries
    {
        system ("cls");
        colYellow();
        boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
        gotoxy(49, 5); printf("UPDATE RESEARCH TASK\n");

        colRed();
        gotoxy(56, 7); printf("!!!!!");
        gotoxy(51, 8); printf("NO ENTRIES FOUND");
        colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
        getch();
    }
    else
    {
        do // asks user what entry to update
        {
            system ("cls");
            researchDisplayAllEntries(nPkCtr,pokemon);   
            colYellow();
            boxMaker(46, 81, 4, 13, 47, 80, 5, 12);
            gotoxy(54, 5); printf("UPDATE RESEARCH TASK");
            gotoxy(49, 8); printf ("CHOOSE ENTRY TO UPDATE");
            gotoxy (49, 9); printf("ENTER ENTRY #: "); scanf(" %d", &entry);
        
            if (entry > nPkCtr || entry <= 0 ) // if entry value is <= 0 and > the nPkCtr, reprompt
            {
                system ("cls");
                colYellow(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11);
                gotoxy(49, 5); printf("UPDATE RESEARCH TASK\n");
                colRed(); gotoxy(57, 7); printf("!!!!!");
                gotoxy(48, 8); printf("THIS ENTRY DOESN'T EXIST");
                colYellow(); gotoxy(46, 11); printf("*PRESS ANY KEY TO CONTINUE*");
                getch();
            }
        } while (entry > nPkCtr || entry <= 0 ); // this will happen until valid number is inputted

            entry--; // decrement entry to match the index of the pokemon[i].entry struct variable
    
            do // reprompt when user inputs a negative number in increment value
            {
                system ("cls");
                colYellow(); boxMaker(43, 84, 4, 20, 44, 83, 5, 19);
                gotoxy(54, 5); printf("UPDATE RESEARCH TASK");
                gotoxy(46, 9); printf("ENTRY NO. %d\n", pokemon[entry].entry); // prints entry no.
                gotoxy(46, 10); printf("POKEMON NAME: %s\n", pokemon[entry].cPokeName); // prints Pokemon Name

                switch (inType) // displays the research task type being update through inType
                {
                    case 0:
                        gotoxy(46,11); colGreen(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[entry].nResearchType[inType]);
                        break;
                    case 1:
                        gotoxy(46,11);  colRed(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[entry].nResearchType[inType]);
                        break;
                    case 2:
                        gotoxy(46,11);  colPurple(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[entry].nResearchType[inType]);
                        break;
                    case 3:
                        gotoxy(46,11);  colYellow(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[entry].nResearchType[inType]);
                        break;
                    case 4:
                        gotoxy(46,11);  colBlue(); printf(" %s: %d \n",sRsrchName[inType],  pokemon[entry].nResearchType[inType]);
                        break;
                    default:
                        break;
                }
            
                gotoxy(46, 13); colCyan(); printf("ENTER INCREMENT AMOUNT: ");
                gotoxy(46, 14); scanf(" %d", &nValue);

                if (nValue < 0) // increment value is a negative number
                {
                    gotoxy(46, 16); colRed(); printf("!! YOU CANNOT DECREMENT !!");
                    gotoxy(46, 17); colYellow(); printf("// PRESS ANY KEY TO CONTINUE //");
                    getch();
                }
            } while (nValue < 0);
            
            pokemon[entry].nResearchType[inType] = pokemon[entry].nResearchType[inType] + nValue; // increments the value of the task type of chosen entry

            gotoxy(51, 19); colYellow(); printf("*PRESS ANY KEY TO CONTINUE*");

            gotoxy(1, 2); printf("// UPDATED ENTRY //"); // displays the entry
            gotoxy(1, 3); researchDisplayEntry(entry, pokemon, nRsrchCtr, sRsrchName); // display the entry for correction to the user
            getch();
    }

}

/*  showTopFive() shows the top pokemon entries of a particular research type, displaying a maximum of five entries
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param pokemon[] - passes the pokemon struct from int main()
    @param nRsrchCtr - the research task number value
    @param inType - the index of the nRsrchCtr of which corresponds to the different task types ~ [0] Seen, [1] Defeated,[2-4] Add Research Task 
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/

/********************************************************************************************************/
// BONUS FUNCTIONS

void 
showTopFive(int nPkCtr, struct pokemonstruct pokemon[],int nRsrchCtr, int inType, String sRsrchName[])
{
    int i, j, k, h, min, temp; 
    int A[ENTRYMAX]; // temporarily stores the index numbers in A[]

    // for initializing the temporary entry numbers
    for (k = 0; k < ENTRYMAX; k++) 
    {
        A[k] = k; // A[0] = 0;
    }
    
    // swap sort algorithm
    for (i = 0; i < nPkCtr - 1; i++) 
    { 
        min = i; // min is the index of the lowest element

        for (j = i + 1; j < nPkCtr; j++) // sort in minimum
        {
             if (pokemon[A[min]].nResearchType[inType]  < pokemon[A[j]].nResearchType[inType] ) // FOR STRUCTS; A[min].resTaskTYpe[inType]  < A[j].resTasktpe[inType]
             {   
                min = j; // stores the entry [j] with the lowest value within the given task type in min
             }
        }

        // swap function
        if (i != min) 
        {
            temp = A[i]; 
            A[i] = A[min]; 
            A[min] = temp;
        }
    }

    if (nPkCtr >= 5)
    {
        if(pokemon[A[0]].nResearchType[inType] > 0) // this is to check if the highest has a value, pag wala, it means 0 lahat and therefore, no top 5
        {
            system("cls");
            colYellow(); printf("\n// TOP POKEMONS (MAX. 5) //\n\n");
        } 
        else 
        {
            system("cls");
            colRed(); printf("\n// NO TOP FIVE POKEMONS //\n\n");
        }

        for (h = 0; h < 5; h++) // this will print the top 5 pokemons of the given research task
        {
            if(pokemon[A[h]].nResearchType[inType] > 0)
            {
                displayEntryByResTaskType(A[h], pokemon, inType, sRsrchName); // display entry with the specific research task
                printf("\n");
            }
            
        }
        colYellow(); printf("// PRESS ANY KEY TO CONTINUE //\n");
        getch();        
    }    
}

/*  addResearchTaskType() asks the user to add a research type in relation to the already existing Seen and Defeated tasks of which has a maximum of 5 tasks
    @param nRsrchCtr - the research task number value
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
int 
addResearchTaskType(int nRsrchCtr, String sRsrchName[])
{
    int i;
    String tempName;

    system("cls");
    gotoxy(1, 1); // reset to top-right
    colYellow(); printf("\n// ADD RESEARCH TASK TYPE //\n"); 
    
    printf("\n EXISTING RESEARCH TASKS\n");
    for (i = 0; i < nRsrchCtr; i++)
    {
        printf(" %s \n", sRsrchName[i]); // displays all existing research tasks
    }

    if (nRsrchCtr >= 5) // if there are 5 research tasks, no more can be added
    {
       colRed(); printf("\n!! MAXIMUM RESEARCH TASKS REACHED. !!\n"); 
       colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
       getch();
    } 
    else 
    {

        printf("\nINPUT RESEARCH TASK TO ADD: ");
        scanf(" %[^\n]s", &tempName); // asks user to input the name of the research task to be added

        if (SearchRsrch(tempName, nRsrchCtr, sRsrchName) == 1) // if research task already exists, break
        {
            colRed(); printf("\nRESEARCH TASK EXISTS\n");
        }
        else // otherwise, store the added research task in its own index
        {
            strcpy(sRsrchName[nRsrchCtr], tempName); // stores the name of the added research task to the sRsrchName of which stores all research task types
            nRsrchCtr++; // Research Counter is incremented since added reserach task is valid
            colGreen(); printf("\nRESEARCH TASK ADDED.\n");
        }
        colYellow(); printf("\n// PRESS ANY KEY TO CONTINUE //\n");
        getch();
    }

    return nRsrchCtr;
}

/*  SearchRsrch() finds for any duplicate addResearch entries, utilized by addResearchTaskType()
    @param key[] - the name of the intended research task type to be added
    @param nPkCtr - the entry number being triggered, overall entries within the PokeDex
    @param sRsrchName[] - the name of research tasks ~ [0] Seen, [1] Defeated, [2-4] Add Research Task
*/
int 
SearchRsrch(char key[], int nPkCtr, String sRsrchName[])
{
   int i;
   int found = -1; // found is initially -1, meaning no duplicates found

   for (i = 0; i < nPkCtr; i++)
   {
      if (strcmp(key, sRsrchName[i]) == 0) // if research task to be added matches an already existing task, return found = 1
         {
            found = 1;
         }
   }
   
   if (found == 1)
   {
      return 1;
   } else
   {
      return -1;
   }
}

/************************************************************************************************************/
// CODE DESIGN/UI FUNCTIONS

/* gotoxy() places succeeding lines of print() to the coordinates passed onto it 
    @param x - x-coordinate
    @param y - y-coordinate
*/
void 
gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

/* colReset() resets color to White */
void 
colReset()
{
    printf("\033[0;37m");
}

/* colCyan() changes color to Cyan */
void 
colCyan()
{
    printf("\033[0;36m");
}

/* colBlue() changes color to Blue */
void 
colBlue()
{
    printf("\033[0;34m");
}

/* colRed() changes color to Red */
void 
colRed()
{
    printf("\033[0;31m");
}

/* colYellow() changes color to Yellow */
void 
colYellow()
{
    printf("\033[0;33m");
}

/* colGreen() changes color to Green */
void 
colGreen()
{
    printf("\033[0;32m");
}

/* colPurple() changes color to Purple */
void 
colPurple()
{
    printf("\033[0;35m");
}