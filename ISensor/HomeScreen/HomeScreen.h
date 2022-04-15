#ifndef HOME_SCREEN
#define HOME_SCREEN

//Qt
#include <QWidget>
#include <QPushButton>
#include <QChartView>

//Logic
#include "GlobalThings/GlobalThings.h"

#include "NetworkManager/NetworkManager.h"
#include "Logger/Logger.h"

QT_CHARTS_USE_NAMESPACE // for charts

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    HomeScreen();
    virtual ~HomeScreen();

private slots:
    void GetData();
    void SetData();

    void SetDarkTheme();
    void SetLightTheme();

private:
    QChartView* m_pTemperatureChartView;
    QChartView* m_pHumidityChartView;
    QChartView* m_pPressureChartView;
    QChartView* m_pUvChartView;

    QPushButton* m_pUpdataDataBtn;
};

#endif //HOME_SCREEN
