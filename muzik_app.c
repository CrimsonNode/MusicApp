#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sarki_Ekle.c"
#include "album_Sanatcisi_Listele.c"
#include "sarki_Albumu_Listele.c"
#include "album_Ekle.c"
#include "sanatci_Ekle.c"


void sarkiEkle(); // Fonksiyonların prototipleri deklare edilmektedirrr.
void sanatciEkle();
void albumEkle();
void sarkiAlbumuListele();
void albumSanatcisiListele();

struct Sarki // Şarkı yapısı tanımlanmaktadır.
{
    char sarkiAdi[31];
    int sarkiNumarasi;
    int albumKodu;
};

struct Sanatci // Sanatçı yapısı tanımlanmaktadır.
{
    char sanatciAdi[31];
    int sanatciNumarasi;
};

struct Album // Albüm yapısı tanımlanmaktadır.
{
    char albumAdi[31];
    int albumKodu;
    int sanatciNumarasi;
};

int main()
{
    char secim;
    do
    {
        printf("   =Muzik Veri Tabani Sistemi=\n");
        printf("------------------------------------\n");
        printf("(1) - Sarki Ekle\n");
        printf("(2) - Sanatci Ekle\n");
        printf("(3) - Album Ekle\n");
        printf("(4) - Sarki Albumunu Listele\n");
        printf("(5) - Album Sanatcisini Listele\n");
        printf("(6) - Cikis\n");
        printf("------------------------------------\n");
        printf("Seciminiz:");
        scanf(" %c", &secim); // Kullanıcıdan seçimi alınmaktadır.
        fflush(stdin); // Buffer boşaltılmaktadır.
        switch (secim)
        {
            case '1':
                printf("\n-Sarki Ekleme-\n");
                printf("----------------\n\n");
                sarkiEkle();
                printf("\n");
                break;
            case '2':
                printf("\n-Sanatci Ekleme-\n");
                printf("-------------\n\n");
                sanatciEkle();
                printf("\n");
                break;
            case '3':
                printf("\n-Album Ekleme-\n");
                printf("--------------------\n\n");
                albumEkle();
                printf("\n");
                break;
            case '4':
                printf("\n-Sarki Albumunu Listele-\n");
                printf("----------------------------\n\n");
                sarkiAlbumuListele();
                printf("\n");
                break;
            case '5':
                printf("\n-Album Sanatcisini Listele-\n");
                printf("--------------------------------\n\n");
                albumSanatcisiListele();
                printf("\n");
                break;
            case '6':
                printf("\nMuzik Veri Tabani Sisteminden Cikmaktasiniz...\n");
                break;
            default:
                printf("\nBoyle Bir Islem Seceneginiz Bulunmamaktadir. Yeniden Secim Yapiniz.\n\n");
                break;
        }
    } while (secim != '6'); // Kullanıcının 6 girmesiyle döngü sona ermekte ve programdan çıkılmaktadır.

    return 0;
}




