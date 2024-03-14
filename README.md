# My own shell

A shell does three different things in its lifetime:

- **Initialize**: In this step, a typical shell would read and execute its configuration files.

- **Interpret**: The shell reads commands from stdin (which could be interactive, or a file) and executes them.

- **Terminate**: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.

## Basic loop of a shell

- **Read**: Read the command from standard input.

- **Parse**: Separate the command string int oa program and arguments.

- **Execute**: Run the parsed command.

### Parsing

The process of parsing consists of tokenizing the line.