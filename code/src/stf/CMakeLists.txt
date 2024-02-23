add_library(stf INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/containment.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/alg/intersection.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/cam/frustum.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/cam/scamera.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/enums.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/aabb.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/hyperplane.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/polygon.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/polyline.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/geom/segment.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/gfx/color.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/gfx/gradient.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/constants.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/crange.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/interpolation.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/matrix.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/range.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/raw.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/scalar.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/spherical.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/transform.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/math/vector.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/interface/stf/stf.hpp"
)

target_include_directories(stf INTERFACE "include/interface")

# TODO add the public headers inside the include directory to our install