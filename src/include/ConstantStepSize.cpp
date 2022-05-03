#ifndef __kb_math_ConstantStepSize_cpp__
#define __kb_math_ConstantStepSize_cpp__
#include "ConstantStepSize.hpp"

namespace kb{
    namespace math{
        template<typename T>
        ConstantStepSize<T>::ConstantStepSize(const T & p_stepSize)
        {
            this->m_stepSize = p_stepSize;
        }
        template<typename T>
        
        T ConstantStepSize<T>::GetStepSize()
        {
            return this->m_stepSize;
        }
    }
}
#endif