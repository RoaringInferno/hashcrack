#pragma once

#include "daemon_settings.hpp"
#include "daemon_spawn.hpp"

#include "hash_function.hpp"

#include <vector>
#include <string>
#include <atomic>
#include <mutex>

class daemon {
friend class daemon_spawn;
private: // Private member types
    typedef std::vector<std::string> target_list_t;
    typedef std::vector<hash_function> hash_function_list_t;
private: // Member variables
    target_list_t targets;
    daemon_settings settings;
private: // Spawn global variables
    std::atomic<bool> solution_found;

    mutable std::mutex hash_function_list_mutex;
    hash_function_list_t hash_functions;

    void add_hash_function(const hash_function& hf);
    void add_hash_functions(const hash_function_list_t& hfs);
public:
    daemon(int argc, char** argv);
    void run();

    const target_list_t& get_targets() const;

    unsigned int get_target_count() const;
};