# Programming Task Lab

A progressive, self-paced C++ / algorithms / computer systems training repository with mathematics integrated into relevant programming tasks.

## Tasks

- [Task 001 — Ring buffer](tasks/001-ring-buffer/README.md) — completed
- [Task 002 — Timestamp index and binary search](tasks/002-timestamp-index/README.md) — completed
- [Task 003 — Sensor log parser](tasks/003-sensor-log/README.md) — completed
- [Task 004 — Weighted grid A* planner](tasks/004-grid-planner/README.md) — current

## Workflow

1. Read the current task README and prerequisite reading.
2. Implement on the task branch (for Task 004: `task/004-grid-planner`).
3. Record research answers, math derivations, testing, and reflection in the task's `notes.md`.
4. Push and open a pull request to `main`.
5. GitHub Actions builds and tests on Linux and Windows.
6. Merge after both checks pass. The next task is unlocked after the merged PR is verified.

Mathematics is integrated into programming assignments, not a separate homework track. Tasks may span multiple days.

## Local build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## Completion rule

A task is complete only when its PR has passing CI checks and is merged into `main`. No deadline: unfinished tasks remain active.
