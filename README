# **Minishell**  
*As beautiful as a shell.*

---

## **Project Overview**  
Minishell is a simple shell implementation inspired by Bash. This project demonstrates fundamental concepts in system programming, including processes, file descriptors, and signal handling, offering an opportunity to build an interactive command-line interface.

---

## **Features**  
### **Mandatory**  
- Custom shell prompt that waits for user input.
- Command execution:
  - Executes binaries using relative, absolute paths, or the PATH variable.
  - Supports environment variables and `$?` for the last command's exit status.
- Quote handling:
  - Single quotes (`'`) prevent interpretation of special characters.
  - Double quotes (`"`) allow interpretation of `$` for variable expansion.
- Redirections:
  - `<` redirects input.
  - `>` redirects output.
  - `<<` handles heredoc with a delimiter.
  - `>>` appends output to a file.
- Pipes (`|`):
  - Implements piping between multiple commands.
- Built-in commands:
  - `echo` (supports `-n` option).
  - `cd` (handles relative/absolute paths).
  - `pwd` (prints the current directory).
  - `export` (manages environment variables).
  - `unset` (removes environment variables).
  - `env` (displays environment variables).
  - `exit` (exits the shell).
- Signal handling:
  - `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` behave like in Bash.
