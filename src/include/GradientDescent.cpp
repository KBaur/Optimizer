#ifndef __kb_math_GradientDescent_cpp__
#define __kb_math_GradientDescent_cpp__
#include "GradientDescent.hpp"

namespace kb{
    namespace math{
        template<typename T>
        void GradientDescent<T>::SetMaxIterations(std::uint64_t p_maxIterations)
        {
            m_maxIterations = p_maxIterations;
        }

        template<typename T>
        void GradientDescent<T>::SetFunction(const std::function<T (std::vector<T>)> & p_function)
        {
            m_function = p_function;
            m_centralDifference = std::shared_ptr<CentralDifference<T>>(new CentralDifference<T>(p_function));
        }

        template<typename T>
        void GradientDescent<T>::SetMinimumGradientLength(const T & p_minGradientLength)
        {
            m_minGradientLength = p_minGradientLength;
        }

        template<typename T>
        void GradientDescent<T>::SetMinimumStepLength(const T & p_minStepLength)
        {
            m_minStepLength = p_minStepLength;
        }

        template<typename T>
        void GradientDescent<T>::SetStepSizeFunction(std::shared_ptr<StepSize<T>> p_stepSizeFunction)
        {
            m_stepSizeFunction = p_stepSizeFunction;
        }
        
        template<typename T>
        T GradientDescent<T>::Normalize(const std::vector<T> & p_vector)
        {
            T init(0);
            for(auto value:p_vector)
            {
                init += value*value;
            }
            return std::sqrt(init);
        }

        template<typename T>
        void GradientDescent<T>::Minimize(const std::vector<T> & p_initialState)
        {
            std::uint64_t counter = 0;
            T gradientNorm = 100;
            T minStepLength = 100;
            T functionValue;
            std::vector<T> step(p_initialState.size(),0.0);
            std::vector<T> gradient(p_initialState.size(),0.0);
            std::vector<T> initialState = p_initialState;
            T stepSize(0.0);
            m_stepSizeFunction->SetGradientFunction(m_centralDifference);

            while( counter < m_maxIterations &&
                gradientNorm >= m_minGradientLength &&
                minStepLength >= m_minGradientLength)
            {
                #pragma omp parallel for
                for(int i = 0; i < initialState.size();++i)
                    initialState.at(i) -= step.at(i);
                functionValue = m_function(initialState);
                gradient = m_centralDifference->Calculate(initialState);
                gradientNorm = Normalize(gradient);
                m_stepSizeFunction->SetCurrentParameter(initialState);
                m_stepSizeFunction->SetCurrentStepSize(stepSize);
                stepSize = m_stepSizeFunction->GetStepSize();
                #pragma omp parallel for
                for(int i = 0; i < initialState.size();++i)
                    step.at(i) = stepSize * gradient.at(i);
                minStepLength = Normalize(step);
                ++counter;
            }
            m_result.m_iterations = counter;
            m_result.m_converged = ( gradientNorm<m_minGradientLength || minStepLength < m_minGradientLength );
            m_result.m_memberVariables = initialState;
            m_result.m_result = functionValue;
        }

        template<typename T>
        Result<T> GradientDescent<T>::GetResult()
        {
            return m_result;
        }
    }
}
#endif