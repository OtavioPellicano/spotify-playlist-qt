#ifndef USERCONFIG_HPP
#define USERCONFIG_HPP

#include <fstream>
#include <string>

struct UserData
{
    std::string client_id = "";
    std::string client_secret = "";
    const std::string access_token_url = "https://accounts.spotify.com/api/token";
    const std::string auth_url = "https://accounts.spotify.com/authorize";
};

class UserConfig
{
  public:
    UserConfig();

    const UserData &user_data();
    void update_user_data(const std::string &client_id, const std::string &client_secret) const;

  private:
    void read_user_data();

  private:
    UserData m_user_data;
    const std::string m_file_name = ".config";
};

#endif // USERCONFIG_HPP
