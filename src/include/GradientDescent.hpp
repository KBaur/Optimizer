#ifndef __kb_math_GradientDescent_hpp__
#define __kb_math_GradientDescent_hpp__

#include <numeric>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <iomanip>
#include <functional>
#include <execution>

#include "StepSize.hpp"
#include "CentralDifference.hpp"
#include "CentralDifference.cpp"

namespace kb{
    namespace math{
        template<typename T>
        /**
         * @struct Result
         * @details Gives back the results of the optimization process.
         * Number of the iteration, is the convergence criterion fullfilled?
         * The final function value (f(x)) and the current member variables (x). 
         * @author Kevin Baur
         * @date 2021
         */
        struct Result
        {
            std::uint64_t m_iterations;
            bool m_converged;
            T m_result;
            std::vector<T> m_memberVariables;
        };

        template<typename T>
        /**
         * @class GradientDescent
         * @details Numerical optimizer for gradient descent. Finds the local minimum of a certain function.
         * To do this, the state parameters are iteratively increased or decreased in order to find the minimum with the following term:
          \f[
              \mathbf{x}_{i+1} = \mathbf{x}_i - \alpha \nabla f(\mathbf{x}_i) 
          \f] 
          Where \f[ \alpha \f] is the step size, defined by a constant or a inexact line search method.
          \f[ \nabla f \f] is the search direction.
         * @author Kevin Baur
         * @date 2021
         */
        class GradientDescent
        {
        public:
        /**
         * @brief Set the Max Iterations object
         * 
         * @param p_maxIterations 
         */
            void SetMaxIterations(std::uint64_t p_maxIterations);
            /**
             * @brief Set the Function object
             * 
             * @param p_function 
             */
            void SetFunction(const std::function<T (std::vector<T>)> & p_function);
            /**
             * @brief Set the Minimum Gradient Length object
             * 
             * @param p_minGradientLength 
             */
            void SetMinimumGradientLength(const T & p_minGradientLength);
            /**
             * @brief Set the Minimum Step Length object
             * 
             * @param p_minStepLength 
             */
            void SetMinimumStepLength(const T & p_minStepLength);
            /**
             * @brief Set the Step Size Function object
             * 
             * @param p_stepSizeFunction 
             */
            void SetStepSizeFunction(std::shared_ptr<StepSize<T>> p_stepSizeFunction);
            /**
             * @brief 
             * 
             * @param p_initialState 
             */
            void Minimize(const std::vector<T> & p_initialState);
            /**
             * @brief Get the Result object
             * 
             * @return Result<T> 
             */
            Result<T> GetResult();
        private:
            /**
             * @brief 
             * 
             * @param p_vector 
             * @return T 
             */
            T Normalize(const std::vector<T> & p_vector);
            T m_minGradientLength{1e-6};
            T m_minStepLength{1e-3};
            std::uint64_t m_maxIterations{1000};
            std::shared_ptr<StepSize<T>> m_stepSizeFunction;
            std::shared_ptr<CentralDifference<T>> m_centralDifference;
            std::function<T (std::vector<T>)> m_function;
            Result<T> m_result;
        };
    }
}

#include "GradientDescent.cpp"

#endif