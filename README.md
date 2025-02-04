# GooglyEyes
Projet Arduino - 1ere année Polytech Dijon

Le but de ce projet est de reproduire le comportement de Googly Eyes (petits yeux en plastique qui bougent) sur des écrans, à l'aide d'un arduino et de capteurs. Des émotions ont aussi été ajoutées aux yeux grâce aux écrans, elles varient si on secoue trop fort le capteur ou si on le laisse au repos un certain temps.

## MATERIEL

- Arduino : NANO 33 IOT
- Ecrans : 2 PIMORONI PIM374 1.12" Mono OLED (128x128, white/black) Breakout – I2C

## INSTALLATION

*Bibliothèques :*

- Adafruit_SH110X (+ toutes ses dépendances, **sans affichage du splashscreen**)
- Arduino_LSM6DS3

*Materiel :*

- Connecter les deux écrans en dérivation
- L'Arduino NANO 33 IOT est déjà équipée d'une IMU (accélérometre, gyroscope...) mais ces capteurs peuvent êtres rajoutés séparéments à une carte non-équipée

## REMERCIEMENTS

Conversion d'images vers bitmap pour aduino : https://javl.github.io/image2cpp/
