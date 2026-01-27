#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QObject>

class MusicPlayer : public QObject
{
    Q_OBJECT
public:
    MusicPlayer(QObject *parent = nullptr);
    virtual ~MusicPlayer();
    
    bool loadMusic(const QString &filePath);
    bool playMusic();
    void stopMusic();
    bool isPlayingNow() const;
    QString getCurrentSong() const;

protected:
    bool isPlaying;
    QString currentSong;
    QString currentFilePath;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};

#endif // MUSICPLAYER_H