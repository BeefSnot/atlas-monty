#include "monty.h"

/**
 * pint()- prints top of  stack
 * @stack: the stack
 * @args: the arg array
 * @l: the line number
 *
 * Return: no return
 */

void pint(stack_t **stack, char **arg, unsigned int l)
{
    (void)arg;

    do {
        if (!(*stack))
        {
            fprintf(stderr, "L%u: can't pint, stack empty\n", l);
            free_stack(stack);
            fclose(fd);
            exit(EXIT_FAILURE);
        }
    } while (0);

    printf("%d\n", (*stack)->n);
}

/**
 * pop()- pops a node from stack
 * @stack: the stack
 * @args: the arg array
 * @l: the line number
 *
 * Return: no return
 */

void pop(stack_t **stack, char **arg, unsigned int l)
{
    stack_t *current;
    stack_t *tmp;

    do {
        if (!(*stack))
        {
            fprintf(stderr, "L%u: can't pop an empty stack\n", l);
            free_stack(stack);
            fclose(fd);
            exit(EXIT_FAILURE);
        }
    } while (0);

    (void)arg;
    current = *stack;
    if (current->next != NULL)
    {	
        tmp = current->next;
        tmp->prev = NULL;
        *stack = current->next;
    }
    free(current);
}

/**
 * swap()- swaps top two nodes of stack
 * @stack: the stack
 * @args: the arg array
 * @l: the line number
 *
 * Return: no return
 */

void swap(stack_t **stack, char **arg, unsigned int l)
{
    int nodecount, temp;
    stack_t *current;

    (void)arg;
    temp = (*stack)->n;
    nodecount = 0;
    current = *stack;
    while (current != NULL)
    {
        nodecount++;
        current = current->next;
    }

    do {
        if (nodecount < 2)
        {
            fprintf(stderr, "L%u: can't swap, stack too short\n", l);
            free_stack(stack);
            fclose(fd);
            exit(EXIT_FAILURE);
        }
    } while (0);

    current = *stack;
    current->n = (current->next)->n;
    (current->next)->n = temp;
}

/**
 * add()- adds value of top two nodes n deletes top
 * @stack: the stack
 * @args: the arg array
 * @l: the line number
 *
 * Return: no return
 */


void add(stack_t **stack, char **arg, unsigned int l)
{
    int nodecount, val;
    stack_t *current;
    stack_t *tmp;

    (void)arg;
    nodecount = 0;
    current = *stack;
    tmp = current->next;
    while (current != NULL)
    {
        nodecount++;
        current = current->next;
    }

    do {
        if (nodecount < 2)
        {
            fprintf(stderr, "L%u: can't add, stack too short\n", l);
            free_stack(stack);
            fclose(fd);
            exit(EXIT_FAILURE);
        }
    } while (0);

    current = *stack;
    val = current->n;
    tmp->n += val;
    tmp->prev = NULL;
    (*stack) = tmp;
    free(current);
}

/**
 * nop()- does nothing!
 * @stack: the stack
 * @args: the arg array
 * @l: the line number
 *
 * Return: no return
 */

void nop(stack_t **stack, char **arg, unsigned int l)
{
    (void)stack;
    (void)arg;

    switch (l)
    {
    case 0:
        break;
    case 1:
        printf("Case 1: No operation\n");
        break;
    default:
        printf("Default case: No operation\n");
        break;
    }
}
