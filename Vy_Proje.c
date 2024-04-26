/* 
ESKİ YAPİ

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
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct SongType {
    int songType_id;
    char* songType;
} SongType;

typedef struct Singer {
    int singer_id;
    char* singerName;
    char* singerSurname;
    struct Song* song; 
} Singer;

typedef struct Song {
    int song_id;
    int listenCount;
    struct Singer singer; 
    struct SongType songType; 
} Song;











