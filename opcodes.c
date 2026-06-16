#include "monty.h"

/**
 * check_num - checks if a string is a valid integer
 * @str: string to check
 * Return: 0 if valid, 1 if not
 */
int check_num(char *str)
{
	int i = 0;

	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * f_push - pushes an element to the stack
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_push(stack_t **stack, unsigned int line_number)
{
	int n;
	stack_t *new_node;

	if (!bus.arg || check_num(bus.arg) != 0)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	n = atoi(bus.arg);
	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}
	new_node->n = n;
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * f_pall - prints all the values on the stack
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void)line_number;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * f_pint - prints the value at the top of the stack
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * f_pop - removes the top element of the stack
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	*stack = temp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(temp);
}
/**
 * f_swap - swaps the top two elements of the stack
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}

/**
 * f_add - adds the top two elements of the stack
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Add top element's value to the second top element */
	(*stack)->next->n += (*stack)->n;

	/* Remove the top element */
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * f_nop - doesn't do anything
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * f_div - divides the second top element of the stack by the top element
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Check for division by zero error */
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Divide second top element by the top element */
	(*stack)->next->n /= (*stack)->n;

	/* Pop off the top element */
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * f_mul - multiplies the second top element of the stack with the top element
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Multiply the second top element by the top element */
	(*stack)->next->n *= (*stack)->n;

	/* Remove the top node */
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * f_sub - subtracts the top element of the stack from the second top element
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Subtract top element from the second top element */
	(*stack)->next->n -= (*stack)->n;

	/* Pop off the old top element */
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * f_mod - computes the remainder of the division of the second top element
 * by the top element of the stack
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Check for division by zero */
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Compute modulo of second top element by top element */
	(*stack)->next->n %= (*stack)->n;

	/* Remove the top node */
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * f_pchar - prints the char at the top of the stack, followed by a new line
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	/* Validate if the number sits within the ASCII boundary (0 - 127) */
	if ((*stack)->n < 0 || (*stack)->n > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		free_stack(*stack);
		free(bus.content);
		fclose(bus.file);
		exit(EXIT_FAILURE);
	}

	printf("%c\n", (*stack)->n);
}

/**
 * f_pstr - prints the string starting at the top of the stack,
 * followed by a new line
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number
 * Return: void
 */
void f_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void)line_number;

	while (current != NULL)
	{
		/* Stop string parsing if value is 0 or out of ASCII bounds */
		if (current->n <= 0 || current->n > 127)
			break;

		printf("%c", current->n);
		current = current->next;
	}
	printf("\n");
}

/**
 * f_rotl - rotates the stack to the top
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number (unused)
 * Return: void
 */
void f_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *current = *stack;
	(void)line_number;

	/* If stack is empty or has only one element, do nothing */
	if (*stack == NULL || (*stack)->next == NULL)
		return;

	/* Advance the new head pointer to the second element */
	*stack = top->next;
	(*stack)->prev = NULL;

	/* Traverse down to find the last node of the stack */
	while (current->next != NULL)
		current = current->next;

	/* Attach the old top node to the bottom of the stack */
	current->next = top;
	top->prev = current;
	top->next = NULL;
}

/**
 * f_rotr - rotates the stack to the bottom
 * @stack: double pointer to the head of the stack
 * @line_number: counter for the line number (unused)
 * Return: void
 */
void f_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void)line_number;

	/* If stack is empty or has only one element, do nothing */
	if (*stack == NULL || (*stack)->next == NULL)
		return;

	/* Traverse all the way down to find the last node */
	while (current->next != NULL)
		current = current->next;

	/* Detach the last node from its previous neighbor */
	current->prev->next = NULL;

	/* Wire the last node to point to the current top node */
	current->next = *stack;
	current->prev = NULL;
	(*stack)->prev = current;

	/* Make the last node the new head of the stack */
	*stack = current;
}
