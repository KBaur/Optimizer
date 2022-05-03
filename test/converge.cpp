#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <assert.h>

#include <ArmijoLineSearch.hpp>
#include <ConstantStepSize.hpp>
#include <StrongWolfeSearch.hpp>
#include <GradientDescent.hpp>

bool near(double a, double b, double eps)
{
    return std::abs(a-b)<eps;
}
void testNumericOptimization()
{
    //Minimum at zero
    auto paraboloid = [](std::vector<double> p_parameter)->double
    {
        return p_parameter.at(0)*p_parameter.at(0)+p_parameter.at(1)*p_parameter.at(1);
    };
    auto constantStepSize = std::shared_ptr<kb::math::ConstantStepSize<double>>(new kb::math::ConstantStepSize<double>(0.2));
    auto armijoLineSearch = std::shared_ptr<kb::math::ArmijoLineSearch<double>>(new kb::math::ArmijoLineSearch<double>());
    auto strongWolfe = std::shared_ptr<kb::math::StrongWolfeSearch<double>>(new kb::math::StrongWolfeSearch<double>());
    
    kb::math::GradientDescent<double> minimize;
    minimize.SetFunction(paraboloid);
    minimize.SetMaxIterations(1000);
    minimize.SetMinimumGradientLength(1e-6 );
    minimize.SetMinimumStepLength(1e-3);
    minimize.SetStepSizeFunction(armijoLineSearch);
    minimize.Minimize({-1.5,2.0});

    auto result = minimize.GetResult();

    std::cout << "==================" << std::endl;
    std::cout << "Armijo Line Search" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "function value: " << result.m_result << std::endl;
    std::cout << "x: " << result.m_memberVariables.at(0) << " , y: " << result.m_memberVariables.at(1) << std::endl;
    std::cout << "iterations: " << result.m_iterations << std::endl;
    std::cout << "converged : " << (result.m_converged?"true":"false") << std::endl;
    std::cout << std::endl;

    assert(near(result.m_memberVariables.at(0),0.0,1e-6));
    assert(near(result.m_memberVariables.at(1),0.0,1e-6));
    assert(result.m_converged);

    minimize.SetStepSizeFunction(constantStepSize);
    minimize.Minimize({-1.5,2.0});
    result = minimize.GetResult();
    std::cout << "==================" << std::endl;
    std::cout << "Constant Step Size" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "function value: " << result.m_result << std::endl;
    std::cout << "x: " << result.m_memberVariables.at(0) << " , y: " << result.m_memberVariables.at(1) << std::endl;
    std::cout << "iterations: " << result.m_iterations << std::endl;
    std::cout << "converged : " << (result.m_converged?"true":"false") << std::endl;
    std::cout << std::endl;

    assert(near(result.m_memberVariables.at(0),0.0,1e-6));
    assert(near(result.m_memberVariables.at(1),0.0,1e-6));
    assert(result.m_converged);


    minimize.SetStepSizeFunction(strongWolfe);
    minimize.Minimize({-1.5,2.0});
    result = minimize.GetResult();
    std::cout << "==================" << std::endl;
    std::cout << "Strong Wolfe Search" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "function value: " << result.m_result << std::endl;
    std::cout << "x: " << result.m_memberVariables.at(0) << " , y: " << result.m_memberVariables.at(1) << std::endl;
    std::cout << "iterations: " << result.m_iterations << std::endl;
    std::cout << "converged : " << (result.m_converged?"true":"false") << std::endl;
    std::cout << std::endl;

    
    assert(near(result.m_memberVariables.at(0),0.0,1e-6));
    assert(near(result.m_memberVariables.at(1),0.0,1e-6));
    assert(result.m_converged);
}


int main(int argc, char ** argv)
{
    std::cout << "Starting Test" << std::endl;
    testNumericOptimization();
    std::cout << "Success!" << std::endl;
    return EXIT_SUCCESS;
}