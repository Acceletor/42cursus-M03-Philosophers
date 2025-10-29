# Philosophers

A classic concurrency project: implement the **Dining Philosophers** problem with **threads** and **mutexes** in **C**.  
The goal is to manage resource sharing (forks) and timing **without deadlocks, data races, or starvation** — while respecting the **42 Norm**, strict error handling, and precise timing.

---

## 🧠 Subject Summary

You must write a program called **`philo`** that:

- Creates **N philosophers** sitting around a circular table.  
- Each philosopher **thinks → takes forks → eats → sleeps** in a loop.  
- A philosopher **dies** if they don’t eat within `time_to_die` ms since their last meal.  
- The simulation stops when either:
  - A philosopher dies, **or**
  - (if provided) every philosopher has eaten at least `number_of_times_each_philosopher_must_eat`.

---

## ⚙️ Constraints

- **Language:** C  
- **Libraries:** `pthread`, `unistd`, `stdio`, `stdlib`, etc.  
- **Synchronization:** threads and mutexes only  
- **Requirements:**
  - No **data races**
  - No **deadlocks**
  - Correct and **precise timing**
- **Forks:**  
  - One fork per philosopher  
  - To eat, a philosopher needs **both the left and right fork**  
  - **One mutex per fork** is standard

---

## 🧩 Build & Run

```bash
# Build
make            # builds philo
make clean      # removes object files
make fclean     # removes object files + binary
make re         # rebuilds everything
```
```bash
# Run
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [times_each_must_eat]
```
---

## 💡 Examples

```bash
# 5 philosophers, normal speeds
./philo 5 800 200 200

# 200 philosophers (stress test)
./philo 200 610 200 200

# stop when everyone has eaten 7 times
./philo 5 800 200 200 7
```
---

## 🖨️ Output Format

Each event must be printed on a single line with a relative timestamp (in ms) since the simulation started:
```
<timestamp_ms> <philo_id> <message>
```
Possible messages:
- has taken a fork
- is eating
- is sleeping
- is thinking
- died
