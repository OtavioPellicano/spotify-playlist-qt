#include <QCoreApplication>
#include <QtTest>

// add necessary includes here
#include "UserConfig.hpp"

class TestPlayer : public QObject
{
    Q_OBJECT

  public:
    TestPlayer();
    ~TestPlayer();

  private slots:
    void test_user_config();
};

TestPlayer::TestPlayer()
{
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::test_user_config()
{
    UserConfig user_config;
    user_config.update_user_data("Otavio", "Pellicano");
    auto user_data = user_config.user_data();

    QVERIFY(user_data.client_id == "Otavio");
    QVERIFY(user_data.client_secret == "Pellicano");
    QVERIFY(user_data.access_token_url == "https://accounts.spotify.com/api/token");
    QVERIFY(user_data.auth_url == "https://accounts.spotify.com/authorize");
}

QTEST_MAIN(TestPlayer)

#include "tst_player.moc"
