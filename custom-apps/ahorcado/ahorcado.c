/*
 * ahorcado - Juego del Ahorcado para NeonBitOS
 * Simple hangman game in Spanish
 *
 * Public Domain - NeonBitOS Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_INTENTOS 6
#define MAX_PALABRA 30
#define MAX_CATEGORIAS 24

// Estructura para palabra con su categoría
typedef struct {
    const char *palabra;
    int categoria;
} PalabraConCategoria;

// Nombres de categorías
const char *nombres_categorias[] = {
    "ANIMALES",
    "FRUTAS Y VEGETALES",
    "OBJETOS COTIDIANOS",
    "TECNOLOGIA Y CIENCIA",
    "PROFESIONES",
    "NATURALEZA",
    "DEPORTES",
    "MUSICA E INSTRUMENTOS",
    "COLORES",
    "PAISES Y CIUDADES",
    "COMIDA",
    "EMOCIONES Y SENTIMIENTOS",
    "EDIFICIOS Y LUGARES",
    "ROPA Y ACCESORIOS",
    "TRANSPORTES",
    "HERRAMIENTAS",
    "VERBOS",
    "ADJETIVOS",
    "FENOMENOS NATURALES",
    "MATEMATICAS",
    "QUIMICA",
    "CUERPO HUMANO",
    "TIEMPO",
    "CYBERPUNK"
};

// Base de datos de palabras (SIN letra Ñ)
const PalabraConCategoria palabras[] = {
    // Animales (0)
    {"ELEFANTE", 0}, {"JIRAFA", 0}, {"LEOPARDO", 0}, {"RINOCERONTE", 0}, {"HIPOPOTAMO", 0},
    {"COCODRILO", 0}, {"SERPIENTE", 0}, {"AGUILA", 0}, {"CONDOR", 0}, {"COLIBRI", 0},
    {"MARIPOSA", 0}, {"LIBELULA", 0}, {"HORMIGA", 0}, {"ABEJA", 0}, {"ESCARABAJO", 0},
    {"DELFIN", 0}, {"BALLENA", 0}, {"TIBURON", 0}, {"PULPO", 0}, {"MEDUSA", 0},
    {"CABALLO", 0}, {"BURRO", 0}, {"CEBRA", 0}, {"CAMELLO", 0}, {"LLAMA", 0},
    {"TIGRE", 0}, {"LEON", 0}, {"PANTERA", 0}, {"GUEPARDO", 0}, {"LINCE", 0},
    {"MURCIELAGO", 0}, {"ZORRO", 0}, {"LOBO", 0}, {"OSO", 0}, {"PANDA", 0},
    {"CANGURO", 0}, {"KOALA", 0}, {"ORNITORRINCO", 0}, {"PINGUINO", 0}, {"FOCA", 0},

    // Frutas y Vegetales (1)
    {"MANZANA", 1}, {"NARANJA", 1}, {"PLATANO", 1}, {"SANDIA", 1}, {"MELON", 1},
    {"FRESA", 1}, {"CEREZA", 1}, {"DURAZNO", 1}, {"CIRUELA", 1}, {"PERA", 1},
    {"MANGO", 1}, {"PAPAYA", 1}, {"COCO", 1}, {"KIWI", 1},
    {"GRANADA", 1}, {"FRAMBUESA", 1}, {"ARANDANO", 1}, {"MORA", 1}, {"GUAYABA", 1},
    {"TOMATE", 1}, {"ZANAHORIA", 1}, {"LECHUGA", 1}, {"ESPINACA", 1}, {"BROCOLI", 1},
    {"COLIFLOR", 1}, {"PEPINO", 1}, {"CALABAZA", 1}, {"BERENJENA", 1}, {"PIMIENTO", 1},

    // Objetos Cotidianos (2)
    {"COMPUTADORA", 2}, {"TELEFONO", 2}, {"TELEVISION", 2}, {"REFRIGERADOR", 2}, {"MICROONDAS", 2},
    {"LAVADORA", 2}, {"ASPIRADORA", 2}, {"VENTILADOR", 2}, {"LAMPARA", 2}, {"RELOJ", 2},
    {"SILLA", 2}, {"MESA", 2}, {"ESCRITORIO", 2}, {"ESTANTE", 2}, {"ARMARIO", 2},
    {"CAMA", 2}, {"ALMOHADA", 2}, {"SABANA", 2}, {"COBIJA", 2}, {"COLCHON", 2},
    {"TENEDOR", 2}, {"CUCHARA", 2}, {"CUCHILLO", 2}, {"PLATO", 2}, {"VASO", 2},
    {"TAZA", 2}, {"CAFETERA", 2}, {"TETERA", 2}, {"LICUADORA", 2}, {"BATIDORA", 2},

    // Tecnología y Ciencia (3)
    {"INTERNET", 3}, {"SOFTWARE", 3}, {"HARDWARE", 3}, {"ALGORITMO", 3}, {"PROGRAMA", 3},
    {"APLICACION", 3}, {"NAVEGADOR", 3}, {"SERVIDOR", 3}, {"ROUTER", 3}, {"MODEM", 3},
    {"PANTALLA", 3}, {"TECLADO", 3}, {"RATON", 3}, {"IMPRESORA", 3}, {"ESCANER", 3},
    {"DISCO", 3}, {"MEMORIA", 3}, {"PROCESADOR", 3}, {"TARJETA", 3}, {"CABLE", 3},
    {"GALAXIA", 3}, {"PLANETA", 3}, {"ESTRELLA", 3}, {"SATELITE", 3}, {"COMETA", 3},
    {"ASTEROIDE", 3}, {"METEORITO", 3}, {"NEBULOSA", 3}, {"AGUJERO", 3}, {"UNIVERSO", 3},
    {"ATOMO", 3}, {"MOLECULA", 3}, {"ELECTRON", 3}, {"PROTON", 3}, {"NEUTRON", 3},
    {"ENERGIA", 3}, {"MATERIA", 3}, {"GRAVEDAD", 3}, {"VELOCIDAD", 3}, {"FUERZA", 3},

    // Profesiones (4)
    {"MEDICO", 4}, {"ENFERMERO", 4}, {"DENTISTA", 4}, {"VETERINARIO", 4}, {"FARMACEUTICO", 4},
    {"INGENIERO", 4}, {"ARQUITECTO", 4}, {"ELECTRICISTA", 4}, {"PLOMERO", 4}, {"CARPINTERO", 4},
    {"MAESTRO", 4}, {"PROFESOR", 4}, {"DIRECTOR", 4}, {"BIBLIOTECARIO", 4}, {"INVESTIGADOR", 4},
    {"PROGRAMADOR", 4}, {"DESARROLLADOR", 4}, {"ANALISTA", 4}, {"TECNICO", 4},
    {"ABOGADO", 4}, {"JUEZ", 4}, {"NOTARIO", 4}, {"FISCAL", 4}, {"DETECTIVE", 4},
    {"BOMBERO", 4}, {"POLICIA", 4}, {"SOLDADO", 4}, {"PILOTO", 4}, {"MARINERO", 4},

    // Naturaleza (5)
    {"VOLCAN", 5}, {"VALLE", 5}, {"COLINA", 5}, {"LLANURA", 5},
    {"RIO", 5}, {"LAGO", 5}, {"LAGUNA", 5}, {"ARROYO", 5}, {"CASCADA", 5},
    {"OCEANO", 5}, {"MAR", 5}, {"PLAYA", 5}, {"COSTA", 5}, {"ISLA", 5},
    {"BOSQUE", 5}, {"SELVA", 5}, {"DESIERTO", 5}, {"TUNDRA", 5}, {"PRADERA", 5},
    {"NUBE", 5}, {"LLUVIA", 5}, {"TORMENTA", 5}, {"RAYO", 5}, {"TRUENO", 5},
    {"VIENTO", 5}, {"HURACAN", 5}, {"TORNADO", 5}, {"CICLON", 5}, {"TIFON", 5},
    {"ARCOIRIS", 5}, {"NIEBLA", 5}, {"ROCIO", 5}, {"ESCARCHA", 5}, {"GRANIZO", 5},

    // Deportes (6)
    {"FUTBOL", 6}, {"BASQUETBOL", 6}, {"VOLEIBOL", 6}, {"TENIS", 6}, {"GOLF", 6},
    {"BEISBOL", 6}, {"SOFTBOL", 6}, {"CRIQUET", 6}, {"RUGBY", 6}, {"HOCKEY", 6},
    {"NATACION", 6}, {"BUCEO", 6}, {"SURF", 6}, {"ESQUI", 6}, {"SNOWBOARD", 6},
    {"ATLETISMO", 6}, {"GIMNASIA", 6}, {"CICLISMO", 6}, {"BOXEO", 6}, {"KARATE", 6},
    {"JUDO", 6}, {"TAEKWONDO", 6}, {"ESGRIMA", 6}, {"TIRO", 6}, {"ARQUERIA", 6},

    // Música e Instrumentos (7)
    {"GUITARRA", 7}, {"PIANO", 7}, {"VIOLIN", 7}, {"FLAUTA", 7}, {"TROMPETA", 7},
    {"TAMBOR", 7}, {"BATERIA", 7}, {"SAXOFON", 7}, {"CLARINETE", 7}, {"TROMBON", 7},
    {"ARPA", 7}, {"BANJO", 7}, {"MANDOLINA", 7}, {"UKELELE", 7}, {"ACORDEON", 7},
    {"ARMONICA", 7}, {"XILOFONO", 7}, {"MARACAS", 7}, {"PANDERO", 7}, {"TRIANGULO", 7},

    // Colores (8)
    {"ROJO", 8}, {"AZUL", 8}, {"VERDE", 8}, {"AMARILLO", 8}, {"NARANJA", 8},
    {"MORADO", 8}, {"ROSA", 8}, {"NEGRO", 8}, {"BLANCO", 8}, {"GRIS", 8},
    {"MARRON", 8}, {"TURQUESA", 8}, {"VIOLETA", 8}, {"DORADO", 8}, {"PLATEADO", 8},
    {"CELESTE", 8}, {"BEIGE", 8}, {"CREMA", 8}, {"CORAL", 8}, {"MAGENTA", 8},

    // Países y Ciudades (9)
    {"ARGENTINA", 9}, {"BRASIL", 9}, {"CHILE", 9}, {"COLOMBIA", 9}, {"ECUADOR", 9},
    {"PERU", 9}, {"VENEZUELA", 9}, {"URUGUAY", 9}, {"PARAGUAY", 9}, {"BOLIVIA", 9},
    {"MEXICO", 9}, {"PORTUGAL", 9}, {"FRANCIA", 9}, {"ITALIA", 9},
    {"ALEMANIA", 9}, {"INGLATERRA", 9}, {"RUSIA", 9}, {"CHINA", 9}, {"JAPON", 9},
    {"BUENOS", 9}, {"MADRID", 9}, {"BARCELONA", 9}, {"PARIS", 9}, {"ROMA", 9},
    {"BERLIN", 9}, {"MOSCU", 9}, {"TOKIO", 9}, {"PEKIN", 9}, {"LONDRES", 9},

    // Comida (10)
    {"PIZZA", 10}, {"HAMBURGUESA", 10}, {"PASTA", 10}, {"ARROZ", 10}, {"POLLO", 10},
    {"CARNE", 10}, {"PESCADO", 10}, {"ENSALADA", 10}, {"SOPA", 10}, {"GUISO", 10},
    {"PAN", 10}, {"GALLETA", 10}, {"PASTEL", 10}, {"TORTA", 10}, {"EMPANADA", 10},
    {"TACO", 10}, {"BURRITO", 10}, {"ENCHILADA", 10}, {"QUESADILLA", 10}, {"TAMALES", 10},
    {"SUSHI", 10}, {"RAMEN", 10}, {"TEMPURA", 10}, {"YAKISOBA", 10}, {"CURRY", 10},

    // Emociones y Sentimientos (11)
    {"FELICIDAD", 11}, {"TRISTEZA", 11}, {"ALEGRIA", 11}, {"NOSTALGIA", 11}, {"MELANCOLIA", 11},
    {"AMOR", 11}, {"ODIO", 11}, {"MIEDO", 11}, {"VALENTIA", 11}, {"CORAJE", 11},
    {"ESPERANZA", 11}, {"ILUSION", 11}, {"DESEO", 11}, {"PASION", 11}, {"TERNURA", 11},
    {"ENOJO", 11}, {"FURIA", 11}, {"CALMA", 11}, {"PAZ", 11}, {"SERENIDAD", 11},

    // Edificios y Lugares (12)
    {"CASA", 12}, {"EDIFICIO", 12}, {"APARTAMENTO", 12}, {"CHOZA", 12},
    {"CASTILLO", 12}, {"PALACIO", 12}, {"FORTALEZA", 12}, {"TORRE", 12}, {"MUSEO", 12},
    {"BIBLIOTECA", 12}, {"ESCUELA", 12}, {"UNIVERSIDAD", 12}, {"HOSPITAL", 12}, {"CLINICA", 12},
    {"IGLESIA", 12}, {"CATEDRAL", 12}, {"MEZQUITA", 12}, {"TEMPLO", 12}, {"SINAGOGA", 12},
    {"ESTADIO", 12}, {"GIMNASIO", 12}, {"PISCINA", 12}, {"PARQUE", 12}, {"JARDIN", 12},
    {"MERCADO", 12}, {"TIENDA", 12}, {"SUPERMERCADO", 12}, {"RESTAURANTE", 12}, {"CAFETERIA", 12},

    // Ropa y Accesorios (13)
    {"CAMISA", 13}, {"PANTALON", 13}, {"FALDA", 13}, {"VESTIDO", 13}, {"BLUSA", 13},
    {"SUETER", 13}, {"CHAQUETA", 13}, {"ABRIGO", 13}, {"BUFANDA", 13}, {"GUANTES", 13},
    {"SOMBRERO", 13}, {"GORRA", 13}, {"BOINA", 13}, {"CORBATA", 13},
    {"ZAPATOS", 13}, {"BOTAS", 13}, {"SANDALIAS", 13}, {"PANTUFLAS", 13}, {"ZAPATILLAS", 13},
    {"CALCETINES", 13}, {"MEDIAS", 13}, {"ROPA", 13}, {"INTERIOR", 13}, {"PIJAMA", 13},

    // Transportes (14)
    {"AUTOMOVIL", 14}, {"CAMION", 14}, {"AUTOBUS", 14}, {"MOTOCICLETA", 14}, {"BICICLETA", 14},
    {"AVION", 14}, {"HELICOPTERO", 14}, {"COHETE", 14}, {"NAVE", 14}, {"SATELITE", 14},
    {"BARCO", 14}, {"YATE", 14}, {"CANOA", 14}, {"KAYAK", 14}, {"SUBMARINO", 14},
    {"TREN", 14}, {"METRO", 14}, {"TRANVIA", 14}, {"TELEFERICO", 14}, {"FUNICULAR", 14},

    // Herramientas (15)
    {"MARTILLO", 15}, {"DESTORNILLADOR", 15}, {"LLAVE", 15}, {"ALICATE", 15}, {"TENAZA", 15},
    {"SIERRA", 15}, {"TALADRO", 15}, {"NIVEL", 15}, {"CINTA", 15}, {"REGLA", 15},
    {"HACHA", 15}, {"PALA", 15}, {"RASTRILLO", 15}, {"AZADA", 15}, {"TIJERAS", 15},

    // Verbos (16)
    {"CORRER", 16}, {"SALTAR", 16}, {"NADAR", 16}, {"VOLAR", 16}, {"CAMINAR", 16},
    {"CANTAR", 16}, {"BAILAR", 16}, {"ESCRIBIR", 16}, {"LEER", 16}, {"DIBUJAR", 16},
    {"PINTAR", 16}, {"ESCULPIR", 16}, {"CREAR", 16}, {"CONSTRUIR", 16},
    {"PENSAR", 16}, {"IMAGINAR", 16}, {"RECORDAR", 16}, {"OLVIDAR", 16},
    {"APRENDER", 16}, {"ESTUDIAR", 16}, {"PRACTICAR", 16}, {"ENTRENAR", 16},

    // Adjetivos (17)
    {"GRANDE", 17}, {"ALTO", 17}, {"BAJO", 17}, {"LARGO", 17},
    {"CORTO", 17}, {"ANCHO", 17}, {"ESTRECHO", 17}, {"GORDO", 17}, {"DELGADO", 17},
    {"RAPIDO", 17}, {"LENTO", 17}, {"FUERTE", 17}, {"DEBIL", 17}, {"DURO", 17},
    {"BLANDO", 17}, {"CALIENTE", 17}, {"FRIO", 17}, {"TIBIO", 17}, {"FRESCO", 17},
    {"DULCE", 17}, {"SALADO", 17}, {"AMARGO", 17}, {"ACIDO", 17}, {"PICANTE", 17},

    // Fenómenos Naturales (18)
    {"TERREMOTO", 18}, {"TSUNAMI", 18}, {"INUNDACION", 18}, {"SEQUIA", 18}, {"INCENDIO", 18},
    {"AVALANCHA", 18}, {"ALUD", 18}, {"ERUPCION", 18}, {"ECLIPSE", 18}, {"AURORA", 18},
    {"METEORO", 18}, {"ESTRELLA", 18}, {"CONSTELACION", 18}, {"RELAMPAGO", 18}, {"CENTELLA", 18},

    // Matemáticas (19)
    {"NUMERO", 19}, {"SUMA", 19}, {"RESTA", 19}, {"MULTIPLICACION", 19}, {"DIVISION", 19},
    {"FRACCION", 19}, {"DECIMAL", 19}, {"PORCENTAJE", 19}, {"RAIZ", 19}, {"POTENCIA", 19},
    {"ECUACION", 19}, {"GEOMETRIA", 19}, {"ALGEBRA", 19}, {"CALCULO", 19}, {"ESTADISTICA", 19},
    {"TRIANGULO", 19}, {"CUADRADO", 19}, {"CIRCULO", 19}, {"RECTANGULO", 19}, {"ROMBO", 19},

    // Química (20)
    {"OXIGENO", 20}, {"HIDROGENO", 20}, {"CARBONO", 20}, {"NITROGENO", 20}, {"HELIO", 20},
    {"SODIO", 20}, {"CLORO", 20}, {"CALCIO", 20}, {"HIERRO", 20}, {"COBRE", 20},
    {"ORO", 20}, {"PLATA", 20}, {"PLATINO", 20}, {"URANIO", 20}, {"PLUTONIO", 20},

    // Cuerpo Humano (21)
    {"CABEZA", 21}, {"CUELLO", 21}, {"HOMBRO", 21}, {"BRAZO", 21}, {"CODO", 21},
    {"MANO", 21}, {"DEDO", 21}, {"PECHO", 21}, {"ESPALDA", 21},
    {"CINTURA", 21}, {"CADERA", 21}, {"PIERNA", 21}, {"RODILLA", 21}, {"TOBILLO", 21},
    {"PIE", 21}, {"CORAZON", 21}, {"PULMON", 21}, {"HIGADO", 21},
    {"CEREBRO", 21}, {"ESTOMAGO", 21}, {"INTESTINO", 21}, {"HUESO", 21}, {"MUSCULO", 21},

    // Tiempo (22)
    {"SEGUNDO", 22}, {"MINUTO", 22}, {"HORA", 22}, {"DIA", 22}, {"SEMANA", 22},
    {"MES", 22}, {"DECADA", 22}, {"SIGLO", 22}, {"MILENIO", 22},
    {"AYER", 22}, {"HOY", 22}, {"PASADO", 22}, {"FUTURO", 22},
    {"PRESENTE", 22}, {"AMANECER", 22}, {"MEDIODIA", 22}, {"ATARDECER", 22}, {"ANOCHECER", 22},

    // Palabras Cyberpunk (23)
    {"CIBERNETICO", 23}, {"DIGITAL", 23}, {"VIRTUAL", 23}, {"BINARIO", 23}, {"CODIGO", 23},
    {"DATOS", 23}, {"INFORMACION", 23}, {"SISTEMA", 23}, {"RED", 23}, {"CONEXION", 23},
    {"HACKER", 23}, {"FIREWALL", 23}, {"ENCRIPTACION", 23}, {"ALGORITMO", 23}, {"MATRIZ", 23},
    {"NEON", 23}, {"HOLOGRAM", 23}, {"ANDROID", 23}, {"CYBORG", 23}, {"ROBOT", 23}
};

const int total_palabras = sizeof(palabras) / sizeof(palabras[0]);

// Dibujos del ahorcado
const char *dibujo_ahorcado[] = {
    // 0 intentos
    "\n"
    "  +---+\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========\n",

    // 1 intento
    "\n"
    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========\n",

    // 2 intentos
    "\n"
    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "=========\n",

    // 3 intentos
    "\n"
    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|   |\n"
    "      |\n"
    "      |\n"
    "=========\n",

    // 4 intentos
    "\n"
    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    "      |\n"
    "      |\n"
    "=========\n",

    // 5 intentos
    "\n"
    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " /    |\n"
    "      |\n"
    "=========\n",

    // 6 intentos - Game Over
    "\n"
    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " / \\  |\n"
    "      |\n"
    "=========\n"
};

void limpiar_pantalla() {
    printf("\033[2J\033[H");
}

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrar_estado(const char *palabra, const char *adivinada, char *letras_usadas, int errores, int categoria) {
    limpiar_pantalla();

    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║          AHORCADO - NeonBitOS         ║\n");
    printf("╚═══════════════════════════════════════╝\n");

    printf("%s", dibujo_ahorcado[errores]);

    printf("\nCategoria: %s\n", nombres_categorias[categoria]);

    printf("\nPalabra: ");
    for (int i = 0; i < strlen(palabra); i++) {
        printf("%c ", adivinada[i]);
    }

    printf("\n\nLetras usadas: %s", letras_usadas);
    printf("\nIntentos restantes: %d/%d\n", MAX_INTENTOS - errores, MAX_INTENTOS);
}

int letra_ya_usada(char letra, char *letras_usadas) {
    for (int i = 0; i < strlen(letras_usadas); i++) {
        if (letras_usadas[i] == letra) {
            return 1;
        }
    }
    return 0;
}

void jugar() {
    // Seleccionar palabra aleatoria
    int indice = rand() % total_palabras;
    const char *palabra = palabras[indice].palabra;
    int categoria = palabras[indice].categoria;
    int longitud = strlen(palabra);

    // Estado de la palabra adivinada
    char adivinada[MAX_PALABRA];
    for (int i = 0; i < longitud; i++) {
        adivinada[i] = '_';
    }
    adivinada[longitud] = '\0';

    char letras_usadas[100] = "";
    int errores = 0;
    int letras_correctas = 0;

    while (errores < MAX_INTENTOS && letras_correctas < longitud) {
        mostrar_estado(palabra, adivinada, letras_usadas, errores, categoria);

        printf("\nIngresa una letra: ");
        char letra;
        if (scanf(" %c", &letra) != 1) {
            limpiar_buffer();
            continue;
        }
        limpiar_buffer();

        letra = toupper(letra);

        // Validar entrada
        if (!isalpha(letra)) {
            printf("\n¡Ingresa solo letras!");
            printf("\nPresiona Enter para continuar...");
            getchar();
            continue;
        }

        // Verificar si ya fue usada
        if (letra_ya_usada(letra, letras_usadas)) {
            printf("\n¡Ya usaste esa letra!");
            printf("\nPresiona Enter para continuar...");
            getchar();
            continue;
        }

        // Agregar a letras usadas
        int len = strlen(letras_usadas);
        letras_usadas[len] = letra;
        letras_usadas[len + 1] = ' ';
        letras_usadas[len + 2] = '\0';

        // Verificar si la letra está en la palabra
        int encontrada = 0;
        for (int i = 0; i < longitud; i++) {
            if (palabra[i] == letra) {
                adivinada[i] = letra;
                letras_correctas++;
                encontrada = 1;
            }
        }

        if (!encontrada) {
            errores++;
        }
    }

    // Mostrar resultado final
    mostrar_estado(palabra, adivinada, letras_usadas, errores, categoria);

    if (letras_correctas == longitud) {
        printf("\n¡GANASTE! ¡Felicitaciones!\n");
    } else {
        printf("\n¡PERDISTE! La palabra era: %s\n", palabra);
    }
}

void mostrar_ayuda() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║          AHORCADO - NeonBitOS         ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    printf("Cómo jugar:\n");
    printf("  - Adivina la palabra letra por letra\n");
    printf("  - Tienes %d intentos\n", MAX_INTENTOS);
    printf("  - Escribe una letra y presiona Enter\n");
    printf("  - La categoria te da una pista!\n");
    printf("  - ¡Intenta no ahorcar al muñeco!\n\n");
    printf("Base de datos: %d palabras en español\n", total_palabras);
    printf("Categorias: %d temas diferentes\n\n", MAX_CATEGORIAS);
}

int main(int argc, char *argv[]) {
    // Inicializar generador de números aleatorios
    srand(time(NULL));

    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        mostrar_ayuda();
        return 0;
    }

    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        jugar();

        printf("\n¿Jugar otra vez? (s/n): ");
        if (scanf(" %c", &continuar) != 1) {
            break;
        }
        limpiar_buffer();
    }

    printf("\n¡Gracias por jugar!\n\n");

    return 0;
}
