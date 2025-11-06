# 🎮 PINBALL

## 🕹️ Juego Original
Juego original elegido para la referencia: **Metal Pinball** en ClassicGame.  
🔗 [Jugar al original](https://www.classicgame.com/game/Metal+Pinball)

## 🧩 Descripción
Imitación de un **pinball** realizada en **C++** usando **Box2D** para la física y **raylib** para render y audio.  
El objetivo del proyecto es replicar la jugabilidad clásica del pinball con físicas reales, puntuación por combos y un ciclo de rondas con número limitado de bolas.

## ✨ Key Features

- ⚙️ Física realista basada en Box2D: colisiones, rebotes y fuerzas aplicadas a la bola.  
- 🕹️ Flippers y kicker controlables con entrada del usuario.
- 🧮 Sistema de puntuación con un combo: Si golpeas una pelota verde y una roja en menos de 3 sec.  
- 🧭 UI básica: puntuación actual y récord de sesión; menús de inicio, instrucciones y pantalla de fin de ronda.  
- 🔊 Audio: efectos por colisiones, música de fondo.  
- 🧰 Herramientas de depuración: F1 muestra hitboxes, mouse joint para arrastrar la bola.

## 🎮 Controles

- `N` : encender o apagar sonido  
- `M` : encender o apagar música

**En el menú:**
- `Enter` o click izquierdo en **PIN-BALL NOW** → pasa a **How to Play**  
- Click izquierdo en **MUSIC / SOUND** para alternar audio

**En How to Play:**
- `Enter` o click izquierdo en **TAP TO START** → pasa al gameplay

**En el gameplay:**
- `A` / Flecha izquierda : Flippers de la izquierda  
- `D` / Flecha derecha : Flippers de la derecha  
- Flecha abajo : Impulso inicial (kicker)  
- `R` : Resetear la pelota  
- `F1` : Mostrar hitboxes / activar modo debug (mouse joint)  
- Click izquierdo en la pelota para arrastrarla con el mouse

**En la pantalla de eliminación (Game Over):**
- `Enter` para volver al menú

## 👩‍💻 Developers

| Desarrollador | GitHub | Aportaciones |
|--------------|--------|--------------|
| **Marc Jiménez** | [MarcJM-00](https://github.com/MarcJM-00) | Estados del juego, gestión de una sola bola y reseteo, corrección de fallos, interacción con el ratón, círculos verdes y animación de estos. |
| **Irene Calatrava** | [irentren](https://github.com/irentren) | Creación e implementación de los flippers, arreglo de los errores de *memory leaks* , diseño del mapa *pinball-1*. |
| **Jan Corredor** | [JanCorredor](https://github.com/JanCorredor) | Música, sonido, corrección de errores, optimización, ajustes de física, limitación de FPS y parte de controles. |
| **Queralt Escutilla** | [Keral06](https://github.com/Keral06) | Propulsión de la pelota, rebote con botones, corrección de *memory leaks*. |
| **Rubén Mateo** | [Rubenmg0](https://github.com/Rubenmg0) | Mapa *pinball-2*, carga de texturas y background, render de flippers conectado con Box2D, sistema de puntos + combo, visualización de *memory leaks* e intento de GitHub Actions. |

## 📜 Licencia

Este proyecto está publicado bajo **MIT License** (sin modificaciones).  
Consulta el archivo `LICENSE` para más detalles.
