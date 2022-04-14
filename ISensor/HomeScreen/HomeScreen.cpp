//user .h files
#include "HomeScreen/HomeScreen.h"
#include "Logger/Logger.h"
#include "GlobalThings/GlobalThings.h"

//layouts
#include <QGridLayout>
#include <QBoxLayout>

//json
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

//charts
#include <QLineSeries>
#include <QChart>
#include <QCategoryAxis>

//other
#include <QDateTime>
#include <QFile>

static Logger* g_pLogger = Logger::getLogger(SettingManager::GetInstance(g_cszSettingsFile)->ReadValue(g_cszLoggerSection, g_cszLogFileKey).second.toString(), "", "HomeScreen", LOG_LEVEL::INFO);

HomeScreen::HomeScreen()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of HomeScreen()");

    m_pUpdataDataBtn = new QPushButton("Update", this);

    m_pTemperatureChartView = new QChartView(this);
    m_pHumidityChartView = new QChartView(this);
    m_pPressureChartView = new QChartView(this);
    m_pUvChartView = new QChartView(this);

    //Layout
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_pTemperatureChartView, 0, 0);
    layout->addWidget(m_pHumidityChartView, 0, 1);
    layout->addWidget(m_pPressureChartView, 1, 0);
    layout->addWidget(m_pUvChartView, 1, 1);

    layout->setContentsMargins(105, 50, 105, 50);
    layout->setSpacing(40);

    QBoxLayout* pBtnLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    pBtnLayout->addStretch(1);
    pBtnLayout->addWidget(m_pUpdataDataBtn);
    pBtnLayout->addStretch(1);

    layout->addLayout(pBtnLayout, 2, 0, 1, 2);
    setLayout(layout);

    //connections
    connect(m_pUpdataDataBtn, &QPushButton::clicked, this, &HomeScreen::GetData);
    connect(NetworkManager::GetInstance(), &NetworkManager::GotData, this, &HomeScreen::SetData);

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of HomeScreen()");
}

HomeScreen::~HomeScreen()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of ~HomeScreen()");

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of ~HomeScreen()");
}

void HomeScreen::GetData()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of GetData()");

    auto res = SettingManager::GetInstance(g_cszSettingsFile)->ReadValue(g_cszNetworkManagerSection, g_cszUrlKey);

    if(res.first != SettingManager::SUCCESS)
    {
        //log error
        return;
    }

    QUrl url = res.second.toUrl();

    NetworkManager::GetInstance()->Get(url);

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of GetData()");
}

void HomeScreen::SetData()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of SetData()");

    //getting json file name from ini
    auto res = SettingManager::GetInstance(g_cszSettingsFile)->ReadValue(g_cszNetworkManagerSection, g_cszDataFileKey);

    if(res.first != SettingManager::SUCCESS)
    {
        g_pLogger->log(LOG_LEVEL::ERROR, "error while getting json file name from ini file. Error code: %d", res.first);
        return;
    }

    const QString csResFileName = res.second.toString();

    //Parsing json
    QFile file(csResFileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( data, &jsonError );

        if( jsonError.error != QJsonParseError::NoError )
        {
              std::string sError = jsonError.errorString().toStdString();
              g_pLogger->log(LOG_LEVEL::ERROR, "json error: %s", sError.c_str());
              return;
        }

        QLineSeries* pTemperatureSeries = new QLineSeries();
        QLineSeries* pHumiditySeries = new QLineSeries();
        QLineSeries* pPressureSeries = new QLineSeries();
        QLineSeries* pUvSeries = new QLineSeries();
        QCategoryAxis *pTemperatureAxisX = new QCategoryAxis();
        QCategoryAxis *pHumidityAxisX = new QCategoryAxis();
        QCategoryAxis *pPressureAxisX = new QCategoryAxis();
        QCategoryAxis *pUvAxisX = new QCategoryAxis();

        if( document.isArray() )
        {
            QJsonArray arr = document.array();

            int i = 0;
            for(auto val : arr)
            {
                if(val.isObject())
                {
                    auto obj = val.toObject();
                    pTemperatureSeries->append(i,obj.value("temperature").toInt());
                    pHumiditySeries->append(i,obj.value("humidity").toInt());
                    pPressureSeries->append(i,obj.value("pressure").toInt());
                    pUvSeries->append(i,obj.value("uv").toInt());
                    pTemperatureAxisX->append(QDateTime::fromString(obj.value("date").toString(), Qt::ISODate).time().toString(), i);
                    pHumidityAxisX->append(QDateTime::fromString(obj.value("date").toString(), Qt::ISODate).time().toString(), i);
                    pPressureAxisX->append(QDateTime::fromString(obj.value("date").toString(), Qt::ISODate).time().toString(), i);
                    pUvAxisX->append(QDateTime::fromString(obj.value("date").toString(), Qt::ISODate).time().toString(), i);
                }
                i++;
            }
        }
        else
        {
            //log error
            delete pTemperatureSeries;
            delete pHumiditySeries;
            delete pPressureSeries;
            delete pUvSeries;
            delete pTemperatureAxisX;
            delete pHumidityAxisX;
            delete pPressureAxisX;
            delete pUvAxisX;
            return;
        }


        // Create chart, add data, hide legend, and add axis
        QChart* pTemperatureChart = new QChart();
        pTemperatureChart->legend()->hide();
        pTemperatureChart->addSeries(pTemperatureSeries);
        pTemperatureChart->createDefaultAxes();

        QChart* pHumidityChart = new QChart();
        pHumidityChart->legend()->hide();
        pHumidityChart->addSeries(pHumiditySeries);
        pHumidityChart->createDefaultAxes();

        QChart* pPressureChart = new QChart();
        pPressureChart->legend()->hide();
        pPressureChart->addSeries(pPressureSeries);
        pPressureChart->createDefaultAxes();

        QChart* pUvChart = new QChart();
        pUvChart->legend()->hide();
        pUvChart->addSeries(pUvSeries);
        pUvChart->createDefaultAxes();

        // Customize the title font
        QFont font;
        font.setPixelSize(18);

        pTemperatureChart->setTitleFont(font);
        pTemperatureChart->setTitleBrush(QBrush(Qt::black));
        pTemperatureChart->setTitle("Temperature");

        pHumidityChart->setTitleFont(font);
        pHumidityChart->setTitleBrush(QBrush(Qt::black));
        pHumidityChart->setTitle("Humidity");

        pPressureChart->setTitleFont(font);
        pPressureChart->setTitleBrush(QBrush(Qt::black));
        pPressureChart->setTitle("Pressure");

        pUvChart->setTitleFont(font);
        pUvChart->setTitleBrush(QBrush(Qt::black));
        pUvChart->setTitle("Uv");

        // Change the line color and weight
        QPen TemPeraturePen(QRgb(0xff8aae));
        TemPeraturePen.setWidth(4);
        QPen HumidityPen(QRgb(0x33c1ff));
        HumidityPen.setWidth(4);
        QPen PressurePen(QRgb(0x33ff77));
        PressurePen.setWidth(4);
        QPen UvPen(QRgb(0xff3333));
        UvPen.setWidth(4);

        pTemperatureSeries->setPen(TemPeraturePen);
        pHumiditySeries->setPen(HumidityPen);
        pPressureSeries->setPen(PressurePen);
        pUvSeries->setPen(UvPen);

        //animation
        pTemperatureChart->setAnimationOptions(QChart::AllAnimations);
        pHumidityChart->setAnimationOptions(QChart::AllAnimations);
        pPressureChart->setAnimationOptions(QChart::AllAnimations);
        pUvChart->setAnimationOptions(QChart::AllAnimations);

        //AxisX
        pTemperatureChart->setAxisX(pTemperatureAxisX, pTemperatureSeries);
        pHumidityChart->setAxisX(pHumidityAxisX, pHumiditySeries);
        pPressureChart->setAxisX(pPressureAxisX, pPressureSeries);
        pUvChart->setAxisX(pUvAxisX, pUvSeries);

        // Used to display the chart
        m_pTemperatureChartView->setChart(pTemperatureChart);
        m_pHumidityChartView->setChart(pHumidityChart);
        m_pPressureChartView->setChart(pPressureChart);
        m_pUvChartView->setChart(pUvChart);
    }
    else
    {
        g_pLogger->log(LOG_LEVEL::ERROR, "cannot open json file. Maybe it doesn't exist");
        return;
    }

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of SetData()");

}

void HomeScreen::SetDardTheme()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of SetDardTheme()");

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of SetDardTheme()");
}

void HomeScreen::SetLightTheme()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of SetLightTheme()");

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of SetLightTheme()");
}
