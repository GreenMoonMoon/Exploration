#include <malloc.h>

#include "raylib.h"
#include "raymath.h"

#include "src/map.h"

#define RLIGHTS_IMPLEMENTATION
#include "src/rlights.h"

#include "src/utilities/debug_draw.h"

void loadScene();

void unloadScene();

Vector3 processInputs();

void MoveCamera(float deltaTime);

Model terrainModel;
Material terrainMaterial;
Matrix *terrainFlatTransform;

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

    //DEBUG
    Matrix *m = malloc(sizeof(Matrix));
    m[0] = MatrixIdentity();

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

            DebugDrawTilesAndIndex(terrainModel, camera, WHITE);

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    unloadScene();
    CloseWindow();
}


void loadScene() {
    terrainModel = LoadModel("C:/Users/josue/CLionProjects/Exploration/resources/models/terrain_models.glb");
    terrainFlatTransform = malloc(sizeof(Matrix) * 16);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            terrainFlatTransform[(i * 4) + j] = MatrixTranslate((float) j, 0.0f, (float) i);
        };
    };

    //Set terrain material
    Shader shader = LoadShader(
            TextFormat("C:/Users/josue/CLionProjects/Exploration/resources/shaders/base_lighting_instanced.vs"),
            TextFormat("C:/Users/josue/CLionProjects/Exploration/resources/shaders/lighting.fs")
    );

    // Get some shader loactions
    shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader, "instanceTransform");

    // Ambient light level
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]) {0.2f, 0.2f, 0.2f, 1.0f}, SHADER_UNIFORM_VEC4);

    CreateLight(LIGHT_DIRECTIONAL, (Vector3) {50.0f, 50.0f, 0.0f}, Vector3Zero(), WHITE, shader);

    // NOTE: We are assigning the intancing shader to material.shader
    // to be used on mesh drawing with DrawMeshInstanced()
    terrainMaterial = LoadMaterialDefault();
    terrainMaterial.shader = shader;
    terrainMaterial.maps[MATERIAL_MAP_DIFFUSE].color = RED;
}

void unloadScene() {
    UnloadModel(terrainModel);
    free(terrainFlatTransform);
}

Vector3 processInputs() {
    return Vector3Normalize((Vector3) {
            (float) (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
            0.0f,
            (float) (IsKeyDown(KEY_S) - IsKeyDown(KEY_W))
    });
}

void MoveCamera(float deltaTime) {
    cameraTarget = Vector3Add(cameraTarget, Vector3Scale(processInputs(), deltaTime * 10.0f));
}