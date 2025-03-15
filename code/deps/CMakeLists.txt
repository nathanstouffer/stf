include(FetchContent)
if (BUILD_TESTS)
    # declare and populate googletest dependency
    FetchContent_Declare(
        googletest 
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

if (BUILD_DOCS)
    # declare and populate googletest dependency
    FetchContent_Declare(
        doxygen-awesome-css
        GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
        GIT_TAG v2.3.4
    )
    FetchContent_MakeAvailable(doxygen-awesome-css)
    FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR EVALUATED_SOURCE_DIR)
    set(DOXYGEN_AWESOME_SOURCE_DIR ${EVALUATED_SOURCE_DIR} PARENT_SCOPE)
endif()