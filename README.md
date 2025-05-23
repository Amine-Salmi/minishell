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
### 1. Installation  
Clone the repository:  
  ```bash
  git clone https://github.com/Amine-Salmi/minishell.git
  cd minishell
  ```
### 2. Build the Project  
Compile the shell:
  ```bash
  make
  ```
### 3. Run the Shell
Execute the minishell:
  ```bash
  ./minishell
  ```

---

## **Usage Examples**
###  Basic Commands
  ```bash
  -  minishell$ pwd
  /home/user/minishell
  -  minishell$ echo "Hello world"
  Hello world
  -  minishell$ ls -la
  ```
### Pipes and Redirection
  ```bash
  -  minishell$ ls | grep .c
  -  minishell$ echo "test" > output.txt
  -  minishell$ cat < input.txt
  -  minishell$ ls >> log.txt
  ```

### Pipes and Redirection
  ```bash
  -  minishell$ export MY_VAR=hello
  -  minishell$ echo $MY_VAR
  hello
  -  minishell$ echo $?
  0
  ```

### Heredoc
  ```bash
  -  minishell$ cat << EOF
  > This is a heredoc
  > Multiple lines supported
  > EOF
  This is a heredoc
  Multiple lines supported
  ```

---

## **License**
This project is part of the 42 School curriculum.