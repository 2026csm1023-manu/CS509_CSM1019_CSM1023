#include "../include/gradient_descent.h"
#include "../driver/reader.h"

#include <cmath>

namespace
{
// Horner's rule evaluates c0 + c1*x + ... + cd*x^d without pow().
double evaluate_polynomial(const vector<double>& coefficients, double x)
{
    double value = 0.0;

    for (int i = static_cast<int>(coefficients.size()) - 1; i >= 0; --i)
        value = value * x + coefficients[i];

    return value;
}

double evaluate_derivative(const vector<double>& coefficients, double x)
{
    const int degree = static_cast<int>(coefficients.size()) - 1;
    double value = 0.0;

    // This is Horner's rule for c1 + 2*c2*x + ... + d*cd*x^(d-1).
    for (int i = degree; i >= 1; --i)
        value = value * x + static_cast<double>(i) * coefficients[i];

    return value;
}
}

GDResult gradient_descent(const GDInput& input)
{
    GDResult result{};
    double x = input.initial_x;

    for (int iteration = 0; iteration < input.max_iterations; ++iteration)
    {
        const double derivative = evaluate_derivative(input.coefficients, x);

        if (std::abs(derivative) <= input.tolerance)
        {
            result.converged = true;
            break;
        }

        x -= input.learning_rate * derivative;
        ++result.iterations;
    }

    // Check the derivative after the final permitted update as well.  This
    // correctly marks convergence that occurs on the last iteration.
    if (!result.converged &&
        std::abs(evaluate_derivative(input.coefficients, x)) <= input.tolerance)
    {
        result.converged = true;
    }

    result.final_x = x;
    result.final_fx = evaluate_polynomial(input.coefficients, x);
    return result;
}
