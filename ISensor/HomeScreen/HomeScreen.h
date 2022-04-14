#ifndef HOME_SCREEN
#define HOME_SCREEN

//Qt
#include <QWidget>
#include <QPushButton>

//Logic
#include "GlobalThings/GlobalThings.h"

#include "NetworkManager/NetworkManager.h"
#include "Logger/Logger.h"

class HomeScreen : public QWidget
{
public:
    HomeScreen();
    ~HomeScreen();

private slots:
    void GetData();
    void SetData();

    void SetDardTheme();
    void SetLightTheme();

private:
    QPushButton* m_pUpdataDataBtn;
};

#endif //HOME_SCREEN
