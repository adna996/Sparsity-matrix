#include<iostream>
#include<algorithm>
#include "projmatrica.h"

using namespace std;
matrica::matrica(int n, int m)
{
  rows=m;
  cols=n;
  rowhead=new node *[m];
  colhead=new node *[n];
  for (int i=0;i<m;i++){
   rowhead[i]=new node;
   rowhead[i]->nextcol=NULL;
   rowhead[i]->row=i;
  }
  for (int i=0;i<n;i++){
   colhead[i]= new node;
   colhead[i]->nextrow=NULL;
   colhead[i]->col=i;
  }
}

matrica::matrica(int m, int n, vector<pair<pair<int, int>,double>>)
{

}

void matrica::insert_remove(int row,int col,float value)
{
  node *lead, *point, *pre_point;

  if (value==0) //izbacujemo element koji se nalazi na "poziciji"(row, col)
  {
    point=rowhead[row-1]->nextcol;  //row of element that has to remove
    pre_point=rowhead[row-1];
    while (point!=NULL)
    {
      if ((point->row==row )&&(point->col==col))
    {
      pre_point->nextcol=point->nextcol;  //passed
    }
      pre_point=point;
      point=point->nextcol;
    }
    point=colhead[col-1]->nextrow;  //kolona elementa koji treba da bude izbacen
    pre_point=colhead[col-1];
    while (point!=NULL)
    {
      if ((point->row==row)&&(point->col==col))
      {
       pre_point->nextrow=point->nextrow;
      }
     pre_point=point;
	 point=point->nextrow;
    }
  }
  else   //tada je vrijednost!=0
 {
  lead=new node;
  lead->value=value;
  lead->row=row;
  lead->col=col;
  lead->nextcol=NULL;
  lead->nextrow=NULL;

  point=rowhead[row-1]->nextcol;
  if (rowhead[row-1]->nextcol==NULL)
   rowhead[row-1]->nextcol=lead;
  else
  {
   pre_point=rowhead[row-1];
   while ((point->nextcol!=NULL) &&(point->col<col))
   {
    pre_point=point;
    point=point->nextcol;
   }
   if (point->col>col)
   {
    pre_point->nextcol=lead;
    lead->nextcol=point;
   }
   else if (point->col<col)
   {
    point->nextcol=lead;
   }
   else if (point->col==col)
   {
    pre_point->nextcol=lead;
    lead->nextcol=point->nextcol;
   }
  }
  point=colhead[col-1]->nextrow;
  if (colhead[col-1]->nextrow==NULL)
  colhead[col-1]->nextrow=lead;
  else
  {
   pre_point=colhead[col-1];
   while ((point->nextrow!=NULL) &&(point->row<row))
   {
    pre_point=point;
    point=point->nextrow;
   }
   if (point->row>row)
   {
     pre_point->nextrow=lead;
     lead->nextrow=point;
   }
   else if (point->row<row)
   {
    point->nextrow=lead;
   }
   else if (point->row==row)
   {
    pre_point->nextrow=lead;
    lead->nextrow=point->nextrow;
   }
  }
 }
}

void matrica::sabiranje(matrica b)
{
    node *lead1, *lead2;
    int m,n,m1,n1,i,j,kq;
    m=rows;  //rows1 and cols1 are stored size of matrix 1 when call init_matrix1
    n=cols;
    m1=b.rows;
    n1=b.cols;
    if ((m!=m1) || (n!=n1))
    {
        cout<<("Razlicite dimenzije matrice!");
        return;
    }
    matrica c(rows,cols);
    for (i=0;i<m;i++){  // matrica c ona u kojoj cuvamo rezultat
    for (j=0;j<n;j++)
    {
        kq=0;
        if (rowhead[i]->nextcol!=NULL){
            lead1=rowhead[i]->nextcol;
            while (lead1!=NULL)
                { if ((lead1->row==(i+1)) && (lead1->col==(j+1)))
                  kq=kq+lead1->value;
                  lead1=lead1->nextcol;
                }
        }
        if (b.rowhead[i]->nextcol!=NULL){
            lead2=b.rowhead[i]->nextcol;
            while (lead2!=NULL)
            { if ((lead2->row==(i+1)) && (lead2->col==(j+1)))
              kq=kq+lead2->value;
              lead2=lead2->nextcol;
            }
        }
   if (kq!=0)
        c.insert_remove(i+1,j+1,kq);
    }
  }
}
void matrica::oduzimanje(matrica b)
{
    node *lead1, *lead2;
    int m,n,m1,n1,i,j,kq;
    m=rows;  //rows1 and cols1 are stored size of matrix 1 when call init_matrix1
    n=cols;
    m1=b.rows;
    n1=b.cols;
    if ((m!=m1) || (n!=n1))
    {
        cout<<"Razlicite dimenzije matrice!";
        return;
    }
    matrica c(rows,cols);
    for (i=0;i<m;i++){  // matrica c ona u kojoj cuvamo rezultat
    for (j=0;j<n;j++)
    {
        kq=0;
        if (rowhead[i]->nextcol!=NULL){
            lead1=rowhead[i]->nextcol;
            while (lead1!=NULL)
                { if ((lead1->row==(i+1)) && (lead1->col==(j+1)))
                  kq=kq-lead1->value;
                  lead1=lead1->nextcol;
                }
        }
        if (b.rowhead[i]->nextcol!=NULL){
            lead2=b.rowhead[i]->nextcol;
            while (lead2!=NULL)
            { if ((lead2->row==(i+1)) && (lead2->col==(j+1)))
              kq=kq-lead2->value;
              lead2=lead2->nextcol;
            }
        }
   if (kq!=0)
        c.insert_remove(i+1,j+1,kq);
    }
  }
}

void matrica:: mnozenje(matrica b)
{
  node *lead1, *lead2;
    int m,n,i,j,kq,k,m1,n1;
    m=rows;
    n=b.cols;
    if (cols!=b.rows)
    {
        cout<<"Neregularne dimenzije matrice!";
        return;
    }
    matrica c(rows,b.cols);
    for (i=0;i<m;i++){
        if (rowhead[i]->nextcol!=NULL) //
        for(k=0;k<n;k++){
            kq=0;
            lead1=rowhead[i]->nextcol;
            while (lead1!=NULL)
            {
                lead2=b.colhead[k]->nextrow;
                while (lead2!=NULL){
                    if (lead1->col==lead2->row)
                        kq=kq+lead1->value*lead2->value;
                    lead2=lead2->nextrow;
                }
                lead1=lead1->nextcol;
            }
        if (kq!=0)
            c.insert_remove(i+1,k+1,kq);
     }
   }
}
