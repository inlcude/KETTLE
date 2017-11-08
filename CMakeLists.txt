cmake_minimum_required(VERSION 3.10)
aux_source_directory(../Common common_src)
aux_source_directory(../Extern/boost/boost boost_src)
set(boost_libraries boost_atomic-vc140-mt-1_65_1
                    boost_chrono-vc140-mt-1_65_1
					boost_container-vc140-mt-1_65_1
					boost_context-vc140-mt-1_65_1
					boost_coroutine-vc140-mt-1_65_1
					boost_date_time-vc140-mt-1_65_1
					boost_fiber-vc140-mt-1_65_1
					boost_filesystem-vc140-mt-1_65_1
					boost_graph-vc140-mt-1_65_1
					boost_iostreams-vc140-mt-1_65_1
					boost_locale-vc140-mt-1_65_1
					boost_log_setup-vc140-mt-1_65_1
					boost_log-vc140-mt-1_65_1
					boost_math_c99f-vc140-mt-1_65_1
					boost_math_c99l-vc140-mt-1_65_1
					boost_math_c99-vc140-mt-1_65_1
					boost_math_tr1f-vc140-mt-1_65_1
					boost_math_tr1l-vc140-mt-1_65_1
					boost_math_tr1-vc140-mt-1_65_1
					boost_numpy3-vc140-mt-1_65_1
					boost_prg_exec_monitor-vc140-mt-1_65_1
					boost_program_options-vc140-mt-1_65_1
					boost_python3-vc140-mt-1_65_1
					boost_random-vc140-mt-1_65_1
					boost_regex-vc140-mt-1_65_1
					boost_serialization-vc140-mt-1_65_1
					boost_signals-vc140-mt-1_65_1
					boost_stacktrace_noop-vc140-mt-1_65_1
					boost_stacktrace_windbg_cached-vc140-mt-1_65_1
					boost_stacktrace_windbg-vc140-mt-1_65_1
					boost_system-vc140-mt-1_65_1
					boost_thread-vc140-mt-1_65_1
					boost_timer-vc140-mt-1_65_1
					boost_type_erasure-vc140-mt-1_65_1
					boost_unit_test_framework-vc140-mt-1_65_1
					boost_wave-vc140-mt-1_65_1
					boost_wserialization-vc140-mt-1_65_1)
add_subdirectory(Server)