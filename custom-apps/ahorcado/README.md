# Ahorcado - Juego del Ahorcado para NeonBitOS

Implementación simple y divertida del clásico juego del ahorcado en español.

## 🎮 Características

- ✅ **~480 palabras en español** - Sin letra Ñ (compatible teclado US)
- ✅ **24 categorías temáticas** - Pistas para cada palabra
- ✅ **Interfaz simple** - ASCII art clásico
- ✅ **Sin dependencias** - Compilado estáticamente
- ✅ **Dominio público** - Código libre para usar

## 📚 Categorías de Palabras

Cada palabra muestra su categoría como pista durante el juego:

1. **ANIMALES** (40 palabras) - Elefante, Jirafa, Tigre...
2. **FRUTAS Y VEGETALES** (29 palabras) - Manzana, Naranja, Tomate...
3. **OBJETOS COTIDIANOS** (30 palabras) - Computadora, Telefono, Mesa...
4. **TECNOLOGIA Y CIENCIA** (40 palabras) - Internet, Galaxia, Atomo...
5. **PROFESIONES** (29 palabras) - Medico, Ingeniero, Programador...
6. **NATURALEZA** (35 palabras) - Volcan, Rio, Bosque, Tormenta...
7. **DEPORTES** (25 palabras) - Futbol, Tenis, Natacion...
8. **MUSICA E INSTRUMENTOS** (20 palabras) - Guitarra, Piano, Violin...
9. **COLORES** (20 palabras) - Rojo, Azul, Verde, Turquesa...
10. **PAISES Y CIUDADES** (29 palabras) - Argentina, Mexico, Paris...
11. **COMIDA** (25 palabras) - Pizza, Hamburguesa, Sushi...
12. **EMOCIONES Y SENTIMIENTOS** (20 palabras) - Felicidad, Amor, Paz...
13. **EDIFICIOS Y LUGARES** (29 palabras) - Castillo, Biblioteca, Museo...
14. **ROPA Y ACCESORIOS** (24 palabras) - Camisa, Zapatos, Sombrero...
15. **TRANSPORTES** (20 palabras) - Avion, Barco, Tren...
16. **HERRAMIENTAS** (15 palabras) - Martillo, Sierra, Taladro...
17. **VERBOS** (22 palabras) - Correr, Saltar, Nadar...
18. **ADJETIVOS** (24 palabras) - Grande, Rapido, Dulce...
19. **FENOMENOS NATURALES** (15 palabras) - Terremoto, Eclipse, Aurora...
20. **MATEMATICAS** (20 palabras) - Numero, Ecuacion, Triangulo...
21. **QUIMICA** (15 palabras) - Oxigeno, Carbono, Oro...
22. **CUERPO HUMANO** (23 palabras) - Cabeza, Corazon, Cerebro...
23. **TIEMPO** (18 palabras) - Segundo, Hora, Semana...
24. **CYBERPUNK** (20 palabras) - Hacker, Neon, Cyborg, Matriz...

**Total: ~480 palabras**

## 🔧 Compilación

```bash
make
```

Genera un binario estático de ~920KB sin dependencias.

## 🎯 Uso

```bash
# Jugar
./ahorcado

# Ver ayuda
./ahorcado --help
```

## 🎲 Cómo Jugar

1. El juego selecciona una palabra aleatoria
2. Muestra la **categoría como pista**
3. Adivina letra por letra
4. Tienes 6 intentos antes de perder
5. ¡Intenta no ahorcar al muñeco!

## 📊 Ejemplo de Juego

```
╔═══════════════════════════════════════╗
║          AHORCADO - NeonBitOS         ║
╚═══════════════════════════════════════╝

  +---+
  |   |
  O   |
 /|   |
      |
      |
=========

Categoria: TECNOLOGIA Y CIENCIA

Palabra: _ O M P U _ A _ O _ A

Letras usadas: A E I O U T L

Intentos restantes: 3/6

Ingresa una letra:
```

## ⌨️ Compatibilidad de Teclado

**Compatible con teclado US International**

## 🔮 Palabras Cyberpunk

Incluye palabras temáticas de NeonBitOS en la categoría CYBERPUNK:
- CIBERNETICO, DIGITAL, VIRTUAL, BINARIO
- CODIGO, DATOS, INFORMACION, SISTEMA, RED
- HACKER, FIREWALL, ENCRIPTACION, ALGORITMO
- MATRIZ, NEON, HOLOGRAM, ANDROID, CYBORG, ROBOT

## 🎨 Interfaz

El juego muestra:
- ✅ Dibujo ASCII del ahorcado (7 etapas)
- ✅ **Categoría de la palabra (PISTA)**
- ✅ Palabra oculta con espacios
- ✅ Letras ya usadas
- ✅ Intentos restantes

## 📝 Añadir Más Palabras

Edita el array `palabras[]` en `ahorcado.c`:

```c
const PalabraConCategoria palabras[] = {
    {"PALABRA1", 0},  // 0 = ANIMALES
    {"PALABRA2", 23}, // 23 = CYBERPUNK
    // ...
};
```

**Importante**: No uses palabras con Ñ para mantener compatibilidad con teclado US.

## 🛠️ Estructura del Código

```c
// Sistema de categorías
typedef struct {
    const char *palabra;
    int categoria;
} PalabraConCategoria;

// 24 categorías diferentes
const char *nombres_categorias[] = {
    "ANIMALES",
    "FRUTAS Y VEGETALES",
    // ... 22 más
};
```

## 📜 Licencia

Dominio Público - Código libre para NeonBitOS

## 💡 Características Técnicas

- Sin warnings de compilación
- Validación de entrada con scanf
- Limpieza de buffer automática
- Manejo robusto de errores
- Código C99 estándar
- ~480 líneas de código

## 🎯 Ideas Futuras

- [ ] Modo de dificultad (fácil/medio/difícil)
- [ ] Contador de victorias/derrotas
- [ ] Opción de ver todas las categorías
- [ ] Modo "solo categoría X"
- [ ] Más palabras (objetivo: 1000+)
- [ ] Soporte multiidioma (mantener español como default)

---

**ahorcado** - *Diversión clásica en español, optimizado para NeonBitOS* 🎮⚡
