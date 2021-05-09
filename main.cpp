#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
using namespace std;

int k=7, r=0, dogru=0;
COORD koordinator={0,0};

void git(int x,int y){
    COORD koordinator;
    koordinator.X=x;
    koordinator.Y=y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),koordinator);
}

struct tarih{
    int gun,ay,yil;
};

ofstream dosyaOlustur;
ifstream dosyaOku;

class urun{
    int urunNumarasi;
    char isim[25];
    tarih t;

public:
    void ekle(){
        cout<<"\nUrun Numarasi: ";
        cin>>urunNumarasi;
        cout<<"\nUrun Adi: ";
        cin>>isim;
        cout<<"\nUretim Tarihi: ";
        cin>>t.gun>>t.ay>>t.yil;
    }

    void goster(){
        cout<<"\nUrun Numarasi: "<<urunNumarasi;
        cout<<"\nUrun Adi: "<<isim;
        cout<<"\nUretim Tarihi: "<<t.gun<<"."<<t.ay<<"."<<t.yil;
    }

    void rapor(){
        git(3,k);
        cout<<urunNumarasi;
        git(13,k);
        puts(isim);
    }

    int numaraDondur(){
        return(urunNumarasi);
    }
};

class deger:public urun{
    float fiyat,miktar,vergiYuzdesi,brut,indirimYuzdesi,netTutar;

public:
    void ekle();
    void goster();
    void rapor();
    void hesapla();
    void ode();

    float netTutarDondur(){
        return(netTutar);
    }
}tutar;

void deger::ekle(){
    urun::ekle();

    cout<<"\nFiyat: ";
    cin>>fiyat;
    cout<<"\nMiktar: ";
    cin>>miktar;
    cout<<"\nVergi Yuzdesi: ";
    cin>>vergiYuzdesi;
    cout<<"\nIndirim Yuzdesi: ";
    cin>>indirimYuzdesi;

    hesapla();
    dosyaOlustur.write((char *)&tutar,sizeof(tutar));
    dosyaOlustur.close();
}

void deger::hesapla(){
    brut=fiyat+(fiyat*(vergiYuzdesi/100));
    netTutar=miktar*(brut-(brut*(indirimYuzdesi/100)));
}

void deger::goster(){
    dosyaOku.open("esyaDeposu.dat",ios::binary);
    dosyaOku.read((char *)&tutar,sizeof(tutar));
    urun::goster();

    cout<<"\nNet Tutar: "<<netTutar;
    dosyaOku.close();
}

void deger::rapor(){
    urun::rapor();

    git(23,k);
    cout<<fiyat;
    git(33,k);
    cout<<miktar;
    git(44,k);
    cout<<vergiYuzdesi;
    git(52,k);
    cout<<indirimYuzdesi;
    git(64,k);
    cout<<netTutar;

    k=k+1;

    if(k==50){
        git(25,50);
        cout<<"Devam Etmek Icin Herhangi Bir Tusa Basiniz";
        getch();
        k=7;
        system("cls");
        git(30,3);
        cout<<"Urun Detaylari";
        git(3,5);
        cout<<"Numara";
        git(13,5);
        cout<<"Isim";
        git(23,5);
        cout<<"Fiyat";
        git(33,5);
        cout<<"Miktar";
        git(44,5);
        cout<<"Vergi Yuzdesi";
        git(52,5);
        cout<<"Indirim Yuzdesi";
        git(64,5);
        cout<<"Net Tutar";
    }
}

void deger::ode(){
    goster();

    cout<<"\n************************************";
    cout<<"\n             DETAYLAR               ";
    cout<<"\n************************************";
    cout<<"\nFiyat           :"<<fiyat;
    cout<<"\nMiktar          :"<<miktar;
    cout<<"\nVergi Yuzdesi   :"<<vergiYuzdesi;
    cout<<"\nIndirim Yuzdesi :"<<indirimYuzdesi;
    cout<<"\nNet Tutar       :"<<netTutar;
    cout<<"\n************************************";
}

int main(){
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);

    fstream gecici("gecici.dat",ios::binary|ios::out);

menu:
    system("cls");
    cout<<"Supermarket Faturalandirmasi\n";
    cout<<"============================";
    cout<<"\n1 -> Fatura Raporu";
    cout<<"\n2 -> Urun Ekle/Sil/Duzenle";
    cout<<"\n3 -> Urun Detaylarini Goster";
    cout<<"\n4 -> Cikis\n";
    cout<<"============================";
    cout<<"\nLutfen Tercihinizi Yapiniz: ";

    int tercih, ff;
    float genelToplam;

    cin>>tercih;

    switch(tercih){
    case 1:
ss:
        system("cls");
        git(25,2);
        cout<<"Fatura Detaylari";
        git(25,3);
        cout<<"===================";
        cout<<"\n1 -> Tum Urunler";
        cout<<"\n2 -> Ana Menuye Don";
        cout<<"\nLutfen Tercihinizi Yapiniz: ";

        int tercih2;

        cin>>tercih2;

        if(tercih2==1){
            system("cls");
            git(30,3);
            cout<<"Fatura Detaylari";
            git(3,5);
            cout<<"Urun Numarasi";
            git(13,5);
            cout<<"Isim";
            git(23,5);
            cout<<"Fiyat";
            git(33,5);
            cout<<"Miktar";
            git(44,5);
            cout<<"Vergi Yuzdesi";
            git(52,5);
            cout<<"Indirim Yüzdesi";
            git(64,5);
            cout<<"Net Tutar";

            dosyaOku.open("esyaDeposu.dat",ios::binary);

            if(!dosyaOku){
                cout<<"\nDosya Bulunamadi";
                goto menu;
            }

            dosyaOku.seekg(0);
            genelToplam=0;

            while(!dosyaOku.eof()){
                dosyaOku.read((char *)&tutar,sizeof(tutar));
                if(!dosyaOku.eof()){
                    tutar.rapor();
                    genelToplam=tutar.netTutarDondur();
                    ff=0;
                }

                if(ff!=0){
                    genelToplam=0;
                }
            }

            git(17,k);
            cout<<"\nGenel Toplam: "<<genelToplam;
            getch();
            dosyaOku.close();
        }

        if(tercih2==2){
            goto menu;
        }

        goto ss;

    case 2:
db:
    system("cls");
    git(25,2);
    cout<<"Fatura Duzenleyici";
    git(25,3);
    cout<<"===================";
    cout<<"\n1 -> Urun Detaylarini Ekle";
    cout<<"\n2 -> Urun Detaylarini Duzenle";
    cout<<"\n3 -> Urun Detaylarini Sil";
    cout<<"\n4 -> Ana Menuye Don";

    int tercih3;
    cin>>tercih3;

    switch(tercih3){
    case 1:
        dosyaOlustur.open("esyaDeposu.dat",ios::binary|ios::app);
        tutar.ekle();
        cout<<"\nUrun Basariyla Eklendi";
        getch();
        goto db;

    case 2:
        int urunNo;
        dogru=0;
        cout<<"\nDuzenlenecek Urun Numarasini Giriniz: ";
        cin>>urunNo;
        dosyaOku.open("esyaDeposu.dat",ios::binary);
        dosyaOlustur.open("esyaDeposu.dat",ios::binary|ios::app);

        if(!dosyaOku){
            cout<<"\nDosya Bulunamadi";
            goto menu;
        }

        dosyaOku.seekg(0);
        r=0;

        while(!dosyaOku.eof()){
            dosyaOku.read((char *)&tutar,sizeof(tutar));
            if(!dosyaOku.eof()){
                int x=tutar.urun::numaraDondur();
                if(x==urunNo){
                    dogru=1;
                    dosyaOlustur.seekp(r*sizeof(tutar));
                    system("cls");
                    cout<<"\nMevcut Detaylar";
                    tutar.goster();
                    cout<<"\nYeni Detaylari Giriniz: ";
                    tutar.ekle();
                    cout<<"\nUrun Detaylari Duzenlendi";
                }
            }
            r++;
        }

        if(dogru==0){
            cout<<"Urun Numarasi Mevcut Degil, Lutfen Tekrar Deneyin";
            getch();
            goto db;
        }

        dosyaOku.close();
        getch();
        goto db;

    case 3:
        dogru=0;
        cout<<"\nSilinecek Urun Numarasini Giriniz: ";
        cin>>urunNo;
        dosyaOku.open("esyaDeposu.dat",ios::binary);

        if(!dosyaOku){
            cout<<"\nDosya Bulunamadi";
            goto menu;
        }

        dosyaOku.seekg(0);

        while(dosyaOku.read((char *)&tutar,sizeof(tutar))){
            int x=tutar.urun::numaraDondur();

            if(x!=urunNo){
                gecici.write((char *)&tutar,sizeof(tutar));
            }
            else{
                dogru=1;
            }
        }

        dosyaOku.close();
        gecici.close();
        dosyaOlustur.open("esyaDeposu.dat",ios::trunc|ios::binary);
        dosyaOlustur.seekp(0);
        gecici.open("gecici.dat",ios::binary|ios::in);

        if(!gecici){
            cout<<"Dosyada Hata Var";
            goto db;
        }

        while(gecici.read((char *)&tutar,sizeof(tutar))){
            dosyaOlustur.write((char *)&tutar,sizeof(tutar));
        }

        gecici.close();
        dosyaOlustur.close();

        if(dogru==1){
            cout<<"\nUrun Basariyla Silindi";
        }
        else if(dogru==0){
            cout<<"\nUrun Mevcut Degil, Lutfen Tekrar Deneyiniz";
        }

        getch();
        goto db;

    case 4:
        goto menu;

    default:
        cout<<"\nYanlis Secim, Lutfen Tekrar Deneyiniz";
        getch();
        goto db;
    }

    case 3:
        system("cls");
        dogru=0;
        int urunNo;
        cout<<"\nUrun Numarasini Giriniz: ";
        cin>>urunNo;

        dosyaOku.open("esyaDeposu.dat",ios::binary);

        if(!dosyaOku){
            cout<<"\nDosya Bulunamadi, Program Sonlandirildi";
            goto menu;
        }

        dosyaOku.seekg(0);

        while(dosyaOku.read((char *)&tutar,sizeof(tutar))){
            int x=tutar.urun::numaraDondur();
            if(x==urunNo){
                tutar.ode();
                dogru=1;
                break;
            }
        }

        if(dogru==0){
            cout<<"\nUrun Mevcut Degil, Lutfen Tekrar Deneyin";
        }

        getch();
        dosyaOku.close();
        goto menu;

    case 4:
        system("cls");
        git(20,20);

        cout<<"Cikmak Istediginden Emin Misin? (E/H)";
        char eh;
        cin>>eh;

        if((eh=='E')||(eh=='e')){
            git(12,20);
            system("cls");
            cout<<"******************** Tesekkurler ********************";
            getch();
            exit(0);
        }
        else if((eh=='H')||(eh=='h')){
            goto menu;
        }
        else{
            goto menu;
        }

    default:
        cout<<"Yanlis Secim, Lutfen Tekrar Deneyiniz";
        getch();
        goto menu;
    }

    return 0;
}
























