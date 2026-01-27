#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QString>

class MusicPlayer
{
public:
    MusicPlayer();
    virtual ~MusicPlayer();
    
    void playMusic();

protected:
    bool isPlaying;
    QString currentSong;
};

#endif // MUSICPLAYER_H