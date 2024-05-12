
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sarkiEkle(); // Fonksiyonların prototipleri deklare edilmektedir.
void sanatciEkle();

struct Sarki // Şarkı yapısı tanımlanmaktadır.
{
    char sarkiAdi[31];
    int sarkiNumarasi;
};

struct Sanatci // Sanatçı yapısı tanımlanmaktadır.
{
    char sanatciAdi[31];
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
        printf("(3) - Cikis\n");
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
                printf("\nMuzik Veri Tabani Sisteminden Cikmaktasiniz...\n");
                break;
            default:
                printf("\nBoyle Bir Islem Seceneginiz Bulunmamaktadir. Yeniden Secim Yapiniz.\n\n");
                break;
        }
    } while (secim != '3'); // Kullanıcının 3 girmesiyle döngü sona ermekte ve programdan çıkılmaktadır.

    return 0;
}

void sarkiEkle() // Sisteme şarkı ekleme fonksiyonu.
{
    FILE *sarkiPtr;
    struct Sarki girilenSarki;
    int karakterSayisi, sarkiNo;
    int dosyaUzunlugu;

    sarkiPtr = fopen("sarkilar.txt", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
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

    sanatciPtr = fopen("sanatcilar.txt", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
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