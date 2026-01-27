#include "musicplayer.h"
#include <QDebug>

MusicPlayer::MusicPlayer() : isPlaying(false), currentSong("None")
{
    qDebug() << "MusicPlayer initialized";
}

MusicPlayer::~MusicPlayer()
{
    qDebug() << "MusicPlayer destroyed";
}

void MusicPlayer::playMusic()
{
    isPlaying = true;
    currentSong = "Summer Vibes.mp3";
    qDebug() << "🎵 Now playing: " << currentSong;
}