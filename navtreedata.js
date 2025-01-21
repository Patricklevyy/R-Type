/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "R-TYPE", "index.html", [
    [ "Documentation: Gestionnaire UDP pour le projet R-Type", "md_documentation_2Documentation__gestionnaire__UDP__RType.html", [
      [ "1. Structure des messages UDP", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md1", [
        [ "Description des champs", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md2", null ]
      ] ],
      [ "2. Sérialisation et Désérialisation", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md3", [
        [ "Implémentation : Classe <tt>MessageCompressor</tt>", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md4", [
          [ "Méthode <tt>serialize</tt>", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md5", null ],
          [ "Méthode <tt>deserialize</tt>", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md6", null ]
        ] ],
        [ "Processus détaillé", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md7", null ]
      ] ],
      [ "3. Calcul de la bande passante", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md8", [
        [ "Répartition de la taille des messages", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md9", null ],
        [ "Exemple", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md10", null ],
        [ "Formule de bande passante", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md11", [
          [ "Exemple :", "md_documentation_2Documentation__gestionnaire__UDP__RType.html#autotoc_md12", null ]
        ] ]
      ] ]
    ] ],
    [ "Système de Build CMake pour le Projet R-Type", "md_documentation_2CMakeDocumentation.html", [
      [ "Prérequis", "md_documentation_2CMakeDocumentation.html#autotoc_md16", null ],
      [ "Fonctionnalités", "md_documentation_2CMakeDocumentation.html#autotoc_md18", null ],
      [ "Instructions d'installation et d'utilisation", "md_documentation_2CMakeDocumentation.html#autotoc_md20", [
        [ "1. Cloner le dépôt", "md_documentation_2CMakeDocumentation.html#autotoc_md21", null ],
        [ "2. Configurer le projet", "md_documentation_2CMakeDocumentation.html#autotoc_md22", null ],
        [ "3. Compiler le projet", "md_documentation_2CMakeDocumentation.html#autotoc_md23", null ],
        [ "4. Exécuter les binaires", "md_documentation_2CMakeDocumentation.html#autotoc_md24", null ]
      ] ],
      [ "Structure du Projet", "md_documentation_2CMakeDocumentation.html#autotoc_md26", null ],
      [ "Sections techniques du script CMake", "md_documentation_2CMakeDocumentation.html#autotoc_md28", [
        [ "Prérequis minimaux", "md_documentation_2CMakeDocumentation.html#autotoc_md29", null ],
        [ "Intégration de Vcpkg", "md_documentation_2CMakeDocumentation.html#autotoc_md30", null ],
        [ "Gestion des dépendances", "md_documentation_2CMakeDocumentation.html#autotoc_md31", null ],
        [ "Organisation des fichiers sources", "md_documentation_2CMakeDocumentation.html#autotoc_md32", null ],
        [ "Création des cibles", "md_documentation_2CMakeDocumentation.html#autotoc_md33", null ]
      ] ],
      [ "Résolution des problèmes", "md_documentation_2CMakeDocumentation.html#autotoc_md35", null ],
      [ "- Vérifiez que <tt>vcpkg.json</tt> est correctement configuré pour inclure les versions des dépendances nécessaires.", "md_documentation_2CMakeDocumentation.html#autotoc_md36", null ],
      [ "Notes supplémentaires", "md_documentation_2CMakeDocumentation.html#autotoc_md37", null ]
    ] ],
    [ "Documentation des Frameworks et Bibliothèques Utilisés", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html", [
      [ "1. vcpkg", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md40", [
        [ "Rôle", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md41", null ],
        [ "Utilisation", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md42", null ],
        [ "Raisons du choix", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md43", null ]
      ] ],
      [ "2. SFML (Simple and Fast Multimedia Library)", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md45", [
        [ "Rôle", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md46", null ],
        [ "Utilisation", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md47", null ],
        [ "Raisons du choix", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md48", null ],
        [ "Comparatif avec SDL2 et Raylib", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md49", null ]
      ] ],
      [ "3. libconfig", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md51", [
        [ "Rôle", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md52", null ],
        [ "Utilisation", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md53", null ],
        [ "Raisons du choix", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md54", null ]
      ] ],
      [ "4. CMake", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md56", [
        [ "Rôle", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md57", null ],
        [ "Utilisation", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md58", null ],
        [ "Raisons du choix", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md59", null ]
      ] ],
      [ "5. Doxygen", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md61", [
        [ "Rôle", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md62", null ],
        [ "Utilisation", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md63", null ],
        [ "Raisons du choix", "md_documentation_2Documentation__frameworks__bibliotheques__utilises.html#autotoc_md64", null ]
      ] ]
    ] ],
    [ "Espaces de nommage", "namespaces.html", [
      [ "Liste des espaces de nommage", "namespaces.html", "namespaces_dup" ],
      [ "Membres de l'espace de nommage", "namespacemembers.html", [
        [ "Tout", "namespacemembers.html", null ],
        [ "Fonctions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Énumérations", "namespacemembers_enum.html", null ],
        [ "Valeurs énumérées", "namespacemembers_eval.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Liste des classes", "annotated.html", "annotated_dup" ],
      [ "Index des classes", "classes.html", null ],
      [ "Hiérarchie des classes", "hierarchy.html", "hierarchy" ],
      [ "Membres de classe", "functions.html", [
        [ "Tout", "functions.html", "functions_dup" ],
        [ "Fonctions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", null ],
        [ "Définitions de type", "functions_type.html", null ]
      ] ]
    ] ],
    [ "Fichiers", "files.html", [
      [ "Liste des fichiers", "files.html", "files_dup" ],
      [ "Membres de fichier", "globals.html", [
        [ "Tout", "globals.html", null ],
        [ "Fonctions", "globals_func.html", null ],
        [ "Variables", "globals_vars.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"ATH_8hpp.html",
"RoomHandling_8hpp_source.html",
"classecs_1_1Velocity.html",
"classrtype_1_1ERROR_1_1RoomNotFoundExceptions.html",
"classrtype_1_1Monster.html#a0c9deea5ca2150e28f0a38234370b1ab",
"classrtype_1_1SpriteId.html#a0cf38b773b696f38f1cc3a672adad7d5",
"namespacertype.html#a4dfee7a3dedb8a551726b7adcf8c0f62"
];

var SYNCONMSG = 'cliquez pour désactiver la synchronisation du panel';
var SYNCOFFMSG = 'cliquez pour activer la synchronisation du panel';