// D.cpp: archivo de implementaci�n
//

#include "stdafx.h"
#include "Utilidades.h"
#include "D.h"


// Cuadro de di�logo de D

IMPLEMENT_DYNAMIC(D, CDialog)
D::D(CWnd* pParent /*=NULL*/)
	: CDialog(D::IDD, pParent)
{
}

D::~D()
{
}

void D::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(D, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de D
