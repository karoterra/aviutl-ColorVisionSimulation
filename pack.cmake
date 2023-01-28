# -DMANIFEST_FILE
# -DOUTPUT_FILE

if(NOT EXISTS "${MANIFEST_FILE}")
  message(FATAL_ERROR "Cannot find install manifest: ${MANIFEST_FILE}")
endif()

file(READ "${MANIFEST_FILE}" files)
string(REGEX REPLACE "\n" ";" files "${files}")
exec_program(7z ARGS a ${OUTPUT_FILE} ${files})
