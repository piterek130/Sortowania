#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define KONFIGSIZE 10
string konfig [KONFIGSIZE];
int *liczby;

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

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int r, int l)
{
    int i, j;
    for (i = l; i < r - 1; i++)

        // Last i elements are already in place
        for (j = l; j < r - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

/* Function to print an array */
void printArray(int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", liczby[i]);
    printf("\n");
}
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

void QuickSortR(int L, int R) {
    if (R - L + 1 <= 10) {
        bubbleSort(liczby, R, L);
        return;
    }

    int q = PartitionLamuto(L, R);
    QuickSortR(L, q-1);
    QuickSortR(q+1, R);

}

bool isNumber(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

string rodzajSortowania ()
{
    int i = 1;
    while (isNumber(konfig[i++]));
    return konfig[i-1];
}

int zapisDoPlikuPosortowane(int iloscLiczb)
{
    ofstream plik("C:\\Users\\piter\\OneDrive\\Pulpit\\github1\\untitled\\wynik.txt");
    if (!plik.is_open()) {
        cerr << "Nie można otworzyć pliku!\n";
        return -1;
    }

    for (int i = 0; i < iloscLiczb; i++) {
        plik << liczby[i] << '\n';
    }
    plik.close();
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
            auto start = high_resolution_clock::now();
            cout<<"================================="<<endl;
            int iloscLiczb = odczytLiczb(i)-1;
            bubbleSort(liczby, iloscLiczb, 0);
            printArray(iloscLiczb);
            zapisDoPlikuPosortowane(iloscLiczb);
            delete[] liczby;
            i++;
            cout<<"================================="<<endl;
            cout<<"Rozmiar instancji "<<iloscLiczb << endl;
            auto stop = high_resolution_clock ::now();
            auto duration = duration_cast<microseconds >(stop - start);
            cout << "Czas wykonania algorytmu: "
                 << (double)duration.count()/1000000 << " sekund" << endl;
        }else if (sortowanie == "koktajlowe")
        {
            auto start = high_resolution_clock::now();
            cout<<"================================="<<endl;
            int iloscLiczb = odczytLiczb(i)-1;
            CocktailSort(iloscLiczb);
            printArray(iloscLiczb);
            zapisDoPlikuPosortowane(iloscLiczb);
            delete[] liczby;
            i++;
            cout<<"================================="<<endl;
            cout<<"Rozmiar instancji "<<iloscLiczb << endl;
            auto stop = high_resolution_clock ::now();
            auto duration = duration_cast<microseconds >(stop - start);
            cout << "Czas wykonania algorytmu: "
                 << (double)duration.count()/1000000 << " sekund" << endl;
        }else if (sortowanie == "szybkie")
        {
            auto startClock = high_resolution_clock::now();
            cout<<"================================="<<endl;
            int iloscLiczb = odczytLiczb(i)-1;
            QuickSortR(0,iloscLiczb-1);
            printArray(iloscLiczb);
            zapisDoPlikuPosortowane(iloscLiczb);
            delete[] liczby;
            i++;
            cout<<"================================="<<endl;
            cout<<"Rozmiar instancji "<<iloscLiczb << endl;
            auto stop = high_resolution_clock ::now();
            auto duration = duration_cast<microseconds >(stop - startClock);
            cout << "Czas wykonania algorytmu: "
                 << (float)duration.count()/1000000 << " sekund" << endl;

        }
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