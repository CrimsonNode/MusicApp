//veri yapıları baştan oluşturulacak
//veriler txt dosyasından okunup veri yapısına aktarılacak
//sarki ekleme kısmında sanatçı adı da istenecek
//arama kısmı 2'ye ayrılacak 1-sarkı adıyla arama 2-sanatcı adıyla arama
//tümünü listeleme kısmı 2'ye ayrılacak 1-sarkı adlarını listele 2-sanatcı adlarını listele
//ekleme, silme işlemleri hem txt dosyasında hem de veri yapılarında olmali 2 secenek var?? 1-her işlemden sonra aynı işlemi txt dosyasında yapmak 2-işlemlerin hepsi bitince verinin hepsini txt dosyasına geçirmek
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

void veriCek();
void sarkiIslemMenu(); // Fonksiyonların prototipleri deklare edilmektedir.
void sarkiEkle();
void sarkiListele();

typedef struct Sarki{
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    int sarkiNumarasi;
    struct Sarki* ileri;
}Sarki;
typedef Sarki* Sarkiptr;

/*
typedef struct TreeNode{
    Sarkiptr sarkibilgi;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;
typedef TreeNode* TreeNodeptr;
*/

int main()
{
    veriCek();//txt dosyasından veri yapısına veri çek
    sarkiIslemMenu();
}

void sarkiIslemMenu() {
    int islem;

    do {
        printf("   =Muzik Veri Tabani Sistemi=\n");
        printf("------------------------------------\n");
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sarki Ekle\n");
        printf("2 - Sarkilari Listele\n");
        printf("3 - Cikis\n");
        scanf("%d", &islem);
        getchar(); // Önceki scanf'den kalan newline karakterini al

        switch (islem) {
            case 1:
                sarkiEkle();
                break;

            case 2:
                sarkiListele();
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
//devam edilecek...
Sarkiptr createNode()

void veriCek(){
    char dosyaAdi[] = "denemeler.txt"; // Dosya adı
    char veri[MAX_SIZE];




    FILE *dosyaOku = fopen(dosyaAdi, "r"); // Dosyayı okuma modunda aç
    if (dosyaOku == NULL) {
        printf("Dosya acma hatasi!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(veri, MAX_SIZE, dosyaOku) != NULL) { // Dosyadan veri oku                    
        
        
    }    
}

void sarkiEkle(){
    char dosyaAdi[] = "denemeler.txt"; // Dosya adı
    char veri[MAX_SIZE];

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
    printf("Sarki sisteme eklendi.\n");
    fclose(dosyaYaz); // Dosyayı kapat
}

void sarkiListele(){
    char dosyaAdi[] = "denemeler.txt"; // Dosya adı
    char veri[MAX_SIZE];

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
}