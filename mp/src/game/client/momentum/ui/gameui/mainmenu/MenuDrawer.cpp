#include "cbase.h"

#include "MenuDrawer.h"

#include "tier0/memdbgon.h"

using namespace vgui;

MenuDrawerPanel::MenuDrawerPanel(Panel *pParent) : BaseClass(pParent, "MenuDrawer")
{
    SetProportional(true);


    LoadControlSettings("resource/ui/mainmenu/MenuDrawer.res");
}