cat << 'EOF' > README.md
# Monty Interpreter

A simple interpreter for Monty ByteCode files written in C. This program processes Monty scripts containing stack operations using standard LIFO structures.

## Supported Opcodes
* `push <int>` - Pushes an integer onto the stack.
* `pall` - Prints all the values on the stack.
* `pint` - Prints the value at the top of the stack.
* `pop` - Removes the top element of the stack.

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=c99 *.c -o monty
