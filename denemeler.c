#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct Sarki
{
    int sarkiId;
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    struct Sarki *next;
    struct Sarki* right;
    struct Sarki* left;
};
typedef struct Sarki Sarki;
typedef Sarki *SarkiPtr;

SarkiPtr sarkiBaslangic = NULL;

struct Tree{
    SarkiPtr root;
};
typedef struct Tree Tree;
typedef Tree* Treeptr;

Treeptr newTree(){
    Treeptr newTree=(Treeptr)malloc(sizeof(Tree));
    newTree->root=NULL;
    return newTree;
}

SarkiPtr search(SarkiPtr sarki,int sarkiId){
    if(sarki==NULL)
        return NULL;
    if(sarki->sarkiId==sarkiId){
        printf("\nSarki Adi: %s",sarki->sarkiAdi);
        printf("Sanatci Adi: %s\n",sarki->sanatciAdi);
        return sarki;
        }
    else
        if(sarki->sarkiId>sarkiId)
            return search(sarki->left,sarkiId);
        else
            return search(sarki->right,sarkiId);
}

void AddTree(Treeptr tree,SarkiPtr sarki){   
    SarkiPtr temp = NULL;
    SarkiPtr s = tree->root;
    while(s!=NULL)
    {
        temp=s;
        if(sarki->sarkiId < s->sarkiId) 
            s=s->left;
        else    
            s=s->right;
    }
    if(temp==NULL)
    {
        tree->root = sarki;
    }
    else{
        if(sarki->sarkiId < temp->sarkiId)
            temp->left=sarki;
        else    
            temp->right=sarki;
    }
}

void dosyayaYaz(char sarkiAdi[], char sanatciAdi[]){
    
    FILE *dosya = fopen("sarki.txt", "ab+");
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

    while (temp != NULL && temp->sarkiId != sarkiId) {
        onceki = temp;
        temp = temp->next;
        sayac++;
    }

    if (temp == NULL) {
        printf("Sarki bulunamadi: %d\n", sarkiId);
        return;
    }

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

void sarkiEkle(char sarkiAdi[], char sanatciAdi[],int sarkiId,Treeptr tree1)
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
    
    AddTree(tree1,yeniSarki);
}

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

void dosyaListele(){
    SarkiPtr temp = sarkiBaslangic;
    while (temp != NULL)
    {
        dosyayaYaz(temp->sarkiAdi, temp->sanatciAdi);
        temp = temp->next;
    }
}

void sarkiIslem(int sarkiId,Treeptr tree1)
{
    int islem;
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    char yeniSarkiAdi[MAX_SIZE];
    char yeniSanatciAdi[MAX_SIZE];
    int silId;
    int guncelleId;
    FILE* dosyaSil;
    do
    {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sarki Ekleme\n");
        printf("2 - Sarkilari Listeleme\n");
        printf("3 - Sarki Sil\n");
        printf("4 - Sarki Guncelle\n");
        printf("5 - Sarki Arama\n");
        printf("6 - Cikis\n");
        scanf("%d", &islem);
        getchar();

        switch (islem)
        {
        case 1:
            printf("Bir sarki girin: ");
            fgets(sarkiAdi, MAX_SIZE, stdin);
            printf("Sanatcisini girin:");
            fgets(sanatciAdi, MAX_SIZE, stdin);
            sarkiEkle(sarkiAdi, sanatciAdi, sarkiId++,tree1);

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
            printf("Aramak istediginiz sarkinin Id'sini giriniz:");
            scanf("%d",&sarkiId);
            getchar();
            search(tree1->root,sarkiId);
        case 6:
            dosyaSil = fopen("sarki.txt","w");
            fclose(dosyaSil);
            dosyaListele();
            printf("Programdan cikiliyor...\n");
            break;
        default:
            printf("Gecersiz islem!\n");
            break;
        }
    } while (islem != 6);
}

int main()
{
    Treeptr tree1= newTree();
    int sarkiId=1;
    FILE *sarkiDosya;

    sarkiDosya = fopen("sarki.txt", "a+");
    if (sarkiDosya == NULL)
    {
        fprintf(stderr, "Dosya acilamadi!");
        exit(1);
    }

    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    while (fgets(sarkiAdi, MAX_SIZE, sarkiDosya) != NULL && fgets(sanatciAdi, MAX_SIZE, sarkiDosya) != NULL)
    {       
        sarkiEkle(sarkiAdi, sanatciAdi, sarkiId++,tree1);
    }

    sarkiIslem(sarkiId,tree1);

    fclose(sarkiDosya);

    return 0;
}
