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

### Multiple Inheritance: The "Why"

Multiple inheritance is a powerful C++ feature where a class can derive from more than one base class.

- **In this project**: The `Smartphone` class is defined as `class Smartphone : public Camera, public MusicPlayer`.
- **Why use it here?**:
    - **Functional Composition**: A smartphone is not *just* a camera or *just* a music player; it is both. Multiple inheritance allows us to compose the `Smartphone` class by bringing in the distinct behaviors of a `Camera` and a `MusicPlayer` into a single, unified object.
    - **Code Reusability**: Instead of rewriting photo-taking logic and music-playing logic inside the `Smartphone` class, we "borrow" it from classes that already do those jobs well. This avoids code duplication and makes the system easier to maintain.
    - **Natural Modeling**: It mirrors real-world relationships. A modern phone is an evolution that combined several standalone devices into one.

### Encapsulation & "Private Mode": The "Why"

Encapsulation involves hiding the internal state of an object and requiring all interaction to be performed through a well-defined interface. In C++, this is achieved using the `private` access modifier.

- **In this project**: Sensitive data like `password`, `storageUsed`, and `phoneUnlocked` are kept in **Private Mode**.
- **Implementation**:
  ```cpp
  private:
      QString password;
      int storageUsed;
      bool phoneUnlocked;
  ```
- **Why use Private members?**:
    - **Data Integrity**: If the `password` were `public`, any part of the program (like a bug in the GUI) could change the password without going through a check. By making it `private`, we ensure that only the `Smartphone` class itself can modify it.
    - **Security Simulation**: In a real phone, you wouldn't want any random "app" to be able to see or change your lock-screen password. Keeping it private simulates this security boundary.
    - **Abstraction**: The user of the `Smartphone` class doesn't need to know *how* the storage is calculated or *where* the password is stored; they just need to call `unlockPhone()` or `getStorageInfo()`.

### Access Control: The "Why"

Access control works hand-in-hand with encapsulation to provide "Gatekeeping" for the object's features.

- **In this project**: Even though `getStorageInfo()` is a `public` method, it has internal logic that restricts access based on the phone's state.
- **Implementation**:
  ```cpp
  QString Smartphone::getStorageInfo() {
      if (!phoneUnlocked) {
          return "Phone is locked! Cannot access storage info.";
      }
      // Actual sensitive data is only processed here...
  }
  ```
- **Why implement this?**:
    - **State Management**: It ensures the object behaves consistently. A "Locked" phone should not be able to perform "Unlocked" actions.
    - **Controlled Exposure**: It allows the programmer to define exactly *under what conditions* private data can be viewed or modified. This is the essence of "Information Hiding" in software engineering.
