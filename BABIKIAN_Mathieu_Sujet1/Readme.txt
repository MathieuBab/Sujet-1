Sujet 1 : Prédire le prix d’une habitation que l'on veut mettre en location sur la plateforme Airbnb.


Vérifiez d'avoir dans le dossier les fichiers :

    airbnb_donnees_propres.csv
    airbnbEntrainement.csv
    airbnbTest.csv
    fonction.c
    fonction.h
    main.c
    Makefile


Pour lancer l'algorithme :

    Ouvrez un terminal dans le dossier où se trouve les fichiers.

    Puis, dans le terminal, rentrez la commande : 
        make

    Si make ne fonction pas, essayez :
        make -f Makefile 
    (pour indiquer que le makefile se nomme Makefile)


Afin de supprimer tous les fichiers objet complilés, d'extension *.o :

    Dans le terminal où se trouve les fichiers, rentrer la commande : 
        make clean


Afin de supprimer tous les fichiers objet complilés, d'extension *.o ainsi que l'exécutable :
    Dans le terminal où se trouve les fichiers, rentrer la commande : 
        make mrproper


Pour archiver tous les fichiers relatifs au projet :

    Dans le terminal où se trouve les fichiers, rentrer la commande : 
        make tar


Afin d'accéder à la documentation il suffit d'aller dans le dossier html, et d'ouvrir le index.html, ou pour la documentation en pdf, il faut aller dans le dossier 
latex et ouvrir le refman.pdf