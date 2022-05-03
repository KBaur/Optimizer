#ifndef __kb_math_StepSize_hpp__
#define __kb_math_StepSize_hpp__
#include <numeric>
#include <functional>
#include <stdexcept>
#include <memory>

#include "CentralDifference.hpp"

namespace kb{
    namespace math{
        template<typename T>
        /**
         * @class StepSize
         * @details Abstract class for step size calculation
         * @author Kevin Baur
         * @date 2021 
         */
        class StepSize
        {
        public:
            /**
             * @brief Set the Gradient Function object
             * 
             * @param p_gradientFunction 
             */
            virtual void SetGradientFunction(std::shared_ptr<CentralDifference<T>> p_gradientFunction) = 0;
            /**
             * @brief Set the Current Parameter object
             * 
             * @param p_currentParameter 
             */
            virtual void SetCurrentParameter(const std::vector<T> & p_currentParameter) = 0;
            /**
             * @brief Set the Current Step Size object
             * 
             * @param p_currentStepSize 
             */
            virtual void SetCurrentStepSize(const T p_currentStepSize) = 0;
            /**
             * @brief Get the Step Size object
             * 
             * @return std::vector<T> 
             */
            virtual T GetStepSize() = 0;
        protected:
            T m_stepSize;
        };
    }
}

#include "StepSize.cpp"

#endif