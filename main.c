#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    char isim[100];
    long int kod;
    long int numara;
} telephone;

void KayitEkle();
void TelefonListele();
void KayitGuncelle();
void NumaraKayitBul();
void IsimKayitBul();
void KayitSil();

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Turkish");
    FILE *prehber;
    prehber=fopen("telefonrehber.txt","rb+");
    if(prehber==NULL)
        prehber=fopen("telefonrehber","w");
    int secim,sayi=0;

    while(sayi==0)
    {
        Menu();

        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            KayitEkle();
            break;
        case 2:
            TelefonListele();
            break;
        case 3:
            KayitGuncelle();
            break;
        case 4:
            NumaraKayitBul();
            break;
        case 5:
            IsimKayitBul();
            break;
        case 6:
            KayitSil();
            break;
        case 7:
            sayi=1;
            printf("Çýkmak için bir tuþa basýnýz.");
            break;
        default:

            system("CLS");
            printf("\n \n Yanlýþ seçim yaptýnýz. Tekrar seciniz.\n");
        }
    }
    return 0;
}
void Menu()
{
    printf("*****************************************************\n");
    printf("\tTELEFON REHBERÝ V1.0\n");
    printf("*****************************************************\n");
    printf("ÝÞLEMLER\n\n");
    printf("-----------------------------------------------------\n");
    printf("1.Kayýt Ekle\n");
    printf("2.Telefonlarý Listele\n");
    printf("3.Kaydý Düzenle\n");
    printf("4.Numara Ýle Kayýt Bul\n");
    printf("5.Ýsim ile Kayýt Bul\n");
    printf("6.Kayýt Sil\n");
    printf("7.Çýkýþ\n");
    printf("Seçim:");
}

void KayitEkle(void)
{
    system("CLS");
    FILE *prehber;
    telephone rehber= { "", 0, 0 };
    prehber=fopen("telefonrehber.txt","ab");

    if(prehber==NULL)
    {
        printf("Dosya Açýlmadý.\n");
        exit(1);
    }
    else
    {
        printf("\n\n\t\t *****KAYIT EKLE*****\n\n\n");

        printf("Ýsmi Giriniz:");
        scanf("%s",rehber.isim);
        long long randomsayi;
        srand(time(NULL));
        randomsayi=100000+rand()%899999;
        printf("Numarayý giriniz:");
        scanf("%ld",&rehber.numara);
        rehber.kod=randomsayi;
        if(fwrite(&rehber,sizeof(telephone),1,prehber)!=1)
        {
            printf("Yazma hatasý");
            exit(1);
        }
        printf("Ozel rehber kodunuz: %lld \n",randomsayi);
        printf("Bu kodu kullanarak silme islemi yapabilirsiniz. \n");
        printf("------------------------------- \n");
        printf("Kiþi baþarýyla eklendi\n\n");
                printf("------------------------------- \n");
        printf("\n");
        rewind(prehber);
    }
}

void TelefonListele(void)
{
    system("CLS");
    FILE *prehber;
    telephone rehber;
    prehber=fopen("Telefonrehber.txt","rb");
    if(prehber==NULL)
    {
        printf("TelefonRehber.txt dosyasi acilmadi!\n");
        exit(1);
    }
    printf("\n\n******Rehber Listele*****\n");
    printf("Ýsim \t\t| Kod \t\t| Numara\n");
    printf("-----------------------------------------------------\n");
    fseek(prehber,0,0);
    fread(&rehber,sizeof(telephone),1,prehber);

    while(!feof(prehber))
    {
        if(strcmp(rehber.isim,""))

            printf("%10s  \t| %10ld  \t| %10ld\n",rehber.isim,rehber.kod,rehber.numara);
        fread(&rehber,sizeof(telephone),1,prehber);
    }
    fclose(prehber);
}

void KayitGuncelle(void)
{
    telephone rehber;
    char isim[50];
    int sayac=0;
    FILE *prehber;
    if((prehber=fopen("telefonrehber.txt","rb+"))==NULL)
    {
        printf("Dosya açýlmadý");
    }
    printf("\n\nKayýt Düzenleme\n");
    printf("Güncellenecek Ýsimi Giriniz:");
    scanf("%s",isim);

    while(!feof(prehber))
    {
        fread(&rehber,sizeof(rehber),1,prehber);
        sayac++;

        if(!strcmp(rehber.isim,isim))
        {
            system("CLS");
            printf("\n\nDuzenlenecek Konum: %d",sayac);
            printf("\n Isim   : %s",rehber.isim);
            printf("\n Kod    : %ld",rehber.kod);
            printf("\n Numara : %ld",rehber.numara);
            printf("\n#####################################\n");

            printf("Yeni Ýsmi giriniz:");
            scanf("%s",rehber.isim);
            printf("Yeni Kodu giriniz:");
            scanf("%ld",&rehber.kod);
            printf("Yeni Numarayi giriniz:");
            scanf("%ld",&rehber.numara);

            fseek(prehber,(sayac-1)*sizeof(rehber),SEEK_SET);
            fwrite(&rehber,sizeof(rehber),1,prehber);
            system("CLS");
            printf("----------------------------\n");
            printf("---------------------------\n\n");
            printf("Duzenleme islemi basarili. \n\n");
            printf("---------------------------\n");
            printf("----------------------------\n");
            break;
        }
        if(feof(prehber))
        {

            {
                system("CLS");
                printf("Kisi Bulunamadý..!\n");
                printf("Tekrar Arama Yapmak Ýster misiniz? (E/H)-(e/h)\n");

                char ch=getch();
                if(ch=='E' || ch=='e')
                {
                    KayitGuncelle();
                }
                else
                {
                    printf("Arama Yapýlmadý Menuye yonlendiriliyorsunuz..!\n\n");

                }
            }
            break;
        }



    }

    fclose(prehber);
}

NumaraKayitBul()
{
    system("CLS");
    FILE *prehber;
    telephone rehber;
    int no;
    int sayac=0;
    prehber=fopen("Telefonrehber.txt","rb");
    printf("\n*****Numara Arama*****\n");
    printf("Numara Giriniz:");
    scanf("%d",&no);

    fseek(prehber,0,0);
    fread(&rehber,sizeof(telephone),1,prehber);

    while(!feof(prehber))
    {
        if(rehber.numara==no)
        {
            printf("\nIsim   : %s",rehber.isim);
            printf("\nKod    : %ld",rehber.kod);
            printf("\nNumara : %ld",rehber.numara);
            printf("\n##########################################\n");

            sayac++;
        }
        fread(&rehber,sizeof(telephone),1,prehber);
    }
    if(sayac==0)
    {
        printf("Numara Bulunamadý.\n");
    }
    else
    {
        printf("%d Adet Numara Bulundu.\n\n",sayac);
    }
    fclose(prehber);
}

IsimKayitBul()
{
    system("CLS");
    FILE *prehber;
    telephone rehber;
    char ad[50];
    int sayac=0;
    prehber=fopen("Telefonrehber.txt","rb");
    printf("\n*****Ýsim Arama*****\n");
    printf("Ýsim Giriniz:");
    scanf("%s",ad);
    fseek(prehber,0,0);
    fread(&rehber,sizeof(telephone),1,prehber);
    while(!feof(prehber))
    {

        if(!strcmp(rehber.isim,ad))
        {
            printf("\nIsim   : %s",rehber.isim);
            printf("\nKod    : %ld",rehber.kod);
            printf("\nNumara : %ld",rehber.numara);
            printf("\n#####################################\n");

            sayac++;

        }
        fread(&rehber,sizeof(telephone),1,prehber);
    }
    if(sayac==0)
    {
        printf("Ýsim Bulunamadý.\n");
    }
    else
    {
        printf("%d Kiþi Bulundu.\n\n",sayac);
    }
    fclose(prehber);
}

void KayitSil(void)
{
    system("CLS");
    telephone rehber,boskayit= {"",0,0};
    long int kod;
    int sayac=0;
    FILE *prehber;
    if((prehber=fopen("telefonrehber.txt","rb+"))==NULL)
    {
        printf("Dosya açýlmadý");
    }
    printf("\n\n\n");
    printf("Kayit Sil\n");
    printf("Silinecek kisinin Kodunu Giriniz: \n");
    printf("NOT: Kayit olurken verilmis random kod kayitlari goruntuleden kodunuzu ogrenin \n ");
    scanf("%ld",&kod);
    printf("\n");

    while(fread(&rehber,sizeof(rehber),1,prehber))
    {
        sayac++;

        if(rehber.kod==kod)
        {

            printf("Konum1:%d",sayac);
            printf("\nIsim   : %s",rehber.isim);
            printf("\nKod    : %ld",rehber.kod);
            printf("\nNumara : %ld",rehber.numara);
            printf("\n###################################\n");
            fseek(prehber,(sayac-1)*sizeof(rehber),SEEK_SET);
            fwrite(&boskayit,sizeof(rehber),1,prehber);
            printf("\nKayýt Silindi..!\n");
            break;

        }
    }

    if(rehber.kod!=kod)

    {
        printf("Kayýt Bulunamadý..!\n");
        printf("Tekrar Arama Yapmak Ýster misiniz? (E/H)-(e/h)\n");

        char ch=getch();
        if(ch=='E' || ch=='e')
        {
            KayitSil();
        }
        else
        {
            printf("Arama Yapýlmadý..!\n\n");

        }
    }

    fclose(prehber);
}

