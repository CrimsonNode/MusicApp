/*
Proje
Müzik Yönetim Sistemi

Ogrenci1 No: 032290083
Ogrenci1 İsmi: Fatih Efe Aydoğan

Ogrenci2 No: 032290062
Ogrenci2 İsmi: Emir Uçar

Ogrenci3 No: 032290005
Ogrenci3 İsmi: Berke Kadir Çelik

Ogrenci4 No: 032290072
Ogrenci4 İsmi: Halil Çiftçi

Ogrenci5 No: 032190102
Ogrenci5 İsmi: Fatos Kamberi

Ogrenci6 No: 032290043
Ogrenci6 İsmi: Eren Eryılmaz

Ders Kodu: BMB2006

Dosya İsmi: music_app
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct Sarki{
    int sarkiId;
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    struct Sarki* next;
    struct Sarki* right;
    struct Sarki* left;
};
typedef struct Sarki Sarki;
typedef Sarki* SarkiPtr;

struct List {
    SarkiPtr bas;
    SarkiPtr son;
};
typedef struct List List;
typedef List* ListPtr;

struct Queue{
    int dizi[10];
    int on;
    int arka;
    int boyut;
};
typedef struct Queue Queue;
typedef Queue *QueuePtr;

struct Tree{
    SarkiPtr root;
};
typedef struct Tree Tree;
typedef Tree* TreePtr;

struct Action {
    int actionType;
    Sarki songData; 
    int sarkiId;    
};
typedef struct Action Action;
typedef Action* ActionPtr;

struct Stack {
    int bas;
    Action dizi[10];
};
typedef struct Stack Stack;
typedef Stack *StackPtr;

ListPtr newList(){      // Zaman Karmaşıklığı: O(1) - Alan Karmaşıklığı: O(1)
    ListPtr list = (ListPtr)malloc(sizeof(List));
    list->bas=NULL;
    list->son=NULL;
    return list;
}

StackPtr newStack(){        // Zaman Karmaşıklığı: O(1) - Alan Karmaşıklığı: O(1)
    StackPtr yeniStack = (StackPtr)malloc(sizeof(Stack));
    yeniStack->bas=-1;
    return yeniStack;
}

TreePtr newTree(){      // Zaman Karmaşıklığı: O(1) - Alan Karmaşıklığı: O(1)
    TreePtr newTree=(TreePtr)malloc(sizeof(Tree));
    newTree->root=NULL;
    return newTree;
}

QueuePtr newQueue(){        // Zaman Karmaşıklığı: O(1) - Alan Karmaşıklığı: O(1)
    QueuePtr q=(QueuePtr)malloc(sizeof(Queue));
    q->on=0;
    q->arka=-1;
    q->boyut=0;
    return q;
}

int height(SarkiPtr node) {             //Zaman Karmaşıklığı: O(n) - Alan Karmaşıklığı: O(log n)
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

SarkiPtr rotateRight(SarkiPtr y) {      // Zaman Karmaşıklığı: O(1)
    SarkiPtr x = y->left;
    SarkiPtr T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

SarkiPtr rotateLeft(SarkiPtr x) {       // Zaman Karmaşıklığı: O(1)
    SarkiPtr y = x->right;
    SarkiPtr T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

SarkiPtr insertAVL(SarkiPtr node, SarkiPtr newSarki) {      //Zaman Karmaşıklığı: O(log n) - Alan Karmaşıklığı: O(log n)
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

void enqueue(QueuePtr q, int x) {    // Zaman Karmaşıklığı: O(1) - Alan Karmaşıklığı: O(1)
    if (q->boyut == 10) {        
        return;
    }
    q->arka = (q->arka + 1) % 10;
    q->dizi[q->arka] = x;
    q->boyut++;
}

int dequeue(QueuePtr q) {    // Zaman Karmaşıklığı: O(1) - Alan Karmaşıklığı: O(1)
    int x = q->dizi[q->on];
    q->on = (q->on + 1) % 10;
    q->boyut--;
    return x;
}

SarkiPtr search(SarkiPtr sarki,int sarkiId){    // Zaman Karmaşıklığı: O(log n) - Alan Karmaşıklığı: O(log n)
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

int isFull(StackPtr stack){    // Zaman Karmaşıklığı: O(1)
    return stack->bas==9;
}

int isEmpty(StackPtr stack){       // Zaman Karmaşıklığı: O(1)
    return stack->bas==-1;
}

void pushStack(StackPtr stack, Action action) {     // Zaman Karmaşıklığı: O(1)
    if (stack->bas == 9) {
        printf("Stack dolu.");
        return;
    }
    stack->dizi[++stack->bas] = action;
}

Action pop(StackPtr stack) {       // Zaman Karmaşıklığı: O(1)
    if (stack->bas == -1) {
        printf("Stack bos.");
        Action emptyAction = {0, {0, "", "", NULL, NULL, NULL}, 0};
        return emptyAction;
    }
    return stack->dizi[stack->bas--];
}

void AddTree(TreePtr tree, SarkiPtr sarki) {
    SarkiPtr temp = NULL;
    SarkiPtr current = tree->root;
    
    while (current != NULL) {
        temp = current;
        if (sarki->sarkiId < current->sarkiId)
            current = current->left;
        else if (sarki->sarkiId > current->sarkiId)
            current = current->right;
        else
            return;
    }
    
    if (temp == NULL) {
        tree->root = sarki;
    } else if (sarki->sarkiId < temp->sarkiId) {
        temp->left = sarki;
    } else {
        temp->right = sarki;
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

void sarkiSil(int sarkiId, ListPtr list) {    // Zaman Karmaşıklığı: O(n) - Alan Karmaşıklığı: O(1)
    if (list->bas == NULL) {
        return;
    }

    SarkiPtr temp = list->bas;
    SarkiPtr onceki = NULL;
    
    if (temp != NULL && temp->sarkiId == sarkiId) {
        list->bas = temp->next;
        free(temp);
        temp = NULL;
        printf("Sarki silindi: %d\n", sarkiId);
        return;
    }

    while (temp != NULL && temp->sarkiId != sarkiId) {
        onceki = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Sarki bulunamadi: %d\n", sarkiId);
        return;
    }

    onceki->next = temp->next;

    free(temp);
    temp = NULL;
    printf("Sarki silindi: %d\n", sarkiId);
}

void sarkiGuncelle(ListPtr list,int sarkiId, char yeniSarkiAdi[], char yeniSanatciAdi[]) {      // Zaman Karmaşıklığı: O(n) - Alan Karmaşıklığı: O(1)
    SarkiPtr temp = list->bas;

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

void sarkiEkle(ListPtr list,char sarkiAdi[], char sanatciAdi[], int sarkiId, TreePtr tree1){    // Zaman Karmaşıklığı: O(n) - Alan Karmaşıklığı: O(1)
    SarkiPtr yeniSarki = (SarkiPtr)malloc(sizeof(Sarki));
    yeniSarki->sarkiId=sarkiId;
    strcpy(yeniSarki->sarkiAdi, sarkiAdi);
    strcpy(yeniSarki->sanatciAdi, sanatciAdi);
    
    yeniSarki->next = NULL;
    yeniSarki->left = NULL;
    yeniSarki->right = NULL;

    if (list->bas == NULL)
    {
        list->bas = yeniSarki;
    }
    else
    {
        SarkiPtr temp = list->bas;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = yeniSarki;
        list->son = yeniSarki;
    }
    
    AddTree(tree1,yeniSarki);
    tree1->root = insertAVL(tree1->root, yeniSarki);
}

void sarkilariListele(ListPtr list){     // Zaman Karmaşıklığı: O(1)    
    SarkiPtr temp = list->bas;
    printf("\nSarkilar:\n");
    while (temp != NULL)
    {
        printf("%d) %s - %s\n", temp->sarkiId, temp->sarkiAdi, temp->sanatciAdi);
        temp = temp->next;
    }
}

void dosyaListele(ListPtr list){        // Zaman Karmaşıklığı: O(1)
    SarkiPtr temp = list->bas;
    while (temp != NULL)
    {
        dosyayaYaz(temp->sarkiAdi, temp->sanatciAdi);
        temp = temp->next;
    }
}

void undoLastAction(ListPtr list,StackPtr stack, TreePtr tree) {    // Zaman Karmaşıklığı: O(n) - Alan Karmaşıklığı: O(1)
    if (isEmpty(stack)) {
        printf("Geri alma islemi bulunmamaktadir.\n");
        return;
    }
    Action lastAction = pop(stack);
    switch (lastAction.actionType) {
        case 1: 
            sarkiSil(lastAction.songData.sarkiId, list);
            printf("Sarki ekleme islemi geri alindi: %d\n", lastAction.songData.sarkiId);
            break;
        case 2: 
            sarkiEkle(list,lastAction.songData.sarkiAdi, lastAction.songData.sanatciAdi, lastAction.songData.sarkiId, tree);
            printf("Sarki silme islemi geri alindi: %d\n", lastAction.songData.sarkiId);
            break;
        case 3: 
            sarkiGuncelle(list,lastAction.sarkiId, lastAction.songData.sarkiAdi, lastAction.songData.sanatciAdi);
            printf("Sarki guncelleme islemi geri alindi: %d\n", lastAction.sarkiId);
            break;
        default:
            printf("Gecersiz islem!\n");
            break;
    }
}

void islemYazdir(QueuePtr q){   // Zaman Karmaşıklığı: O(1)
    Queue tempQueue = *q;
    int count = 0;
    while (tempQueue.boyut > 0) {            
        switch (dequeue(&tempQueue))
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
                printf("Gecersiz islem!\n");
                break;
            }
    }
}

void sarkiIslem(ListPtr list,int sarkiId, TreePtr tree1, QueuePtr q1, StackPtr stack1) {
    int islem;
    int arananId;
    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    char yeniSarkiAdi[MAX_SIZE];
    char yeniSanatciAdi[MAX_SIZE];
    int silId;
    int guncelleId;
    FILE* dosyaSil;
    
    do {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1 - Sarki Ekleme\n");
        printf("2 - Sarkilari Listeleme\n");
        printf("3 - Sarki Sil\n");
        printf("4 - Sarki Guncelle\n");
        printf("5 - Sarki Arama\n");
        printf("6 - Islem Listesi\n");
        printf("7 - Geri Al\n");
        printf("8 - Cikis\n");
        printf("Girişiniz: ");
        scanf("%d", &islem);
        getchar();

        Action action;
        SarkiPtr searchedSong;

        switch (islem) {
            case 1:
                printf("Bir sarki girin: ");
                fgets(sarkiAdi, MAX_SIZE, stdin);
                printf("Sanatcisini girin:");
                fgets(sanatciAdi, MAX_SIZE, stdin);
                sarkiEkle(list,sarkiAdi, sanatciAdi, sarkiId, tree1);
                printf("Sarki eklendi.\n");

                action.actionType = 1;
                action.songData.sarkiId = sarkiId;
                strcpy(action.songData.sarkiAdi, sarkiAdi);
                strcpy(action.songData.sanatciAdi, sanatciAdi);
                pushStack(stack1, action);

                sarkiId++;
                enqueue(q1, 1);
                break;
            case 2:
                sarkilariListele(list);
                enqueue(q1, 2);
                break;
            case 3:
                printf("Silmek istediginiz sarkinin Id sini giriniz:");
                scanf("%d", &silId);
                searchedSong = search(tree1->root, silId);

                if (searchedSong) {
                    action.actionType = 2;
                    action.songData = *searchedSong;
                    pushStack(stack1, action);
                    
                    sarkiSil(silId, list);
                    printf("Sarki silindi.\n");
                }
                enqueue(q1, 3);
                break;
            case 4:
                printf("Guncellenecek sarkinin Id'sini giriniz:");
                scanf("%d", &guncelleId);
                getchar();
                printf("Yeni sarki adini giriniz:");
                fgets(yeniSarkiAdi, MAX_SIZE, stdin);
                printf("Yeni sanatci adini giriniz:");
                fgets(yeniSanatciAdi, MAX_SIZE, stdin);
                
                searchedSong = search(tree1->root, guncelleId);
                
                if (searchedSong) {
                    action.actionType = 3;
                    action.sarkiId = guncelleId;
                    action.songData = *searchedSong;
                    pushStack(stack1, action);

                    sarkiGuncelle(list,guncelleId, yeniSarkiAdi, yeniSanatciAdi);
                    printf("Guncellendi.\n");
                }
                enqueue(q1, 4);
                break;
            case 5:
                printf("Aramak istediginiz sarkinin Id'sini giriniz:");
                scanf("%d", &arananId);
                getchar();
                search(tree1->root, arananId);
                enqueue(q1, 5);
                break;
            case 6:
                printf("\nYapilan son 10 islem goruntuleniyor...\n");
                islemYazdir(q1);
                break;
            case 7:
                undoLastAction(list,stack1, tree1);
                break;
            case 8:
                dosyaSil = fopen("sarki.txt", "w");
                fclose(dosyaSil);
                dosyaListele(list);
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz islem!\n");
                break;
        }
    } while (islem != 8);
}


int main() {
    QueuePtr q1 = newQueue();
    TreePtr tree1 = newTree();
    StackPtr stack1 = newStack();
    ListPtr List1 = newList();
    int sarkiId = 1;
    FILE *sarkiDosya;

    sarkiDosya = fopen("sarki.txt", "a+");
    if (sarkiDosya == NULL) {
        fprintf(stderr, "Dosya acilamadi!");
        exit(1);
    }

    char sarkiAdi[MAX_SIZE];
    char sanatciAdi[MAX_SIZE];
    while (fgets(sarkiAdi, MAX_SIZE, sarkiDosya) != NULL && fgets(sanatciAdi, MAX_SIZE, sarkiDosya) != NULL) {       
        sarkiEkle(List1,sarkiAdi, sanatciAdi, sarkiId++, tree1);
    }

    sarkiIslem(List1,sarkiId, tree1, q1, stack1);

    fclose(sarkiDosya);

    return 0;
}
