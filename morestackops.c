#include "monty.h"

/**
 * add - adds top 2 nodes of a stacfk
 * @h: head of stack
 * @ln: line
 * Return: void
 */

void add(stack_t **h, unsigned int ln)
{
	unsigned int sum;
	stack_t *temp;

	if (*h == NULL || (*h)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", ln);
		isFail = 1;
		return;
	}

	temp = (*h)->next;
	sum = (*h)->n + temp->n;
	temp->n = sum;
	pop(h, ln);
}

/**
 * nop - literally do nothing!
 * @h: head of stack
 * @ln: line
 * Return: void
 */

void nop(stack_t **h, unsigned int ln)
{
	(void)h;
	(void)ln;
}
