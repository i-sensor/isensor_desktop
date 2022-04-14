#include "HomeScreen/HomeScreen.h"

#include <QVBoxLayout>

#include "GlobalThings/GlobalThings.h"

HomeScreen::HomeScreen()
{
    m_pUpdataDataBtn = new QPushButton("Update", this);

    //Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_pUpdataDataBtn);
    setLayout(layout);

    //connections
    connect(m_pUpdataDataBtn, &QPushButton::clicked, this, &HomeScreen::GetData);
    connect(NetworkManager::GetInstance(), &NetworkManager::GotData, this, &HomeScreen::SetData);
}

HomeScreen::~HomeScreen()
{

}

void HomeScreen::GetData()
{
    auto res = SettingManager::GetInstance(g_cszSettingsFile)->ReadValue(g_cszNetworkManagerSection, g_cszUrlKey);

    if(res.first != SettingManager::SUCCESS)
    {
        //log error
        return;
    }

    QUrl url = res.second.toUrl();

    NetworkManager::GetInstance()->Get(url);

}

void HomeScreen::SetData()
{
    //setting the data to graphic
}

void HomeScreen::SetDardTheme()
{

}

void HomeScreen::SetLightTheme()
{

}
