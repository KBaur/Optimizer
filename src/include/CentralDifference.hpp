#ifndef __kb_math_CentralDifference_hpp__
#define __kb_math_CentralDifference_hpp__

#include <numeric>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

namespace kb{
    namespace math{
        template<typename T>
        /**
         * @class CentralDifference
         * @details
         * @author Kevin Baur
         * @date 2021
         */
        class CentralDifference
        {
        public:
            /**
             * @brief Construct a new Central Difference object
             * 
             * @param p_function 
             */
            CentralDifference(const std::function<T (std::vector<T>)> & p_function);
            /**
             * @brief Calculate the derivate of the given state
             * 
             * @param p_arguments 
             * @return std::vector<T> 
             */
            std::vector<T> Calculate(const std::vector<T> & p_arguments);
            /**
             * @brief Get the Function object
             * 
             * @return std::function<T (std::vector<T>)> 
             */
            std::function<T (std::vector<T>)> GetFunction();
        private:
            std::function<T (std::vector<T>)> m_function; 
            T m_h{1e-6};
        };
    }
}

#include "CentralDifference.cpp"

#endif