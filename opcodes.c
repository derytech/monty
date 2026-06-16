#include "monty.h"

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
