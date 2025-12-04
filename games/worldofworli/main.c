/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute 'raylib_compile_execute' script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
 *   Web version of the program is generated in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   Example originally created with raylib 1.0, last time updated with raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "./raygui.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

typedef enum BoneName
{
    SKULL,
    NECK,
    SHOULDER,
    UPPER_SPINE,
    LOWER_SPINE,
    HIPS,
    RIGHT_UPPER_ARM,
    RIGHT_LOWER_ARM,
    RIGHT_UPPER_LEG,
    RIGHT_LOWER_LEG,
    LEFT_UPPER_ARM,
    LEFT_LOWER_ARM,
    LEFT_UPPER_LEG,
    LEFT_LOWER_LEG,
} BoneName;

const char *const BoneNameStr[] =
    {
        [SKULL] = "Skull",
        [NECK] = "Neck",
        [SHOULDER] = "Shoulder",
        [UPPER_SPINE] = "Upper Spine",
        [LOWER_SPINE] = "Lower Spine",
        [HIPS] = "Hips",
        [RIGHT_UPPER_ARM] = "RUArm",
        [RIGHT_LOWER_ARM] = "RLArm",
        [RIGHT_UPPER_LEG] = "RULeg",
        [RIGHT_LOWER_LEG] = "RLLeg",
        [LEFT_UPPER_ARM] = "LUArm",
        [LEFT_LOWER_ARM] = "LLArm",
        [LEFT_UPPER_LEG] = "LULeg",
        [LEFT_LOWER_LEG] = "LLLeg"};

typedef struct Bone
{
    BoneName name;
    float length;
    Vector2 startsAt;
    float rotatedBy;
} Bone;

typedef enum JoinAngleType
{
    RELATIVE = 0,
    ABSOLUTE = 1
} JoinAngleType;

typedef struct Joint
{
    BoneName boneA, boneB;
    float boneAJoinAtX, boneAJoinAtY, boneBJoinAt;
    JoinAngleType joinAngleType;
    float joinAngle;
    Vector2 joinPoint;
} Joint;

typedef struct Skeleton
{
    Bone *bones;
    int bonesCount;

    Joint *joints;
    int jointsCount;

    int startingBoneIndex;
    float startingBoneAngle;
} Skeleton;

Skeleton generatePersonSkeleton()
{
    Skeleton sk = {};

    sk.startingBoneIndex = 0;
    sk.startingBoneAngle = PI / 2;

    // bones
    {
        sk.bonesCount = 14;
        sk.bones = RL_MALLOC(sk.bonesCount * sizeof(Bone));
        int index = 0;
        sk.bones[index] = (Bone){.name = SKULL, .length = 70.0f};
        index++;
        sk.bones[index] = (Bone){.name = NECK, .length = 30.0f};
        index++;
        sk.bones[index] = (Bone){.name = SHOULDER, .length = 100.0f};
        index++;
        sk.bones[index] = (Bone){.name = LEFT_UPPER_ARM, .length = 70.0f};
        index++;
        sk.bones[index] = (Bone){.name = LEFT_LOWER_ARM, .length = 80.0f};
        index++;
        sk.bones[index] = (Bone){.name = RIGHT_UPPER_ARM, .length = 70.0f};
        index++;
        sk.bones[index] = (Bone){.name = RIGHT_LOWER_ARM, .length = 80.0f};
        index++;
        sk.bones[index] = (Bone){.name = UPPER_SPINE, .length = 70.0f};
        index++;
        sk.bones[index] = (Bone){.name = LOWER_SPINE, .length = 70.0f};
        index++;
        sk.bones[index] = (Bone){.name = HIPS, .length = 75.0f};
        index++;
        sk.bones[index] = (Bone){.name = LEFT_UPPER_LEG, .length = 70.0f};
        index++;
        sk.bones[index] = (Bone){.name = LEFT_LOWER_LEG, .length = 100.0f};
        index++;
        sk.bones[index] = (Bone){.name = RIGHT_UPPER_LEG, .length = 70.0f};
        index++;
        sk.bones[index] = (Bone){.name = RIGHT_LOWER_LEG, .length = 100.0f};
        index++;
    }

    float normalizeTo = 1000.0f;
    float total = 400.0f;
    float normalizeFactor = normalizeTo / total;
    for (int i = 0; i < sk.bonesCount; i++)
    {
        sk.bones[i].length *= normalizeFactor;
    }

    // joints
    {
        sk.jointsCount = 13;
        sk.joints = RL_MALLOC(sk.jointsCount * sizeof(Joint));

        int index = 0;
        sk.joints[index] = (Joint){
            .boneA = SKULL,
            .boneB = NECK,
            .boneAJoinAtX = 0.9f,
            .boneBJoinAt = 0,
            .joinAngleType = ABSOLUTE,
            .joinAngle = PI * 0.5f};
        index++;

        sk.joints[index] = (Joint){
            .boneA = NECK,
            .boneB = SHOULDER,
            .boneAJoinAtX = 0.9f,
            .boneBJoinAt = 0.5f,
            .joinAngleType = ABSOLUTE,
            .joinAngle = 0,
        };
        index++;

        sk.joints[index] = (Joint){
            .boneA = SHOULDER,
            .boneB = UPPER_SPINE,
            .boneAJoinAtX = 0.5f,
            .boneBJoinAt = 0,
            .joinAngleType = ABSOLUTE,
            .joinAngle = PI / 2,
        };
        index++;

        sk.joints[index] = (Joint){
            .boneA = UPPER_SPINE,
            .boneB = LOWER_SPINE,
            .boneAJoinAtX = 1,
            .boneBJoinAt = 0,
            .joinAngleType = ABSOLUTE,
            .joinAngle = PI / 2,
        };
        index++;

        sk.joints[index] = (Joint){
            .boneA = SHOULDER,
            .boneB = LEFT_UPPER_ARM,
            .boneAJoinAtX = 0.01f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = PI / 2 + PI * 0.1,
        };
        index++;
        sk.joints[index] = (Joint){
            .boneA = LEFT_UPPER_ARM,
            .boneB = LEFT_LOWER_ARM,
            .boneAJoinAtX = 0.99f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = PI * 0.7,
        };
        index++;

        sk.joints[index] = (Joint){
            .boneA = SHOULDER,
            .boneB = RIGHT_UPPER_ARM,
            .boneAJoinAtX = 0.99f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = PI / 2 - PI * 0.1,
        };
        index++;
        sk.joints[index] = (Joint){
            .boneA = RIGHT_UPPER_ARM,
            .boneB = RIGHT_LOWER_ARM,
            .boneAJoinAtX = 0.99f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = -PI * 0.5,
        };
        index++;

        sk.joints[index] = (Joint){
            .boneA = LOWER_SPINE,
            .boneB = HIPS,
            .boneAJoinAtX = 1,
            .boneBJoinAt = 0.5f,
            .joinAngleType = ABSOLUTE,
            .joinAngle = 0,
        };
        index++;

        sk.joints[index] = (Joint){
            .boneA = HIPS,
            .boneB = LEFT_UPPER_LEG,
            .boneAJoinAtX = 0.25f,
            .boneAJoinAtY = 0.25f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = PI / 2 - PI * 0.06f,
        };
        index++;
        sk.joints[index] = (Joint){
            .boneA = LEFT_UPPER_LEG,
            .boneB = LEFT_LOWER_LEG,
            .boneAJoinAtX = 0.99f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = PI * 0.1f,
        };
        index++;

        sk.joints[index] = (Joint){
            .boneA = HIPS,
            .boneB = RIGHT_UPPER_LEG,
            .boneAJoinAtX = 0.75f,
            .boneAJoinAtY = 0.25f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = PI / 2 - PI * 0.06f,
        };
        index++;
        sk.joints[index] = (Joint){
            .boneA = RIGHT_UPPER_LEG,
            .boneB = RIGHT_LOWER_LEG,
            .boneAJoinAtX = 0.99f,
            .boneBJoinAt = 0,
            .joinAngleType = RELATIVE,
            .joinAngle = PI * 0.1f,
        };
        index++;
    }

    return sk;
}

void PlaceSkeleton(Skeleton sk)
{

    sk.bones[sk.startingBoneIndex].startsAt = (Vector2){.x = 0, .y = 0};
    sk.bones[sk.startingBoneIndex].rotatedBy = sk.startingBoneAngle;
    int bonesStack[100];
    int placedBones = 0;

    // push to stack
    bonesStack[placedBones] = sk.startingBoneIndex;
    placedBones++;

    while (placedBones != 0)
    {
        // pop from stack
        Bone fromBone = sk.bones[bonesStack[placedBones - 1]];
        placedBones--;

        for (int i = 0; i < sk.jointsCount; i++)
        {
            if (sk.joints[i].boneA == fromBone.name)
            {
                int toBoneIndex = -1;
                for (int b = 0; b < sk.bonesCount; b++)
                {
                    if (sk.bones[b].name == sk.joints[i].boneB)
                    {
                        toBoneIndex = b;
                    }
                }

                float angle = sk.joints[i].joinAngle;
                if (sk.joints[i].joinAngleType == RELATIVE)
                {
                    angle += fromBone.rotatedBy;
                }
                sk.joints[i].joinPoint = (Vector2){
                    .x = fromBone.startsAt.x + sk.joints[i].boneAJoinAtX * fromBone.length * cosf(fromBone.rotatedBy) + sk.joints[i].boneAJoinAtY * fromBone.length * sinf(fromBone.rotatedBy),
                    .y = fromBone.startsAt.y + sk.joints[i].boneAJoinAtX * fromBone.length * sinf(fromBone.rotatedBy) - sk.joints[i].boneAJoinAtY * fromBone.length * cosf(fromBone.rotatedBy),
                };
                sk.bones[toBoneIndex].startsAt = (Vector2){
                    .x = sk.joints[i].joinPoint.x - sk.joints[i].boneBJoinAt * sk.bones[toBoneIndex].length * cosf(angle),
                    .y = sk.joints[i].joinPoint.y - sk.joints[i].boneBJoinAt * sk.bones[toBoneIndex].length * sinf(angle),
                };
                sk.bones[toBoneIndex].rotatedBy = angle;

                // push to stack
                bonesStack[placedBones] = toBoneIndex;
                placedBones++;
            }
        }
    }
}

void DrawSkeleton(float x, float y, Skeleton skeleton, float scaleBy)
{
    for (int i = 0; i < skeleton.bonesCount; i++)
    {
        Bone bone = skeleton.bones[i];
        DrawRectanglePro(
            (Rectangle){
                .x = x + bone.startsAt.x * scaleBy,
                .y = y + bone.startsAt.y * scaleBy,
                .height = 2.0f,
                .width = bone.length * scaleBy},
            (Vector2){
                .x = 0,
                .y = 0,
            },
            bone.rotatedBy * RAD2DEG,
            WHITE);
    }
    for (int i = 0; i < skeleton.jointsCount; i++)
    {
        // DrawCircle(x + skeleton.joints[i].joinPoint.x * scaleBy, y + skeleton.joints[i].joinPoint.y * scaleBy, 20.0f * scaleBy, WHITE);
    }
}

bool lockLR = true;
void DrawSkeletonDebugMenu(float x, float y, Skeleton skeleton)
{
    for (int i = 0; i < skeleton.bonesCount; i++)
    {
        int changed = GuiSliderBar((Rectangle){.x = x, .y = y + i * 25, 120, 20}, BoneNameStr[skeleton.bones[i].name], TextFormat("%.0f", skeleton.bones[i].length), &skeleton.bones[i].length, 1, 400);
        if (changed && lockLR)
        {
            BoneName toChange = skeleton.bones[i].name;
            if (skeleton.bones[i].name == LEFT_UPPER_ARM)
            {
                toChange = RIGHT_UPPER_ARM;
            }
            if (skeleton.bones[i].name == LEFT_LOWER_ARM)
            {
                toChange = RIGHT_LOWER_ARM;
            }
            if (skeleton.bones[i].name == LEFT_UPPER_LEG)
            {
                toChange = RIGHT_UPPER_LEG;
            }
            if (skeleton.bones[i].name == LEFT_LOWER_LEG)
            {
                toChange = RIGHT_LOWER_LEG;
            }

            if (skeleton.bones[i].name == RIGHT_UPPER_ARM)
            {
                toChange = LEFT_UPPER_ARM;
            }
            if (skeleton.bones[i].name == RIGHT_LOWER_ARM)
            {
                toChange = LEFT_LOWER_ARM;
            }
            if (skeleton.bones[i].name == RIGHT_UPPER_LEG)
            {
                toChange = LEFT_UPPER_LEG;
            }
            if (skeleton.bones[i].name == RIGHT_LOWER_LEG)
            {
                toChange = LEFT_LOWER_LEG;
            }
            if (toChange != skeleton.bones[i].name)
            {
                for (int k = 0; k < skeleton.bonesCount; k++)
                {
                    if (skeleton.bones[k].name == toChange)
                    {
                        skeleton.bones[k].length = skeleton.bones[i].length;
                    }
                }
            }
        }
    }
    GuiCheckBox((Rectangle){.x = x, .y = y + skeleton.bonesCount * 25, 20, 20}, "Lock L&R", &lockLR);
}

void DrawSkin(float x, float y, Skeleton skeleton, float scaleBy)
{
    float lineThickness = 3;
    Bone shoulder, lowerSpine, hips;
    for (int i = 0; i < skeleton.bonesCount; i++)
    {
        Bone bone = skeleton.bones[i];
        if (bone.name == SKULL)
        {
            DrawCircle(
                x + bone.startsAt.x * scaleBy + bone.length * scaleBy * 0.5 * cos(bone.rotatedBy),
                y + bone.startsAt.y * scaleBy + bone.length * scaleBy * 0.5 * sin(bone.rotatedBy),
                bone.length * scaleBy * 0.5,
                WHITE);
        }
        else
        {
            if (
                bone.name == LEFT_UPPER_ARM ||
                bone.name == LEFT_LOWER_ARM ||
                bone.name == LEFT_UPPER_LEG ||
                bone.name == LEFT_LOWER_LEG ||
                bone.name == RIGHT_UPPER_ARM ||
                bone.name == RIGHT_LOWER_ARM ||
                bone.name == RIGHT_UPPER_LEG ||
                bone.name == RIGHT_LOWER_LEG ||
                bone.name == NECK)
            {
                DrawLineEx(
                    (Vector2){
                        .x = x + (bone.startsAt.x) * scaleBy,
                        .y = y + (bone.startsAt.y) * scaleBy,
                    },
                    (Vector2){
                        .x = x + bone.startsAt.x * scaleBy + (bone.length) * scaleBy * cos(bone.rotatedBy),
                        .y = y + bone.startsAt.y * scaleBy + (bone.length) * scaleBy * sin(bone.rotatedBy),
                    },
                    lineThickness,
                    WHITE);
            }
            if (bone.name == SHOULDER)
            {
                shoulder = bone;
            }
            if (bone.name == LOWER_SPINE)
            {
                lowerSpine = bone;
            }
            if (bone.name == HIPS)
            {
                hips = bone;
            }
        }
    }
    DrawTriangle(
        (Vector2){
            x + lowerSpine.startsAt.x * scaleBy,
            y + lowerSpine.startsAt.y * scaleBy,
        },
        (Vector2){
            .x = x + shoulder.startsAt.x * scaleBy + shoulder.length * cos(shoulder.rotatedBy) * scaleBy,
            .y = y + shoulder.startsAt.y * scaleBy + shoulder.length * sin(shoulder.rotatedBy) * scaleBy},
        (Vector2){
            x + shoulder.startsAt.x * scaleBy,
            y + shoulder.startsAt.y * scaleBy,
        },
        (Color){230, 41, 55, 55});
    DrawTriangle(
        (Vector2){
            x + lowerSpine.startsAt.x * scaleBy,
            y + lowerSpine.startsAt.y * scaleBy,
        },
        (Vector2){
            x + hips.startsAt.x * scaleBy,
            y + hips.startsAt.y * scaleBy,
        },
        (Vector2){
            .x = x + hips.startsAt.x * scaleBy + hips.length * cos(hips.rotatedBy) * scaleBy,
            .y = y + hips.startsAt.y * scaleBy + hips.length * sin(hips.rotatedBy) * scaleBy},

        (Color){230, 41, 55, 55});
}
int main(void)
{
    setbuf(stdout, NULL);
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int squareUnit = 20;
    const int squareSize = squareUnit * 20;
    const Vector2 squareCenter = {.x = screenWidth / 2, .y = screenHeight / 2};

    Skeleton skeleton = generatePersonSkeleton();

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTraceLogLevel(LOG_ALL);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    int offX = (screenWidth - squareSize) / 2;
    int offY = (screenHeight - squareSize) / 2;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(MAROON);

        // Draw Grid Lines
        {
            for (int i = 0; i <= squareSize; i += squareUnit)
            {
                DrawLineEx((Vector2){offX, offY + i}, (Vector2){offX + squareSize, offY + i}, 1.0f + (i / squareUnit % 2 == 0 ? 1.5f : 0), LIGHTGRAY);
                DrawLineEx((Vector2){offX + i, offY}, (Vector2){offX + i, offY + squareSize}, 1.0f + (i / squareUnit % 2 == 0 ? 1.5f : 0), LIGHTGRAY);
            }
        }

        //Draw GUI options
        {

        }
        PlaceSkeleton(skeleton);
        DrawSkeleton(squareCenter.x, offY, skeleton, 0.4f);
        DrawSkin(squareCenter.x, offY, skeleton, 0.4f);
        DrawSkeletonDebugMenu(squareCenter.x + squareUnit * 12, offY, skeleton);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
