ml /c /coff %1.asm
link /subsystem:console /entry:start /out:%1.exe io.obj %1.obj kernel32.lib msvcrt.lib