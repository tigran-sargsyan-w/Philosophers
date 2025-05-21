# Philosophers

✅ **Completed**: Mandatory  
🏅 **Score**: 100/100

In this project, you will learn the basics of threading a process.  
You will see how to create threads and you will discover mutexes.

## Tests

| Test                                    | Expected result                                                        |   |
|-----------------------------------------|------------------------------------------------------------------------|:-:|
| `./philo 1 200 200 200`                 | philo 1 only takes a fork and dies after 200 ms                         | ✅ |
| `./philo 2 800 200 200`                 | nobody dies                                                            | ✅ |
| `./philo 5 800 200 200`                 | nobody dies                                                            | ✅ |
| `./philo 5 800 200 200 7`               | the simulation stops when each philosopher has eaten 7 times            | ✅ |
| `./philo 4 410 200 200`                 | nobody dies                                                            | ✅ |
| `./philo 4 310 200 200`                 | one philosopher dies                                                   | ✅ |
| `./philo 4 300 200 1.2`                 | invalid argument                                                       | ✅ |
| `./philo 4 0 200 200`                   | invalid argument                                                       | ✅ |
| `./philo 4 -300 200 200`                | invalid argument                                                       | ✅ |
| `./philo 4 300 200 2147483647`          | one philosopher dies after 300 ms                                       | ✅ |
| `./philo 4 2147483647 200 200`          | nobody dies                                                            | ✅ |
| `./philo 4 214748364732 200 200`        | invalid argument                                                       | ✅ |
| `./philo 4 200 210 200`                 | one philosopher dies, you must display the death before 210 ms         | ✅ |
| `valgrind --tool=helgrind --error-exitcode=1 ./philo 5 200 300 400 5` | one philosopher dies                                                   | ✅ |
| `valgrind --tool=helgrind --error-exitcode=1 ./philo 5 800 200 200 2` | each philosopher should eat 2 times                                    | ✅ |
| `valgrind --tool=drd --error-exitcode=1 ./philo 5 200 300 400 5`      | one philosopher dies                                                   | ✅ |
| `valgrind --tool=drd --error-exitcode=1 ./philo 5 800 200 200 2`      | each philosopher should eat 2 times                                    | ✅ |
| `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./philo 5 200 300 400 5` | one philosopher dies                                                   | ✅ |
| `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./philo 5 800 200 200 2` | each philosopher should eat 2 times                                    | ✅ |

✅ **All tests passed!**
