# Loop Fusion Pass

## Legacy Pass

### Building The Pass

Build the pass as follows:

```
mkdir build
cd build
cmake ..
make
```

### Running The Pass

To run the legacy loop fusion pass on a test and print debugs, make a test as follows:

```
cd tests
make clean
make legacy-debug test=<test_name>
```
`<test_name>` can be something like `normal-test0.cpp`, corresponding to `normal-test0.cpp`.

### Visualizing The Results

In the tests dir, run `./viz.sh <bitcode>` to vizualize the CFG for the test results. `<bitcode>` can be something like `no-opt.bc` or `fused.bc`, corresponding to the outputs of the `Makefile` called `no-opt.bc` or `fused.bc`.