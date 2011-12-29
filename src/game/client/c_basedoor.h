//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
#if !defined( C_BASEDOOR_H )
#define C_BASEDOOR_H
#ifdef _WIN32
#pragma once
#endif

#include "c_baseentity.h"
#include "c_basetoggle.h"
#include "iasw_client_usable_entity.h"
#include "glow_outline_effect.h"

#if defined( CLIENT_DLL )
#define CBaseDoor C_BaseDoor
#endif

class C_BaseDoor : public C_BaseToggle, public IASW_Client_Usable_Entity
{
public:
	DECLARE_CLASS( C_BaseDoor, C_BaseToggle );
	DECLARE_CLIENTCLASS();

	C_BaseDoor( void );
	~C_BaseDoor( void );

	static int s_nUseActionIconTextureIDLocked;
	static int s_nUseActionIconTextureIDUnlocked;

	// IASW_Client_Usable_Entity
	virtual C_BaseEntity* GetEntity() { return this; }
	virtual bool IsUsable( C_BaseEntity *pUser );
	virtual bool GetUseAction( ASWUseAction &action, C_ASW_Marine *pUser );
	virtual void CustomPaint( int ix, int iy, int alpha, vgui::Panel *pUseIcon ) {}
	virtual bool ShouldPaintBoxAround() { return false; }
	virtual bool NeedsLOSCheck() { return true; }
	virtual void OnDataChanged( DataUpdateType_t updateType );
	void ClientThink();
	CGlowObject m_GlowObject;

	float		m_flWaveHeight;
	bool		m_bLocked;
};

#endif // C_BASEDOOR_H
