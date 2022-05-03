#ifndef __kb_math_StrongWolfeSearch_cpp__
#define __kb_math_StrongWolfeSearch_cpp__

#include "StrongWolfeSearch.hpp"

namespace kb{
    namespace math{
        template<typename T>
        StrongWolfeSearch<T>::StrongWolfeSearch()
        : ArmijoLineSearch<T>(1e-4,1e-6, 1.0, 1000)
        {
            m_C2 = 1.1;
        }
        template<typename T>
        StrongWolfeSearch<T>::StrongWolfeSearch(const T p_C1,const T p_C2,const T p_minStep,const T p_maxStep,const std::uint64_t p_iterations) 
        : ArmijoLineSearch<T>(p_C1,p_minStep,p_maxStep,p_iterations)
        {
            m_C2 = p_C2;
        }
        template<typename T>
        void StrongWolfeSearch<T>::SetConstant(T p_C1, T p_C2)
        {
            SetConstant(p_C1);
            m_C2 = p_C2;
        }
        template<typename T>
        bool StrongWolfeSearch<T>::CheckCondition(const std::vector<T> & p_parameter, const std::vector<T> & p_newParameter,T p_stepSize,T p_sum)
        {
            auto functionToEvaluate =  this->m_gradientFunction->GetFunction();
            T functionValue = functionToEvaluate(p_parameter);
            T functionValueNew =  functionToEvaluate(p_newParameter);
            bool armijoCondition = (functionValueNew <= functionValue - this->m_C1 * p_stepSize * p_sum);
            std::vector<T> gradientNew = this->m_gradientFunction->Calculate(p_newParameter);
            std::vector<T> gradient = this->m_gradientFunction->Calculate(p_parameter);
            double sum{0};
            #pragma omp parallel for
            for(int i = 0; i<gradientNew.size();++i)
            {
                sum += (gradient.at(i)*gradientNew.at(i));
            }
            bool strongWolfeCondition = (std::abs(sum)<=m_C2*std::abs(p_sum));
            return armijoCondition && strongWolfeCondition;
        }
    }
}
#endif