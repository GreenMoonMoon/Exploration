#include <malloc.h>

#include "raylib.h"
#include "raymath.h"

#include "src/chunk.h"

#include "src/utilities/debug_draw.h"

void loadScene();

void unloadScene();

void DrawChunk();

Model terrainModel;
Material terrainMaterial;
Matrix *terrainTransform;

int main() {
    InitWindow(800, 600, "Exploration");

    Camera3D camera = {
            (Vector3) {4.0f, 8.0f, 0.0f},
            Vector3Zero(),
            (Vector3) {0.0f, 1.0f, 0.0f},
            70,
            CAMERA_PERSPECTIVE
    };
    SetCameraMode(camera, CAMERA_ORBITAL);

    loadScene();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //Update
        PollInputEvents();
        UpdateCamera(&camera);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(camera);
            {
                DrawGrid(64, 1.0f);

//                DrawMeshInstanced(
//                        terrainModel.meshes[0],
//                        terrainModel.materials[terrainModel.meshMaterial[0]],
//                        terrainTransform,
//                        1
//                );
            }
            EndMode3D();

            DebugDrawModelWithMeshIndex(terrainModel, camera, WHITE);

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    unloadScene();
    CloseWindow();
}


void loadScene() {
    terrainModel = LoadModel("C:/Users/josue/CLionProjects/Exploration/resources/models/terrain_models.glb");
    terrainMaterial = LoadMaterialDefault();
    terrainTransform = malloc(sizeof(Matrix) * 16);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            terrainTransform[(i * 4) + j] = MatrixTranslate((float)j, 0.0f, (float)i);
        };
    };
}

void unloadScene() {
    UnloadModel(terrainModel);
    free(terrainTransform);
}

void DrawChunk() {
    Matrix flat[16] = {
            MatrixTranslate(-2.0f, 0.0f, -2.0f), MatrixTranslate(-1.0f, 0.0f, -2.0f),
            MatrixTranslate(0.0f, 0.0f, -2.0f), MatrixTranslate(1.0f, 0.0f, -2.0f),
            MatrixTranslate(-2.0f, 0.0f, -1.0f), MatrixTranslate(-1.0f, 0.0f, -1.0f),
            MatrixTranslate(0.0f, 0.0f, -1.0f), MatrixTranslate(1.0f, 0.0f, -1.0f),
            MatrixTranslate(-2.0f, 0.0f, 0.0f), MatrixTranslate(-1.0f, 0.0f, 0.0f), MatrixTranslate(0.0f, 0.0f, 0.0f),
            MatrixTranslate(1.0f, 0.0f, 0.0f),
            MatrixTranslate(-2.0f, 0.0f, 1.0f), MatrixTranslate(-1.0f, 0.0f, 1.0f), MatrixTranslate(0.0f, 0.0f, 1.0f),
            MatrixTranslate(1.0f, 0.0f, 1.0f)
    };

    Matrix matrix = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1};
    DrawMeshInstanced(terrainModel.meshes[0], terrainModel.materials[0], &matrix, 1);
}