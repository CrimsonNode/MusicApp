
void albumSanatcisiListele() // Bir albümün hangi sanatçıya ait olduğunu gösteren fonksiyon.
{
    FILE *sanatciPtr, *albumPtr;
    struct Sanatci okunanSanatci;
    struct Album okunanAlbum;
    int albumKod;
    albumPtr = fopen("albumler.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (albumPtr == NULL)
    {
        printf("albumler.bin Dosyasi Acilamadi...\n");
        exit(0);
    }

    sanatciPtr = fopen("sanatcilar.bin", "rb"); // Dosya okuma modunda açılmaktadır.
    if (sanatciPtr == NULL)
    {
        printf("sanatcilar.bin Dosyasi Acilamadi...\n");
        exit(0);
    }

    printf("Sanatcisini Ogrenmek Istediginiz Album Kodunu Giriniz:");
    scanf("%d", &albumKod);
    fflush(stdin);

    fseek(albumPtr, (albumKod - 1001) * sizeof(struct Album), SEEK_SET);
    fread(&okunanAlbum, sizeof(struct Album), 1, albumPtr);

    fseek(sanatciPtr, (okunanAlbum.sanatciNumarasi - 1) * sizeof(struct Sanatci), SEEK_SET);
    fread(&okunanSanatci, sizeof(struct Sanatci), 1, sanatciPtr);
    printf("Album Kodu      : %d\n", okunanAlbum.albumKodu);
    printf("Album Adi       : %s\n\n", okunanAlbum.albumAdi);
    printf("Sanatci Numarasi: %d\n", okunanSanatci.sanatciNumarasi);
    printf("Sanatci Adi     : %s\n\n", okunanSanatci.sanatciAdi);

    fclose(albumPtr); // Dosyalar kapatılmaktadır.
    fclose(sanatciPtr);
}
