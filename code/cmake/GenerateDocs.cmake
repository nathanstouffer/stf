if (BUILD_DOCS)
	find_package(Doxygen)

	# output-related settings
	set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/docs/generated")
	set(DOXYGEN_GENERATE_HTML YES)
	set(DOXYGEN_GENERATE_MAN YES)
	set(DOXYGEN_GENERATE_TREEVIEW YES)
	set(DOXYGEN_MARKDOWN_SUPPORT YES)
	set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/readme.md")
	set(DOXYGEN_QUIET YES)

	set(DOXYGEN_AUTOLINK_SUPPORT YES)
	set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
	set(DOXYGEN_WARN_AS_ERROR YES)

	# graph-related settings
	set(DOXYGEN_HAVE_DOT YES)
	set(DOXYGEN_COLLABORATION_GRAPH YES)
	set(DOXYGEN_ENABLE_PREPROCESSING YES)
	set(DOXYGEN_SEARCH_INCLUDES YES)
	set(DOXYGEN_INCLUDE_GRAPH YES)
	set(DOXYGEN_INCLUDED_BY_GRAPH NO)
	set(DOXYGEN_DIRECTORY_GRAPH YES)
	set(DOXYGEN_CLASS_GRAPH YES)
	set(DOXYGEN_UML_LOOK YES)
	set(DOXYGEN_DOT_UML_DETAILS YES)
	set(DOXYGEN_DOT_WRAP_THRESHOLD 100)
	set(DOXYGEN_CALL_GRAPH YES)

	if (Doxygen_FOUND STREQUAL TRUE)
		doxygen_add_docs(docs
			"${CMAKE_SOURCE_DIR}/code/src"
			"${CMAKE_SOURCE_DIR}/readme.md"
			# ALL # enable this when you want to add the docs target to all
			COMMENT "Generating documentation"
		)
	else()
		message(WARNING "Failed to find Doxygen -- skipped docs target")
	endif()
endif()