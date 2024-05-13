#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Şarkı yapısı
struct Sarki
{
    int sarkiId;
    char sarkiAdi[31];
    Sarki *next;
};

typedef struct Sarki Sarki;
typedef Sarki *SarkiPtr;

// Sanatçı yapısı
struct Sanatci
{
    int sanatciId;
    char sanatciAdi[31];
    Sanatci *next;
};

typedef struct Sanatci Sanatci;
typedef Sanatci *SanatciPtr;

SarkiPtr sarkiBaslangic = NULL;
SanatciPtr sanatciBaslangic = NULL;

// Yeni bir şarkıyı bağlı listeye ekler
void sarkiEkle(char sarkiAdi[],int sarkiId)
{
    SarkiPtr yeniSarki = (SarkiPtr)malloc(sizeof(Sarki));
    yeniSarki->sarkiId=sarkiId;
    strcpy(yeniSarki->sarkiAdi, sarkiAdi);

    yeniSarki->next = NULL;

    if (sarkiBaslangic == NULL)
    {
        sarkiBaslangic = yeniSarki;
    }
    else
    {
        SarkiPtr temp = sarkiBaslangic;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = yeniSarki;
    }

    // Dosyaya da ekleyelim
    FILE *dosya = fopen("sarki.txt", "a");
    if (dosya == NULL)
    {
        fprintf(stderr, "Dosya acilamadi!");
        exit(1);
    }
    fprintf(dosya, "%s\n", sarkiAdi);
    fclose(dosya);
}

// Yeni bir sanatçıyı bağlı listeye ekler
void sanatciEkle(char sanatciAdi[])
{
    SanatciPtr yeniSanatci = (SanatciPtr)malloc(sizeof(Sanatci));
    strcpy(yeniSanatci->sanatciAdi, sanatciAdi);
    yeniSanatci->next = NULL;

    if (sanatciBaslangic == NULL)
    {
        sanatciBaslangic = yeniSanatci;
    }
    else
    {
        SanatciPtr temp = sanatciBaslangic;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = yeniSanatci;
    }

    // Dosyaya da ekleyelim
    FILE *dosya = fopen("sanatci.txt", "a");
    if (dosya == NULL)
    {
        fprintf(stderr, "Dosya acilamadi!");
        exit(1);
    }
    fprintf(dosya, "%s\n", sanatciAdi);
    fclose(dosya);
}

// Şarkıları listeler
void sarkilariListele()
{
    SarkiPtr temp = sarkiBaslangic;
    int i = 1;
    printf("\nSarkilar:\n");
    while (temp != NULL)
    {
        printf("%d) %s\n", i++, temp->sarkiAdi);
        temp = temp->next;
    }
}

// Sanatçıları listeler
void sanatcilariListele()
{
    SanatciPtr temp = sanatciBaslangic;
    int i = 1;
    printf("\nSanatcilar:\n");
    while (temp != NULL)
    {
        printf("%d) %s\n", i++, temp->sanatciAdi);
        temp = temp->next;
    }
}

// Şarkı işlemlerini gerçekleştirir
void sarkiIslem()
{
    int islem;
    char veri[MAX_SIZE];

    do
    {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sarki Ekleme\n");
        printf("2 - Sarkilari Listeleme\n");
        printf("3 - Cikis\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem)
        {
        case 1:
            printf("Bir sarki girin: ");
            fgets(veri, MAX_SIZE, stdin);
            sarkiEkle(veri);
            printf("Sarki eklendi.\n");
            break;

        case 2:
            sarkilariListele();
            break;

        case 3:
            printf("Programdan cikiliyor...\n");
            break;

        default:
            printf("Gecersiz islem!\n");
            break;
        }
    } while (islem != 3);
}

// Sanatçı işlemlerini gerçekleştirir
void sanatciIslem()
{
    int islem;
    char veri[MAX_SIZE];

    do
    {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sanatci Ekleme\n");
        printf("2 - Sanatci Listeleme\n");
        printf("3 - Cikis\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem)
        {
        case 1:
            printf("Bir sanatci girin: ");
            fgets(veri, MAX_SIZE, stdin);
            sanatciEkle(veri);
            printf("Sanatci eklendi.\n");
            break;

        case 2:
            sanatcilariListele();
            break;

        case 3:
            printf("Programdan cikiliyor...\n");
            break;

        default:
            printf("Gecersiz islem!\n");
            break;
        }
    } while (islem != 3);
}

int main()
{
    char secim;
    FILE *sarkiDosya;
    FILE *sanatciDosya;

    // Dosyaları aç
    sarkiDosya = fopen("sarkilar.txt", "a+");
    sanatciDosya = fopen("sanatcilar.txt", "a+");
    if (sarkiDosya == NULL || sanatciDosya == NULL)
    {
        fprintf(stderr, "Dosya acilamadi!");
        exit(1);
    }

    // Dosyalardan şarkıları ve sanatçıları oku
    char sarki[MAX_SIZE];
    while (fgets(sarki, MAX_SIZE, sarkiDosya) != NULL)
    {
        sarkiEkle(sarki);
    }

    char sanatci[MAX_SIZE];
    while (fgets(sanatci, MAX_SIZE, sanatciDosya) != NULL)
    {
        sanatciEkle(sanatci);
    }

    do
    {
        printf("   =Muzik Veri Tabani Sistemi=\n");
        printf("------------------------------------\n");
        printf("(1) - Sarki Islemleri\n");
        printf("(2) - Sanatci Islemleri\n");
        printf("(3) - Cikis\n");
        printf("------------------------------------\n");
        printf("Seciminiz:");
        scanf(" %c", &secim); // Kullanıcıdan seçimi alınmaktadır.
        getchar();           // Buffer boşaltılmaktadır.
        switch (secim)
        {
        case '1':
            printf("\n-Sarki Islemlerinden Secim Yap-\n");
            printf("----------------\n\n");
            sarkiIslem();
            printf("\n");
            break;
        case '2':
            printf("\n-Sanatci Islemlerinden Secim Yap-\n");
            printf("-------------\n\n");
            sanatciIslem();
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

    // Dosyaları kapat
    fclose(sarkiDosya);
    fclose(sanatciDosya);

    return 0;
}
