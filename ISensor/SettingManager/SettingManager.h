#ifndef SETTING_MANAGER
#define SETTING_MANAGER

#include <QObject>
#include <QVariant>
#include <QPair>
#include <QSettings>

#include "Logger/Logger.h"

class SettingManager : public QObject
{
public: //Sigleton logic

    /*
     * Singletons should not be cloneable and assignable
     */
    SettingManager(SettingManager &other) = delete;
    void operator=(const SettingManager &) = delete;

    /*
     * GetInstance - returns pointer to single object of SettingManager
     */
    static SettingManager *GetInstance(const QString& csIniFile = "");

    ~SettingManager();

public:

    enum //results
    {
        SUCCESS,
        INVALID_INIFILE,
        NO_SUCH_VALUE
    };

public: //methods
    void SetFile(const QString& csFile);
    const QString& GetFile();

    /*
     * ReadValue - reads value from ini file
     *
     * [parameters]
     * csSection - section name
     * csKey - key name
     *
     * [return]
     * Pair of values.
     *     1) first - error code:
     *     - SUCCESS -- on success
     *     - INVALID_INIFILE -- if you provided(while initialization or SetFile call) invalid ini file
     *     - NO_SUCH_VALUE -- if there isn't such value in ini file
     *
     *     2) second - value from ini file (in QVariant form)
     */
    QPair<int, QVariant> ReadValue(const QString& csSection, const QString& csKey);

private:
    SettingManager(const QString& csIniFile = "");

private: //fields
    static SettingManager* pInstance; //Singleton

    QSettings* m_pSettings;
    QString m_sIniFile; //path to file + file name

};

#endif
