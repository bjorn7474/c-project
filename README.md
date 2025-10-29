# OptionCalc — GTK3-baserad optionskalkylator

OptionCalc är en grafisk kalkylator skriven i C för beräkning av optioners teoretiska värde och greker (delta, gamma, theta, vega, rho). Applikationen använder GTK3 för gränssnittet och kan byggas i både Windows (MSYS2/MinGW64) och Linux. Syftet är en enkel, portabel lösning för Black–Scholes-beräkningar med ett lättanvänt GUI.

## Funktioner

Beräkning av call- och put-optioner med Black–Scholes-formeln

Visning av greker (delta, gamma, theta, vega, rho)

GTK3-baserat, responsivt gränssnitt

Makefile-baserad kompilering (MSYS2/MinGW64 och Linux)

Minimal extern beroendestruktur

## Utvecklingsmiljö

Utvecklat och testat i Windows 10/11, MSYS2/MinGW64, GTK3 och Visual Studio (för redigering). Byggning sker via Makefile.

## Installation och byggning (Windows / MSYS2)

Installera MSYS2 från https://www.msys2.org

Starta ett MSYS2 MinGW64-terminalfönster

Installera verktyg och GTK3: pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtk3

Klona projektet: git clone https://github.com/bjorn7474/c-project.git och gå in i katalogen: cd c-project

Bygg: make

Kör: ./dist/optioncalc.exe

## Installation och byggning (Linux)

Installera byggverktyg och GTK3: sudo apt install build-essential libgtk-3-dev

Klona projektet: git clone https://github.com/bjorn7474/c-project.git och cd c-project

Bygg: make

Kör: ./optioncalc

## Projektstruktur (översikt)

gui.c, gui.h – GTK3-gränssnitt

calc.c, calc.h – Black–Scholes- och grek-beräkningar

resource.rc, .res – resurser/ikoner (Windows)

Makefile – bygginstruktioner

dist/ – körbar fil och DLL:er efter bygg (Windows)

.gitignore

README.md

## 🧮 Användning

1. **Starta programmet.**  
2. **Ange följande parametrar:**
   - **Underliggande pris**  
   - **Lösenpris (strike)**  
   - **Löptid** (i år)  
   - **Riskfri ränta** – anges som decimal, t.ex. `0,03` för 3 %  
   - **Volatilitet** – anges som decimal, t.ex. `0,30` för 30 %  
   - Använd **komma (`,`)** som decimalavgränsare.  
3. **Tryck på “Calculate”** för att visa optionens teoretiska värde och greker.


## Tips

För distribution i Windows: zippa dist/ efter byggning (innehåller optioncalc.exe och nödvändiga GTK-DLL:er).
I Linux räcker den kompilerade binären ./optioncalc om GTK3 redan finns.

## Licens

Fritt att använda och modifiera för icke-kommersiellt bruk. För annan användning, kontakta författaren.

## Kontakt

bjornhallstrom74@gmail.com
