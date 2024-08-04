#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

extern unsigned int isFail;

/**
 * struct stack_s - doubly linked list representation of a queue (stack)
 * @n: integer
 * @prev: Previous element of the queque (stack)
 * @next: Mext element of the queueeed (stack)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;


/**
 * struct instruction_s - The opcode and it's function
 * @opcode: the opcode
 * @f: function handling the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


int read_file(FILE *fd);
int parse_line(char *line, stack_t **h, unsigned int lnum);

void push(stack_t **h, unsigned int ln);
void pall(stack_t **h, unsigned int ln);
void pint (stack_t **h, unsigned int ln);
void pop(stack_t **h, unsigned int ln);
void swap(stack_t **h, unsigned int ln);
void add(stack_t **h, unsigned int ln);
void nop(stack_t **h, unsigned int ln);

void (*get_op(char *str))(stack_t **stack, unsigned int line_number);
void free_stack(stack_t *head);

#endif
