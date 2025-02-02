#ifndef REPL_H
#define REPL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// Constants for column sizes
#define COLUMN_USERNAME_SIZE 32                             // Maximum length of username
#define COLUMN_EMAIL_SIZE 255                               // Maximum length of email
#define PAGE_SIZE 4096                                      // Size of a memory page
#define TABLE_MAX_PAGES 100                                 // Maximum number of pages in a table

// Derived constants (calculated values)
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)                // Number of rows per page
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)    // Maximum rows in table

// Enum for meta-command results
typedef enum {
  META_COMMAND_SUCCESS,                                     // Meta-command executed successfully
  META_COMMAND_UNRECOGNIZED_COMMAND                         // Meta-command not recognized
} MetaCommandResult;

// Enum for preparation results
typedef enum {
  PREPARE_SUCCESS,                                          // Statement prepared successfully
  PREPARE_SYNTAX_ERROR,                                     // Statement has syntax error
  PREPARE_UNRECOGNIZED_STATEMENT                            // Statement not recognized
} PrepareResult;

// Enum for execution results
typedef enum {
  EXECUTE_SUCCESS,                                          // Statement executed successfully
  EXECUTE_TABLE_FULL                                        // Table is full
} ExecuteResult;

// Enum for statement types
typedef enum {
  STATEMENT_INSERT,                                         // Insert statement
  STATEMENT_SELECT                                          // Select statement
} StatementType;

/**
 * Structure to store user input
 * @buffer: Pointer to input string
 * @buffer_length: Size of the allocated buffer
 * @input_length: Length of the input string
 */
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

/**
 * Structure for a database row
 * @id: Row ID
 * @username: Username (max 32 chars)
 * @email: Email (max 255 chars)
 */
typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE];
  char email[COLUMN_EMAIL_SIZE];
} Row;

/**
 * Structure to represent a SQL statement
 * @type: Type of statement (insert/select)
 * @row_to_insert: Row data for insert statement
 */
typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;

/**
 * Structure for a database table
 * @num_rows: Number of rows in the table
 * @pages: Array of pointers to memory pages
 */
typedef struct {
  uint32_t num_rows;
  void* pages[TABLE_MAX_PAGES];
} Table;

/* Function prototypes for REPL operations */

/**
 * Allocates and initializes a new InputBuffer
 * @return Pointer to newly created InputBuffer
 */
InputBuffer* new_input_buffer();

/**
 * Displays the command prompt to the user
 */
void print_prompt();

/**
 * Reads a line of input into the provided InputBuffer
 * @param input_buffer Buffer to store input
 */
void read_input(InputBuffer* input_buffer);

/**
 * Frees memory allocated for an InputBuffer
 * @param input_buffer Buffer to free
 */
void close_input_buffer(InputBuffer* input_buffer);

/**
 * Initiates the Read-Eval-Print Loop (REPL)
 */
void start_repl();

/**
 * Executes a meta-command entered by the user
 * @param input_buffer Buffer containing the command
 * @param table Database table to operate on
 * @return MetaCommandResult indicating success/failure
 */
MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);

/**
 * Prepares an SQL statement from user input
 * @param input_buffer Buffer containing SQL command
 * @param statement Statement structure to populate
 * @return PrepareResult indicating parsing success/failure
 */
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

/**
 * Executes a prepared SQL statement
 * @param statement Statement to execute
 * @param table Database table to operate on
 * @return ExecuteResult indicating execution success/failure
 */
ExecuteResult execute_statement(Statement* statement, Table* table);

/**
 * Creates a new database table
 * @return Pointer to newly created Table
 */
Table* new_table();

/**
 * Frees memory allocated for a Table
 * @param table Table to free
 */
void free_table(Table* table);

/**
 * Serializes a Row into a destination buffer
 * @param source Row to serialize
 * @param destination Buffer to write to
 */
void serialize_row(Row* source, void* destination);

/**
 * Deserializes a Row from a source buffer
 * @param source Buffer to read from
 * @param destination Row to populate
 */
void deserialize_row(void* source, Row* destination);

/**
 * Finds the memory slot for a specific row number
 * @param table Table containing the rows
 * @param row_num Row number to locate
 * @return Pointer to the memory slot
 */
void* row_slot(Table* table, uint32_t row_num);

#endif // REPL_H
