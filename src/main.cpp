#include <Arduino.h>
#include <LittleFS.h>

#define BORRAR_REGISTRO 0



void escribirArchivo(const char *ruta, const char *texto){
  Serial.printf("escribiendo en: %s\n", ruta);

  File archivo = LittleFS.open(ruta, "w");

  if(!archivo){
    Serial.println("archivo no se puede abrir");
    return;
  }

  if(archivo.print(texto)){
    Serial.println("archivo escribiendo");
  }else{
    Serial.println("error escribiendo");
  }

  archivo.close();
  
}

void leerArchivo(const char *ruta){
  Serial.printf("leer archivo en: %s\n", ruta);
  File archivo = LittleFS.open(ruta, "r");
  if(!archivo){
    Serial.println("archivo no se puede abrir");
    return;
  }
  Serial.print("contiene: ");
  while(archivo.available()){
    Serial.write(archivo.read());
  }
  Serial.println();
  archivo.close();
} 

void agregarArchivo(const char *ruta, const char *texto){
  Serial.printf("agregar en: %s\n", ruta);
  File archivo = LittleFS.open(ruta, "a");
  if(!archivo){
    Serial.println("archivo no se puede abrir");
    return;
  }

  if(archivo.print(texto)){
    Serial.println("agregrando texto");
  }else{
    Serial.println("error al agregar texto");
  }

  Serial.println();
  archivo.close();
}


void borrarArchivo(const char *ruta){
  Serial.printf("borrar archivo en: %s\n", ruta);
  if(LittleFS.remove(ruta)){
    Serial.println("archivo borrado");
    return;
  }else{
    Serial.println("error en borrar archivo");
  }
  
  
}

void setup() {
Serial.begin(115200);
Serial.println("iniciando comunicacion serial");





#if BORRAR_REGISTRO
  if(!LittleFS.begin(true)){
    Serial.println("error al formatear LittleFS");
    return;
  }
  if(!LittleFS.format()){
    Serial.println("error al formatear");
    return;
  }
  else{
    Serial.println("memoria formateada");
  }
#else
  if(!LittleFS.begin()){
    Serial.println("error al iniciar LittleFS");
    return;
  }

#endif

Serial.println("demo de LittleFS");

escribirArchivo("/mensaje.txt", "hola mundo");
agregarArchivo("/mensaje.txt", "hola como estas");
leerArchivo("/mensaje.txt");
borrarArchivo("/mensaje.txt");
leerArchivo("/mensaje.txt");


LittleFS.end();
  
}

void loop() {
}