#include "UserConfig.hpp"

UserConfig::UserConfig()
{
    this->update();
}

const UserData &UserConfig::userData()
{
    this->update();
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
    }
}

void UserConfig::setUserData(const UserData &user_data)
{
    m_user_data = user_data;
    this->saveUserData(user_data.client_id, user_data.client_secret);
    //    this->update();
}

void UserConfig::saveUserData(const QString &client_id, const QString &client_secret)
{
    // TODO: use QFile
    auto file = std::ofstream(m_file_name);
    file << client_id.toStdString() << std::endl;
    file << client_secret.toStdString() << std::endl;
    file.close();
}
