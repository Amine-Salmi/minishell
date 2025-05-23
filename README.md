# **Minishell**  
*As beautiful as a shell.*

---

## **Project Overview**  
Minishell is a simple shell implementation inspired by Bash. This project demonstrates fundamental concepts in system programming, including processes, file descriptors, and signal handling, offering an opportunity to build an interactive command-line interface.

---

## **Features**  
- **Interactive Shell Prompt**: Customizable and ready for user input.  
- **Command Execution**: Runs binaries using paths or the `PATH` variable.  
- **Redirection Support**: Includes `<`, `>`, `>>`, and heredoc (`<<`).  
- **Pipes**: Chains multiple commands seamlessly.  
- **Environment Variables**: Supports `$VARIABLE` and `$?`.  
- **Built-in Commands**:  
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.  
- **Signal Handling**: Reacts to `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` like Bash.  

---

## **Getting Started**  
### Installation  
1. Clone the repository:  
  ```bash
  git clone https://github.com/Amine-Salmi/minishell.git
  cd minishell
2. Build the project:
  make
3. Run the shell:
  ./minishell
