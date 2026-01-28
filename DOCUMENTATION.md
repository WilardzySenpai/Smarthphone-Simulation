# Smartphone Simulator - Technical Documentation

## Overview

The Smartphone Simulator is a C++ Qt application designed to demonstrate fundamental Object-Oriented Programming (OOP) concepts, specifically **Multiple Inheritance**, **Encapsulation**, and **Access Control**. It simulates the core functionalities of a smartphone, including camera operations, music playback, and security features.

The application provides a graphical user interface (GUI) built with the Qt framework, allowing users to interact with the simulated smartphone.

## Project Structure

The project consists of the following files:

- **`main.cpp`**: The entry point of the application. It initializes the Qt Application and shows the main window.
- **`camera.h` / `camera.cpp`**: Defines the `Camera` base class, handling photo-taking capabilities.
- **`musicplayer.h` / `musicplayer.cpp`**: Defines the `MusicPlayer` base class, handling audio playback using Qt's Multimedia module.
- **`smartphone.h` / `smartphone.cpp`**: Defines the `Smartphone` class, which inherits from both `Camera` and `MusicPlayer`. It adds security and storage management.
- **`mainwindow.h` / `mainwindow.cpp`**: Implements the GUI and handles user interactions.
- **`SmartphoneSimulator.pro`**: The Qt Project file that defines build settings and dependencies (like `multimedia`).
- **`README.md`**: Provides a general overview and instructions for building and using the application.
- **`DOCUMENTATION.md`**: This file, providing detailed technical documentation of the codebase.

## Class Documentation

### 1. Camera (Base Class)

The `Camera` class handles basic photography functions.

#### Definition (from `camera.h`):
```cpp
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
```

#### Key Implementation (from `camera.cpp`):
The `takePhoto()` function demonstrates how the camera state is managed:
```cpp
bool Camera::takePhoto()
{
    if (!cameraAvailable) {
        qDebug() << "❌ Camera not available!";
        return false;
    }

    photoCount++;
    // ... logic to generate timestamp and photo path ...
    lastPhotoPath = photoPath;
    return true;
}
```

### 2. MusicPlayer (Base Class)

The `MusicPlayer` class provides audio playback functionality.

#### Definition (from `musicplayer.h`):
```cpp
class MusicPlayer : public QObject
{
    Q_OBJECT
public:
    MusicPlayer(QObject *parent = nullptr);
    virtual ~MusicPlayer();

    bool loadMusic(const QString &filePath);
    bool playMusic();
    void stopMusic();
    // ...
protected:
    bool isPlaying;
    QString currentSong;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};
```

#### Key Implementation (from `musicplayer.cpp`):
Loading music involves validating the file extension:
```cpp
bool MusicPlayer::loadMusic(const QString &filePath)
{
    // ... file existence checks ...
    QString suffix = fileInfo.suffix().toLower();
    if (suffix != "mp3" && suffix != "wav" && suffix != "flac" && suffix != "ogg") {
        return false;
    }
    currentFilePath = filePath;
    currentSong = fileInfo.fileName();
    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    return true;
}
```

### 3. Smartphone (Derived Class)

The `Smartphone` class represents the unified device. It uses **Multiple Inheritance** to combine the features of both `Camera` and `MusicPlayer`.

#### Definition (from `smartphone.h`):
```cpp
class Smartphone : public Camera, public MusicPlayer
{
public:
    Smartphone();
    ~Smartphone();

    bool unlockPhone(const QString &inputPassword);
    QString getStorageInfo();
    void lockPhone();
    // ... wrappers for inherited methods ...
private:
    QString password;
    int storageUsed;
    int totalStorage;
    bool phoneUnlocked;
};
```

#### Key Implementation (from `smartphone.cpp`):
The `unlockPhone` method manages the security state:
```cpp
bool Smartphone::unlockPhone(const QString &inputPassword)
{
    if (inputPassword == password) {
        phoneUnlocked = true;
        return true;
    } else {
        phoneUnlocked = false;
        return false;
    }
}
```

### 4. MainWindow (GUI)

The `MainWindow` class manages the graphical user interface.

#### UI Update Logic (from `mainwindow.cpp`):
The `updateUI()` method is central to the application's access control, enabling or disabling features based on the phone's state:
```cpp
void MainWindow::updateUI()
{
    if (myPhone->isPhoneUnlocked()) {
        phoneStateLabel->setText("Status: 🔓 UNLOCKED");
        takePhotoButton->setEnabled(true);
        playMusicButton->setEnabled(true);
        getStorageButton->setEnabled(true);
    } else {
        phoneStateLabel->setText("Status: 🔒 LOCKED");
        takePhotoButton->setEnabled(false);
        playMusicButton->setEnabled(false);
        getStorageButton->setEnabled(false);
    }
    // ... update music status ...
}
```

## Application Workflow

1. **Initialization**: A `Smartphone` object is created.
   ```cpp
   // From mainwindow.cpp
   myPhone = new Smartphone();
   ```
2. **Security**: User enters a password and clicks unlock.
   ```cpp
   // From mainwindow.cpp
   bool success = myPhone->unlockPhone(password);
   ```
3. **State Management**: The UI is updated based on the `Smartphone` state.
   ```cpp
   // From smartphone.cpp
   bool Smartphone::isPhoneUnlocked() const { return phoneUnlocked; }
   ```

## Core Concepts Demonstrated

### Multiple Inheritance: The "Why"

Multiple inheritance allows a class to derive from more than one base class.

- **In this project**: The `Smartphone` class inherits from two parents.
  ```cpp
  // From smartphone.h
  class Smartphone : public Camera, public MusicPlayer
  ```
- **Why use it here?**:
    - **Functional Composition**: It allows the `Smartphone` to be both a "Camera" and a "Music Player" simultaneously, reusing the code from both base classes.

### Encapsulation & "Private Mode": The "Why"

Encapsulation involves hiding the internal state of an object using the `private` access modifier.

- **In this project**: Sensitive data is kept in **Private Mode** within the `Smartphone` class.
  ```cpp
  // From smartphone.h
  private:
      QString password;
      int storageUsed;
      bool phoneUnlocked;
  ```
- **Why use Private members?**:
    - **Data Integrity**: By making these members `private`, we ensure that only the `Smartphone` class itself can modify them, preventing external code from bypassing security rules.

### Access Control: The "Why"
> Not so important to the graph and report

Access control provides "Gatekeeping" for the object's features.

- **In this project**: Methods restrict access based on internal state.
  ```cpp
  // From smartphone.cpp
  QString Smartphone::getStorageInfo() {
      if (!phoneUnlocked) {
          return "Phone is locked! Cannot access storage info.";
      }
      // ... process storage info ...
  }
  ```
- **Why implement this?**:
    - **State Management**: It ensures that a "Locked" phone cannot perform "Unlocked" actions, providing a simulation of real-world device security.
