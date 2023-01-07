#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#define Noir "\033[30m"
 #define Rouge "\033[31m"
 #define Vert "\033[32m"
 #define Jaune "\033[33m"
 #define Bleu "\033[34m"
 #define Magenta "\033[35m"
 #define Cyan "\033[36m"
 #define Blanc "\033[37m"
 #define fin "\033[0m\n"
typedef struct elt{ //declaration des structures de donnees : listes pour les pages, et l'livre pour l'index
    int numpage;
    struct elt *suivant;
}elt;
typedef elt* liste;
//declaration de l'index du livre=======================================================++++++
typedef struct information
{
  liste page;
  char mot[30];
}information;
typedef struct index{
    liste page;
    char mot[30];
    struct index *succg, *succd;
}index;
typedef index* livre;
//declaration des donnees===================================================================================
typedef struct donnees{
    int *p;
    int nmbpage;
    char mot[30];
}donnees;
//declaration de la file pour le parcours en largeur=======================================================
typedef struct eltfile{
  livre info;
  struct eltfile *suivant;
}eltfile;
typedef struct file{
  eltfile *tete, *queue;
}file;
//declaration de la pile
typedef struct eltpile{
    livre info;
    struct eltpile *suivant;
}eltpile;
typedef eltpile* pile;
//declaration d'une file qui contient des mots (utilisé pour les chemins)
typedef struct eltfilechemin{
    char mot[30];
    struct eltfilechemin *suivant;
}eltfilechemin;
typedef struct filechemin{
  eltfilechemin *tete, *queue;
}filechemin;
//declaration d'une liste qui contient les chemins d'un arbre (les files)
typedef struct eltlistechemin{
    filechemin info;
    struct eltlistechemin *suivant;
}eltlistechemin;
typedef struct eltlistechemin* listechemin;
 
//fonctions primitives de la file modifie pour être adapte aux nouveaux structures de donnees=============
void enfiler(file *F, livre a);
void defiler(file *F, livre *a);
bool filevide(file F);
//fonctions de tri par selection
void echange(int *xp, int *yp);
void trier(int tab[], int n);
//fonction pour creer la liste de pages=====================================================================
liste creer_liste(int *p, int taille);
//fonction pour inserer un noeud dans l'livre===============================================================
void ajouter_noeud(livre *a,donnees data,int *k);
//fonction Const_Tree avec deux options, saisie manuel, ou saisie par le programme (exemple)
void Const_Tree(livre *a,int x);
//fonction d'affichage de l'arbre par largeur
void affichagelargeur(livre a);
//fonction d'affichage de la structure de l'arbre
void affiche_struct_arbre(livre a);
//fonction de recherche d'un mot, ajout, suppression d'une page;
bool recherche_mot_inserer_supprimer_page(livre *a, char* val, int nv,int x,int pg);
// Fonction d'ajoute une page dans la liste des pages 
void addPage(liste *l, int num);
// Fonction d'aprés un mot et une liste de pages elle cree un noeud d'une arbre 
livre creerNoeud(char *mot, int numPage);
// Fonction pour ajouter un mot et son numéro de page à l'arbre
livre ajouterMot(livre arbre, char *mot, int numPage);
// Fonction pour remplire les mots d'arbre dans un tableau de chaine de caractères 
void storeValues(livre root, information *values, int *index);
// Fonction de tri par insertion on va tri le tableau de mots
void tri_tableau(information *values, int size);
/*Fonction pour construire l'arbre binaire ordonné équilibré à partir d'un tableau
  La fonction Cree_arbre_equlibre utilise une approche de construction de l'arbre 
  en utilisant un algorithme de division et de conquête. */
livre Cree_arbre_equlibre(information *values, int start, int end);
// Fonction pour construire un arbre binaire ordonné équilibré à partir d'un arbre binaire non ordonné
livre Creer_Arbre_Ordonee(livre a);
// Fonction de parcours infixe de l'arbre binaire
void parcoursInfixe(index *root);
// Cette fonction permet de supprimer un mot de l'arbre avec tous les numéros de pages associées au mot.
void supprimerMot(livre *arbre, char *mot);
// ************************************************************les fonctions de la 3 partie ***************************************************************************************************
//primitives de la pile adapté aux nouveaux structures de données
bool pilevide(pile p);
void empiler(pile *p, livre a);
void depiler(pile *p, livre *a);
//pour créer une nouvelle file dans la fonction de chemins
void copierfile(filechemin *destination, filechemin source);
//fonction pour afficher le chemin (le contenu de la file)
void afficherfile(filechemin F);
//procédure qui construit une liste qui contient une file de chemin en utilisant les piles (file de mots représentant un chemin)
void branches(livre a,listechemin *l);
void defilermot(filechemin *F);
void enfilermot(filechemin *F, char *word);
void afficher_chemins(listechemin l);


void menu();
void menu2();
void menu3();
void sortir();
void menupartie3();
void main(){
    
    
    livre a = NULL; listechemin l=NULL;
    int choix=1, e=0,f=0, pg=0, partie=1, page;
    char word[30], input, let, lettre;//variable utiliser quand la lecture des carractére   
    char str[] = Cyan"Bienvenue\033[0m\t" Jaune"Merci de consulter notre projet"fin "\t\tNous Sommes Les etudiants:\n"Magenta"\t\t\t\t\t   MAHDJOUB ABDERRAOUF\n\t\t\t\t\t   SADI MOHAMED MOUAAD\t\t"fin""Vert"\n Voici Notre Projet **********************************************"fin;
    // system("cls");
    for (int i = 0; str[i] != '\0'; i++)
    {   
        printf("%c", str[i]);
        fflush(stdout);
        usleep(15000); // attend 250 ms
    }
    
     while(partie!=0){
      system("cls");
      menu2();
      scanf(" %c",&lettre);
      if(lettre=='1') partie=1;
      else if (lettre=='2') partie=2;
           else if (lettre=='3') partie=3;
               else if (lettre=='0') partie=0;
                    else partie=10;
      if(partie == 1){
        while( let!='0'){
          system("cls");
  parti1: menu();
          scanf(" %c",&let);                          
          switch(let){
            case '0':
                system("cls");
                break;
            case '1':
              system("cls");
              Const_Tree(&a,1);
              if (e==1){e=0;system("cls");  printf(Vert "Construire de l arbre fait avec succes....\nVous pouvez maintenant acceder a la deuxieme partie.\t"fin Cyan"Merci pour votre comprehension"fin); goto ExitPartie1; }
              if (f==1){f=0;system("cls");  printf(Vert "Construire de l arbre fait avec succes....\nVous pouvez maintenant acceder a la deuxieme partie.\t"fin Cyan"Merci pour votre comprehension"fin); goto PARTI3; }
              break;
              
            case '2':
              system("cls");
              Const_Tree(&a,2);
             if (e==1){e=0;  printf(Vert "Construire de l arbre faite avec succes...."fin"Vous pouvez maintenant acceder a la deuxieme partie.\n\tMerci pour votre comprehension\n"); goto ExitPartie1;}break;
            case '3':
              system("cls");
              if(a!=NULL){
                affichagelargeur(a);
              }
              else{
                printf(Rouge"Veuillez construire d'abord l'arbre."fin);
              }
              sortir();
              break;
            case '4':
              system("cls");
              if(a!=NULL){
                affiche_struct_arbre(a);
              }
              else{
                printf(Rouge"Veuillez construire d'abord l'arbre."fin);
              }
              sortir();
              break;
            case '5':
              system("cls");
              if(a!=NULL){
                printf("Entrez un mot : ");
                scanf("%s", word);
                if(recherche_mot_inserer_supprimer_page(&a,word,0,0,0)==false){
                  printf(Rouge"Mot n'existe pas..."fin);
                }
              }
              else{
                printf(Rouge"Veuillez construire d'abord l'arbre."fin);
              }
              sortir();
              break;
            case '6':
              system("cls");
              if(a!=NULL){
                printf("Entrez un mot : ");
                scanf("%s", word);
                printf("\nEntrez la page a inserer : ");
                scanf("%d", &pg);
                  if(recherche_mot_inserer_supprimer_page(&a,word,0,1,pg)==false){
                    printf(Rouge"Mot n'existe pas..."fin);
                  }
                }
              else{
                printf(Rouge"Veuillez construire d'abord l'arbre."fin);
              }
              sortir();
              break;
            case '7':
              system("cls");
              if(a!=NULL){
                printf("Entrez un mot : ");
                scanf("%s", word);
                printf("\nEntrez la page a supprimer : ");
                scanf("%d", &pg);
                if(recherche_mot_inserer_supprimer_page(&a,word,0,2,pg)==false){
                  printf(Rouge"Mot n'existe pas..."fin);
                }
              }
              else{
                printf(Rouge"Veuillez construire d'abord l'arbre."fin);
              }
              sortir();
              break;
            default:
                  system("cls");
                  printf(Rouge"ERREUR! Revenir en arriere ? Y/N"fin);
                   scanf(" %c",&input);
                  while(input!='y' && input!='Y' && input!='n' && input!='N') {
                      system("cls");
                      printf(Rouge"\nERREUR! Tapez y pour revenir ou n pour arreter le programme : "fin);
                      scanf(" %c",&input);
                  }
                  if(!(input=='y' || input == 'Y')) {
                    strcpy (str,Jaune"Merci d'avoir utilise le logiciel!"fin);
                 for (int i = 0; str[i] != '\0'; i++)
    {   
        printf("%c", str[i]);
        fflush(stdout);
        usleep(17000); let='0';
    }
      } 
                      
                    
                  }
            }
        }
      else if(partie == 2){
        system("cls");
        if(a==NULL){
          printf(Rouge"Arbre non construit..."fin Cyan" veuillez le construire d'abord\n Voici la partie 1 taper 1 ou 2 pour construir l arbre "fin); e=1; goto parti1;
        }else
            { while(let!='0'){
            system("cls");
ExitPartie1:menu3 ();
            scanf(" %c", &let);
            
            switch(let){
              case 0:
                  system("cls");
                
                  break;
              case '1':
                system("cls");
              a=Creer_Arbre_Ordonee(a);
                
                break;
              case '2':
       refrche:system("cls");
              printf("tapez "Vert" 1\033[0m pour afficher l arbre ordonnee utilisant "Vert"le parcours Infixe\033[0m \ntaper "Vert" n'importe quoi\033[0m pour afficher l arbre utilisant "Vert"le parcours en largeur \033[0m(En precisant pour chaque noeud le fils gauche et le fils droit)."fin);
               scanf(" %c",&let); 
               if (let=='1')parcoursInfixe(a);else affiche_struct_arbre(a);
              printf(Jaune"\ntapez 1 pour refrche"fin);
              printf(Jaune"\nTapez n'importe quoi pour revenir."fin);
              scanf(" %c",&let); 
              if (let=='1') goto refrche;
              
                break;
              case '3':
                system("cls");
                if(a!=NULL){
                  printf("Entrez un mot : ");
                  scanf("%s", word);
                  if(recherche_mot_inserer_supprimer_page(&a,word,0,0,0)==false){
                    printf(Rouge"Mot n'existe pas..."fin);
                  }
                sortir();
                break;
              case '4':
                system("cls");
                printf("Entrez le mot que vous voulez l ajouter et le num de la page : ");
                scanf("%s%d", word,&page);
                a=ajouterMot(a,word,page);
                sortir();
                break;
              case '5':
      Réessayer: system("cls");
                 printf("Entrez un mot : ");
                 scanf("%s", word);
                 if(recherche_mot_inserer_supprimer_page(&a,word,0,0,0)==false){
                    printf(Rouge"Mot n'existe pas...\ntappez 5 pour Réessayer."fin);
                    scanf("%d",&choix);
                  } else supprimerMot(&a,word);
                      printf(Vert "\nla suppression faite avec succes"fin);
                     if (choix==5) goto Réessayer;
                      sortir();
                break;
                }
              default:
                    system("cls");
                    printf(Rouge"ERREUR! Revenir en arriere ? Y/N"fin);
                    scanf(" %c", &input);
                    while(input!='y' && input!='Y' && input!='n' && input!='N') {
                        system("cls");
                        printf(Rouge"\nERREUR! Tapez y pour revenir ou n pour arreter le programme : "fin);
                        scanf(" %c", &input);
                    }
                    if(!(input=='y' || input == 'Y')) {
                      strcpy (str,Jaune"Merci d'avoir utilise le logiciel!"fin);
                 for (int i = 0; str[i] != '\0'; i++)
    {   
        printf("%c", str[i]);
        fflush(stdout);
        usleep(17000); let='0';
    }
      } 
                        
                   
              }
        } }
        
      
      }
      else if(partie == 3){
        if(a==NULL){system("cls");
          printf(Rouge"Arbre non construit..."fin Cyan" veuillez le construire d'abord\n Voici la partie 1 taper 1 ou 2 pour construir l arbre "fin); f=1; goto parti1;
        }
        else{while(let!='0'){
            printf("\e[1;1H\e[2J");
     PARTI3:menupartie3();
            scanf(" %c", &let);
            switch(let){
              case '0':
                  printf("\e[1;1H\e[2J");
                 strcpy (str,Jaune"Merci d'avoir utilise le logiciel!"fin);
                 for (int i = 0; str[i] != '\0'; i++)
                  {   
                      printf("%c", str[i]);
                      fflush(stdout);
                      usleep(17000); 
                  }
      
                  break;
              case '1':
                printf("\e[1;1H\e[2J");
                branches(a,&l);
                printf(Vert"Liste construite avec success...\n"fin);
                sortir();
                break;
              case '2':
                printf("\e[1;1H\e[2J");
                afficher_chemins(l);
                sortir();
                break;
              default:
                  printf("\e[1;1H\e[2J");
                  printf(Rouge"ERREUR! Revenir en arriere ? Y/N\n"fin);
                  scanf(" %c", &input);
                  while(input!='y' && input!='Y' && input!='n' && input!='N') {
                      printf("\e[1;1H\e[2J");
                      printf(Rouge"\nERREUR! Tapez y pour revenir ou n pour arreter le programme : "fin);
                      scanf(" %c", &input);
                  }
                  if(!(input=='y' || input == 'Y')) {
                      strcpy (str,Jaune"Merci d'avoir utilise le logiciel!"fin);
                 for (int i = 0; str[i] != '\0'; i++)
                  {   
                      printf("%c", str[i]);
                      fflush(stdout);
                      usleep(17000); let='0';
                  }
       
                      
                     
          
        }}}
        
      }}
      else if(partie != 0){
       system("cls");
        printf("Choix erronee...");
        sortir();partie=1;
      }
      else if(partie == 0){
                  system("cls");
           SORT : strcpy (str,Jaune"Merci d'avoir utilise le logiciel!"fin);
                 for (int i = 0; str[i] != '\0'; i++)
                    {   
                      printf("%c", str[i]);
                      fflush(stdout);
                      usleep(17000); 
                    }
      } 
      let='1';
    }

}
//fonctions primitives de la file modifie pour être adapte aux nouveaux structures de donnees=============
void enfiler(file *F, livre a){
  eltfile *t;
  if (F->tete==NULL){
    F->tete = malloc(sizeof(eltfile));
    F->tete->info = a;
    F->tete->suivant = NULL;
    F->queue = F->tete;
  }
  else{
    t = malloc(sizeof(eltfile));
    t->info = a;
    t->suivant = NULL;
    F->queue->suivant= t;
    F->queue = t;
  }
}
void defiler(file *F, livre *a){
  eltfile *t;
  t = F->tete;
  (*a) = t->info;
  F->tete = F->tete->suivant;
  free(t);

}
bool filevide(file F){
  if(F.tete == NULL){
    return true;
  }
  else{
    return false;
  }
}
void echange(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void trier(int tab[], int n)
{                                                   //les fonctions pour trier les pages, on le trie par ordre croissant
                                                    //car la liste est creee en lifo.
    int i, j, max;
    for (i = 0; i < n-1; i++)
    {
        max = i;
        for (j = i+1; j < n; j++)
          if (tab[j] > tab[max])
            max = j;
           if(max != i)
            echange(&tab[max], &tab[i]);
    }
}
//fonction pour creer la liste de pages=========================================================
liste creer_liste(int *p, int taille){
    liste temp,listepage;
    listepage = malloc(sizeof(elt));
    (listepage)->numpage = p[0];
    (listepage)->suivant = NULL;
    for(int i = 1;i<taille;i++){
        temp = malloc(sizeof(elt));
        temp->numpage = p[i];
        temp->suivant = listepage;
        (listepage) = temp;
    }
    return listepage;
}
//fonction pour inserer un noeud dans l'livre
void ajouter_noeud(livre *a,donnees data,int *k){ 
  livre b;
  if (*a==NULL){
    *a = malloc(sizeof(index));
    strcpy((*a)->mot,data.mot);
    (*a)->page = creer_liste(data.p,data.nmbpage);
    (*a)->succd = NULL;
    (*a)->succg = NULL;
  }
  else {
    if (*k>0) {
      if((*a)->succg == NULL && (*a)->succd == NULL){
        b = malloc(sizeof(index));
        strcpy(b->mot,data.mot);
        b->page = creer_liste(data.p,data.nmbpage);
        b->succd = NULL;
        b->succg = NULL;
        (*a)->succg = b;
      }
      else {
      ajouter_noeud(&((*a)->succg),data,k);
      }
    }
    else{
      if((*a)->succg == NULL && (*a)->succd == NULL){
        b = malloc(sizeof(index));
        strcpy(b->mot,data.mot);
        b->page = creer_liste(data.p,data.nmbpage);
        b->succd = NULL;
        b->succg = NULL;
        (*a)->succd = b;
        }
      else{
      ajouter_noeud(&((*a)->succd),data,k);
      }
    }
  }
}
//fonction Const_Tree avec deux possibilites, saisie manuel, ou saisie par le programme (exemple)
void Const_Tree(livre *a,int x){
    srand(time(0));
    *a = NULL;
    int k=1,taille,page;
    liste listepage= NULL;
    donnees data[10], manualdata;
    if (x == 1) { //Choix d'un exemple
        do{printf("Generation d'un exemple avec 10 noeuds : \n\tEntrez le nombre de pages du livre (different de 0): "); 
        scanf("%d", &taille);
        printf("\e[1;1H\e[2J");
        }while(taille==0);
        
        for(int j = 0; j<10;j++){      //initialisation du tableau dynamique de pages
                data[j].nmbpage = (rand()%(taille)) +1;
                data[j].p = malloc(sizeof(int)*data[j].nmbpage);
        }
        strcpy(data[5].mot,"RAM");
        strcpy(data[1].mot,"Processeur");
        strcpy(data[2].mot,"ROM");
        strcpy(data[3].mot,"Ordinateur");
        strcpy(data[4].mot,"Microprocesseur");
        strcpy(data[0].mot,"Disque Dur");
        strcpy(data[6].mot,"Memoire");
        strcpy(data[7].mot,"Carte-mere");
        strcpy(data[8].mot,"Ports");
        strcpy(data[9].mot,"Carte graphique");
        for(int j = 0; j<10;j++){
            for(int i =0; i<data[j].nmbpage;i++){
                data[j].p[i] = i+1;
            }
            trier(data[j].p, data[j].nmbpage);
            ajouter_noeud(a,data[j],&k);
            k *= -1;   //alterner a chaque fois l'insertion du noeud (pour qu'il sois symétrique)
        }
        
    }
    else{
        printf("Entrez le mot (entrez # pour arreter): ");
        scanf("%s", manualdata.mot);
        while(strcmp(manualdata.mot,"#")!=0){
            printf("\nEntrez les pages ou le mot apparait (entrez 0 pour arreter) : ");
            scanf("%d", &page);
            if(page!=0){
                manualdata.p = malloc(sizeof(int));
                manualdata.p[0] = page;
                manualdata.nmbpage = 1;
                scanf("%d", &page);
                while(page!=0){
                    manualdata.nmbpage++;
                    manualdata.p = realloc(manualdata.p,sizeof(int)*manualdata.nmbpage);
                    manualdata.p[manualdata.nmbpage-1] = page;
                    scanf("%d", &page);
                }
                printf("taille : %d \n", manualdata.nmbpage);
                trier(manualdata.p,manualdata.nmbpage);
                ajouter_noeud(a,manualdata,&k);
            }
            manualdata.p = NULL;
            k *= -1;
            printf("\e[1;1H\e[2J"); // Alternative à system clear pour éviter le problème d'incompatiblité (OS)
            printf("Entrez un autre mot (entrez # pour arreter): ");
            scanf("%s", manualdata.mot);
        }
    }
}
void affichagelargeur(livre a){
  file F;
  liste p;
  F.tete = NULL;
  F.queue = NULL;
  if(a!=NULL){
    enfiler(&F,a);
  }
  while(!filevide(F)){
    defiler(&F,&a);
    printf("\n(%s,[",a->mot);
    p = a->page;
    while(p!=NULL){
        if(p->suivant==NULL){
            printf("%d])", p->numpage);
        }
        else{
            printf("%d,", p->numpage);
        }
        p = p->suivant;
    }
    if(a->succg != NULL){
      enfiler(&F,a->succg);
    }
    if(a->succd != NULL){
      enfiler(&F, a->succd);
    }
  }
}
void affiche_struct_arbre(livre a){
  file F;
  liste p;
  int k = 0;
  F.tete = NULL;
  F.queue = NULL;
  if(a!=NULL){
    enfiler(&F,a);
  }
  while(!filevide(F)){
    defiler(&F,&a);
    printf("\n\n(%s,[",a->mot);
    p=a->page;
    while(p!=NULL){
        if(p->suivant==NULL){
            printf("%d])", p->numpage);
        }
        else{
            printf("%d,", p->numpage);
        }
        p = p->suivant;
    }
    if(a->succg != NULL){
      printf("-->filsgauche(%s)",a->succg->mot);
      enfiler(&F,a->succg);
    }
    else{
        printf("-->filsgauche(NULL)");
    }
    if(a->succd != NULL){
        printf("-->filsdroite(%s)",a->succd->mot);
      enfiler(&F, a->succd);
    }
    else{
        printf("-->filsdroite(NULL)");
    }
  }
}
bool recherche_mot_inserer_supprimer_page(livre *a, char* val, int nv,int x,int pg){
    liste p;
    liste t,q;
    if(*a!=NULL){
        if(strcmp((*a)->mot, val)==0){
            if(x==0){
                printf("Le mot %s, les pages : ", (*a)->mot);
                p = (*a)->page;
                while(p!=NULL){
                    printf("%d ", p->numpage);
                    p = p->suivant;
                }
                printf("et le niveau : %d", nv);
            }
            else if(x==1){  //option pour inserer un numero de page
              p = (*a)->page;
              while(p->suivant!=NULL && p!= NULL &&  p->suivant->numpage < pg){
                p = p->suivant;
              }
              if(p!=NULL){
                if(p == (*a)->page){
                  t = malloc(sizeof(elt));
                  t->numpage = pg;
                  t->suivant = (*a)->page;
                  (*a)->page = t;
                }
                else if(p->suivant == NULL){
                    t = malloc(sizeof(elt));
                    t->numpage = pg;
                    t->suivant = NULL;
                    p->suivant = t;
                }
                else if(p->suivant->numpage>pg){
                  t = malloc(sizeof(elt));
                  t->numpage = pg;
                  t->suivant = p->suivant;
                  p->suivant = t;
                }
              }
            }
            else if(x==2){ //option pour supprimer un numero de page
              p = (*a)->page;
              if(p!=NULL){
                if (p->numpage == pg){
                  t = (*a)->page;
                  (*a)->page = t->suivant;
                  free(t);
                }
                else{
                  while(p!=NULL && p->numpage != pg){
                    q = p;
                    p = p->suivant;
                  }
                  if(p!=NULL){
                    q->suivant = p->suivant;
                    free(p);
                  }
                }
              }


            }
            return true;        
        }
        else{
            if((recherche_mot_inserer_supprimer_page(&((*a)->succg),val,nv+1,x,pg)== false)){
                return (recherche_mot_inserer_supprimer_page(&((*a)->succd),val,nv+1,x,pg));
            }
            else{
                return true;
            }
        }
    }
    else {
      return false;
    }
}
//  les fonctions de la deuxéme partie
        // Fonction pour ajouter un numéro de page à la liste
        void addPage(liste *l, int num) {
          elt *nouvelElt = (elt*) malloc(sizeof(elt));
          nouvelElt->numpage = num;
          nouvelElt->suivant = *l;
          *l = nouvelElt;
        }
        // Fonction pour créer un nouveau nœud dans l'arbre
        livre creerNoeud(char *mot, int numPage) {
          livre nouveauNoeud = (livre) malloc(sizeof(index));
          strcpy(nouveauNoeud->mot, mot);
          nouveauNoeud->page = NULL;
          addPage(&(nouveauNoeud->page), numPage);
          nouveauNoeud->succg = NULL;
          nouveauNoeud->succd = NULL;
          return nouveauNoeud;
        }
        // Fonction pour ajouter un mot et son numéro de page à l'arbre
        livre ajouterMot(livre arbre, char *mot, int numPage) {
          if (arbre == NULL) {
            return creerNoeud(mot, numPage);
          }
          if (strcmp(mot, arbre->mot) < 0) {
            arbre->succg = ajouterMot(arbre->succg, mot, numPage);
          } else if (strcmp(mot, arbre->mot) > 0) {
            arbre->succd = ajouterMot(arbre->succd, mot, numPage);
          } else {
            // Le mot existe déjà dans l'arbre, ajoutez simplement le numéro de page à la liste
            addPage(&(arbre->page), numPage);
          }
          return arbre;
        }
        // Fonction pour remplire les mots d'arbre dans un tableau de chaine de caractères 
        void storeValues(livre root, information*values, int *index) {
          if (root == NULL) {
            return;
          }
          storeValues(root->succg, values, index);
          strcpy((values+(*index))->mot, root->mot);
          values[*index].page=root->page;
          (*index)++;
          storeValues(root->succd, values, index);
        }
        // Fonction de tri par insertion
        void tri_tableau(information *values, int size) {
          for (int i = 1; i < size; i++) {
            information key;
            strcpy(key.mot, values[i].mot);
            key.page=values[i].page;
            int j = i - 1;
            while (j >= 0 && strcmp(values[j].mot, key.mot) > 0) {
              strcpy(values[j + 1].mot, values[j].mot);
              values[j + 1].page=values[j].page;
              j--;
            }
            strcpy(values[j + 1].mot, key.mot);
            values[j + 1].page=key.page;
          }
      
        }
        // Fonction pour construire l'arbre binaire ordonné équilibré à partir d'un tableau
        livre Cree_arbre_equlibre(information *values, int start, int end) {

          if (start > end) {
            return NULL;
          }
          int mid = (start + end) / 2;
          livre root = (livre) malloc(sizeof(index));
          strcpy(root->mot, values[mid].mot);
          root->page=values[mid].page;
          root->succg = Cree_arbre_equlibre(values, start, mid - 1);
          root->succd = Cree_arbre_equlibre(values, mid + 1, end);
         
          return root;
        }
        // Fonction pour construire un arbre binaire ordonné équilibré à partir d'un arbre binaire non ordonné
        livre Creer_Arbre_Ordonee(livre a) {
        information * val =(information*)malloc(10*sizeof(information));
        int indice=0;
        storeValues(a,val,&indice);
        tri_tableau(val,indice);
        return Cree_arbre_equlibre(val,0,indice-1);
        }
        // Fonction de parcours infixe de l'arbre binaire
        void parcoursInfixe(index *root) {
          liste current;
          if (root == NULL) {
            return;
          }
          parcoursInfixe(root->succg); // Affiche d'abord les mots plus petits
          printf("\n(%s,[",root->mot); // Affiche le mot courant
         
          current = root->page;
          while (current != NULL) {
           if(current->suivant==NULL)
            printf("%d])",current->numpage); // Affiche chaque page associee au mot
            else
            printf("%d,", current->numpage); 
            current = current->suivant;
          }
          printf("\n");
          parcoursInfixe(root->succd); // Affiche ensuite les mots plus grands
        }
 
        void supprimerNoeud(livre *arbre, char *mot) {
  if (*arbre == NULL) {
    return;
  }
  if (strcmp(mot, (*arbre)->mot) < 0) {
    supprimerNoeud(&((*arbre)->succg), mot);
  } else if (strcmp(mot, (*arbre)->mot) > 0) {
    supprimerNoeud(&((*arbre)->succd), mot);
  } else {
    // Nous avons trouvé le noeud à supprimer
    livre noeudASupprimer = *arbre;
    if ((*arbre)->succg == NULL) {
      // Le noeud n'a pas de fils gauche, remplacer par le fils droit (s'il existe)
      *arbre = (*arbre)->succd;
    } else if ((*arbre)->succd == NULL) {
      // Le noeud n'a pas de fils droit, remplacer par le fils gauche
      *arbre = (*arbre)->succg;
    } else {
      // Le noeud a deux fils, trouver le plus petit noeud dans le sous-arbre droit et le remplacer
      livre noeudMin = (*arbre)->succd;
      while (noeudMin->succg != NULL) {
        noeudMin = noeudMin->succg;
      }
      strcpy((*arbre)->mot, noeudMin->mot);
      (*arbre)->page = noeudMin->page;
      supprimerNoeud(&((*arbre)->succd), noeudMin->mot);
    }
    free(noeudASupprimer);
  }
}
        // Cette fonction permet de supprimer un mot de l'arbre avec tous les numéros de pages associées au mot.
        void supprimerMot(livre *arbre, char *mot) {
        if (*arbre == NULL) {
          return;
        }
        if (strcmp(mot, (*arbre)->mot) < 0) {
          supprimerMot(&((*arbre)->succg), mot);
        } else if (strcmp(mot, (*arbre)->mot) > 0) {
          supprimerMot(&((*arbre)->succd), mot);
        } else {
          // Nous avons trouvé le noeud à supprimer
          livre noeudASupprimer = *arbre;
          if ((*arbre)->succg == NULL) {
            // Le noeud n'a pas de fils gauche, remplacer par le fils droit (s'il existe)
            *arbre = (*arbre)->succd;
          } else if ((*arbre)->succd == NULL) {
            // Le noeud n'a pas de fils droit, remplacer par le fils gauche
            *arbre = (*arbre)->succg;
          } else {
            // Le noeud a deux fils, trouver le plus petit noeud dans le sous-arbre droit et le remplacer
            livre noeudMin = (*arbre)->succd;
            while (noeudMin->succg != NULL) {
              noeudMin = noeudMin->succg;
            }
            strcpy((*arbre)->mot, noeudMin->mot);
            (*arbre)->page = noeudMin->page;
            supprimerNoeud(&((*arbre)->succd), noeudMin->mot);
          }
          // Supprimer la liste de numéros de page associés au mot
          elt *pageASupprimer = noeudASupprimer->page;
          while (pageASupprimer != NULL) {
            elt *temp = pageASupprimer;
            pageASupprimer = pageASupprimer->suivant;
            free(temp);
          }
          free(noeudASupprimer);
        }
      }
// les fonctions de la 3 partie 
//primitives de la pile adapté aux nouveaux structures de données
bool pilevide(pile p){
    if(p==NULL){
        return true;
    }
    else{
        return false;
    }
}
void empiler(pile *p, livre a){
    pile t;
    if(pilevide(*p)){
        *p = malloc(sizeof(eltpile));
        (*p)->suivant = NULL;
        (*p)->info = a;
    }
    else{
        t = malloc(sizeof(eltpile));
        t->info = a;
        t->suivant = *p;
        *p = t;
    }
}
void depiler(pile *p, livre *a){
    pile t;
    t = (*p);
    *p = (*p)->suivant;
    *a = t->info;
    free(t);
}
//pour créer une nouvelle file dans la fonction de chemins
void copierfile(filechemin *destination, filechemin source){
  eltfilechemin *tempo = source.tete;
  while(tempo!=NULL){
    enfilermot(destination,tempo->mot);
    tempo = tempo->suivant;
  }
}
//fonction pour afficher le chemin (le contenu de la file)
void afficherfile(filechemin F){
    char word[30];
    while(F.tete!=NULL){//afficher le mot)
        printf("%s ", F.tete->mot);
        F.tete = F.tete->suivant;
    }
}
//procédure qui construit une liste qui contient une file de chemin en utilisant les piles (file de mots représentant un chemin)
void branches(livre a,listechemin *l){
  *l = NULL;
  pile P=NULL;
  filechemin temp; temp.queue = NULL;temp.tete=NULL;
  livre b=NULL;       //déclaration des variables & initialisation pour éviter des problèmes de mémoire.
  listechemin p=NULL;
  filechemin F;F.tete =NULL;F.queue=NULL;
  if(a!=NULL){
    empiler(&P,a);
    enfilermot(&F,a->mot);
    while(!pilevide(P)){
      while(a->succd !=NULL || a->succg !=NULL){  //dépiler jusqu'à arriver à un noeud feuille
        if(a->succg!=NULL){   //toujours y aller à la gauche si c'est possible
          empiler(&P,a->succg);
          a = a->succg;
          enfilermot(&F,a->mot);
        }
        else{
          empiler(&P,a->succd);
          a = a->succd;
          enfilermot(&F,a->mot);
        }
      }
      if(*l==NULL){  //cas ou la liste est vide
        *l = malloc(sizeof(eltlistechemin));
        temp.tete = NULL;temp.queue = NULL; //création d'une nouvelle file
        copierfile(&temp,F);      //pour que les données ne changent pas parceque F va constamment changer.
        (*l)->info = temp;
        (*l)->suivant = NULL;
        p = *l;
      }
      else{
        listechemin templiste = malloc(sizeof(eltlistechemin));   //cas ou la liste est déjà créee
        temp.tete = NULL;temp.queue = NULL;
        copierfile(&temp,F);
        templiste->info = temp;
        templiste->suivant = NULL;
        p->suivant = templiste;
        p = p->suivant;
        
      }
      depiler(&P,&b);defilermot(&F);      //on dépile P sur b 
      while(!pilevide(P)){
        depiler(&P,&a);
        if(a->succd ==NULL || a->succd == b){   //on vérifie si on a déjà parcouru le chemin à droite à l'aide de b
          defilermot(&F);b=a;
        }
        else if(a->succd!=b){//au cas ou on trouve un fils droit, on sort de la boucle.
          empiler(&P,a);empiler(&P,a->succd);
          enfilermot(&F,a->succd->mot);
          a = a->succd;           
          break; //on aurait pu utiliser un boolen en langage algorithmique
        }
      } 
    }
  }
}
void defilermot(filechemin *F){
  eltfilechemin *p = F->tete;
  eltfilechemin *temp;
  if(p->suivant!=NULL){
    while(p->suivant!=F->queue){
      p = p->suivant;
    }
    p->suivant = NULL;
    temp = F->queue;
    F->queue = p;
    free(temp);
  }
}
void enfilermot(filechemin *F, char *word){
  eltfilechemin *t;
  if (F->tete==NULL){
    F->tete = malloc(sizeof(eltfilechemin));
    strcpy(F->tete->mot,word);
    F->tete->suivant = NULL;
    F->queue = F->tete;
  }
  else{
    t = malloc(sizeof(eltfilechemin));
    strcpy(t->mot,word);
    t->suivant = NULL;
    F->queue->suivant= t;
    F->queue = t;
  }
}
void afficher_chemins(listechemin l){ 
    filechemin temp;
    while(l!=NULL){
      temp = l->info;
      afficherfile(temp);
      l = l->suivant;
      printf("\n");
    }
}

void menu() {
    printf(" _______________________________________________________________________________________________\n");
    printf("|                                       PARTIE I                                                |\n");
    printf("|                                                                                               |\n");
    printf("|    1 :"Jaune" Construire l'arbre avec des donnees fixe par le programmeur (exemple)\033[0m                  |\n");
    printf("|    2 :"Jaune" Construire l'arbre manuellement\033[0m                                                        |\n");
    printf("|    3 :"Jaune" Afficher en largeur du contenu de l'arbre\033[0m                                              |\n");
    printf("|    4 :"Jaune" Afficher la structure de l'arbre\033[0m                                                       |\n");
    printf("|    5 :"Jaune" Recherche d'un mot dans l'arbre\033[0m                                                        |\n");
    printf("|    6 :"Jaune" Ajout d'un numero de page pour un mot donnee dans l'arbre\033[0m                              |\n");
    printf("|    7 :"Jaune" Suppression d'un numero de page pour un mot donnee dans l'arbre\033[0m                        |\n");
    printf("|    0 :"Vert" Quitter\033[0m                                                                                |\n");
    printf("|                                                                                               |\n");
    printf("|_______________________________________________________________________________________________|\n\nVotre choix : ");
}
void menu2() {
    printf(" _______________________________________________________________________________________________\n");
    printf("|                                 Veuillez choisir la patie :                                   |\n");
    printf("|                                                                                               |\n");
    printf("|    1 : "Jaune"Partie I\033[0m                                                                               |\n");
    printf("|    2 : "Jaune"Partie II\033[0m                                                                              |\n");
    printf("|    3 : "Jaune"Partie III\033[0m                                                                             |\n");
    printf("|    0 : "Vert"Quitter\033[0m                                                                                |\n");
    printf("|                                                                                               |\n");
    printf("|_______________________________________________________________________________________________|\n\nVotre choix : ");
}
void menu3() {
    printf(" ____________________________________________________________________________________________________________\n");
    printf("|                                               PARTIE II                                                    |\n");
    printf("|                                                                                                            |\n");
    printf("|   1 : "Jaune"A partir de un arbre non ordonne deja construit, construire un arbre binaire ordonne et equilibre\033[0m    |\n");
    printf("|   2 : "Jaune"Afficher le contenu de l index en respectant l ordre croissant des mots et des pages pour chaque mot\033[0m |\n");
    printf("|   3 : "Jaune"Rechercher un mot donne dans l arbre et retourner son niveau (si il existe)\033[0m                          |\n");
    printf("|   4 : "Jaune"Ajouter un mot donne dans l arbre avec un numero de page. l arbre reste ordonne\033[0m                      |\n");
    printf("|   5 : "Jaune"Supprimer un mot de l index avec tous les numeros de pages associees au mot.\033[0m                         |\n");
    printf("|   0 : "Vert"Quitter\033[0m                                                                                              |\n");
    printf("|                                                                                                            |\n");
    printf("|____________________________________________________________________________________________________________|\n\nVotre choix : ");
}
void menupartie3() {
    printf(" _______________________________________________________________________________________________\n");
    printf("|                                       PARTIE III                                              |\n");
    printf("|                                                                                               |\n");
    printf("|    1 : "Jaune"Construire les differentes listes comportant les chemins de l arbre\033[0m                    |\n");
    printf("|    2 : "Jaune"Afficher tous les chemins en commencant par le plus a gauche.\033[0m                          |\n");
    printf("|    0 : "Vert"Quitter\033[0m                                                                                |\n");
    printf("|                                                                                               |\n");
    printf("|_______________________________________________________________________________________________|\n\nVotre choix : ");
}

void sortir(){
    char input;
    printf(Jaune"\nTapez n'importe quoi pour revenir."fin);
    scanf(" %c",&input);
}
