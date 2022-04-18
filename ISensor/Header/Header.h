#ifndef HEADER_H
#define HEADER_H

#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>

enum THEME
{
    LIGHT,
    DARK
};

class Header : public QWidget
{
    Q_OBJECT

public:
    Header();
    virtual ~Header();

private: //methods

public slots:
    void setLightTheme();
    void setDarkTheme();

private slots:
    void emitSignalForChangeTheme();

signals:
    void setHomeScreen();
    void setInformationScreen();
    void setLightThemeSignal();
    void setDarkThemeSignal();

private:
    QMenuBar* m_pMenuBar;
    QLabel* m_pLabel;
    QPushButton* m_pButton;

    THEME m_eCurrentTheme = THEME::LIGHT;
};

#endif // HEADER_H
