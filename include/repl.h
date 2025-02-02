#ifndef REPL_H
#define REPL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum for meta-command results
typedef enum {
    META_COMMAND_SUCCESS,               // Meta-command executed successfully
    META_COMMAND_UNRECOGNIZED_COMMAND   // Meta-command not recognized
} MetaCommandResult;

// Enum for preparation results
typedef enum {
  PREPARE_SUCCESS,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

// Enum for statement types
typedef enum {
    STATEMENT_INSERT,                   // Insert statement
    STATEMENT_SELECT                    // Select statement
} StatementType;

// Structure to store user input
typedef struct {
    char* buffer;                       // Pointer to input string
    size_t buffer_length;               // Size of the allocated buffer
    ssize_t input_length;               // Length of the input string
} InputBuffer;

// Structure to represent a SQL statement
typedef struct {
    StatementType type;                 // Type of statement (insert/select)
} Statement;

// Function prototypes for REPL operations

/**
 * Allocates and initializes a new InputBuffer.
 * 
 * @return A pointer to the newly created InputBuffer.
 */
InputBuffer* new_input_buffer();

/**
 * Displays the command prompt to the user.
 * 
 * Typically used to indicate readiness for a new command.
 */
void print_prompt();

/**
 * Reads a line of input from the user into the provided InputBuffer.
 * 
 * @param input_buffer A pointer to the InputBuffer where input will be stored.
 */
void read_input(InputBuffer* input_buffer);

/**
 * Frees the memory allocated for the InputBuffer.
 * 
 * @param input_buffer A pointer to the InputBuffer to be freed.
 */
void close_input_buffer(InputBuffer* input_buffer);

/**
 * Initiates the Read-Eval-Print Loop (REPL).
 * 
 * Continuously reads and processes user commands.
 */
void start_repl();

/**
 * Executes a meta-command entered by the user.
 * 
 * @param input_buffer A pointer to the InputBuffer containing the command.
 * @return A MetaCommandResult indicating success or unrecognized command.
 */
MetaCommandResult do_meta_command(InputBuffer* input_buffer);

/**
 * Parses the user input and prepares an SQL statement.
 * 
 * @param input_buffer A pointer to the InputBuffer containing the SQL command.
 * @param statement A pointer to a Statement structure to store the parsed command.
 * @return A PrepareResult indicating success or unrecognized statement.
 */
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

/**
 * Executes the prepared SQL statement.
 * 
 * @param statement A pointer to the Statement to be executed.
 */
void execute_statement(Statement* statement);

#endif // REPL_H
