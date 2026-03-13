#include "global.h"
#include "m4a.h"
#include "main.h"
#include "constants/bg_music.h"



void AllBoardProcess_1A_47100(void)
{
    gCurrentPinballGame->unkFC = 128;
}

void sub_47110(void)
{
    s16 i;

    for (i = 0; i < 0x800; i++)
        gUnknown_03005C00[i] = 0x1FF;

    DmaCopy16(3, gUnknown_03005C00, (void *)0x06002000, 0x1000);
}


void AllBoardProcess_1B_47160(void)
{
    if (JOY_NEW(START_BUTTON) && gMain.mainState != STATE_GAME_IDLE && gCurrentPinballGame->unk1100 == 0)
    {
        if (gMain.modeChangeFlags & MODE_CHANGE_PAUSE)
        {
            gMain.modeChangeFlags &= ~MODE_CHANGE_PAUSE;
            sub_497BC();
        }
        else if ((gMain.modeChangeFlags & MODE_CHANGE_END_OF_GAME) == 0)
        {
            gMain.modeChangeFlags |= MODE_CHANGE_PAUSE;
            sub_495A0();
        }
    }

    //Game is paused
    if (gMain.modeChangeFlags & MODE_CHANGE_PAUSE)
    {
        if (JOY_NEW(DPAD_UP))
        {
            gCurrentPinballGame->unk1104 ^= 1;
            m4aSongNumStart(SE_UNKNOWN_0xA3);
        }

        if (JOY_NEW(DPAD_DOWN))
        {
            gCurrentPinballGame->unk1104 ^= 1;
            m4aSongNumStart(SE_UNKNOWN_0xA3);
        }

        if (JOY_NEW(A_BUTTON) && !JOY_HELD(B_BUTTON | SELECT_BUTTON | START_BUTTON))
        {
            if (gCurrentPinballGame->unk1104 == 0)
            {
                gMain.unkE = 2;
                sub_49850();
            }

            gMain.modeChangeFlags &= ~MODE_CHANGE_PAUSE;
            sub_497BC();
            gMain.newKeys &= ~A_BUTTON;
        }

        if (JOY_NEW(B_BUTTON))
        {
            gMain.modeChangeFlags &= ~MODE_CHANGE_PAUSE;
            sub_497BC();
            gMain.newKeys &= ~B_BUTTON;
        }

        if (gMain.modeChangeFlags & MODE_CHANGE_PAUSE)
            sub_49A34();
    }

    //Game is not paused
    if (gMain.modeChangeFlags == MODE_CHANGE_NONE)
    {
        gCurrentPinballGame->unk740 = 0;
        if (gMain.unk14 != 0)
        {
            gMain.unk14--;
            if (gMain.unk14 == 1)
            {
                if (gCurrentPinballGame->unkE4)
                    gMain.unk14 = 10;
                else if (gMain.unk11 == 0x8)
                    gCurrentPinballGame->unkE4 = 19;
                else
                    gCurrentPinballGame->unkE4 = 20;
            }

            if (gMain.unk14 == 0)
                gMain.modeChangeFlags = gMain.unk11;
        }
    }
}

