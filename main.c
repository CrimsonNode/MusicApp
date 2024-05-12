#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Verileri dosyaya yazan ve dosyadan okuyan fonksiyon
void veriIsle() {
    char dosyaAdi[] = "veri.txt"; // Dosya adı
    char veri[MAX_SIZE];
    int islem;

    do {
        printf("\nYapmak istediğiniz işlemi seçin:\n");
        printf("1 - Veri yazma\n");
        printf("2 - Veri okuma\n");
        printf("3 - Çıkış\n");
        scanf("%d", &islem);

        switch (islem) {
            case 1: // Veri yazma işlemi
                printf("Bir kelime girin: ");
                getchar(); // Önceki scanf'den kalan newline karakterini al
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
                    printf("%s", veri); // Veriyi ekrana yaz
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

int main() {
    veriIsle(); // Veri işleme fonksiyonunu çağır

    return 0;
}
