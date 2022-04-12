#ifndef NETWORK_MANAGER
#define NETWORK_MANAGER

#include <QObject>

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
    static NetworkManager *GetInstance(const QUrl& cUrl, QObject* parent = nullptr);

    ~NetworkManager();

private:
    NetworkManager(const QUrl& cUrl, QObject* parent = nullptr);

public: //methods

private:

    static NetworkManager* pInstance; //Singleton

};

#endif //NETWORK_MANAGER
