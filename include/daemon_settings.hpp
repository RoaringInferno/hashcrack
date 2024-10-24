#pragma once

class daemon_settings
{
public:
    enum setting_id_t : unsigned int
    {
        INVALID,
        SEARCH_DEPTH
    };
private:
    int search_depth;
public:
    daemon_settings();

    unsigned int get(setting_id_t setting_id) const;
    void set(setting_id_t setting_id, int value);
    void toggle(setting_id_t setting_id);
public:
    static setting_id_t get_setting_id(const std::string_view& setting_name);
    static setting_id_t get_setting_id(char setting_short_name);

    static bool is_int_setting(setting_id_t setting_id);
};