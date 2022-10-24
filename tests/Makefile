# To use: make no-opt test=normal-test1

no-opt:
	clang -emit-llvm $(test).cpp -c -o no-opt.bc

legacy:
	clang -emit-llvm $(test).cpp -c -o no-opt.bc  # compile program to bitcode
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION.so -loop-fusion < no-opt.bc > /dev/null

clean:
	rm -f *.bc
	rm -ri dot
