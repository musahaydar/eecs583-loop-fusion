#!/bin/bash
# Usage: viz.sh benchmark or vis.sh benchmark [TYPE]
# Do not add ".bc" to the end of the benchmark name, the script will find the file benchmark.bc
# TYPE should be one of: cfg, cfg-only, dom, dom-only, postdom, postdom-only.
# Default type is cfg.

BENCH=$1

# Default to cfg
VIZ_TYPE=${2:-cfg}

OUTPUT_DIR=$(realpath ./dot)  # will put .pdf file here
TMP_DIR=$OUTPUT_DIR/tmp       # will put .dot files here
BITCODE_DIR=$(pwd)            # run this script from the same dir as bitcode
BITCODE=$BITCODE_DIR/$BENCH.bc

mkdir -p $OUTPUT_DIR
mkdir -p $TMP_DIR
cd $TMP_DIR

# Generate .dot files in tmp dir
opt -enable-new-pm=0 -dot-$VIZ_TYPE $BITCODE > /dev/null

# Combine .dot files into PDF
if [[ $VIZ_TYPE == "cfg" ]]; then
  DOT_FILES=$(ls .*.dot)
else
  DOT_FILES=$(ls *.dot)
fi
cat $DOT_FILES | dot -Tpdf > $OUTPUT_DIR/$BENCH.$VIZ_TYPE.pdf
echo "Created $BENCH.$VIZ_TYPE.pdf"

rm -rf $TMP_DIR
