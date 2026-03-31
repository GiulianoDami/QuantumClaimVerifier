cpp
#ifndef CLAIMPARSER_H
#define CLAIMPARSER_H

#include <string>
#include <boost/json.hpp>
#include "QuantumClaim.h"

class ClaimParser {
public:
    static QuantumClaim parse_json(const std::string& filename);
};

#endif // CLAIMPARSER_H