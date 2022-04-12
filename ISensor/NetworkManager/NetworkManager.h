#ifndef NETWORK_MANAGER
#define NETWORK_MANAGER

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetworkManager : public QObject
{
    Q_OBJECT

public: //Sigleton logic

    /*
     * Singletons should not be cloneable and assignable
     */
    NetworkManager(NetworkManager &other) = delete;
    void operator=(const NetworkManager &) = delete;

    /*
     * GetInstance - returns pointer to single object of SettingManager
     */
    static NetworkManager *GetInstance();

    ~NetworkManager();

private:
    NetworkManager();

private slots:
    void OnReplyReceived(QNetworkReply*);

public: //methods
    void SetUrl(const QUrl& cUrl);

    void Get();
    void Get(const QUrl& cUrl);

signals:
    void GotData();

private: //fields

    static NetworkManager* pInstance; //Singleton

    QUrl m_url;
    QNetworkAccessManager* m_pNetworkAccessManager = nullptr;

};

#endif //NETWORK_MANAGER
