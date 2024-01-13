function(bomberman_enable_doxygen_comments)
	cmake_parse_arguments(PROJ "" "NAME" "INPUTS;" ${ARGN})
	set(INPUT_DIRS ${PROJ_INPUTS})
	string(REPLACE ";" " " INPUT_DIRS "${INPUT_DIRS}")

	configure_file(
			Doxyfile.in
			Doxyfile @ONLY
			NEWLINE_STYLE LF
			)

	add_custom_target(documentation
	                  COMMAND doxygen Doxyfile
	                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	                  COMMENT "Generating Doxygen documentation")
endfunction()