#include "global.h"
#include "main.h"


void RubyBoardProcess_0A_50848(void)
{
    s16 i;
    struct SpriteGroup *group;

    for (i = 0; i < 84; i++)
        gMain.spriteGroups[i].active = FALSE;

    gMain.spriteGroups[64].active = TRUE;
    group = &gMain.spriteGroups[48]; // fake match?
    gMain.spriteGroups[70].active = TRUE;
    gMain.spriteGroups[0].active = TRUE;
    gMain.spriteGroups[1].active = TRUE;
    gMain.spriteGroups[2].active = TRUE;
    gMain.spriteGroups[28].active = TRUE;
    gMain.spriteGroups[81].active = TRUE;
    gMain.spriteGroups[65].active = TRUE;
    gMain.spriteGroups[71].active = TRUE;
    gMain.spriteGroups[66].active = TRUE;
    gMain.spriteGroups[51].active = TRUE;
    gMain.spriteGroups[61].active = TRUE;
    group->active = TRUE;
    gMain.spriteGroups[52].active = TRUE;
    gMain.spriteGroups[62].active = TRUE;
    LoadSpriteSets(
        gFieldSpriteSets[gMain.selectedField].spriteSets,
        gFieldSpriteSets[gMain.selectedField].numSpriteSets,
        gMain.spriteGroups);
}

void RubyBoardProcess_0B_50918(void)
{
    s16 i;

    gMain.spriteGroups[10].active = FALSE;
    gMain.spriteGroups[11].active = FALSE;
    gMain.spriteGroups[48].active = FALSE;
    gMain.spriteGroups[71].active = FALSE;
    for (i = 51; i < 67; i++)
        gMain.spriteGroups[i].active = FALSE;

    gCurrentPinballGame->randomSpriteVariantSeed = gMain.systemFrameCount % 25;
    if (gCurrentPinballGame->cameraYViewport < 110)
    {
        gMain.spriteGroups[65].active = TRUE;
        gMain.spriteGroups[71].active = TRUE;
        gMain.spriteGroups[66].active = TRUE;
    }

    if (gCurrentPinballGame->cameraYViewport < 168)
    {
        gMain.spriteGroups[48].active = TRUE;
        gMain.spriteGroups[52].active = TRUE;
    }

    if (gCurrentPinballGame->cameraYViewport < 220)
    {
        gMain.spriteGroups[51].active = TRUE;
        gMain.spriteGroups[61].active = TRUE;
        gMain.spriteGroups[64].active = TRUE;
        if (gCurrentPinballGame->shouldProcessWhiscash)
            gMain.spriteGroups[63].active = TRUE;
        else
            gMain.spriteGroups[62].active = TRUE;
    }

    if (gCurrentPinballGame->cameraYViewport > 63)
    {
        gMain.spriteGroups[53].active = TRUE;
        gMain.spriteGroups[57].active = TRUE;
    }

    if (gCurrentPinballGame->cameraYViewport > 115)
        gMain.spriteGroups[58].active = TRUE;

    if (gCurrentPinballGame->cameraYViewport > 130)
    {
        gMain.spriteGroups[59].active = TRUE;
        gMain.spriteGroups[60].active = TRUE;
    }

    if (gCurrentPinballGame->cameraYViewport > 216)
    {
        gMain.spriteGroups[56].active = TRUE;
        gMain.spriteGroups[54].active = TRUE;
        gMain.spriteGroups[55].active = TRUE;
        gMain.spriteGroups[10].active = TRUE;
        gMain.spriteGroups[11].active = TRUE;
    }

    LoadSpriteSets(
        gFieldSpriteSets[gMain.selectedField].spriteSets,
        gFieldSpriteSets[gMain.selectedField].numSpriteSets,
        gMain.spriteGroups);
}

void SapphireBoardProcess_0A_50AD4(void)
{
    s16 i;

    for (i = 0; i < 87; i++)
        gMain.spriteGroups[i].active = FALSE;

    gMain.spriteGroups[72].active = TRUE;
    gMain.spriteGroups[63].active = TRUE;
    gMain.spriteGroups[60].active = TRUE;
    gMain.spriteGroups[69].active = TRUE;
    gMain.spriteGroups[52].active = TRUE;
    gMain.spriteGroups[74].active = TRUE;
    gMain.spriteGroups[0].active = TRUE;
    gMain.spriteGroups[1].active = TRUE;
    gMain.spriteGroups[2].active = TRUE;
    gMain.spriteGroups[25].active = TRUE;
    gMain.spriteGroups[85].active = TRUE;
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void SapphireBoardProcess_0B_50B80(void)
{
    s16 i;

    for (i = 55; i < 71; i++)
        gMain.spriteGroups[i].active = FALSE;

    gMain.spriteGroups[52].active = FALSE;
    gMain.spriteGroups[72].active = FALSE;
    gMain.spriteGroups[26].active = FALSE;
    gMain.spriteGroups[51].active = FALSE;
    gMain.spriteGroups[76].active = FALSE;
    gMain.spriteGroups[75].active = FALSE;
    gMain.spriteGroups[10].active = FALSE;
    gMain.spriteGroups[11].active = FALSE;
    gCurrentPinballGame->randomSpriteVariantSeed = gMain.systemFrameCount % 25;
    if (gCurrentPinballGame->cameraYViewport < 90)
    {
        gMain.spriteGroups[52].active = TRUE;
        gMain.spriteGroups[51].active = TRUE;
    }
    if (gCurrentPinballGame->cameraYViewport < 220)
    {
        gMain.spriteGroups[72].active = TRUE;
    }
    if (gCurrentPinballGame->cameraYViewport < 150)
    {
        gMain.spriteGroups[60].active = TRUE;
        gMain.spriteGroups[69].active = TRUE;
    }
    if (gCurrentPinballGame->cameraYViewport < 196)
    {
        gMain.spriteGroups[63].active = TRUE;
        gMain.spriteGroups[75].active = TRUE;
    }
    if (gCurrentPinballGame->cameraYViewport < 202)
    {
        gMain.spriteGroups[61].active = TRUE;
        gMain.spriteGroups[58].active = TRUE;
        gMain.spriteGroups[62].active = TRUE;
        gMain.spriteGroups[59].active = TRUE;
        gMain.spriteGroups[76].active = TRUE;
    }
    if (gCurrentPinballGame->cameraYViewport > 118)
    {
        gMain.spriteGroups[70].active = TRUE;
        gMain.spriteGroups[26].active = TRUE;
        gMain.spriteGroups[64].active = TRUE;
        gMain.spriteGroups[68].active = TRUE;
        gMain.spriteGroups[65].active = TRUE;
        gMain.spriteGroups[66].active = TRUE;
        gMain.spriteGroups[67].active = TRUE;
    }
    if (gCurrentPinballGame->cameraYViewport > 216)
    {
        gMain.spriteGroups[57].active = TRUE;
        gMain.spriteGroups[55].active = TRUE;
        gMain.spriteGroups[56].active = TRUE;
        gMain.spriteGroups[10].active = TRUE;
        gMain.spriteGroups[11].active = TRUE;
    }

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets, gFieldSpriteSets[gMain.selectedField].numSpriteSets, gMain.spriteGroups);
}

void DusclopsBoardProcess_0A_50D48(void)
{
    s16 i;

    for (i = 0; i < 15; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = TRUE;
        else
            gMain.spriteGroups[i].active = FALSE;
    }

    gMain.fieldSpriteGroups[0]->active = TRUE;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void DusclopsBoardProcess_0B_50DB8(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void KecleonBoardProcess_0A_50DE0(void)
{
    s16 i;

    for (i = 0; i < 33; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = TRUE;
        else
            gMain.spriteGroups[i].active = FALSE;
    }

    gMain.fieldSpriteGroups[0]->active = TRUE;
    gMain.spriteGroups[23].active = TRUE;
    gMain.spriteGroups[9].active = TRUE;
    gMain.spriteGroups[24].active = TRUE;
    gMain.spriteGroups[16].active = TRUE;
    gMain.spriteGroups[17].active = TRUE;
    gMain.spriteGroups[7].active = TRUE;
    gMain.spriteGroups[10].active = TRUE;
    gMain.spriteGroups[11].active = TRUE;
    gMain.spriteGroups[12].active = TRUE;
    gMain.spriteGroups[13].active = TRUE;
    gMain.spriteGroups[14].active = TRUE;
    gMain.spriteGroups[15].active = TRUE;
    gMain.spriteGroups[18].active = TRUE;
    gMain.spriteGroups[19].active = TRUE;
    gMain.spriteGroups[20].active = TRUE;
    gMain.spriteGroups[21].active = TRUE;
    gMain.spriteGroups[25].active = TRUE;
    gMain.spriteGroups[26].active = TRUE;
    gMain.spriteGroups[27].active = TRUE;
    gMain.spriteGroups[28].active = TRUE;
    gMain.spriteGroups[31].active = TRUE;
    gMain.spriteGroups[32].active = TRUE;
    gMain.spriteGroups[29].active = TRUE;
    gMain.spriteGroups[30].active = TRUE;

    LoadSpriteSets(
        gFieldSpriteSets[gMain.selectedField].spriteSets,
        gFieldSpriteSets[gMain.selectedField].numSpriteSets,
        gMain.spriteGroups
    );
}

void nullsub_20(void)
{}

void KyogreBoardProcess_0A_50F04()
{
    s16 i;

    for (i = 0; i < 27; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = TRUE;
        else
            gMain.spriteGroups[i].active = FALSE;
    }

    gMain.fieldSpriteGroups[0]->active = TRUE;
    gMain.spriteGroups[11].active = TRUE;
    gMain.spriteGroups[12].active = TRUE;
    gMain.spriteGroups[13].active = TRUE;
    gMain.spriteGroups[14].active = TRUE;
    gMain.spriteGroups[21].active = TRUE;
    gMain.spriteGroups[22].active = TRUE;
    gMain.spriteGroups[23].active = TRUE;
    gMain.spriteGroups[15].active = TRUE;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void KyogreBoardProcess_0B_50FAC(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void GroudonBoardProcess_0A_50FD4(void)
{
    s16 i;

    for (i = 0; i < 32; i++)
    {
        if (i < 5) {
            gMain.spriteGroups[i].active = TRUE;
        } else {
            gMain.spriteGroups[i].active = FALSE;
        }
    }

    gMain.fieldSpriteGroups[0]->active = TRUE;
    gMain.spriteGroups[11].active = TRUE;
    gMain.spriteGroups[12].active = TRUE;
    gMain.spriteGroups[13].active = TRUE;
    gMain.spriteGroups[14].active = TRUE;
    gMain.spriteGroups[29].active = TRUE;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void GroudonBoardProcess_0B_51068(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void RayquazaBoardProcess_0A_51090(void)
{
    s16 i;

    for (i = 0; i < 46; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = TRUE;
        else
            gMain.spriteGroups[i].active = FALSE;
    }

    gMain.fieldSpriteGroups[0]->active = TRUE;
    gMain.spriteGroups[42].active = TRUE;
    gMain.spriteGroups[11].active = TRUE;
    gMain.spriteGroups[12].active = TRUE;
    gMain.spriteGroups[13].active = TRUE;
    gMain.spriteGroups[21].active = TRUE;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void RayquazaBoardProcess_0B_51128(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void SphealBoardProcess_0A_51150(void)
{
    s16 i;

    for (i = 0; i < 23; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = TRUE;
        else
            gMain.spriteGroups[i].active = FALSE;
    }

    gMain.fieldSpriteGroups[0]->active = TRUE;
    gMain.spriteGroups[18].active = TRUE;
    gMain.spriteGroups[21].active = TRUE;
    gMain.spriteGroups[22].active = TRUE;
    gMain.spriteGroups[14].active = TRUE;
    gMain.spriteGroups[15].active = TRUE;
    gMain.spriteGroups[16].active = TRUE;
    gMain.spriteGroups[17].active = TRUE;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void SphealBoardProcess_0B_511F8(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}
