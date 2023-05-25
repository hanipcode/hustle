#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H
#include "map"
#include "string"

enum class ResourceId {
  ROOM_TILEMAP,
  CHARACTER,
};

class Resource {
  static Resource *instance;
  const static std::map<ResourceId, std::string> resourceMap;

public:
  static Resource *getInstance();
  const std::string get(ResourceId name);
};

#endif