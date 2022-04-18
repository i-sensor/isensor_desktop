#include "Header/Header.h"
#include <QHBoxLayout>
#include <QFile>
#include <QFont>
#include <QColor>
#include <QWidget>

Header::Header()
{


  m_MenuBar = new QMenuBar(this);

  QMenu* pHome = new QMenu("Home", m_MenuBar);
  QMenu* pInformation = new QMenu("Information", m_MenuBar );


  m_pButton = new QPushButton("push", this);
//m_pButton->move(400, 10);

  QLabel* m_Label = new QLabel("isensor",this);
  //m_Label->move(220, 5);



 m_MenuBar->addMenu(pHome);
  m_MenuBar->addMenu(pInformation);


  QBoxLayout * layout = new QBoxLayout(QBoxLayout::LeftToRight);
layout->addWidget(m_MenuBar);
layout->addStretch(1);
layout->addWidget(m_Label);
layout->addStretch(2);
layout->addWidget(m_pButton);



setLayout(layout);



  connect(pHome, &QMenu::triggered, this, &Header::setHomeScreen);
  connect(pInformation, &QMenu::triggered, this, &Header::setInformationScreen);
  connect(m_pButton, &QPushButton::clicked, this, &Header::emitChangeTheme);
}

Header::~Header()
{

}
