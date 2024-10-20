<img src="./cover-minishell.png"/>


Minishell is a simple shell implementation inspired by Bash, designed to handle essential shell functionalities like pipelines, redirections, built-in commands, and more. This project dives deep into Unix-like process handling, memory management, and system calls.

## Project Overview
Minishell provides a foundational shell experience, handling command execution interactively and supporting advanced features such as variable expansion, pipes, and custom signal handling.

## Features

- **Interactive Shell**: Displays a customizable prompt, waits for user input, and supports command execution.
- **Command Execution**: Executes binaries based on the `PATH` environment variable, supporting relative and absolute paths.
- **Built-in Commands**:
  - `echo` (with `-n` option)
  - `cd` (handles both relative and absolute paths)
  - `pwd` (prints the current working directory)
  - `export` (sets environment variables)
  - `unset` (removes environment variables)
  - `env` (prints the current environment variables)
  - `exit` (supports numeric arguments for status codes)
- **Redirections**:
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Output append redirection (`>>`)
  - Heredoc (`<<`) with variable expansion (similar to Bash)
- **Pipes**: Implements pipelines (`|`), allowing the output of one command to be used as input for another.
- **Environment Variables**: Expands variables like `$VAR` and supports special variables like `$?` (last exit status).
- **Signal Handling**: Custom handling for signals in normal operation:
  - `Ctrl-C` displays a new prompt.
  - `Ctrl-D` exits the shell.
  - `Ctrl-\` is ignored.
- **Heredoc Signal Behavior**: During heredoc:
  - `Ctrl-C` and `Ctrl-D` end the heredoc immediately without requiring end of file input. Only after pressing `Enter` is the prompt displayed again.
- **Exit Status Handling**: The `exit` command allows passing numeric arguments to set the exit status.

## Data Structures
Minishell uses a dynamic and flexible system to parse and execute commands through linked lists:
- **Command List (`t_command`)**: Stores the input and the list of parsed commands.
- **Node List (`t_node`)**: Represents each segment of the input separated by pipes (`|`). Each node contains:
  - A list of tokens (`t_tokens`).
  - File descriptors for input/output redirection.
  - Process ID (`pid`) for child processes.
  - Exit status of the command executed in that node.
- **Token List (`t_tokens`)**: Contains individual words and their corresponding token types (e.g., command, argument, redirection).
- **Environment Variables List (`t_env`)**: Stores environment variables in key-value pairs.

## Memory Management and Suppression File
To ensure no memory leaks in user-written code, all dynamically allocated memory is freed appropriately. However, the `readline()` function can still produce leaks. For these, a custom suppression file (`supressions.supp`) is included for use with Valgrind.

## Makefile
The project includes a comprehensive `Makefile` that handles compilation, testing, and cleaning. It supports the following targets:

- `all`: Builds the project.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Rebuilds the project from scratch.
- `run`: Rebuilds the project from scratch and runs it.
- `valgrind`: Runs the project with Valgrind using the `supressions.supp` file for leak checking.
- `norm`: Checks the code against the Norm standard.

To compile and run the shell, use the following commands:

```bash
make
./minishell
```

## Conclusion
Minishell is an exploration into the inner workings of Unix-like shells, allowing users to build a functional shell while handling complex topics like process management, signal handling, and memory management.
