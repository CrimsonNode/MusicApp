
void albumEkle() // Sisteme albüm ekleme fonksiyonu.
{
    FILE *albumPtr;
    struct Album girilenAlbum;
    int karakterSayisi, albumKod;
    int sanatciNo;
    int dosyaUzunluğu;
    albumPtr = fopen("albumler.bin", "ab+"); // Dosya ekleme ve okuma modunda açılmaktadır.
    if (albumPtr == NULL)
    {
        printf("albumler.bin Dosyasi Acilamadi...\n");
        exit(0); // Programdan çıkılmaktadır.
    }

    fseek(albumPtr, 0, SEEK_END); // İmleç dosyanın sonuna konumlandırılır.
    dosyaUzunluğu = ftell(albumPtr); // Dosyanın uzunluğu hesaplanmaktadır.

    if (dosyaUzunluğu == 0) // Dosya boş ise ilk albüm kodu 1001 olur.
    {
        albumKod = 1001;
    }
    else
    {
        fseek(albumPtr, -sizeof(struct Album), SEEK_END); // Dosyanın sonundaki son albümü okur.
        struct Album sonAlbum;
        fread(&sonAlbum, sizeof(struct Album), 1, albumPtr); // Son albümü okur.
        albumKod = sonAlbum.albumKodu + 1; // Yeni albüm kodu oluşturulmaktadır.
    }

    if (albumKod > 1020)
    {
        printf("Sistemde 20 Albüm Kayitlidir. Yeni Album Ekleyemessiniz!\n");
    }
    else // Albüm eklemeye devam etmek için if yapı dışına çıkılır.
    {
        printf("Album Adini Giriniz:");
        gets(girilenAlbum.albumAdi); // Kullanıcıdan albüm adı alınmaktadır.
        fflush(stdin);

        printf("Sanatci Numarasini Giriniz:");
        scanf("%d", &sanatciNo);
        fflush(stdin);

        girilenAlbum.albumKodu = albumKod; // Albüm kodu atanır.
        girilenAlbum.sanatciNumarasi = sanatciNo; // Albümün sanatçı numarası atanır.
        printf("Album %d Sisteme Eklenmistir!\n", albumKod);

        fwrite(&girilenAlbum, sizeof(struct Album), 1, albumPtr); // Albüm dosyaya yazılır.
    }

    fclose(albumPtr); // Dosya kapatılmaktadır.
}