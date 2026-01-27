#include "smartphone.h"
#include <QDebug>

Smartphone::Smartphone() 
    : Camera(), MusicPlayer(), password("1234"), 
      storageUsed(0), totalStorage(256), phoneUnlocked(false)
{
    qDebug() << "🔒 Smartphone initialized and LOCKED";
}

Smartphone::~Smartphone()
{
    qDebug() << "Smartphone destroyed";
}

bool Smartphone::unlockPhone(const QString &inputPassword)
{
    if (inputPassword == password) {
        phoneUnlocked = true;
        qDebug() << "🔓 Phone UNLOCKED successfully!";
        return true;
    } else {
        phoneUnlocked = false;
        qDebug() << "❌ Incorrect password! Phone remains LOCKED";
        return false;
    }
}

QString Smartphone::getStorageInfo()
{
    if (!phoneUnlocked) {
        return "Phone is locked! Cannot access storage info.";
    }
    
    int availableStorage = totalStorage - storageUsed;
    int usagePercentage = (storageUsed * 100) / totalStorage;
    
    QString info = QString("📊 Storage Info:\n"
                           "Total Storage: %1 MB\n"
                           "Used: %2 MB\n"
                           "Available: %3 MB\n"
                           "Usage: %4%")
                           .arg(totalStorage)
                           .arg(storageUsed)
                           .arg(availableStorage)
                           .arg(usagePercentage);
    
    qDebug() << info;
    return info;
}

bool Smartphone::isPhoneUnlocked() const
{
    return phoneUnlocked;
}

void Smartphone::lockPhone()
{
    phoneUnlocked = false;
    qDebug() << "🔒 Phone LOCKED";
}