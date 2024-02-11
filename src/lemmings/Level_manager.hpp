#pragma once

#include <vector>
#include <string>
// Incluir otros archivos necesarios

class Level_Manager
{
private:
  int current_level_index = 0;          // Índice del nivel actual
  std::vector<std::string> level_paths; // Rutas a los archivos de definición de los niveles

public:
  Level_Manager();  // Constructor
  ~Level_Manager(); // Destructor

  void load_levels();                  // Cargar la lista de niveles desde un directorio o archivo de configuración
  bool load_level(int index);          // Cargar un nivel específico por índice
  void next_level();                   // Avanzar al siguiente nivel
  void restart_level();                // Reiniciar el nivel actual
  int get_current_level_index() const; // Obtener el índice del nivel actual
                                       // Otros métodos necesarios
};
