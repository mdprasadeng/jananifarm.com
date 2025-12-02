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
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

typedef enum BoneName
{
    SKULL,
    NECK,
    SHOULDER,
    SPINE,
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
    float boneAJoinAt, boneBJoinAt;
    JoinAngleType joinAngleType;
    float joinAngle;
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

/*
head            2
neck            0.6
upperSpine      2.5
LowerSpine      2.5
UpperLeg        1.2
LowerLeg        1.2

*/

Skeleton generatePersonSkeleton()
{
    Skeleton sk = {};

    sk.startingBoneIndex = 0;
    sk.startingBoneAngle = PI / 2;

    sk.bonesCount = 13;
    sk.bones = RL_MALLOC(sk.bonesCount * sizeof(Bone));

    int index = 0;
    sk.bones[index] = (Bone){.name = SKULL, .length = 60.0f};
    index++;
    sk.bones[index] = (Bone){.name = NECK, .length = 20.0f};
    index++;
    sk.bones[index] = (Bone){.name = SHOULDER, .length = 60.0f};
    index++;
    sk.bones[index] = (Bone){.name = LEFT_UPPER_ARM, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = LEFT_LOWER_ARM, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = RIGHT_UPPER_ARM, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = RIGHT_LOWER_ARM, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = SPINE, .length = 120.0f};
    index++;
    sk.bones[index] = (Bone){.name = HIPS, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = LEFT_UPPER_LEG, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = LEFT_LOWER_LEG, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = RIGHT_UPPER_LEG, .length = 40.0f};
    index++;
    sk.bones[index] = (Bone){.name = RIGHT_LOWER_LEG, .length = 40.0f};
    index++;

    sk.jointsCount = 12;
    sk.joints = RL_MALLOC(sk.jointsCount * sizeof(Joint));

    index = 0;
    sk.joints[index] = (Joint){
        .boneA = SKULL,
        .boneB = NECK,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = 0};
    index++;

    sk.joints[index] = (Joint){
        .boneA = NECK,
        .boneB = SHOULDER,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0.5f,
        .joinAngleType = RELATIVE,
        .joinAngle = -PI / 2,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = SHOULDER,
        .boneB = SPINE,
        .boneAJoinAt = 0.5f,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI / 2,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = SHOULDER,
        .boneB = LEFT_UPPER_ARM,
        .boneAJoinAt = 0,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI / 2 + 0.2f,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = LEFT_UPPER_ARM,
        .boneB = LEFT_LOWER_ARM,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = -0.2f,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = SHOULDER,
        .boneB = RIGHT_UPPER_ARM,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI / 2,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = RIGHT_UPPER_ARM,
        .boneB = RIGHT_LOWER_ARM,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = 0,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = SPINE,
        .boneB = HIPS,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0.5f,
        .joinAngleType = RELATIVE,
        .joinAngle = -PI / 2,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = HIPS,
        .boneB = LEFT_UPPER_LEG,
        .boneAJoinAt = 0,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI / 2,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = LEFT_UPPER_LEG,
        .boneB = LEFT_LOWER_LEG,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = 0,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = HIPS,
        .boneB = RIGHT_UPPER_LEG,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI / 2,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = RIGHT_UPPER_LEG,
        .boneB = RIGHT_LOWER_LEG,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = 0,
    };
    index++;

    return sk;
}

void CalculateDrawOffsets(float x, float y, Skeleton skeleton)
{

    skeleton.bones[skeleton.startingBoneIndex].startsAt = (Vector2){.x = x, .y = y};
    skeleton.bones[skeleton.startingBoneIndex].rotatedBy = skeleton.startingBoneAngle;
    Bone bonesToWalk[100];
    int centeredBonesLength = 0;
    bonesToWalk[centeredBonesLength] = skeleton.bones[skeleton.startingBoneIndex];
    centeredBonesLength++;
    while (centeredBonesLength != 0)
    {
        Bone *workingBone = &bonesToWalk[centeredBonesLength - 1];
        centeredBonesLength--;

        TraceLog(LOG_INFO, "Walking bone of type %d", workingBone->name);
        for (int i = 0; i < skeleton.jointsCount; i++)
        {
            Joint joint = skeleton.joints[i];
            if (joint.boneA == workingBone->name)
            {
                Bone *boneB = NULL;
                for (int b = 0; b < skeleton.bonesCount; b++)
                {
                    if (skeleton.bones[b].name == joint.boneB)
                    {
                        boneB = &skeleton.bones[b];
                    }
                }
                
                float angle = joint.joinAngle;
                if (joint.joinAngleType == RELATIVE)
                {
                    angle += workingBone->rotatedBy;
                }
                Vector2 jointPoint = (Vector2){
                    .x = workingBone->startsAt.x + joint.boneAJoinAt * workingBone->length * cosf(workingBone->rotatedBy),
                    .y = workingBone->startsAt.y + joint.boneAJoinAt * workingBone->length * sinf(workingBone->rotatedBy),
                };
                boneB->startsAt = (Vector2){
                    .x = jointPoint.x - joint.boneBJoinAt * boneB->length * cosf(angle),
                    .y = jointPoint.y - joint.boneBJoinAt * boneB->length * sinf(angle),
                };
                boneB->rotatedBy = angle;
                bonesToWalk[centeredBonesLength] = *boneB;
                centeredBonesLength++;
            }
        }
    }
}

void DrawSkeleton(float x, float y, Skeleton skeleton)
{
    for (int i = 0; i < skeleton.bonesCount; i++)
    {
        Bone bone = skeleton.bones[i];
        DrawRectanglePro(
            (Rectangle){
                .x = bone.startsAt.x,
                .y = bone.startsAt.y,
                .height = 2.0f,
                .width = bone.length},
            (Vector2){
                .x = 0,
                .y = 0,
            },
            bone.rotatedBy * RAD2DEG,
            RED);
        
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
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

    CalculateDrawOffsets(squareCenter.x, offY, skeleton);
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i <= squareSize; i += squareUnit)
        {
            DrawLineEx((Vector2){offX, offY + i}, (Vector2){offX + squareSize, offY + i}, 1.0f + (i / squareUnit % 2 == 0 ? 1.5f : 0), LIGHTGRAY);
            DrawLineEx((Vector2){offX + i, offY}, (Vector2){offX + i, offY + squareSize}, 1.0f + (i / squareUnit % 2 == 0 ? 1.5f : 0), LIGHTGRAY);
        }

        DrawSkeleton(squareCenter.x, offY, skeleton);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
