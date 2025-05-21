# Philosophers

✅ **Completed**: Mandatory  
🏅 **Score**: 100/100

![42 Logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTXfAZMOWHDQ3DKE63A9jWhIqQaKcKqUIXvzg&s)

**Philosophers** is a concurrency project from 42 School that introduces you to multithreading, synchronization, and the problem of deadlocks. The goal is to simulate the classical Dining Philosophers Problem using POSIX threads and mutexes in C.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Tests](#tests)
- [Troubleshooting](#troubleshooting)

## Description

The **Philosophers** project is a simulation of a classic synchronization problem. A group of philosophers sits at a table with a fork between each pair. Each philosopher must alternately think and eat. They must use the two forks closest to them to eat, and the simulation must avoid deadlocks and race conditions.

![Philosophers problem](https://ibb.co/yFys2J3S)

## Features

- **Multithreaded Simulation** using `pthread` library.
- **Mutex-Based Synchronization** to manage access to forks.
- **Death Detection** with timing constraints.
- **Time-Stamped Output** for easy analysis of the simulation.
- **Precise Sleep Handling** to ensure accurate timing and fairness.

## Requirements

- **C Compiler** (e.g., `gcc`)
- **Make** (for building the project)
- **POSIX Threads Support**
- **Unix-based Operating System:** Linux or macOS.

## Installation

1. **Clone the repository:**
```
git clone https://github.com/tigran-sargsyan-w/philosophers.git
```

2. **Navigate to the project directory:**
```
cd philosophers
```

3. **Compile the project:**
```
make
```

## Usage

Run the simulation with the following arguments:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example:
```
./philo 5 800 200 200
```

This starts a simulation with 5 philosophers, each of whom:
- dies if they don’t eat within 800 ms
- eats for 200 ms
- sleeps for 200 ms

Optional last argument stops the simulation after all philosophers have eaten that many times.

## How It Works

1. **Initialization:**  
   The program parses arguments, allocates memory, creates philosopher threads, and initializes mutexes.

2. **Thread Routine:**  
   Each philosopher follows a routine of:
   - Taking forks (mutexes)
   - Eating
   - Sleeping
   - Thinking

3. **Timing and Death Monitoring:**  
   A monitor thread checks if any philosopher has starved.

4. **Clean Exit:**  
   When the simulation ends, all threads and mutexes are properly destroyed.


## Tests

The following test cases were used to validate the correctness, robustness, and memory safety of the simulation:

| Command                                                                 | Expected Result                                                       |   |
|-------------------------------------------------------------------------|------------------------------------------------------------------------|:-:|
| `./philo 1 200 200 200`                                                | Philosopher 1 only takes a fork and dies after 200 ms                 | ✅ |
| `./philo 2 800 200 200`                                                | No philosopher dies                                                   | ✅ |
| `./philo 5 800 200 200`                                                | No philosopher dies                                                   | ✅ |
| `./philo 5 800 200 200 7`                                              | Simulation stops after each philosopher has eaten 7 times             | ✅ |
| `./philo 4 410 200 200`                                                | No philosopher dies                                                   | ✅ |
| `./philo 4 310 200 200`                                                | One philosopher dies                                                  | ✅ |
| `./philo 4 300 200 1.2`                                                | Invalid argument                                                      | ✅ |
| `./philo 4 0 200 200`                                                  | Invalid argument                                                      | ✅ |
| `./philo 4 -300 200 200`                                               | Invalid argument                                                      | ✅ |
| `./philo 4 300 200 2147483647`                                         | One philosopher dies after 300 ms                                     | ✅ |
| `./philo 4 2147483647 200 200`                                         | No philosopher dies                                                   | ✅ |
| `./philo 4 214748364732 200 200`                                       | Invalid argument                                                      | ✅ |
| `./philo 4 200 210 200`                                                | One philosopher dies before 210 ms                                    | ✅ |
| `valgrind --tool=helgrind --error-exitcode=1 ./philo 5 200 300 400 5` | One philosopher dies                                                  | ✅ |
| `valgrind --tool=helgrind --error-exitcode=1 ./philo 5 800 200 200 2` | Each philosopher eats 2 times                                         | ✅ |
| `valgrind --tool=drd --error-exitcode=1 ./philo 5 200 300 400 5`      | One philosopher dies                                                  | ✅ |
| `valgrind --tool=drd --error-exitcode=1 ./philo 5 800 200 200 2`      | Each philosopher eats 2 times                                         | ✅ |
| `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./philo 5 200 300 400 5` | One philosopher dies                                   | ✅ |
| `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./philo 5 800 200 200 2` | Each philosopher eats 2 times                          | ✅ |


## 🧪 Edge Case

```
./philo 3 1000 330 330
```

This test is a borderline case where only one philosopher can eat at a time (odd number of philosophers and shared forks).  
The sum of `time_to_eat + time_to_sleep` is 660 ms, leaving very little buffer before reaching `time_to_die = 1000 ms`.

Any slight delay in thread scheduling or `usleep` inaccuracy may cause one philosopher to starve unexpectedly.  
This case highlights the importance of precise timing and fairness in concurrent systems.

> 📌 **Note:** I discovered this edge case after completing the project, so it remains **unresolved** in the final implementation.


## Troubleshooting

- **Philosophers die immediately:** Check your timing values and ensure `time_to_die > time_to_eat + time_to_sleep`.
- **Race conditions or segfaults:** Review mutex usage and shared memory access.
- **Memory leaks:** Run with `valgrind` to detect unfreed memory.

---

Happy coding! 🧠🍴
