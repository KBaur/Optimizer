#ifndef __kb_math_ArmijoLineSearch_cpp__
#define __kb_math_ArmijoLineSearch_cpp__

#include "ArmijoLineSearch.hpp"

namespace kb{
    namespace math{
        template<typename T>
        ArmijoLineSearch<T>::ArmijoLineSearch() : ArmijoLineSearch(1e-4,1e-6, 1.0, 1000)
        {}

        template<typename T>
        ArmijoLineSearch<T>::ArmijoLineSearch(
            const T p_C1,
            const T p_minStep,
            const T p_maxStep,
            const std::uint64_t p_maxIterations
            )
        {
            SetConstant(p_C1);
            SetStepLength(p_minStep,p_maxStep);
            SetMaxIterations(p_maxIterations);
        }

        template<typename T>
        void ArmijoLineSearch<T>::SetConstant(T p_C1)
        {
            if(p_C1<=0)
            {
                std::stringstream ss; 
                ss << "Parameter cannot be 0 or smaller." <<" File: "<< __FILE__ << " Line: "<< __LINE__;
                throw std::invalid_argument(ss.str().c_str());
            }
            m_C1 = p_C1;
        }

        template<typename T>
        void ArmijoLineSearch<T>::SetStepLength(T p_minStep,T p_maxStep)
        {
            if(p_minStep<=0||p_maxStep<=0)
            {
                std::stringstream ss; 
                ss << "Step parameter cannot be 0 or smaller." <<" File: "<< __FILE__ << " Line: "<< __LINE__;
                throw std::invalid_argument(ss.str().c_str());
            }
            m_minStep = p_minStep<p_maxStep?p_minStep:p_maxStep;
            m_maxStep = m_minStep==p_minStep?p_maxStep:p_minStep;
        }

        template<typename T>
        void ArmijoLineSearch<T>::SetLearningRate(T p_learningRate)
        {
            if(p_learningRate<=0)
            {
                std::stringstream ss; 
                ss << "Learning rate cannot be 0 or smaller." <<" File: "<< __FILE__ << " Line: "<< __LINE__;
                throw std::invalid_argument(ss.str().c_str());
            }
            m_learningRate = p_learningRate;
        }
        
        template<typename T>
        void ArmijoLineSearch<T>::SetMaxIterations(std::uint64_t p_maxIterations)
        {
            if(p_maxIterations<=0)
            {
                std::stringstream ss; 
                ss << "Maximal iterations cannot be 0 or smaller." <<" File: "<< __FILE__ << " Line: "<< __LINE__;
                throw std::invalid_argument(ss.str().c_str());
            }
            m_maxIterations = p_maxIterations;
        }  

        template<typename T>
        void ArmijoLineSearch<T>::SetCurrentStepSize(T p_currentStepSize)
        {
            if(p_currentStepSize<0)
            {
                std::stringstream ss; 
                ss << "Step parameter cannot be smaller than 0." <<" File: "<< __FILE__ << " Line: "<< __LINE__;
                throw std::invalid_argument(ss.str().c_str());
            }
            m_currentStepSize = p_currentStepSize;
        }

        template<typename T>
        void ArmijoLineSearch<T>::SetGradientFunction(std::shared_ptr<CentralDifference<T>> p_gradientFunction)
        {
            if(p_gradientFunction==nullptr)
            {
                std::stringstream ss; 
                ss << "Gradient function cannot be a nullptr." <<" File: "<< __FILE__ << " Line: "<< __LINE__;
                throw std::invalid_argument(ss.str().c_str());
            }
            m_gradientFunction = p_gradientFunction;
        }

        template<typename T>
        void ArmijoLineSearch<T>::SetCurrentParameter(const std::vector<T> & p_currentParameter)
        {
            if(p_currentParameter.size()==0)
            {
                std::stringstream ss; 
                ss << "Current parameter size must be bigger than 0." <<" File: "<< __FILE__ << " Line: "<< __LINE__;
                throw std::invalid_argument(ss.str().c_str());
            }
            m_currentParameter = p_currentParameter;
        }
        
        template<typename T>
        bool ArmijoLineSearch<T>::CheckCondition(const std::vector<T> & p_parameter, const std::vector<T> & p_newParameter,T p_stepSize,T p_sum)
        {
            T functionValue = m_gradientFunction->GetFunction()(p_parameter);
            T functionValueNew =  m_gradientFunction->GetFunction()(p_newParameter);
            return (functionValueNew <= functionValue - m_C1 * p_stepSize * p_sum);
        }

        template<typename T>
        T ArmijoLineSearch<T>::GetStepSize()
        {
            auto functionToEvaluate = m_gradientFunction->GetFunction();
            std::vector<T> parameterNew = std::vector<T>(m_currentParameter.size(),0);
            std::vector<T> gradientNew = std::vector<T>(m_currentParameter.size(),0);
            std::vector<T> gradient = m_gradientFunction->Calculate(m_currentParameter);
            T functionValue{0};
            T newFunctionValue{0};
            bool armijoCondition = false;
            T stepSize = m_currentStepSize==0?m_maxStep:m_currentStepSize;
            std::uint64_t counter{0};
            double sum{0};
            for(T val : gradient)
            {
                sum+= val*val;
            }
            functionValue = functionToEvaluate(m_currentParameter);
            while( counter < m_maxIterations &&stepSize >= m_minStep &&!armijoCondition)
            {
                stepSize*=m_learningRate;
                #pragma omp parallel for
                for(int i = 0;i<m_currentParameter.size();++i)
                {
                    parameterNew.at(i) = m_currentParameter.at(i) -  stepSize * gradient.at(i);
                }
                newFunctionValue = functionToEvaluate(parameterNew);
                armijoCondition = CheckCondition(m_currentParameter,parameterNew,stepSize,sum);
                ++counter;
            }
            this->m_stepSize = stepSize;
            return this->m_stepSize;
        }      

    }
}

#endif