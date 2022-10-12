//
//  main.c
// Playdate C Template
//

#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

static int update(void* userdata);

const char* fontpath = "/System/Fonts/Asheville-Sans-24-Light.pft";
LCDFont* font = NULL;

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed
    
    const char* err;
        font = pd->graphics->loadFont(fontpath, &err);
            
    if ( font == NULL )
        pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
    
    if ( event == kEventInit ) {
//        pd->display->setRefreshRate(50);
        pd->system->setUpdateCallback(update, pd);
    }
    
    return 0;
}

static int update(void* userdata)
{
    PlaydateAPI* pd = userdata;
    
    pd->graphics->clear(kColorWhite);
    pd->graphics->setFont(font);
    pd->graphics->drawText("Playdate C Template!", strlen("Playdate C Template!"), kASCIIEncoding,75, 100);
        
    pd->system->drawFPS(0,0);

    return 1;
}

