#include "monty.h"

FILE *fd = NULL;

/**
 * main - the entry to the file!
 * @ac: number of args passed
 * @av: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
    FILE *fd;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    stack_t *stack = NULL;
    unsigned int line_number = 0;
    char **args;
    void (*op_func)(stack_t **stack, char **args, unsigned int l);

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    fd = fopen(argv[1], "r");
    if (fd == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fd)) != -1)
    {
        line_number++;
        args = tokenize(line);
        if (args[0] == NULL || args[0][0] == '#')
        {
            free_tokens(args);
            continue;
        }

        op_func = getopfunc(&stack, args, line_number);
        if (op_func == NULL)
        {
            free(line);
            fclose(fd);
            exit(EXIT_FAILURE);
        }

        op_func(&stack, args, line_number);
        free_tokens(args);
    }

    free(line);
    fclose(fd);
    free_stack(&stack);
    return (EXIT_SUCCESS);
}

/**
 * tokenize - tokenizes buffer
 * @tokens: the token bucket
 * @buffer: the buffer we're reading from
 *
 * Return: no return
 */
void tokenize_recursive(char **tokens, char *buffer, int i)
{
    char *token;

    token = strtok(buffer, " \t\n$");
    if (token == NULL)
    {
        tokens[i] = NULL;
        return;
    }

    tokens[i] = malloc(strlen(token) + 1);
    if (tokens[i] == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        free_tokens(tokens);
        return;
    }
    strcpy(tokens[i], token);
    tokenize_recursive(tokens, strtok(NULL, " "), i + 1);
}

void tokenize(char **tokens, char *buffer)
{
    san_buffer(buffer);
    tokenize_recursive(tokens, buffer, 0);
}

/**
 * free_tokens - frees token array
 * @tokens: the array of tokens to free
 *
 * Return: no return
 */
void free_tokens_recursive(char **tokens, int i)
{
    if (tokens[i] == NULL)
    {
        return;
    }
    free(tokens[i]);
    tokens[i] = NULL;
    free_tokens_recursive(tokens, i + 1);
}

void free_tokens(char **tokens)
{
    free_tokens_recursive(tokens, 0);
}

int empty_recursive(char *buffer, int i)
{
    if (buffer[i] == '\0')
    {
        return (-1);
    }
    if (isalnum(buffer[i]))
    {
        return (1);
    }
    return empty_recursive(buffer, i + 1);
}

int empty(char *buffer)
{
    return empty_recursive(buffer, 0);
}
