#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#define NBR_NOTES 14
#define RESET "\033[0m"
#define RED "\033[31m"       // Red text
#define GREEN "\033[32m" 
#define CYAN "\033[36m"
#define BOLD "\033[1m" 
#define YELLOW "\033[33m"
typedef struct {
    char libelle[100];
    float valeur;
} Notes;
typedef struct {
    int jour, mois, annee;
} DateNaisRepere;
typedef struct etudiant {
    char nom[50];
    char prenom[50];
    int age;
    DateNaisRepere date;
    int Id;
    Notes note[NBR_NOTES];
    struct etudiant* suivant; 
    float Moy;
} EtudiantRepere;
typedef struct ListeRepere{
    EtudiantRepere *tete;
    EtudiantRepere *queue;
    int nef;
}Liste;
Liste * Creer_Liste_Etudiants();
float calculer_Moyenne(const EtudiantRepere *P);
int calculerAge(const EtudiantRepere* P);
void Libelle_notes(EtudiantRepere *P);
void bultane_etu(EtudiantRepere*p);
EtudiantRepere * Creer_Etudiant();
void afficherEtudiant(EtudiantRepere* E);
void ajouter_Etudiant_liste(Liste* li);
void afficher_liste_Etudiant (Liste* li);
void creer_fichier_txt ();
void enregistrer_liste_etudiant(Liste* li);
int* Recherche_et_Affichage_des_Informations_nom(Liste* li,int *nbt);
int check_ID(int a);
int Recherche_et_Affichage_des_Informations_identifiant(Liste* li);
void afficher_menu_modifier(EtudiantRepere*p);
void modifier_infor(Liste* li,int positions);
int* Recherche_et_Affichage_des_Informations_age(Liste* li,int* nbt);
Liste* lire_fichier_txt ();
void afficher_menu();
void afficher_menu_recherche();
int Recherche_tous (Liste* liste);
float* calculer_Moyenne_Module_Rapport(Liste* li);
float calculer_Moyenne_Generale_Rapport(Liste* li);
int Validation(Liste* li);
void Generer_Rapport_Academique(Liste* li);
void Supprimer_Etudiant(Liste* li, int pos);
Liste* check_and_load_file();
int demanderEntier(const char* message);
int valide_datenaissance(EtudiantRepere* P);
void rapport_etu();
Liste * Creer_Liste_Etudiants(){
    Liste *Li;
    Li = (Liste*)malloc(sizeof(Liste));
    if (Li == NULL) {
        perror(RED "Erreur d'allocation mémoire" RESET);
        exit(EXIT_FAILURE);
    }
    Li -> tete = NULL;
    Li -> queue = NULL;
    Li -> nef = 0;
return(Li);
}
float calculer_Moyenne(const EtudiantRepere *P) { 
    float MOY=0;
    for (int i=0;i<NBR_NOTES;i++) {
        MOY+=P->note[i].valeur;
    }
    return (MOY) / NBR_NOTES; 
}
int calculerAge(const EtudiantRepere* P) {
    // Récupérer la date actuelle
    time_t t = time(NULL);
    struct tm dateActuelle = *localtime(&t);
    // Extraire l'année, le mois et le jour actuels
    int anneeActuelle = dateActuelle.tm_year + 1900; // tm_year donne l'année depuis 1900
    int moisActuel = dateActuelle.tm_mon + 1;        // tm_mon va de 0 à 11
    int jourActuel = dateActuelle.tm_mday;
    // Calcul de l'âge
    int age = anneeActuelle - P->date.annee;
    // Ajuster si la date d'anniversaire n'est pas encore passée
    if (P->date.mois > moisActuel || (P->date.mois == moisActuel && P->date.jour > jourActuel)) {
        age--;
    }
    return age;
}
void Libelle_notes(EtudiantRepere *P) {
    for (int i = 0; i < NBR_NOTES; i++) { 
        if (i == 0) {
            strcpy(P->note[i].libelle, "Theorie des Graphes et Recherche Operationnelle");
        } else if (i == 1) {
            strcpy(P->note[i].libelle, "Architecture des Ordinateurs & Assembleur      ");
        } else if (i == 2) {
            strcpy(P->note[i].libelle, "Base des Donnees Relationnelles                ");
        } else if (i == 3) {
            strcpy(P->note[i].libelle, "Reseaux Informatiques                          ");
        } else if (i == 4) {
            strcpy(P->note[i].libelle, "Structure de Donnees en C                      ");
        } else if (i == 5) {
            strcpy(P->note[i].libelle, "Langues etrangeres 1                           ");
        } else if (i == 6) {
            strcpy(P->note[i].libelle, "Digital Skills                                 ");
        } else if (i == 7) {
            strcpy(P->note[i].libelle, "Systemes d'Exploitation et Linux               ");
        } else if (i == 8) {
            strcpy(P->note[i].libelle, "Modelisation Oriente Objet                     ");
        } else if (i == 9) {
            strcpy(P->note[i].libelle, "Theories des Langages et Compilation           ");
        } else if (i == 10) {
            strcpy(P->note[i].libelle, "Developpement Web                              ");
        } else if (i == 11) {
            strcpy(P->note[i].libelle, "Programmation Oriente Objet Java               ");
        } else if (i == 12) {
            strcpy(P->note[i].libelle, "Langues etrangeres 2                           ");
        } else if (i == 13) {
            strcpy(P->note[i].libelle, "Culture & Arts & Sport Skills                  ");
        }
    }
}
void bultane_etu(EtudiantRepere*p){
    char nom_fichier[100];
    sprintf(nom_fichier, "%s.%d_rapport.txt", p->nom,p->Id);
    FILE*file=fopen(nom_fichier,"w");
    if (file == NULL) {
        printf(RED "Erreur d'ouverture du fichier.\n" RESET );
        return;
    }
    fprintf(file,"identifiant: %d \n",p->Id);
    fprintf(file,"nom:         %s \n",p->nom);
    fprintf(file,"prenom:      %s \n",p->prenom);
    fprintf(file,"age:         %d \n",p->age);
    for(int i=0;i<NBR_NOTES;i++){
        fprintf(file,"%s: %.2f/20 \n",p->note[i].libelle,p->note[i].valeur);
    }
    fprintf(file,"moyenne generale                               : %.2f/20 \n",p->Moy);
    if (p->Moy>=12){
        fprintf(file,"Année validée.\n");
    }else if (p->Moy<12){
        fprintf(file,"Année non validée\n");
    }
    fclose(file);
}
EtudiantRepere * Creer_Etudiant(){
    EtudiantRepere *P=(EtudiantRepere*)malloc(sizeof(EtudiantRepere));
    int V=1;
    do{
        P->Id=demanderEntier("\nEntrez l'identifiant de l'etudiant :");
        V=check_ID(P->Id);
    }while (V==1);
    printf("Entrez le nom de l'etudiant :");
    scanf(" %[^\n]", P->nom);
    printf("Entrez le prenom de l'etudiant :");
    scanf(" %[^\n]", P->prenom);
    int B;
    do
    {
        printf("Entrez la date de naissance (jour mois annee) :");
        scanf("%d %d %d", &P->date.jour, &P->date.mois, &P->date.annee);
        B=valide_datenaissance(P);
    } while (B==-1);
    P->age=calculerAge(P);
    Libelle_notes(P);
    for (int i = 0; i < NBR_NOTES; i++) { 
        do{
            printf("Entrez la note pour %s : ", P->note[i].libelle); 
            scanf("%f", &P->note[i].valeur); 
            if ((P->note[i].valeur>20) || (P->note[i].valeur<0)){
                printf("Veuillez Saisir une note entre 0 et 20.\n");
            }
        }while ((P->note[i].valeur>20) || (P->note[i].valeur<0));
    }
    P->Moy=calculer_Moyenne(P);
    P->suivant=NULL;
    FILE* fichier = fopen("pEtudiants.txt", "a");
    if (fichier==NULL)
    {
        printf(RED "Erreur d'ouverture" RESET);
        return NULL;
    }
    fprintf(fichier,"%d\t| %s\t| %s\t| %i\t| %02d/%02d/%02d\t|", P->Id, P->nom, P->prenom, P->age, P->date.jour, P->date.mois,P->date.annee);
    for (int i = 0; i < NBR_NOTES; i++) {
        fprintf(fichier, "%.2f/20\t| ", P->note[i].valeur);
    }
    fprintf(fichier,"%.2f/20\n",P->Moy);
    fclose(fichier);
    bultane_etu(P);
    return P;
}
void afficherEtudiant(EtudiantRepere* E) {
    printf("Identifiant: %d\nNom: %s\nPrenom: %s\nAge: %d ans, ne le %d/%d/%d\n", E->Id, E->nom, E->prenom, E->age, E->date.jour, E->date.mois, E->date.annee);
    for (int i = 0; i < NBR_NOTES; i++) {
        printf("Note en %s : %.2f/20\n", E->note[i].libelle, E->note[i].valeur);
    }
    printf("Moyenne generale : %.2f/20\n----------------------------\n", E->Moy);
}
void ajouter_Etudiant_liste(Liste* li){
    EtudiantRepere* P = Creer_Etudiant();
    if (li->tete == NULL) {// si la liste est vide
        li->tete=P;
        li->queue=P;
    }else{
        li->queue->suivant=P; //2ème case du dernier element doit pointer sur ce nouveau element
        li->queue=P; //le dérnier element de la liste doit etre ce P
    }
    li->nef++;
}
void afficher_liste_Etudiant (Liste* li){
    EtudiantRepere* P;
    P = li->tete;
    printf("\nLa liste des etudiants avec leurs details\n:");
    while (P!=NULL){
        printf("Identifiant: %d\nNom: %s\nPrenom: %s\nAge: %d ans , ne le %02d/%02d/%04d \n",P->Id, P->nom, P->prenom, P->age, P->date.jour, P->date.mois,P->date.annee);
        P->Moy=calculer_Moyenne(P);
        printf("Moyenne generale : %.2f/20\n--------------------------------------------------\n", P->Moy);  
        P=P->suivant;
    }
}
void creer_fichier_txt (){ //Fonction pour créer un fichier txt où on peut
    FILE *fichier=fopen("pEtudiants.txt","w");
    if (fichier == NULL){
        perror ("Erreur d'ouverture du fichier");
        return ;
    }
    const char *modules[] = {"TG&RO","AO&A","BDR","RI","SDC","LE1","DS","SE&L","MOO","TLC","DW","POO","LE2","CASS"};
    fprintf(fichier, "Identifiant\t| Nom\t| Prenom\t| Age\t| Date de Naissance\t|");
    for (int i = 0; i < NBR_NOTES; i++) {
        fprintf(fichier, "%s\t| ", modules[i]);
    }
    fprintf(fichier,"Moyenne Generale");
    fprintf(fichier, "\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fichier);
}
void enregistrer_liste_etudiant(Liste* li) { // fonction pour enregistrer les etudiants ans un fichier txt
    FILE* fichier = fopen("pEtudiants.txt", "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    EtudiantRepere* P = li->tete;
    while (P != NULL) {
        fprintf(fichier, "%d\t| %s\t| %s\t| %i\t| %02d/%02d/%02d\t|", P->Id, P->nom, P->prenom, P->age, P->date.jour, P->date.mois,P->date.annee);
        for (int i = 0; i < NBR_NOTES; i++) {
            fprintf(fichier, "%.2f/20\t| ", P->note[i].valeur);
        }
        fprintf(fichier,"%.2f/20\n",P->Moy);
        P = P->suivant;
    }
    fclose(fichier);
}
int* Recherche_et_Affichage_des_Informations_nom(Liste* li,int *nbt) {
    EtudiantRepere *courant=li->tete;
    char nom[50];
    printf("veuiller saisir le nom de l'etudiant:  ");
    fflush(stdin);
    scanf("%[^\n]", nom);
    int found=0;
    int i=1;
    (*nbt)=0;
    int* pos=NULL;
    while(courant!=NULL){
        if(strcmp(courant->nom,nom)==0){
            printf("les informations de l etu avec le nom %s sont \n",nom);
            afficherEtudiant(courant);
            found=1;
            pos=realloc(pos,((*nbt)+1)*sizeof(int));
            if (pos == NULL) {
                perror("Erreur de realloc");
                free(pos); // Libérer la mémoire précédemment allouée
                return NULL;
            }
            pos[*nbt]=i;
            (*nbt)++;
            }
            i++;
        courant=courant->suivant;}
        if (!found){
            printf("l'etu n existe pas dans la base");
            return NULL;
        }
return pos;
}
int check_ID(int ID) {
    Liste* li=check_and_load_file();
    EtudiantRepere *courant=li->tete;
    int found=0;
    while(courant!=NULL){
        if(courant-> Id==ID){
            printf("L'ID que vous avez saisit existe deja dans la base de donnees, veuillez tapez un ID unique \n");
            found=1;
            break;
            }
        courant=courant->suivant;  
    }
    if(!found){
        printf("L'ID est valide.\n");
        return -1;
    }
    return 1;
}
int Recherche_et_Affichage_des_Informations_identifiant(Liste* li) {
    int ID;
    EtudiantRepere *courant=li->tete;
    printf("saisire l'identifiant de l'etudiant que vous vouler chercher: ");
    scanf("%d",&ID);
    int found=0;
    int i=1;
    int pos=0;
    while(courant!=NULL){
        if(courant-> Id==ID){
            printf("les informations de l etu avec identifiant %d sont \n",ID);
            afficherEtudiant(courant);
            found=1;
            pos=i;
            }
            i++;
            courant=courant->suivant;  
        }
        if(!found){
            printf("l etu n existe pas dans la base");
            return 0;
            }
    return pos;
}
void afficher_menu_modifier(EtudiantRepere*p) {
    printf(CYAN BOLD"\n<===================Menu Modification===================>\n");
    printf("                1. Changer l'identifiant\n");
    printf("                2. Changer le nom\n");
    printf("                3. Changer le prénom\n");
    printf("                4. Changer Date de naissance\n");

    // Affichage pour les 14 notes
    for (int i = 0; i < NBR_NOTES; i++) {
        printf("%d. Modifier la note %s\n", 5+i, p->note[i].libelle);
    }
    printf("19. Retour au menu principal\n");
    printf("\n<===================Menu Modification===================>\n"RESET);
}
void modifier_infor(Liste *li, int positions){
    int l;
    if (positions ==0 ) {
        printf("Étudiant non trouvé.\n");
        return;
    }
    EtudiantRepere* courant = li->tete;
    for (int i = 1; i < positions; i++) { 
        courant = courant->suivant;
    }
    int B;
    do{
        afficher_menu_modifier(courant);
        l=demanderEntier("Choisissez une option: ");
        printf("Modification des informations de l'étudiant:\n");
        switch (l){
        case 1:
        printf("Modification par ID: \n");
        char nomfich_1[100];
        char nvnom_1[100];
        sprintf(nomfich_1,"%s.%d_rapport.txt",courant->nom,courant->Id);
        int V=1;
        do{
            courant->Id=demanderEntier("\nEntrez l'identifiant de l'etudiant :");
            V=check_ID(courant->Id);
        }while (V==1);
        sprintf(nvnom_1,"%s.%d_rapport.txt", courant->nom,courant->Id);
        if (rename(nomfich_1, nvnom_1) == 0) {
            printf(GREEN"Le fichier '%s' a ete renomme en '%s' avec succes.\n" RESET, nomfich_1, nvnom_1);
        } else {
            perror(RED"Erreur lors du renommage du fichier"RESET);
        }
        break;
        case 2:
        printf("Entrez le nouveau nom: ");
        char nomfich[100];
        char nvnom[100];
        sprintf(nomfich,"%s.%d_rapport.txt",courant->nom,courant->Id);
        scanf(" %[^\n]", courant->nom);
        sprintf(nvnom,"%s.%d_rapport.txt", courant->nom,courant->Id);
        if (rename(nomfich, nvnom) == 0) {
            printf(GREEN"Le fichier '%s' a ete renomme en '%s' avec succes.\n"RESET, nomfich, nvnom);
        } else {
            perror(RED"Erreur lors du renommage du fichier"RESET);
        }
        break;
        case 3:
        printf("Entrez le nouveau prenom: ");
        scanf(" %[^\n]", courant->prenom);
        break;
        case 4:
        do{
            printf("Entrez la date de naissance (jour mois annee) :");
            scanf("%d %d %d", &courant->date.jour, &courant->date.mois, &courant->date.annee);
            B=valide_datenaissance(courant);
        }while (B==-1);
        break;
        case 19:
        printf("Retour au menu principal.\n");
        return;
        default:
        if (l >= 5 && l < 5 + NBR_NOTES) {
            int index = l - 5;
            printf("Entrez la nouvelle valeur pour la note %d (%s) : ", index + 1, courant->note[index].libelle);
            scanf("%f", &courant->note[index].valeur);
            } else {
                printf(RED"Option invalide.\n"RESET);
            }
            break;}
        printf(GREEN"Modification effectuee.\n"RESET);
        courant->age = calculerAge(courant);
        courant->Moy = calculer_Moyenne(courant);
        creer_fichier_txt ();
        enregistrer_liste_etudiant(li);
        bultane_etu(courant);
        return;
    }while (l!=19);
}
int* Recherche_et_Affichage_des_Informations_age(Liste* li,int* nbt) {
    EtudiantRepere *courant=li->tete;
    printf("saisir l age de l'etudiant que vous souhaitez trouver: ");
    int age;
    scanf("%d",&age);
    int found=0;
    int i=1;
    (*nbt)=0;
    int* pos=NULL;
    while(courant!=NULL){
        if(courant->age==age){
            printf(GREEN"les informations de l'etudiant(s) qui a l age %d sont \n"RESET,age);
            afficherEtudiant(courant);
            found=1;
            pos=realloc(pos,((*nbt)+1)*sizeof(int));
            if (pos == NULL) {
                perror(RED"Erreur de realloc"RESET);
                free(pos); // Libérer la mémoire précédemment allouée
                return NULL;
            }
            pos[*nbt]=i;
            (*nbt)++;
        }
        i++;
        courant=courant->suivant;
    }
    if(!found){
        printf(RED"\nl'etudiant n'existe pas.\n"RESET);
        return NULL;
    }
return pos;
}
Liste* lire_fichier_txt () {
    FILE *F=fopen("pEtudiants.txt","r");
    if ((F)==NULL) {
        perror (RED"Erreur d'ouverture du fichier"RESET);
        return NULL;
    }
    Liste* li=Creer_Liste_Etudiants();
    char buffer[512];
    rewind(F);
    fgets(buffer, sizeof(buffer), F); // Première ligne
    fgets(buffer, sizeof(buffer), F); // Ligne de séparation
    while (fgets(buffer, sizeof(buffer), F) != NULL){
        EtudiantRepere *P=(EtudiantRepere*)malloc(sizeof(EtudiantRepere));
        if (P == NULL) {
            perror("Erreur d'allocation mémoire pour un étudiant");
            fclose(F);
            return li; // On retourne la liste partiellement construite
        }
        int notesStartIndex = 0;
        sscanf(buffer,"%d\t| %[^\t|]\t| %[^\t|]\t| %i\t| %d/%d/%d\t|%n", &P->Id, P->nom, P->prenom, &P->age, &P->date.jour, &P->date.mois,&P->date.annee, &notesStartIndex);
        char* notesData = buffer + notesStartIndex;
        for (int i=0; i<NBR_NOTES;i++){
            sscanf(notesData, "%f/20\t| %n", &P->note[i].valeur, &notesStartIndex);
            notesData += notesStartIndex;
        }
        sscanf(notesData, "%f/20\n", &P->Moy);
        Libelle_notes(P);
        P->suivant=NULL;
        bultane_etu(P);
        if (li->tete == NULL) { // si la liste est vide
            li->tete=P;
            li->queue=P;
        }else{
            li->queue->suivant=P; //2ème case du dernier element doit pointer sur ce nouveau element
            li->queue=P; //le dérnier element de la liste doit etre ce P
        }
        li->nef++;
        }
    fclose(F);
    return li;
}
void afficher_menu() {
    printf(CYAN BOLD"\n<===================Menu Principale===================>\n");
    printf("                 1. Ajouter un etudiant\n");
    printf("                 2. Afficher la liste d'etudiants\n");
    printf("                 3. Supprimer un etudiant\n");
    printf("                 4. chercher un etudiant\n");
    printf("                 5. Modifier un etudiant\n");
    printf("                 6. Rapport d'un etudiant\n");
    printf("                 7. Generer un Rapport academique.\n");
    printf("                 8. Quitter le programme");
    printf("\n<===================Menu Principale===================>\n"RESET);
}
void afficher_menu_recherche(){
    printf(CYAN BOLD"\n<===================Menu Recherche===================>\n");
    printf("1. chercher par nom\n");
    printf("2. chercher par age\n");
    printf("3. chercher par identifiant\n");
    printf("4. Quitter le menu de recherche vers menu principale");
    printf("\n<===================Menu Recherche===================>\n"RESET);
}
int Recherche_tous (Liste* liste){
    int R;
    int nbt=0;
    int position=0;
    int* L=(int*)malloc(sizeof(int));
    do{
        afficher_menu_recherche();
        R=demanderEntier("Choisissez une option: ");
        nbt=0;
        position=0;
        switch (R){
            case 1:
            L=Recherche_et_Affichage_des_Informations_nom(liste,&nbt);
            if(L==NULL){
                return 0;
            }
            position=L[0];
            break;
            case 2:
            L=Recherche_et_Affichage_des_Informations_age(liste,&nbt);
            if(L==NULL){
                return 0;
            }
            position=L[0];
            break;
            case 3:
            position=Recherche_et_Affichage_des_Informations_identifiant(liste);
            if(position>=1){
                nbt=1;
            }
            break;
            case 4:
            printf("\nRetour.");
            break;
            default:
            printf(RED"Option invalide\n"RESET);
            break;
        }
    } while (R!=4 && nbt != 1);
    return position;
}
float* calculer_Moyenne_Module_Rapport(Liste* li){
    float *Moy=(float*)malloc(NBR_NOTES*(sizeof(float)));
    if (Moy == NULL) {
        perror("Erreur d'allocation memoire pour les moyennes.");
        return NULL;
    }
    for (int i=0;i<NBR_NOTES;i++){
        float S=0;
        EtudiantRepere* courant=li->tete;
        while (courant!=NULL){
            S+=courant->note[i].valeur;
            courant=courant->suivant;
        }
        Moy[i]=S/(li->nef);
    }
    return Moy;
} 
float calculer_Moyenne_Generale_Rapport(Liste* li){
    EtudiantRepere* courant=li->tete;
    float MoyGen=0;
    float S=0;
    while (courant!=NULL){
        S+=courant->Moy;
        courant=courant->suivant;
    }
    MoyGen=S/li->nef;
    return MoyGen;
}
int Validation(Liste* li){
    EtudiantRepere* courant=li->tete;
    int EV=0;
    while (courant != NULL){
        if (courant->Moy>=12)
        {
            EV++;
        }
        courant=courant->suivant;
    }
    return EV;
}
void Generer_Rapport_Academique(Liste* li){
    FILE* fichier=fopen("Rapport_Academique.txt","w");
    fprintf(fichier,"<=================== Rapport Académique ===================>\n");
    printf(RED BOLD"<=================== Rapport Academique ===================>\n"RESET);
    fprintf(fichier,"Les moyennes generaux de chaque Module:\n");
    printf(BOLD"Les moyennes generaux de chaque Module:\n"RESET);
    EtudiantRepere P;
    Libelle_notes(&P);
    float* MoyMod=calculer_Moyenne_Module_Rapport(li);
    for (int i=0;i<NBR_NOTES;i++){
        fprintf(fichier,"%s : %.2f/20\n",P.note[i].libelle,MoyMod[i]);
        printf("%s : %.2f/20\n", P.note[i].libelle, MoyMod[i]);
    }
    float B=calculer_Moyenne_Generale_Rapport(li);
    fprintf(fichier,"La moyenne generale de la filière GI1           : %.2f/20\n", B);
    printf(BOLD"La moyenne generale de la filiere GI1           : %.2f/20\n", B);
    fprintf(fichier,"Le nombre des étudiants dans la filière GI1           : %d\n", li->nef);
    printf("Le nombre des etudiants dans la filiere GI1           : %d\n", li->nef);
    int V=Validation(li);
    fprintf(fichier,"Le nombre des étudiants qui ont validée l'année       : %d/%d\n",V,li->nef);
    printf("Le nombre des etudiants qui ont validee l'annee       : %d/%d\n", V, li->nef);
    fprintf(fichier,"Le nombre des étudiants qui n'ont pas validée l'année : %d/%d\n",li->nef-V,li->nef);
    printf("Le nombre des etudiants qui n'ont pas validee l'annee : %d/%d\n",li->nef-V,li->nef);
    if(V==li->nef){
        fprintf(fichier,"Taux de validation: 100%%\n");
        printf("Taux de validation: 100%%\n");
    }else {
        float T = ((float)V/li->nef)*100;
        fprintf(fichier,"Taux de validation: %.2f%%\n",T);
        printf("Taux de validation: %.2f%%\n",T );
    }
    printf(RED BOLD"<================= Fin Rapport Academique =================>\n"RESET);
    fclose(fichier);
    free(MoyMod);
}
void Supprimer_Etudiant(Liste* li, int pos){
    if (li == NULL || li->tete == NULL){
        exit(EXIT_FAILURE);
    }
    EtudiantRepere* Courant=li->tete,*temp;
    char nom_fichier[100];
    if (pos == 1) {
        li->tete = Courant->suivant; // La tête de liste avance au nœud suivant
        printf(GREEN "L'étudiant de position %d est supprimé avec succès.\n"RESET, pos );
        sprintf(nom_fichier, "%s.%d_rapport.txt", Courant->nom,Courant->Id);
        if(remove(nom_fichier) == 0){
        printf(GREEN"Le fichier '%s' a ete supprime avec succes.\n" RESET, nom_fichier);
        } else {
        perror("Erreur lors de la suppression du fichier");
        }
        free(Courant); // Libération de la mémoire de l'ancien premier nœud
        return;
    }
    for(int i=1; Courant!=NULL && i<pos-1;i++){
        Courant=Courant->suivant;
    }
    if (Courant == NULL || Courant->suivant == NULL) {
        printf(RED"Aucun étudiant n'a été supprimé.\n"RESET);
        return;
    }
    temp=Courant->suivant;
    Courant->suivant=temp->suivant;
    sprintf(nom_fichier, "%s.%d_rapport.txt", temp->nom,temp->Id);
    if(remove(nom_fichier) == 0){
        printf(GREEN"Le fichier '%s' a ete supprime avec succes.\n" RESET, nom_fichier);
    } else {
        perror(RED"Erreur lors de la suppression du fichier"RESET);
    }
    free(temp);
    printf(GREEN"L'etudiant est supprime avec succes.\n"RESET);
    li->nef--;
}
Liste* check_and_load_file() {
    char filename[50];
    strcpy(filename,"pEtudiants.txt");
    FILE* file = fopen(filename, "r");
    if (!file) {
        creer_fichier_txt();
        Liste* liste=Creer_Liste_Etudiants();
        return liste;
    }
    int line_count = 0;
    char buffer[512]; // Temporary buffer to read lines
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_count++;
    }
    fclose(file);
    if (line_count <= 2) {
        Liste* liste=Creer_Liste_Etudiants();
        return liste;
    }
    Liste* liste=lire_fichier_txt();
    return liste; // Your existing function to load data from the file
}
int demanderEntier(const char* message) {
    int valeur;
    int c; 
    while (1) {
        printf("%s", message);
        if (scanf("%d", &valeur) != 1) {
            printf(RED"Entree invalide. Veuillez entrer un nombre entier\n"RESET);
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        c = getchar();
        if (c != '\n' && c != EOF) {
            printf(RED"Entree invalide. Veuillez entrer un nombre entier sans caracteres supplementaires.\n"RESET);
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        return valeur;
    }
}
int valide_datenaissance(EtudiantRepere* P) {
    // Tableau des jours par mois (par défaut, février a 28 jours)
    int jours_par_mois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Vérifie si l'année est bissextile
    if ((P->date.annee % 4 == 0 && P->date.annee % 100 != 0) || (P->date.annee % 400 == 0)) {
        jours_par_mois[1] = 29;  // Février a 29 jours dans une année bissextile
    }
    // Vérification du mois
    if (P->date.mois < 1 || P->date.mois > 12) {
        printf(RED"Mois invalide.\n"RESET);
        return -1;
    }
    // Vérification du jour
    if (P->date.jour < 1 || P->date.jour > jours_par_mois[P->date.mois - 1]) {
        printf(RED"Jour invalide pour le mois %d.\n"RESET, P->date.mois);
        return -1;
    }
    if(P->date.annee>2024 || P->date.annee<0){
        printf(RED"Annee invalide.\n"RESET);
        return -1;
    }
    // Si tout est valide
    printf(GREEN"Date valide.\n"RESET);
    return 1;
}
void rapport_etu() {
    int ID;
    char nom[50],nom_fichier[100];
    ID=demanderEntier("\nVeuillez saisir L'ID: ");
    printf("\nVeuillez saisir le nom: ");
    scanf("%[^\n]",nom);
    sprintf(nom_fichier,"%s.%d_rapport.txt",nom,ID);
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf(RED"Erreur lors de l'ouverture du fichier"RESET);
        return;
    }
    char ligne[256];
    printf(YELLOW"\n<===========================Rapport %s.%d===========================>\n"RESET,nom,ID) ;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        printf("%s", ligne);
    }
    printf(YELLOW"\n<===========================FIN Rapport %s.%d===========================>\n"RESET,nom,ID);
}
int main (){
    int C,k;
    Liste* liste=check_and_load_file();
    do{
        afficher_menu();
        C=demanderEntier("Choisissez une option: ");
        switch(C){
            case 1:
            ajouter_Etudiant_liste(liste);
            break;
            case 2:
            afficher_liste_Etudiant(liste);
            break;
            case 3:
            printf("veuiller chercher l'etudiant que vous souhaitez suprimer: ");
            int Z=0;
            Z=Recherche_tous(liste);
            if(Z>0){
                Supprimer_Etudiant(liste,Z);
            }
            creer_fichier_txt();
            enregistrer_liste_etudiant(liste);
            break;
            case 4:
            do{   
                afficher_menu_recherche();
                k=demanderEntier("Choisissez une option: ");
                switch(k){
                    int nbt=0;
                    case 1:
                    Recherche_et_Affichage_des_Informations_nom(liste,&nbt);
                    break;
                    case 2:
                    Recherche_et_Affichage_des_Informations_age(liste,&nbt);
                    break;
                    case 3:
                    Recherche_et_Affichage_des_Informations_identifiant(liste);
                    break;
                    default:
                    printf(RESET"Option invalide, veuillez reessayer.\n"RESET);
                    break;
                }
            }while (k!=4);
            break;
            case 5:
            printf("veuiller chercher l'etudiant que vous souhaitez modifier: ");
            int position=0;
            position=Recherche_tous(liste);
            if(position>0){
                modifier_infor(liste,position);
            }
            break;
            case 6:
            rapport_etu();
            break;
            case 7: 
            Generer_Rapport_Academique(liste);
            break;
            case 8:
            printf("Au revoir");
            break;
            default:
            printf(RED"Option invalide, veuillez reessayer.\n"RESET);
            break;
        }
    }while (C != 8);
    return 0;
} 