###############################################################################
# 🧠 GTK3-projekt – OptionCalc
# Den här Makefilen kompilerar, rensar och paketerar ett GTK-baserat C-program.
# Den är anpassad för MSYS2/MINGW64 på Windows.
###############################################################################

# 🔧 Kompilatorn som ska användas
# Vi använder GCC (GNU Compiler Collection), standardkompilatorn i MSYS2.
CC = gcc

# 📦 Kompilatorflaggor (CFLAGS)
# $(shell ...) kör ett kommandot i shell och ersätter det med resultatet.
# Här frågar vi "pkg-config" efter vilka include-flaggor (-I) som GTK+ 3 kräver.
CFLAGS = $(shell pkg-config --cflags gtk+-3.0)

# 🔗 Länkningsflaggor (LIBS)
# Samma princip, men här hämtas alla bibliotek som måste länkas (-lgtk-3, -lgobject osv.)
LIBS = $(shell pkg-config --libs gtk+-3.0)

# 📄 Källfiler (alla .c-filer i projektet)
SRC = main.c calc.c gui.c

# 📦 Resursfil (för ikonen)
RES = resource.res

# 🎯 Namnet på den körbara filen
TARGET = dist/optioncalc.exe

###############################################################################
# 🧱 MÅL (Targets)
###############################################################################

# 🏁 "make" utan argument kommer att köra detta mål.
# Det betyder: bygg programmet.
all: $(TARGET)

# 🧩 Hur man bygger programmet
# $(TARGET) beror på (alltså byggs från) alla filer i $(SRC) och $(RES)
$(TARGET): $(SRC) $(RES)
	@echo "🔧 Kompilerar och länkar programmet..."
	$(CC) $(SRC) $(RES) -o $(TARGET) $(CFLAGS) $(LIBS) -mwindows
	@echo "✅ Färdig! $(TARGET) skapades."

###############################################################################
# 🎨 Ikon-kompilering
###############################################################################

# Om resource.res saknas, eller om resource.rc är nyare, bygg om den.
$(RES): resource.rc
	@echo "🎨 Bygger resursfil (ikon)..."
	windres resource.rc -O coff -o resource.res
	@echo "✅ Ikon inbäddad i resource.res"

###############################################################################
# 🧹 Rensningsmål
###############################################################################

# Kör: `make clean` för att ta bort körbara filer (börja om från noll)
clean:
	@echo "🧹 Rensar byggfiler..."
	rm -f $(TARGET) *.res
	@echo "✅ Rent!"

###############################################################################
# 📦 Deploy-mål
###############################################################################

# Kör: `make deploy`
# 1️⃣ Bygger programmet (via "all")
# 2️⃣ Skapar mappen "dist/"
# 3️⃣ Kopierar dit .exe-filen
# 4️⃣ Letar upp alla DLL:er programmet är beroende av (med ntldd)
# 5️⃣ Kopierar dessa DLL:er till "dist/"
deploy: all
	@echo "📦 Skapar distributabel version i dist/..."
	mkdir -p dist
	cp $(TARGET) dist/
	ntldd $(TARGET) |
