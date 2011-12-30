#ifndef _INCLUDED_C_ASW_CEILING_H
#define _INCLUDED_C_ASW_CEILING_H
#ifdef _WIN32
#pragma once
#endif

class C_ASW_Ceiling : public C_BaseEntity
{
public:
	DECLARE_CLASS( C_ASW_Ceiling, C_BaseEntity );

	C_ASW_Ceiling() {}

	bool Initialize();
	void Spawn();
	bool ShouldDraw();

	static void RecreateAll(); // recreate all clientside snow volumes in map
	static void DestroyAll();  // clear all clientside created snow volumes	
	static C_ASW_Ceiling *CreateNew(bool bForce = false);

protected:
	static const char *ParseEntity( const char *pEntData );
	static void ParseAllEntities(const char *pMapData);
};

#endif // _INCLUDED_C_ASW_CEILING_H