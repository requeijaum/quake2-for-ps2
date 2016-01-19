
/* ================================================================================================
 * -*- C -*-
 * File: main_ps2.c
 * Author: Guilherme R. Lampert
 * Created on: 26/10/15
 * Brief: Main application entry point for QPS2.
 *
 * This source code is released under the GNU GPL v2 license.
 * Check the accompanying LICENSE file for details.
 * ================================================================================================ */

#include "common/q_common.h"

/*
================
Test programs:
================
*/
extern void Test_PS2_Draw2D(void);
extern void Test_PS2_Cinematics(void);
extern void Test_PS2_QuakeMenus(void);
extern void Test_PS2_VU1Triangle(void);

/*
================
PS2 main() function
================
*/
int main(void)
{
    // The base path must be set for the PS2 because
    // of the different drive prefixes. Defaults to USB.
    #ifdef PS2_FS_BASE_PATH
    FS_SetDefaultBasePath(PS2_FS_BASE_PATH);
    #else // !PS2_FS_BASE_PATH
    FS_SetDefaultBasePath("mass:"); // Assume USB drive.
    #endif // PS2_FS_BASE_PATH

    // PS2 main() takes no arguments.
    // Fake a default program name argv[].
    int argc = 1;
    char * argv[] = { "QPS2.ELF" };
    Qcommon_Init(argc, argv);

    // Which "program" to run. 0 is game, following numbers are the tests.
    cvar_t * ps2_prog = Cvar_Get("ps2_prog", "0", 0);

    // Run Quake 2 normally:
    if ((int)ps2_prog->value == 0)
    {
        int time    = 0;
        int newtime = 0;
        int oldtime = Sys_Milliseconds();

        for (;;)
        {
            do
            {
                newtime = Sys_Milliseconds();
                time = newtime - oldtime;
            } while (time < 1);

            Qcommon_Frame(time);
            oldtime = newtime;
        }
    }
    else // Run a test:
    {
        switch ((int)ps2_prog->value)
        {
        case 1 :
            Test_PS2_Draw2D();
            break;
        case 2 :
            Test_PS2_Cinematics();
            break;
        case 3 :
            Test_PS2_QuakeMenus();
            break;
        case 4 :
            Test_PS2_VU1Triangle();
            break;
        }
    }

    Sys_Quit();
}
