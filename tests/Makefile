# To use: make no-opt test=normal-test1

no-opt:
	clang -emit-llvm $(test).cpp -c -o no-opt.bc

legacy:
	clang -emit-llvm $(test).cpp -c -o no-opt.bc  # compile program to bitcode
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION.so  -analyze -scalar-evolution -mem2reg --loop-simplify -loop-fusion-legacy < no-opt.bc > /dev/null

legacy-debug:
	clang -emit-llvm $(test).cpp -c -o no-opt.bc  # compile program to bitcode
	opt -enable-new-pm=0 -o fused.bc -load ../build/LoopFuseLegacy/LOOP_FUSION.so  -analyze -scalar-evolution -mem2reg --loop-simplify -loop-fusion-legacy -loop-fusion-legacy-verbose-debug -debug < no-opt.bc

clean:
	rm -f *.bc
	rm -ri dot
