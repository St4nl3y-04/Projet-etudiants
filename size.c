int demanderEntier(const char* message) {
    int valeur;
    int c; 
    while (1) {
        printf("%s", message);
        if (scanf("%d", &valeur) != 1) {
            printf("Entree invalide. Veuillez entrer un nombre entier:\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        c = getchar();
        if (c != '\n' && c != EOF) {
            perror("Entree invalide. Veuillez entrer un nombre entier sans caracteres supplementaires.\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        return valeur;
    }
}