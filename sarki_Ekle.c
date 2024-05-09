void sarkiEkle() // Sisteme şarkı ekleme fonksiyonu.
{
    FILE *sarkiPtr;
    struct Sarki girilenSarki;
    int karakterSayisi, sarkiNo;
    int dosyaUzunlugu;

    sarkiPtr = fopen("sarkilar.bin", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
    if (sarkiPtr == NULL)
    {
        printf("sarkilar.bin Dosyasi Acilamadi...\n");
        exit(0); // Programdan çıkılmaktadır.
    }

    fseek(sarkiPtr, 0, SEEK_END); // İmleç dosyanın sonuna konumlandırılır.
    dosyaUzunlugu = ftell(sarkiPtr); // Dosyanın uzunluğu hesaplanmaktadır.

    if (dosyaUzunlugu == 0) // Dosya boş ise ilk şarkıya şarkı numarası olarak 1 atanır.
    {
        sarkiNo = 1;
    }
    else
    {
        fseek(sarkiPtr, -sizeof(struct Sarki), SEEK_END); // Dosyanın sonundaki son şarkıyı okur.
        struct Sarki sonSarki;
        fread(&sonSarki, sizeof(struct Sarki), 1, sarkiPtr); // Son şarkıyı okur.
        sarkiNo = sonSarki.sarkiNumarasi + 1; // Yeni şarkı numarası oluşturulmaktadır.
    }

    if (sarkiNo > 100)
    {
        printf("Sistemde 100 Sarki Kayitlidir. Yeni Sarki Ekleyemessiniz!\n");
    }
    else // Şarkı eklemeye devam etmek için if yapı dışına çıkılır.
    {
        printf("Sarki Adini Giriniz:");
        gets(girilenSarki.sarkiAdi); // Kullanıcıdan şarkı adını alınmaktadır.
        fflush(stdin);

        girilenSarki.sarkiNumarasi = sarkiNo; // Şarkı numarası atanır.
        printf("Sarki %d Sisteme Eklenmistir!\n", sarkiNo);

        fwrite(&girilenSarki, sizeof(struct Sarki), 1, sarkiPtr); // Şarkı dosyaya yazılır.
    }

    fclose(sarkiPtr); // Dosya kapatılmaktadır.
}
