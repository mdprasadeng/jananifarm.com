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

    sk.bonesCount = 13;
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
    sk.bones[index] = (Bone){.name = SPINE, .length = 130.0f};
    index++;
    sk.bones[index] = (Bone){.name = HIPS, .length = 45.0f};
    index++;
    sk.bones[index] = (Bone){.name = LEFT_UPPER_LEG, .length = 70.0f};
    index++;
    sk.bones[index] = (Bone){.name = LEFT_LOWER_LEG, .length = 100.0f};
    index++;
    sk.bones[index] = (Bone){.name = RIGHT_UPPER_LEG, .length = 70.0f};
    index++;
    sk.bones[index] = (Bone){.name = RIGHT_LOWER_LEG, .length = 100.0f};
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
        .joinAngle = 0.1f};
    index++;

    sk.joints[index] = (Joint){
        .boneA = NECK,
        .boneB = SHOULDER,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0.5f,
        .joinAngleType = ABSOLUTE,
        .joinAngle = 0,
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
        .joinAngle = PI / 2 + PI * 0.1,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = LEFT_UPPER_ARM,
        .boneB = LEFT_LOWER_ARM,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI * 0.5,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = SHOULDER,
        .boneB = RIGHT_UPPER_ARM,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI / 2 - PI * 0.1,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = RIGHT_UPPER_ARM,
        .boneB = RIGHT_LOWER_ARM,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = -PI * 0.5,
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
        .joinAngle = PI / 2 + PI * 0.06f,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = LEFT_UPPER_LEG,
        .boneB = LEFT_LOWER_LEG,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = -PI * 0.1f,
    };
    index++;

    sk.joints[index] = (Joint){
        .boneA = HIPS,
        .boneB = RIGHT_UPPER_LEG,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI / 2 - PI * 0.06f,
    };
    index++;
    sk.joints[index] = (Joint){
        .boneA = RIGHT_UPPER_LEG,
        .boneB = RIGHT_LOWER_LEG,
        .boneAJoinAt = 1,
        .boneBJoinAt = 0,
        .joinAngleType = RELATIVE,
        .joinAngle = PI * 0.1f,
    };
    index++;

    return sk;
}

void PlaceSkeleton(float x, float y, Skeleton sk)
{

    sk.bones[sk.startingBoneIndex].startsAt = (Vector2){.x = x, .y = y};
    sk.bones[sk.startingBoneIndex].rotatedBy = sk.startingBoneAngle;
    int bonesStack[100];
    int placedBones = 0;
    
    //push to stack
    bonesStack[placedBones] = sk.startingBoneIndex;
    placedBones++;
    
    while (placedBones != 0)
    {
        //pop from stack
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
                    .x = fromBone.startsAt.x + sk.joints[i].boneAJoinAt * fromBone.length * cosf(fromBone.rotatedBy),
                    .y = fromBone.startsAt.y + sk.joints[i].boneAJoinAt * fromBone.length * sinf(fromBone.rotatedBy),
                };
                sk.bones[toBoneIndex].startsAt = (Vector2){
                    .x = sk.joints[i].joinPoint.x - sk.joints[i].boneBJoinAt * sk.bones[toBoneIndex].length * cosf(angle),
                    .y = sk.joints[i].joinPoint.y - sk.joints[i].boneBJoinAt * sk.bones[toBoneIndex].length * sinf(angle),
                };
                sk.bones[toBoneIndex].rotatedBy = angle;
                
                //push to stack
                bonesStack[placedBones] = toBoneIndex;
                placedBones++;
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
    for (int i = 0; i < skeleton.jointsCount; i++)
    {
        DrawCircleLinesV(skeleton.joints[i].joinPoint, 10.0f, GRAY);
    }
    
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

    PlaceSkeleton(squareCenter.x, offY, skeleton);
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
