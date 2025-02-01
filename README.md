Certainly! Here's the updated documentation with the resource included:

# simple-database-c

A **lightweight SQLite clone** written in C, designed to explore how databases work from the ground up. This project walks through building a simple relational database step by step, covering key concepts like indexing, transactions, and storage formats.

## 🚀 Why This Project?
Ever wondered **how databases actually work under the hood**?

- How is data stored in memory and on disk?
- What makes transactions and rollbacks possible?
- How do indexes speed up queries?
- What happens when a table gets too big?

This project is a hands-on attempt to **build a database from scratch** to understand these concepts deeply.

## 🔧 Features
- 🖥️ **Interactive REPL** to run SQL-like commands
- 📝 **Basic SQL compiler & virtual machine**
- 📂 **File-based storage** for persistence
- 🌳 **B-Tree indexing** for fast lookups
- 🔄 **Transaction support** with rollbacks
- 🔍 **Binary search for efficient queries**

## 📚 What You’ll Learn
- The **fundamentals of database storage** (memory & disk)
- How **SQL queries** are processed behind the scenes
- How **B-Trees** work and why they’re used in databases
- The **mechanics of transactions** and rollbacks
- The basics of writing a **mini SQL engine** in C

## 🏗️ How It’s Built (Step by Step)
1. Setting up a simple **REPL**
2. Building a **SQL compiler & virtual machine**
3. ~~Implementing an **in-memory database**~~
4. ~~Adding **file storage** for persistence~~
5. ~~Creating a **cursor abstraction** for data traversal~~
6. ~~Implementing **B-Trees** for indexing~~
7. ~~Handling **binary search & duplicate keys**~~
8. ~~Splitting **leaf & internal nodes**~~
9. ~~Supporting **multi-level B-Tree traversal**~~
10. ~~Optimizing query execution~~

## 🛠️ Getting Started
### Required Tools
- **C Compiler**: Ensure you have GCC or another C compiler installed.
- **Make**: Used to build the project.

Clone the repo and compile it using a C compiler:

```sh
git clone https://github.com/proXDhiya/simple-database-c.git
cd simple-database-c
make
./sqlite
```

Now you’re ready to start **experimenting with database internals! 🚀**

> This project is inspired by SQLite’s architecture and is meant for learning and fun. It follows the tutorial available at [cstack's DB tutorial](https://cstack.github.io/db_tutorial/). Feel free to contribute or tweak it to explore database internals further!
