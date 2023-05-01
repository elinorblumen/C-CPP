/**
 * Source file that contains the main function and runs the program
 * using the header cipher.h file.
 * @author: ElinorB
 */
#ifndef BONUS
#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEFAULT_SIZE 11
#define READ_SIZE 10
#define ARGUMENTS_NUM 5
#define NUM_BASE 10

/**
 * Main function. receives two arguments from user input.
 * @param argc number of arguments
 * @param argv 4 arguments: [command-encode/decode, k-number of
 * cyclic indentation, output file address, input file address].
 * @return EXIT_FAILURE if failed to run the program, EXIT_SUCCESS otherwise.
 */
int main(int argc, const char *argv[]){

    int shifts_val;

    // Checks for correct num of arguments from user.
    if(argc != ARGUMENTS_NUM){
        fprintf (stderr, "Usage: cipher <encode|decode> <k> <source "
                         "path file> <output path file>\n");
        return EXIT_FAILURE;
    }

    // Checks the given shifts value is valid
    char *next;
    long val = strtol (argv[2], &next, NUM_BASE);
    if((*next != '\0')||(round (val)!=val)){
        fprintf (stderr, "The given shifts value is invalid\n");
        return EXIT_FAILURE;
    }
    shifts_val = (int) val;

    // Checks for correct command argument
    if((strcmp(argv[1], "encode")!=0)&&(strcmp(argv[1], "decode")!=0)){
        fprintf (stderr, "The given command is invalid\n");
        return EXIT_FAILURE;
    }

    // Checks the input file is valid and creates file structs for
    // input and output files.
    FILE *input_file, *output_file;
    input_file = fopen(argv[3], "r");
    if (input_file == NULL){
        fprintf (stderr, "The given file is invalid\n");
        return EXIT_FAILURE;
    }
    output_file = fopen(argv[4], "w");
    if (output_file == NULL){ // If output file is invalid,
      // creates a new output file
        output_file = fopen("output.txt", "w");
    }
    char buffer[DEFAULT_SIZE] = {0};
    while (fgets (buffer, READ_SIZE, input_file) != NULL)
      {
        if(strcmp(argv[1], "encode") == 0){
            encode (buffer, shifts_val);
            fprintf (output_file, "%s", buffer);
        }
        else{
            decode (buffer, shifts_val);
            fprintf (output_file, "%s", buffer);
        }
      }
    fclose (input_file);
    fclose (output_file);
    return 0;
}

#endif
