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

✨ Engineering & Systems Programming HighlightsProcess Isolation: Each operation executes within its own virtual address space, eliminating side-effects across workloads.   IPC with Anonymous Pipes: Unidirectional byte streaming using pipe() connects the worker's stdout directly to the parent's read descriptor.   File Descriptor Redirection: Utilizes dup2(pipe_arr[1], STDOUT_FILENO) so child executables write calculations naturally to stdout without awareness of the parent pipe.   Dynamic Binary Replacement: Seamless runtime handover via execl() to modular binaries based on user input (+, -, *, /).   Asynchronous Persistence: Dedicated worker (saver.c) spawned to append results to disk without blocking subsequent terminal interactions.   Defensive Error Handling: Validates division-by-zero anomalies and argument counts at the subprocess level.

.
├── makefile             # Multi-target build and clean automation
├── calculator.c         # Orchestrator: input parsing, pipe routing, child supervision
├── addition.c           # Subprocess worker: addition logic
├── subtraction.c        # Subprocess worker: subtraction logic
├── multiplication.c     # Subprocess worker: multiplication logic
├── division.c           # Subprocess worker: division with zero-division validation
├── saver.c              # Subprocess worker: persistent logging to results.txt
├── report.pdf           # Academic technical report and verification notes
└── README.md            # Technical documentation
```
