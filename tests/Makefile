# To use: make no-opt test=normal-test1.cpp

no-opt:
	clang -O -Xclang -disable-llvm-passes -emit-llvm $(test) -c -o no-opt.bc

built-in-debug:
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -debug -loop-fusion -loop-fusion-verbose-debug < no-opt.bc

legacy:
	$(MAKE) clean-test
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION_LEGACY.so -loop-fusion-legacy < no-opt.bc > /dev/null

legacy-debug:
	$(MAKE) clean-test
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION_LEGACY.so -debug -loop-fusion-legacy -loop-fusion-legacy-verbose-debug < no-opt.bc

loop-fuse:
	$(MAKE) clean-test
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION.so -loop-fusion-583 < no-opt.bc > /dev/null

loop-fuse-debug:
	$(MAKE) clean-test
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuse/LOOP_FUSION.so -debug -loop-fusion-583 -loop-fusion-583-verbose-debug < no-opt.bc

compare:
	clang no-opt.bc -o test_no_opt
	clang fused.bc -o test_fused
	./test_no_opt > res_no_opt
	./test_fused > res_fused
	diff res_no_opt res_fused

clean-test:
	-rm -f *.bc
	-rm res_* test_*

clean:
	$(MAKE) clean-test
	-rm -ri dot
