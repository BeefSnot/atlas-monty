#include "monty.h"

/**
 * push - pushes a node to a stack
 * @h: head of stack
 * @ln: line num
 * Return: void
 */

void push(stack_t **h, __attribute((unused))unsigned int ln)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(37);
	}

	new->prev = NULL;

	if (*h == NULL)
	{
		new->next = NULL;
	}
	else
	{
		(*h)->prev = new;
		new->next = *h;
	}
	*h = new;
}


/**
 * pall - prints every value in a stack
 * @h: head of stack
 * @ln: line number
 * Return: void
 */

void pall(stack_t **h, __attribute__((unused))unsigned int ln)
{
	stack_t *temp = *h;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}


/**
 * pint - prints a value in the head of stack
 * * @h: head of node
 * @ln: line number
 * Return: void
 */

void pint(stack_t **h, unsigned int ln)
{
	if (*h == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", ln);
		isFail = 1;
		return;
	}
	printf("%d\n", (*h)->n);
}


/**
 * pop - pop! head
 * @h: head of stack
 * @ln: line number
 * Return: void
 */

void pop(stack_t **h, unsigned int ln)
{
	stack_t *temp = *h;

	if (*h == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", ln);
		isFail = 1;
		return;
	}
	*h = (*h)->next;
	free(temp);

}


/**
 * swap - swaps the top recent nodes on a stack
 * @h: head of stack
 * @ln: line number
 * Return: void
 */

void swap(stack_t **h, unsigned int ln)
{
	stack_t *temp;
	int x;

	if (*h == NULL || (*h)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", ln);
		isFail = 1;
		return;
	}
	temp = (*h)->next;
	x = (*h)->n;
	(*h)->n = temp->n;
	temp->n = x;

}
