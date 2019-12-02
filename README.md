3dGraphAnim

## commands to execute
```
	bash bld
```

source for conan : `https://bintray.com/conan/conan-center`

install conan : `pip install conan` with python3

windows conan install -> `conan install ..	-s build_type=Debug --build=missing`
windows cmake commands -> `cmake .. -G "Visual Studio 16 2019"`

conan remote add <REMOTE> https://api.bintray.com/conan/bincrafters/public-conan

TODO

afficher un modele 3d - done
charger un modele 3d - done
placer un modele 3d - done
appliquer une texture dynamiquement - done
appliquer un shader general - done

changer les get d input + changement de position de camera

faire le jeu
 - generation de la carte
 - generation des pieces
   - rotation des pieces (faire tourner toutes les pieces)
   - descendre les pieces (les faire bouger)
 - gerer l'arret d une piece
 - gerer la destruction de ligne
 - gerer la fin de jeu
   - gerer l'augmentation de difficulte

 - faire un mouvement de camera rigodrole
 - gerer les inputs manette