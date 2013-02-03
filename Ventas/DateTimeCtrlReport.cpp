// EditReport.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DateTimeCtrlReport.h"

// CDateTimeCtrlReport

IMPLEMENT_DYNAMIC(CDateTimeCtrlReport, CDateTimeCtrl)
CDateTimeCtrlReport::CDateTimeCtrlReport()
{
}

CDateTimeCtrlReport::~CDateTimeCtrlReport()
{
}


BEGIN_MESSAGE_MAP(CDateTimeCtrlReport, CDateTimeCtrl)
	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnNMKillfocus)
	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnNMSetfocus)
END_MESSAGE_MAP()


void CDateTimeCtrlReport::OnNMKillfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	GetParent()->SendMessage (WM_KILLFOCUS);
}


void CDateTimeCtrlReport::OnNMSetfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	GetParent()->SendMessage (WM_SETFOCUS);
}

// Controladores de mensajes de CDateTimeCtrlReport

