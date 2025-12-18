#pragma once

#include <vector>

#include "stf/gfx/color.hpp"
#include "stf/math/constants.hpp"

/**
 * @file gradient.hpp
 * @brief A file containing a gradient class along with associated functions
 */

namespace stf::gfx
{

    /**
     * @brief A class that represents a gradient
     * @todo Possibly template the gradient class
     */
    class gradient final
    {
    public:

        /**
         * @brief Type alias for the input
         */
        using time_t = float;

        /**
         * @brief Struct to represent an interpolation anchor
         */
        struct stop
        {

            /**
             * @brief The time value associated with the anchor
             */
            time_t x;

            /**
             * @brief The color associated with the anchor
             */
            rgba color;
        };

        /**
         * @brief Construct a gradient from a vector of stops
         * @param [in] stops
         * @param [in] period The period used when sampling the color -- 0 signifies that there is no period
         */
        gradient(std::vector<stop> const& stops, float period = math::constants<time_t>::zero) : m_stops(stops), m_period(period) {}

        /**
         * @brief Sample a color at a specified time value @p x
         * @param [in] x
         * @return The sampled @ref rgba value
         */
        rgba sample(time_t const x) const
        {
            // account for edge cases
            if (m_stops.empty()) { return rgba::from_hex_argb(0xFF000000); }
            else if (m_stops.size() == 1) { return m_stops.front().color; }

            stop const& first = m_stops.front();
            stop const& last = m_stops.back();

            if (m_period != math::constants<time_t>::zero)
            {
                if (x < first.x || x > last.x)      // check if x is between last and first
                {
                    // compute endpoints that we are lerping between
                    time_t a = (x >= last.x) ? last.x : last.x - m_period;
                    time_t b = (x <= first.x) ? first.x : first.x + m_period;

                    time_t t = (x - a) / (b - a);
                    return lerp(last.color, first.color, t);
                }
                else
                {
                    // compute the two points on either side
                    size_t i = 0;
                    while (!(m_stops[i].x <= x && x <= m_stops[i + 1].x)) { ++i; }

                    stop const& left = m_stops[i];
                    stop const& right = m_stops[i + 1];

                    time_t t = (x - left.x) / (right.x - left.x);
                    return lerp(left.color, right.color, t);
                }
            }
            else
            {
                if (x <= first.x) { return first.color; }
                else if (x >= last.x) { return last.color; }
                else
                {
                    // compute the two points on either side
                    size_t i = 0;
                    while (!(m_stops[i].x <= x && x <= m_stops[i + 1].x)) { ++i; }

                    stop const& left = m_stops[i];
                    stop const& right = m_stops[i + 1];

                    time_t t = (x - left.x) / (right.x - left.x);
                    return lerp(left.color, right.color, t);
                }
            }
        }

    private:

        std::vector<stop> m_stops;
        float m_period;

    };

}