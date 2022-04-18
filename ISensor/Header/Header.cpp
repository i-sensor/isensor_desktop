#include "Header/Header.h"
#include <QHBoxLayout>
#include <QFile>
#include <QFont>
#include <QColor>
#include <QWidget>

Header::Header()
{
    //UI
    m_pMenuBar = new QMenuBar(this);
    QMenu* pHome = new QMenu("Home", m_pMenuBar);
    QMenu* pInformation = new QMenu("Information", m_pMenuBar );
    m_pMenuBar->addMenu(pHome);
    m_pMenuBar->addMenu(pInformation);

    m_pButton = new QPushButton("push", this);
    m_pLabel = new QLabel("isensor",this);

    //Layout
    QBoxLayout* playout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    playout->addWidget(m_pMenuBar);
    playout->addStretch(1);
    playout->addWidget(m_pLabel);
    playout->addStretch(1);
    playout->addWidget(m_pButton);
    setLayout(playout);

    connect(pHome, &QMenu::triggered, this, &Header::setHomeScreen);
    connect(pInformation, &QMenu::triggered, this, &Header::setInformationScreen);
    connect(m_pButton, &QPushButton::clicked, this, &Header::emitSignalForChangeTheme);
}

void Header::emitSignalForChangeTheme()
{
    if (m_eCurrentTheme == THEME::LIGHT)
    {
        emit setDarkThemeSignal();
    }
    else if (m_eCurrentTheme == THEME::DARK)
    {
        emit setLightThemeSignal();
    }
}

void Header::setLightTheme()
{
    if(m_eCurrentTheme != THEME::LIGHT)
    {
        //read style sheets from file
        m_eCurrentTheme = THEME::LIGHT;
    }
}

void Header::setDarkTheme()
{
    if(m_eCurrentTheme != THEME::DARK)
    {
        //read style sheets from file
        m_eCurrentTheme = THEME::DARK;
    }
}

Header::~Header()
{

}
