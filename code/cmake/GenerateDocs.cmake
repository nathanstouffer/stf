if(BUILD_DOCS)
    find_package(Doxygen)

    # console settings
    set(DOXYGEN_WARN_AS_ERROR YES)
    set(DOXYGEN_QUIET YES)

    # configuration
    set(DOXYGEN_PROJECT_NUMBER "0.0.0-dev")
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/docs/generated")
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_MARKDOWN_SUPPORT YES)

    # style settings
    set(DOXYGEN_HTML_EXTRA_STYLESHEET "${DOXYGEN_AWESOME_SOURCE_DIR}/doxygen-awesome.css")
    set(DOXYGEN_HTML_COLORSTYLE LIGHT)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/readme.md")
    set(DOXYGEN_GENERATE_TREEVIEW YES) # required by doxygen-awesome-css
    set(DOXYGEN_DISABLE_INDEX NO) # required by doxygen-awesome-css
    set(DOXYGEN_FULL_SIDEBAR NO)
    set(DOXYGEN_AUTOLINK_SUPPORT YES)
    set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

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

    if(Doxygen_FOUND STREQUAL TRUE)
        doxygen_add_docs(docs
            "${CMAKE_SOURCE_DIR}/code/src"
            "${CMAKE_SOURCE_DIR}/readme.md"
            "${CMAKE_SOURCE_DIR}/changelog.md"
            "${CMAKE_SOURCE_DIR}/docs/architecture.md"
            "${CMAKE_SOURCE_DIR}/docs/contributing.md"
            "${CMAKE_SOURCE_DIR}/docs/support.md"
            "${CMAKE_SOURCE_DIR}/docs/todo.md"

            # ALL # enable this when you want to add the docs target to all
            COMMENT "Generating documentation"
        )
    else()
        message(WARNING "Failed to find Doxygen -- skipped docs target")
    endif()
endif()