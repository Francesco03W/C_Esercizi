/*
Un'azienda deve aprire un nuovo magazzino nella provincia di Ferrara e deve decidere in quale paese è più conveniente aprirlo. 
Viene dato un array di strutture, che contiene le coordinate (longitudine e latitudine) dei paesi in cui ci sono punti vendita 
(al massimo 100).
Per ciascun paese si hanno le seguenti informazioni:
- nome: stringa di 20 caratteri (massimo), compreso il terminatore.
- longitudine, latitudine: float.
Si vuole posizionare il magazzino nello stesso paese di uno dei punti vendita; inoltre si desidera fare in modo che la distanza media
che si deve percorrere per arrivare dal magazzino a ciascuno dei punti vendita sia minima.
Si supponga che la distanza da percorrere sia la distanza euclidea.

Esempio: si supponga che l’array di strutture contenga i seguenti dati:

- Topolinia 0 0
- LostVegas 3 4
- Gotham 0 4

Se si posiziona il magazzino a Topolinia:
Per andare a Topolinia si ha distanza 0,
Per LostVegas la distanza è √((3-0)^2+(4-0)^2)=5,
Per Gotham si ha distanza 4.
La media, quindi è di (0+5+4)/3=3

Se il magazzino viene costruito a LostVegas, si hanno le seguenti distanze:
Topolinia 5, LostVegas 0, Gotham 3, quindi la media è (5+0+3)/3=2.667 per tanto è migliore di Topolinia

Se si costruisce il magazzino a Gotham, le distanze sono:
Topolinia 4, LostVegas 3, Gotham 0, per una media di (4+3+0)/3=2.333
Quindi si costruirà il magazzino a Gotham poiché migliore di tutte e 3

Si utilizzi il seguente algoritmo:
1. Nel main, si invochi la funzione di lettura dell’array di strutture (lettura_negozi), poi si invochi la funzione "elabora",
 da implementare nel punto 2; si stampi poi a video il paese in cui si consiglia di costruire il magazzino e la distanza media dai
  punti vendita.
Per semplificare l’immissione, la funzione lettura_negozi è fornita già implementata nel file inizializzazione.txt
2. La funzione "elabora": dato l'array di strutture, calcola il paese in cui costruire il magazzino e la distanza media del magazzino 
dai paesi in cui ci sono punti vendita; fornisce poi questi dati al main.
Per calcolare dove posizionare il magazzino, si può calcolare la distanza media di ogni paese da tutti gli altri punti vendita.
Per calcolare la distanza media dei punti vendita da un paese, si utilizzi una funzione distanza_media, che verrà implementata al 
punto 3.
3. Si implementi la funzione distanza_media, che prende in ingresso, fra i parametri, un paese P da cui si vuole calcolare 
la distanza media dei punti vendita e l'array di strutture.

Per calcolare la distanza euclidea fra due paesi, si utilizzi una funzione distanza e la si implementi.*/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define dim 100

typedef struct negozio
{
    char* nome; //non settare grandezza altrimenti non funziona la lettura
    double longitudine;
    double latitudine;
} negozio; //Il paese è un punto vendita

void distanza(double x1,double x2, double y1, double y2,double *dist)
{
    *dist=sqrt(pow(x1-x2,2))+(pow(y1-y2,2));
}

void distanza_media(negozio *P,int mag_index,negozio N[],int N_negozi,double *distanza_media) //p è l'ipotetico magazzino
{
    double distanza_totale_temp=0;
    double distanza_totale=0;
    int negozi_controllati=0;
    //distanza media tra un magazzino e tutti i negozi
    for (int j = 0; j < N_negozi; j++)
    {
        if(j!=mag_index)
        {
            //allora non è se stesso, calcolo la distanza
            distanza(P->longitudine,N[j].longitudine,P->latitudine,N[j].latitudine,&distanza_totale_temp);
            distanza_totale=distanza_totale+distanza_totale_temp;
            negozi_controllati++;
        }
    }
    *distanza_media=distanza_totale/negozi_controllati;
}


void lettura_negozi(negozio N[], int* N_negozi){
    const int N_elementi = 24;
    int i;
    negozio provincia[] = {
        {"Ferrara",44.830551,11.617699},
        {"Focomorto",44.831528,11.678467},
        {"Palmirano",44.780617,11.695290},
        {"Portomaggiore",44.696968,11.804466},
        {"Molinella",44.617355,11.668510},
        {"Cento",44.728931,11.289482},
        {"Bondeno",44.887257,11.420975},
        {"Mirandola",44.886524,11.063919},
        {"Cenacchio",44.694286,11.430931},
        {"Minerbio",44.623955,11.490326},
        {"Consandolo",44.653023,11.775627},
        {"Argenta",44.614666,11.833305},
        {"Filo",44.587044,11.929092},
        {"Comacchio",44.692577,12.182808},
        {"Lagosanto",44.761604,12.139549},
        {"Codigoro",44.828846,12.107964},
        {"Mesola",44.919842,12.228470},
        {"Alberazzo",44.888229,12.250099},
        {"Goro",44.853191,12.298508},
        {"Donzella",44.930050,12.328033},
        {"Copparo",44.891392,11.825409},
        {"Tamara",44.875580,11.771851},
        {"Pontelagoscuro",44.874119,11.606712},
        {"Spinazzino",44.709904,11.630745}
    };
    for(i = 0; i < N_elementi; i++)
        N[i] = provincia[i];
    (*N_negozi) = N_elementi;
}

void elabora(negozio N[],int N_negozi,char *nome_magazzino,double *distanza_magazzino)
{
    double valori_medi[100]; //uguaglianza tra indici di valori_medi e indici di N[], dato che si parte da 0
    int valori_medi_effettivi=0;

    //prendiamo un ipotetico magazzino
    for (int i = 0; i < N_negozi; i++)
    {
        double dist_media_mag=0;
        negozio Mag;
        Mag=N[i];
        //passo l'ipotetico magazzino e il suo indice, per evitare di calcolare la distanza da se stesso
        distanza_media(&Mag,i,N,N_negozi,&dist_media_mag);
        //allora diciamo che il magazzino ipotetico, di indice i, ha un valore medio di distanza da tutti i negozi
        valori_medi[i]=dist_media_mag;
        valori_medi_effettivi++;
    }
    double dist_media_minore=valori_medi[0]; //inizio dal primo indice per semplicità
    //controllo quale sia il magazzino migliore, prendendo la distanza media minore
    for (int k = 0; k < valori_medi_effettivi; k++)
    {
        if(valori_medi[k]<dist_media_minore)
        {
            dist_media_minore=valori_medi[k];
            //ritorno i valori necessari, alle variabili passate per riferimento
            strcpy(nome_magazzino,N[k].nome);
            *distanza_magazzino=dist_media_minore;
        }

    }
    

}


int main()
{
    int N_negozi=0;
    negozio N[dim];

    char nome_Magazzino[20];
    double distanza_magazzino=0;

    lettura_negozi(N,&N_negozi);
    printf("I negozi inseriti sono: %d\n",N_negozi);

    elabora(N,N_negozi,nome_Magazzino,&distanza_magazzino);

    printf("Il paese consigliato in cui costruire il magazzino è %s che ha distanza media dai negozi di %lf \n",nome_Magazzino,distanza_magazzino);
return 0;
    
}






































