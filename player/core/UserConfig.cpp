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
    // TODO: use QFile
    if (auto file = std::ifstream(m_file_name))
    {
        std::string str;
        std::getline(file, str);
        m_user_data.client_id = QString::fromStdString(str);
        std::getline(file, str);
        m_user_data.client_secret = QString::fromStdString(str);
        file.close();
        m_updated = true;
    }
}

bool UserConfig::updated() const
{
    return m_updated;
}

void UserConfig::save_user_data(const QString &client_id, const QString &client_secret)
{
    // TODO: use QFile
    auto file = std::ofstream(m_file_name);
    file << client_id.toStdString() << std::endl;
    file << client_secret.toStdString() << std::endl;
    file.close();
    m_updated = false;
}
