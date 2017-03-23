cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(OPENMP_LLVM_TOOLS_DIR "" CACHE PATH "Path to LLVM tools for testing")

# TODO: Remove this later
set(LIBOMP_OMPT_SUPPORT ON CACHE BOOL
    "Enable OMPT Support")

if (${USE_STATIC_CHUNKS})
  add_definitions(-DOMPT_STATIC_CHUNKS)
  message (STATUS "Compiling runtime with static chunk info")
endif()

add_subdirectory(runtime)

if (NOT WIN32)
  add_subdirectory(libomptarget)
endif()
