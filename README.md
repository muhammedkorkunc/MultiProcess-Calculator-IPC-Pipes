# 🧮 Multi-Process Modular Calculator via POSIX Pipes

An operating systems systems-programming project implemented in **C (POSIX)** demonstrating process lifecycle management, IPC through unidirectional anonymous pipes, file descriptor redirection, and modular process execution.

---

## 🏛️ System Architecture & Data Flow

The application isolates each mathematical operation into a distinct executable binary, orchestrating data communication through kernel pipes rather than monolithic in-memory calculations:

```text
               ┌────────────────────────────────────────────────────────┐
               │              Parent Process (calculator)               │
               │  • Accepts user input (operands & operator)            │
               │  • Instantiates anonymous pipe: pipe(pipe_arr)         │
               └───────────┬────────────────────────────────┬───────────┘
                           │ fork()                         │ wait() & read()
                           ▼                                ▲
        ┌──────────────────────────────────────┐            │
        │             Child Process            │            │
        │  • dup2(pipe_arr[1], STDOUT_FILENO)  │            │
        │  • execl() replacements:             │            │
        │    - ./addition <num1> <num2>        │            │
        │    - ./subtraction <num1> <num2>     │            │
        │    - ./multiplication <num1> <num2>  │            │
        │    - ./division <num1> <num2>        │            │
        └──────────────────┬───────────────────┘            │
                           │                                │
                           │ write(STDOUT_FILENO, &result)  │
                           └─────────────► [ Anonymous Pipe ]
                                                            │
                                                            ▼
                                   ┌─────────────────────────────────┐
                                   │ File Saver Process (fork+execl) │
                                   │  • ./saver <result>             │
                                   │  • Appends to "results.txt"     │
                                   └─────────────────────────────────┘