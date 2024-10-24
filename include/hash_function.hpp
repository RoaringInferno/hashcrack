#pragma once

#include <string>

class hash_function {
public:
    static unsigned int target_count;
public: // Accessor functions
    std::string get_signature() const;
    const char* get_hash() const;
};