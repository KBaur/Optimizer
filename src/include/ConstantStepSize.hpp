#ifndef __kb_math_ConstantStepSize_hpp__
#define __kb_math_ConstantStepSize_hpp__
#include "StepSize.hpp"

namespace kb{
    namespace math{
        template<typename T>
        /**
         * @class ConstantStepSize
         * @details Gives a constant step size back, which is used by the gradient descent optimizer.
         * @author Kevin Baur
         * @date 2021
         */
        class ConstantStepSize : public StepSize<T>
        {
        public:
            /**
             * @brief Construct a new Constant Step Size object
             * 
             * @param p_stepSize 
             * @param p_numberOfVariables 
             */
            ConstantStepSize(const T & p_stepSize);
            /**
             * @brief Set the Current Parameter object
             * 
             * @param p_currentParameter 
             */
            virtual void SetCurrentParameter(const std::vector<T> & p_currentParameter)
            {}
            /**
             * @brief Set the Current Step Size object
             * 
             * @param p_currentStepSize 
             */
            virtual void SetCurrentStepSize(const T p_currentStepSize)
            {}
            /**
             * @brief Set the Gradient Function object
             * 
             * @param p_gradientFunction 
             */
            virtual void SetGradientFunction(std::shared_ptr<CentralDifference<T>> p_gradientFunction)
            {}
            /**
             * @brief Get the Step Size object
             * 
             * @return std::vector<T> 
             */
            virtual T GetStepSize();
        };
    }
}

#include "ConstantStepSize.cpp"

#endif