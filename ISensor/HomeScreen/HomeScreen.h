#ifndef HOME_SCREEN
#define HOME_SCREEN

//Qt
#include <QWidget>
#include <QPushButton>

//Logic
#include "NetworkManager/NetworkManager.h"
#include "SettingManager/SettingManager.h"
#include "Logger/Logger.h"

class HomeScreen : public QWidget
{
public:


private:
    QPushButton* m_pUpdataDataBtn;

    NetworkManager* m_pNetworkManager;
};

#endif //HOME_SCREEN
