
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
EtudiantRepere * Creer_Etudiant(){
    EtudiantRepere *P=(EtudiantRepere*)malloc(sizeof(EtudiantRepere));
    printf("\nEntrez l'identifiant de l'etudiant :");
    scanf(" %d", &P->Id);
    fflush(stdin);//vider le tampon
    printf("Entrez le nom de l'etudiant :");
    fgets(P->nom,50, stdin); 
    P->nom[strcspn(P->nom,"\n")] = '\0';
    printf("Entrez le prenom de l'etudiant :");
    fgets(P->prenom,50, stdin); // Lire le prenom, même s'il contient des espaces
    P->prenom[strcspn(P->prenom, "\n")] = '\0'; // Retirer le caractère '\n' ajouté par fgets
    printf("Entrez la date de naissance (jour mois annee) :");
    scanf("%d %d %d", &P->date.jour, &P->date.mois, &P->date.annee);
    P->age=calculerAge(P);
    for (int i = 0; i < NBR_NOTES; i++) { 
        if (i == 0) {
            strcpy(P->note[i].libelle, "Théorie des Graphes et Recherche Opérationnelle");
        } else if (i == 1) {
            strcpy(P->note[i].libelle, "Architecture des Ordinateurs & Assembleur");
        } else if (i == 2) {
            strcpy(P->note[i].libelle, "Base des Données Relationnelles");
        } else if (i == 3) {
            strcpy(P->note[i].libelle, "Réseaux Informatiques");
        } else if (i == 4) {
            strcpy(P->note[i].libelle, "Structure de Données en C");
        } else if (i == 5) {
            strcpy(P->note[i].libelle, "Langues étrangères 1");
        } else if (i == 6) {
            strcpy(P->note[i].libelle, "Digital Skills");
        } else if (i == 7) {
            strcpy(P->note[i].libelle, "Systèmes d'Exploitation et Linux");
        } else if (i == 8) {
            strcpy(P->note[i].libelle, "Modélisation Orientée Objet");
        } else if (i == 9) {
            strcpy(P->note[i].libelle, "Théories des Langages et Compilation");
        } else if (i == 10) {
            strcpy(P->note[i].libelle, "Développement Web");
        } else if (i == 11) {
            strcpy(P->note[i].libelle, "Programmation Orientée Objet Java");
        } else if (i == 12) {
            strcpy(P->note[i].libelle, "Langues étrangères 2");
        } else if (i == 13) {
            strcpy(P->note[i].libelle, "Culture & Arts & Sport Skills");
        }
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
    return P;
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
        printf("Identifiant: %d\nNom: %s\nPrenom: %s\nAge: %d ans , ne le %d/%d/%d \n",P->Id, P->nom, P->prenom, P->age, P->date.jour, P->date.mois,P->date.annee);
        for (int i = 0; i < NBR_NOTES; i++) { 
            printf("Note en %s : %.2f/20\n", P->note[i].libelle, P->note[i].valeur);
        }
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
    printf("Le fichier a ete cree avec succes\n");
}
void enregistrer_liste_etudiant(Liste* li) { // fonction pour enregistrer les etudiants ans un fichier txt
    FILE* fichier = fopen("pEtudiants.txt", "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    EtudiantRepere* P = li->tete;
    while (P != NULL) {
        fprintf(fichier, "%d\t| %s\t| %s\t| %i\t| %d/%d/%d\t|", P->Id, P->nom, P->prenom, P->age, P->date.jour, P->date.mois,P->date.annee);
        for (int i = 0; i < NBR_NOTES; i++) {
            fprintf(fichier, "%.2f/20\t| ", P->note[i].valeur);
        }
        fprintf(fichier,"%.2f/20\n",P->Moy);
        printf("L'etudiant '%s %s' a ete enregistrer avec succes.\n", P->nom, P->prenom);
        P = P->suivant;
    }
    fclose(fichier);
}
void afficher_menu() {
    printf("\nMenu:\n");
    printf("1. Ajouter etudiant\n");
    printf("2. Afficher liste etudiant\n");
    printf("3. Quitter\n");
    printf("Choisissez une option: ");
}
int main (){
    int C;
    Liste* liste = Creer_Liste_Etudiants();
    creer_fichier_txt();
    do{
        afficher_menu();
        scanf("%d",&C);
        switch(C){
            case 1:
            ajouter_Etudiant_liste(liste);
            break;
            case 2:
            afficher_liste_Etudiant(liste);
            break;
            case 3:
            enregistrer_liste_etudiant(liste);
            break;
            default:
            printf("Option invalide, veuillez reessayer.\n");
            break;
        }
    }while (C != 3);
    return 0;
}//okeee