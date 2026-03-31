cpp
#ifndef QUANTUMCLAIMVERIFIER_STATISTICALVALIDATOR_H
#define QUANTUMCLAIMVERIFIER_STATISTICALVALIDATOR_H

#include <vector>
#include <cmath>
#include <numeric>

class StatisticalValidator {
public:
    static double perform_t_test(const std::vector<double>& group1, const std::vector<double>& group2);
    
private:
    static double calculate_mean(const std::vector<double>& data);
    static double calculate_variance(const std::vector<double>& data, double mean);
};

#endif //QUANTUMCLAIMVERIFIER_STATISTICALVALIDATOR_H