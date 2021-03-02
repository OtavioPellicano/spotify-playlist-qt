#include "UserConfig.hpp"

UserConfig::UserConfig()
{
    this->update();
}

const UserData &UserConfig::user_data()
{
    if (!m_updated)
    {
        this->update();
    }

    return m_user_data;
}

void UserConfig::update()
{
    if (auto file = std::ifstream(m_file_name))
    {
        std::getline(file, m_user_data.client_id);
        std::getline(file, m_user_data.client_secret);
        file.close();
        m_updated = true;
    }
}

bool UserConfig::updated() const
{
    return m_updated;
}

void UserConfig::save_user_data(const std::string &client_id, const std::string &client_secret)
{
    auto file = std::ofstream(m_file_name);
    file << client_id << std::endl;
    file << client_secret << std::endl;
    file.close();
    m_updated = false;
}
