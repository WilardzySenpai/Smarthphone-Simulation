#ifndef SMARTPHONE_H
#define SMARTPHONE_H

#include "camera.h"
#include "musicplayer.h"
#include <QString>

class Smartphone : public Camera, public MusicPlayer
{
public:
    Smartphone();
    ~Smartphone();
    
    // Public methods to access private data
    bool unlockPhone(const QString &inputPassword);
    QString getStorageInfo();
    bool isPhoneUnlocked() const;
    void lockPhone();
    bool isCameraAvailable() const;
    bool takePhoto();
    QString getLastPhotoPath() const;
    
private:
    // Private members - sensitive data
    QString password;
    int storageUsed;      // in MB
    int totalStorage;     // in MB
    bool phoneUnlocked;
};

#endif // SMARTPHONE_H