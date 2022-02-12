//
// Created by MoonMoon on 2022-01-30.
//
#include <filesystem>

#ifndef EXPLORATION_RESSOURCE_H
#define EXPLORATION_RESSOURCE_H


namespace Expl {
    struct Resource {
        virtual void Serialize(const std::filesystem::path &path) = 0;
        virtual void Deserialize(const std::filesystem::path &path) = 0;
    };

    class ResourceLoader {
        virtual void Load(const std::filesystem::path &path) = 0;
    };
}

#endif //EXPLORATION_RESSOURCE_H
