cpp
#ifndef QUANTUMCLAIM_H
#define QUANTUMCLAIM_H

#include <string>
#include <vector>
#include <memory>
#include <boost/test/tools/floating_point_comparison.hpp>

// Forward declarations for Eigen types if needed
namespace Eigen {
    class ArrayXd;
    class ArrayXXd;
}

/**
 * @brief Structure to hold the result of a quantum claim validation
 */
struct ValidationResult {
    bool isValid;                    ///< Whether the quantum claim is statistically valid
    double pValue;                   ///< Statistical p-value of the validation
    std::string message;             ///< Detailed validation message
    double confidenceInterval;       ///< Confidence interval for the claim
    
    ValidationResult() : isValid(false), pValue(1.0), confidenceInterval(0.0) {}
    ValidationResult(bool valid, double p, const std::string& msg, double ci)
        : isValid(valid), pValue(p), message(msg), confidenceInterval(ci) {}
};

/**
 * @brief Class representing a quantum computing claim that can be validated
 */
class QuantumClaim {
private:
    std::string claimId;             ///< Unique identifier for the claim
    std::string algorithmName;       ///< Name of the quantum algorithm claimed
    std::string description;         ///< Description of the quantum advantage claimed
    std::vector<double> experimentalData; ///< Experimental data points
    std::vector<double> expectedClassical; ///< Expected classical performance
    double claimedSpeedup;           ///< The claimed quantum speedup factor
    double significanceLevel;        ///< Statistical significance level (alpha)
    
public:
    /**
     * @brief Construct a new QuantumClaim object
     * @param id Unique identifier
     * @param algo Algorithm name
     * @param desc Claim description
     * @param data Experimental data
     * @param classical Expected classical performance
     * @param speedup Claimed speedup
     * @param alpha Significance level
     */
    QuantumClaim(const std::string& id,
                 const std::string& algo,
                 const std::string& desc,
                 const std::vector<double>& data,
                 const std::vector<double>& classical,
                 double speedup,
                 double alpha = 0.05);
    
    /**
     * @brief Validate the quantum claim using statistical methods
     * @return ValidationResult containing validation results
     */
    ValidationResult validate() const;
    
    // Getters
    const std::string& getId() const { return claimId; }
    const std::string& getAlgorithm() const { return algorithmName; }
    const std::string& getDescription() const { return description; }
    const std::vector<double>& getExperimentalData() const { return experimentalData; }
    const std::vector<double>& getExpectedClassical() const { return expectedClassical; }
    double getClaimedSpeedup() const { return claimedSpeedup; }
    double getSignificanceLevel() const { return significanceLevel; }
    
    // Setters
    void setClaimedSpeedup(double speedup) { claimedSpeedup = speedup; }
    void setSignificanceLevel(double alpha) { significanceLevel = alpha; }
};

#endif // QUANTUMCLAIM_H