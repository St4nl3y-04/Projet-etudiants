int valide_datenaissance(EtudiantRepere* P) {
    // Tableau des jours par mois (par défaut, février a 28 jours)
    int jours_par_mois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Vérifie si l'année est bissextile
    if ((P->date.annee % 4 == 0 && P->date.annee % 100 != 0) || (P->date.annee % 400 == 0)) {
        jours_par_mois[1] = 29;  // Février a 29 jours dans une année bissextile
    }
    // Vérification du mois
    if (P->date.mois < 1 || P->date.mois > 12) {
        printf("Mois invalide.\n");
        return -1;
    }
    // Vérification du jour
    if (P->date.jour < 1 || P->date.jour > jours_par_mois[P->date.mois - 1]) {
        printf("Jour invalide pour le mois %d.\n", P->date.mois);
        return -1;
    }

    // Si tout est valide
    return 1;
}