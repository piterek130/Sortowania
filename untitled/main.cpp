#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <iomanip>

using namespace std;
using namespace chrono;

#define KONFIGSIZE 26
string konfig [KONFIGSIZE];
int *liczby;
vector<pair<float, int>> czasIWielkoscInstancji;

// Wyswietlanie stanu obliczen
void print_progress(double progress) {
    // Szerokosc paska progresu
    const int progressbar_width = 50;
    // Okreslenie pozycji kursora
    int position = progress * progressbar_width;
    std::cout << "STAN: [";
    for(int i = 0; i < progressbar_width; i++){
        if( i < position)
            std::cout << '#';
        else
            std::cout << '.';
    }
    std::cout << "] " << std::setprecision(0) << std::fixed << (progress * 100) << '%' << std::endl;
}

//ZAMIANA STRINGA NA INTA
int strToInt(const std::string& s)
{
    bool negative = false;
    int tmp = 0;
    int i = 0;
    if(s[0] == '-')
    {
        i++;
        negative = true;
    }
    while(i<s.size())
    {
        tmp = 10 * tmp + s[i] - '0';
        i++;
    }
    return negative ? -tmp : tmp;
}

//ZAMIANA DOWCH LICZB ZE SOBA
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// SORTOWANIE BABELKOWE
void bubbleSort(int arr[], int r, int l) {
    int i, j;
    for (i = l; i < r - 1; i++) {
        //print_progress((float)i/(r-2));
        // Last i elements are already in place
        for (j = l; j < r - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
    }
}

// WYSWIETLENIE TABLICY
void printArray(int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf( " %d", liczby[i]);
    printf("\n");
}
void printArray()
{
    int i;
    for (i = 0; i < czasIWielkoscInstancji.size(); i++)
        printf("czas: %f wielkoscInstancji: %d", czasIWielkoscInstancji[i].first, czasIWielkoscInstancji[i].second);
    printf("\n");
}

//USUWANIE SPACJI
string usuwanieSpacji(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i]==' ')
        {
            str.erase(i,1);
            i--;
        }
    }
    return str;
}

// ODCZYT LICZB Z PLIKU
int odczytLiczb(int j)
{
    ifstream plik(konfig[0]); // otwórz plik do odczytu

    if (!plik.is_open()) // sprawdź, czy plik został otwarty
    {
        cerr << "Nie można otworzyć pliku!\n";
        return -1;
    }
    int iloscLiczb = strToInt(konfig[j]);

    liczby = new int [iloscLiczb];

    int i = 0;
    string line;
    //for (i = 0; i< iloscLiczb; i++)
    while(i<iloscLiczb)
    {
        if(!getline(plik, line, ','))break; // odczytaj linie z pliku
        liczby[i] = strToInt(usuwanieSpacji(line));
        //cout << liczby[i] << '\n'; // wypisz linię na standardowe wyjście
        i++;
    }

    plik.close(); // zamknij plik
    return i + 1;
}

// ODCZYT KONFIGA Z PLIKU
void odczytZPliku()
{
    ifstream plik("C:\\Users\\piter\\OneDrive\\Pulpit\\github1\\untitled\\konfig.txt"); // otwórz plik do odczytu

    if (!plik.is_open()) // sprawdź, czy plik został otwarty
    {
        cerr << "Nie można otworzyć pliku!\n";
    }
    int i;
    for (i = 0; i<KONFIGSIZE; i++)
    {
        getline(plik, konfig[i]); // odczytaj linie z pliku
        //strToInt(konfig1[i]);
        cout << konfig[i] << '\n'; // wypisz linię na standardowe wyjście
    }

    plik.close(); // zamknij plik
}

// SORTOWANIE KOKTAILOWE
void CocktailSort(int iloscLiczb) {
//    auto startClock = high_resolution_clock::now();
    bool swapped = true;             // flaga sprawdzajaca czy doszklo do wymiany w danej iteracji
    int start = 0;
    int end = iloscLiczb - 1;
    int compares = 0;               // liczba porownan
    int shifts = 0;                 // liczba przesuniec
    int temp = 0;

    //cout <<"Metoda sortowania: KOKTAJLOWE\n";

    while(swapped == true) {            // dopoki tablica nie jest jeszcze posortowana
        swapped = false;                // wyzerowanie flagi

        for (int i = start; i < end; i++) { // podobnie jak w buublesort petla od lewej do prawej
            compares++;
            if(liczby[i] > liczby[i+1]) {             // jesli nie posortowane to zamien
                shifts++;
                swapped = true;             // doszlo do wymiany
                temp = liczby[i];
                liczby[i] = liczby[i+1];
                liczby[i+1] = temp;
            }
        }

        if (swapped = false) {              // jesli nie doszlo do wymiany to koniec
            break;
        }

        end--;                              // poniewaz ostatni element jest na dobrej pozycji zmniejszamy zasieg petli

        for (int i = end - 1; i >= start; i--) {    // od prawej do lewej porownujac jak poprzednio
            compares++;
            if(liczby[i] > liczby[i+1]) {             // jesli nie posortowane to zamien
                shifts++;
                swapped = true;             // doszlo do wymiany
                temp = liczby[i];
                liczby[i] = liczby[i + 1];
                liczby[i + 1] = temp;
            }
        }

        start++;                            // przesuniecie poczatku poniewaz po ostatniej petli jest on na dobrej pozycji

    }
//    auto stop = high_resolution_clock ::now();
//    auto duration = duration_cast<microseconds >(stop - startClock);
//    cout << "Czas wykonania algorytmu: "
//         << (float)duration.count()/1000000 << " sekund" << endl;
}

int PartitionLamuto(int L, int R) {
    int boarder = L - 1;
    int pivot = liczby[R];

    for (int i = L; i < R; ++i) {
        if (liczby[i] < pivot)
        {
            boarder++;
            int tmp = liczby[boarder];
            liczby[boarder] = liczby[i];
            liczby[i] = tmp;
        }
            //swap(++boarder, i);
    }
    //swap(++boarder, R);
    boarder++;
    int tmp = liczby[boarder];
    liczby[boarder] = liczby[R];
    liczby[R] = tmp;
    return boarder;
}

// SZYBKIE SORTOWANIE
int chuj = 0;
void QuickSortR(int L, int R, int iloscLiczb) {
    if (R - L + 1 <= 1) {
        //print_progress((float)chuj++/iloscLiczb);
        //bubbleSort(liczby, R, L);
        return;
    }

    int q = PartitionLamuto(L, R);
    QuickSortR(L, q-1, iloscLiczb);
    QuickSortR(q+1, R, iloscLiczb);

}

// SPRAWDZENIE CZY DANA JEST LICZBA
bool isNumber(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// WYBOR SORTOWANIA
string rodzajSortowania ()
{
    int i = 1;
    while (isNumber(konfig[i++]));
    return konfig[i-1];
}

// ZAPIS DO PLIKU
int zapisDoPlikuPosortowane(int iloscLiczb)
{
    fstream plik;
    plik.open("C:\\Users\\piter\\OneDrive\\Pulpit\\github1\\untitled\\wynik.txt", ios::out);
    if (!plik.is_open()) {
        cerr << "Nie można otworzyć pliku!\n";
        return -1;
    }

    for (int i = 0; i < iloscLiczb; i++) {
        plik << liczby[i] << '\n';
    }
    plik.close();
}

// ZAPIS DO PLIKU
int zapisDoPlikuCzas(int j)
{
    fstream plik;
    if (j == 1)
        plik.open("C:\\Users\\piter\\OneDrive\\Pulpit\\github1\\untitled\\wynikCzas.txt", ios::out);
    else
        plik.open("C:\\Users\\piter\\OneDrive\\Pulpit\\github1\\untitled\\wielkoscInstancji.txt", ios::out);
    if (!plik.is_open()) {
        cerr << "Nie można otworzyć pliku!\n";
        return -1;
    }


    for (int i = 0; i < czasIWielkoscInstancji.size(); i++) {
        j == 1 ?
        plik << czasIWielkoscInstancji[i].first << '\n' : plik << czasIWielkoscInstancji[i].second << '\n';
    }
    plik.close();
}

void heapify(int liczby[], int n, int i) {
    int largest = i; // węzeł o największej wartości
    int l = 2*i + 1; // lewe dziecko
    int r = 2*i + 2; // prawe dziecko

    // Sprawdzamy, czy lewe dziecko jest większe od węzła
    if (l < n && liczby[l] > liczby[largest])
        largest = l;

    // Sprawdzamy, czy prawe dziecko jest większe od węzła
    if (r < n && liczby[r] > liczby[largest])
        largest = r;

    // Jeśli największy węzeł nie jest korzeniem
    if (largest != i) {
        swap(liczby[i], liczby[largest]);

        // Rekurencyjnie wywołujemy heapify dla poddrzewa, które może być zmienione
        heapify(liczby, n, largest);
    }
}

void heapSort(int liczby[], int n) {
    // Budujemy kopiec (najpierw z ostatniego węzła, który ma dzieci)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(liczby, n, i);

    // Przechodzimy po elementach kopca i zamieniamy największy element z ostatnim elementem
    for (int i=n-1; i>=0; i--) {
        swap(liczby[0], liczby[i]);

        // Wywołujemy heapify tylko dla poddrzewa o rozmiarze i
        heapify(liczby, i, 0);
    }
}


void countingSort(int arr[], int n) {
    int min = arr[0];
    int max = arr[0];

    for (int i =0; i<n;i++)
    {
        if(min>arr[i])
        {
            min=arr[i];
        }
        if(max<arr[i])
        {
            max=arr[i];
        }
    }
    int size = max-min+1;
    int tab[size];
    for (int i = 0; i < size; ++i)
        tab[i] = 0;
    int przesuniecie;
    if (min<0){
        przesuniecie=min;
    }else{
        przesuniecie=0;
    }
    for (int i = 0; i < n; ++i)
        tab[arr[i]-przesuniecie]++;

    for (int i = 1; i < size; ++i)
        tab[i] += tab[i-1];

    int sortedArr[size];

    for (int i = 0; i < n; ++i)
        sortedArr[--tab[arr[i]-przesuniecie]] = arr[i];

    for (int i=0; i<n;i++)
        arr[i]=sortedArr[i];
}



int main()
{
    odczytZPliku();
    string sortowanie = rodzajSortowania();
    int i = 1;
    while (isNumber(konfig[i]))
    {
        if(sortowanie == "babelkowe")
        {
            //auto start = high_resolution_clock::now();
            cout<<"================================="<<endl;
            int iloscLiczb = odczytLiczb(i)-1;
            auto start = high_resolution_clock::now();
            bubbleSort(liczby, iloscLiczb, 0);
            auto stop = high_resolution_clock ::now();
            auto duration = duration_cast<microseconds >(stop - start);
            //printArray(iloscLiczb);
            zapisDoPlikuPosortowane(iloscLiczb);
            delete[] liczby;
            print_progress((float)i/(KONFIGSIZE-2));
            i++;
            cout<<"================================="<<endl;
            cout<<"Rozmiar instancji "<<iloscLiczb << endl;
//            auto stop = high_resolution_clock ::now();
//            auto duration = duration_cast<microseconds >(stop - start);
            cout << "Czas wykonania algorytmu: "
                 << (double)duration.count()/1000000 << " sekund" << endl;

            czasIWielkoscInstancji.push_back(make_pair((double)duration.count()/1000000, iloscLiczb));
            //printArray();
            zapisDoPlikuCzas(1);
            zapisDoPlikuCzas(2);


        }else if (sortowanie == "koktajlowe")
        {
            //auto start = high_resolution_clock::now();
            cout<<"================================="<<endl;
            int iloscLiczb = odczytLiczb(i)-1;
            auto start = high_resolution_clock::now();
            CocktailSort(iloscLiczb);
            auto stop = high_resolution_clock ::now();
            auto duration = duration_cast<microseconds >(stop - start);
            //printArray(iloscLiczb);
            zapisDoPlikuPosortowane(iloscLiczb);
            delete[] liczby;
            i++;
            cout<<"================================="<<endl;
            cout<<"Rozmiar instancji "<<iloscLiczb << endl;
//            auto stop = high_resolution_clock ::now();
//            auto duration = duration_cast<microseconds >(stop - start);
            cout << "Czas wykonania algorytmu: "
                 << (double)duration.count()/1000000 << " sekund" << endl;

            czasIWielkoscInstancji.push_back(make_pair((double)duration.count()/1000000, iloscLiczb));
            //printArray();
            zapisDoPlikuCzas(1);
            zapisDoPlikuCzas(2);

        }else if (sortowanie == "szybkie")
        {
            auto startClock = high_resolution_clock::now();
            cout<<"================================="<<endl;
            int iloscLiczb = odczytLiczb(i)-1;
            QuickSortR(0,iloscLiczb-1, iloscLiczb);
            //printArray(iloscLiczb);
            zapisDoPlikuPosortowane(iloscLiczb);
            delete[] liczby;
            i++;
            cout<<"================================="<<endl;
            cout<<"Rozmiar instancji "<<iloscLiczb << endl;
            auto stop = high_resolution_clock ::now();
            auto duration = duration_cast<microseconds >(stop - startClock);
            cout << "Czas wykonania algorytmu: "
                 << (double)duration.count()/1000000 << " sekund" << endl;

            czasIWielkoscInstancji.push_back(make_pair((double)duration.count()/1000000, iloscLiczb));
            //printArray();
            zapisDoPlikuCzas(1);
            zapisDoPlikuCzas(2);

        }else if (sortowanie == "kopcowanie")
            {
                //auto start = high_resolution_clock::now();
                cout<<"================================="<<endl;
                int iloscLiczb = odczytLiczb(i)-1;
                //int n = sizeof(liczby) / sizeof(liczby[0]);
                auto start = high_resolution_clock::now();
                heapSort(liczby, iloscLiczb);
                auto stop = high_resolution_clock ::now();
                auto duration = duration_cast<microseconds >(stop - start);
                //printArray(iloscLiczb);
                zapisDoPlikuPosortowane(iloscLiczb);
                delete[] liczby;
                i++;
                cout<<"================================="<<endl;
                cout<<"Rozmiar instancji "<<iloscLiczb << endl;
//            auto stop = high_resolution_clock ::now();
//            auto duration = duration_cast<microseconds >(stop - start);
                cout << "Czas wykonania algorytmu: "
                     << (double)duration.count()/1000000 << " sekund" << endl;

                czasIWielkoscInstancji.push_back(make_pair((double)duration.count()/1000000, iloscLiczb));
                //printArray();
                zapisDoPlikuCzas(1);
                zapisDoPlikuCzas(2);
        }else if (sortowanie == "zliczanie")
        {
            //auto start = high_resolution_clock::now();
            cout<<"================================="<<endl;
            int iloscLiczb = odczytLiczb(i)-1;
            auto start = high_resolution_clock::now();
            countingSort(liczby, iloscLiczb);
            auto stop = high_resolution_clock ::now();
            auto duration = duration_cast<microseconds >(stop - start);
            zapisDoPlikuPosortowane(iloscLiczb);
            delete[] liczby;
            i++;
            cout<<"================================="<<endl;
            cout<<"Rozmiar instancji "<<iloscLiczb << endl;
//            auto stop = high_resolution_clock ::now();
//            auto duration = duration_cast<microseconds >(stop - start);
            cout << "Czas wykonania algorytmu: "
                 << (double)duration.count()/1000000 << " sekund" << endl;

            czasIWielkoscInstancji.push_back(make_pair((double)duration.count()/1000000, iloscLiczb));
            //printArray();
            zapisDoPlikuCzas(1);
            zapisDoPlikuCzas(2);}
    }
//    ofstream plik("C:\\Users\\piter\\OneDrive\\Pulpit\\github1\\untitled\\wynik.txt");
//    if (!plik.is_open()) {
//        cerr << "Nie można otworzyć pliku!\n";
//        return 1;
//    }
//
//    for (int i = 0; i < 30; i++) {
//        plik << liczby[i] << '\n';
//    }
//    plik.close();




    return 0;
}