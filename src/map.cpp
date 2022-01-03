//
// Created by MoonMoon on 2021-12-17.
//

#include "map.h"


TileSet::TileSet(Model model) : material({0}), meshes(model.meshes), tileCount(model.meshCount) {
}

TileMap::TileMap(int columns, int rows, TileSet set) : tileSet(set),
                                                       chunks(std::vector<Chunk>(columns * rows)) {
}

void TileMap::Render() {
    for (Chunk &c: chunks) {
        c.Render(tileSet);
    }
}

void Chunk::Render(TileSet &set) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            DrawMesh(
                    set.meshes[tileInstances[j + i * 8]],
                    set.material,
                    MatrixTranslate((float) (i + coordinate.x * 8), 0.0f, (float) (8 - j + coordinate.z * 8))
            );
        }
    }
}

Chunk::Chunk() {}
