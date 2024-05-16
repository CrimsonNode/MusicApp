//BAĞLI LİSTE YAPISI DÜZENLENECEK
//1 veya 2 VERİ YAPISI DAHA EKLENECEK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct Queue{
    int dizi[10];
    int on;
    int arka;
    int boyut;
};
typedef struct Queue Queue;
typedef Queue *QueuePtr;

struct Sarki
{
    int sarkiId;
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    struct Sarki* next;
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
typedef Tree* TreePtr;

struct Stack{
    int bas;
    int dizi[10];
};
typedef struct Stack Stack;
typedef Stack *StackPtr;

StackPtr newStack(){
    StackPtr yeniStack = (StackPtr)malloc(sizeof(Stack));
    yeniStack->bas=-1;
    return yeniStack;
}

TreePtr newTree(){
    TreePtr newTree=(TreePtr)malloc(sizeof(Tree));
    newTree->root=NULL;
    return newTree;
}

QueuePtr newQueue(){
    QueuePtr q=(QueuePtr)malloc(sizeof(Queue));
    q->on=0;
    q->arka=-1;
    q->boyut=0;
    return q;
}

int height(SarkiPtr node) {
    if (node == NULL)
        return 0;
    int left_height = height(node->left);
    int right_height = height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int balanceFactor(SarkiPtr node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

SarkiPtr rotateRight(SarkiPtr y) {
    SarkiPtr x = y->left;
    SarkiPtr T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

SarkiPtr rotateLeft(SarkiPtr x) {
    SarkiPtr y = x->right;
    SarkiPtr T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

SarkiPtr insertAVL(SarkiPtr node, SarkiPtr newSarki) {
    if (node == NULL)
        return newSarki;

    if (newSarki->sarkiId < node->sarkiId)
        node->left = insertAVL(node->left, newSarki);
    else if (newSarki->sarkiId > node->sarkiId)
        node->right = insertAVL(node->right, newSarki);
    else
        return node;

    int balance = balanceFactor(node);

    if (balance > 1 && newSarki->sarkiId < node->left->sarkiId)
        return rotateRight(node);

    if (balance < -1 && newSarki->sarkiId > node->right->sarkiId)
        return rotateLeft(node);

    if (balance > 1 && newSarki->sarkiId > node->left->sarkiId) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && newSarki->sarkiId < node->right->sarkiId) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void enqueue(QueuePtr q, int x) {
    if (q->boyut == 10) {        
        return;
    }
    q->arka = (q->arka + 1) % 10;
    q->dizi[q->arka] = x;
    q->boyut++;
}

int dequeue(QueuePtr q) {
    if (q->boyut == 0) {
        printf("Queue bos.\n");
        return -1;
    }
    int x = q->dizi[q->on];
    q->on = (q->on + 1) % 10;
    q->boyut--;
    return x;
}

void initialize(QueuePtr q){
    q->on=0;
    q->arka=-1;
    q->boyut=0;
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

int isFull(StackPtr stack){    
    return stack->bas==9;
}

int isEmpty(StackPtr stack){
    return stack->bas==-1;
}

void pushStack(StackPtr stack,int x){
    if(stack->bas == 9){
        printf("Stack dolu.");
        return;
    }
    stack->dizi[++stack->bas]=x;
}

int pop(StackPtr stack){
    if(stack->bas == -1){
        printf("Stack bos.");
        return -1;
    }
    return stack->dizi[stack->bas--];
}

void AddTree(TreePtr tree,SarkiPtr sarki){   
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

void sarkiEkle(char sarkiAdi[], char sanatciAdi[],int sarkiId,TreePtr tree1)
{
    SarkiPtr yeniSarki = (SarkiPtr)malloc(sizeof(Sarki));
    yeniSarki->sarkiId=sarkiId;
    strcpy(yeniSarki->sarkiAdi, sarkiAdi);
    strcpy(yeniSarki->sanatciAdi, sanatciAdi);
    
    yeniSarki->next = NULL;
    yeniSarki->left = NULL;
    yeniSarki->right = NULL;

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
    tree1->root = insertAVL(tree1->root, yeniSarki);
}

void preorder(SarkiPtr root) {
    if (root != NULL) {
        printf("%d) %s - %s\n", root->sarkiId, root->sarkiAdi, root->sanatciAdi);
        preorder(root->left);
        preorder(root->right);
    }
}

void sarkilariListele(TreePtr tree1) {
    printf("\nSarkilar:\n");
    preorder(tree1->root);
}

void dosyaListele(){
    SarkiPtr temp = sarkiBaslangic;
    while (temp != NULL)
    {
        dosyayaYaz(temp->sarkiAdi, temp->sanatciAdi);
        temp = temp->next;
    }
}

void islemYazdir(QueuePtr q){
    int count = 0;
    while (q->boyut != 0) {            
        switch (dequeue(q))
            {
            case 1:
                count++;
                printf("%d.Sarki Ekleme Islemi\n",count);                    
                break;
            case 2:
                count++;
                printf("%d.Sarkilari Listeleme Islemi\n",count);
                break;
            case 3:
                count++;
                printf("%d.Sarki Silme Islemi\n",count);
                break;
            case 4:
                count++;
                printf("%d.Sarki Guncelleme Islemi\n",count);
                break;
            case 5:
                count++;
                printf("%d.Sarki Arama Islemi\n",count);
                break;
            default:
                printf("Gecersiz islem!\n",count);
                break;
            }
    }
}

void sarkiIslem(int sarkiId,TreePtr tree1,QueuePtr q1)
{
    int islem;
    int arananId;
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
        printf("6 - Islem Listesi\n");
        printf("7 - Cikis\n");
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
            enqueue(q1,1);
            break;
        case 2:
            sarkilariListele(tree1);
            enqueue(q1,2);
            break;
        case 3:
            printf("Silmek istediginiz sarkinin Id sini giriniz:");
            scanf("%d",&silId);
            sarkiSil(silId);
            enqueue(q1,3);
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
            enqueue(q1,4);
            break;
        case 5:
            printf("Aramak istediginiz sarkinin Id'sini giriniz:");
            scanf("%d",&arananId);
            getchar();
            search(tree1->root,arananId);
            enqueue(q1,5);
            break;
        case 6:
            printf("\nYapilan son 10 islem goruntuleniyor...\n");
            islemYazdir(q1);
            
            break;
        case 7:
            dosyaSil = fopen("sarki.txt","w");
            fclose(dosyaSil);
            dosyaListele();
            printf("Programdan cikiliyor...\n");
            break;
        default:
            printf("Gecersiz islem!\n");
            break;
        }
    } while (islem != 7);
}

int main()
{
    QueuePtr q1 = newQueue();
    TreePtr tree1= newTree();
    StackPtr stack1= newStack();
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

    sarkiIslem(sarkiId,tree1,q1);

    fclose(sarkiDosya);

    return 0;
}
