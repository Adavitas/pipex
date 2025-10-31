# Pipex

<div align="center">

![42 School Project](https://img.shields.io/badge/42-Project-blue)
![C](https://img.shields.io/badge/Language-C-brightgreen)
![Norminette](https://img.shields.io/badge/Norminette-passing-success)
![Grade](https://img.shields.io/badge/Grade-125%2F100-success)

A 42 School project that recreates the behavior of shell pipes using system calls in C.

[Features](#features) •
[Installation](#installation) •
[Usage](#usage) •
[Examples](#examples) •
[Documentation](#documentation)

</div>

---

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Here Document](#here-document)
  - [Multiple Pipes](#multiple-pipes)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Implementation](#implementation)
- [Testing](#testing)
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

## 🎯 About

**Pipex** is a system programming project from 42 School that deepens understanding of:

- Unix pipes and inter-process communication (IPC)
- Process creation and management with `fork()`
- File descriptor manipulation and I/O redirection
- Command execution and PATH resolution
- Error handling in system-level programming

The program mimics the behavior of shell pipes, allowing you to chain commands together just like in bash.

### Mandatory Part

Recreates this shell behavior:
```bash
< file1 cmd1 | cmd2 > file2
```

### Bonus Part

Adds support for:
- ✅ Multiple pipes (unlimited command chaining)
- ✅ Here document functionality (`<<`)

## ✨ Features

- **📦 Basic Pipe**: Execute two commands with input/output redirection
- **🔗 Multiple Pipes**: Chain unlimited number of commands (bonus)
- **📝 Here Document**: Support for `<<` delimiter (bonus)
- **🛡️ Error Handling**: Robust error management for all edge cases
- **🧹 Memory Safe**: No memory leaks (verified with valgrind)
- **📏 42 Norm Compliant**: Follows strict 42 School coding standards

## 🚀 Installation

### Prerequisites

- GCC compiler
- Make
- Unix-like operating system (Linux, macOS)

### Build

Clone the repository and compile:

```bash
# Clone the repository
git clone https://github.com/Adavitas/pipex.git
cd pipex

# Compile the project
make

# The executable 'pipex' will be created
```

### Make Commands

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything from scratch
```

## 📖 Usage

### Basic Usage

Execute two commands with pipe:

```bash
./pipex file1 cmd1 cmd2 file2
```

**Equivalent to:**
```bash
< file1 cmd1 | cmd2 > file2
```

**Parameters:**
- `file1`: Input file
- `cmd1`: First command to execute
- `cmd2`: Second command to execute
- `file2`: Output file (will be created/truncated)

### Here Document

Support for here document syntax:

```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```

**Equivalent to:**
```bash
cmd1 << LIMITER | cmd2 >> file
```

**Parameters:**
- `here_doc`: Keyword to activate here_doc mode
- `LIMITER`: Delimiter to stop reading from stdin
- `cmd1`: First command
- `cmd2`: Second command
- `file`: Output file (will be created/appended)

### Multiple Pipes

Chain multiple commands (bonus):

```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdN fileN
```

**Equivalent to:**
```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdN > fileN
```

## 💡 Examples

### Example 1: Word Count

Count words in a file:

```bash
./pipex infile "cat" "wc -w" outfile
```

**Shell equivalent:**
```bash
< infile cat | wc -w > outfile
```

### Example 2: Search and Sort

Find lines containing "error" and sort them:

```bash
./pipex logfile.txt "grep error" "sort" results.txt
```

**Shell equivalent:**
```bash
< logfile.txt grep error | sort > results.txt
```

### Example 3: Multiple Command Pipeline

Complex data processing:

```bash
./pipex data.txt "cat" "grep pattern" "sort -r" "uniq" output.txt
```

**Shell equivalent:**
```bash
< data.txt cat | grep pattern | sort -r | uniq > output.txt
```

### Example 4: Here Document

Read from stdin until delimiter:

```bash
./pipex here_doc EOF "grep hello" "wc -l" count.txt
hello world
hello pipex
goodbye
hello 42
EOF
```

**Shell equivalent:**
```bash
grep hello << EOF | wc -l >> count.txt
```

### Example 5: Advanced Grep and AWK

Extract specific columns:

```bash
./pipex users.csv "grep active" "awk -F, '{print $1, $3}'" active_users.txt
```

**Shell equivalent:**
```bash
< users.csv grep active | awk -F, '{print $1, $3}' > active_users.txt
```

## 📁 Project Structure

```
pipex/
├── 📄 Makefile              # Build automation
├── 📄 README.md             # This file
│
├── 📂 includes/             # Header files
│   ├── libft.h             # Custom library functions
│   └── pipex.h             # Main project header
│
├── 📂 llibtf/              # Custom library implementation
│   ├── ft_putstr_fd.c      # Write string to file descriptor
│   ├── ft_split.c          # Split string by delimiter
│   ├── ft_strjoin.c        # Join two strings
│   ├── ft_strlcpy.c        # Copy string with size limit
│   ├── ft_strlen.c         # Calculate string length
│   └── ft_strnstr.c        # Find substring in string
│
└── 📂 src/                 # Source files
    ├── pipex.c             # Main program entry point
    ├── utils.c             # Child/parent process handlers
    ├── bonus_utils.c       # Bonus utility functions
    ├── here_doc.c          # Here document implementation
    └── pipeline.c          # Multiple pipes implementation
```

## 🔧 Implementation

### Core Components

#### 1. Process Management

- **`main()`**: Entry point, argument validation, mode selection
- **`ft_child()`**: First child process (reads from infile → writes to pipe)
- **`ft_parent()`**: Second child process (reads from pipe → writes to outfile)

#### 2. Command Execution

- **`ft_execute()`**: Parses command, finds executable path, calls `execve()`
- **`ft_get_path()`**: Searches PATH environment variable for executables

#### 3. Bonus Features

- **`run_pipeline()`**: Handles multiple command chaining
- **`run_here_doc()`**: Implements here document functionality

### System Calls Used

| System Call | Purpose |
|------------|---------|
| `fork()` | Create child processes |
| `pipe()` | Create pipes for IPC |
| `dup2()` | Duplicate file descriptors for redirection |
| `execve()` | Execute commands |
| `waitpid()` | Wait for child processes to finish |
| `access()` | Check file/executable permissions |
| `open()`, `close()` | File operations |
| `read()`, `write()` | I/O operations |

### Data Flow Diagram

**Basic Pipe (2 commands):**
```
┌─────────┐     ┌──────┐     ┌──────┐     ┌─────────┐
│ file1   │────▶│ cmd1 │────▶│ cmd2 │────▶│ file2   │
└─────────┘     └──────┘     └──────┘     └─────────┘
   (stdin)        pipe         pipe         (stdout)
```

**Multiple Pipes (N commands):**
```
┌─────┐   ┌────┐   ┌────┐         ┌────┐   ┌─────┐
│file1│──▶│cmd1│──▶│cmd2│── ... ──▶│cmdN│──▶│fileN│
└─────┘   └────┘   └────┘         └────┘   └─────┘
```

## 🧪 Testing

### Manual Testing

Create test files and run basic tests:

```bash
# Create test file
echo "Hello World\nTest Line\nAnother Line" > test.txt

# Test basic pipe
./pipex test.txt "cat" "wc -l" output.txt
cat output.txt  # Should show line count

# Compare with shell behavior
< test.txt cat | wc -l
```

### Error Testing

Test error handling:

```bash
# Non-existent input file
./pipex nonexistent.txt "cat" "wc -l" out.txt

# Invalid command
./pipex test.txt "invalidcmd" "wc -l" out.txt

# Permission errors
touch readonly.txt
chmod 000 readonly.txt
./pipex readonly.txt "cat" "wc -l" out.txt
```

### Memory Leak Testing

Use valgrind to check for memory leaks:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./pipex test.txt "cat" "wc -l" out.txt
```

### Automated Testing

You can use the following testers:

- [pipex-tester](https://github.com/vfurmane/pipex-tester)
- [pipex_tester_42](https://github.com/ael-bekk/pipex_tester_42)

## 📚 Resources

### Documentation

- [Unix Pipes (Wikipedia)](https://en.wikipedia.org/wiki/Pipeline_(Unix))
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/)
- [Advanced Linux Programming](https://mentorembedded.github.io/advancedlinuxprogramming/)

### Man Pages

```bash
man fork     # Process creation
man pipe     # Create pipe
man execve   # Execute program
man dup2     # Duplicate file descriptor
man waitpid  # Wait for process
man access   # Check permissions
```

### Tutorials

- [Understanding Unix Pipes and Redirection](https://www.rozmichelle.com/pipes-forks-dups/)
- [Process Management in Linux](https://www.geeksforgeeks.org/process-management-in-linux/)

## 🤝 Contributing

This is a school project, but feedback and suggestions are welcome!

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add some improvement'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## 👤 Author

**Adavitas**

- GitHub: [@Adavitas](https://github.com/Adavitas)
- Project Link: [https://github.com/Adavitas/pipex](https://github.com/Adavitas/pipex)

## 📝 License

This project is part of the 42 School curriculum. Feel free to use it for educational purposes.

---

<div align="center">

**Made with ❤️ at 42 School**

⭐ If you found this project helpful, consider giving it a star!

</div>
