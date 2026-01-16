set(STF_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/clipping.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/containment.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/hull.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/intersect.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/intersects.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/statistics.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/tessellation.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/triangulation.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/cam/frustum.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/cam/scamera.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/ds/indexed_list.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/enums.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/aabb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/holygon.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/hyperplane.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/obb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/polygon.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/polyline.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/ray.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/segment.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/hypersphere.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/gfx/color.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/gfx/gradient.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/basis.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/constants.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/cinterval.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/interpolation.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/matrix.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/interval.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/raw.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/scalar.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/spherical.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/transform.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/vector.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/platform.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/spatial/interval_tree.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/stf.hpp"
)

add_library(stf INTERFACE ${STF_FILES})

target_compile_definitions(stf INTERFACE
    STF_ENABLED=1
    STF_DISABLED=0
)

option(STF_SUPPRESS_ANONYMOUS_STRUCT_WARNINGS "Suppress warnings related to anonymous structs" TRUE)

if(STF_SUPPRESS_ANONYMOUS_STRUCT_WARNINGS)
    target_compile_definitions(stf INTERFACE STF_SUPPRESS_ANONYMOUS_STRUCT_WARNINGS=1)
else()
    target_compile_definitions(stf INTERFACE STF_SUPPRESS_ANONYMOUS_STRUCT_WARNINGS=0)
endif()

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${STF_FILES})

target_include_directories(stf INTERFACE "include/interface")

# TODO add the public headers inside the include directory to our install