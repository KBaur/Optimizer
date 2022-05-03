#ifndef __kb_math_ArmijoLineSearch_hpp__
#define __kb_math_ArmijoLineSearch_hpp__

#include <sstream>

#include "StepSize.hpp"
#include "CentralDifference.hpp"

namespace kb{
    namespace math{
    template<typename T>
    /**
     * @class ArmijoLineSearch
     * @details Inexact line search method for adaptive step size backtracking. Step size has reached a good value when condition,
    \f[
        g = \dot{f} \\
        f(\mathbf{x}+a \cdot \mathbf{d}) \leq  f(\mathbf{x}) + C_1 \cdot a \cdot \langle \mathbf{g(x)},\mathbf{g(x)} \rangle
    \f]
    is satisified. (a) is the step size, (g(x)) is the gradient/direction and (f) is the function.
    @author Kevin Baur
    @date 2021
     */
    class ArmijoLineSearch : public StepSize<T>
    {
    public:
      /**
       * @brief Construct a new Armijo Line Search object 
       */
      ArmijoLineSearch();
      /**
       * @brief Construct a new Armijo Line Search object
       * 
       * @param p_C1 
       * @param p_minStep 
       * @param p_maxStep 
       * @param p_iterations 
       */
      ArmijoLineSearch(const T p_C1,
        const T p_minStep,
        const T p_maxStep,
        const std::uint64_t p_iterations);
      /**
       * @brief Set the Constant object
       * 
       * @param p_C1 
       */
      void SetConstant(T p_C1);
      /**
       * @brief Set the Step Length object
       * 
       * @param p_minStep 
       * @param p_maxStep 
       */
      void SetStepLength(T p_minStep,const T p_maxStep);
      /**
       * @brief Set the Learning Rate object
       * 
       * @param p_learningRate 
       */
      void SetLearningRate(T p_learningRate);
      /**
       * @brief Set the Max Iterations object
       * 
       * @param p_maxIterations 
       */
      void SetMaxIterations(std::uint64_t p_maxIterations);
      /**
       * @brief Set the Current Parameter object
       * 
       * @param p_currentParameter 
       */
      void SetCurrentParameter(const std::vector<T> & p_currentParameter);
      /**
       * @brief Set the Gradient Function object
       * 
       * @param p_gradientFunction 
       */
      void SetGradientFunction(std::shared_ptr<CentralDifference<T>> p_gradientFunction);
      /**
       * @brief Set the Current Step Size object
       * 
       * @param p_currentStepSize 
       */
      void SetCurrentStepSize(T p_currentStepSize);
      /**
       * @brief Get the Step Size object
       * 
       * @return std::vector<T> 
       */
      virtual T GetStepSize();
      /**
       * @brief 
       * 
       * @param p_functionValue 
       * @param p_functionValueNew 
       * @param p_stepSize 
       * @param p_sum 
       * @return true 
       * @return false 
       */
      virtual bool CheckCondition(const std::vector<T> & p_parameter, const std::vector<T> & p_newParameter,T p_stepSize,T p_sum);
    protected:
      T m_C1{1e-4};
      T m_currentStepSize{0.5};
      T m_minStep{1e-6};
      T m_maxStep{1};
      T m_learningRate{0.9};
      std::uint64_t m_maxIterations{500};
      std::vector<T> m_currentParameter;
      std::shared_ptr<CentralDifference<T>> m_gradientFunction;
    };
    }
}

#include "ArmijoLineSearch.cpp"

#endif