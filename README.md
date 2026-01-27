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
- Qt 5.15 or higher (or Qt 6.x)
- GCC/Clang compiler (Linux/macOS) or MSVC (Windows)
- CMake or Qt Creator

### Build Steps

#### Option 1: Using Qt Creator (Recommended)
1. Open Qt Creator
2. File → Open File or Project
3. Select `SmartphoneSimulator.pro`
4. Configure with your Qt Kit
5. Click "Build" (Ctrl+B)
6. Click "Run" (Ctrl+R)

#### Option 2: Command Line (Linux/macOS)
```bash
cd /path/to/smartphone_app
qmake SmartphoneSimulator.pro
make
./SmartphoneSimulator
```

#### Option 3: Command Line (Windows)
```bash
cd \path\to\smartphone_app
qmake SmartphoneSimulator.pro
mingw32-make  # or nmake if using MSVC
SmartphoneSimulator.exe
```

## Usage

### Default Password
`1234`

### Features

1. **Take Photo**
   - Requires phone to be unlocked
   - Increments photo counter
   - Shows in activity log

2. **Play Music**
   - Requires phone to be unlocked
   - Shows current playing song
   - Demonstrates inherited functionality

3. **Security**
   - Enter password (default: 1234)
   - Click "Unlock Phone" to gain access
   - Features are disabled when locked
   - Click "Lock Phone" to re-lock

4. **Storage Info**
   - Only accessible when phone is unlocked
   - Shows storage usage in MB and percentage
   - Demonstrates access control

5. **Activity Log**
   - Displays all actions and messages
   - Shows success/failure of operations
   - Demonstrates encapsulation in action

## Project Structure

```
smartphone_app/
├── camera.h              # Camera base class header
├── camera.cpp            # Camera base class implementation
├── musicplayer.h         # MusicPlayer base class header
├── musicplayer.cpp       # MusicPlayer base class implementation
├── smartphone.h          # Smartphone derived class header
├── smartphone.cpp        # Smartphone derived class implementation
├── mainwindow.h          # GUI window header
├── mainwindow.cpp        # GUI window implementation
├── main.cpp              # Application entry point
├── SmartphoneSimulator.pro # Qt project file
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
- Implement file storage simulation
- Add contacts and call history
- Create settings/preferences system
- Add notification system
- Implement call/message features

## License

Educational use only.