# Requisitos del proyecto

1) Instaláis MSYS2 (instalación limpia recomendable): https://www.msys2.org/

2) En MSYS2 instaláis las herramientas:

```shell
pacman -S mingw-w64-ucrt-x86_64-gcc \
          mingw-w64-ucrt-x86_64-make \
          mingw-w64-ucrt-x86_64-cmake \
          mingw-w64-ucrt-x86_64-ninja \
          mingw-w64-ucrt-x86_64-pkgconf

pacman -S mingw-w64-ucrt-x86_64-ntldd
```

4) Añadid estos directorios a las variables de entorno:

 - **PATH** ← C:\msys64\ucrt64\bin
 - **LIBRARY_PATH** ← C:\msys64\ucrt64\lib;C:\msys64\mingw64\lib

5) Reiniciar por si acaso.

6) En MSYS2 instaláis las bibliotecas:

```shell
pacman -S mingw-w64-ucrt-x86_64-SDL2 \
          mingw-w64-ucrt-x86_64-SDL2_ttf \
          mingw-w64-ucrt-x86_64-SDL2_image \
          mingw-w64-ucrt-x86_64-SDL2_mixer \
          mingw-w64-ucrt-x86_64-SDL2_sound

#Biblioteca de vídeo
pacman -S mingw-w64-ucrt-x86_64-ffmpeg
```

7) Instalad CMake Tools en VSCode si no lo tenéis.

8) Al abrir el proyecto os pedirá configurarlo, si no `Ctrl` + `shift` + `P`
   y buscar CMake Configure. Marcar gcc 13.2.

9) Compilar con el botón de abajo a la izquierda (`⚙️build`) y ejecutar con play
   o desde la terminal.

10) No debería decir nada de estas, pero si da fallo por ellas las instaláis

```shell
pacman  -S  mingw-w64-ucrt-x86_64-libpng \
            mingw-w64-ucrt-x86_64-libjxl \
            mingw-w64-ucrt-x86_64-libjpeg-turbo \
            mingw-w64-ucrt-x86_64-libtiff \
            mingw-w64-ucrt-x86_64-libavif \
            mingw-w64-ucrt-x86_64-libwebp \
            mingw-w64-ucrt-x86_64-mpg123 \
            mingw-w64-ucrt-x86_64-opusfile
```

11) Si se quiere exportar el proyecto compilar en modo Release, abrir este
    directorio desde la terminal de MSYS2 y ejecutar esto:

```shell
ldd bin/*|grep -iv system32|grep -vi windows|grep -v :$  | cut -f2 -d\> | cut -f1 -d\( | tr \\ / |while read a; do ! [ -e "bin/`basename $a`" ] && cp -v "$a" bin/; done
```

Esto llena el directorio bin de ficheros dll. No es necesario salvo para cuando
tengamos que hacer una entrega.

12) Podéis configurar VSCode para que use la terminal de MSYS2 añadiendo el fichero
    `.vscode/settings.json` y escribiendo esto en él:

```
{
    "terminal.integrated.profiles.windows": {
        "MSYS2": {
            "path": "C:\\msys64\\usr\\bin\\bash.exe",
            "args": [
            "--login",
            "-i"
            ],
            "env": {
            "MSYSTEM": "MINGW64",
            "CHERE_INVOKING": "1"
            }
        }
    }
}
```

**¡¡Cuidado!!** No uses esta terminal para introducir los comandos de git.

## En Ubuntu

```
sudo apt install gcc g++ make cmake ninja-build libc6-dev
./scripts/install_dependencies.sh
```

En principio no es necesario eliminar instalaciones previas de SDL2 que se
hayan hecho con el gestor de paquetes del sistema, pero si da algún problema
probad a eliminarlas.
