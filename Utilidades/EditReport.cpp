// EditReport.cpp: archivo de implementación
//

#include "stdafx.h"
#include "EditReport.h"

// CEditReport

IMPLEMENT_DYNAMIC(CEditReport, CEdit)
CEditReport::CEditReport()
{
}

CEditReport::~CEditReport()
{
}


BEGIN_MESSAGE_MAP(CEditReport, CEdit)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnEnKillfocus)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnEnSetfocus)
END_MESSAGE_MAP()


void CEditReport::OnEnKillfocus()
{
	GetParent()->SendMessage (WM_KILLFOCUS);
}

void CEditReport::OnEnSetfocus()
{
	GetParent()->SendMessage (WM_SETFOCUS);
}

// Controladores de mensajes de CEditReport

