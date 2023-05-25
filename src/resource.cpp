#include "resource.h"
#include "map"

const std::map<ResourceId, std::string> Resource::resourceMap = {
    {ResourceId::ROOM_TILEMAP, "room_tilemap.json"},
    {ResourceId::CHARACTER, "character.png"},
};
Resource *Resource::instance = nullptr;

Resource *Resource::getInstance() {
  if (instance == nullptr) {
    instance = new Resource();
  }
  return instance;
}

const std::string Resource::get(ResourceId name) {
  return "resources/" + resourceMap.at(name);
}