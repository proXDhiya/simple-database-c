# REPL Implementation for Simple Database

This document provides an overview of the Read-Eval-Print Loop (REPL) implementation for the Simple Database project. The REPL allows users to interactively input and execute commands, making it an essential component for testing and exploring database functionalities.

## Overview

The REPL is implemented in C, providing an interactive shell for users to input commands. It is designed to handle basic input operations and execute specific commands like `.exit`.

### Key Components

- **Header File (`repl.h`)**: Defines the structure and function prototypes.
- **Source File (`repl.c`)**: Implements the REPL logic.

## `repl.h`

### Structure

```c
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;
```

- **`buffer`**: A dynamically allocated string to store user input.
- **`buffer_length`**: The size of the allocated buffer.
- **`input_length`**: The length of the input string.

### Functions

- **`InputBuffer* new_input_buffer();`**: Allocates and initializes a new `InputBuffer`.
- **`void print_prompt();`**: Displays the input prompt to the user.
- **`void read_input(InputBuffer* input_buffer);`**: Reads user input into the buffer.
- **`void close_input_buffer(InputBuffer* input_buffer);`**: Frees allocated memory for the input buffer.
- **`void start_repl();`**: Initiates the REPL loop for continuous input processing.

## `repl.c`

### Function Implementations

#### `InputBuffer* new_input_buffer()`

- Allocates memory for a new `InputBuffer`.
- Initializes `buffer` to `NULL`, `buffer_length` and `input_length` to `0`.

#### `void print_prompt()`

- Prints `"db > "` to signal readiness for input.

#### `void read_input(InputBuffer* input_buffer)`

- Utilizes `getline()` to read input from the user.
- Dynamically adjusts `buffer` size and stores the input length.
- Removes the trailing newline character for cleaner processing.

#### `void close_input_buffer(InputBuffer* input_buffer)`

- Frees the memory allocated for both the buffer and the `InputBuffer` structure.

#### `void start_repl()`

- Initializes a new `InputBuffer`.
- Enters a loop to continuously read and process input.
- Recognizes the `.exit` command to terminate the REPL.

### Example Workflow

1. **Start REPL**: Initializes input buffer and displays prompt.
2. **Read Input**: Waits for user input and reads it into the buffer.
3. **Process Input**: Checks for specific commands, such as `.exit`.
4. **Repeat**: Continues the loop for further input, unless an exit command is received.

## Conclusion

The REPL implementation provides a simple yet effective way to interact with the Simple Database. It facilitates easy testing and exploration of database functionalities, laying the groundwork for more advanced features.
