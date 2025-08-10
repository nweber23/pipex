# pipex
A UNIX pipe simulation program that replicates shell pipe behavior, developed as part of the 42 School curriculum.

## Overview
This project implements a program that simulates the behavior of shell pipes in UNIX systems. It recreates the functionality of the shell command `< file1 cmd1 | cmd2 > file2` by using system calls like `pipe()`, `fork()`, `dup2()`, and `execve()`. The program demonstrates inter-process communication and process management in C.

## Features
### Core Functionality
- Executes two commands connected by a pipe
- Redirects input from a file and output to another file
- Proper error handling and exit codes
- Support for both built-in commands and executable scripts
- Shell command execution with argument parsing

### Bonus Features
- **Multiple Pipes**: Handle unlimited number of commands chained together
- **Complex Pipeline**: Support for `< file1 cmd1 | cmd2 | cmd3 | ... | cmdN > file2`
- **Advanced Process Management**: Efficient handling of multiple child processes
- **Exit Code Preservation**: Returns the exit code of the last command in the pipeline

### Process Management
- Fork-based process creation for each command
- Proper pipe file descriptor management
- Synchronous process waiting with correct exit codes
- Memory-safe cleanup of all resources

## Project Structure
```
.
├── Makefile                     # Build configuration
├── includes/
│   ├── pipex.h                  # Main header file
│   └── pipex_bonus.h            # Bonus header file
├── srcs/                        # Core implementation
│   ├── pipex.c                  # Main program logic
│   ├── execution.c              # Command execution handling
│   ├── processing.c             # Process management
│   └── utils.c                  # Utility functions
├── bonus_srcs/                  # Bonus implementation
│   ├── pipex_bonus.c           # Multi-command main logic
│   ├── execution_bonus.c       # Enhanced command execution
│   ├── pipes_bonus.c           # Pipeline management
│   ├── pipe_utils_bonus.c      # Pipeline utilities
│   └── utils_bonus.c           # Bonus utility functions
└── libft/                      # Custom C library (external)
```

## Compilation
### Prerequisites
- GCC or compatible C compiler
- Make build system
- Custom libft library (included)

### Build Commands
```bash
# Basic version (2 commands)
make

# Bonus version (unlimited commands)
make bonus

# Clean object files
make clean

# Full cleanup
make fclean

# Rebuild everything
make re
```

## Usage
### Basic Usage (2 Commands)
```bash
# Equivalent to: < infile cmd1 | cmd2 > outfile
./pipex infile "cmd1" "cmd2" outfile

# Example: Count lines in a file
./pipex input.txt "grep hello" "wc -l" output.txt

# Example: Process text data
./pipex data.txt "cat" "sort" sorted_data.txt
```

### Bonus Usage (Multiple Commands)
```bash
# Unlimited command pipeline
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile

# Example: Complex text processing
./pipex input.txt "grep -v '#'" "sort" "uniq -c" "sort -nr" output.txt

# Example: System monitoring pipeline
./pipex /etc/passwd "cat" "cut -d: -f1" "sort" "head -10" users.txt
```

## Implementation Details
- **Process Communication**: Uses UNIX pipes for inter-process communication
- **Command Resolution**: Searches PATH environment variable for executables
- **Script Support**: Detects and executes shell scripts with proper shebang handling
- **Error Handling**: Comprehensive error checking with appropriate exit codes
- **Memory Management**: Proper cleanup of all allocated resources
- **Environment Handling**: Supports custom environment variables with fallback defaults

## Command Execution Types
### Regular Commands
- PATH-based executable resolution
- Argument parsing and proper parameter passing
- Shell command execution via `/bin/sh -c`

### Script Execution
- Shebang (`#!`) detection for executable scripts
- Direct execution for script files with proper permissions
- Relative and absolute path support

### Error Scenarios
- Command not found (exit code 127)
- Permission denied (exit code 126)
- File access errors with descriptive messages
- Pipe creation and process forking failures

## Function Behavior
- **Basic Version**: Handles exactly 4 arguments (infile, cmd1, cmd2, outfile)
- **Bonus Version**: Handles 4+ arguments (infile, cmd1, ..., cmdN, outfile)
- Creates child processes for each command in the pipeline
- Maintains proper file descriptor management across all processes
- Returns the exit code of the last command in the pipeline

## Supported Features
- **File Redirection**: Input from file, output to file with proper permissions
- **Environment Variables**: PATH resolution with default fallback
- **Complex Commands**: Multi-argument commands with proper quote handling
- **Error Propagation**: Shell-compatible exit codes and error messages

## Error Handling
```bash
# File not found
./pipex nonexistent.txt "cat" "wc" output.txt
# Output: pipex: nonexistent.txt: No such file or directory

# Command not found  
./pipex input.txt "invalidcmd" "wc" output.txt
# Output: pipex: invalidcmd: command not found

# Usage error
./pipex
# Output: Usage: ./pipex <file1> <cmd1> <cmd2> <file2>
```

## Technical Specifications
- **Process Limit**: No artificial limits on number of commands (bonus)
- **Memory Management**: Zero memory leaks with proper cleanup
- **File Permissions**: Output files created with 644 permissions
- **Pipe Capacity**: Handles data larger than pipe buffer size
- **Standards Compliance**: Follows 42 School coding standards (Norminette)

## Author
**nweber** - 42 Heilbronn Student
