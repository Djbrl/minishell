# Minishell

Minishell is a simple yet robuts shell implementation. It provides a user-friendly interface with essential features, allowing users to interact with the system through a command-line interface.

## Features

### Display a Prompt
Minishell displays a prompt when waiting for a new command, making it easy for users to input commands.

### Working History
The shell maintains a working history, allowing users to access and repeat previously executed commands.

### Command Execution
Minishell searches and launches the right executable based on the PATH variable or using a relative or absolute path.

### Global Variables
The implementation follows the requirement of not using more than one global variable, ensuring a clean and efficient design. The purpose of the global variable is explained within the code.

### Quote Handling
The shell handles single quotes ('), preventing interpretation of meta-characters in the quoted sequence. It also handles double quotes (") while allowing the interpretation of the $ (dollar sign) meta-character.

### Redirections
- `<` redirects input.
- `>` redirects output.
- `<<` reads input until a line containing the specified delimiter, without updating the history.
- `>>` redirects output in append mode.

### Pipes
The shell supports pipes (|), allowing the output of each command in the pipeline to connect to the input of the next command via a pipe.

### Environment Variables
Minishell handles environment variables ($ followed by a sequence of characters), expanding them to their values.

### Special Variables
- `$?` expands to the exit status of the most recently executed foreground pipeline.

### Signal Handling
The shell handles the following signals:
- ctrl-C: Displays a new prompt on a new line.
- ctrl-D: Exits the shell.
- ctrl-\: Does nothing.

### Built-in Commands
Minishell implements the following built-in commands:
- `echo` with the option `-n`
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

### Memory Leaks
While the `readline()` function may cause memory leaks (which are not fixed), the code written by the developer is ensured to be free of memory leaks.

## Usage

To compile and run Minishell, use the provided Makefile with the following commands:

```bash
make
./minishell
```

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute the code as per the license terms.
