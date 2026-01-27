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

#### Member Variables (Protected):
- `int photoCount`: Keeps track of the total number of photos taken.
- `QString lastPhotoPath`: Stores the file path of the most recently taken photo.
- `bool cameraAvailable`: A flag indicating if the camera hardware is available.

#### Public Functions:
- `Camera()`: Constructor that initializes `photoCount` to 0 and `cameraAvailable` to true.
- `virtual ~Camera()`: Virtual destructor.
- `bool isCameraAvailable() const`: Returns the availability of the camera.
- `bool takePhoto()`: Simulates taking a photo. It generates a filename with a timestamp and "saves" it to the system's Pictures directory path. Returns `true` if successful.
- `QString getLastPhotoPath() const`: Returns the path of the last photo taken.

### 2. MusicPlayer (Base Class)

The `MusicPlayer` class provides audio playback functionality. It inherits from `QObject` to support signals and slots.

#### Member Variables (Protected):
- `bool isPlaying`: Indicates if music is currently playing.
- `QString currentSong`: The name of the currently loaded song.
- `QString currentFilePath`: The full path of the currently loaded audio file.
- `QMediaPlayer *mediaPlayer`: Pointer to the Qt Multimedia player.
- `QAudioOutput *audioOutput`: Pointer to the audio output device.

#### Public Functions:
- `MusicPlayer(QObject *parent = nullptr)`: Constructor that initializes the `mediaPlayer` and `audioOutput`.
- `virtual ~MusicPlayer()`: Destructor that ensures proper cleanup of media objects.
- `bool loadMusic(const QString &filePath)`: Validates and loads an audio file (MP3, WAV, FLAC, OGG).
- `bool playMusic()`: Starts playback of the loaded music.
- `void stopMusic()`: Stops the music playback.
- `bool isPlayingNow() const`: Returns the current playback state from the `mediaPlayer`.
- `QString getCurrentSong() const`: Returns the name of the current song.

### 3. Smartphone (Derived Class)

The `Smartphone` class represents the unified device. It uses **Multiple Inheritance** to combine the features of both `Camera` and `MusicPlayer`.

#### Inheritance:
```cpp
class Smartphone : public Camera, public MusicPlayer
```

#### Member Variables (Private):
- `QString password`: The security password (default is "1234").
- `int storageUsed`: Amount of storage used in MB.
- `int totalStorage`: Total storage capacity in MB (default 256 MB).
- `bool phoneUnlocked`: State of the phone (Locked/Unlocked).

#### Public Functions:
- `Smartphone()`: Constructor that initializes the phone to a locked state and sets default storage values.
- `~Smartphone()`: Destructor.
- `bool unlockPhone(const QString &inputPassword)`: Validates the password and unlocks the phone if correct.
- `void lockPhone()`: Re-locks the phone.
- `bool isPhoneUnlocked() const`: Returns whether the phone is unlocked.
- `QString getStorageInfo()`: Returns a formatted string with storage details, but only if the phone is unlocked (demonstrating access control).
- **Overridden/Wrapped Methods**: It provides wrapper methods for inherited functionality (`takePhoto`, `playMusic`, etc.) to maintain a clean interface.

### 4. MainWindow (GUI)

The `MainWindow` class manages the graphical user interface and connects user actions to the `Smartphone` logic.

#### Key Components:
- `Smartphone *myPhone`: The instance of the smartphone being simulated.
- `QTextEdit *outputLog`: A scrollable area that displays the history of actions and system messages.
- `QLineEdit *passwordInput`: Where users enter the unlock password.
- Various `QPushButton` objects for triggering actions (Take Photo, Play Music, Unlock, etc.).

#### Key Slots (Event Handlers):
- `onUnlockClicked()`: Retrieves the text from `passwordInput` and attempts to unlock the phone.
- `onTakePhotoClicked()`: Triggers the camera functionality if the phone is unlocked.
- `onLoadMusicClicked()`: Opens a file dialog to select an audio file.
- `onPlayMusicClicked()`: Starts playback of the loaded file.
- `updateUI()`: A crucial method that enables or disables buttons based on the phone's locked/unlocked state, ensuring that protected features cannot be accessed while locked.

## Application Workflow

1. **Initialization**: When the app starts, a `Smartphone` object is created in a **LOCKED** state.
2. **Security**: The user must enter the correct password ("1234") and click "Unlock Phone".
3. **State Change**: Upon successful unlock, `updateUI()` enables the photo, music, and storage buttons.
4. **Interaction**:
   - **Photography**: Clicking "Take Photo" calls `myPhone->takePhoto()`.
   - **Music**: The user first loads a file via "Load MP3 File", then plays it.
   - **Storage**: "Get Storage Info" displays the internal state of the `Smartphone`.
5. **Logging**: Every action is recorded in the "Activity Log" at the bottom of the window, providing feedback on what the code is doing.

## Core Concepts Demonstrated

### Multiple Inheritance

Multiple inheritance allows a class to inherit features from more than one base class.
- **In this project**: `Smartphone` inherits from both `Camera` and `MusicPlayer`.
- **Benefit**: It allows the `Smartphone` to be both a "Camera" and a "Music Player" simultaneously, reusing the code from both base classes without duplication.

### Encapsulation (Data Hiding)

Encapsulation is the practice of bundling data and the methods that operate on that data into a single unit (a class) and restricting direct access to some of the object's components.
- **In this project**: The `password` and `storageUsed` variables in the `Smartphone` class are `private`.
- **Implementation**:
  ```cpp
  private:
      QString password;
      int storageUsed;
  ```
- **Benefit**: It prevents external code (like `MainWindow`) from accidentally or maliciously changing the password or storage values directly.

### Access Control

Access control is implemented through public methods that provide a controlled way to interact with private data.
- **In this project**: The `getStorageInfo()` method checks the `phoneUnlocked` state before returning any sensitive data.
- **Implementation**:
  ```cpp
  QString Smartphone::getStorageInfo() {
      if (!phoneUnlocked) {
          return "Phone is locked! Cannot access storage info.";
      }
      // ... return actual info ...
  }
  ```
- **Benefit**: It ensures that sensitive operations and data are only accessible when certain conditions (like being unlocked) are met.
