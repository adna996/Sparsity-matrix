#ifndef PROJMATRICA_H_INCLUDED
#define PROJMATRICA_H_INCLUDED
#include<iostream>
#include<algorithm>
#include<utility>
using namespace std;

struct node {
  node *nextcol; //pokazivac na sljedeci u koloni
  node *nextrow; //pokazivac na sljedeci u redu
  int row; //red
  int col; //kolona
  int value; //vrijednost
};

class matrica {
  node **colhead; //pokazivac kolona
  node **rowhead; // pokazivac reda
  int rows,cols; //oznacava broj redova i kolona
  public:
    matrica(int m, int n); //matrica sa m redova i n kolona
    matrica(int m, int n, vector<pair<pair<int,int>,double>>);
    void sabiranje(matrica b); //sabiranje 2 matrica
    void oduzimanje(matrica b); //oduzimanje 2 matrica
    void mnozenje(matrica b); //mnozenje matrica
    void stepenovanje(matrica b); //stepenovanje matrica
    void trans(matrica b); //transponovanje matreica
    void insert_remove(int row,int col,float value);//dodajemo elemente ili ih izbacujemo ako je vrijednost elementa 0
                                                   //pomocna funkcija
    int getRed() //geter broja redova matrice
    {
        return rows;
    }
    int getKol() //geter broja kolona matrice
    {
        return cols;
    }
};

#endif // PROJMATRICA_H_INCLUDED
