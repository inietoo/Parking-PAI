# 🅿️ Parking ASIX — Interfaz Web

Esta carpeta contiene la interfaz web visual del sistema de parking inteligente del proyecto PAI (ASIX). Es un dashboard en tiempo real que muestra el estado de disponibilidad de las plazas de aparcamiento distribuidas en 3 plantas.

---

## ¿Qué hace esta web?

Básicamente es un **mapa interactivo del parking** que se refresca automáticamente cada 2 segundos. Consulta una API REST que corre en el ESP32 (o servidor backend) y pinta en pantalla qué plazas están libres y cuáles ocupadas.

De un vistazo puedes ver:
- **Cuántas plazas hay en total** y cuántas están libres ahora mismo
- **Estado por zona** (Zona A / B / C, que corresponden a Planta 0 / 1 / 2)
- **Cada plaza individualmente**, representada como un slot que cambia de color verde (libre) a rojo (ocupado)
- **Indicador de conexión** con la API — si se cae, avisa con un banner y sigue mostrando los últimos datos válidos

---

## Estructura visual

```
┌─────────────────────────────────────────────────┐
│  🅿️  Parking ASIX         ● CONECTADO · API EN LÍNEA │
│                                                 │
│  Total: 30  Libres: 18  Zona A: 6  B: 7  C: 5  │
│                                                 │
│  ┌─ ZONA A — Planta 0 ──────────────────────┐  │
│  │  [1][2][3][4][5]..   ← fila superior      │  │
│  │  ----  circulación  ----                  │  │
│  │  [6][7][8][9][10]..  ← fila inferior      │  │
│  │                            ENTRADA ⟵ SALIDA│  │
│  └──────────────────────────────────────────┘  │
│                                                 │
│  ┌─ ZONA B — Planta 1 ──────────────────────┐  │
│  │  ...                                     │  │
│  └──────────────────────────────────────────┘  │
│                                                 │
│  ┌─ ZONA C — Planta 2 ──────────────────────┐  │
│  │  ...                                     │  │
│  └──────────────────────────────────────────┘  │
└─────────────────────────────────────────────────┘
```

Cada plaza tiene un pequeño círculo de color:
- 🟢 **Verde** → libre
- 🔴 **Rojo** → ocupada

Al pasar el ratón sobre cualquier plaza aparece un tooltip con su número y estado.

---

## Cómo funciona por dentro

1. **Al cargar la página**, hace una petición `GET` a `http://10.0.101.90:8080/api/parking`
2. La API devuelve un array JSON con todas las plazas, por ejemplo:
   ```json
   [
     { "id": 1, "zone": "A", "free": true },
     { "id": 2, "zone": "A", "free": false },
     ...
   ]
   ```
3. La web construye el DOM completo la primera vez (**full build**)
4. Cada 2 segundos vuelve a consultar la API y solo actualiza las plazas que han cambiado (**incremental update**), evitando re-renderizados completos innecesarios
5. Si la API no responde, muestra el banner de error pero mantiene visible el último estado conocido

---

## Tecnologías usadas

| Cosa | Para qué |
|---|---|
| HTML/CSS/JS puro | Sin frameworks, cero dependencias locales |
| [Outfit](https://fonts.google.com/specimen/Outfit) | Tipografía principal (cargada desde Google Fonts) |
| [JetBrains Mono](https://fonts.google.com/specimen/JetBrains+Mono) | Números y etiquetas monoespaciadas |
| `fetch()` + `setInterval` | Polling a la API cada 2 segundos |
| CSS custom properties | Sistema de tokens de color y espaciado |

No necesita ningún servidor para servir el HTML — puedes abrirlo directamente en el navegador, siempre que tengas acceso a la red donde corre la API (`10.0.101.90:8080`).

---

## Requisitos para que funcione

- Estar en la misma red que el servidor/ESP32 (o tener la IP accesible)
- Que la API esté corriendo en `http://10.0.101.90:8080` y respondiendo en `/api/parking`
- Un navegador moderno (Chrome, Firefox, Edge... cualquiera de los últimos 3 años)

---

## Archivos

```
html/
├── index.html   ← La interfaz completa (todo en un único archivo)
└── README.md    ← Este archivo
```

---

## Capturas de pantalla

> _Abre `index.html` con acceso a la red del parking para ver el dashboard en vivo._
