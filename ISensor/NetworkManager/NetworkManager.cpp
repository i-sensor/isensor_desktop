#include "NetworkManager/NetworkManager.h"

#include <QFile>

NetworkManager* NetworkManager::pInstance = nullptr;

NetworkManager::NetworkManager(const QUrl& cUrl, QObject* parent)
    : m_url{cUrl}, QObject(parent)
{
    m_pNetworkAccessManager = new QNetworkAccessManager(this);
}

NetworkManager* NetworkManager::GetInstance(const QUrl& cUrl, QObject* parent)
{
    if(pInstance == nullptr)
    {
        pInstance = new NetworkManager(cUrl, parent);
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

void OnReplyReceived(QNetworkReply* pReply)
{
    QFile file("data.json");
    file.open(QIODevice::WriteOnly);
    file.write(pReply->readAll());
}


NetworkManager::~NetworkManager()
{

}
