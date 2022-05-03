#ifndef __kb_math_StrongWolfeSearch_hpp__
#define __kb_math_StrongWolfeSearch_hpp__

#include <sstream>

#include "CentralDifference.hpp"
#include "ArmijoLineSearch.hpp"

namespace kb{
    namespace math{
    template<typename T>
    /**
     * @class StrongWolfeSearch
     * @details Inexact line search method for adaptive step size backtracking. Step size has reached a good value when condition,
      \f[
          0 < C_1 < C_2 < 1 \\
          g = \dot{f} \\
          f(\mathbf{x}+a \cdot \mathbf{d}) \leq  f(\mathbf{x}) + C_1 \cdot a \cdot \langle \mathbf{g(x)},\mathbf{g(x)} \rangle
      \f]
      and
      \f[
          | \langle g(\mathbf{x}+a \cdot \mathbf{d}), \mathbf{g(x)} \rangle | \leq C_2 \cdot | \langle \mathbf{g(x)},\mathbf{g(x)} \rangle |
      \f]
      is satisified. (a) is the step size, (g(x)) is the gradient/direction and (f) is the function.
      C_1 and C_2 are the coefficients. C_1 is usually much smaller than C_2.
     * @author Kevin Baur
     * @date 2021
     */
    class StrongWolfeSearch : public ArmijoLineSearch<T>
    {
    public:
      /**
       * @brief Construct a new Strong Wolfe Search object
       * 
       */
      StrongWolfeSearch();
      /**
       * @brief Construct a new Strong Wolfe Search object
       * 
       * @param p_C1 
       * @param p_C2 
       * @param p_minStep 
       * @param p_maxStep 
       * @param p_iterations 
       */
      StrongWolfeSearch(const T p_C1,const T p_C2,
        const T p_minStep,
        const T p_maxStep,
        const std::uint64_t p_iterations);
      /**
       * @brief Set the Constant object
       * 
       * @param p_C1 
       * @param p_C2 
       */
      void SetConstant(T p_C1, T p_C2);
      /**
       * @brief 
       * 
       * @param p_parameter 
       * @param p_newParameter 
       * @param p_stepSize 
       * @param p_sum 
       * @return true 
       * @return false 
       */
      virtual bool CheckCondition(const std::vector<T> & p_parameter, const std::vector<T> & p_newParameter,T p_stepSize,T p_sum);
    protected:
      T m_C2{1.1};
    };
    }
}

#include "StrongWolfeSearch.cpp"

#endif