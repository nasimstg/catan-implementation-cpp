#ifndef RESOURCE_TYPE_HPP
#define RESOURCE_TYPE_HPP

#include <iostream>

namespace ariel {
enum class ResourceType {
    WOOD,
    BRICK,
    WOOL,
    OATS,
    IRON,
    NONE
};
std::ostream &operator<<(std::ostream &os, const ResourceType &resourceType);
} // namespace ariel
#endif