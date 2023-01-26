set(TARGET_FILES
  色覚シミュレーションKR.anm
)

add_custom_target(script ALL DEPENDS ${TARGET_FILES})

foreach(target_file IN LISTS TARGET_FILES)
  add_custom_command(OUTPUT ${target_file}
    COMMAND
      ${CMAKE_COMMAND}
      -DSCRIPT_VERSION="${PROJECT_VERSION}"
      -DINPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/${target_file}.in"
      -DOUTPUT_FILE="${target_file}"
      -P ${CMAKE_CURRENT_SOURCE_DIR}/script.cmake
    DEPENDS
      ${target_file}.in
  )
  list(APPEND SCRIPT_OUTPUT_FILES ${CMAKE_CURRENT_BINARY_DIR}/${target_file})
endforeach()

set(SCRIPT_OUTPUT_FILES ${SCRIPT_OUTPUT_FILES} PARENT_SCOPE)
