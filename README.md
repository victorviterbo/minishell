# 🐚 Minishell

A custom shell implementation as part of the 42 curriculum. This project aims to create a simplified version of the Bash shell, implementing various features including command execution, builtin commands, and more.

![Minishell Banner](https://i.imgur.com/pWw8LYh.png)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
  - [Mandatory Features](#mandatory-features)
  - [Bonus Features](#bonus-features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Project Structure](#project-structure)
- [Team](#team)

## 🔍 Overview

Minishell is a shell implementation that provides a command-line interface for users to interact with the operating system. It interprets user commands, executes programs, and manages input/output redirections. Our implementation follows POSIX standards and aims to mimic bash behavior while maintaining a clean and efficient codebase.

## ✨ Features

### Mandatory Features

- **Command Prompt Display**: Shows a prompt when waiting for a new command
- **Command History**: Navigate through command history using up and down arrow keys
- **Executable Search and Execution**: Uses PATH variable or relative/absolute paths
- **Quoting**: Handles both single (`'`) and double (`"`) quotes with appropriate behavior
- **Redirections**:
  - Input (`<`): Redirect input from a file
  - Output (`>`): Redirect output to a file (truncate)
  - Append Output (`>>`): Redirect output to a file (append)
  - Here Document (`<<`): Read input until a delimiter is encountered
- **Pipes** (`|`): Connect the output of one command to the input of another
- **Environment Variables**: Expand variables (e.g., `$USER`, `$HOME`)
- **Exit Status** (`$?`): Access the exit status of the most recently executed command
- **Signal Handling**:
  - `Ctrl-C`: Displays a new prompt on a new line
  - `Ctrl-D`: Exits the shell
  - `Ctrl-\`: Does nothing
- **Builtin Commands**:
  - `echo` with option `-n`
  - `cd` with relative or absolute path
  - `pwd` without options
  - `export` without options
  - `unset` without options
  - `env` without options or arguments
  - `exit` without options

### Bonus Features

- **Logical Operators**:
  - `&&`: Execute the right-hand command only if the left-hand command succeeds
  - `||`: Execute the right-hand command only if the left-hand command fails
- **Parentheses** (`(` and `)`): Change the precedence of operations
- **Wildcards** (`*`): Expand to matching files and directories in the current directory

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make utility
- Readline library

### Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```

2. Navigate to the project directory:
   ```bash
   cd minishell
   ```

3. Compile the project:
   ```bash
   make
   ```

## 🖥️ Usage

Run the shell:
```bash
./bin/minishell
```

Example commands:
```bash
# Simple command execution
minishell$ ls -la

# Redirections
minishell$ ls > file.txt
minishell$ cat < file.txt

# Pipes
minishell$ ls -la | grep .c

# Environment variables
minishell$ echo $HOME

# Logical operators (bonus)
minishell$ ls && echo "success"
minishell$ ls non_existent_file || echo "failure"

# Wildcards (bonus)
minishell$ ls *.c

# Parentheses for precedence (bonus)
minishell$ (ls && echo "done") || echo "failed"
```

## 🔧 Implementation Details

### Parsing and Lexing

The shell uses a lexer to tokenize the input string and then builds an abstract syntax tree (AST) to represent the command structure. This allows for proper handling of complex command combinations, especially with the bonus features like logical operators and parentheses.

### Command Execution

Commands are executed by traversing the AST. For external commands, the shell uses fork and execve. For built-in commands, it calls the corresponding function directly.

### Signal Handling

Signals are handled differently depending on whether the shell is in interactive mode (waiting for user input) or executing a command.

### Environment Variables

Environment variables are stored in a linked list for easy manipulation. The shell supports variable expansion in various contexts, including within double quotes.

### Redirections and Pipes

File descriptors are carefully managed to ensure proper redirection of standard input and output. Pipes are implemented using the pipe system call and fork.

## 📁 Project Structure

```
minishell/
├── bin/                  # Compiled executable
├── include/              # Header files
│   └── minishell.h       # Main header file
├── lib/                  # Libraries
│   └── libft/            # Custom C library
├── srcs/                 # Source files
│   ├── exec/             # Command execution
│   ├── parsing/          # Input parsing
│   └── utils/            # Utility functions
├── Makefile              # Build instructions
└── README.md             # Project documentation
```

## 👥 Team

This project was developed by:

- [Victo Bronov](https://github.com/VictorBro) - vbronov@student.42lausanne.ch
- [Victor Viterbo](https://github.com/victorviterbo) - vviterbo@student.42.fr

---

Project developed as part of the 42 curriculum.
