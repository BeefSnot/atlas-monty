#include "monty.h"

FILE *fd = NULL;

/**
 * main()- the entry to the file!
 * @ac: number of args passed
 * @av: argument vector
 *
 * Return: 0 on success
 */

int main(int ac, char **av)
{
    char *buffer;
    char **tokens;
    size_t n, linenum;
    ssize_t neg;
    int status;
    stack_t *stack = NULL;

    n = 0, status = 0; neg = -1, linenum = 1, buffer = NULL;
    tokens = malloc(sizeof(char *) * 100);
    if (ac < 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    fd = fopen(av[1], "r");
    if (fd == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", av[1]);
        exit(EXIT_FAILURE);
    }
read_line:
    if ((getline(&buffer, &n, fd)) != neg)
    {
        if (empty(buffer) < 0)
        {
            linenum++;
            goto read_line;
        }
        tokenize(tokens, buffer);
        getopfunc(&stack, tokens, linenum)(&stack, tokens, linenum);
        free_tokens(tokens);
        linenum++;
        goto read_line;
    }
    free(buffer);
    free(tokens);
    free_stack(&stack);
    fclose(fd);
    if (status < 0)
    {
        exit(EXIT_FAILURE);
    }
    return (0);
}

/**
 * tokenize()- tokenizes buffer
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
        printf("Token failed!");
        fprintf(stderr, "Could not allocate memory for token");
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
 * free_tokens()- frees token array
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
