//--------------------------------------------------------------------------------------------------------
// Copyright (c) 2007 Turtle Rock Studios, Inc.

#if !defined( C_BASETOGGLE_H )
#define C_BASETOGGLE_H

#ifdef _WIN32
#pragma once
#endif

#include "c_baseentity.h"
#include "iasw_client_usable_entity.h"
#include "glow_outline_effect.h"

//--------------------------------------------------------------------------------------------------------
class C_BaseToggle: public C_BaseEntity
{
public:
	DECLARE_CLASS( C_BaseToggle, C_BaseEntity );
	DECLARE_CLIENTCLASS();

	virtual void GetGroundVelocityToApply( Vector &vecGroundVel );
};


//--------------------------------------------------------------------------------------------------------
class C_BaseButton: public C_BaseToggle, public IASW_Client_Usable_Entity
{
public:
	DECLARE_CLASS( C_BaseButton, C_BaseToggle );
	DECLARE_CLIENTCLASS();

	C_BaseButton();

	virtual bool IsPotentiallyUsable( void );

	// IASW_Client_Usable_Entity
	virtual C_BaseEntity* GetEntity() { return this; }
	virtual bool IsUsable( C_BaseEntity *pUser );
	virtual bool GetUseAction( ASWUseAction &action, C_ASW_Marine *pUser );
	virtual void CustomPaint( int ix, int iy, int alpha, vgui::Panel *pUseIcon ) {}
	virtual bool ShouldPaintBoxAround() { return true; }
	virtual bool NeedsLOSCheck() { return true; }
	virtual void OnDataChanged( DataUpdateType_t updateType );
	void ClientThink();
	CGlowObject m_GlowObject;
	static int s_nUseActionIconTextureID;

private:
	bool m_usable;
};


#endif // C_BASETOGGLE_H