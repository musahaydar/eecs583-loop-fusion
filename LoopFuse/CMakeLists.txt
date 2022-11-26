add_llvm_library(LOOP_FUSION MODULE
  LoopFuse.cpp

  PLUGIN_TOOL
  opt
  )
