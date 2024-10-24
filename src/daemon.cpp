#include "daemon.hpp"

#include "light-cli"
#include <stdexcept>

daemon::daemon(int argc, char **argv) :
    targets(0),
    hash_functions(0),
    solution_found(false)
{
    lcli::cli_parser parser(argc, argv); // Parse the command line arguments

    for (lcli::cli_parser::iterator it = parser.begin(); it != parser.end(); ++it) // Iterate over the arguments
    {
        const auto pull_long_option_value = [&it, &parser](std::string_view option_name) -> lcli::cli_parser::argument // Lambda to pull the argument
        {
            ++it; // Increment the iterator
            if (it == parser.end() || (it->argument_type != lcli::cli_parser::argument::type::soft_argument && it->argument_type != lcli::cli_parser::argument::type::passed_long_option_value)) // If the iterator is at the end
            {
                throw std::runtime_error("Expected argument after option \"--" + std::string(option_name) + "\""); // Throw an error
            }
            lcli::cli_parser::argument argument = *it; // Get the argument
            return argument; // Return the argument
        };
        const auto pull_short_option_value = [&it, &parser](char option_symbol) -> lcli::cli_parser::argument // Lambda to pull the argument
        {
            ++it; // Increment the iterator
            if (it == parser.end() || it->argument_type != lcli::cli_parser::argument::type::soft_argument) // If the iterator is at the end
            {
                throw std::runtime_error("Expected argument after option \"-" + std::string(1, option_symbol) + "\""); // Throw an error
            }
            lcli::cli_parser::argument argument = *it; // Get the argument
            return argument; // Return the argument
        };

        switch (it->argument_type) // Switch on the argument type
        {
        case lcli::cli_parser::argument::soft_argument: // If the argument is a soft argument
            targets.push_back(std::string(it->argument_value)); // Add the argument to the target list
            break;
        case lcli::cli_parser::argument::hard_argument: // If the argument is a hard argument
            targets.push_back(std::string(it->argument_value)); // Add the argument to the target list
            break;
        case lcli::cli_parser::argument::long_option: // If the argument is a long option
            daemon_settings::setting_id_t setting_id = daemon_settings::get_setting_id(it->argument_value); // Get the setting ID
            if (daemon_settings::is_int_setting(setting_id)) // If the setting takes a value
            {
                lcli::cli_parser::argument value = pull_long_option_value(it->argument_value); // Pull the argument
                settings.set(setting_id, std::stoi(std::string(value.argument_value))); // Set the setting
            }
            else  // If the setting does not take a value
            {
                settings.toggle(setting_id); // Toggle the setting
            }
            break;
        case lcli::cli_parser::argument::short_option_string: // If the argument is a short option string
            for (char option_symbol : it->argument_value) // Iterate over the option symbols
            {
                daemon_settings::setting_id_t setting_id = daemon_settings::get_setting_id(option_symbol); // Get the setting ID
                if (daemon_settings::is_int_setting(setting_id)) // If the setting takes a value
                {
                    lcli::cli_parser::argument value = pull_short_option_value(option_symbol); // Pull the argument
                    settings.set(setting_id, std::stoi(std::string(value.argument_value))); // Set the setting
                }
                else // If the setting does not take a value
                {
                    settings.toggle(setting_id); // Toggle the setting
                }
            }
            break;
        case lcli::cli_parser::argument::passed_long_option_value: // If the argument is a passed long option value
            throw std::runtime_error("Unexpected value passed to an option \"" + std::string(it->argument_value) + "\""); // Throw an error
            break;
        }
    }
}