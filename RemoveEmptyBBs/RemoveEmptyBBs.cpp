
#include "llvm/IR/CFG.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar/LoopPassManager.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

#define DEBUG_TYPE "remove-empty-bbs"

// An "empty" basic block is a basic block which only contains a branch instruction
// to the next bb. We can replace the branch in the predecessor to the success in that case 
// to remove the empty BB entirely
struct RemoveEmptyBBs : public FunctionPass {
  static char ID;
  RemoveEmptyBBs() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    bool changed = false;

    // loop through basic blocks of this function
    for (BasicBlock &bb : F) {
      LLVM_DEBUG(dbgs() << "\nConsidering BB: " << bb.getName() << "\n";);

      // for each basic block, check if the instruction count is 1 and it's a branch
      int num_insts = 0;
      bool remove_bb = true;
      BasicBlock *target = nullptr;

      for (Instruction &inst : bb) {
        num_insts += 1;

        if(inst.getOpcode() != Instruction::Br || num_insts > 1) {
          remove_bb = false;
          break;
        }

        target = ((BranchInst *)&inst)->getSuccessor(0);
      }

      if (!remove_bb) {
        LLVM_DEBUG(dbgs() << "\tCannot remove basic block\n";);
        continue;
      }
      
      // this BB can be removed
      // this crashes LLVM for some reason :(
      // MergeBlockIntoSuccessor(&bb);
      // changed = true;

      for (BasicBlock *pred : predecessors(&bb)) {
        BranchInst *pred_br = (BranchInst *)pred->getTerminator();

        // loop through all this blocks preds to point to it's succ
        for(int i = 0; i < pred_br->getNumSuccessors(); ++i) {
          if (pred_br->getSuccessor(i) == &bb) {
            pred_br->setSuccessor(i, target);
            changed = true;

            // update phi nodes in target
            // for (Instruction &inst : *target) {
            //   if(isa<PHINode>(inst)) {
            //     PHINode *phi = (PHINode *)&inst;

            //     LLVM_DEBUG(dbgs() << "\tLooking at PHINode:\n");
            //     LLVM_DEBUG(phi->print(dbgs()));
            //     LLVM_DEBUG(dbgs() << "\n");

            //     // check all incoming values for the phi node to see if any are from this bb we're deleting
            //     for (int j = 0; j < phi->getNumIncomingValues(); ++j) {
            //       BasicBlock *incoming = phi->getIncomingBlock(j);
            //       LLVM_DEBUG(dbgs() << "\t\tPHINode has parent block: " << incoming->getName() << "\n");
                  
            //       if (incoming == &bb) {
            //         // phi->setIncomingBlock(j, pred);
            //         phi->replaceIncomingBlockWith(incoming, pred);
            //         LLVM_DEBUG(dbgs() << "\t\tReplacing " << incoming->getName() << " with " << pred->getName() << "\n");
            //       }
            //     }
            //   }
            // }
            updatePhiNodes(target, &bb, pred);    
          }
        }

        // delete the branch from the pred
        bb.back().eraseFromParent();

        // Add unreachable to now empty BB.
        new UnreachableInst(bb.getContext(), &bb);

        // remove the basic block
        // this is crashing, I can't explain why
        // DeleteDeadBlock(&bb);
      }
    }

    return changed;
  }

};


char RemoveEmptyBBs::ID = 0;
static RegisterPass<RemoveEmptyBBs> X("remove-empty-bbs", "Pass to Remove Empty BBs From All Functions", false, false);
