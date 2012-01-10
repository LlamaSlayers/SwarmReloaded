#include "cbase.h"
#include "modelentities.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CASW_Ceiling : public CFuncBrush
{
	DECLARE_CLASS( CASW_Ceiling, CFuncBrush );
public:
	CASW_Ceiling() {}
};

LINK_ENTITY_TO_CLASS( asw_ceiling, CASW_Ceiling );