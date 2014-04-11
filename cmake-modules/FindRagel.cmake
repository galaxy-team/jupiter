find_program(RAGEL "ragel")

function(ragel_gen in_rl)
    set(output_path "${CMAKE_CURRENT_BINARY_DIR}/${in_rl}.cc")
    set(input_path "${CMAKE_CURRENT_SOURCE_DIR}/${in_rl}.rl")

    add_custom_command(
        OUTPUT ${output_path}
        COMMAND ${RAGEL} -G2 -o ${output_path} ${CMAKE_CURRENT_SOURCE_DIR}/${in_rl}.rl -I ${CMAKE_CURRENT_SOURCE_DIR} ${ARGN}
        DEPENDS ${input_path}
    )

    string(REGEX REPLACE "/" "_" target_name "${in_rl}")
    add_custom_target(ragel${target_name} DEPENDS ${output_path})
endfunction(ragel_gen)

if(RAGEL)
    message(STATUS "ragel found at: ${RAGEL}")
else(RAGEL)
    message(FATAL_ERROR "ragel not found")
endif(RAGEL)
