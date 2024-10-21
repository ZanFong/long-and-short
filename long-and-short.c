#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//define max string length
#define STR_LEN 1000

//init prototypes
void printError(int x);
void parseFile(char *readFile, char *upFile, char *lowFile, int *low, int *up);
int checkfile(FILE *file);
void printToFile(int check, char *line, FILE *filename);

//main function
//takes arguments from the command line
int main(int argc, char *argv[])
{
    //init vars to hold number of lines written
    int up = 0;
    int low = 0;

    //if there are more or less than 3 arguments (not including argv[0])
    if(argc < 4 || argc > 4)
    {
        printError(argc); //print error and exit program
        exit(1);
    }
    else
    {
        //call function to read from argv[1] and write to argv[2] and argv[3]
        //pass addresses for up and low variabls
        parseFile(argv[1], argv[2], argv[3], &low, &up);
    }

    //print how many lines were written to each file
    printf("%d lines written to %s\n%d lines written to %s\n", up, argv[2], low, argv[3]);

}

//function to print error message
void printError(int x)
{
    printf("Invalid number of arguments! 3 arguments expected, recieved %d.\n", x - 1); //x - 1 = number of args excluding argv[0]
}

//function to read from arg 1 and write to args 2 and 3
void parseFile(char *readFile, char *writeFile1, char *writeFile2, int *low, int *up)
{
    //open all files
    FILE *file = fopen(readFile, "r");
    FILE *upFile = fopen(writeFile1, "w");
    FILE *lowFile = fopen(writeFile2, "w");

    //check that each file opened correctly
    if(checkfile(file) || checkfile(upFile) || checkfile(lowFile))
    {
        printf("Unable to open one or more file!\n"); //if not, print error and exit program
        exit(1); 
    }

    //init vars to hold file line and number of lines written
    char line[STR_LEN];
    int upLines = 0;
    int lowLines = 0;

    //while not at EOF
    while (fgets(line, STR_LEN, file))
    {
        //if the length of the string is less than 20 characters
        if(strlen(line) < 20)
        {
            //call function to write to first file
            printToFile(1, line, upFile);
            upLines++; //increase count of lines written
        }
        else
        {
            //call function to write to second file
            printToFile(0, line, lowFile);
            lowLines++; //increase count of line written
        }
    }

    //set totals of line written
    *low = lowLines;
    *up = upLines;

    //close all files
    fclose(file);
    fclose(upFile);
    fclose(lowFile);
}

//function to check if a file failed to open
int checkfile(FILE *file)
{   
    //if null
    if(!file)
    {
        return 1;   //return true
    }
    else return 0;  //return false
}

//function to print the current line to a given file
void printToFile(int check, char *line, FILE *filename)
{
    //init string to store copy of the line 
    char str[strlen(line)];
    strcpy(str, line);

    //if check == 1
    if(check)
    {
        //for length of str
        for(int i = 0; i < strlen(str); i++)
        {   
            //change characters to uppercase
            str[i] = toupper((unsigned char)str[i]);
        }
    }
    //else if check == 0
    else
    {
        //for length of str
        for(int i = 0; i < strlen(str); i++)
        {   
            //change characters to lowercase
            str[i] = tolower((unsigned char)str[i]);
        }
    }
    

    //write str to the file
    fputs(str, filename);
}

