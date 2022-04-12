#include "NetworkManager/NetworkManager.h"

#include <QFile>

NetworkManager* NetworkManager::pInstance = nullptr;

NetworkManager::NetworkManager()
{
    m_pNetworkAccessManager = new QNetworkAccessManager(this);
}

NetworkManager* NetworkManager::GetInstance()
{
    if(pInstance == nullptr)
    {
        pInstance = new NetworkManager();
    }

    return pInstance;
}

void NetworkManager::SetUrl(const QUrl& cUrl)
{
    m_url = cUrl;
}

void NetworkManager::Get()
{
    QNetworkRequest request;
    request.setUrl(QUrl(m_url));

    m_pNetworkAccessManager->get(request);

    connect(m_pNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkManager::OnReplyReceived);
}

void NetworkManager::Get(const QUrl& cUrl)
{
    QNetworkRequest request;
    request.setUrl(QUrl(cUrl));

    m_pNetworkAccessManager->get(request);

    connect(m_pNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkManager::OnReplyReceived);
}

void NetworkManager::OnReplyReceived(QNetworkReply* pReply)
{
    QFile file("data.json");
    file.open(QIODevice::WriteOnly);
    file.write(pReply->readAll());

    emit GotData();
}


NetworkManager::~NetworkManager()
{

}
