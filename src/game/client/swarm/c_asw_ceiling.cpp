#include "cbase.h"
#include "c_asw_ceiling.h"
#include "mapentities_shared.h"
#include "datacache/imdlcache.h"
#include "gamestringpool.h"

CUtlVector<C_ASW_Ceiling *> g_ASWCeilings;

C_ASW_Ceiling::~C_ASW_Ceiling()
{
	g_ASWCeilings.FindAndRemove( this );
}

C_ASW_Ceiling *C_ASW_Ceiling::CreateNew( bool bForce )
{
	return new C_ASW_Ceiling();
}

void C_ASW_Ceiling::Spawn()
{
	SetSolid( SOLID_BBOX );
	SetModel( STRING( GetModelName() ) ); // set size and link into world
	AddFlag( FL_WORLDBRUSH );

	g_ASWCeilings.AddToTail( this );

	BaseClass::Spawn();

	m_takedamage = DAMAGE_NO;
}

bool C_ASW_Ceiling::Initialize()
{
	if ( InitializeAsClientEntity( NULL, false ) == false )
	{
		return false;
	}
	
	Spawn();

	const model_t *mod = GetModel();
	if ( mod )
	{
		Vector mins, maxs;
		modelinfo->GetModelBounds( mod, mins, maxs );
		SetCollisionBounds( mins, maxs );
	}

	SetBlocksLOS( false );
	SetNextClientThink( CLIENT_THINK_NEVER );

	return true;
}

void C_ASW_Ceiling::RecreateAll()
{
	DestroyAll();	
	ParseAllEntities( engine->GetMapEntitiesString() );
}

void C_ASW_Ceiling::DestroyAll()
{
	while (g_ASWCeilings.Count() > 0 )
	{
		C_ASW_Ceiling *p = g_ASWCeilings[0];
		p->Release();
	}
}

const char *C_ASW_Ceiling::ParseEntity( const char *pEntData )
{
	CEntityMapData entData( (char*)pEntData );
	char className[MAPKEY_MAXLENGTH];
	
	MDLCACHE_CRITICAL_SECTION();

	if (!entData.ExtractValue("classname", className))
	{
		Error( "classname missing from entity!\n" );
	}

	if ( !Q_strcmp( className, "asw_ceiling" ) )
	{
		// always force clientside entitis placed in maps
		C_ASW_Ceiling *pEntity = C_ASW_Ceiling::CreateNew( true ); 

		if ( pEntity )
		{	// Set up keyvalues.
			pEntity->ParseMapData(&entData);
			
			if ( !pEntity->Initialize() )
				pEntity->Release();
		
			return entData.CurrentBufferPosition();
		}
	}
	
	// Just skip past all the keys.
	char keyName[MAPKEY_MAXLENGTH];
	char value[MAPKEY_MAXLENGTH];
	if ( entData.GetFirstKey(keyName, value) )
	{
		do 
		{
		} 
		while ( entData.GetNextKey(keyName, value) );
	}

	//
	// Return the current parser position in the data block
	//
	return entData.CurrentBufferPosition();
}

//-----------------------------------------------------------------------------
// Purpose: Only called on BSP load. Parses and spawns all the entities in the BSP.
// Input  : pMapData - Pointer to the entity data block to parse.
//-----------------------------------------------------------------------------
void C_ASW_Ceiling::ParseAllEntities(const char *pMapData)
{
	int nEntities = 0;

	char szTokenBuffer[MAPKEY_MAXLENGTH];

	//
	//  Loop through all entities in the map data, creating each.
	//
	for ( ; true; pMapData = MapEntity_SkipToNextEntity(pMapData, szTokenBuffer) )
	{
		//
		// Parse the opening brace.
		//
		char token[MAPKEY_MAXLENGTH];
		pMapData = MapEntity_ParseToken( pMapData, token );

		//
		// Check to see if we've finished or not.
		//
		if (!pMapData)
			break;

		if (token[0] != '{')
		{
			Error( "C_ASW_Ceiling::ParseAllEntities: found %s when expecting {", token);
			continue;
		}

		//
		// Parse the entity and add it to the spawn list.
		//

		pMapData = ParseEntity( pMapData );

		nEntities++;
	}
}

bool C_ASW_Ceiling::ShouldDraw()
{
	return true;
}
