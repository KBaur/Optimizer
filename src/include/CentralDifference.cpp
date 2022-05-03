#ifndef __kb_math_CentralDifference_cpp__
#define __kb_math_CentralDifference_cpp__
#include "CentralDifference.hpp"

namespace kb{
    namespace math{
        template<typename T>
        CentralDifference<T>::CentralDifference(const std::function<T (std::vector<T>)> & p_function)
        {
            m_h = std::sqrt(std::numeric_limits<double>::epsilon());
            m_function = p_function;
        }

        
        template<typename T>
        std::function<T (std::vector<T>)> CentralDifference<T>::GetFunction()
        {
            return m_function;
        }

        template<typename T>
        std::vector<T> CentralDifference<T>::Calculate(const std::vector<T> & p_arguments)
        {
            std::vector<T> gradients(p_arguments.size());
            std::vector<T> temporaryArgumentsAdd(p_arguments.size());
            std::vector<T> temporaryArgumentsSub(p_arguments.size());
            #pragma omp parallel for
            for(int i = 0 ; i<p_arguments.size();++i)
            {
                std::copy(p_arguments.begin(),p_arguments.end(),temporaryArgumentsAdd.begin());
                std::copy(p_arguments.begin(),p_arguments.end(),temporaryArgumentsSub.begin());
                temporaryArgumentsAdd.at(i)+=m_h;
                temporaryArgumentsSub.at(i)-=m_h;
                gradients.at(i) = (m_function(temporaryArgumentsAdd)-m_function(temporaryArgumentsSub))/(2*m_h);
            }
            return gradients;
        }

    }
}
#endif