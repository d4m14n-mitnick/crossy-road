# Cruzando-la-canasta-basica

## Contenido:
1. Descripción General
2. Tecnologías utilizadas
3. Funcionamiento y/o manual
4. Diagrama de clases UML del proyecto

## Descripción General
Este juego está  programado en C++, inspirado en Crossy Road, pero ambientado en un supermercado Bodega Aurrera (funcionando como parodia). En lugar de carreteras y ríos, el escenario presenta bandas transportadoras, mientras que los vehículos son reemplazados por  despensa. El personaje principal es Mamá Lucha, y el objetivo es esquivar los obstáculos en movimiento para llegar a los anaqueles superiores. Esta versión adapta la jugabilidad clásica del arcade original a un entorno dinámico y único en un supermercado.

## Tecnologías utilizadas:
- C++
- SFML
- Mingw
- Make

## Funcionamiento y/o manual

### Menú Principal:

![Ménu Principal](/assets/images/capturas%20de%20pantalla/menu_principal.PNG)

**Botón Jugar:** Ejecuta el juego

**Botón Niveles:** Se tenía pensado hacer más de un nivel, pero por el tiempo no se termino de implementar, su propósito es mostrar los diferentes niveles.

**Salir:** Cierra la ventana y el programa.

### Ejecución del juego:

![Ejecución del juego](/assets/images/capturas%20de%20pantalla/ejecucion.PNG)

El objetivo es esquivar todos los obstáculos y finalmente llegar a los estantes superiores.

El movimiento del jugador consiste en cuatro direcciones arriba, abajo, izquierda y derecha. Y este es controlado por las flechas del teclado.

### Ventana Ganador:

![Ventana Ganador](/assets/images/capturas%20de%20pantalla/ventana_ganador.PNG)

Esta ventana se muestra cuando llegas a los estantes superiores y por ende ganas el nivel.

**Botón volver a jugar:** Reinicia la partida para que puedas volver a a jugar.

**Botón regresar al menu:** Te regresa al menú principal.

### Ventana Perdedor:

![Ventana Perdedor](/assets/images/capturas%20de%20pantalla/ventana_perdedor.PNG)

Esta ventana es generada cuando pierdes chocando con algunos de los obstáculos que se mueven a través de las bandas transportadoras.

**Botón Reintentar:** Reinicia la partida para que puedas volver a a jugar.

**Botón regresar al menu:** Te regresa al menú principal.

## Diagrama de clases UML del proyecto:

![Diagrama UML](/assets/images/capturas%20de%20pantalla/diagrama_uml.png)