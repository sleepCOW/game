#include "cbase.h"

#include "UserComponent.h"

#include "vgui_controls/Label.h"
#include "vgui_controls/ProgressBar.h"
#include "vgui_controls/Tooltip.h"
#include "vgui_avatarimage.h"

#include "fmtstr.h"
#include "mom_api_requests.h"
#include "util/mom_system_xp.h"

#include "tier0/memdbgon.h"

using namespace vgui;

UserComponent::UserComponent(Panel* pParent) : BaseClass(pParent, "UserComponent")
{
    SetProportional(true);
    SetPaintBackgroundEnabled(true);

    m_uUID = 0;

    m_pUserImage = new CAvatarImagePanel(this, "UserImage");
    m_pUserName = new Label(this, "UserName", "<UNKNOWN>");
    m_pUserRank = new Label(this, "UserRank", "Stoopid Head");
    m_pXPProgressBar = new ContinuousProgressBar(this, "XPProgress");
    m_pXPProgressBar->SetProgress(0);

    LoadControlSettings("resource/ui/UserComponent.res");
}

void UserComponent::SetUser(uint64 uID)
{
    m_uUID = uID;

    const CSteamID userID(m_uUID);

    m_pUserImage->SetPlayer(userID, k_EAvatarSize184x184);

    m_pUserName->SetText(SteamFriends()->GetFriendPersonaName(userID));

    g_pAPIRequests->GetUserStats(uID, UtlMakeDelegate(this, &UserComponent::OnUserDataReceived));

    InvalidateLayout();
}

void UserComponent::OnUserDataReceived(KeyValues* pKv)
{
    const auto pData = pKv->FindKey("data");
    const auto pErr = pKv->FindKey("error");
    if (pData)
    {
        const auto pUser = pData->FindKey("users", true)->FindKey("1");
        if (!pUser)
            return;

        m_pUserName->SetText(pUser->GetString("alias"));

        const auto pUserStats = pUser->FindKey("stats");
        if (!pUserStats)
            return;

        int curLvl = pUserStats->GetInt("level");
        int curXP = pUserStats->GetInt("CosXP");
        int xpForLvl = g_pXPSystem->GetCosmeticXPForLevel(curLvl + 1);
        float progress = (float)curXP / (float)xpForLvl;
        m_pXPProgressBar->SetProgress(progress);
        m_pXPProgressBar->GetTooltip()->SetText(CFmtStr("%i XP to Level %i", xpForLvl - curXP, curLvl + 1));

        m_pUserRank->SetVisible(true);
        m_pUserRank->SetText(CFmtStr("Level %i", curLvl));

        InvalidateLayout();
    }
    else if (pErr)
    {
        // MOM_TODO error handle
    }
}


void UserComponent::PerformLayout()
{
    BaseClass::PerformLayout();

    int pWide, pTall;
    GetSize(pWide, pTall);

    m_pUserImage->SetBounds(0, 0, pTall, pTall);
}

void UserComponent::ApplySchemeSettings(IScheme* pScheme)
{
    BaseClass::ApplySchemeSettings(pScheme);
}
