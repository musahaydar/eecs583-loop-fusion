add_llvm_library(LOOP_FUSION_LEGACY MODULE
  LoopFuse.cpp

  PLUGIN_TOOL
  opt
  )
