#ifndef  __OMPT_EVENT_SPECIFIC_H__
#define  __OMPT_EVENT_SPECIFIC_H__

/******************************************************************************
 * File: ompt-event-specific.h
 *
 * Description:
 *
 *   specify which of the OMPT events are implemented by this runtime system
 *   and the level of their implementation by a runtime system.
 *****************************************************************************/

#define _ompt_tokenpaste_helper(x,y)        x ## y
#define _ompt_tokenpaste(x,y)               _ompt_tokenpaste_helper(x,y)
#define ompt_event_implementation_status(e) _ompt_tokenpaste(e,_implemented)


/*----------------------------------------------------------------------------
 | Specify whether an event may occur or not, and whether event callbacks
 | never, sometimes, or always occur.
 |
 | The values for these constants are defined in section 6.1.2 of
 | the OMPT TR. They are exposed to tools through ompt_set_callback.
 +--------------------------------------------------------------------------*/

#define ompt_event_NEVER             ompt_set_result_event_never_occurs
#define ompt_event_UNIMPLEMENTED     ompt_set_result_event_may_occur_no_callback
#define ompt_event_MAY_CONVENIENT    ompt_set_result_event_may_occur_callback_some
#define ompt_event_MAY_ALWAYS        ompt_set_result_event_may_occur_callback_always

#if OMPT_TRACE
#define ompt_event_MAY_ALWAYS_TRACE   ompt_event_MAY_ALWAYS
#else
#define ompt_event_MAY_ALWAYS_TRACE   ompt_event_UNIMPLEMENTED
#endif

#if OMPT_BLAME
#define ompt_event_MAY_ALWAYS_BLAME   ompt_event_MAY_ALWAYS
#else
#define ompt_event_MAY_ALWAYS_BLAME   ompt_event_UNIMPLEMENTED
#endif

/*----------------------------------------------------------------------------
 | Mandatory Events
 +--------------------------------------------------------------------------*/

#define ompt_callback_parallel_begin_implemented        ompt_event_MAY_ALWAYS
#define ompt_callback_parallel_end_implemented          ompt_event_MAY_ALWAYS

#define ompt_callback_task_create_implemented           ompt_event_MAY_ALWAYS
#define ompt_callback_task_schedule_implemented         ompt_event_MAY_ALWAYS

#define ompt_callback_thread_begin_implemented          ompt_event_MAY_ALWAYS
#define ompt_callback_thread_end_implemented            ompt_event_MAY_ALWAYS

#define ompt_event_control_implemented                  ompt_event_MAY_ALWAYS

#define ompt_event_runtime_shutdown_implemented         ompt_event_MAY_ALWAYS

#define ompt_callback_implicit_task_implemented         ompt_event_MAY_ALWAYS


/*----------------------------------------------------------------------------
 | Optional Events (blame shifting)
 +--------------------------------------------------------------------------*/

#define ompt_callback_idle_implemented                  ompt_event_MAY_ALWAYS_BLAME

#define ompt_callback_sync_region_wait_implemented      ompt_event_MAY_ALWAYS_BLAME

#define ompt_event_wait_taskwait_begin_implemented      ompt_event_UNIMPLEMENTED
#define ompt_event_wait_taskwait_end_implemented        ompt_event_UNIMPLEMENTED

#define ompt_event_wait_taskgroup_begin_implemented     ompt_event_UNIMPLEMENTED
#define ompt_event_wait_taskgroup_end_implemented       ompt_event_UNIMPLEMENTED

#define ompt_callback_mutex_released_implemented        ompt_event_MAY_ALWAYS_BLAME


/*----------------------------------------------------------------------------
 | Optional Events (synchronous events)
 +--------------------------------------------------------------------------*/

#define ompt_event_initial_task_begin_implemented       ompt_event_UNIMPLEMENTED
#define ompt_event_initial_task_end_implemented         ompt_event_UNIMPLEMENTED

#define ompt_callback_work_implemented                  ompt_event_MAY_ALWAYS_TRACE

#define ompt_event_sections_begin_implemented           ompt_event_UNIMPLEMENTED
#define ompt_event_sections_end_implemented             ompt_event_UNIMPLEMENTED

#define ompt_event_workshare_begin_implemented          ompt_event_UNIMPLEMENTED
#define ompt_event_workshare_end_implemented            ompt_event_UNIMPLEMENTED

#define ompt_callback_master_implemented                ompt_event_MAY_ALWAYS_TRACE

#define ompt_callback_sync_region_implemented           ompt_event_MAY_ALWAYS_BLAME

#define ompt_callback_mutex_acquire_implemented         ompt_event_MAY_ALWAYS_TRACE
#define ompt_callback_mutex_acquired_implemented        ompt_event_MAY_ALWAYS_TRACE
#define ompt_callback_nest_lock_implemented             ompt_event_MAY_ALWAYS_TRACE

#define ompt_callback_lock_init_implemented             ompt_event_MAY_ALWAYS_TRACE
#define ompt_callback_lock_destroy_implemented          ompt_event_MAY_ALWAYS_TRACE

#define ompt_callback_flush_implemented                 ompt_event_MAY_ALWAYS_TRACE

// Start of PVLangdal extensions

#define pvl_callback_task_create_begin_implemented     ompt_event_MAY_ALWAYS

// End of PVLangdal extensions

#if OMP_40_ENABLED
# define ompt_callback_task_dependences_implemented      ompt_event_MAY_ALWAYS_TRACE
# define ompt_callback_task_dependence_implemented       ompt_event_MAY_ALWAYS_TRACE
#else
# define ompt_callback_task_dependences_implemented      ompt_event_UNIMPLEMENTED
# define ompt_callback_task_dependence_implemented       ompt_event_UNIMPLEMENTED
#endif /* OMP_40_ENABLED */

#endif
