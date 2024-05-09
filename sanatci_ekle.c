

void sanatciEkle() // Sisteme sanatçı ekleme fonksiyonu.
{
    FILE *sanatciPtr;
    struct Sanatci girilenSanatci;
    int karakterSayisi, sanatciNo;
    int dosyaUzunlugu;

    sanatciPtr = fopen("sanatcilar.bin", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
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