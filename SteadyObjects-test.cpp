#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "fssimplewindow.h"
#include "SteadyObjects.h"

int main()
{
    int winWid, winHei;
    int marioX, marioY, marioW, marioH;
    std::string marioState ("super");
    int marioVX, marioVY;
    int block_hit_x;
    double dt;
    int cameraX;
    int terminate = 0;
    int cycle = 0;
    winWid = 768;
    winHei = 576;
    cameraX = 800;

    ///////////////////////////////////////////////////////////
    /////////// Code for creating and using Objects ///////////
    Objects objects;
    objects.Init();
    /////////// Code for creating and using Objects ///////////
    ///////////////////////////////////////////////////////////

	// test Mario
	marioX = 19*48;
	//marioY = 7*48+24;
	marioY = 576 - (3*48+72);
	marioW = 48;
	marioH = 48;
    marioVX = 5;
    //marioVY = 5;

	FsOpenWindow(400,0,winWid,winHei,1);
    FsPassedTime();
	while(!terminate) {
		FsPollDevice();
		dt = (double)FsPassedTime()/1000.0;
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        cycle++;
        if (cycle > 70) {
            marioVX = -marioVX;
            //marioVY = -marioVY;
            cycle = 0;
        }
        marioX += marioVX;
        //marioY += marioVY;
        //marioY -= 2;
        if (0 != FsGetKeyState(FSKEY_RIGHT)) {
            cameraX += 50;
        }
        if (0 != FsGetKeyState(FSKEY_LEFT)) {
            cameraX -= 50;
        }
        if (0 != FsGetKeyState(FSKEY_ESC)) {
            terminate = 1;
        }

        glColor3ub(0,0,0);
        DrawRect(marioX-cameraX, marioY, marioX-cameraX + marioW, marioY + marioH,1);


    ///////////////////////////////////////////////////////////
    /////////// Code for creating and using Objects ///////////
        /* Return the x position of hit block */
        block_hit_x = objects.Contact(marioX, marioY, marioW, marioH, marioState);
        // It's a trick!!
        // Call twice to increase resolution
        objects.MushroomMove(marioX, marioY, marioW, marioH, dt);
        objects.MushroomMove(marioX, marioY, marioW, marioH, dt);

        objects.Draw(cameraX);
    /////////// Code for creating and using Objects ///////////
    ///////////////////////////////////////////////////////////

		FsSwapBuffers();
        FsSleep(10);
	}

	return 0;
}
