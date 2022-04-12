#include "SettingManager/SettingManager.h"

#include <QFile>

SettingManager* SettingManager::pInstance = nullptr;

SettingManager::SettingManager(const QString& csIniFile, QObject* parent)
    : m_sIniFile{csIniFile}, QObject(parent)
{
    m_pSettings = new QSettings(csIniFile, QSettings::IniFormat);
}

SettingManager* SettingManager::GetInstance(const QString& csIniFile, QObject* parent)
{
    if(pInstance==nullptr)
    {
        pInstance=new SettingManager(csIniFile, parent);
    }

    return pInstance;
}

void SettingManager::SetFile(const QString& csIniFile)
{
    m_sIniFile = csIniFile;
}

const QString& SettingManager::GetFile()
{
    return m_sIniFile;
}

QPair<int, QVariant> SettingManager::ReadValue(const QString& csSection, const QString& csKey)
{
    QPair<int, QVariant> result = {SUCCESS, 0};

    do
    {
        if(!QFile::exists(m_sIniFile))
        {
            result.first = INVALID_INIFILE;
            break;
        }

        if(!m_pSettings->contains(csSection + "/" + csKey))
        {
            result.first = NO_SUCH_VALUE;
            break;
        }

        //read value from ini file
        result.second = m_pSettings->value(csSection + "/" + csKey);

    } while(false);

    return result;
}

SettingManager::~SettingManager()
{

}
