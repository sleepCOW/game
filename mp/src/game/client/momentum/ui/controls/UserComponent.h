#pragma once
#include "vgui_controls/EditablePanel.h"

class CAvatarImagePanel;

class UserComponent : public vgui::EditablePanel
{
public:
    DECLARE_CLASS_SIMPLE(UserComponent, EditablePanel);
    UserComponent(Panel *pParent);

    void SetUser(uint64 uID);

    void OnUserDataReceived(KeyValues *pKv);

protected:
    void PerformLayout() override;
    void ApplySchemeSettings(vgui::IScheme* pScheme) override;


private:
    CAvatarImagePanel *m_pUserImage;
    vgui::Label *m_pUserName, *m_pUserRank;
    vgui::ProgressBar *m_pXPProgressBar;

    uint64 m_uUID;
};