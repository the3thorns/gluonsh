/*
    Function name: gluonsh_modifier_action
    Macro name: GSH_PROPERTY_NAME    
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> // fork()
#include <sys/wait.h>   // wait()

#define GSH_BUFFER_SIZE             64
#define GSH_TOKENS_LIST_SIZE        10

char *gluonsh_read_line(void);
char **gluonsh_get_arguments(char *raw_text);
void gluonsh_exec_program(char **arguments);


int main (int argc, char **argv) {

    printf("gluonsh >> ");

    char *input = gluonsh_read_line();
    char **tokens = gluonsh_get_arguments(input); // tokenize function
    gluonsh_exec_program(tokens);

    // Free both input and tokens
    free(input);
    free(tokens);

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

    // TODO: Mejorar con do-while
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
 * The separator is the space character ' '
 * TODO: Fix function
*/

char **gluonsh_get_arguments(char *raw_text) {
    // Up to 10 tokens before reallocating
    char **tokens_list = (char**) malloc(sizeof(char*) * GSH_TOKENS_LIST_SIZE);
    int tokens_list_size = GSH_TOKENS_LIST_SIZE;
    int tokens_list_position = 0;
    int raw_text_position = 0;
    
    while (raw_text[raw_text_position] != '\0') {
        //printf("Raw_text_pos: %d\n", raw_text_position);
        //printf("Tokens_list_pos: %d\n", tokens_list_position);

        if (raw_text_position == 0) {
            tokens_list[tokens_list_position] = raw_text;
            tokens_list_position++;
        } else if (raw_text[raw_text_position] == ' ') {
            raw_text[raw_text_position] = '\0';
        } else if (raw_text[raw_text_position - 1] == '\0') {
            tokens_list[tokens_list_position] = raw_text + (raw_text_position * sizeof(char));
            tokens_list_position++;
        }
        raw_text_position++;

        // reallocation process
        if (tokens_list_position + 1 >= tokens_list_size) {
            tokens_list_size += GSH_TOKENS_LIST_SIZE;
            tokens_list = (char**)realloc(tokens_list, tokens_list_size * sizeof(char**));
        }
    }

    tokens_list[tokens_list_position] = NULL;
    return tokens_list;
}

/**
 * * This function executes the arguments
*/

void gluonsh_exec_program(char **arguments) {
    if (fork() == 0) {
        execvp(arguments[0], arguments);
        perror("Error execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}