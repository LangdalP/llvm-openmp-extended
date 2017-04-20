# LLVM OpenMP - Extended for Grain Graphs

Forked from: https://github.com/OpenMPToolsInterface/LLVM-openmp/tree/towards_tr4

This version of the LLVM OpenMP runtime has the following OMPT extensions:

- The ability to obtain the duration of task creation
- The ability to obtain information about loop iteration ranges and chunks

The exact approach can still change, but at the time of writing, it is as follows:

### Summary

**Note: Support for the chunk callback for statically scheduled loops requires that programs are compiled with the following Clang fork:** https://github.com/LangdalP/clang/tree/pedervl/static-chunks-conditional
```c
// If the tool registers ext_tool_time callback, it is used by the runtime to calculate durations.
// If it is not registered, durations are reported as 0 instead.
typedef double (*ext_tool_time_t) (void);

// New ompt_callback_task_create
typedef void (*ompt_callback_task_create_t) (
    ompt_data_t *parent_task_data,
    const ompt_frame_t *parent_frame,
    ompt_data_t *new_task_data,
    ompt_task_type_t type,
    int has_dependences,
    double event_duration,  // New parameter
    const void *codeptr_ra
);

typedef enum ompt_loop_sched_e {
    ext_loop_sched_static   = 1,
    ext_loop_sched_dynamic  = 2,
    ext_loop_sched_guided   = 3
} ompt_loop_sched_t;

// Invoked per chunk
typedef void (*ompt_callback_chunk_t) (
    ompt_data_t *task_data,     // The impl. task of the worker
    int64_t lower,              // Lower bound of chunk
    int64_t upper,              // Upper bound of chunk
    double create_duration,     // Interval found from tool-supplied instants
    int is_last_chunk           // Is it the last chunk?
);

// Replaces the old ompt_callback_work
typedef void (*ompt_callback_loop_t) (
    ext_loop_sched_t loop_sched,    // Schedule type at runtime
    ompt_scope_endpoint_t endpoint, // Begin or end?
    ompt_data_t *parallel_data,     // The parallel region
    ompt_data_t *task_data,         // The implicit task of the worker
    int is_iter_signed,             // Is the loop iteration variable signed?
    int64_t step,                   // Loop increment
    const void *codeptr_ra          // Runtime call return address
);
```

# Some known bugs

- For static loops, step is always reported as 1. This is due to Clang's code generation, and requires a fix in Clang.
- For dynamic loops, an extra chunk with range [0, 0] is reported to the tool on each worker

# How to configure/build:
## Make all implemented callbacks active:
    mkdir BUILD && cd BUILD
    cmake ../ -DLIBOMP_OMPT_SUPPORT=on
    make

## Make only minimal set of mandatory callbacks active:
    mkdir BUILD && cd BUILD
    cmake ../ -DLIBOMP_OMPT_SUPPORT=on -DLIBOMP_OMPT_BLAME=off -DLIBOMP_OMPT_TRACE=off
    make

## Build & execute tests
The test tools of LLVM are needed, configure how to find them (these are built during LLVM build, but not installed):

    cmake . -DLIBOMP_LLVM_LIT_EXECUTABLE=/path/to/lit -DFILECHECK_EXECUTABLE=/path/to/FileCheck
    make check-libomp