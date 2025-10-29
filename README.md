# 🧮 OptionCalc — GTK3-baserad optionskalkylator

**OptionCalc** är en grafisk kalkylator skriven i **C** som beräknar optioners teoretiska värde och greker med hjälp av **Black–Scholes-modellen**.  

Byggd med **GTK3**, fungerar både i **Windows (MSYS2/MinGW64)** och **Linux**.  
Designad för att vara **enkel, portabel och snabb**, med ett rent och lättanvänt GUI.

## ✨ Funktioner

- Beräkning av call- och put-optioner med Black–Scholes-formeln

- Visning av greker (delta, gamma, theta, vega, rho)

- GTK3-baserat, responsivt gränssnitt

- Makefile-baserad kompilering (MSYS2/MinGW64 och Linux)

- Minimal extern beroendestruktur

##  💻 Utvecklingsmiljö

Utvecklat och testat i Windows 10/11, MSYS2/MinGW64, GTK3 och Visual Studio (för redigering). Byggning sker via Makefile.

## 🧰 Installation och byggning (Windows / MSYS2)

- Installera MSYS2 från https://www.msys2.org

- Starta ett MSYS2 MinGW64-terminalfönster

- Installera verktyg och GTK3: pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtk3

- Klona projektet: git clone https://github.com/bjorn7474/c-project.git och gå in i katalogen: cd c-project

- Bygg: make

- Kör: ./dist/optioncalc.exe

## 🧰 Installation och byggning (Linux)

- Installera byggverktyg och GTK3: sudo apt install build-essential libgtk-3-dev

- Klona projektet: git clone https://github.com/bjorn7474/c-project.git och cd c-project

- Bygg: make

- Kör: ./optioncalc

## 📂 Projektstruktur
```
optioncalc/
├── gui.c / gui.h        → GTK3-gränssnitt (UI-logik)
├── calc.c / calc.h      → Black–Scholes-beräkningar och greker
├── resource.rc / .res   → Ikoner och resurser för Windows
├── Makefile             → Bygginstruktioner för gcc/make
├── dist/                → Färdig körbar fil och DLL:er (Windows)
├── .gitignore           → Filtrerar bort binärer och cache
└── README.md            → Projektdokumentation
```

## 🧮 Användning

1. **Starta programmet.**  
2. **Ange följande parametrar:**
   - **Underliggande tillgång (asset)**  
   - **Lösenpris (strike)**  
   - **Löptid (maturity)**  
   - **Riskfri ränta (interest)** – anges som decimal, t.ex. `0,03` för 3 %  
   - **Volatilitet (volatility)** – anges som decimal, t.ex. `0,30` för 30 %  
   - Använd **komma (`,`)** som decimalavgränsare.  
3. **Tryck på “Calculate”** för att visa optionens teoretiska värde och greker.


## :bulb: Tips

För distribution i Windows: zippa dist/ efter byggning (innehåller optioncalc.exe och nödvändiga GTK-DLL:er).
I Linux räcker den kompilerade binären ./optioncalc om GTK3 redan finns.

## ⚖️ Licens

Fritt att använda och modifiera för icke-kommersiellt bruk. För annan användning, kontakta författaren.

## &#x2709;&#xFE0F; Kontakt

bjornhallstrom74@gmail.com
