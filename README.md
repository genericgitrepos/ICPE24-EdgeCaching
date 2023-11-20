# ICPE24-EdgeCaching

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
mkdir executables
make hr
```

This will compile the project and create the necessary executables.

## Running the Project

After building the project, you can run the simulation using the following command:

```bash
./executables/hr [args]
```

Replace `[args]` with the appropriate arguments for the simulation. The `--file-path` argument is required and specifies the path to the file to use for the simulation. Example:

```bashe
./executables/hr --file-path=inputs/wikiTrace.tr --cache-size=68719476736
```

### Additional args:

- `--file-path=`: Specifies the path to the trace file to use for the simulation.
- `--verbose`: Enables verbose logging. If set to true, additional debug information will be printed.
- `--rounds=`: Specifies the number of rounds for the simulation.
- `--cache-size=`: Sets the cache size in bytes for the simulation.
- `--evict-hot-for-cold`: If set to true, cache-friendly object will be evicted for cache-averse object.
- `--features-length=`: Sets the length of the features for the simulation (2 is for frequency and size, to give 30 deltas for instance you would have to set this as 32).
- `--hazard-bandwidth=`: Specifies the hazard bandwidth for the simulation.
- `--hazard-discrete`: If set to true, the hazard will be discrete.
- `--future-labeling`: If set to true, look back labeling will be used.
- `--one-time-training`: If set to true, training will only be performed once.
- `--max-boost-rounds=`: Specifies the maximum number of boosting rounds.
- `--feature-frequency`: If set to true, frequency will be used in features.
- `--feature-decayed-frequency=`: Sets the decay factor for feature decayed frequency.
- `--feature-size`: If set to true, feature size will be used.
- `--report-interval=`: Specifies the report interval for the simulation (by default this is 1 million).
- `--log-file=`: Specifies the name of the log file.


## Trace Format:
Request traces are expected to be in a space-separated format with 3 columns:

* time (can be double)
* id should be a uint32, used to uniquely identify objects
* size should be uint32, this is object's size in bytes

| time | id | size |
|-----------------|-----------------|-----------------|
| 1  | 1  | 140  |
| 3  | 2  | 290  |
