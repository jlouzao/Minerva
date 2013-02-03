// DlgPreparacionAlbaran.cpp: archivo de implementación
//
/******************************************************************************************/

#include "stdafx.h"
#include "DlgPreparacionAlbaran.h"
#include ".\dlgpreparacionalbaran.h"
#include "DlgPreAlbEntrega.h"
#include "DlgPreAlbRecogida.h"
#include "DlgPreAlbDespieceEntrega.h"
#include "DlgPreAlbDespieceRecogida.h"

#define PRE_ALB_ENTREGA    0
#define PRE_ALB_RECOGIDA   1
#define PRE_ALB_DESPIECE_ENTREGA   2
#define PRE_ALB_DESPIECE_RECOGIDA  3

/******************************************************************************************/
// Cuadro de diálogo de CDlgPreparacionAlbaran
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgPreparacionAlbaran, CDialog)
CDlgPreparacionAlbaran::CDlgPreparacionAlbaran(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreparacionAlbaran::IDD, pParent)
	, m_iTipoAlb(0)
{
}

/******************************************************************************************/
CDlgPreparacionAlbaran::~CDlgPreparacionAlbaran()
{
}

/******************************************************************************************/
void CDlgPreparacionAlbaran::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RBTN_ENTREGA, m_iTipoAlb);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgPreparacionAlbaran, CDialog)
	ON_BN_CLICKED(IDC_RBTN_ENTREGA, OnBnClickedRbtnEntrega)
	ON_BN_CLICKED(IDC_RBTN_RECOGIDA, OnBnClickedRbtnRecogida)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_RBTN_DESPIECE, OnBnClickedRbtnDespiece)
	ON_BN_CLICKED(IDC_RBTN_DESPIECE_RECOGIDA, OnBnClickedRbtnDespieceRecogida)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgPreparacionAlbaran
/******************************************************************************************/

/***********************************************************************************************/
BOOL CDlgPreparacionAlbaran::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_iTipoAlb = PRE_ALB_ENTREGA;

	UpdateData(FALSE);

	return TRUE;
}

/******************************************************************************************/
void CDlgPreparacionAlbaran::OnBnClickedRbtnEntrega()
{
	m_iTipoAlb = PRE_ALB_ENTREGA;
}

/******************************************************************************************/
void CDlgPreparacionAlbaran::OnBnClickedRbtnRecogida()
{
	m_iTipoAlb = PRE_ALB_RECOGIDA;
}

/******************************************************************************************/
void CDlgPreparacionAlbaran::OnBnClickedRbtnDespiece()
{
	m_iTipoAlb = PRE_ALB_DESPIECE_ENTREGA;
}

/******************************************************************************************/
void CDlgPreparacionAlbaran::OnBnClickedRbtnDespieceRecogida()
{
	m_iTipoAlb = PRE_ALB_DESPIECE_RECOGIDA;
}

/******************************************************************************************/
void CDlgPreparacionAlbaran::OnBnClickedOk()
{
	if (m_iTipoAlb == PRE_ALB_ENTREGA)
	{
		CDlgPreAlbEntrega dlgPreAlbEntrega;
		dlgPreAlbEntrega.SetConexion(m_db);
		dlgPreAlbEntrega.DoModal();
	}
	else if (m_iTipoAlb == PRE_ALB_RECOGIDA)
	{
		CDlgPreAlbRecogida dlgPreAlbRecogida;
		dlgPreAlbRecogida.SetConexion(m_db);
		dlgPreAlbRecogida.DoModal();
	}
	else if (m_iTipoAlb == PRE_ALB_DESPIECE_ENTREGA)
	{
		CDlgPreAlbDespieceEntrega dlgPreAlbDespiece;
		dlgPreAlbDespiece.SetConexion(m_db);
		dlgPreAlbDespiece.DoModal();
	}
	else if (m_iTipoAlb == PRE_ALB_DESPIECE_RECOGIDA)
	{
		CDlgPreAlbDespieceRecogida dlgPreAlbDespieceRecogida;
		dlgPreAlbDespieceRecogida.SetConexion(m_db);
		dlgPreAlbDespieceRecogida.DoModal();
	}

	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgPreparacionAlbaran::SetConexion(CDatabase *db)
{
	m_db = db;
}




