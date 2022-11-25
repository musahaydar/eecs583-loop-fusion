# To use: make no-opt test=normal-test1.cpp

no-opt:
	clang -emit-llvm $(test) -c -o no-opt.bc

built-in-debug:
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -debug -loop-fusion -loop-fusion-verbose-debug < no-opt.bc

legacy:
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION.so -loop-fusion-legacy < no-opt.bc > /dev/null

legacy-debug:
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION.so -debug -loop-fusion-legacy -loop-fusion-legacy-verbose-debug < no-opt.bc

clean:
	rm -f *.bc
	rm -ri dot
