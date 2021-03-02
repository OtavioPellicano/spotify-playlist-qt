#ifndef USERCONFIG_HPP
#define USERCONFIG_HPP

#include <fstream>
#include <string>

/**
 * @brief The UserData struct
 * This struct represents all user data necessary to connect to spotify API
 */
struct UserData
{
    std::string client_id = "";
    std::string client_secret = "";
    const std::string access_token_url = "https://accounts.spotify.com/api/token";
    const std::string auth_url = "https://accounts.spotify.com/authorize";
};

/**
 * @brief The UserConfig class
 * This class manager UserData for get the current user data (save .config file)
 * or set new Client ID and Client Secret
 */
class UserConfig
{
  public:
    UserConfig();

    /**
     * @brief user_data
     * This method will return the UserData updated
     * @see UserConfig::read_user_data
     * @return
     * UserData as const UserData&
     */
    const UserData &user_data();

    /**
     * @brief save_user_data
     * This method update the .config file with the values of client_id and client_secret
     * If there is no .config file, a new one is created
     * @param client_id
     * @param client_secret
     */
    void save_user_data(const std::string &client_id, const std::string &client_secret);

    bool updated() const;

    /**
     * @brief update
     * This method read the .config file and update the UserData member data
     * if there is no .config file, no update is made at all. So, client id and secret id will be set to empty
     */
    void update();

  private:
    UserData m_user_data;
    const std::string m_file_name = ".user_config";
    bool m_updated = false;
};

#endif // USERCONFIG_HPP
