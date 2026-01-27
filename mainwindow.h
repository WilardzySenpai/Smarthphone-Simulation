#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include "smartphone.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTakePhotoClicked();
    void onPlayMusicClicked();
    void onUnlockClicked();
    void onLockClicked();
    void onGetStorageClicked();
    void updateUI();

private:
    void setupUI();
    void createConnections();
    
    // UI Components
    QLabel *statusLabel;
    QLineEdit *passwordInput;
    QPushButton *unlockButton;
    QPushButton *lockButton;
    QPushButton *takePhotoButton;
    QPushButton *playMusicButton;
    QPushButton *getStorageButton;
    QTextEdit *outputLog;
    QLabel *phoneStateLabel;
    
    // Business Logic
    Smartphone *myPhone;
};

#endif // MAINWINDOW_H