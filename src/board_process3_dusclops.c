#include "global.h"
#include "functions.h"
#include "m4a.h"
#include "main.h"
#include "constants/bg_music.h"
#include "constants/dusclops_states.h"

#define BONUS_DUSKULL_TIME 7200 //2 minutes, 60FPS
#define BONUS_DUSKULL_COMPLETE_POINTS 30000000

#define DUSKULL_NEEDED_TO_PHASE_TRANSFER 20
#define DUSKULL_CONCURRENT_MAX 3
#define DUSKULL_ALLOWED_TO_SPAWN DUSKULL_NEEDED_TO_PHASE_TRANSFER - DUSKULL_CONCURRENT_MAX + 1
#define DUSCLOPS_HITS_NEEDED_TO_SUCCEED 5

extern struct SongHeader se_duskull_appear;
extern s16 DuskullFramesetData[][3];



void DuskullBonus_Setup(void)
{
    s16 i;
    gCurrentPinballGame->unk18 = 0;
    gCurrentPinballGame->unk17 = 0;
    gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_0_INTRO;
    gCurrentPinballGame->unk294 = 1;
    gCurrentPinballGame->eventTimer = gCurrentPinballGame->timerBonus + BONUS_DUSKULL_TIME;
    gCurrentPinballGame->timerBonus = 0;
    gCurrentPinballGame->unk383 = 0;
    gCurrentPinballGame->unk388 = 3;
    gCurrentPinballGame->ball->unk0 = 1;
    gCurrentPinballGame->bonusModeHitCount = 0;
    gCurrentPinballGame->returnToMainBoardFlag = 0;
    gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_NONE;
    gCurrentPinballGame->unk392 = 0;
    gCurrentPinballGame->unk394 = 0;
    gCurrentPinballGame->minionActiveCount = 0;

    for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
    {
        gCurrentPinballGame->minionSpriteVariant[i] = 0;
        gCurrentPinballGame->minionNextSpriteVariant[i] = 0;
        gCurrentPinballGame->minionOamIx[i] = 0;
        gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_SPAWN;
        gCurrentPinballGame->minionFramesetIx[i] = 0;
        gCurrentPinballGame->minionDrawInFrame[i] = FALSE;
        gCurrentPinballGame->minionCanCollide[i] = FALSE;
        gCurrentPinballGame->minionDeathTimer[i] = 0;
        gCurrentPinballGame->minionStateTimer[i] = 0;
        gCurrentPinballGame->minionTimeAlive[i] = 0;
        gCurrentPinballGame->minionEscapeAtTime[i] = 0;
        gCurrentPinballGame->minionLogicPosition[i].x = 0;
        gCurrentPinballGame->minionLogicPosition[i].y = 0;
        gCurrentPinballGame->minionCollisionPosition[i].x = 0;
        gCurrentPinballGame->minionCollisionPosition[i].y = 0;
    }

    gCurrentPinballGame->unk3DC = 0;
    gCurrentPinballGame->unk3DE = 0;
    gCurrentPinballGame->unk3DF = 0;
    gCurrentPinballGame->unk3E0 = 0;
    gCurrentPinballGame->unk3E2 = 0;
    gCurrentPinballGame->unk3E4 = 0;
    gCurrentPinballGame->unk3E6 = 0;
    gCurrentPinballGame->unk3E8 = 0;
    gCurrentPinballGame->unk3EA = 0;
    gCurrentPinballGame->unk3EC = 0;
    gCurrentPinballGame->unk3EE = 0;
    gCurrentPinballGame->unk3F0 = 0;
    gCurrentPinballGame->unk3F2 = 0;
    gCurrentPinballGame->unk1A = 0;

    DuskullPhase_ProcessEntityLogic();
    DuskullPhase_ProcessGraphics();

    m4aSongNumStart(MUS_BONUS_FIELD_DUSKULL);

    DmaCopy16(3, (void *)gUnknown_081B36A4, (void *)0x05000320, 32);
}

void DusclopsBoardProcess_3B_33130(void)
{
    s16 temp;
    switch (gCurrentPinballGame->unk13)
    {
        case DUSCLOPS_BOARD_STATE_0_INTRO:
            gCurrentPinballGame->unk5F7 = 1;
            if (gCurrentPinballGame->unk18 < 120)
            {
                temp = gCurrentPinballGame->unk18 / 24;
                DmaCopy16(3, gUnknown_082EE0E0 + temp * 40, 0x05000000, 160);

                gCurrentPinballGame->unkE6 = gCurrentPinballGame->unk18 / 5 + 0xFFE8;
                gCurrentPinballGame->unk18++;
            }
            else
            {
                gCurrentPinballGame->unkE6 = 0;
                gMain.spriteGroups[7].available = TRUE;
                gMain.spriteGroups[8].available = TRUE;
                gMain.spriteGroups[9].available = TRUE;
                gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_1_DUSKULL_PHASE;
                gCurrentPinballGame->unk18 = 0;
            }

            break;
        case DUSCLOPS_BOARD_STATE_1_DUSKULL_PHASE:
            if (!gCurrentPinballGame->returnToMainBoardFlag)
            {
                gMain.blendControl = 0x1C10;
                gMain.blendAlpha = 0x30D;
            }
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_DUSKULL;
            DuskullPhase_ProcessEntityLogic();
            DuskullPhase_ProcessGraphics();
            break;
        case DUSCLOPS_BOARD_STATE_2_INIT_DUSCLOPS_PHASE:
            gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_3_DUSCLOPS_PHASE;
            gMain.spriteGroups[13].available = TRUE;
            gMain.spriteGroups[14].available = TRUE;
            gMain.spriteGroups[12].available = TRUE;
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_NONE;
            gCurrentPinballGame->bonusModeHitCount = 0;
            m4aSongNumStart(MUS_BONUS_FIELD_DUSCLOPS);
            break;
        case DUSCLOPS_BOARD_STATE_3_DUSCLOPS_PHASE:
            if (!gCurrentPinballGame->returnToMainBoardFlag)
            {
                gMain.blendControl = 0x1C10;
                gMain.blendAlpha = 0x1000;
            }
            DusclopsPhase_ProcessEntityLogicAndGraphics();
            break;
        case DUSCLOPS_BOARD_STATE_4_INIT_SCORE_PHASE:
            if (gCurrentPinballGame->unk18 < 120)
            {
                gCurrentPinballGame->unk18++;
            }
            else
            {
                gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_SCORE_PHASE;
                gCurrentPinballGame->unk18 = 0;
                gMain.spriteGroups[6].available = TRUE;
                gMain.spriteGroups[5].available = TRUE;
                DmaCopy16(3, gDusclopsBonusClear_Gfx, OBJ_VRAM1+0x1800, 8192);
                gCurrentPinballGame->unk394 = 136;
            }
            break;
        case DUSCLOPS_BOARD_STATE_SCORE_PHASE:
            ProceessBonusBannerAndScoring();
            if (gCurrentPinballGame->scoreCounterAnimationEnabled)
            {
                gCurrentPinballGame->unk18 = 181;
            }
            if (gCurrentPinballGame->unk18 == 180)
            {
                gCurrentPinballGame->scoreCounterAnimationEnabled = TRUE;
                gCurrentPinballGame->scoreAddStepSize = 400000;
                gCurrentPinballGame->scoreAddedInFrame = BONUS_DUSKULL_COMPLETE_POINTS;
            }
            if (gCurrentPinballGame->unk18 < 240)
            {
                if (gCurrentPinballGame->unk18 == 20)
                {
                    m4aMPlayAllStop();
                    m4aSongNumStart(MUS_SUCCESS3);
                }
                gCurrentPinballGame->unk18++;
            }
            else
            {
                gCurrentPinballGame->unk18 = 0;
                gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_SCORE_COUNTING_FINISHED;
                gCurrentPinballGame->numCompletedBonusStages++;
            }

            break;
        case DUSCLOPS_BOARD_STATE_SCORE_COUNTING_FINISHED:
            ProceessBonusBannerAndScoring();
            gCurrentPinballGame->returnToMainBoardFlag = 1;
            break;
    }

    if (gCurrentPinballGame->unk294)
    {
        if (gCurrentPinballGame->eventTimer < 2)
        {
            if (!gMain.modeChangeFlags)
            {
                m4aMPlayAllStop();
                m4aSongNumStart(MUS_END_OF_BALL3);
                gMain.modeChangeFlags |= MODE_CHANGE_EXPIRED_BONUS;
            }
        }
    }

    if (gCurrentPinballGame->returnToMainBoardFlag)
        FadeToMainBoard();

    BonusStage_HandleModeChangeFlags();
}

void SwapDuskullEntityIndex(s16 index1, s16 index2)
{
    u8 tempSpriteVariant, tempNextSpriteVariant, tempOamIx, tempState, tempFramesetIx, tempDrawInFrame, tempCanCollide, tempDeathTimer;
    u16 tempStateTimer, tempTimeAlive, tempEscapeAtTime;
    struct Vector16 tempLogicPosition, tempCollisionPosition;

    tempSpriteVariant = gCurrentPinballGame->minionSpriteVariant[index1];
    tempNextSpriteVariant = gCurrentPinballGame->minionNextSpriteVariant[index1];
    tempOamIx = gCurrentPinballGame->minionOamIx[index1];
    tempState = gCurrentPinballGame->minionState[index1];
    tempFramesetIx = gCurrentPinballGame->minionFramesetIx[index1];
    tempDrawInFrame = gCurrentPinballGame->minionDrawInFrame[index1];
    tempCanCollide = gCurrentPinballGame->minionCanCollide[index1];
    tempDeathTimer = gCurrentPinballGame->minionDeathTimer[index1];
    tempStateTimer = gCurrentPinballGame->minionStateTimer[index1];
    tempTimeAlive = gCurrentPinballGame->minionTimeAlive[index1];
    tempEscapeAtTime = gCurrentPinballGame->minionEscapeAtTime[index1];
    tempLogicPosition.x = gCurrentPinballGame->minionLogicPosition[index1].x;
    tempLogicPosition.y = gCurrentPinballGame->minionLogicPosition[index1].y;
    tempCollisionPosition.x = gCurrentPinballGame->minionCollisionPosition[index1].x;
    tempCollisionPosition.y = gCurrentPinballGame->minionCollisionPosition[index1].y;

    gCurrentPinballGame->minionSpriteVariant[index1] = gCurrentPinballGame->minionSpriteVariant[index2];
    gCurrentPinballGame->minionNextSpriteVariant[index1] = gCurrentPinballGame->minionNextSpriteVariant[index2];
    gCurrentPinballGame->minionOamIx[index1] = gCurrentPinballGame->minionOamIx[index2];
    gCurrentPinballGame->minionState[index1] = gCurrentPinballGame->minionState[index2];
    gCurrentPinballGame->minionFramesetIx[index1] = gCurrentPinballGame->minionFramesetIx[index2];
    gCurrentPinballGame->minionDrawInFrame[index1] = gCurrentPinballGame->minionDrawInFrame[index2];
    gCurrentPinballGame->minionCanCollide[index1] = gCurrentPinballGame->minionCanCollide[index2];
    gCurrentPinballGame->minionDeathTimer[index1] = gCurrentPinballGame->minionDeathTimer[index2];
    gCurrentPinballGame->minionStateTimer[index1] = gCurrentPinballGame->minionStateTimer[index2];
    gCurrentPinballGame->minionTimeAlive[index1] = gCurrentPinballGame->minionTimeAlive[index2];
    gCurrentPinballGame->minionEscapeAtTime[index1] = gCurrentPinballGame->minionEscapeAtTime[index2];
    gCurrentPinballGame->minionLogicPosition[index1].x = gCurrentPinballGame->minionLogicPosition[index2].x;
    gCurrentPinballGame->minionLogicPosition[index1].y = gCurrentPinballGame->minionLogicPosition[index2].y;
    gCurrentPinballGame->minionCollisionPosition[index1].x = gCurrentPinballGame->minionCollisionPosition[index2].x;
    gCurrentPinballGame->minionCollisionPosition[index1].y = gCurrentPinballGame->minionCollisionPosition[index2].y;

    gCurrentPinballGame->minionSpriteVariant[index2] = tempSpriteVariant;
    gCurrentPinballGame->minionNextSpriteVariant[index2] = tempNextSpriteVariant;
    gCurrentPinballGame->minionOamIx[index2] = tempOamIx;
    gCurrentPinballGame->minionState[index2] = tempState;
    gCurrentPinballGame->minionFramesetIx[index2] = tempFramesetIx;
    gCurrentPinballGame->minionDrawInFrame[index2] = tempDrawInFrame;
    gCurrentPinballGame->minionCanCollide[index2] = tempCanCollide;
    gCurrentPinballGame->minionDeathTimer[index2] = tempDeathTimer;
    gCurrentPinballGame->minionStateTimer[index2] = tempStateTimer;
    gCurrentPinballGame->minionTimeAlive[index2] = tempTimeAlive;
    gCurrentPinballGame->minionEscapeAtTime[index2] = tempEscapeAtTime;
    gCurrentPinballGame->minionLogicPosition[index2].x = tempLogicPosition.x;
    gCurrentPinballGame->minionLogicPosition[index2].y = tempLogicPosition.y;
    gCurrentPinballGame->minionCollisionPosition[index2].x = tempCollisionPosition.x;
    gCurrentPinballGame->minionCollisionPosition[index2].y = tempCollisionPosition.y;
}

void DuskullPhase_ProcessEntityLogic(void) {
    s16 i, j;
    bool32 r4 = TRUE;
    u16 oamIx = 0;
    u16 tileOffset = 0;

    // If target number of Duskulls spawned, check to see if all are removed before moving to next state
    if (gCurrentPinballGame->bonusModeHitCount > DUSKULL_ALLOWED_TO_SPAWN)
    {
        for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
        {
            if (gCurrentPinballGame->minionDrawInFrame[i])
                r4 = FALSE;
        }
        if (r4)
        {
            gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_2_INIT_DUSCLOPS_PHASE;
            gMain.spriteGroups[7].available = FALSE;
            gMain.spriteGroups[8].available = FALSE;
            gMain.spriteGroups[9].available = FALSE;
        }
    }

    for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
    {
        switch(gCurrentPinballGame->minionState[i])
        {
        case DUSKULL_ENTITY_STATE_SPAWN:
            if (gCurrentPinballGame->bonusModeHitCount <= DUSKULL_ALLOWED_TO_SPAWN && 
                gCurrentPinballGame->minionActiveCount < 2)
            {
                gCurrentPinballGame->minionActiveCount++;
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_APPEARS; 
                gCurrentPinballGame->minionFramesetIx[i] = 0;
                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->minionLogicPosition[i].x = (Random() % 1400) - 700;
                gCurrentPinballGame->minionLogicPosition[i].y = (Random() % 9) * 80;
                gCurrentPinballGame->minionEscapeAtTime[i] = (Random() % 1000) + 200;
                gCurrentPinballGame->minionDrawInFrame[i] = FALSE;
                gCurrentPinballGame->minionCanCollide[i] = FALSE;
                oamIx = 4;
                tileOffset = DUSKULL_TILE_OFFSET_FACE_FORWARD; // Facing forward picture
                gCurrentPinballGame->minionTimeAlive[i] = 0;
                MPlayStart(&gMPlayInfo_SE1, &se_duskull_appear);

                //Check/swap Y index ordering, for proper sprite draw layering
                for (j = DUSKULL_CONCURRENT_MAX - 1; j > 0; j--)
                {
                    if (gCurrentPinballGame->minionLogicPosition[j].y > gCurrentPinballGame->minionLogicPosition[j-1].y)
                    {
                        SwapDuskullEntityIndex(j, j - 1);
                        j = DUSKULL_CONCURRENT_MAX;
                    }
                }
            }
            else
            {
                gCurrentPinballGame->minionLogicPosition[i].x = 0;
                gCurrentPinballGame->minionLogicPosition[i].y = 120;
                gCurrentPinballGame->minionDrawInFrame[i] = FALSE;
                Random();
            }
            break;
        case DUSKULL_ENTITY_STATE_APPEARS: //Spawn in, Wait and initial movement decision
            if (gCurrentPinballGame->minionStateTimer[i] < 20)
            {
                gCurrentPinballGame->minionStateTimer[i]++;
                // Minion 'Blinking' by alternating whether drawn in frame, or off screen
                gCurrentPinballGame->minionDrawInFrame[i] = (gCurrentPinballGame->minionStateTimer[i] % 4) / 2;
                oamIx = 4;
                tileOffset = DUSKULL_TILE_OFFSET_FACE_FORWARD;
                break;
            }
            else
            {
                if (gMain.systemFrameCount % 2)
                {
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_LEFT;
                    gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_MOVE_LEFT_START;
                }
                else
                {
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_RIGHT;
                    gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_MOVE_RIGHT_START;
                }

                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->minionDrawInFrame[i] = TRUE;
                gCurrentPinballGame->minionCanCollide[i] = TRUE;
                oamIx = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
                tileOffset = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            }
            break;
        case DUSKULL_ENTITY_STATE_MOVE_LEFT:
            gCurrentPinballGame->minionTimeAlive[i]++;
            if (gCurrentPinballGame->minionLogicPosition[i].x > -800)
            {
                gCurrentPinballGame->minionLogicPosition[i].x -= 3; //Move left
                if (DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++;
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0;
                    gCurrentPinballGame->minionFramesetIx[i]++;

                    //Animation frame reset
                    if (gCurrentPinballGame->minionFramesetIx[i] > DUSKULL_FRAME_MOVE_LEFT_END)
                        gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_MOVE_LEFT_START;
                }
            }
            else
            {
                if (DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++;
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0;
                    gCurrentPinballGame->minionFramesetIx[i]++;

                    //Animation frame at neutral forward, continue with move right
                    if (gCurrentPinballGame->minionFramesetIx[i] > DUSKULL_FRAME_NEUTRAL_FACING)
                    {
                        gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_MOVE_RIGHT_START;
                        gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_RIGHT;
                    }
                }
            }
            oamIx = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_MOVE_RIGHT:
            gCurrentPinballGame->minionTimeAlive[i]++;
            if (gCurrentPinballGame->minionLogicPosition[i].x < 800)
            {
                gCurrentPinballGame->minionLogicPosition[i].x += 3; //Move right
                gCurrentPinballGame->minionLogicPosition[i].y += 0; // ! Dead code needed for matching
                if (DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++;
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0;
                    gCurrentPinballGame->minionFramesetIx[i]++;
                    if (gCurrentPinballGame->minionFramesetIx[i] > DUSKULL_FRAME_MOVE_RIGHT_END)
                        gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_MOVE_RIGHT_START;
                }
            }
            else
            {
                if (DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++;
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0;
                    gCurrentPinballGame->minionFramesetIx[i]++;
                    if (gCurrentPinballGame->minionFramesetIx[i] > DUSKULL_FRAME_TURN_TO_FACE_LEFT_END)
                    {
                        gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_MOVE_LEFT_START;
                        gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_LEFT;
                    }
                }
            }
            oamIx = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_HIT:
            oamIx = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_HIT;
            gCurrentPinballGame->minionStateTimer[i] = 0;
            gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_DYING;
            gCurrentPinballGame->minionDeathTimer[i] = 0;
            gCurrentPinballGame->minionCanCollide[i] = FALSE;

            if (gCurrentPinballGame->minionActiveCount > 0)
                gCurrentPinballGame->minionActiveCount--; //Number of active duskull
            gCurrentPinballGame->scoreAddedInFrame = 100000;
            gCurrentPinballGame->bonusModeHitCount++; // Number hit
            m4aSongNumStart(SE_DUSKULL_DEATH_CRY); //Duskull Death cry
            PlayRumble(7);
            break;
        case DUSKULL_ENTITY_STATE_DYING:
            if (DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
            {
                gCurrentPinballGame->minionStateTimer[i]++;
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->minionFramesetIx[i]++;
                if (gCurrentPinballGame->minionFramesetIx[i] > DUSKULL_FRAME_DYING)
                {
                    gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_DYING;
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_CLEANUP;
                    gCurrentPinballGame->minionDrawInFrame[i] = FALSE;
                }
            }
            if (gCurrentPinballGame->minionFramesetIx[i] == DUSKULL_FRAME_DYING)
                gCurrentPinballGame->minionDeathTimer[i]++;
            oamIx = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_LEFT:
            if (gCurrentPinballGame->minionStateTimer[i] < 6)
            {
                gCurrentPinballGame->minionStateTimer[i]++;
                oamIx = 3;
                tileOffset = DUSKULL_TILE_OFFSET_QUARTER_FACING;
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_ESCAPE_PREP;
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE;
                gCurrentPinballGame->minionCanCollide[i] = FALSE;
                if (gCurrentPinballGame->minionActiveCount > 0)
                    gCurrentPinballGame->minionActiveCount--;
                oamIx = 3;
                tileOffset = DUSKULL_TILE_OFFSET_QUARTER_FACING;
                m4aSongNumStart(SE_DUSCLOPS_DEPART_INCOMPLETE);
            }
            break;
        case DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_RIGHT:
            if (gCurrentPinballGame->minionStateTimer[i] < 6)
            {
                gCurrentPinballGame->minionStateTimer[i]++;
                oamIx = 9;
                tileOffset = DUSKULL_TILE_OFFSET_QUARTER_FACING;
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_ESCAPE_PREP;
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE;
                gCurrentPinballGame->minionCanCollide[i] = FALSE;
                if (gCurrentPinballGame->minionActiveCount > 0)
                    gCurrentPinballGame->minionActiveCount--;
                m4aSongNumStart(SE_DUSCLOPS_DEPART_INCOMPLETE);
                oamIx = 9;
                tileOffset = DUSKULL_TILE_OFFSET_QUARTER_FACING;
            }
            break;
        case DUSKULL_ENTITY_STATE_ESCAPE:
            if (DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
            {
                gCurrentPinballGame->minionStateTimer[i]++;
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->minionFramesetIx[i]++;
                if (gCurrentPinballGame->minionFramesetIx[i] > DUSKULL_FRAME_ESCAPE)
                {
                    gCurrentPinballGame->minionFramesetIx[i] = DUSKULL_FRAME_ESCAPE;
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_CLEANUP;
                }
            }
            oamIx = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_CLEANUP:
            gCurrentPinballGame->minionDrawInFrame[i] = FALSE;
            gCurrentPinballGame->minionCanCollide[i] = FALSE;
            gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_SPAWN;
            oamIx = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DuskullFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        }

        // Time alive > time before escape, && Not in the last set before moving to the next mode.
        if (gCurrentPinballGame->minionTimeAlive[i] > gCurrentPinballGame->minionEscapeAtTime[i] &&
            gCurrentPinballGame->bonusModeHitCount <= DUSKULL_ALLOWED_TO_SPAWN)
        {
            gCurrentPinballGame->minionTimeAlive[i] = 0;
            if (gCurrentPinballGame->minionState[i] == DUSKULL_ENTITY_STATE_MOVE_LEFT)
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_LEFT;
            else
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_RIGHT;

            gCurrentPinballGame->minionStateTimer[i] = 0;
        }

        gCurrentPinballGame->minionSpriteVariant[i] = gCurrentPinballGame->minionNextSpriteVariant[i];
        gCurrentPinballGame->minionNextSpriteVariant[i] = tileOffset;
        gCurrentPinballGame->minionOamIx[i] = oamIx;
        gCurrentPinballGame->minionCollisionPosition[i].x = (gCurrentPinballGame->minionLogicPosition[i].x / 10) * 2 + 208;
        gCurrentPinballGame->minionCollisionPosition[i].y = (gCurrentPinballGame->minionLogicPosition[i].y / 10) * 2 + 66;
    }
}

extern const u8 gDusclopsBoardDuskull_Gfx[];
extern const u16 gDuskullSpritesheetOam[][2][3];
void DuskullPhase_ProcessGraphics() {
    s16 i, animPiece;
    s16 oamIx;
    struct SpriteGroup *spriteGroup;
    struct OamDataSimple * oamData;
    u16 * dst;
    const u16 * src;

    for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
    {
        s16 spriteVariant = gCurrentPinballGame->minionSpriteVariant[i];
        DmaCopy16(3, gDusclopsBoardDuskull_Gfx + spriteVariant * 0x280, OBJ_VRAM0 + 0x920 + i * 0x280, 0x280);
        oamIx = gCurrentPinballGame->minionOamIx[i];
        spriteGroup = &gMain_spriteGroups[7 + i];

        if (gCurrentPinballGame->minionDrawInFrame[i]) {
            s32 x = 0; // Scrub C to get the compiler to add before subtracting
            spriteGroup->baseX = gCurrentPinballGame->minionLogicPosition[i].x / 10 + 108 + x - gCurrentPinballGame->unk58;
            spriteGroup->baseY = gCurrentPinballGame->minionLogicPosition[i].y / 10 + 28 + x - gCurrentPinballGame->unk5A;
        } else {
            // Draw off screen, past lower right bounds of screen
            spriteGroup->baseX = 240;
            spriteGroup->baseY = 180;
        }

        if (spriteVariant == 6)
        {
            u16 scaleX;
            u16 scaleY;
            if (gCurrentPinballGame->minionDeathTimer[i] <= 6) {
                scaleX = (gCurrentPinballGame->minionDeathTimer[i] * 0x80) / 6 + 0x100;
                scaleY = ((6-gCurrentPinballGame->minionDeathTimer[i]) * 0x80) / 6 + 0x80;
            } else {
                scaleX = ((24-gCurrentPinballGame->minionDeathTimer[i]) * 0x170) / 18 + 0x10;
                scaleY = ((gCurrentPinballGame->minionDeathTimer[i]-6) * 0x1C0) / 18 + 0x80;
            }
            SetMatrixScale(scaleX, scaleY, i + 2);
            spriteGroup->baseX -= 16;
            spriteGroup->baseY -= 16;

            for (animPiece = 0; animPiece < 2; animPiece++)
            {
                oamData = &spriteGroup->oam[animPiece];

                dst = (u16*)&gOamBuffer[oamData->oamId];
                src = gDuskullSpritesheetOam[oamIx][animPiece];
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;

                gOamBuffer[oamData->oamId].x += spriteGroup->baseX;
                gOamBuffer[oamData->oamId].y += spriteGroup->baseY;
                gOamBuffer[oamData->oamId].tileNum += i * 20;
                gOamBuffer[oamData->oamId].affineMode = ST_OAM_AFFINE_DOUBLE;
                gOamBuffer[oamData->oamId].matrixNum = i + 2;
            }
        }
        else
        {
            for (animPiece = 0; animPiece < 2; animPiece++)
            {
                oamData = &spriteGroup->oam[animPiece];
                dst = (u16*)&gOamBuffer[oamData->oamId];
                src = gDuskullSpritesheetOam[oamIx][animPiece];
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;

                gOamBuffer[oamData->oamId].x += spriteGroup->baseX;
                gOamBuffer[oamData->oamId].y += spriteGroup->baseY;
                gOamBuffer[oamData->oamId].tileNum += i * 20;
            }
        }
    }
}

void DusclopsPhase_ProcessEntityLogicAndGraphics(void)
{
    s16 tileOffset;
    u16 available;
    struct OamDataSimple *oamSimple;
    struct SpriteGroup *spriteGroup;

    tileOffset = 0;
    spriteGroup = &gMain.spriteGroups[14];
    switch(gCurrentPinballGame->unk3DC)
    {
    case DUSCLOPS_ENTITY_STATE_INIT:
    {
        gCurrentPinballGame->unk3E8 = 880;
        gCurrentPinballGame->unk3EA = 300;
        gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_INTRO_APPEARANCE;
        gCurrentPinballGame->unk3E6 = 184;
        gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_INTRO_START;
        tileOffset = 0;
        gCurrentPinballGame->unk294 = 1;
        break;
    }

    case DUSCLOPS_ENTITY_STATE_INTRO_APPEARANCE:
    {
        if (DuclopsFramesetData[gCurrentPinballGame->unk3E2][1] > gCurrentPinballGame->unk3E4)
            gCurrentPinballGame->unk3E4++;
        else
        {
            gCurrentPinballGame->unk3E4 = 0;
            gCurrentPinballGame->unk3E2++;

            if (gCurrentPinballGame->unk3E2 > DUSCLOPS_FRAME_INTRO_END)
            {
                gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_INTRO_START;

                if (gCurrentPinballGame->unk3E0 <= 0)
                    gCurrentPinballGame->unk3E0++;
                else
                {
                    gCurrentPinballGame->unk3E0 = 0;
                    gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_GUARD_READY;
                }
            }

            if (gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_INTRO_FOOTSTEP_LEFT)
            {
                gCurrentPinballGame->unk129 = 0;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE);
                PlayRumble(8);
            }

            if (gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_INTRO_FOOTSTEP_RIGHT)
            {
                gCurrentPinballGame->unk129 = 1;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE);
                PlayRumble(8);

            }
        }

        tileOffset = 0;
        break;
    }
    case DUSCLOPS_ENTITY_STATE_GUARD_READY:
    {
        if (gCurrentPinballGame->unk3E4 <= 255)
        {
            tileOffset = gUnknown_08137D40[(gCurrentPinballGame->unk3E4 % 0x40) / 16];
            gCurrentPinballGame->unk3E4++;

            if (gCurrentPinballGame->unk3E4 == 256)
            {
                gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_WALKING;
                gCurrentPinballGame->unk3E4 = 0;

                if (gCurrentPinballGame->unk3E0 > 3)
                    gCurrentPinballGame->unk3E0 = 0;
                if (gCurrentPinballGame->unk3E0 <= 1)
                    gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
                else
                    gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_RIGHT_FOOT_FORWARD;
            }
        }

        if (gCurrentPinballGame->unk3E6 > 0)
        {
            if (gCurrentPinballGame->unk3E6 > 64)
                gCurrentPinballGame->unk3E6--;
            else
                gCurrentPinballGame->unk3E6 -= 2;

            if (gCurrentPinballGame->unk3E6 == 154)
                m4aSongNumStart(SE_DUSCLOPS_APPEAR); //Dusclops Appears
        }
        else
        {
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_DUSCLOPS;
            gCurrentPinballGame->unk294 = 2;
        }

        break;
    }
    case DUSCLOPS_ENTITY_STATE_WALKING:
    {
        if (DuclopsFramesetData[gCurrentPinballGame->unk3E2][1] > gCurrentPinballGame->unk3E4)
        {
            gCurrentPinballGame->unk3E4++;
        }
        else
        {
            gCurrentPinballGame->unk3E4 = 0;

            if (gCurrentPinballGame->unk3E0 <= 1)
            {
                gCurrentPinballGame->unk3E2++;

                if (gCurrentPinballGame->unk3E2 > DUSCLOPS_FRAME_RIGHT_FOOT_FORWARD)
                {
                    gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
                    gCurrentPinballGame->unk3E0++;

                    if ((gCurrentPinballGame->unk3E0 & 1) == 0)
                    {
                        gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_GUARD_READY;
                        gCurrentPinballGame->unk3E4 = 0;
                    }
                }
            }
            else if (--gCurrentPinballGame->unk3E2 < 0)
            {
                gCurrentPinballGame->unk3E0++;

                if ((gCurrentPinballGame->unk3E0 & 1) == 0)
                {
                    gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_GUARD_READY;
                    gCurrentPinballGame->unk3E4 = 0;
                    gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
                }
                else
                    gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_RIGHT_FOOT_FORWARD;
            }

            if (gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_LEFT_FOOT_LANDS)
            {
                gCurrentPinballGame->unk129 = 0;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE);
                PlayRumble(8);
            }

            if (gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_RIGHT_FOOT_LANDS)
            {
                gCurrentPinballGame->unk129 = 1;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE);
                PlayRumble(8);
            }
        }

        tileOffset = DuclopsFramesetData[gCurrentPinballGame->unk3E2][0];

        if( gCurrentPinballGame->unk3E2  == DUSCLOPS_FRAME_WALK_NEUTRAL || 
            gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_WALK_NEUTRAL_RIGHT_FOOT_FORWARD )
        {
            break;
        }

        if (gCurrentPinballGame->unk3E0 <= 1)
        {
            if (gCurrentPinballGame->unk3EA <= 583)
            {
                gCurrentPinballGame->unk3EA++;
                break;
            }

            if ((gCurrentPinballGame->unk3E2 % 4) != 0)
                break;

            gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_GUARD_READY;
            gCurrentPinballGame->unk3E4 = 0;
            gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
            gCurrentPinballGame->unk3E0 = 2;
            break;
        }

        if (gCurrentPinballGame->unk3EA > 300)
        {
            gCurrentPinballGame->unk3EA--;
            break;
        }

        if ((gCurrentPinballGame->unk3E2 % 4) != 0)
            break;

        gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_GUARD_READY;
        gCurrentPinballGame->unk3E4 = 0;
        gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
        gCurrentPinballGame->unk3E0 = 4;

        break;
    }
    case DUSCLOPS_ENTITY_STATE_HIT:
    {
        gCurrentPinballGame->unk3E4 = 0;
        gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
        gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_HIT_STUN;
        tileOffset = DUSCLOPS_TILE_OFFSET_HIT;

        m4aSongNumStart(SE_DUSCLOPS_HIT); //Dusclops hit
        gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_NONE;
        PlayRumble(7);
        break;
    }
    case DUSCLOPS_ENTITY_STATE_HIT_STUN:
    {
        if (gCurrentPinballGame->unk3E4 <= 27)
        {
            tileOffset = DUSCLOPS_TILE_OFFSET_HIT;
            gCurrentPinballGame->unk3E4++;
            break;
        }

        if (gCurrentPinballGame->bonusModeHitCount < DUSCLOPS_HITS_NEEDED_TO_SUCCEED -1)
        {
            gCurrentPinballGame->unk3E4 = 128;
            gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
            gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_GUARD_READY;
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_NONE;
            tileOffset = DUSCLOPS_TILE_OFFSET_HIT;
        }
        else
        {
            gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_VANISH;
            tileOffset = DUSCLOPS_TILE_OFFSET_HIT;
        }

        gCurrentPinballGame->bonusModeHitCount++;
        gCurrentPinballGame->scoreAddedInFrame = 300000;

        break;
    }
    case DUSCLOPS_ENTITY_STATE_HIT_ABSORB_ZONE:
    {
        struct Vector16 tempVector;

        gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_ABSORB_START;
        gCurrentPinballGame->unk3E4 = 0;
        gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_ABSORBED_BALL;
        gCurrentPinballGame->unk5A6 = 0;
        tileOffset = DUSCLOPS_TILE_OFFSET_ABSORB_START;

        m4aSongNumStart(SE_DUSCLOPS_BALL_ABSORB); //Dusclops absorbs ball
        gCurrentPinballGame->unk288 = (gCurrentPinballGame->unk3E8 / 10) + 32;
        gCurrentPinballGame->unk28A = (gCurrentPinballGame->unk3EA / 10) + 36;

        tempVector.x = (gCurrentPinballGame->unk288 << 8) - gCurrentPinballGame->ball->positionQ8.x;
        tempVector.y = (gCurrentPinballGame->unk28A << 8) - gCurrentPinballGame->ball->positionQ8.y;

        gCurrentPinballGame->unk5AC = (tempVector.x * tempVector.x) + (tempVector.y * tempVector.y);
        gCurrentPinballGame->unk5AC = Sqrt(gCurrentPinballGame->unk5AC * 4) / 2;
        gCurrentPinballGame->unk5B0 = ArcTan2(-tempVector.x, tempVector.y);

        PlayRumble(13);
        break;
    }
    case DUSCLOPS_ENTITY_STATE_ABSORBED_BALL:
    {
        if (DuclopsFramesetData[gCurrentPinballGame->unk3E2][1] > gCurrentPinballGame->unk3E4)
            gCurrentPinballGame->unk3E4++;
        else
        {
            gCurrentPinballGame->unk3E4 = 0;
            gCurrentPinballGame->unk3E2++;

            if (gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_ABSORB_LAUNCH_PREP)
            {
                gCurrentPinballGame->ball->velocity.x = (gMain.systemFrameCount % 2 * 300) + 65386;
                gCurrentPinballGame->ball->velocity.y = 300;
                gCurrentPinballGame->ball->unk0 = 0;
                m4aSongNumStart(SE_DUSCLOPS_BALL_LAUNCH); //Dusclops launch ball
                PlayRumble(8);
            }

            if (gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_ABSOLB_LAUNCH)
                gCurrentPinballGame->unk1F = 0;

            if (gCurrentPinballGame->unk3E2 > DUSCLOPS_FRAME_ABSOLB_LAUNCH)
            {
                gCurrentPinballGame->unk3E4 = 128;
                gCurrentPinballGame->unk3E2 = DUSCLOPS_FRAME_WALK_NEUTRAL;
                gCurrentPinballGame->unk3DC = DUSCLOPS_ENTITY_STATE_GUARD_READY;
            }
        }

        if (gCurrentPinballGame->ballSpeed != 0)
        {
            if ((gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_ABSOLB_LAUNCH) && (gCurrentPinballGame->unk3E4 > 4))
                gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_DUSCLOPS;
        }
        else
        {
            if ((gCurrentPinballGame->unk3E2 == DUSCLOPS_FRAME_ABSOLB_LAUNCH) && (gCurrentPinballGame->unk3E4 != 0))
                gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLLISION_MODE_DUSCLOPS;
        }

        if (gCurrentPinballGame->unk5A6 <= 29)
        {
            s16 tr4 = 29 - gCurrentPinballGame->unk5A6;
            s32 sl;

            gCurrentPinballGame->unk5B0 -= ((tr4 * 8192) / 30) - 8192;
            gCurrentPinballGame->ball->unkA = gCurrentPinballGame->ball->unkA - 8192;

            sl = (gCurrentPinballGame->unk5AC * tr4) / 30;

            gCurrentPinballGame->ball->positionQ8.x = (gCurrentPinballGame->unk288 * 256) + ((Cos(gCurrentPinballGame->unk5B0) * sl) / 20000);

            gCurrentPinballGame->ball->positionQ8.y = (gCurrentPinballGame->unk28A * 256) - ((Sin(gCurrentPinballGame->unk5B0) * sl) / 20000);

            gCurrentPinballGame->ball->velocity.x = (gCurrentPinballGame->ball->velocity.x * 4) / 5;
            gCurrentPinballGame->ball->velocity.y = (gCurrentPinballGame->ball->velocity.y * 4) / 5;
        }

        if (gCurrentPinballGame->unk5A6 == 40)
        {
            gCurrentPinballGame->ball->unk0 = 1;
            gCurrentPinballGame->ball->velocity.x = 0;
            gCurrentPinballGame->ball->velocity.y = 0;
        }

        gCurrentPinballGame->unk5A6++;
        tileOffset = DuclopsFramesetData[gCurrentPinballGame->unk3E2][0];

        break;
    }
    case DUSCLOPS_ENTITY_STATE_VANISH:
    {
        gCurrentPinballGame->unk294 = 3;
        gMain.modeChangeFlags = MODE_CHANGE_BONUS_BANNER;

        if (gCurrentPinballGame->unk3E6 == 0)
        {
            gCurrentPinballGame->unk388 = 2;
            gCurrentPinballGame->unk392 = 0;
        }

        tileOffset = DUSCLOPS_TILE_OFFSET_VANQUISHED;

        if (gCurrentPinballGame->unk3E6 <= 183)
        {
            if (gCurrentPinballGame->unk3E6 <= 63)
                gCurrentPinballGame->unk3E6++;
            else
                gCurrentPinballGame->unk3E6 += 2;

            if (gCurrentPinballGame->unk3E6 == 30)
            {
                MPlayStart(&gMPlayInfo_SE1, &se_dusclops_appear);
            }
            break;
        }

        gMain.spriteGroups[13].available = FALSE;
        gMain.spriteGroups[14].available = FALSE;
        gMain.spriteGroups[12].available = FALSE;
        gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_4_INIT_SCORE_PHASE;
        gCurrentPinballGame->unk18 = 0;
        break;
    }
    default:
        break;
    } //End switch

    DmaCopy16(3 , gDusclopsBoardDusclops_Gfx + tileOffset * 1024, (void *)OBJ_VRAM0+0x10a0, BG_SCREEN_SIZE);

    gCurrentPinballGame->unk3F0 = ((gCurrentPinballGame->unk3E8 / 10) * 2) + 16;
    gCurrentPinballGame->unk3F2 = ((gCurrentPinballGame->unk3EA / 10) * 2) + 16;

    // Draw dusclops
    if(spriteGroup->available != 0)
    {
        struct OamDataSimple *new_var;
        spriteGroup->baseX = (-gCurrentPinballGame->unk58) + (gCurrentPinballGame->unk3E8 / 10);
        spriteGroup->baseY = (-gCurrentPinballGame->unk5A) + (gCurrentPinballGame->unk3EA / 10);

        oamSimple = spriteGroup->oam;

        if (tileOffset == DUSCLOPS_TILE_OFFSET_HIT)
        {
            if (gCurrentPinballGame->unk3E4 <= 5)
                gOamBuffer[oamSimple->oamId].paletteNum = 4;
            else
                gOamBuffer[oamSimple->oamId].paletteNum = 3;
        }
        else
            gOamBuffer[oamSimple->oamId].paletteNum = 3;

        gOamBuffer[oamSimple->oamId].x = oamSimple->xOffset + spriteGroup->baseX;
        gOamBuffer[oamSimple->oamId].y = oamSimple->yOffset + spriteGroup->baseY;
    }

    // Blend appearance Lines
    spriteGroup = &gMain.spriteGroups[12];
    if (spriteGroup->available != 0)
    {
        if (gCurrentPinballGame->returnToMainBoardFlag == 0)
        {
            u32 offY = 92;

            spriteGroup->baseX = -gCurrentPinballGame->unk58 + (gCurrentPinballGame->unk3E8 / 10);
            spriteGroup->baseY = -gCurrentPinballGame->unk5A + (gCurrentPinballGame->unk3EA / 10)
                + ((gCurrentPinballGame->unk3E6 / 2) - offY);
        }
        else
        {
            spriteGroup->baseX = 240;
            spriteGroup->baseY = 160;
        }

        {
            s16 i;
            u8 r1;
            r1 = gMain.systemFrameCount % 4;
            DmaCopy16(3 , gDusclopsBoardDusclopsAppearFx_Gfx + r1 / 2 * 0x600, (void *)OBJ_VRAM0 + 0x1aa0, 0xc00);

            for (i = 0; i < 2; i++)
            {
                oamSimple = &spriteGroup->oam[i];
                gOamBuffer[oamSimple->oamId].x = oamSimple->xOffset + spriteGroup->baseX;
                gOamBuffer[oamSimple->oamId].y = oamSimple->yOffset + spriteGroup->baseY;
            }
        }
    }

    // Draw ball capture vortex
    spriteGroup = &gMain.spriteGroups[13];

    if (spriteGroup->available != 0)
    {
        s32 offX = 16;
        s32 offY = 20;
        spriteGroup->baseX = gCurrentPinballGame->unk3E8 / 10 + offX - gCurrentPinballGame->unk58;
        if (gCurrentPinballGame->unk3E2 >= DUSCLOPS_FRAME_ABSORB_VORTEX_START &&
            gCurrentPinballGame->unk3E2 <= DUSCLOPS_FRAME_ABSORB_VORTEX_END )
        {
            s16 r0;
            spriteGroup->baseY = ((gCurrentPinballGame->unk3EA / 10) + offY) - gCurrentPinballGame->unk5A;
            r0 = gCurrentPinballGame->unk5A6 % 24;
            if(r0 <= 10)
                tileOffset = 0;
            else if (r0 <= 17)
                tileOffset = 1;
            else
                tileOffset = 2;

            DmaCopy16(3 , gDusclopsBoardDusclopsBallGrabSwirl_Gfx + tileOffset * 0x200,(void *)OBJ_VRAM0+0x18a0, 0x200);
        }
        else
        {
            spriteGroup->baseY = 180;
        }

        oamSimple = spriteGroup->oam;
        gOamBuffer[oamSimple->oamId].x = oamSimple->xOffset + spriteGroup->baseX;
        gOamBuffer[oamSimple->oamId].y = oamSimple->yOffset + spriteGroup->baseY;
    }
}
