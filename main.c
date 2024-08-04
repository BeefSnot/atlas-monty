FILE *fd = NULL;

/**
 * main - the entry to the file!
 * @ac: number of args passed
 * @av: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int ac, char **av)
{
    char *buffer = NULL;
    char **tokens;
    size_t n = 0;
    ssize_t neg = -1;
    unsigned int linenum = 1;
    int status = 0;
    stack_t *stack = NULL;

    tokens = malloc(sizeof(char *) * 100);
    if (tokens == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    if (ac < 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        free(tokens);
        exit(EXIT_FAILURE);
    }

    fd = fopen(av[1], "r");
    if (fd == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", av[1]);
        free(tokens);
        exit(EXIT_FAILURE);
    }

    while ((getline(&buffer, &n, fd)) != neg)
    {
        if (empty(buffer) < 0)
        {
            linenum++;
            continue;
        }
        tokenize(tokens, buffer);
        if (getopfunc(&stack, tokens, linenum) == NULL)
        {
            status = 1;
            break;
        }
        getopfunc(&stack, tokens, linenum)(&stack, tokens, linenum);
        free_tokens(tokens);
        linenum++;
    }

    free(buffer);
    free(tokens);
    free_stack(&stack);
    fclose(fd);

    if (status != 0)
    {
        exit(EXIT_FAILURE);
    }

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
