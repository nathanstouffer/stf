# set up the coverage config -- this is clang only
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI)
    if (IS_MULTI_CONFIG)
        if (NOT "Coverage" IN_LIST CMAKE_CONFIGURATION_TYPES)
            list(APPEND CMAKE_CONFIGURATION_TYPES Coverage)
        endif()
    else()
        set(KNOWN_BUILD_TYPES Debug Release RelWithDebInfo Coverage)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${KNOWN_BUILD_TYPES})
        if (NOT CMAKE_BUILD_TYPE IN_LIST KNOWN_BUILD_TYPES)
            message(FATAL_ERROR "Unkown build type: ${CMAKE_BUILD_TYPE}")
        endif()
    endif()

    set(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} -fprofile-instr-generate -fcoverage-mapping -fno-inline -fno-inline-small-functions -fno-default-inline -fno-elide-constructors")
    set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-instr-generate -fcoverage-mapping -fno-inline -fno-inline-small-functions -fno-default-inline -fno-elide-constructors")
    set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
    set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
endif()
