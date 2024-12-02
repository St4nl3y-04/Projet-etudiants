
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#define NBR_NOTES 14
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
Liste * Creer_Liste_Etudiants(){
    Liste *Li;
    Li = (Liste*)malloc(sizeof(Liste));
    if (Li == NULL) {
        perror("Erreur d'allocation mémoire");
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
            strcpy(P->note[i].libelle, "Architecture des Ordinateurs & Assembleur");
        } else if (i == 2) {
            strcpy(P->note[i].libelle, "Base des Donnees Relationnelles");
        } else if (i == 3) {
            strcpy(P->note[i].libelle, "Reseaux Informatiques");
        } else if (i == 4) {
            strcpy(P->note[i].libelle, "Structure de Donnees en C");
        } else if (i == 5) {
            strcpy(P->note[i].libelle, "Langues etrangeres 1");
        } else if (i == 6) {
            strcpy(P->note[i].libelle, "Digital Skills");
        } else if (i == 7) {
            strcpy(P->note[i].libelle, "Systemes d'Exploitation et Linux");
        } else if (i == 8) {
            strcpy(P->note[i].libelle, "Modelisation Oriente Objet");
        } else if (i == 9) {
            strcpy(P->note[i].libelle, "Theories des Langages et Compilation");
        } else if (i == 10) {
            strcpy(P->note[i].libelle, "Developpement Web");
        } else if (i == 11) {
            strcpy(P->note[i].libelle, "Programmation Oriente Objet Java");
        } else if (i == 12) {
            strcpy(P->note[i].libelle, "Langues etrangeres 2");
        } else if (i == 13) {
            strcpy(P->note[i].libelle, "Culture & Arts & Sport Skills");
        }
    }
}
EtudiantRepere * Creer_Etudiant(){
    EtudiantRepere *P=(EtudiantRepere*)malloc(sizeof(EtudiantRepere));
    printf("\nEntrez l'identifiant de l'etudiant :");
    scanf(" %d", &P->Id);
    printf("Entrez le nom de l'etudiant :");
    scanf(" %[^\n]", P->nom);
    printf("Entrez le prenom de l'etudiant :");
    scanf(" %[^\n]", P->prenom);
    printf("Entrez la date de naissance (jour mois annee) :");
    scanf("%d %d %d", &P->date.jour, &P->date.mois, &P->date.annee);
    P->age=calculerAge(P);
    for (int i = 0; i < NBR_NOTES; i++) { 
        Libelle_notes(P);
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
    fprintf(fichier, "%d\t| %s\t| %s\t| %i\t| %02d/%02d/%02d\t|", P->Id, P->nom, P->prenom, P->age, P->date.jour, P->date.mois,P->date.annee);
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
        printf("Moyenne generale : %.2f/20\n----------------------------\n", P->Moy);  
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
void bultane_etu(EtudiantRepere*p){
    char nom_fichier[100];
    sprintf(nom_fichier, "%s_rapport.txt", p->nom);
    FILE*file=fopen(nom_fichier,"w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    fprintf(file,"identifiant: %d \n",p->Id);
    fprintf(file,"nom: %s \n",p->nom);
    fprintf(file,"prenom: %s \n",p->prenom);
    fprintf(file,"age: %d \n",p->age);
    for(int i=0;i<NBR_NOTES;i++){
    fprintf(file,"note %s: %.2f \n",p->note[i].libelle,p->note[i].valeur);}
    fprintf(file,"moyenne generale: %.2f \n",p->Moy);
    fclose(file);
}
void afficher_menu_modifier(EtudiantRepere*p) {
    printf("\nMenu de modification des informations de l'étudiant :\n");
    printf("1. Changer l'identifiant\n");
    printf("2. Changer le nom\n");
    printf("3. Changer le prénom\n");
    printf("4. Changer l'âge\n");

    // Affichage pour les 14 notes
    for (int i = 0; i < NBR_NOTES; i++) {
        printf("%d. Modifier la note %s\n", 5+i, p->note[i].libelle);
    }
    printf("19. Retour au menu principal\n");
    printf("Veuillez choisir une option : ");
}
void Rech_Pos_Occ(int *pos, const int nbt){
    if(nbt != 0){
        printf("Nombre d'etudiants trouvée: %d", nbt);
        for(int i=0;i<nbt;i++){
            printf("\nLa postion de l'etudinat n '%d' trouvee est: %d",i+1,pos[i]);
        }
    }
}
void* modifier_infor(Liste* li,int positions) {
    int l;
    
    if (positions ==0 ) {
        printf("Étudiant non trouvé.\n");
        return NULL;
    }

    EtudiantRepere* courant = li->tete;
    for (int i = 1; i < positions; i++) { 
        courant = courant->suivant;
    }
    do{
        afficher_menu_modifier(courant);
        scanf("%d",&l);
        printf("Modification des informations de l'étudiant:\n");
        switch (l){
        case 1:
        printf("Entrez le nouveau identifiant: ");
        scanf("%d",&courant->Id);
        break;
        case 2:
        printf("Entrez le nouveau nom: ");
        char nomfich[100];
        char nvnom[100];
        sprintf(nomfich,"%s_rapport.txt",courant->nom);
        scanf(" %[^\n]", courant->nom);
        sprintf(nvnom,"%s_rapport.txt",courant->nom);
        if (rename(nomfich, nvnom) == 0) {
            printf("Le fichier '%s' a ete renomme en '%s' avec succes.\n", nomfich, nvnom);
        } else {
            perror("Erreur lors du renommage du fichier");
        }
        break;
        case 3:
        printf("Entrez le nouveau prénom: ");
        scanf(" %[^\n]", courant->prenom);
        break;
        case 4:
        printf("Entrez la nouvelle date de naissance (jour mois année): ");
        scanf("%d %d %d", &courant->date.jour, &courant->date.mois, &courant->date.annee);
        break;
        case 19:
                printf("Retour au menu principal.\n");
                return courant;
            default:
                if (l >= 5 && l < 5 + NBR_NOTES) {
                    int index = l - 5;
                    printf("Entrez la nouvelle valeur pour la note %d (%s) : ", index + 1, courant->note[index].libelle);
                    scanf("%f", &courant->note[index].valeur);
                } else {
                    printf("Option invalide.\n");
                }
                break;}
    printf("Modification effectuée.\n");
    courant->age = calculerAge(courant);
    courant->Moy = calculer_Moyenne(courant);
    printf("Les informations ont été modifiées avec succès.\n");
    creer_fichier_txt ();
    enregistrer_liste_etudiant(li);
    bultane_etu(courant);
    return courant;
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
            printf("les informations de l etu qui a l age %d sont \n",age);
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
        courant=courant->suivant;
    }
    if(!found){
        printf("l etu n existe pas dans la base");
        return NULL;
    }
return pos;
}
Liste* lire_fichier_txt () {
    FILE *F=fopen("pEtudiants.txt","r");
    if ((F)==NULL) {
        perror ("Erreur d'ouverture du fichier");
        return NULL;
    }
    Liste* li=Creer_Liste_Etudiants();
    char buffer[512];
    rewind(F);
    fgets(buffer, sizeof(buffer), F); // Première ligne (Nom, Prix, Quantité)
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
    printf("\nMenu Principale:\n");
    printf("1. Ajouter un etudiant\n");
    printf("2. Afficher la liste d'etudiants\n");
    printf("3. Supprimer un etudiant\n");
    printf("4. chercher un etudiant\n");
    printf("5. Modifier un etudiant\n");
    printf("6. Generer un Rapport academique.\n");
    printf("7. Quitter le programme\n");
    printf("Choisissez une option: ");
}
void afficher_menu_recherche(){
    printf("\nMenu  de recherche:\n");
    printf("1. chercher par nom\n");
    printf("2. chercher par age\n");
    printf("3. chercher par identifiant\n");
    printf("4. Quitter le menu de recherche vers menu principale\n");
    printf("5. Quitter le programme\n");
    printf("Choisissez une option: ");
}
int Recherche_tous (Liste* liste){
            int R;
            int nbt=0;
            int position=0;
            do
            {
                afficher_menu_recherche();
                scanf("%d",&R);
                nbt=0;
                position=0;
                switch (R)
                {
                    int* L=NULL;
                    case 1:
                    L=Recherche_et_Affichage_des_Informations_nom(liste,&nbt);
                    position=L[0];
                    break;
                    case 2:
                    L=Recherche_et_Affichage_des_Informations_age(liste,&nbt);
                    position=L[0];
                    break;
                    case 3:
                    position=Recherche_et_Affichage_des_Informations_identifiant(liste);
                    if(position>1){
                        nbt=1;
                    }
                    break;
                    case 5:
                    break;
                    default:
                    printf("Option invalide\n");
                    break;
                }
            } while (R!=4 && nbt != 1 );
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
void Generer_Rapport_Academique(Liste* li){
    FILE* fichier=fopen("Rapport_Academique.txt","w");
    fprintf(fichier,"Le rapport académique de la filière GI1: \n");
    EtudiantRepere P;
    Libelle_notes(&P);
    float* MoyMod=calculer_Moyenne_Module_Rapport(li);
    for (int i=0;i<NBR_NOTES;i++){
        fprintf(fichier,"%s :%.2f/20\n",P.note[i].libelle,MoyMod[i]);
    }
    fprintf(fichier,"La moyenne generale du filière est: %.2f/20\n", calculer_Moyenne_Generale_Rapport(li));
    fclose(fichier);
    free(MoyMod);
}
void Suprimer_Etudiant(Liste* li, int pos){
    if (li == NULL || li->tete == NULL){
        exit(EXIT_FAILURE);
    }
    EtudiantRepere* Courant=li->tete,*temp;
    char nom_fichier[100];
    if (pos == 1) {
        li->tete = Courant->suivant; // La tête de liste avance au nœud suivant
        free(Courant); // Libération de la mémoire de l'ancien premier nœud
        printf("L'étudiant de position %d est supprimé avec succès.\n", pos);
        return;
    }
    for(int i=1; Courant!=NULL && i<pos-1;i++){
        Courant=Courant->suivant;
    }
    if (Courant == NULL || Courant->suivant == NULL) {
        printf("Position invalide. Aucun étudiant n'a été supprimé.\n");
        return;
    }
    temp=Courant->suivant;
    Courant->suivant=temp->suivant;
    sprintf(nom_fichier, "%s_rapport.txt", temp->nom);
    if(remove(nom_fichier) == 0){
        printf("Le fichier '%s' a ete supprime avec succes.\n", nom_fichier);
    } else {
        perror("Erreur lors de la suppression du fichier");
    }
    free(temp);
    printf("L'etudiant de position %d est supprime avec succes.\n", pos);
    li->nef--;
    Generer_Rapport_Academique(li);
}
int main (){
    int C,k;
    char nom[50];   
    Liste* liste = lire_fichier_txt();
    do{
        afficher_menu();
        scanf("%d",&C);
        switch(C){
            case 1:
            ajouter_Etudiant_liste(liste);
            creer_fichier_txt();
            enregistrer_liste_etudiant(liste);
            break;
            case 2:
            afficher_liste_Etudiant(liste);
            break;
            case 3:
            printf("veuiller saisir le nom de l etu que souhaiter suprimer: ");
            int nbt=0;
            int* pos=NULL;
            fflush(stdin); //vider le tampon
            fgets(nom,50, stdin);
            nom[strcspn(nom,"\n")] = '\0';
            pos=Recherche_et_Affichage_des_Informations_nom(liste,&nbt);
            Rech_Pos_Occ(pos,nbt);
            for(int i=0;i<nbt;i++){
                Suprimer_Etudiant(liste,pos[i]);
            }
            creer_fichier_txt();
            enregistrer_liste_etudiant(liste);
            break;
            case 4:
            do{   
                afficher_menu_recherche();
                scanf("%d",&k);
                switch(k){
                    int nbt=0;
                    int* pos=NULL;
                    case 1:
                    pos=Recherche_et_Affichage_des_Informations_nom(liste,&nbt);
                    Rech_Pos_Occ(pos,nbt);
                    break;
                    case 2:
                    pos=Recherche_et_Affichage_des_Informations_age(liste,&nbt);
                    Rech_Pos_Occ(pos,nbt);
                    break;
                    case 3:
                    printf("tst");
                    int position;
                    position = Recherche_et_Affichage_des_Informations_identifiant(liste);
                    printf("La position de cet etudiant est: %d",position);
                    break;
                    case 5:
                    C=7;
                    printf("Au revoir");
                    break;
                    default:
                    printf("Option invalide, veuillez reessayer.\n");
                    break;
                }
            }while (k!=4 && k!=5);
            break;
            case 5:
            printf("modification:\n");
            int position=0;
            position=Recherche_tous(liste);
            if(position>0){
                modifier_infor(liste,position);
            }
            break;
            case 6: 
            Generer_Rapport_Academique(liste);
            break;
            case 7:
            printf("Au revoir");
            break;
            default:
            printf("Option invalide, veuillez reessayer.\n");
            break;
        }
    }while (C != 7);
    return 0;
} 