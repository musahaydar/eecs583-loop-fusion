# Loop Fusion Benchmarks


# Test Names


Tests are named as follows

"Test<x><y><z>_<unique>.cpp"

x represents whether or not to merge (M means merge, N means no merge)

y represents whether it incorporates MIC (Y means yes, N means no)

z represents whether or not we're adding a guard (Y means yes, N means no)

unique represents a unique identifier in case we have duplicate benchmarks.


# Test Name Example

TestMNY_array means we're merging two loops, there is no MIC, there is a guard needed, and we're working with arrays