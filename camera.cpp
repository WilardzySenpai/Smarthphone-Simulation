#include "camera.h"
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDir>
#include <QStandardPaths>

Camera::Camera() : photoCount(0), cameraAvailable(true)
{
    // Check if camera hardware is available (simplified check)
    // In a real app, you'd use platform-specific APIs
    cameraAvailable = true; // Assume camera is available
    qDebug() << "Camera initialized - Available: " << cameraAvailable;
}

Camera::~Camera()
{
    qDebug() << "Camera destroyed";
}

bool Camera::isCameraAvailable() const
{
    return cameraAvailable;
}

bool Camera::takePhoto()
{
    if (!cameraAvailable) {
        qDebug() << "❌ Camera not available!";
        return false;
    }
    
    photoCount++;
    
    // Create a photo filename with timestamp
    QString timestamp = QDate::currentDate().toString("yyyy-MM-dd") + "_" + 
                       QTime::currentTime().toString("hh-mm-ss");
    QString photoFilename = QString("photo_%1_%2.jpg").arg(timestamp).arg(photoCount);
    
    // Save photo to Pictures directory
    QString picturesPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString photoPath = picturesPath + "/" + photoFilename;
    
    lastPhotoPath = photoPath;
    qDebug() << "📷 Photo taken! Total photos: " << photoCount;
    qDebug() << "📸 Photo saved to: " << photoPath;
    
    return true;
}

QString Camera::getLastPhotoPath() const
{
    return lastPhotoPath;
}