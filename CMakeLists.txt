cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(OPENMP_LLVM_TOOLS_DIR "" CACHE PATH "Path to LLVM tools for testing")

# TODO: Remove this later
set(LIBOMP_OMPT_SUPPORT ON)

add_subdirectory(runtime)

if (NOT WIN32)
  add_subdirectory(libomptarget)
endif()
