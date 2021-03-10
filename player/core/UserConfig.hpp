#ifndef USERCONFIG_HPP
#define USERCONFIG_HPP

#include <QString>
#include <fstream>
#include <string>

/**
 * @brief The UserData struct
 * This struct represents all user data necessary to connect to spotify API
 */
struct UserData
{
    QString client_id = "";
    QString client_secret = "";
    QString access_token_url = "https://accounts.spotify.com/api/token";
    QString auth_url = "https://accounts.spotify.com/authorize";
    QString api_url = "https://api.spotify.com";
    QString api_version = "v1";
    QString base_url = api_url + "/" + api_version;
};

/**
 * @brief The UserConfig class
 * This class manager UserData geting the current user data (saved in .user_config file)
 * or set new Client ID and Client Secret
 */
class UserConfig
{
  public:
    UserConfig();

    /**
     * @brief data
     * This method will return the UserData updated
     * @return
     * data as const UserData&
     */
    const UserData &data();

    /**
     * @brief save
     * This method update the .config file with the values of client_id and client_secret
     * If there is no .config file, a new one is created
     * @param client_id
     * @param client_secret
     */
    void save(const QString &client_id, const QString &client_secret);

    /**
     * @brief setUserData
     * @param user_data
     */
    void setUserData(const UserData &user_data);

  private:
    /**
     * @brief update
     * This method read the .config file and update the UserData member data
     * if there is no .config file, no update is made at all. So, client id and secret id will be set to empty
     */
    void update();

  private:
    UserData m_user_data;
    const std::string m_file_name = ".user_config";
};

#endif // USERCONFIG_HPP
