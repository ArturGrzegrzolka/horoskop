#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <cmath>

using namespace std;

class Cechy
{ public:
	string imie;
	int rok_urodzenia;
	int miesiac_urodzenia;
	int dzien_urodzenia;
	string nazwa_dnia_urodzenia;
	string znak_zodiaku;
	char plec;
	string horoskop_link;
};

Cechy Funboy; //obiekt Funboy opisany przez klase Cechy
Cechy *pFunboy; //deklaracja wskaznika do obiektu

//-------------------------------------------------------------------------------------
bool f_CzyJestYearUrodzenia ( int v_year )
{
int vl_length=0, vl_rok	= v_year;
	SYSTEMTIME st;
	GetSystemTime(&st);
	//cout << "Podany rok to " << v_year<< endl;
	//cout << "Biezacy rok to " << st.wYear<< endl;
	cin.clear();
	cin.sync();
	//sprawdzam z ilu cyfr sklada sie liczba v_year
	do
	{	vl_rok = vl_rok/10;
		vl_length++;
	} while (vl_rok > 0);

	if (v_year		>	st.wYear 		//jesli podany rok jest wiekszy niz biezacy rok
		|| st.wYear-150	>	v_year		//lub jesli biezacy rok - 150 lat jest wiekszy niz podany rok
		|| vl_length	!=	4)			//lub ilosc cyfr w roku jest <> 4 
		{	cout<< "Podales niewlasciwy rok urodzenia. Sprobuj jeszcze raz." << endl;
			getch();
			return false;
		}
	else if (v_year == st.wYear ) 		//jesli podany rok jest rowny biezacemu
		{	cout<< "Jetes za mlody na korzystanie z komputera." << endl;
			getch();
			exit(0);
			return false;
		}
	return true;
}
//-------------------------------------------------------------------------------------
bool f_CzyJestMountUrodzenia ( int v_month  )
{	cin.clear();
	cin.sync();
	if (v_month>12 || v_month<1)		//jesli podany miesiac nie istnieje
		{	cout<< "Podales niewlasciwy miesiac urodzenia. Sprobuj jeszcze raz" << endl;
			getch();
			return false;
		}
	return true;
}

//-------------------------------------------------------------------------------------
bool f_CzyJestDayUrodzenia ( int v_day, int v_month, int v_year )
{
	int vl_max_day, i=0;
	int vl_tab_31[7]={1,3,5,7,8,10,12};
	int vl_tab_30[4]={4,6,9,11};
	int vl_tab_28[1]={2};

	cin.clear();
	cin.sync();
	
	//jesli miesiac to luty
	if (v_month==2 )
	{	//okreslenie czy rok byl przestepny
		if((v_year%4==0 && !(v_year%100==0)) || (v_year%400==0))
			{vl_max_day = 29;}
		else
			{vl_max_day = 28;}

		for( i=0; i < sizeof(vl_tab_28)/sizeof(int); i++)
		{	if( vl_tab_28[i] == v_month && (v_day>0 && v_day<vl_max_day+1))
				return true;	
			else
				cout<< "W roku "<<v_year<<" ilosc dni w lutym wynosila: "<<vl_max_day<<endl;
		}
	}
	else
	{	//cout<<"jesli miesiac ma 31 dni"<<endl;
		for( i=0; i < sizeof(vl_tab_31)/sizeof(int); i++)
		{	if( vl_tab_31[i] == v_month && (v_day>0 && v_day<32))
				{	//cout<<"i: "<< i <<" "<<vl_tab_31[i]<<"v_month"<<v_day<<endl;
					return true; }
		}
		//cout<<"jesli miesiac ma 30 dni"<<endl;
		for( i=0; i < sizeof(vl_tab_30)/sizeof(int); i++)
		{	if( vl_tab_30[i] == v_month && (v_day>0 && v_day<31))
			{	//cout<<"i: "<< i <<" "<<vl_tab_30[i]<<"v_month"<<v_day<<endl;
				return true;}
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------
string f_OdgadnijDzienUrodzin ( int v_day, int v_month, int v_year )
{
	time_t czas;
	struct tm * data;
	const char * dzien_tygodnia[] = { "Niedziela", "Poniedzialek","Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota" };

	time( & czas );
	data = localtime( & czas );
	data->tm_year = v_year - 1900;
	data->tm_mon = v_month - 1;
	data->tm_mday = v_day;

	mktime( data );
	return dzien_tygodnia[ data->tm_wday ];
}
//-------------------------------------------------------------------------------------
bool f_CzyPoprawneImie ( string v_name )
{
	int vl_NameLength, i, j, vl_ZnalezionaLiterka=0;
	char tl_ZbiorZnakow[53]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

	vl_NameLength = v_name.length();
	//cout<<"vl_NameLength"<<vl_NameLength<<endl;
	for (i=0; i<vl_NameLength; i++)
	{
		//cout<<"litera : "<< v_name[i] <<endl;
		for (j=0; j<52; j++)
		{
			if (v_name[i] == tl_ZbiorZnakow[j])
			{	//cout<<"literka : "<< tl_ZbiorZnakow[j] <<endl;
				vl_ZnalezionaLiterka++;
				exit;}
		}
	}
	//cout<<"vl_ZnalezionaLiterka: "<<vl_ZnalezionaLiterka<<endl;
	if (v_name.length() == vl_ZnalezionaLiterka)
		{	//getch();
			return true;
		}
	else
		{cout<< "Wpisane imie jest niepoprawne. Sprobuj jeszcze raz.";}
return false;
}
//-------------------------------------------------------------------------------------
string f_ImieInitCap ( string v_name )
{
	string lv_name = v_name;
	lv_name[0] = toupper(lv_name[0]);
	//v_name=lv_name;
return lv_name;
}
//-------------------------------------------------------------------------------------
/*wyznaczanie plci*/
char f_SprawdzPlec (string v_name)
{
	const string v_imiemeskie[] = {"Barnaba", "Bonawentura", "Jarema", "Jona", "Kosma", "Dyzma"};
	const string v_imiezenskie[] = {"Beatrycze", "D¿anan", "Mariam", "Miriam", "Megi", "Noemi", "Rut", "Szarlin"};
	int v_nietypoweimie = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v_name == v_imiemeskie[i])
		{
			return 'M';
			int v_nietypoweimie = 1;
			break;
		}
	};
	for (int i = 0; i < 8; i++)
	{
		if (v_name == v_imiezenskie[i])
		{
			return 'K';
			int v_nietypoweimie = 1;
			break;
		}
	};
	if (v_nietypoweimie == 0)
	{
		if (v_name[v_name.length() - 1] == 'a')
		{	
			return 'K';
		}
		else
		{
			return 'M';
		};
	}
}
/*wyznaczanie plci*/
/*znak zodiaku*/
string f_Zodiak(int v_day, int v_month)
{
	switch (v_month)
		{
			case 1:
				if (v_day < 20) {return "Koziorozec";}
				else{return "Wodnik";};
				break;
			case 2:
				if (v_day < 19) {return "Wodnik";}
				else{return "Ryby";};
				break;
			case 3:
				if (v_day < 21) {return "Ryby";}
				else{return "Baran";};
				break;
			case 4:
				if (v_day < 20) {return "Baran";}
				else{return "Byk";};
				break;
			case 5:
				if (v_day < 23) {return "Byk";}
				else{return "Bliznieta";};
				break;
			case 6:
				if (v_day < 22) {return "Bliznieta";}
				else{return "Rak";};
				break;
			case 7:
				if (v_day < 23) {return "Rak";}
				else{return "Lew";};
				break;
			case 8:
				if (v_day < 24) {return "Lew";}
				else{return "Panna";};
				break;
			case 9:
				if (v_day < 23) {return "Panna";}
				else{return "Waga";};
				break;
			case 10:
				if (v_day < 23) {return "Waga";}
				else{return "Skorpion";};
				break;
			case 11:
				if (v_day < 22) {return "Skorpion";}
				else{return "Strzelec";};
				break;
			case 12:
				if (v_day < 22) {return "Strzelec";}
				else{return "Koziorozec";};
				break;
		};
}
/*znak zodiaku*/
/*link do horoskopu*/
string f_HoroskopLink (string v_zodiac)
{
	string url = "https://www.horoskop360.pl/horoskop-";
	string url_part2 = v_zodiac;
	url_part2[0] = tolower(url_part2[0]);
	return url + url_part2;
}

int f_OtworzLinkHoroskop (string v_zodiac)
{
	string v_url;
	v_url = f_HoroskopLink(v_zodiac);
	ShellExecuteA(NULL, "open", v_url.c_str(), NULL, NULL, SW_SHOWNORMAL);
	return 0;
}
/*link do horoskopu*/
/*przeliczanie daty na kalendarz julianski*/
double f_NaKalendarzJulianski(int v_day, int v_month, int v_year)
{
	return (1729279.5 + 367 * v_year + floor(275 * v_month / 9) - floor(7 * (4716 + v_year + floor((v_month + 9) / 12)) / 4) + v_day) + 38 - floor(3 * (floor((4716 + v_year + floor((v_month + 9) / 12) + 83) / 100) + 1) /4);
}
/*przeliczanie daty na kalendarz julianski*/
/*wyznaczanie fazy ksiezyca w dniu urodzin*/
/*wyznaczanie fazy ksiezyca w dniu urodzin*/
//-------------------------------------------------------------------------------------
void f_PodajDane ()
{
	int v_day, v_month, v_year;
	bool v_czyPoprawneDane = false;
	string v_name, v_dzienUrodzin, v_zodiac;
	char v_gender;

	do
	{ 	cin.clear();
		cin.sync();
		system("cls");
		cout<<"podaj rok urodzenia" <<endl;
		cin>>v_year;
		v_czyPoprawneDane = f_CzyJestYearUrodzenia( v_year );
	} while (v_czyPoprawneDane == false);

	v_czyPoprawneDane = false;
	do
	{ 	cin.clear();
		cin.sync();
		cout<<"podaj miesiac urodzenia" <<endl;
		cin>>v_month;
		v_czyPoprawneDane = f_CzyJestMountUrodzenia( v_month );
	} while (v_czyPoprawneDane == false);

	//cout<< "true: "<< true<<endl;
	//cout<< "false:"<< false<<endl;
	//cout << "v_czyYear:  "<<v_czyYear << endl;
	//cout << "v_czyMount: "<<v_czyMount << endl;

	v_czyPoprawneDane = false;
	do
	{	cin.clear();
		cin.sync();
		cout<<"podaj dzien urodzenia" <<endl;
		cin>>v_day;
		v_czyPoprawneDane = f_CzyJestDayUrodzenia( v_day, v_month, v_year);
		//cout << "v_czyDay: "<<v_czyDay << endl;
	} while (v_czyPoprawneDane== false);

	v_czyPoprawneDane = true; //po zrobieniu walidacji zmien na false
	do
	{	cin.clear();
		cin.sync();
		cout<<"Podaj imie" <<endl;
		cin>>v_name;
		v_czyPoprawneDane = f_CzyPoprawneImie( v_name) ;	//wywolanie funkcji do walidacji imienia czy np. user nie wpisal 1234...
	} while (v_czyPoprawneDane== false);
	v_name = f_ImieInitCap(v_name);							//initcap - niezaleznie od tego co user wpisal.
	v_dzienUrodzin = f_OdgadnijDzienUrodzin(v_day, v_month, v_year);
	v_gender = f_SprawdzPlec(v_name);
	v_zodiac = f_Zodiak(v_day, v_month);

	pFunboy = &Funboy;
	pFunboy->imie=v_name;
	pFunboy->rok_urodzenia=v_year;
	pFunboy->miesiac_urodzenia=v_month;
	pFunboy->dzien_urodzenia=v_day;
	pFunboy->nazwa_dnia_urodzenia=v_dzienUrodzin;
	pFunboy->znak_zodiaku=v_zodiac;
	pFunboy->plec=v_gender;
	pFunboy->horoskop_link=f_HoroskopLink(v_zodiac);

	cin.clear();
	cin.sync();
	system("cls");
	cout << "Czesc "<< pFunboy->imie <<". "<<endl;
	cout << "Data Twoich narodzin to: " <<pFunboy->dzien_urodzenia<<"/"<<pFunboy->miesiac_urodzenia<<"/"<<pFunboy->rok_urodzenia<<endl;
	cout << "Dzien twoich urodzin to: " << pFunboy->nazwa_dnia_urodzenia <<endl;
	cout << "Twoja plec to: ";
	if(pFunboy->plec == 'K'){cout << "Kobieta";} else {cout << "Mezczyzna";};
	cout << endl;
	cout << "Twoj znak zodiaku to: " << pFunboy->znak_zodiaku << endl;
	cout << "Link do Twojego horoskopu: " << f_HoroskopLink(v_zodiac) << endl;
	cout << "Kliknij dowolny przycisk, zeby otworzyc horoskop w przegladarce." << endl;
	getch();
	f_OtworzLinkHoroskop(v_zodiac);

	cout << "Press any key to continue... " <<endl;
	getch();
}

//-------------------------------------------------------------------------------------
void f_Zapisz_do_pliku ()
{
	fstream plik;
	pFunboy = &Funboy;
	plik.open( "zodiak.txt", ios::out | ios::app );
		plik<<pFunboy->imie<<';';
		plik<<pFunboy->rok_urodzenia<<';';
		plik<<pFunboy->miesiac_urodzenia<<';';
		plik<<pFunboy->dzien_urodzenia<<';';
		plik<<pFunboy->nazwa_dnia_urodzenia<<';';
		plik<<pFunboy->znak_zodiaku<<';';
		plik<<pFunboy->plec<<';';
		plik<<pFunboy->horoskop_link<< endl;
		plik.flush();
	plik.close();
}

int main()
{	//srand(time ( 0 ) );

	Cechy *pFunboy; //deklaracja wskaznika do obiektu
	char v_znak;
	pFunboy = &Funboy;

	do
	{
		cin.clear();
		cin.sync();
		system("cls");
		cout <<"Program Horoskop."<< endl;
		cout <<" "<< endl;
		cout <<"Program stworzony na zaliczenie cwiczen z Podstaw Programowania."			<< endl;
		cout <<"Funkcjonalnosci programu:"													<< endl;
		cout <<"1. Podanie imienia i daty urodzenia"										<< endl;
		cout <<"2. Okreslenie dnia tygodnia na podstawie daty urodzenia"					<< endl;
		cout <<"3. Zmiana koloru czcionki w zaleznosci od dnia tygodnia z daty urodzenia"	<< endl;
		cout <<"4. Stworzenie/otwarcie bazy danych"											<< endl;
		cout <<"5. Okreslenie plci na podstawie imienia"									<< endl;
		cout <<"6. Wyznaczenie wieku uzytkownika"											<< endl;
		cout <<"7. Rozpoznanie znaku zodiaku"												<< endl;
		cout <<"8. Zwrocenie horoskopu"														<< endl;
		cout <<"9. Wyznaczenie fazy ksiezyca w dniu urodzin"								<< endl;
		cout <<"10.Import danych do glownej bazy danych"									<< endl;
		cout <<"11.Funkcja zwracajaca pelna zawartosc bazy danych"							<< endl;
		cout <<"12.Agregaty na bazie danych"												<< endl<< endl;
		cout <<"Aby rozpoczac korzystanie z programu wcisnij 1, aby zakonczyc dzialanie programu wcisnij W."<< endl << endl;
		cout<<"Dokonaj wyboru :";

		v_znak = getchar();
		if (v_znak=='W')
		{
			exit(0);
		}

	} while (v_znak!='1');

	do
	{
		cin.clear();
		cin.sync();
		system("cls");
		cout <<"********************* MENU *********************"	<< endl;
		cout << "1. Okreslenie dnia tygodnia z daty urodzenia	"	<< endl;
		cout << "   Okreslenia plci na podstawie imienia		"	<< endl;
		cout << "   Wyznaczenie wieku uzytkownika				"	<< endl;
		cout << "   Rozpoznanie znaku zodiaku					"	<< endl;
		cout << "   Wyswietl horoskop							"	<< endl;
		cout << "   Wyznaczenie fazy ksiezyca w dniu urodzin	"	<< endl;
		cout << "2. Wyswietl historie							"	<< endl;
		cout << "3. Dodaj dane z pliku							"	<< endl;
		cout << "4. Pokaz agregaty								"	<< endl;
		cout << "W. Wyjscie z programu							"	<< endl;
		cout<<"Wybieram : ";

		v_znak = getchar();
		switch (v_znak)
		{
			case '1':
				f_PodajDane();
				f_Zapisz_do_pliku();
				
				cin.clear();
				cin.sync();
				system("cls");
				//
					cout<<pFunboy->imie<< endl;
					cout<<pFunboy->rok_urodzenia<< endl;
					cout<<pFunboy->miesiac_urodzenia<< endl;
					cout<<pFunboy->dzien_urodzenia<< endl;
					cout<<pFunboy->nazwa_dnia_urodzenia<< endl;
					cout<<pFunboy->znak_zodiaku<< endl;
					cout<<pFunboy->plec<< endl;
					cout<<pFunboy->horoskop_link<< endl;
				//
				getch();
				break;
			case '2':
				//f_znajdz_url();
				break;
			case '3':
				//f_wyswietl_historie();
				break;
			case 'W':
				exit(0);
				break;
			default:
				cout << "Nie ma takiej opcji w menu."<< flush;
				Sleep(750);
				break;
		}
	} while (v_znak!='W');

	return 0;

}
