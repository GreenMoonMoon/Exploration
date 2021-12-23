//
// Created by MoonMoon on 2021-12-19.
//
#include "raylib.h"
#include "raymath.h"

#ifndef EXPLORATION_DEBUG_DRAW_H
#define EXPLORATION_DEBUG_DRAW_H

void DebugDrawTilesAndIndex(Model model, Camera camera, Color color) {
    BeginMode3D(camera);
    for (int i = 0; i < model.meshCount; i++) {
        Matrix m =  MatrixTranslate((float)i, 0.0f, 0.0f);
        DrawMesh(model.meshes[i], model.materials[model.meshMaterial[i]], m);
    }
    EndMode3D();
    for (int i = 0; i < model.meshCount; i++) {
        Vector2 pos = GetWorldToScreen((Vector3){(float)i + 0.5f, 0.1f, -0.5f}, camera);
        DrawText(TextFormat("%d", i), pos.x, pos.y, 20, color);
    }
}

#endif //EXPLORATION_DEBUG_DRAW_H
