# run program
execute_process(
    COMMAND ${test_cmd} ${input_file} ${output_file} ${run_mode}
    RESULT_VARIABLE run_failed
)

if (NOT run_failed)
    # compare output and answer
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E compare_files ${output_file} ${answer_file}
        RESULT_VARIABLE test_not_successful
    )

    if (test_not_successful)
        message(SEND_ERROR "wrong answer")
    endif (test_not_successful)
else (NOT run_failed)
    message(SEND_ERROR "runtime error")
endif (NOT run_failed)
