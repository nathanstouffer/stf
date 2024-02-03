#pragma once

#include "stf/cam/scamera.hpp"

namespace stf::cam
{

    // TODO (stouff) write this class once we have a plane and aabb class
    template<typename T>
    struct frustum
    {


        // fully qualified frustum constructor
        //frustum()

        // convenience constructors
        //frustum(scamera<T> const& camera)

        void reset(scamera<T> const& camera)
        {
            // TODO (stouff) write this method
        }

    private:

        // TODO (stouff) probably make members private?

    };

} // stf::cam