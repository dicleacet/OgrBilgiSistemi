//Gerekli kütüphaneler
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

struct ders
{
	char derskodu[10];
	char dersadi[50];
	ders *next;
};

struct ogrenci
{
	char ogrno[15];
	char ad[30];
	char soyad[30];
	ders *dersdugumu;
	ogrenci *next;
};

ogrenci *head = NULL;

//eklenecek dersler için bellekte yer ayırıyoruz.
ders *listekurDers()
{
	ders *node;
	node = (ders *)malloc(sizeof(ders));
	return node;
}

//eklenecek öğrenciler için bellekte yer ayırıyoruz.
ogrenci *listekurOgrenci()
{
	ogrenci *node;
	node = (ogrenci *)malloc(sizeof(ogrenci));
	return node;
}

//ogrenci derslerini bağlıyoruz.
void Dersgirisi(string derskodu, string dersadi, ogrenci *ogr)
{
	ders *temp;
	temp = listekurDers();
	strcpy(temp->dersadi, dersadi.c_str());
	strcpy(temp->derskodu, derskodu.c_str());
	temp->next = NULL;
	if (ogr->dersdugumu == NULL)
		ogr->dersdugumu = temp;
	else
	{
		ders *t;
		t = ogr->dersdugumu;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
}

//ogrenci linkedlistini oluşturuyoruz.
void OgrenciGirisi(string ogrnum, string ograd, string ogrsoyad)
{
	ogrenci *temp;
	temp = listekurOgrenci();
	strcpy(temp->ogrno, ogrnum.c_str());
	strcpy(temp->ad, ograd.c_str());
	strcpy(temp->soyad, ogrsoyad.c_str());
	temp->next = NULL;

	if (head == NULL)
		head = temp;
	else
	{
		ogrenci *t;
		t = head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
}

//ogrenci listesini yazdırıyoruz.
void ogrenciListele()
{
	ogrenci *tp = head;
	while (tp != NULL)
	{
		cout << tp->ogrno << endl
			<< tp->ad << endl
			<< tp->soyad << endl;
		if (tp->dersdugumu != NULL)
		{
			ders *d = tp->dersdugumu;
			while (d != NULL)
			{
				cout << d->dersadi << endl
					<< d->derskodu << endl
					<< endl;
				d = d->next;
			}
		}
		cout
			<< endl;
		tp = tp->next;
	}
}

//Girişi yapılan öğrenci eğer listede varsa sadece dersi eklemek için kullandığımız eşsiz bulma fonksiyonu 
bool itsUnique(string ogrno)
{
	bool kontrol = false;
	ogrenci *tp = head;
	while (tp != NULL)
	{
		if (tp->ogrno == ogrno)
		{
			kontrol = true;
			break;
		}
		tp = tp->next;
	}
	return kontrol;
}

//dosyadan veri okuyup listeye ekleme fonksiyonu 
void VeriGiriisi(string dosyaadi)
{
	ifstream dosyaOku(dosyaadi);
	string satir = "";
	int sayac = 0, forsayac = 0;
	string derskodu = "", dersadi = "";
	if (dosyaOku.is_open())
	{
		while (getline(dosyaOku, satir))
		{
			forsayac = 0;
			int boslukSayisi = 0, isimsayisi = 0;
			string ogrno = "", ogradi = "", ogrsoyadi = "";
			for (int k = 0; k < satir.length(); k++)
				if (satir[k] == ' ')
					boslukSayisi++;
			if (sayac == 0)
				for (int i = 0; i < satir.length(); i++)
					if (forsayac == 0)
						if (satir[i] != ' ')
							derskodu += satir[i];
						else
							forsayac++;
					else
						if (satir[i] != ' ')
							dersadi += satir[i];
			else
				for (int i = 0; i < satir.length(); i++)
					if (forsayac == 0)
						if (satir[i] != '\t')
							ogrno += satir[i];
						else
							forsayac++;
					else
						if (boslukSayisi == 1)
							if (forsayac == 1)
								if (satir[i] != ' ')
									ogradi += satir[i];
								else
									forsayac++;
							else
								ogrsoyadi += satir[i];
						else
							if (forsayac == 1)
								if (satir[i] != ' ')
									ogradi += satir[i];
								else
									if (isimsayisi == 0)
									{
										ogradi += ' ';
										isimsayisi++;
									}
									else
										forsayac++;
							else
								ogrsoyadi += satir[i];
			sayac++;
			if (sayac != 1)
				if (itsUnique(ogrno))
				{
					ogrenci *tp = head, *ogr;
					while (tp != NULL)
					{
						if (tp->ogrno == ogrno)
						{
							ogr = tp;
							break;
						}
						tp = tp->next;
					}
					Dersgirisi(derskodu, dersadi, ogr);
				}
				else
				{
					OgrenciGirisi(ogrno, ogradi, ogrsoyadi);
					ogrenci *tp = head, *ogr = NULL;
					while (tp != NULL)
					{
						if (tp->ogrno == ogrno)
						{
							ogr = tp;
							break;
						}
						tp = tp->next;
					}
					ogr->dersdugumu = NULL;
					Dersgirisi(derskodu, dersadi, ogr);
				}
		}

		dosyaOku.close();
	}
	else
		cout << "açamadı" << endl;
}

//Veri girişi yapılacak txt dosyalarının statik olarak eklemek için kullandığımız fonksiyon
void listeKur()
{
	VeriGiriisi("eng101.txt");
	VeriGiriisi("fiz101.txt");
	VeriGiriisi("mat101.txt");
}

//Ogrenci verilerini listeden silmek için kullanılan fonksiyon 
void ogrenciSil(string ogrno)
{
	if (head == 0)
		cout << "Node silinemez cunku liste bos";
	else
	{
		ogrenci *iter = head;
		ogrenci *trail = 0;
		while (iter != 0)
			if (iter->ogrno == ogrno)
				break;
			else
			{
				trail = iter;
				iter = iter->next;
			}
		if (iter == 0)
			cout << "Boyle bir ogrenci yok" << endl;
		else
			if (head == iter)
			{
				head = head->next;
				cout << "Silindi" << endl;
			}
			else
			{
				trail->next = iter->next;
				cout << "Silindi" << endl;
			}
	}
}

//Ders verilerini bağlı olduğu öğrenci listesinden silmek için kullanılan fonksiyon 
void DersSil(string ogrno, string derskodu)
{
	ogrenci *tp = head;
	while (tp != NULL)
	{
		if (ogrno == tp->ogrno)
			break;
		tp = tp->next;
	}
	if (tp != NULL)
	{
		ders *iter = tp->dersdugumu, *trail = NULL;
		while (iter != NULL)
		{
			if (derskodu == iter->derskodu)
				break;
			else
			{
				trail = iter;
				iter = iter->next;
			}
		}
		if (iter != NULL)
		{
			if (tp->dersdugumu == iter)
				tp->dersdugumu = tp->dersdugumu->next;
			else
				trail->next = iter->next;
			cout<<derskodu << " basari ile silindi" << endl;
		}
		else
			cout << "Boyle bir ders yok" << endl;
	}
	else
		cout << "Boyle bir ogrenci yok" << endl;
}

//Kesişim bulan fonksiyon
void KesisimBul(string drs1, string drs2)
{
	ogrenci *tp = head;
	ders *dp, *rp;
	cout << drs1 << " /// " << drs2 << endl
		<< "--------------------" << endl
		<< endl;
	while (tp != NULL)
	{
		dp = tp->dersdugumu;
		rp = tp->dersdugumu;
		while (dp != NULL)
		{
			if (dp->derskodu == drs1)
				while (rp != NULL)
				{
					if (rp->derskodu == drs2)
					{
						cout << tp->ogrno << endl
							<< tp->ad << endl
							<< tp->soyad << endl
							<< endl;
					}
					rp = rp->next;
				}
			dp = dp->next;
		}
		tp = tp->next;
	}
}

//Numara bilgisiyle arama yapmak için kullanılan fonksiyon
void noAra(string ogrno)
{
	ogrenci *tp = head;
	while (tp != NULL)
	{
		if (tp->ogrno == ogrno)
		{
			cout << tp->ogrno << endl
				<< tp->ad << endl
				<< tp->soyad << endl
				<< endl;
			break;
		}
		tp = tp->next;
	}
}

//Soyadı bilgisiyle arama yapmak için kullanılan fonksiyon
void soyadAra(string ogrsoyad)
{
	ogrenci *tp = head;
	while (tp != NULL)
	{
		if (tp->soyad == ogrsoyad)
		{
			cout << tp->ogrno << endl
				<< tp->ad << endl
				<< tp->soyad << endl
				<< endl;
		}
		tp = tp->next;
	}
}

//Dosyaya yazmak için kullanılan fonksiyon
void dosyaYaz()
{
	ofstream dosyaYaz("students.txt");
	ogrenci *tp = head;
	if (dosyaYaz.is_open())
	{
		while (tp != NULL)
		{
			string dersler = "";
			ders *dp = tp->dersdugumu;
			while (dp != NULL)
			{
				dersler = dersler + " " + dp->dersadi + " " + dp->derskodu + " - ";
				dp = dp->next;
			}
			dosyaYaz << tp->ogrno << " ||| " << tp->ad << " ||| " << tp->soyad << " ||| " << dersler << endl;
			tp = tp->next;
		}
		cout<<endl<<"DOSYAYA YAZILDI !! "<<endl;
		dosyaYaz.close();
	}
}

//Main fonksiyonu
int main()
{
	listeKur();
	char secim;
	string giris, giris2;
	while (true)
	{
		system("CLS");
		cout << " -----------Yapmak istediginiz islemi seciniz---------- " << endl;
		cout << "Arama yapmak icin: A" << endl;
		cout << "Ders silmek icin: D" << endl;
		cout << "Kesisim bulmak icin: K" << endl;
		cout << "Listeyi ekrana yazmak icin: L" << endl;
		cout << "Ogrenci silmek icin: O" << endl;
		cout << "Dosyaya yaz: Y" << endl;
		cout << "Cikis icin: C" << endl;
		cout << "Lutfen bir secim yapiniz ->  ";
		cin >> secim;
		secim = toupper(secim);

		switch (secim)
		{
		case 'A':
			system("CLS");
			char araSecim;
			cout << "Soyisimn ile arama yapmak icin: A " << endl;
			cout << "Ogr No ile arama yapmak icin: O " << endl;
			cin >> araSecim;
			araSecim = toupper(araSecim);
			switch (araSecim)
			{
			case 'A':
				cout << "Ogr soyadini giriniz: ";
				cin >> giris;
				soyadAra(giris);
				break;
			case 'O':
				cout << "Ogr numarasini giriniz: ";
				cin >> giris;
				noAra(giris);
				break;
			default:
				cout << "Hatali giris!!" << endl;
				break;
			}
			break;
		case 'D':
			cout << "Ogr numarasi giriniz: ";
			cin >> giris;
			cout << "Silinecek ders kodunu giriniz: ";
			cin >> giris2;
			DersSil(giris, giris2);
			break;
		case 'K':
			cout << "1. ders kodunu giriniz: ";
			cin >> giris;
			cout << "2. ders kodunu giriniz: ";
			cin >> giris2;
			KesisimBul(giris, giris2);
			break;
		case 'L':
			ogrenciListele();
			break;
		case 'O':
			cout << "Ogr numarasi giriniz: ";
			cin >> giris;
			ogrenciSil(giris);
			break;
		case 'Y':
			dosyaYaz();
			break;
		case 'C':
		cout<<"Cikiliyor... "<<endl;
		system("PAUSE");

			return (-1);
			break;
		default:
			cout << "Gecersiz giris" << endl;
			break;
		}
		system("PAUSE");
	}
}
