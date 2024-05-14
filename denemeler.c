#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100



// Şarkı yapısı
struct Sarki
{
    int sarkiId;
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    struct Sarki *next;
};

typedef struct Sarki Sarki;
typedef Sarki *SarkiPtr;

SarkiPtr sarkiBaslangic = NULL;


void dosyayaYaz(char sarkiAdi[], char sanatciAdi[]){
    
    // Dosyaya da ekleyelim
    FILE *dosya = fopen("sarki.txt", "a");
    if (dosya == NULL)
    {
        fprintf(stderr, "Dosya acilamadi!");
        exit(1);
    }
    fprintf(dosya, "%s%s", sarkiAdi,sanatciAdi);
    fclose(dosya);
}

void sarkiSil(int sarkiId) {
    if (sarkiBaslangic == NULL) {
        printf("Liste bos.\n");
        return;
    }

    SarkiPtr temp = sarkiBaslangic;
    SarkiPtr onceki = NULL;
    int sayac = 0;
    
    if (temp != NULL && temp->sarkiId == sarkiId) {
        sarkiBaslangic = temp->next;
        free(temp);
        printf("Sarki silindi: %d\n", sarkiId);
        return;
    }

    // Silinecek düğümün aranması
    while (temp != NULL && temp->sarkiId != sarkiId) {
        onceki = temp;
        temp = temp->next;
        sayac++;
    }

    // Eğer şarkı bulunamazsa
    if (temp == NULL) {
        printf("Sarki bulunamadi: %d\n", sarkiId);
        return;
    }

    // Düğüm listeden çıkarılır
    onceki->next = temp->next;



    free(temp);
    printf("Sarki silindi: %d\n", sarkiId);
}

void sarkiGuncelle(int sarkiId, char yeniSarkiAdi[], char yeniSanatciAdi[]) {
    SarkiPtr temp = sarkiBaslangic;

    while (temp != NULL) {
        if (temp->sarkiId == sarkiId) {
            strcpy(temp->sarkiAdi, yeniSarkiAdi);
            strcpy(temp->sanatciAdi, yeniSanatciAdi);
            printf("Sarki guncellendi: ID=%d, Yeni Sarki Adi = %s,\n Yeni Sanatci Adi = %s\n", sarkiId, yeniSarkiAdi, yeniSanatciAdi);
            return;
        }
        temp = temp->next;
    }

    printf("Sarki bulunamadi: ID=%d\n", sarkiId);
}
// Yeni bir şarkıyı bağlı listeye ekler
void sarkiEkle(char sarkiAdi[], char sanatciAdi[],int sarkiId)
{
    SarkiPtr yeniSarki = (SarkiPtr)malloc(sizeof(Sarki));
    yeniSarki->sarkiId=sarkiId;
    strcpy(yeniSarki->sarkiAdi, sarkiAdi);
    strcpy(yeniSarki->sanatciAdi, sanatciAdi);

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
}


// Şarkıları listeler
void sarkilariListele()
{
    SarkiPtr temp = sarkiBaslangic;
    printf("\nSarkilar:\n");
    while (temp != NULL)
    {
        printf("%d) %s - %s\n", temp->sarkiId, temp->sarkiAdi, temp->sanatciAdi);
        temp = temp->next;
    }
}


// Şarkı işlemlerini gerçekleştirir
void sarkiIslem(int sarkiId)
{
    int islem;
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    char yeniSarkiAdi[MAX_SIZE];
    char yeniSanatciAdi[MAX_SIZE];
    int silId;
    int guncelleId;
    do
    {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sarki Ekleme\n");
        printf("2 - Sarkilari Listeleme\n");
        printf("3 - Sarki Sil\n");
        printf("4 - Sarki Guncelle\n");
        printf("5 - Cikis\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem)
        {
        case 1:
            printf("Bir sarki girin: ");
            fgets(sarkiAdi, MAX_SIZE, stdin);
            printf("Sanatcisini girin:");
            fgets(sanatciAdi, MAX_SIZE, stdin);
            sarkiEkle(sarkiAdi, sanatciAdi, sarkiId++);
            dosyayaYaz(sarkiAdi,sanatciAdi);
            printf("Sarki eklendi.\n");
            break;
        case 2:
            sarkilariListele();
            break;
        case 3:
            printf("Silmek istediginiz sarkinin Id sini giriniz:");
            scanf("%d",&silId);
            sarkiSil(silId);
            break;
        case 4:
            printf("Guncellenecek sarkinin Id'sini giriniz:");
            scanf("%d",&guncelleId);
            getchar();
            printf("Yeni sarki adini giriniz:");
            fgets(yeniSarkiAdi, MAX_SIZE, stdin);
            printf("Yeni sanatci adini giriniz:");
            fgets(yeniSanatciAdi, MAX_SIZE, stdin);
            sarkiGuncelle(guncelleId,yeniSarkiAdi,yeniSanatciAdi);
            printf("Guncellendi.\n");
            break;
        case 5:
            printf("Programdan cikiliyor...\n");
            break;
        default:
            printf("Gecersiz islem!\n");
            break;
        }
    } while (islem != 5);
}


int main()
{
    int sarkiId=1;
    FILE *sarkiDosya;

    // Dosyaları aç
    sarkiDosya = fopen("sarki.txt", "a+");
    if (sarkiDosya == NULL)
    {
        fprintf(stderr, "Dosya acilamadi!");
        exit(1);
    }

    // Dosyalardan şarkıları ve sanatçıları oku
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    while (fgets(sarkiAdi, MAX_SIZE, sarkiDosya) != NULL && fgets(sanatciAdi, MAX_SIZE, sarkiDosya) != NULL)
    {       
        sarkiEkle(sarkiAdi, sanatciAdi, sarkiId++);
    }

    sarkiIslem(sarkiId);

    // Dosyaları kapat
    fclose(sarkiDosya);

    return 0;
}
