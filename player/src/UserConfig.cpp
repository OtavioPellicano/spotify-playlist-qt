#include "UserConfig.hpp"

const UserData &UserConfig::user_data()
{
    this->read_user_data();
    return m_user_data;
}

void UserConfig::read_user_data()
{
    if (auto file = std::ifstream(m_file_name))
    {
        std::getline(file, m_user_data.client_id);
        std::getline(file, m_user_data.client_secret);
        file.close();
    }
}

void UserConfig::update_user_data(const std::string &client_id, const std::string &client_secret) const
{
    auto file = std::ofstream(m_file_name);
    file << client_id << std::endl;
    file << client_secret << std::endl;
    file.close();
}
