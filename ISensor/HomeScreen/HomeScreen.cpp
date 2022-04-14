#include "HomeScreen/HomeScreen.h"

#include <QFile>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QBoxLayout>

#include <QLineSeries>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QChart>
#include <QCategoryAxis>
#include <QDateTime>

#include "GlobalThings/GlobalThings.h"

HomeScreen::HomeScreen()
{
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
    int i = 10;
    i++;
    QFile file("data.json");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( data, &jsonError );

        if( jsonError.error != QJsonParseError::NoError )
        {
              // log erro jsonError.errorString().toStdString()
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
}

void HomeScreen::SetDardTheme()
{

}

void HomeScreen::SetLightTheme()
{

}
