#include "camera.h"
#include <QDebug>

Camera::Camera() : photoCount(0)
{
    qDebug() << "Camera initialized";
}

Camera::~Camera()
{
    qDebug() << "Camera destroyed";
}

void Camera::takePhoto()
{
    photoCount++;
    qDebug() << "📷 Photo taken! Total photos taken: " << photoCount;
}