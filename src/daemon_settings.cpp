#include "daemon_settings.hpp"

#include <iostream>

daemon_settings::daemon_settings() :
    search_depth(3)
{
}

unsigned int daemon_settings::get(setting_id_t setting_id) const
{
    switch (setting_id)
    {
    case SEARCH_DEPTH:
        return search_depth;
    default:
        throw std::runtime_error("daemon_settings::get(setting_id_t): unknown setting_id\n"); // Error message
        return 0;
    }
}

void daemon_settings::set(setting_id_t setting_id, int value)
{
    switch (setting_id)
    {
    case SEARCH_DEPTH:
        search_depth = value;
        break;
    default:
        throw std::runtime_error("daemon_settings::set(setting_id_t, int): unknown setting_id\n"); // Error message
    }
}

void daemon_settings::toggle(setting_id_t setting_id)
{
    switch (setting_id)
    {
    case SEARCH_DEPTH:
        search_depth = !search_depth;
        break;
    default:
        throw std::runtime_error("daemon_settings::toggle(setting_id_t): unknown setting_id\n"); // Error message
    }
}

daemon_settings::setting_id_t daemon_settings::get_setting_id(const std::string_view &setting_name)
{
    if (setting_name == "search_depth")
    {
        return SEARCH_DEPTH;
    }
    else
    {
        throw std::runtime_error("daemon_settings::get_setting_id(const std::string_view&): unknown setting_name\n"); // Error message
        return INVALID;
    }
}

daemon_settings::setting_id_t daemon_settings::get_setting_id(char setting_short_name)
{
    switch (setting_short_name)
    {
    case 'd':
        return SEARCH_DEPTH;
    default:
        throw std::runtime_error("daemon_settings::get_setting_id(char): unknown setting_short_name\n"); // Error message
        return INVALID;
    }
}

bool daemon_settings::is_int_setting(setting_id_t setting_id)
{
    switch (setting_id)
    {
    case SEARCH_DEPTH:
        return true;
    default:
        throw std::runtime_error("daemon_settings::is_int_setting(setting_id_t): unknown setting_id\n"); // Error message
        return false;
    }
}
