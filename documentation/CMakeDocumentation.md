# Système de Build CMake pour le Projet R-Type

Ce projet est un jeu avec une architecture client-serveur, configuré et construit à l'aide de CMake. Ce système de build gère automatiquement les dépendances via Vcpkg, organise les fichiers sources et génère deux exécutables : un pour le client et un pour le serveur.

---

## Prérequis

Avant de commencer, assurez-vous que les outils suivants sont installés sur votre système :

- **CMake** (version 3.21 ou supérieure)
- **Git**
- **Vcpkg** (si absent, le script le configure automatiquement)
- **Compilateur C++17**

---

## Fonctionnalités

- **Gestion des dépendances** :
  - Utilisation de [Vcpkg](https://github.com/microsoft/vcpkg) pour la gestion des bibliothèques externes.
  - Dépendances automatiquement configurées et installées si nécessaire.
  - Activation du mode manifeste si un fichier `vcpkg.json` est présent.
  
- **Dépendances intégrées** :
  - `fmt` : bibliothèque pour la mise en forme des sorties.
  - `libconfig` : bibliothèque pour les fichiers de configuration.
  - `SFML` : bibliothèque multimédia pour les graphismes et l'audio.

- **Organisation des fichiers sources** :
  - Code spécifique au client : `rtype_game/client/`.
  - Code spécifique au serveur : `rtype_game/server/`.
  - Code partagé entre client et serveur : `rtype_game/shared/`.
  - Fonctionnalités additionnelles : `ecs/`.

- **Cibles générées** :
  - `r-type_client` : exécutable pour le client.
  - `r-type_server` : exécutable pour le serveur.

---

## Instructions d'installation et d'utilisation

### 1. Cloner le dépôt

Cloner le projet dans votre répertoire de travail :
```bash
git clone <repository-url>
cd <repository-folder>
```

### 2. Configurer le projet

Exécuter la commande suivante pour générer les fichiers de configuration :
```bash
cmake -S . -B build
```

### 3. Compiler le projet

Compiler les cibles générées par CMake :
```bash
cmake --build build
```

### 4. Exécuter les binaires

Une fois la compilation terminée, vous pouvez exécuter les applications client et serveur :
```bash
./build/r-type_server
./build/r-type_client
```

---

## Structure du Projet

Voici une description de la structure des fichiers du projet :

- **rtype_game/client/** : Code spécifique au client.
- **rtype_game/server/** : Code spécifique au serveur.
- **rtype_game/shared/** : Code partagé entre le client et le serveur.
- **ecs/** : Gestion des entités et des composants.

---

## Sections techniques du script CMake

### Prérequis minimaux
```cmake
cmake_minimum_required(VERSION 3.21)
project(RType LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)
```

### Intégration de Vcpkg
```cmake
if(NOT DEFINED ENV{VCPKG_ROOT})
    message(STATUS "Vcpkg non trouvé dans l’environnement. Clonage et configuration en cours...")
    execute_process(COMMAND git clone https://github.com/microsoft/vcpkg.git ${CMAKE_BINARY_DIR}/vcpkg)
    execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg)
    set(ENV{VCPKG_ROOT} "${CMAKE_BINARY_DIR}/vcpkg")
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Fichier de chaîne d'outils Vcpkg")
```

### Gestion des dépendances
```cmake
find_package(fmt CONFIG REQUIRED)
find_package(libconfig CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
```

### Organisation des fichiers sources
```cmake
file(GLOB_RECURSE CLIENT_SRC
    "${CMAKE_SOURCE_DIR}/rtype_game/client/*.cpp"
    "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp"
    "${CMAKE_SOURCE_DIR}/ecs/*.cpp"
)

file(GLOB_RECURSE SERVER_SRC
    "${CMAKE_SOURCE_DIR}/rtype_game/server/*.cpp"
    "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp"
    "${CMAKE_SOURCE_DIR}/ecs/*.cpp"
)
```

### Création des cibles
```cmake
add_executable(r-type_client ${CLIENT_SRC})
add_executable(r-type_server ${SERVER_SRC})

target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)
target_link_libraries(r-type_server PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)
```
---

## Résolution des problèmes

- **Problèmes de dépendances :**
  - Vérifiez que Vcpkg est bien cloné et initialisé.
  - Vérifiez que `vcpkg.json` est correctement configuré pour inclure les versions des dépendances nécessaires.
---

## Notes supplémentaires

- **Dossier de sortie :** Les binaires sont placés dans `build/bin`.
- **Personnalisation :**
  - Il est possible d'ajouter des options spécifiques au compilateur dans `add_compile_options`.
  - Les dépendances supplémentaires peuvent être ajoutées dans la section `find_package`.
