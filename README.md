# 42 Malaga

Personal repository containing exercises, projects, and exam preparation completed during my training at **42 Malaga**.

The purpose of this repository is to document my technical progress in low-level programming, algorithms, Unix systems, networking, containers, and modern C++. It is also intended as part of my portfolio/CV, showcasing real code written under the usual 42 constraints: limited use of external functions, manual memory management, `Makefile`, coding standards, and project-based evaluation.

## About 42

42 is a project-based programming school focused on peer learning and peer evaluation. The learning process is built around solving practical problems without traditional classes, strengthening autonomy, debugging skills, documentation reading, and the ability to defend technical decisions.

## Repository Contents

```text
.
├── c-piscine/   # C Piscine exercises and introductory projects
├── cursi/       # Core curriculum projects organized by rings
├── exams/       # Exam practice and solutions
├── c00/         # Standalone C exercises
├── commands.txt # Common compilation and review commands
└── Paso.txt     # Personal notes about the exam workflow
```

## Technologies and Skills

- **Languages:** C, C++, Shell, Makefile.
- **Systems:** Unix/Linux, processes, pipes, signals, file descriptors, permissions, and memory.
- **Algorithms:** sorting, parsing, backtracking, linked data structures, input validation, and operation optimization.
- **Graphics programming:** projects using MiniLibX/MLX42.
- **Concurrency:** threads, mutexes, and synchronization.
- **Networking and backend:** sockets, IRC protocol, HTTP servers, and service configuration.
- **DevOps:** Docker, Docker Compose, NGINX, MariaDB, WordPress, Redis, Prometheus, and secrets management.
- **Good practices:** compilation with `-Wall -Wextra -Werror`, `Makefile`, Norminette checks, and Git version control.

## Featured Projects

| Project | Path | Focus |
| --- | --- | --- |
| **Libft** | `cursi/ring_0/libft` | Implementation of a foundational C library recreating standard functions and custom utilities. |
| **ft_printf** | `cursi/ring_1/printf` | Partial reimplementation of `printf`, including variadic arguments and output formatting. |
| **get_next_line** | `cursi/ring_1/get_next_line` | Incremental file descriptor reading with configurable buffer size and dynamic memory management. |
| **pipex** | `cursi/ring_2/pipex` | Reproduction of shell pipe behavior using processes, `fork`, `execve`, and redirections. |
| **push_swap** | `cursi/ring_2/push_swap` | Integer sorting with two stacks and a limited instruction set, focused on minimizing moves. |
| **so_long** | `cursi/ring_2/so_long` | Small 2D game with maps, sprites, path validation, and keyboard events. |
| **minishell** | `cursi/ring_3/minishell` | Custom shell with parsing, builtins, redirections, pipes, environment variables, and signals. |
| **philosophers** | `cursi/ring_3/philosophers` | Classic concurrency problem using threads, mutexes, and timing control. |
| **CPP Modules** | `cursi/ring_4`, `cursi/ring_5/cpp_*` | Progressive C++ exercises covering classes, inheritance, polymorphism, exceptions, templates, and STL. |
| **IRC** | `cursi/ring_5/irc` | C++ IRC server based on sockets and client/command management. |
| **webserv** | `cursi/ring_5/webserv` | C++ HTTP server with configuration parsing, routing, and request handling. |
| **Inception** | `cursi/ring_5/inception` | Docker infrastructure with NGINX, WordPress, MariaDB, and bonus services. |

## Piscine and Exams

- `c-piscine/` contains foundational C exercises: pointers, strings, arrays, recursion, dynamic memory, lists, parsing, and small group projects such as `rush` and `bsq`.
- `exams/` contains preparation exercises for Exam Rank 02, 03, 04, and 05, organized by level.
- `Paso.txt` contains personal notes about the 42 exam workflow.

## How to Build

Most main projects include their own `Makefile`. General example:

```bash
cd cursi/ring_2/push_swap
make
./push_swap 3 2 1
```

To remove generated binaries and object files:

```bash
make clean
make fclean
```

Some projects include additional targets such as `bonus`, `re`, `setup`, `up`, or `down`. Check the `Makefile` inside each project directory.

## Quick Examples

Build and run `push_swap`:

```bash
cd cursi/ring_2/push_swap
make
./push_swap 5 2 9 1 3
```

Build `bsq`:

```bash
cd c-piscine/bsq
make
./bsq m1
```

Start `inception`:

```bash
cd cursi/ring_5/inception
make setup
make up
```

## Working Standards

- C/C++ code compiled with strict flags when applicable: `-Wall -Wextra -Werror`.
- Use of `Makefile` to automate compilation, cleanup, and bonus targets.
- Explicit memory management and leak checks during development.
- Input validation and error handling as core parts of each project.
- Progressive documentation of learnings, commands, and exercises.

## Note

This repository brings together academic and learning work. Some exercises may include practice versions, local tests, or personal notes. The featured curriculum projects are the most representative ones for evaluating my technical growth.

## Author

**Sebastian Villa**  
42 login: `svilla-d`
