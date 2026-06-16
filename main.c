#include "monty.h"

bus_t bus = {NULL, NULL, NULL};

void free_stack(stack_t *head)
{
	stack_t *temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

int main(int argc, char *argv[])
{
	char *opcode;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	bus.file = fopen(argv[1], "r");
	if (!bus.file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&bus.content, &len, bus.file)) != -1)
	{
		line_number++;
		opcode = strtok(bus.content, " \t\n");
		if (opcode == NULL || opcode[0] == '#')
			continue;
		bus.arg = strtok(NULL, " \t\n");
		execute_opcode(opcode, &stack, line_number);
	}
	free(bus.content);
	fclose(bus.file);
	free_stack(stack);
	return (EXIT_SUCCESS);
}
