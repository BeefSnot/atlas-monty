#include "monty.h"

/**
 * getopfunc()- gets a pointer to the operation!
 * @s: the op to compare to!
 * @stack: the stack!
 * @l: the line count!
 */

void (*getopfunc_recursive(stack_t **stack, char **args, unsigned int l, instruction_t *ops, int i))(stack_t **stack, char **args, unsigned int l)
{
    if (ops[i].opcode == NULL)
    {
        fprintf(stderr, "L%u: unknown instruction %s\n", l, args[0]);
        free_stack(stack);
        free_tokens(args);
        free(args);
        fclose(fd);
        exit(EXIT_FAILURE);
    }

    if (strcmp(args[0], ops[i].opcode) == 0)
    {
        return (ops[i].f);
    }

    return getopfunc_recursive(stack, args, l, ops, i + 1);
}

void (*getopfunc(stack_t **stack, char **args, unsigned int l))(stack_t **stack, char **args, unsigned int l)
{
    instruction_t ops[] = {
        {"push", push},
        {"pall", pall},
        {"pint", pint},
        {"pop", pop},
        {"swap", swap},
        {"add", add},
        {"nop", nop},
        {NULL, NULL}
    };

    return getopfunc_recursive(stack, args, l, ops, 0);
}
/**
 * push - pushes a new node to the stack
 * @stack: double pointer to the stack
 * @args: array of arguments
 * @l: line number
 */
void push(stack_t **stack, char **args, unsigned int l)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    stack_t *tmp;

    if (!args[1])
    {
        fprintf(stderr, "L%u: usage: push integer\n", l);
        free_stack(stack);
        free_tokens(args);
        free(args);
        fclose(fd);
        exit(EXIT_FAILURE);
    }
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        free_stack(stack);
        free_tokens(args);
        free(args);
        fclose(fd);
        exit(EXIT_FAILURE);
    }
    if (*stack)
    {
        tmp = *stack;
        tmp->prev = new_node;
    }
    new_node->n = atoi(args[1]);
    new_node->next = *stack;
    new_node->prev = NULL;
    *stack = new_node;
}

/**
 * pall()- prints stack
 * @stack: the stack
 * @args: the arg array
 * @l: the line number
 *
 * Return: no return
 */

void pall(stack_t **stack, char **args, unsigned int l)
{
	size_t  nodecount;
	stack_t *current = *stack;

	(void)args;
	(void)l;
	nodecount = 0;
	while (current != NULL)
	{
		printf("%d\n",current->n);
		current = current->next;
		nodecount++;
	}
}

/**
 * free_stack()- frees a stack
 * @stack: the stack
 *
 * Return: no return
 */

void free_stack(stack_t **stack)
{
	stack_t *current = *stack;

	while (current != NULL)
	{
		stack_t *next = current->next;
		free(current);
		current = next;
	}
}
