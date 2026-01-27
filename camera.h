#ifndef CAMERA_H
#define CAMERA_H

#include <QString>

class Camera
{
public:
    Camera();
    virtual ~Camera();
    
    bool isCameraAvailable() const;
    bool takePhoto();
    QString getLastPhotoPath() const;

protected:
    int photoCount;
    QString lastPhotoPath;
    bool cameraAvailable;
};

#endif // CAMERA_H