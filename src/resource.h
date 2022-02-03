//
// Created by MoonMoon on 2022-01-30.
//

#ifndef EXPLORATION_RESSOURCE_H
#define EXPLORATION_RESSOURCE_H


namespace Expl {
    struct Resource {
        const char* path = nullptr;

        virtual void Serialize() = 0;
        virtual void Deserialize() = 0;
    };
}

#endif //EXPLORATION_RESSOURCE_H
