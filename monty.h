#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

extern FILE *fd;
/**
 * struct stack_s - doubly linked list representation of a queue (stack)
 * @n: integer
 * @prev: points to the previous element of the queue (stack
 * @next: points to the next element of the queue (stack)
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
 * struct instruction_s - opcode function
 * @opcode: the opcode
 * @f: function handling the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, char **args, unsigned int line_number);
} instruction_t;

int empty(char *buffer);
void san_buffer(char *buffer);
void clean_buffer(char *buffer);
void tokenize(char **tokens, char *buffer);
void free_tokens(char **tokens);
void print_tokens(char **tokens);
void (*getopfunc(stack_t **, char **, unsigned int))(stack_t **, char **, unsigned int);
void push(stack_t **stack, char **args, unsigned int line_number);
void pall(stack_t **stack, char **args, unsigned int line_number);
void pint(stack_t **stack, char **args, unsigned int line_number);
void pop(stack_t **stack, char **args, unsigned int line_number);
void swap(stack_t **stack, char **args, unsigned int line_number);
void add(stack_t **stack, char **args, unsigned int line_number);
void nop(stack_t **stack, char **args, unsigned int line_number);
void free_stack(stack_t **stack);


#endif
