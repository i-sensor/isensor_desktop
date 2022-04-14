#include "NetworkManager/NetworkManager.h"
#include "GlobalThings/GlobalThings.h"
#include "SettingManager/SettingManager.h"

#include <QFile>


static Logger* g_pLogger = Logger::getLogger(SettingManager::GetInstance(g_cszSettingsFile)->ReadValue(g_cszLoggerSection, g_cszLogFileKey).second.toString(), "", "NetworkManager", LOG_LEVEL::INFO);
NetworkManager* NetworkManager::pInstance = nullptr;

NetworkManager::NetworkManager()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of NetworkManager()");

    m_pNetworkAccessManager = new QNetworkAccessManager(this);

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of NetworkManager()");
}

NetworkManager* NetworkManager::GetInstance()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of GetInstance()");

    if(pInstance == nullptr)
    {
        pInstance = new NetworkManager();
        g_pLogger->log(LOG_LEVEL::INFO, "NetworkManager instance was created. Pointer: %p", pInstance);
    }

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of GetInstance()");

    return pInstance;
}

void NetworkManager::SetUrl(const QUrl& cUrl)
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of SetUrl()");

    m_url = cUrl;

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of SetUrl()");
}

void NetworkManager::Get()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of Get()");

    QNetworkRequest request;
    request.setUrl(m_url);

    g_pLogger->log(LOG_LEVEL::INFO, "making get request. Url: %s", m_url.toString().toStdString().c_str());
    m_pNetworkAccessManager->get(request);

    connect(m_pNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkManager::OnReplyReceived);

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of Get()");
}

void NetworkManager::Get(const QUrl& cUrl)
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of Get(QUrl)");

    QNetworkRequest request;
    request.setUrl(QUrl(cUrl));

    g_pLogger->log(LOG_LEVEL::INFO, "making get request. Url: %s", cUrl.toString().toStdString().c_str());
    m_pNetworkAccessManager->get(request);

    connect(m_pNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkManager::OnReplyReceived);

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of Get(QUrl)");
}

void NetworkManager::OnReplyReceived(QNetworkReply* pReply)
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of OnReplyReceived()");

    auto res = SettingManager::GetInstance(g_cszSettingsFile)->ReadValue(g_cszNetworkManagerSection, g_cszDataFileKey);

    if(res.first != SettingManager::SUCCESS)
    {
        g_pLogger->log(LOG_LEVEL::ERROR, "error while getting json file name from ini file. Error code: %d", res.first);
        return;
    }

    const QString csResFileName = res.second.toString();

    QFile file(csResFileName);
    file.open(QIODevice::WriteOnly);
    file.write(pReply->readAll());
    file.close();

    g_pLogger->log(LOG_LEVEL::INFO, "data wrote into %s file", csResFileName.toStdString().c_str());

    emit GotData();

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of OnReplyReceived()");
}


NetworkManager::~NetworkManager()
{
    g_pLogger->log(LOG_LEVEL::DEBUG, "start of ~NetworkManager()");

    g_pLogger->log(LOG_LEVEL::DEBUG, "end of ~NetworkManager()");
}
