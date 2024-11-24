
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#define NBR_NOTES 14
typedef struct {
    char libelle[30];
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
} EtudiantRepere;
typedef struct ListeRepere{
    EtudiantRepere *tete;
    EtudiantRepere *queue;
    int nef;
}Liste;
Liste * Creer_Liste_Etudiants(){
    Liste *Li;
    Li = (Liste*)malloc(sizeof(Liste));
    Li -> tete = NULL;
    Li -> queue = NULL;
    Li -> nef = 0;
return(Li);
}
EtudiantRepere * Creer_Etudiant(){
    EtudiantRepere *P=(Prod*)malloc(sizeof(Prod));
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
        printf("Entrez la note pour %s : ", P->note[i].libelle); 
        scanf("%f", &P->note[i].valeur); 
    }
    P->suivant=NULL;
    return P;
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
float calculerMoyennePonderee(const EtudiantRepere *P) { 
    float MOY=0;
    for (int i=0;i<NBR_NOTES;i++) {
        MOY+=P->note[i].valeur;
    }
    return (MOY) / NBR_NOTES; 
}
void afficherEtudiant (const EtudiantRepere *P){
    printf("Identifiant: %d\nNom: %s\nPrenom: %s\nAge: %d ans , ne le %d/%d/%d \n",P->Id, P->nom, P->prenom, P->age, P->date.jour, P->date.mois,P->date.annee);
    for (int i = 0; i < NBR_NOTES; i++) { 
        printf("Note en %s : %.2f/20\n", P->note[i].libelle, P->note[i].valeur);}
    float M=calculerMoyennePonderee(P);
    printf("Moyenne ponderee : %.2f/20\n", M); 
}

void creer_fichier_txt (){
    FILE *fichier=fopen("pEtudiants.txt","w");
    if (fichier == NULL){
        perror ("Erreur d'ouverture du fichier");
        return ;
    }
    const char *modules[] = {
        "TG&RO",  // Théorie des Graphes et Recherche Opérationnelle
        "AO&A",   // Architecture des Ordinateurs & Assembleur
        "BDR",   // Base des Données Relationnelles
        "RI",    // Réseaux Informatiques
        "SDC",   // Structure de Données en C
        "LE1",   // Langues étrangères 1
        "DS",    // Digital Skills
        "SE&L",   // Systèmes d’Exploitation et Linux
        "MOO",   // Modélisation Orientée Objet
        "TLC",   // Théories des Langages et Compilation
        "DW",    // Développement Web
        "POO",   // Programmation Orientée Objet Java
        "LE2",   // Langues étrangères 2
        "CASS"   // Culture & Arts & Sport Skills
    };
    fprintf(fichier, "Identifiant\t| Nom\t| Prénom\t| Age\t| Date de Naissance\t|");
    for (int i = 0; i < NBR_NOTES; i++) {
        fprintf(fichier, "%s\t| ", modules[i]);
    }
    fprintf(fichier,"Moyenne Génerale");
    fprintf(fichier, "\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fichier);
    printf("Le fichier a ete cree avec succes\n");
}
int main (){
    int N;
    do {
    printf("Combien d'etudiants voulez-vous entrer ? ");
    scanf("%d", &N);
    } while (N<=0);
    EtudiantRepere *E=(EtudiantRepere*)malloc(N*sizeof(EtudiantRepere));
    if (E == NULL) { 
        perror("Erreur d'allocation memoire\n"); 
        return 1;
    }
    for (int i = 0; i < N; i++) { 
        printf("\n--- Lecture des informations pour l'étudiant %d ---\n", i + 1); 
        lireEtudiant(&E[i]);
    }
    for (int i = 0; i < N; i++) { 
        printf("\n--- Affichage des informations pour l'etudiant %d ---\n", i + 1); 
        afficherEtudiant(&E[i]); 
    }
    creer_fichier_txt();
    free(E);
    return 0;
}