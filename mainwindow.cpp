#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    myPhone = new Smartphone();
    
    setWindowTitle("Smartphone Simulator - Multiple Inheritance & Encapsulation");
    setGeometry(100, 100, 800, 700);
    
    setupUI();
    createConnections();
    updateUI();
}

MainWindow::~MainWindow()
{
    delete myPhone;
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    
    // Phone Status Section
    QGroupBox *statusGroup = new QGroupBox("Phone Status", this);
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    phoneStateLabel = new QLabel("Status: 🔒 LOCKED", this);
    phoneStateLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: red;");
    statusLayout->addWidget(phoneStateLabel);
    
    mainLayout->addWidget(statusGroup);
    
    // Lock/Unlock Section
    QGroupBox *lockGroup = new QGroupBox("Security", this);
    QVBoxLayout *lockLayout = new QVBoxLayout(lockGroup);
    
    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(new QLabel("Password:", this));
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setPlaceholderText("Enter password (default: 1234)");
    passwordLayout->addWidget(passwordInput);
    lockLayout->addLayout(passwordLayout);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    unlockButton = new QPushButton("🔓 Unlock Phone", this);
    lockButton = new QPushButton("🔒 Lock Phone", this);
    buttonLayout->addWidget(unlockButton);
    buttonLayout->addWidget(lockButton);
    lockLayout->addLayout(buttonLayout);
    
    mainLayout->addWidget(lockGroup);
    
    // Features Section
    QGroupBox *featuresGroup = new QGroupBox("Phone Features", this);
    QVBoxLayout *featuresLayout = new QVBoxLayout(featuresGroup);
    
    QHBoxLayout *featureButtonLayout = new QHBoxLayout();
    takePhotoButton = new QPushButton("📷 Take Photo", this);
    playMusicButton = new QPushButton("🎵 Play Music", this);
    getStorageButton = new QPushButton("📊 Get Storage Info", this);
    
    featureButtonLayout->addWidget(takePhotoButton);
    featureButtonLayout->addWidget(playMusicButton);
    featureButtonLayout->addWidget(getStorageButton);
    featuresLayout->addLayout(featureButtonLayout);
    
    mainLayout->addWidget(featuresGroup);
    
    // Camera Status Section
    QGroupBox *cameraGroup = new QGroupBox("Camera Status", this);
    QVBoxLayout *cameraLayout = new QVBoxLayout(cameraGroup);
    
    cameraStatusLabel = new QLabel("📹 Camera: Available", this);
    cameraStatusLabel->setStyleSheet("font-size: 12px; color: #0066cc;");
    cameraLayout->addWidget(cameraStatusLabel);
    
    photoPreviewLabel = new QLabel("No photo taken yet", this);
    photoPreviewLabel->setStyleSheet("background-color: #f0f0f0; padding: 10px; border: 1px solid #ccc; font-size: 11px; color: #000000; font-weight: bold;");
    photoPreviewLabel->setMinimumHeight(40);
    cameraLayout->addWidget(photoPreviewLabel);
    
    mainLayout->addWidget(cameraGroup);
    
    // Output Log Section
    QGroupBox *logGroup = new QGroupBox("Activity Log", this);
    QVBoxLayout *logLayout = new QVBoxLayout(logGroup);
    
    outputLog = new QTextEdit(this);
    outputLog->setReadOnly(true);
    outputLog->setMaximumHeight(120);
    outputLog->setMinimumHeight(80);
    outputLog->setStyleSheet("background-color: #f0f0f0; font-family: Courier; color: #000;");
    logLayout->addWidget(outputLog);
    
    mainLayout->addWidget(logGroup);
    
    // Info Section
    QGroupBox *infoGroup = new QGroupBox("About This Program", this);
    QVBoxLayout *infoLayout = new QVBoxLayout(infoGroup);
    
    QLabel *infoLabel = new QLabel(
        "This program demonstrates:\n"
        "• Multiple Inheritance (Camera + MusicPlayer)\n"
        "• Encapsulation (Private password & storage)\n"
        "• Access Control (Public methods protect private data)\n\n"
        "Default Password: 1234", this);
    infoLabel->setFont(QFont("Default", 11));
    infoLabel->setPalette(palette());
    infoLabel->setStyleSheet("font-size: 11px;");
    infoLayout->addWidget(infoLabel);
    
    mainLayout->addWidget(infoGroup);
    mainLayout->addStretch();
}

void MainWindow::createConnections()
{
    connect(unlockButton, &QPushButton::clicked, this, &MainWindow::onUnlockClicked);
    connect(lockButton, &QPushButton::clicked, this, &MainWindow::onLockClicked);
    connect(takePhotoButton, &QPushButton::clicked, this, &MainWindow::onTakePhotoClicked);
    connect(playMusicButton, &QPushButton::clicked, this, &MainWindow::onPlayMusicClicked);
    connect(getStorageButton, &QPushButton::clicked, this, &MainWindow::onGetStorageClicked);
}

void MainWindow::onTakePhotoClicked()
{
    outputLog->append("→ Take Photo button clicked");
    
    // Check if camera is available
    if (!myPhone->isCameraAvailable()) {
        outputLog->append("❌ No camera available on this device!");
        cameraStatusLabel->setText("📹 Camera: NOT AVAILABLE");
        cameraStatusLabel->setStyleSheet("font-size: 12px; color: red;");
        return;
    }
    
    // Take the photo
    if (myPhone->takePhoto()) {
        outputLog->append("✓ Photo taken successfully!");
        QString photoPath = myPhone->getLastPhotoPath();
        photoPreviewLabel->setText("📷 Last photo: " + photoPath);
    } else {
        outputLog->append("❌ Failed to take photo!");
    }
    
    updateUI();
}

void MainWindow::onPlayMusicClicked()
{
    outputLog->append("→ Play Music button clicked");
    myPhone->playMusic();
    updateUI();
}

void MainWindow::onUnlockClicked()
{
    QString password = passwordInput->text();
    if (password.isEmpty()) {
        outputLog->append("❌ Please enter a password!");
        return;
    }
    
    outputLog->append("→ Attempting to unlock with password: " + password);
    bool success = myPhone->unlockPhone(password);
    if (success) {
        outputLog->append("✓ Phone unlocked successfully!");
    } else {
        outputLog->append("✗ Incorrect password!");
    }
    passwordInput->clear();
    updateUI();
}

void MainWindow::onLockClicked()
{
    outputLog->append("→ Lock Phone button clicked");
    myPhone->lockPhone();
    updateUI();
}

void MainWindow::onGetStorageClicked()
{
    outputLog->append("→ Get Storage Info button clicked");
    QString storageInfo = myPhone->getStorageInfo();
    if (myPhone->isPhoneUnlocked()) {
        outputLog->append("✓ Storage Info:\n" + storageInfo);
    } else {
        outputLog->append("✗ " + storageInfo);
    }
    updateUI();
}

void MainWindow::updateUI()
{
    if (myPhone->isPhoneUnlocked()) {
        phoneStateLabel->setText("Status: 🔓 UNLOCKED");
        phoneStateLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: green;");
        takePhotoButton->setEnabled(true);
        playMusicButton->setEnabled(true);
        getStorageButton->setEnabled(true);
    } else {
        phoneStateLabel->setText("Status: 🔒 LOCKED");
        phoneStateLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: red;");
        takePhotoButton->setEnabled(false);
        playMusicButton->setEnabled(false);
        getStorageButton->setEnabled(false);
    }
}