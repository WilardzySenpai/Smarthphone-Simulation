#ifndef CAMERA_H
#define CAMERA_H

#include <QString>

class Camera
{
public:
    Camera();
    virtual ~Camera();
    
    void takePhoto();

protected:
    int photoCount;
};

#endif // CAMERA_H