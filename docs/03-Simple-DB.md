# In-Memory, Append-Only, Single-Table Database Implementation

This document describes the architecture and implementation of a simple in-memory database with the following characteristics:
- **Append-only writes** (no updates/deletes)
- **Single hard-coded table** structure
- **Memory-only storage** (no disk persistence)
- **Fixed schema** with three columns

## Key Features

### 1. Table Schema
Stores user data with fixed columns:
```c
column     type            size
---------------------------------
id        integer          4 bytes
username  varchar(32)     32 bytes
email     varchar(255)   255 bytes
```

### 2. Storage Characteristics
| Aspect               | Specification                          |
|----------------------|----------------------------------------|
| Persistence          | Volatile (in-memory only)              |
| Max Rows             | 100 pages × 14 rows/page = 1,400 rows  |
| Page Size            | 4KB (matches OS page size)             |
| Row Size             | 291 bytes (4 + 32 + 255)               |
| Allocation Strategy  | Demand-paged (pages allocated on use)  |

## Design Implementation

### Row Storage Architecture
```c
typedef struct {
  uint32_t id;                  // 4 bytes
  char username[32];            // 32 bytes
  char email[255];              // 255 bytes
} Row;

// Serialized layout
+---------+-----------+-----------+
| id (4)  | username  | email     |
|         | (32)      | (255)     |
+---------+-----------+-----------+
```

### Memory Management
```c
#define PAGE_SIZE 4096                          // 4KB pages
#define TABLE_MAX_PAGES 100                     // Fixed page array size
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)    // 14 rows/page

typedef struct {
  uint32_t num_rows;                            // Current row count
  void* pages[TABLE_MAX_PAGES];                 // Page pointers array
} Table;
```

### Key Functions

#### 1. Row Serialization
```c
void serialize_row(Row* source, void* destination) {
  memcpy(destination + 0, &source->id, 4);
  memcpy(destination + 4, source->username, 32);
  memcpy(destination + 36, source->email, 255);
}
```

#### 2. Memory Access
```c
void* row_slot(Table* table, uint32_t row_num) {
  uint32_t page_num = row_num / 14;
  if (!table->pages[page_num]) {
    table->pages[page_num] = malloc(PAGE_SIZE); // Lazy allocation
  }
  uint32_t byte_offset = (row_num % 14) * 291;
  return table->pages[page_num] + byte_offset;
}
```

### Operation Flow

#### Insert Operation
1. Parse input: `insert <id> <username> <email>`
2. Validate input syntax
3. Check table capacity
4. Serialize row to next available slot
5. Increment row counter

#### Select Operation
1. Iterate through all allocated pages
2. Deserialize each row
3. Print formatted output

## Limitations

1. **Capacity Limits**
   - Maximum 1,400 rows (100 pages × 14 rows)
   - Fixed column sizes (no variable-length fields)

2. **Functional Constraints**
   - No persistence between sessions
   - No update/delete operations
   - No indexing or query optimization
   - Single table only

3. **Error Handling**
   - Basic syntax checking
   - Table full detection
   - No data validation (e.g., duplicate IDs)

## Example Usage

```text
$ ./database
db > insert 1 alice alice@example.com
Executed.
db > insert 2 bob bob@domain.com
Executed.
db > select
(1, alice, alice@example.com)
(2, bob, bob@domain.com)
Executed.
db > insert invalid data
Syntax error. Could not parse statement.
db > .exit
```

## Test Considerations

Critical test scenarios include:
1. **Boundary Conditions**
   - Inserting exactly 1,400 rows
   - Attempting 1,401st insert (table full error)

2. **Data Validation**
   - Overlength usernames/emails (truncation behavior)
   - Non-integer ID values
   - Missing/extra insert arguments

3. **Memory Management**
   - Verify page allocation on first access
   - Confirm proper memory release on exit
   - Test interleaved insert/select operations

## Implementation Notes

1. **Append-Only Design**
   - Simple write pattern enables high insert speed
   - No fragmentation concerns
   - Tradeoff: No update/delete capabilities

2. **Serialization Choices**
   - Fixed offsets enable O(1) row access
   - Memory layout matches disk format (future-proofing)
   - Padding not required due to exact size matching

3. **Page Allocation Strategy**
   - Lazy allocation reduces memory overhead
   - 4KB pages align with virtual memory systems
   - Array-based management simplifies access

4. **Concurrency Model**
   - Single-threaded execution only
   - No locking mechanisms implemented
   - Not thread-safe for concurrent access

5. **Error Recovery**
   - No transaction rollback capability
   - Failed operations leave partial state
   - Memory integrity maintained through:
     - Atomic page allocations
     - Bounds-checked row access

6. **Data Validation**
   - Minimal input sanitization:
     - Basic type checking for IDs
     - Automatic string truncation for overflow
   - Missing validation for:
     - Duplicate IDs
     - Email format compliance
     - Username character restrictions

7. **Schema Rigidity**
   - Hard-coded column structure
   - Type system limitations:
     - No true VARCHAR implementation
     - Fixed-size character arrays
   - Schema changes require recompilation

8. **Performance Characteristics**
   - O(1) insert complexity (append-only)
   - O(n) select complexity (full scan)
   - Memory access patterns:
     - Sequential writes (inserts)
     - Random reads (selects)
   - No cache optimization implemented

9. **Security Considerations**
   - Memory-safe operations through:
     - Bounded string copies
     - Page boundary checks
   - Vulnerabilities:
     - No input sanitization for special characters
     - Potential for buffer overflows in edge cases
     - Memory contents not zeroed after free
