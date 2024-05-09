
void sarkiAlbumuListele() // Şarkıların hangi albümde olduğunu listeleyen fonksiyon.
{
    FILE *sarkiPtr, *albumPtr;
    struct Sarki okunanSarki;
    struct Album okunanAlbum;
    int sarkiNo;
    sarkiPtr = fopen("sarkilar.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (sarkiPtr == NULL)
    {
        printf("sarkilar.bin Dosyasi Acilamadi...\n");
        exit(0); // Programdan çıkılmaktadır.
    }

    albumPtr = fopen("albumler.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (albumPtr == NULL)
    {
        printf("albumler.bin Dosyasi Acilamadi...\n");
        exit(0);
    }

    printf("Albumunu Ogrenmek Istediginiz Sarki Numarasini Giriniz:");
    scanf("%d", &sarkiNo);
    fflush(stdin);

    fseek(sarkiPtr, (sarkiNo - 1) * sizeof(struct Sarki), SEEK_SET);
    fread(&okunanSarki, sizeof(struct Sarki), 1, sarkiPtr);

    if (sarkiNo != okunanSarki.sarkiNumarasi)
    {
        printf("Bu numarada bir sarki bulunmuyor.\n");
    }
    else
    {
        fseek(albumPtr, (okunanSarki.albumKodu - 1001) * sizeof(struct Album), SEEK_SET);
        fread(&okunanAlbum, sizeof(struct Album), 1, albumPtr);

        printf("Sarki Numarasi  : %d\n", okunanSarki.sarkiNumarasi);
        printf("Sarki Adi       : %s\n\n", okunanSarki.sarkiAdi);
        printf("Album Kodu      : %d\n", okunanAlbum.albumKodu);
        printf("Album Adi       : %s\n\n", okunanAlbum.albumAdi);
    }

    fclose(sarkiPtr); // Dosya kapatılmaktadır.
    fclose(albumPtr);
}
