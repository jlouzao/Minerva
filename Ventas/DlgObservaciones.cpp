// DlgObservaciones.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgObservaciones.h"
#include ".\dlgobservaciones.h"


/************************************************************************************/
// Cuadro de diálogo de CDlgObservaciones
/************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgObservaciones, CDialog)
CDlgObservaciones::CDlgObservaciones(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObservaciones::IDD, pParent)
	, m_strObs(_T(""))
	, m_strObsCliente(_T(""))
{
	m_bReadOnly = FALSE;
}

/************************************************************************************/
CDlgObservaciones::~CDlgObservaciones()
{
}

/************************************************************************************/
void CDlgObservaciones::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OBSERVACIONES, m_strObs);
	DDV_MaxChars(pDX, m_strObs, 100);
	DDX_Text(pDX, IDC_OBS_CLIENTE, m_strObsCliente);
	DDX_Control(pDX, IDC_OBSERVACIONES, m_cObservaciones);
}


/************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgObservaciones, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/************************************************************************************/
// Controladores de mensajes de CDlgObservaciones
/************************************************************************************/

/************************************************************************************/
BOOL CDlgObservaciones::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_GRUPO_OBS)->SetWindowText(m_strTitulo.Trim());

	if (m_bReadOnly)
		m_cObservaciones.SetReadOnly();
	else
		GetDlgItem(IDC_OBSERVACIONES)->SetFocus();

	UpdateData(FALSE);

	return FALSE;
}

/******************************************************************************************/
void CDlgObservaciones::OnBnClickedOk()
{
	GetDlgItem(IDC_OBSERVACIONES)->GetWindowText(m_strObs);

	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgObservaciones::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgObservaciones::SetObservaciones(CString strObs)
{
	m_strObs = strObs;
}

/******************************************************************************************/
CString CDlgObservaciones::GetObservaciones()
{
	return m_strObs;
}

/******************************************************************************************/
void CDlgObservaciones::SetObsCliente(CString strObsCliente)
{
	m_strObsCliente = strObsCliente;
}

/******************************************************************************************/
void CDlgObservaciones::SetTitulo(CString strTitulo)
{
	m_strTitulo = strTitulo.Trim();
}

/******************************************************************************************/
void CDlgObservaciones::SetReadOnly()
{
	m_bReadOnly = TRUE;
}
