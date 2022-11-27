
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopIterator.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar/LoopPassManager.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/Analysis/BlockFrequencyInfo.h"


#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace llvm;

#define DEBUG_TYPE "trip-count"



struct TripCountPass : public LoopPass {
  static char ID;
  TripCountPass() : LoopPass(ID) {}

  bool runOnLoop(Loop *L, LPPassManager &LPM) override {
    bool Changed = false;

    auto &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    auto &SE = getAnalysis<ScalarEvolutionWrapperPass>().getSE();
    auto trip_count = SE.getConstantMaxBackedgeTakenCount(L);
    if (isa<SCEVCouldNotCompute>(trip_count)) {
      LLVM_DEBUG(dbgs() << "getConstantMaxBackedgeTakenCount: Could not solve trip count for  " << L->getName() << "\n");
    }
    else {
      auto tc_value = dyn_cast<SCEVConstant>(trip_count);
       LLVM_DEBUG(dbgs() << "getConstantMaxBackedgeTakenCount: Loop trip count for " << L->getName() << " is " << tc_value <<"\n");
    }    
    auto trip_count_constant = SE.getSmallConstantTripCount(L);
    LLVM_DEBUG(dbgs() << "getSmallConstantTripCount: Loop trip count for " << L->getName() << " is " << trip_count_constant <<"\n");
    return Changed;
  }


  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequired<LoopInfoWrapperPass>();
    AU.addRequired<ScalarEvolutionWrapperPass>();
  }



};


char TripCountPass::ID = 0;
static RegisterPass<TripCountPass> X("trip-count", "Trip Count Debuging for Loop Fusion", false, false);
