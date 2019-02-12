//========= Copyright � 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================
#pragma once

#include "IMapList.h"
#include "vgui_controls/PropertyPage.h"

class MapFilterPanel;
class CMapListPanel;
struct MapData;

// Map keynames
#define KEYNAME_MAP_ID "id"
#define KEYNAME_MAP_NAME "name"
#define KEYNAME_MAP_HASH "hash"
#define KEYNAME_MAP_TIME "time"
#define KEYNAME_MAP_TYPE "MapType"
#define KEYNAME_MAP_STATUS "MapStatus"
#define KEYNAME_MAP_ZONE_COUNT "numZones"
#define KEYNAME_MAP_LAYOUT "MapLayout"
#define KEYNAME_MAP_DIFFICULTY "difficulty"
#define KEYNAME_MAP_WORLD_RECORD "WorldRecord"
#define KEYNAME_MAP_IMAGE "MapImage"
#define KEYNAME_MAP_PATH "MapPath"

//-----------------------------------------------------------------------------
// Purpose: Base property page for all the games lists (internet/favorites/lan/etc.)
//-----------------------------------------------------------------------------
class CBaseMapsPage : public vgui::PropertyPage, public IMapList, public CGameEventListener
{
    DECLARE_CLASS_SIMPLE(CBaseMapsPage, vgui::PropertyPage);

public:
    CBaseMapsPage(Panel *parent, const char *name);
    ~CBaseMapsPage();

    virtual void PerformLayout();
    virtual void ApplySchemeSettings(vgui::IScheme *pScheme);

    virtual void SetListCellColors(MapData *pData, KeyValues *pKvInto);

    // Called by CGameList when the enter key is pressed.
    // This is overridden in the add server dialog - since there is no Connect button, the message
    // never gets handled, but we want to add a server when they dbl-click or press enter.
    virtual bool OnGameListEnterPressed();

    int GetSelectedItemsCount();

    // Filters
    // loads filter settings from disk
    virtual void LoadFilters();
    virtual KeyValues *GetFilters();
    void ApplyFilters(KeyValues *pFilters) OVERRIDE;
    virtual bool MapPassesFilters(MapData *pData, KeyValues *pFilters);

    void FireGameEvent(IGameEvent* event) OVERRIDE;
protected:
    virtual void OnCommand(const char *command);
    
    MESSAGE_FUNC(OnItemSelected, "ItemSelected");

    // updates map count
    void UpdateStatus();

    virtual void AddMapToList(MapData *pData);
    void UpdateMapListData(MapDisplay_t *pMap, bool bMain, bool bInfo, bool bPB, bool bWR, bool bThumbnail);

    // Removes map from list
    void RemoveMap(MapDisplay_t&);

    //Clears the list of maps
    void ClearMapList();

    virtual int GetInvalidMapListID();
    MapDisplay_t *GetMapDisplayByID(uint32 id);

    virtual void GetNewMapList();
    virtual void OnPageShow();
    virtual void OnPageHide();

    // Called when map should be started
    MESSAGE_FUNC_INT(OnMapStart, "StartMap", id);
    // called to look at map info
    MESSAGE_FUNC_INT(OnViewMapInfo, "ViewMapInfo", id);
    // Called when map should be added to/removed from library
    MESSAGE_FUNC_INT(OnAddMapToLibrary, "AddToLibrary", id);
    MESSAGE_FUNC_INT(OnRemoveFromLibrary, "RemoveFromLibrary", id);
    // Called when map should be added to/removed from favorites
    MESSAGE_FUNC_INT(OnAddToFavorites, "AddToFavorites", id);
    MESSAGE_FUNC_INT(OnRemoveFromFavorites, "RemoveFromFavorites", id);
    // Right clicking a map
    MESSAGE_FUNC_INT(OnOpenContextMenu, "OpenContextMenu", itemID);

    // If true, then we automatically select the first item that comes into the games list.
    bool m_bAutoSelectFirstItemInGameList;

    CMapListPanel *m_pMapList;

    CUtlVector<MapDisplay_t> m_vecMaps;

    int m_iOnlineMapsCount;

private:
    vgui::HFont m_hFont;

    typedef enum
    {
        HEADER_MAP_IMAGE = 0,
        HEADER_MAP_NAME,
        HEADER_MAP_LAYOUT,
        HEADER_DIFFICULTY,
        HEADER_WORLD_RECORD,
        HEADER_BEST_TIME
    } HEADERS;

};