#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sarkiEkle(); // Fonksiyonların prototipleri deklare edilmektedir.
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

void sarkiEkle() // Sisteme şarkı ekleme fonksiyonu.
{
    FILE *sarkiPtr;
    struct Sarki girilenSarki;
    int karakterSayisi, sarkiNo;
    int dosyaUzunlugu;

    sarkiPtr = fopen("sarkilar.bin", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
    if (sarkiPtr == NULL)
    {
        printf("sarkilar.bin Dosyasi Acilamadi...\n");
        exit(0); // Programdan çıkılmaktadır.
    }

    fseek(sarkiPtr, 0, SEEK_END); // İmleç dosyanın sonuna konumlandırılır.
    dosyaUzunlugu = ftell(sarkiPtr); // Dosyanın uzunluğu hesaplanmaktadır.

    if (dosyaUzunlugu == 0) // Dosya boş ise ilk şarkıya şarkı numarası olarak 1 atanır.
    {
        sarkiNo = 1;
    }
    else
    {
        fseek(sarkiPtr, -sizeof(struct Sarki), SEEK_END); // Dosyanın sonundaki son şarkıyı okur.
        struct Sarki sonSarki;
        fread(&sonSarki, sizeof(struct Sarki), 1, sarkiPtr); // Son şarkıyı okur.
        sarkiNo = sonSarki.sarkiNumarasi + 1; // Yeni şarkı numarası oluşturulmaktadır.
    }

    if (sarkiNo > 100)
    {
        printf("Sistemde 100 Sarki Kayitlidir. Yeni Sarki Ekleyemessiniz!\n");
    }
    else // Şarkı eklemeye devam etmek için if yapı dışına çıkılır.
    {
        printf("Sarki Adini Giriniz:");
        gets(girilenSarki.sarkiAdi); // Kullanıcıdan şarkı adını alınmaktadır.
        fflush(stdin);

        girilenSarki.sarkiNumarasi = sarkiNo; // Şarkı numarası atanır.
        printf("Sarki %d Sisteme Eklenmistir!\n", sarkiNo);

        fwrite(&girilenSarki, sizeof(struct Sarki), 1, sarkiPtr); // Şarkı dosyaya yazılır.
    }

    fclose(sarkiPtr); // Dosya kapatılmaktadır.
}

void sanatciEkle() // Sisteme sanatçı ekleme fonksiyonu.
{
    FILE *sanatciPtr;
    struct Sanatci girilenSanatci;
    int karakterSayisi, sanatciNo;
    int dosyaUzunlugu;

    sanatciPtr = fopen("sanatcilar.bin", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
    if (sanatciPtr == NULL)
    {
        printf("sanatcilar.bin Dosyasi Acilamadi...\n");
        exit(0); // Programdan çıkılmaktadır.
    }

    fseek(sanatciPtr, 0, SEEK_END); // İmleç dosyanın sonuna konumlandırılır.
    dosyaUzunlugu = ftell(sanatciPtr); // Dosyanın uzunluğu hesaplanmaktadır.

    if (dosyaUzunlugu == 0) // Dosya boş ise ilk sanatçı numarası 1 olur.
    {
        sanatciNo = 1;
    }
    else
    {
        fseek(sanatciPtr, -sizeof(struct Sanatci), SEEK_END); // Dosyanın sonundaki son sanatçıyı okur.
        struct Sanatci sonSanatci;
        fread(&sonSanatci, sizeof(struct Sanatci), 1, sanatciPtr); // Son sanatçıyı okur.
	    sanatciNo = sonSanatci.sanatciNumarasi + 1; // Yeni sanatçı numarası oluşturulmaktadır.
    }

    if (sanatciNo > 100)
    {
        printf("Sistemde 100 Sanatci Kayitlidir. Yeni Sanatci Ekleyemessiniz!\n");
    }
    else // Sanatçı eklemeye devam etmek için else dışına çıkılır.
    {
        printf("Sanatci Adini Giriniz:");
        gets(girilenSanatci.sanatciAdi); // Kullanıcıdan sanatçı adı alınmaktadır.
        fflush(stdin);

        girilenSanatci.sanatciNumarasi = sanatciNo; // Sanatçı numarası atanır.
        printf("Sanatci %d Sisteme Eklenmistir!\n", sanatciNo);

        fwrite(&girilenSanatci, sizeof(struct Sanatci), 1, sanatciPtr); // Sanatçı dosyaya yazılır.
    }

    fclose(sanatciPtr); // Dosya kapatılmaktadır.
}

void albumEkle() // Sisteme albüm ekleme fonksiyonu.
{
    FILE *albumPtr;
    struct Album girilenAlbum;
    int karakterSayisi, albumKod;
    int sanatciNo;
    int dosyaUzunluğu;
    albumPtr = fopen("albumler.bin", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
    if (albumPtr == NULL)
    {
        printf("albumler.bin Dosyasi Acilamadi...\n");
        exit(0); // Programdan çıkılmaktadır.
    }

    fseek(albumPtr, 0, SEEK_END); // İmleç dosyanın sonuna konumlandırılır.
    dosyaUzunluğu = ftell(albumPtr); // Dosyanın uzunluğu hesaplanmaktadır.

    if (dosyaUzunluğu == 0) // Dosya boş ise ilk albüm kodu 1001 olur.
    {
        albumKod = 1001;
    }
    else
    {
        fseek(albumPtr, -sizeof(struct Album), SEEK_END); // Dosyanın sonundaki son albümü okur.
        struct Album sonAlbum;
        fread(&sonAlbum, sizeof(struct Album), 1, albumPtr); // Son albümü okur.
        albumKod = sonAlbum.albumKodu + 1; // Yeni albüm kodu oluşturulmaktadır.
    }

    if (albumKod > 1020)
    {
        printf("Sistemde 20 Albüm Kayitlidir. Yeni Album Ekleyemessiniz!\n");
    }
    else // Albüm eklemeye devam etmek için if yapı dışına çıkılır.
    {
        printf("Album Adini Giriniz:");
        gets(girilenAlbum.albumAdi); // Kullanıcıdan albüm adı alınmaktadır.
        fflush(stdin);

        printf("Sanatci Numarasini Giriniz:");
        scanf("%d", &sanatciNo);
        fflush(stdin);

        girilenAlbum.albumKodu = albumKod; // Albüm kodu atanır.
        girilenAlbum.sanatciNumarasi = sanatciNo; // Albümün sanatçı numarası atanır.
        printf("Album %d Sisteme Eklenmistir!\n", albumKod);

        fwrite(&girilenAlbum, sizeof(struct Album), 1, albumPtr); // Albüm dosyaya yazılır.
    }

    fclose(albumPtr); // Dosya kapatılmaktadır.
}

void sarkiAlbumuListele() // Şarkıların hangi albümde olduğunu listeleyen fonksiyon.
{
    FILE *sarkiPtr, *albumPtr;
    struct Sarki okunanSarki;
    struct Album okunanAlbum;
    int sarkiNo;
    sarkiPtr = fopen("sarkilar.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (sarkiPtr == NULL)
    {
        printf("sarkilar.bin Dosyasi Acilamadi...\n");
        exit(0); // Programdan çıkılmaktadır.
    }

    albumPtr = fopen("albumler.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (albumPtr == NULL)
    {
        printf("albumler.bin Dosyasi Acilamadi...\n");
        exit(0);
    }

    printf("Albumunu Ogrenmek Istediginiz Sarki Numarasini Giriniz:");
    scanf("%d", &sarkiNo);
    fflush(stdin);

    fseek(sarkiPtr, (sarkiNo - 1) * sizeof(struct Sarki), SEEK_SET);
    fread(&okunanSarki, sizeof(struct Sarki), 1, sarkiPtr);

    if (sarkiNo != okunanSarki.sarkiNumarasi)
    {
        printf("Bu numarada bir sarki bulunmuyor.\n");
    }
    else
    {
        fseek(albumPtr, (okunanSarki.albumKodu - 1001) * sizeof(struct Album), SEEK_SET);
        fread(&okunanAlbum, sizeof(struct Album), 1, albumPtr);

        printf("Sarki Numarasi  : %d\n", okunanSarki.sarkiNumarasi);
        printf("Sarki Adi       : %s\n\n", okunanSarki.sarkiAdi);
        printf("Album Kodu      : %d\n", okunanAlbum.albumKodu);
        printf("Album Adi       : %s\n\n", okunanAlbum.albumAdi);
    }

    fclose(sarkiPtr); // Dosya kapatılmaktadır.
    fclose(albumPtr);
}

void albumSanatcisiListele() // Bir albümün hangi sanatçıya ait olduğunu gösteren fonksiyon.
{
    FILE *sanatciPtr, *albumPtr;
    struct Sanatci okunanSanatci;
    struct Album okunanAlbum;
    int albumKod;
    albumPtr = fopen("albumler.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (albumPtr == NULL)
    {
        printf("albumler.bin Dosyasi Acilamadi...\n");
        exit(0);
    }

    sanatciPtr = fopen("sanatcilar.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (sanatciPtr == NULL)
    {
        printf("sanatcilar.bin Dosyasi Acilamadi...\n");
        exit(0);
    }

    printf("Sanatcisini Ogrenmek Istediginiz Album Kodunu Giriniz:");
    scanf("%d", &albumKod);
    fflush(stdin);

    fseek(albumPtr, (albumKod - 1001) * sizeof(struct Album), SEEK_SET);
    fread(&okunanAlbum, sizeof(struct Album), 1, albumPtr);

    fseek(sanatciPtr, (okunanAlbum.sanatciNumarasi - 1) * sizeof(struct Sanatci), SEEK_SET);
    fread(&okunanSanatci, sizeof(struct Sanatci), 1, sanatciPtr);
    printf("Album Kodu      : %d\n", okunanAlbum.albumKodu);
    printf("Album Adi       : %s\n\n", okunanAlbum.albumAdi);
    printf("Sanatci Numarasi: %d\n", okunanSanatci.sanatciNumarasi);
    printf("Sanatci Adi     : %s\n\n", okunanSanatci.sanatciAdi);

    fclose(albumPtr); // Dosyalar kapatılmaktadır.
    fclose(sanatciPtr);
}

