# 🏎️ Turbo Escape

Juego 2D desarrollado en **C++** utilizando la biblioteca gráfica **SFML**, en el marco de la materia **Programación Orientada a Objetos (POO)** de la carrera de Ingeniería en Informática (UNL).

El objetivo del juego es esquivar los obstáculos que aparecen en la carretera mientras se suman puntos a medida que pasa el tiempo. La dificultad aumenta de forma progresiva, haciendo la partida cada vez más desafiante.

## 🎮 Características

- Movimiento del auto y detección de colisiones con obstáculos.
- Sistema de puntaje en tiempo real según el tiempo sobrevivido.
- Dificultad progresiva: la velocidad y frecuencia de obstáculos aumenta con el tiempo.
- Interfaz simple con botones y tipografía personalizada.
- Efectos de audio y música de fondo.

## 🛠️ Tecnologías utilizadas

- **Lenguaje:** C++
- **Librería gráfica:** [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
- **Paradigma:** Programación Orientada a Objetos

## 📁 Estructura del proyecto

- `Auto.cpp / Auto.h` — Lógica y comportamiento del vehículo del jugador.
- `Asfalto.cpp / Asfalto.h` — Manejo de la carretera y su desplazamiento.
- `Boton.cpp / Boton.h` — Botones de la interfaz (menú, reinicio, etc.).
- `Imagenes/` — Recursos gráficos del juego.
- `Musica/` — Audio y efectos de sonido.
- `Tipografia/` — Fuentes utilizadas en la interfaz.

## ▶️ Cómo ejecutarlo

1. Cloná el repositorio: https://github.com/LorenzoViotti-prog/Turbo-Escape.git
2. Asegurate de tener instalada la librería [SFML](https://www.sfml-dev.org/download.php) en tu entorno de desarrollo (Visual Studio / Code::Blocks / MinGW).
3. Compilá el proyecto incluyendo los archivos `.cpp` y enlazando las librerías de SFML.
4. Ejecutá el `.exe` generado — asegurate de que las carpetas `Imagenes`, `Musica` y `Tipografia` estén en la misma ubicación que el ejecutable.

## 👥 Autores

Proyecto grupal desarrollado en 2024 por un equipo de 3 estudiantes de Ingeniería en Informática (UNL):

- **Lorenzo Viotti** — [GitHub](https://github.com/LorenzoViotti-prog)
- Santiago Robledo.
- Joaquín Vetack.

## 📌 Estado del proyecto

Proyecto académico finalizado y aprobado. No se planean nuevas actualizaciones, aunque se aceptan sugerencias.
