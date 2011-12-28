#ifndef _INCLUDED_C_ASW_OBJECTIVE_COUNTER_H
#define _INCLUDED_C_ASW_OBJECTIVE_COUNTER_H

#include "c_asw_objective.h"

class C_ASW_Objective_Counter : public C_ASW_Objective
{
public:
	DECLARE_CLASS( C_ASW_Objective_Counter, C_ASW_Objective );
	DECLARE_CLIENTCLASS();

	C_ASW_Objective_Counter();

	virtual const wchar_t* GetObjectiveTitle();
	virtual bool NeedsTitleUpdate();
	virtual float GetObjectiveProgress();

	CNetworkVar(int, m_iTargetCount);
	CNetworkVar(int, m_iCurrentCount);

	wchar_t *m_pCountText;
	bool m_bFoundText;

	wchar_t m_dest_buffer[64];
	int m_iCountLeft;

private:
	C_ASW_Objective_Counter( const C_ASW_Objective_Counter & ); // not defined, not accessible
};


#endif // _INCLUDED_C_ASW_OBJECTIVE_COUNTER_H