# To use: make no-opt test=normal-test1.cpp

# no-opt recipe preps loops for loop fusion by running other necessary passes
# first we run -loop-rotate since the loop-fusion pass expects rotated loops
# then -mem2reg replaces memory loop trip count variables with registers to make the trip count computable
# this adds redundant phi nodes, which we remove with -instcombine (currently they break they fusion pass)
# then we run the custom RemoveEmptyBBs pass to remove empty BBs which may be considered intervening code
no-opt:
	clang -O -Xclang -disable-llvm-passes -emit-llvm $(test) -c -o no-opt.bc
	opt -enable-new-pm=0 -loop-simplify -mem2reg -loop-rotate -o no-opt.bc < no-opt.bc
	opt -enable-new-pm=0 -instcombine -simplifycfg -o no-opt.bc < no-opt.bc

# no-opt-cpp:
# 	clang++ -O -Xclang -disable-llvm-passes -emit-llvm $(test) -c -o no-opt.bc

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
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuse/LOOP_FUSION.so -debug -loop-fusion-583 -loop-fusion-583-verbose-debug  < no-opt.bc

loop-fuse-stable-debug:
	$(MAKE) clean-test
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseStable/LOOP_FUSION.so -debug -loop-fusion-583  -loop-fusion-583-verbose-debug  < no-opt.bc

trip-count:
	$(MAKE) no-opt
	opt -enable-new-pm=0 -o fused.bc -load ../build/TripCountDebug/TRIP_COUNT.so -trip-count -debug -analyze -mem2reg -indvars -loop-simplify -scalar-evolution < no-opt.bc

# compare results after running fusion on a test
compare:
	clang no-opt.bc -o test_no_opt
	clang fused.bc -o test_fused
	./test_no_opt > res_no_opt
	./test_fused > res_fused
	diff res_no_opt res_fused

compare_scanf:
	clang no-opt.bc -o test_no_opt
	clang fused.bc -o test_fused
	./test_no_opt < input.txt > res_no_opt
	./test_fused < input.txt > res_fused
	diff res_no_opt res_fused

# generate graphs after running fusion on a test
viz:
	./viz.sh no-opt.bc
	./viz.sh fused.bc

clean-test:
	-rm -f *.bc
	-rm res_* test_*

clean:
	$(MAKE) clean-test
	-rm -ri dot
