#ifndef ASW_CAMERA_CONTROL_H
#define ASW_CAMERA_CONTROL_H

class CASW_Camera_Control_Dummy : public CServerOnlyEntity
{
	DECLARE_CLASS( CASW_Camera_Control_Dummy, CServerOnlyEntity );
	DECLARE_DATADESC();
public:
	float m_fYaw;
};

#endif