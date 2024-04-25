#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int singer_id;
    char* singerName;
    char* singerSurname; 
    Song song;
    char* song;
}Singer;

typedef struct{
    int song_id;
    int listenCount;
    Singer singer;
    SongType songtype;
    char* song_type;
    char* singer_name;
}Song;


typedef struct{
    int songType_id;
    char* songType;
}SongType;








