/*
    Name syntax
    - Project name: gluonsh

    Function name: gluonsh_modifier_action
    Macro name: GSH_PROPERTY_NAME
    
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define GSH_BUFFER_SIZE             64
#define GSH_TOKENS_LIST_SIZE        10

char *gluonsh_read_line(void);
char *gluonsh_get_arguments(char *raw_text);

int main (int argc, char **argv) {

    // ! There are not config statements in this shell    

    // TODO: Here there is a tokenize function

    // TODO: Here gluon execs the program in question

    // @test Tests go here

    char *input = gluonsh_read_line();
    printf("%s\n", input);
    free(input);

    return 0;
}


/*
    * This function reads user input and returns a pointer with the raw string. It has no arguments

*/

char *gluonsh_read_line(void) {
    // Initialize buffer to store the raw string
    char *buffer = (char*) malloc(sizeof(char) * GSH_BUFFER_SIZE);
    
    // Letter from the input stream (stdin)
    char letter = getchar();
    int buffer_position = 0;
    int buffer_size = GSH_BUFFER_SIZE;

    // Eliminate initial whitespaces

    while (letter == ' ') {
        letter = getchar();
    }

    buffer[buffer_position] = letter;
    buffer_position++;

    while (1) {
        letter = getchar();

        if (letter == EOF || letter == '\n') {
            buffer[buffer_position] = '\0';
            return buffer;
        }

        buffer[buffer_position] = letter;
        buffer_position++;

        // Check if a reallocation is needed

        if (buffer_position >= buffer_size) {
            buffer = realloc(buffer, buffer_size + GSH_BUFFER_SIZE);
            buffer_size+= GSH_BUFFER_SIZE;
        }
    }
}


/**
 * * Recieves raw text and tokenizes its contents
 * 
 * @param raw_text: A pointer to non-tokenized string and creates token that can be used as arguments
 * 
 * The tokens list must be adapted to execvp.
 * 
 * TODO: Create the function
*/

char *gluonsh_get_arguments(char *raw_text) {
    // Up to 10 tokens before reallocating
    char **tokens_list = (char**) malloc(sizeof(char**) * GSH_TOKENS_LIST_SIZE);
    int tokens_list_size = GSH_TOKENS_LIST_SIZE;
    char *token;
    int tokens_list_position = 0;
    int raw_text_position = 0;

    /**
     * The function iterates through @param raw_text and looks for leetters that are after spaces
     * or the first one.
     * 
     * When it finds a character it sends the address to tokens_list
    */

   while (raw_text[raw_text_position] != '\0') {
        if (raw_text_position == 0) {
            tokens_list[tokens_list_position] = raw_text;
        } else if (raw_text[raw_text_position - 1] == '\0') {
            tokens_list[tokens_list_position] = raw_text + (raw_text_position * sizeof(char));
            tokens_list_position++;
        } else if (raw_text[raw_text_position] == ' ') {
            raw_text[raw_text_position] = '\0';
        }
        raw_text_position++;

        // Reallocation process
        if (tokens_list_position + 1>= tokens_list_size) {
            tokens_list = realloc(tokens_list, tokens_list_size + GSH_TOKENS_LIST_SIZE);
            tokens_list_size += GSH_TOKENS_LIST_SIZE;
        }
    }
    tokens_list[tokens_list_position] = NULL;
   
}