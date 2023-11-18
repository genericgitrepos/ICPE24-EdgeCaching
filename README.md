# ICPE24-EdgeCaching
```markdown
# Project Installation and Running Guide

This guide provides instructions on how to build and run the project.

## Prerequisites

The project requires LightGBM. If you already have LightGBM installed and it's accessible by g++, you can skip the LightGBM installation step.

## Building LightGBM

If you don't have LightGBM installed, you can build it using the provided Makefile:

```bash
mkdir -p builds
make build_lightgbm
```

This will build LightGBM from source.

## Building the Project

After installing LightGBM, you can compile the project using the following command:

```bash
mkdir -p builds
make hr
```

This will compile the project and create the necessary executables.

## Running the Project

After building the project, you can run the simulation using the following command:

```bash
./executables/hr [args]
```

Replace `[args]` with the appropriate arguments for the simulation. The `--file-path` argument is required and specifies the path to the file to use for the simulation.

### Additional args:

- `--file-path=`: Specifies the path to the file to use for the simulation.
- `--concurrency=`: Sets the concurrency level for the simulation.
- `--verbose`: Enables verbose logging. If set to true, additional debug information will be printed.
- `--rounds=`: Specifies the number of rounds for the simulation.
- `--cache-size=`: Sets the cache size for the simulation.
- `--hot-lower-bound=`: Sets the lower bound for hot data.
- `--cold-lower-bound=`: Sets the lower bound for cold data.
- `--evict-hot-for-cold`: If set to true, hot data will be evicted for cold data.
- `--window-size=`: Sets the window size for the simulation.
- `--learning-rate=`: Specifies the learning rate for the simulation.
- `--features-length=`: Sets the length of the features for the simulation.
- `--hazard-bandwidth=`: Specifies the hazard bandwidth for the simulation.
- `--hazard-discrete`: If set to true, the hazard will be discrete.
- `--future-labeling`: If set to true, future labeling will be used.
- `--one-time-training`: If set to true, training will only be performed once.
- `--max-boost-rounds=`: Specifies the maximum number of boosting rounds.
- `--feature-frequency`: If set to true, feature frequency will be used.
- `--feature-decayed-frequency=`: Sets the decay factor for feature frequency.
- `--feature-size`: If set to true, feature size will be used.
- `--report-interval=`: Specifies the report interval for the simulation.
- `--log-file=`: Specifies the name of the log file.
```
