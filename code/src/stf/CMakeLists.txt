add_library(stf INTERFACE
	"include/interface/stf/alg/containment.hpp"
	"include/interface/stf/alg/intersection.hpp"
	"include/interface/stf/cam/frustum.hpp"
	"include/interface/stf/cam/scamera.hpp"
	"include/interface/stf/enums.hpp"
	"include/interface/stf/geom/aabb.hpp"
	"include/interface/stf/geom/hyperplane.hpp"
	"include/interface/stf/geom/polygon.hpp"
	"include/interface/stf/geom/polyline.hpp"
	"include/interface/stf/geom/segment.hpp"
	"include/interface/stf/gfx/color.hpp"
	"include/interface/stf/gfx/gradient.hpp"
	"include/interface/stf/math/constants.hpp"
	"include/interface/stf/math/crange.hpp"
	"include/interface/stf/math/interpolation.hpp"
	"include/interface/stf/math/matrix.hpp"
	"include/interface/stf/math/range.hpp"
	"include/interface/stf/math/raw.hpp"
	"include/interface/stf/math/scalar.hpp"
	"include/interface/stf/math/spherical.hpp"
	"include/interface/stf/math/transform.hpp"
	"include/interface/stf/math/vector.hpp"
	"include/interface/stf/stf.hpp"
)

target_include_directories(stf INTERFACE "include/interface")

# TODO add the public headers inside the include directory to our install