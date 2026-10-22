# Programming Task Lab

A progressive, self-paced C++ / algorithms / computer systems training repository.

## Workflow
1. Read the current task in `tasks/001-ring-buffer/README.md`.
2. Implement on a branch named `task/001-ring-buffer`.
3. Push and open a pull request to `main`.
4. GitHub Actions checks build and tests on Linux and Windows.
5. Merge after all checks pass. The next task is unlocked after the merged PR is verified.

## Local build
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## Completion rule
A task is complete only when its PR has passing CI checks and is merged into `main`. No deadline: unfinished tasks remain active.
