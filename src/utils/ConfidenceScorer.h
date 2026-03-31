cpp
#ifndef QUANTUMCLAIMVERIFIER_CONFIDENCESCORER_H
#define QUANTUMCLAIMVERIFIER_CONFIDENCESCORER_H

#include <boost/test/tools/floating_point_comparison.hpp>
#include <Eigen/Dense>
#include <cmath>

// Forward declaration assuming ValidationResult is defined elsewhere
struct ValidationResult {
    double p_value;
    double test_statistic;
    double expected_statistic;
    int sample_size;
    bool is_valid;
};

class ConfidenceScorer {
public:
    /**
     * Calculates a confidence score based on validation results
     * @param result The validation result to score
     * @return A confidence score between 0.0 and 1.0
     */
    static double calculate_confidence(const ValidationResult& result) {
        if (!result.is_valid) {
            return 0.0;
        }
        
        // Calculate p-value based confidence (lower p-values indicate higher confidence)
        double p_value_confidence = result.p_value < 0.05 ? 
            (1.0 - result.p_value) : 
            std::max(0.0, 1.0 - (result.p_value / 0.05));
        
        // Calculate statistic deviation confidence
        double deviation = std::abs(result.test_statistic - result.expected_statistic);
        double max_deviation = std::max(std::abs(result.test_statistic), 
                                       std::abs(result.expected_statistic));
        double deviation_confidence = max_deviation > 0 ? 
            std::max(0.0, 1.0 - (deviation / max_deviation)) : 
            1.0;
        
        // Weighted average of both confidences
        double final_confidence = 0.6 * p_value_confidence + 0.4 * deviation_confidence;
        
        // Ensure confidence is within [0, 1] bounds
        return std::min(1.0, std::max(0.0, final_confidence));
    }
};

#endif //QUANTUMCLAIMVERIFIER_CONFIDENCESCORER_H