#include <cstdio>
#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

void procAffiche(int nb_allumette){                                             //Fonction Affichage allumettes
    int i;
    cout<<endl;
    for (i=1;i<=nb_allumette;i++){
        cout<<"!";
        if (i%5==0) cout<<endl;
    }
    cout<<endl;
}

int tourJoueur(int allu_saisie,const string nom_joueur){                              //Fonction Tour Joueur
    cout<<"\nLe joueur "<<nom_joueur<<" joue"<<endl;
    cout<<"==========================================================================="<<endl;
    cout<<"Saisir un nombre d'allumette(s) a prendre entre 1 et 3 (O pour abandonner)."<<endl;
    cout<<"==========================================================================="<<endl;
    cin>>allu_saisie;
    if (allu_saisie==0){                                                        //Abandon
        cout<<"Abandon!"<<endl<<"L'ordi remporte la victoire par forfait.";
        return allu_saisie;
    }
    while (allu_saisie!=1 and allu_saisie!=2 and allu_saisie!=3){               //Saisie incorrect
        cout<<"Incorrect."<<endl<<"Choisir un nombre d'allumette(s) entre 1 et 3"<<endl;
        cin>>allu_saisie; 
    }
    return allu_saisie;
}

int tourNiv_bot(int allu_saisie,int nb_allumette,const string niveau){             //Fonction Tour Bot
    int i;
    cout<<"\nL'ordi joue"<<endl;
    if (niveau=="N" or niveau=="n"){                                            //Bot NOVICE
        allu_saisie=(rand()%3)+ 1;                                              
    }else{
        for (i=1;i<=3;i++){                                                     //Bot EXPERT
            if ((nb_allumette-i)%4==1){    
                allu_saisie=i;
                i=4;
                
            }else{
                allu_saisie=1;
            }
        }
    }
    cout<<"============================"<<endl;    
    cout<<"L'ordi prend "<<allu_saisie<<" allumette(s)."<<endl; 
    cout<<"============================"<<endl;
    return allu_saisie;
}

void delay_ms(int i)                                                            //Marque un temps d'arret defini en millisecondes
{
    clock_t start;
    clock_t end;
    start=clock();
    while(((end=clock())-start)<=i);
}

int main()
{
    int nb_allu;
    int allu_choisie;
    string niv;
    string nom;
    string prem;
    int i;
    cout<<"Règle du jeu des allumettes:"                                        //Règle du jeu pour informer le joueur
    "\n     - On dispose un petit tas d'allumettes." 
    "\n     - Chaque joueur prend à tour de rôle de 1 à 3 allumettes."
    "\n     - Le joueur qui prend la dernière allumette a perdu. "
    "\n     - Pour gagner, il faut donc laisser la dernière allumette à son adversaire."
    "\nIci, vous jouerez contre un ordinateur dont vous pourrez choisir la difficulté avec la Lettre N pour naîf ou la lettre E pour expert."<<endl;
    cout<<"\nCommençons"<<endl;
    cout<<"Veullier rentrer votre nom: ";
    cin>>nom;
    cout<<"Choisir le niveau de l'odinateur: ";                                 //N(naîf)ou E(expert)
    cin>>niv;
    while ((niv!="N" and niv!="n")and(niv!="E" and niv!="e")){
      cout<<"Incorrect!"<<endl<<"Choisir E pour expert ou N pour naîf: ";
      cin>>niv;
    }
    cout<<"Saisir un nombre d'allumettes entre 0 et 30: ";
    cin>>nb_allu;
    while (nb_allu<0 or nb_allu>30){                                            //Saisie d'allumette et si 0 impossible de faire une partie donc fin du programme
        cout<<"Incorrect!"<<endl<<"Saisir une valeur entre 0 et 30: ";
        cin>>nb_allu;
    }
    if (nb_allu==0){
        cout<<"Pas de partie"<<endl;
        return 0;
    }
    cout<<"Qui est le premier joueur: ";                                        //(nom)ou(ordinateur)
    cin>>prem;
    while ((prem!=nom and prem!="ordi")and prem!="ordinateur"){
        cout<<"Incorrect!"<<endl<<"\nSaisir votre nom ou ordinateur pour commencer"<<endl;
        cin>>prem;
    }
    procAffiche(nb_allu);
    if (prem=="ordi" or prem=="ordinateur"){
        delay_ms(65000);
        allu_choisie=tourNiv_bot(allu_choisie,nb_allu,niv);
        nb_allu=nb_allu-allu_choisie;
        procAffiche(nb_allu);
        i=1;
    }else{
        delay_ms(65000);
        allu_choisie=tourJoueur(allu_choisie,nom);
        if(allu_choisie==0){
            return 0;
        }
        nb_allu=nb_allu-allu_choisie;
        procAffiche(nb_allu);
        i=0;
    }
    while (nb_allu>=1){
        if (i==1){
            delay_ms(65000);
            allu_choisie=tourJoueur(allu_choisie,nom);
            if(allu_choisie==0){
                return 0;
            }
            nb_allu=nb_allu-allu_choisie;
            procAffiche(nb_allu);
            i=0;
        }else{
            delay_ms(65000);
            allu_choisie=tourNiv_bot(allu_choisie,nb_allu,niv);
            nb_allu=nb_allu-allu_choisie;
            procAffiche(nb_allu);
            i=1;
        }
    }
    if (i==1){
        cout<<"Bien joué tu as gagné !"<<endl;
    }else{
        cout<<"L'ordi triomphe !"<<endl;
    }
    cout<<"Merci d'avoir joué";
}
