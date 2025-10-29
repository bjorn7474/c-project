#!/usr/bin/env bash
set -e
echo "🔨 Bygger programmet..."

gcc -nostartfiles /mingw64/lib/crt2.o main.c -o optioncalc.exe \
$(pkg-config --cflags --libs gtk+-3.0) -lmingw32 -lmingwex -lkernel32 -Wl,--subsystem,console

echo "📦 Skapar dist/ och samlar DLL:er..."
mkdir -p dist

ntldd optioncalc.exe \
  | grep mingw64 \
  | awk '{print $3}' \
  | sed 's#\\#/#g' \
  | xargs -I{} cp -u "{}" dist/

cp -u optioncalc.exe dist/

echo "✅ Klart! Starta programmet via ./dist/optioncalc.exe"
