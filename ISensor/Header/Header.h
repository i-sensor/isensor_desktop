#ifndef HEADER_H
#define HEADER_H
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>

#include <QtWidgets>
enum THEME{
   LIGHT,
    DARK
};




class Header: public QWidget

{
    Q_OBJECT

public:
    Header();
  virtual ~Header();

private:
    QMenuBar *m_MenuBar;
    QLabel *m_Label;





public:
    THEME m_eCurrentTheme = THEME::LIGHT;
        QPushButton* m_pButton;


public slots:
  void setLightTheme()
  {

  }
  void setDarkTheme()
  {

  }


private slots:
  void emitChangeTheme()
   {
     if (m_eCurrentTheme ==THEME::LIGHT){

       m_eCurrentTheme = DARK;
     }
     else if (m_eCurrentTheme == THEME:: DARK){

       m_eCurrentTheme = LIGHT;
   }
}
 signals:
        void setHomeScreen();
      void setInformationScreen();
};

#endif // HEADER_H
