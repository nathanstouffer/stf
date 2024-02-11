#pragma once

#include "stf/cam/scamera.hpp"

namespace stf::cam
{

    // TODO write this class once we have a plane and aabb class
    template<typename T>
    struct frustum final
    {


        // fully qualified frustum constructor
        //frustum()

        // convenience constructors
        //frustum(scamera<T> const& camera)

        void reset(scamera<T> const& camera)
        {
            // TODO write this method
        }

    private:

        // TODO probably make members private?

    };

} // stf::cam