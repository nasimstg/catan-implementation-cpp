#include "./ResourceType.hpp"

std::ostream &ariel::operator<<(std::ostream &os, const ResourceType &resourceType) {
    switch (resourceType) {
    case ResourceType::WOOD:
        os << "WOOD";
        break;
    case ResourceType::BRICK:
        os << "BRICK";
        break;
    case ResourceType::WOOL:
        os << "WOOL";
        break;
    case ResourceType::OATS:
        os << "OATS";
        break;
    case ResourceType::IRON:
        os << "IRON";
        break;
    default:
        os << "UNKNOWN";
        break;
    }
    return os;
}