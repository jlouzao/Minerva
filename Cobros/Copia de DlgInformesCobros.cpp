// DlgInformesCobros.cpp: archivo de implementaci�n
//

#include "stdafx.h"
#include "Cobros.h"
#include "DlgInformesCobros.h"


// Cuadro de di�logo de CDlgInformesCobros

IMPLEMENT_DYNAMIC(CDlgInformesCobros, CDialog)
CDlgInformesCobros::CDlgInformesCobros(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInformesCobros::IDD, pParent)
{
}

CDlgInformesCobros::~CDlgInformesCobros()
{
}

void CDlgInformesCobros::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgInformesCobros, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgInformesCobros
