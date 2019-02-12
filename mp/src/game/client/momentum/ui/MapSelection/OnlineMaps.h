#pragma once

#include "BaseMapsPage.h"

//-----------------------------------------------------------------------------
// Purpose: Internet games list
//-----------------------------------------------------------------------------
class COnlineMaps : public CBaseMapsPage
{

    DECLARE_CLASS_SIMPLE(COnlineMaps, CBaseMapsPage);

public:
    COnlineMaps(Panel *parent, const char *panelName = "OnlineMaps");
    ~COnlineMaps();

    // property page handlers
    virtual void OnPageShow();

    MapListType_e GetMapListType() OVERRIDE { return MAP_LIST_BROWSE; }

    // gets a new server list
    MESSAGE_FUNC(GetNewMapList, "GetNewMapList");

    enum EMapQueryOutputs
    {
        eNoMapsReturned,
        eNoServerReturn,
        eServerBadReturn,
        eSuccess
    };

    void RefreshComplete(EMapQueryOutputs response);

    void MapsQueryCallback(KeyValues* pKvResponse);

    void FillMapList();

protected:
    // vgui overrides
    virtual void PerformLayout();
private:
    bool m_bRequireUpdate;	// checks whether we need an update upon opening
    bool m_bOfflineMode;
    int m_iCurrentPage;
};