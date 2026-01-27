#include "musicplayer.h"
#include <QDebug>
#include <QFileInfo>

MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent), isPlaying(false), currentSong("None")
{
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    
    qDebug() << "MusicPlayer initialized with audio support";
}

MusicPlayer::~MusicPlayer()
{
    if (mediaPlayer) {
        mediaPlayer->stop();
        delete mediaPlayer;
    }
    if (audioOutput) {
        delete audioOutput;
    }
    qDebug() << "MusicPlayer destroyed";
}

bool MusicPlayer::loadMusic(const QString &filePath)
{
    if (filePath.isEmpty()) {
        qDebug() << "❌ No file provided";
        return false;
    }
    
    // Check if file exists and is an audio file
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        qDebug() << "❌ File not found: " << filePath;
        return false;
    }
    
    QString suffix = fileInfo.suffix().toLower();
    if (suffix != "mp3" && suffix != "wav" && suffix != "flac" && suffix != "ogg") {
        qDebug() << "❌ Unsupported audio format: " << suffix;
        return false;
    }
    
    currentFilePath = filePath;
    currentSong = fileInfo.fileName();
    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    
    qDebug() << "✓ Audio file loaded: " << currentSong;
    return true;
}

bool MusicPlayer::playMusic()
{
    if (currentFilePath.isEmpty()) {
        qDebug() << "❌ No music file loaded";
        return false;
    }
    
    mediaPlayer->play();
    isPlaying = true;
    qDebug() << "🎵 Now playing: " << currentSong;
    return true;
}

void MusicPlayer::stopMusic()
{
    if (mediaPlayer) {
        mediaPlayer->stop();
        isPlaying = false;
        qDebug() << "⏹️ Music stopped";
    }
}

bool MusicPlayer::isPlayingNow() const
{
    return mediaPlayer && mediaPlayer->playbackState() == QMediaPlayer::PlayingState;
}

QString MusicPlayer::getCurrentSong() const
{
    return currentSong;
}