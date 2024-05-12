
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

void sarkiIsle(); // Fonksiyonların prototipleri deklare edilmektedir.
void sanatciIsle();

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
                sarkiIsle();
                printf("\n");
                break;
            case '2':
                printf("\n-Sanatci Ekleme-\n");
                printf("-------------\n\n");
                sanatciIsle();
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

void sarkiIsle() {
    char dosyaAdi[] = "veri.txt"; // Dosya adı
    char veri[MAX_SIZE];
    int islem;

    do {
        printf("\nYapmak istediğiniz işlemi seçin:\n");
        printf("1 - Şarkı Ekleme\n");
        printf("2 - Şarkıları Listeleme\n");
        printf("3 - Çıkış\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem) {
            case 1: // Veri yazma işlemi
                printf("Bir şarkı girin: ");
                fgets(veri, MAX_SIZE, stdin); // Kullanıcıdan veri al

                // fgets() fonksiyonuyla okunan verinin sonunda bir satır ataması oluşur,
                // bunu kaldırmak için '\n' karakterini kaldırıyoruz.
                if (veri[strlen(veri) - 1] == '\n') 
                    veri[strlen(veri) - 1] = '\0';

                FILE *dosyaYaz = fopen(dosyaAdi, "a"); // Dosyayı ekleme modunda aç
                if (dosyaYaz == NULL) {
                    printf("Dosya açma hatası!\n");
                    exit(EXIT_FAILURE);
                }
                fprintf(dosyaYaz, "%s\n", veri); // Veriyi dosyaya yaz ve yeni satır ekle
                printf("Veri dosyaya yazıldı.\n");
                fclose(dosyaYaz); // Dosyayı kapat
                break;

            case 2: // Veri okuma işlemi
                FILE *dosyaOku = fopen(dosyaAdi, "r"); // Dosyayı okuma modunda aç
                if (dosyaOku == NULL) {
                    printf("Dosya açma hatası!\n");
                    exit(EXIT_FAILURE);
                }
                while (fgets(veri, MAX_SIZE, dosyaOku) != NULL) { // Dosyadan veri oku
                    printf("\nVeri dosyasındaki veriler:%s", veri); // Veriyi ekrana yaz
                }
                if (!feof(dosyaOku)) { // Dosya sonuna gelinmediyse
                    printf("Dosya okuma hatası!\n");
                    exit(EXIT_FAILURE);
                }
                fclose(dosyaOku); // Dosyayı kapat
                break;

            case 3: // Çıkış
                printf("Programdan çıkılıyor...\n");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Geçersiz işlem!\n");
                break;
        }
    } while (islem != 3);
}

void sanatciIsle() {
    char dosyaAdi[] = "veri.txt"; // Dosya adı
    char veri[MAX_SIZE];
    int islem;

    do {
        printf("\nYapmak istediğiniz işlemi seçin:\n");
        printf("1 - Sanatçı Ekleme\n");
        printf("2 - Sanatçı Listeleme\n");
        printf("3 - Çıkış\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem) {
            case 1: // Veri yazma işlemi
                printf("Bir sanatçı girin: ");
                fgets(veri, MAX_SIZE, stdin); // Kullanıcıdan veri al

                // fgets() fonksiyonuyla okunan verinin sonunda bir satır ataması oluşur,
                // bunu kaldırmak için '\n' karakterini kaldırıyoruz.
                if (veri[strlen(veri) - 1] == '\n') 
                    veri[strlen(veri) - 1] = '\0';

                FILE *dosyaYaz = fopen(dosyaAdi, "a"); // Dosyayı ekleme modunda aç
                if (dosyaYaz == NULL) {
                    printf("Dosya açma hatası!\n");
                    exit(EXIT_FAILURE);
                }
                fprintf(dosyaYaz, "%s\n", veri); // Veriyi dosyaya yaz ve yeni satır ekle
                printf("Veri dosyaya yazıldı.\n");
                fclose(dosyaYaz); // Dosyayı kapat
                break;

            case 2: // Veri okuma işlemi
                FILE *dosyaOku = fopen(dosyaAdi, "r"); // Dosyayı okuma modunda aç
                if (dosyaOku == NULL) {
                    printf("Dosya açma hatası!\n");
                    exit(EXIT_FAILURE);
                }
                while (fgets(veri, MAX_SIZE, dosyaOku) != NULL) { // Dosyadan veri oku
                    printf("\nVeri dosyasındaki veriler:%s", veri); // Veriyi ekrana yaz
                }
                if (!feof(dosyaOku)) { // Dosya sonuna gelinmediyse
                    printf("Dosya okuma hatası!\n");
                    exit(EXIT_FAILURE);
                }
                fclose(dosyaOku); // Dosyayı kapat
                break;

            case 3: // Çıkış
                printf("Programdan çıkılıyor...\n");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Geçersiz işlem!\n");
                break;
        }
    } while (islem != 3);
}