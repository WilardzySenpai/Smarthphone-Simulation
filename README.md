# Smartphone Simulator - Qt Application

A C++ Qt application that demonstrates **Multiple Inheritance** and **Encapsulation** concepts through an interactive smartphone simulator.

## Program Features

### Class Hierarchy
- **Camera** (Base Class): Handles photo functionality
- **MusicPlayer** (Base Class): Handles music playback
- **Smartphone** (Derived Class): Combines both features via multiple inheritance

### Key Concepts Demonstrated

1. **Multiple Inheritance**
   - `Smartphone` inherits from both `Camera` and `MusicPlayer`
   - Combines functionality from two parent classes

2. **Encapsulation (Data Hiding)**
   - Private members: `password`, `storageUsed`, `totalStorage`, `phoneUnlocked`
   - Public methods provide controlled access: `unlockPhone()`, `getStorageInfo()`
   - Sensitive data is protected from direct access

3. **Access Control**
   - Phone features are disabled when locked
   - Storage information only accessible when unlocked
   - Password protection on unlock functionality

## Building the Application

### Prerequisites
- Qt 6.x (with Qt Multimedia module for audio support)
- GCC compiler (MinGW on Windows recommended)
- qmake build tool

### Build Steps

#### Windows (Command Line)
```bash
cd C:\path\to\Smartphone
qmake SmartphoneSimulator.pro
mingw32-make clean
mingw32-make
.\release\SmartphoneSimulator.exe
```

#### Linux/macOS (Command Line)
```bash
cd /path/to/smartphone_app
qmake SmartphoneSimulator.pro
make clean
make
./SmartphoneSimulator
```

#### Qt Creator (All Platforms)
1. Open Qt Creator
2. File → Open File or Project
3. Select `SmartphoneSimulator.pro`
4. Click "Configure Project"
5. Press Ctrl+B to build
6. Press Ctrl+R to run

## Usage

### Default Password
`1234`

### Features

1. **Take Photo** 📷
   - Requires phone to be unlocked
   - Detects if camera is available on the device
   - Takes actual photos and saves them to Pictures folder with timestamps
   - Photos are named: `photo_YYYY-MM-DD_HH-MM-SS_#.jpg`
   - Shows photo save path in Camera Status section
   - Demonstrates camera hardware detection

2. **Play Music** 🎵
   - Requires phone to be unlocked
   - Click "📁 Load MP3 File" to select an audio file from your computer
   - Supports MP3, WAV, FLAC, and OGG formats
   - Click "🎵 Play Music" to play the loaded audio
   - Click "⏹️ Stop Music" to stop playback
   - Music Status section shows currently loaded/playing song
   - Demonstrates inherited MusicPlayer functionality with real audio playback

3. **Security** 🔐
   - Enter password (default: 1234)
   - Click "🔓 Unlock Phone" to gain access
   - Features are disabled when locked
   - Click "🔒 Lock Phone" to re-lock
   - Password verification with feedback

4. **Storage Info** 📊
   - Only accessible when phone is unlocked
   - Shows storage usage in MB and percentage
   - Demonstrates access control

5. **Camera Status** 📹
   - Displays if camera is available on device
   - Shows last photo taken with file path
   - Real-time camera availability detection

6. **Activity Log** 📋
   - Displays all actions and messages
   - Shows success/failure of operations
   - Shows detailed information about photo and music operations
   - Demonstrates encapsulation in action

## Project Structure

```
smartphone_app/
├── camera.h              # Camera base class header
├── camera.cpp            # Camera implementation with photo capture
├── musicplayer.h         # MusicPlayer base class header
├── musicplayer.cpp       # MusicPlayer implementation with Qt Multimedia
├── smartphone.h          # Smartphone derived class header
├── smartphone.cpp        # Smartphone derived class implementation
├── mainwindow.h          # GUI window header with Qt Widgets
├── mainwindow.cpp        # GUI window implementation
├── main.cpp              # Application entry point
├── SmartphoneSimulator.pro # Qt project file with multimedia module
└── README.md             # This file
```

## Code Examples

### Multiple Inheritance in Action
```cpp
class Smartphone : public Camera, public MusicPlayer
{
    // Inherits takePhoto() from Camera
    // Inherits playMusic() from MusicPlayer
    // Adds own private data and access methods
};
```

### Encapsulation Example
```cpp
// Private members - hidden from outside
private:
    QString password;
    int storageUsed;

// Public method - controlled access
public:
    QString getStorageInfo()
    {
        if (!phoneUnlocked) {
            return "Phone is locked!";
        }
        // Return storage info only if unlocked
    }
```

## Learning Outcomes

Students will understand:
- ✓ How to implement multiple inheritance in C++
- ✓ How to use private members for data protection
- ✓ How public methods provide controlled access to private data
- ✓ Real-world application of encapsulation concepts
- ✓ Qt framework basics (signals, slots, layouts, widgets)
- ✓ Qt Multimedia library for audio playback
- ✓ File I/O operations in Qt
- ✓ Hardware detection and capability checking
- ✓ User authentication and access control patterns

## Troubleshooting

### "Cannot find -lQt5Core" Error
- Ensure Qt is properly installed
- Check Qt path in Qt Creator: Tools → Options → Kits

### Application won't compile
- Check C++ standard is set to C++17 or higher
- Ensure all .pro file paths are correct
- Clean and rebuild: Build → Clean All → Build

### GUI doesn't appear
- Check that Qt libraries are in system PATH
- Try running from Qt Creator instead of command line

## Future Enhancements

Possible extensions to the project:
- Add battery level system
- Implement photo gallery/slideshow
- Create music playlist with queue management
- Add volume control for audio
- Implement voice recording functionality
- Add contacts and call history system
- Create settings/preferences system
- Add notification/alert system
- Implement SMS/messaging features
- Add timestamp and metadata to photos
- Real-time audio visualization

## License

Educational use only.