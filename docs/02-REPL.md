# Updated REPL Implementation for Simple Database

This document provides an overview of the enhanced Read-Eval-Print Loop (REPL) implementation for the Simple Database project. The REPL allows users to interactively input and execute commands, making it an essential component for testing and exploring database functionalities.

## Overview

The REPL is implemented in C, providing an interactive shell for users to input commands. It now supports basic SQL-like commands and meta-commands, enhancing its functionality.

### Key Components

- **Header File (`repl.h`)**: Defines structures, enums, and function prototypes.
- **Source File (`repl.c`)**: Implements the REPL logic and command handling.

## `repl.h`

### Enums and Structures

#### MetaCommandResult

```c
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;
```

- Indicates the result of executing a meta-command.

#### PrepareResult

```c
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;
```

- Represents the outcome of preparing a SQL statement.

#### StatementType

```c
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;
```

- Defines types of SQL statements supported.

#### InputBuffer

```c
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;
```

- Stores user input dynamically.

#### Statement

```c
typedef struct {
    StatementType type;
} Statement;
```

- Represents a parsed SQL statement.

### Functions

- **`InputBuffer* new_input_buffer();`**: Allocates and initializes a new `InputBuffer`.
- **`void print_prompt();`**: Displays the input prompt to the user.
- **`void read_input(InputBuffer* input_buffer);`**: Reads user input into the buffer.
- **`void close_input_buffer(InputBuffer* input_buffer);`**: Frees allocated memory for the input buffer.
- **`void start_repl();`**: Initiates the REPL loop for continuous input processing.
- **`MetaCommandResult do_meta_command(InputBuffer* input_buffer);`**: Executes a meta-command.
- **`PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);`**: Parses and prepares an SQL statement.
- **`void execute_statement(Statement* statement);`**: Executes the prepared SQL statement.

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

#### `MetaCommandResult do_meta_command(InputBuffer* input_buffer)`

- Processes meta-commands like `.exit`.
- Returns a result indicating success or an unrecognized command.

#### `PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)`

- Parses input to determine if it matches supported SQL commands (`insert`, `select`).
- Returns a result indicating success or an unrecognized statement.

#### `void execute_statement(Statement* statement)`

- Executes the parsed SQL statement.
- Currently contains placeholders for `insert` and `select`.

#### `void start_repl()`

- Initializes a new `InputBuffer`.
- Enters a loop to continuously read and process input.
- Handles both SQL and meta-commands, terminating on `.exit`.

### Example Workflow

1. **Start REPL**: Initializes input buffer and displays prompt.
2. **Read Input**: Waits for user input and reads it into the buffer.
3. **Process Meta-Commands**: Handles commands starting with a dot.
4. **Prepare SQL Commands**: Parses and prepares SQL-like commands.
5. **Execute Commands**: Executes recognized commands.
6. **Repeat**: Continues the loop for further input, unless an exit command is received.

## Conclusion

The updated REPL implementation provides a more robust interface for interacting with the Simple Database. It supports basic SQL commands and meta-commands, paving the way for further development and enhancements.