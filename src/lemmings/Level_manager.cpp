#include "Level_manager.hpp"
// Incluir otros archivos necesarios

Level_Manager::Level_Manager()
{
  load_levels(); // Cargar la lista de niveles al inicializar
}

Level_Manager::~Level_Manager()
{
  // Limpieza si es necesario
}

void Level_Manager::load_levels()
{
  // Implementar la lógica para cargar las rutas de los archivos de niveles
  // Por ejemplo, podría leer desde un archivo de configuración o directorio específico
}

bool Level_Manager::load_level(int index)
{
  if (index < 0 || index >= level_paths.size())
  {
    return false; // Índice fuera de rango
  }
  current_level_index = index;
  // Aquí se cargaría el nivel especificado, incluyendo la inicialización de Lemmings, obstáculos, y objetivos
  return true;
}

void Level_Manager::next_level()
{
  if (current_level_index + 1 < level_paths.size())
  {
    load_level(current_level_index + 1);
  }
  // Manejar el caso de haber completado todos los niveles, si es necesario
}

void Level_Manager::restart_level()
{
  load_level(current_level_index); // Simplemente recargar el nivel actual
}

int Level_Manager::get_current_level_index() const
{
  return current_level_index;
}
