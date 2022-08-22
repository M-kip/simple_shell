#include "main.h"
#include <stdlib.h>
/**
* main - main driver function
* @argc: number of args
* @argv: array to store args
*
* Description: This function is the driver to
* our shell function
* Return: 0 on success and 1 on failure
*/
int main(int argc, char *argv[])
{
	int int_mode = isatty(STDIN_FILENO);
	char *buffer;
	size_t size = 32;
    size_t characters;
    char *token;
    char **tokens;
    char *delimeter = " :'\t''\n'";
    int counter = 0;
    int ret;

    tokens = (char **)malloc(sizeof(char *) * size);
    buffer = (char *)malloc(sizeof(char) * size);
    if ((buffer == NULL) | (tokens == NULL))
    {
        perror("unable to allocate memory");
        exit(EXIT_FAILURE);
    }
    while (int_mode)
    {
        int_mode = isatty(STDIN_FILENO);
        if (int_mode == 1)
        {
            write(STDOUT_FILENO, "($)",3);
        }
        characters = getline(&buffer, &size, stdin);
        token = strtok(buffer, delimeter);
        if (token == NULL)
        {
            perror("No tokens created");
            exit(EXIT_FAILURE);
        }

        while (token != NULL)
        {
            tokens[counter] = strdup(token);
            token = strtok(NULL, delimeter);
            counter++;
        }
        tokens[counter] = token;

        ret = fork();
        if (ret == 0)
        {
           if (execve(tokens[0], tokens, NULL) == -1)
           {
               perror("unknown command");
               exit(EXIT_FAILURE);
           }
        }
        else if (ret < -1)
        {
            perror("could not create child process");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }

    } /* while */
    
    return (0);
} /* main */
