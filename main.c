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
            printf("��kmak i�in bir tu�a bas�n�z.");
            break;
        default:

            system("CLS");
            printf("\n \n Yanl�� se�im yapt�n�z. Tekrar seciniz.\n");
        }
    }
    return 0;
}
void Menu()
{
    printf("*****************************************************\n");
    printf("\tTELEFON REHBER� V1.0\n");
    printf("*****************************************************\n");
    printf("��LEMLER\n\n");
    printf("-----------------------------------------------------\n");
    printf("1.Kay�t Ekle\n");
    printf("2.Telefonlar� Listele\n");
    printf("3.Kayd� D�zenle\n");
    printf("4.Numara �le Kay�t Bul\n");
    printf("5.�sim ile Kay�t Bul\n");
    printf("6.Kay�t Sil\n");
    printf("7.��k��\n");
    printf("Se�im:");
}

void KayitEkle(void)
{
    system("CLS");
    FILE *prehber;
    telephone rehber= { "", 0, 0 };
    prehber=fopen("telefonrehber.txt","ab");

    if(prehber==NULL)
    {
        printf("Dosya A��lmad�.\n");
        exit(1);
    }
    else
    {
        printf("\n\n\t\t *****KAYIT EKLE*****\n\n\n");

        printf("�smi Giriniz:");
        scanf("%s",rehber.isim);
        long long randomsayi;
        srand(time(NULL));
        randomsayi=100000+rand()%899999;
        printf("Numaray� giriniz:");
        scanf("%ld",&rehber.numara);
        rehber.kod=randomsayi;
        if(fwrite(&rehber,sizeof(telephone),1,prehber)!=1)
        {
            printf("Yazma hatas�");
            exit(1);
        }
        printf("Ozel rehber kodunuz: %lld \n",randomsayi);
        printf("Bu kodu kullanarak silme islemi yapabilirsiniz. \n");
        printf("------------------------------- \n");
        printf("Ki�i ba�ar�yla eklendi\n\n");
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
    printf("�sim \t\t| Kod \t\t| Numara\n");
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
        printf("Dosya a��lmad�");
    }
    printf("\n\nKay�t D�zenleme\n");
    printf("G�ncellenecek �simi Giriniz:");
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

            printf("Yeni �smi giriniz:");
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
                printf("Kisi Bulunamad�..!\n");
                printf("Tekrar Arama Yapmak �ster misiniz? (E/H)-(e/h)\n");

                char ch=getch();
                if(ch=='E' || ch=='e')
                {
                    KayitGuncelle();
                }
                else
                {
                    printf("Arama Yap�lmad� Menuye yonlendiriliyorsunuz..!\n\n");

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
        printf("Numara Bulunamad�.\n");
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
    printf("\n*****�sim Arama*****\n");
    printf("�sim Giriniz:");
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
        printf("�sim Bulunamad�.\n");
    }
    else
    {
        printf("%d Ki�i Bulundu.\n\n",sayac);
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
        printf("Dosya a��lmad�");
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
            printf("\nKay�t Silindi..!\n");
            break;

        }
    }

    if(rehber.kod!=kod)

    {
        printf("Kay�t Bulunamad�..!\n");
        printf("Tekrar Arama Yapmak �ster misiniz? (E/H)-(e/h)\n");

        char ch=getch();
        if(ch=='E' || ch=='e')
        {
            KayitSil();
        }
        else
        {
            printf("Arama Yap�lmad�..!\n\n");

        }
    }

    fclose(prehber);
}

