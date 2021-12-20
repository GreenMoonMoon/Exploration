#include <malloc.h>

#include "raylib.h"
#include "raymath.h"

#include "src/chunk.h"

#include "src/utilities/debug_draw.h"

void loadScene();

void unloadScene();

void DrawChunk();

Vector3 getInputs();

void MoveCamera(float deltaTime);

Model terrainModel;
Material terrainMaterial;
Matrix *terrainTransform;

Vector3 cameraTarget;

int main() {
    InitWindow(800, 600, "Exploration");

    Camera3D camera = {
            (Vector3) {4.0f, 8.0f, 0.0f},
            Vector3Zero(),
            (Vector3) {0.0f, 1.0f, 0.0f},
            70,
            CAMERA_PERSPECTIVE
    };
    SetCameraMode(camera, CAMERA_THIRD_PERSON);
    cameraTarget = Vector3Zero();

    loadScene();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //Update
        PollInputEvents();
        MoveCamera(GetFrameTime());

        camera.target = cameraTarget;
        UpdateCamera(&camera);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(camera);
            {
                DrawGrid(64, 1.0f);
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
            terrainTransform[(i * 4) + j] = MatrixTranslate((float) j, 0.0f, (float) i);
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

Vector3 getInputs() {
    return Vector3Normalize((Vector3) {
            (float) (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
            0.0f,
            (float) (IsKeyDown(KEY_S) - IsKeyDown(KEY_W))
    });
}

void MoveCamera(float deltaTime) {
    cameraTarget = Vector3Add(cameraTarget, Vector3Scale(getInputs(), deltaTime * 10.0f));
}