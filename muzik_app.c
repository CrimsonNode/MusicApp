
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

void sarkiIslem(); // Fonksiyonların prototipleri deklare edilmektedir.
void sanatciIslem();

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
        printf("(1) - Sarki Islemleri\n");
        printf("(2) - Sanatci Islemleri\n");
        printf("(3) - Cikis\n");
        printf("------------------------------------\n");
        printf("Seciminiz:");
        scanf(" %c", &secim); // Kullanıcıdan seçimi alınmaktadır.
        fflush(stdin); // Buffer boşaltılmaktadır.
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

    return 0;
}

void sarkiIslem() {
    char dosyaAdi[] = "sarkilar.txt"; // Dosya adı
    char veri[MAX_SIZE];
    int islem;

    do {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sarki Ekleme\n");
        printf("2 - Sarkilari Listeleme\n");
        printf("3 - Cikis\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem) {
            case 1: // Veri yazma işlemi
                printf("Bir sarki girin: ");
                fgets(veri, MAX_SIZE, stdin); // Kullanıcıdan veri al

                // fgets() fonksiyonuyla okunan verinin sonunda bir satır ataması oluşur,
                // bunu kaldırmak için '\n' karakterini kaldırıyoruz.
                if (veri[strlen(veri) - 1] == '\n') 
                    veri[strlen(veri) - 1] = '\0';

                FILE *dosyaYaz = fopen(dosyaAdi, "a"); // Dosyayı ekleme modunda aç
                if (dosyaYaz == NULL) {
                    printf("Dosya acma hatasi!\n");
                    exit(EXIT_FAILURE);
                }
                fprintf(dosyaYaz, "%s\n", veri); // Veriyi dosyaya yaz ve yeni satır ekle
                printf("Veri dosyaya yazildi.\n");
                fclose(dosyaYaz); // Dosyayı kapat
                break;

            case 2: // Veri okuma işlemi
                FILE *dosyaOku = fopen(dosyaAdi, "r"); // Dosyayı okuma modunda aç
                if (dosyaOku == NULL) {
                    printf("Dosya acma hatasi!\n");
                    exit(EXIT_FAILURE);
                }
                printf("\nSarkilar:");
                int i = 1;
                while (fgets(veri, MAX_SIZE, dosyaOku) != NULL) { // Dosyadan veri oku                    
                    printf("\n%d)%s", i,veri); // Veriyi ekrana yaz
                    i++;
                }
                if (!feof(dosyaOku)) { // Dosya sonuna gelinmediyse
                    printf("Dosya okuma hatasi!\n");
                    exit(EXIT_FAILURE);
                }
                fclose(dosyaOku); // Dosyayı kapat
                break;

            case 3: // Çıkış
                printf("Programdan cikiliyor...\n");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Gecersiz islem!\n");
                break;
        }
    } while (islem != 3);
}

void sanatciIslem() {
    char dosyaAdi[] = "sanatcilar.txt"; // Dosya adı
    char veri[MAX_SIZE];
    int islem;

    do {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sanatci Ekleme\n");
        printf("2 - Sanatci Listeleme\n");
        printf("3 - Cikis\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem) {
            case 1: // Veri yazma işlemi
                printf("Bir sanatci girin: ");
                fgets(veri, MAX_SIZE, stdin); // Kullanıcıdan veri al

                // fgets() fonksiyonuyla okunan verinin sonunda bir satır ataması oluşur,
                // bunu kaldırmak için '\n' karakterini kaldırıyoruz.
                if (veri[strlen(veri) - 1] == '\n') 
                    veri[strlen(veri) - 1] = '\0';

                FILE *dosyaYaz = fopen(dosyaAdi, "a"); // Dosyayı ekleme modunda aç
                if (dosyaYaz == NULL) {
                    printf("Dosya acma hatasi!\n");
                    exit(EXIT_FAILURE);
                }
                fprintf(dosyaYaz, "%s\n", veri); // Veriyi dosyaya yaz ve yeni satır ekle
                printf("Veri dosyaya yazildi.\n");
                fclose(dosyaYaz); // Dosyayı kapat
                break;

            case 2: // Veri okuma işlemi
                FILE *dosyaOku = fopen(dosyaAdi, "r"); // Dosyayı okuma modunda aç
                if (dosyaOku == NULL) {
                    printf("Dosya acma hatasi!\n");
                    exit(EXIT_FAILURE);
                }
                printf("\nSanatcilar:");
                int i = 1;
                while (fgets(veri, MAX_SIZE, dosyaOku) != NULL) { // Dosyadan veri oku                   
                    printf("\n%d)%s", i,veri); // Veriyi ekrana yaz
                    i++;
                }
                if (!feof(dosyaOku)) { // Dosya sonuna gelinmediyse
                    printf("Dosya okuma hatasi!\n");
                    exit(EXIT_FAILURE);
                }
                fclose(dosyaOku); // Dosyayı kapat
                break;

            case 3: // Çıkış
                printf("Programdan cikiliyor...\n");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Gecersiz islem!\n");
                break;
        }
    } while (islem != 3);
}