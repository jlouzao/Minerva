#include "stdafx.h"
#include "Contabilidad.h"
#include "DlgEleccionObra.h"
#include ".\dlgeleccionobra.h"


// Cuadro de diálogo de CDlgEleccionObra

IMPLEMENT_DYNAMIC(CDlgEleccionObra, CDialog)
CDlgEleccionObra::CDlgEleccionObra(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEleccionObra::IDD, pParent)
	, m_strObra(_T(""))
	, m_strDesObra(_T(""))
{
}

CDlgEleccionObra::~CDlgEleccionObra()
{
}

void CDlgEleccionObra::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OBRA, m_ctrlObra);
	DDX_Text(pDX, IDC_OBRA, m_strObra);
	DDV_MaxChars(pDX, m_strObra, 3);
	DDX_Text(pDX, IDC_DES_OBRA, m_strDesObra);
}


BEGIN_MESSAGE_MAP(CDlgEleccionObra, CDialog)
	ON_EN_KILLFOCUS(IDC_OBRA, OnEnKillfocusObra)
	ON_BN_CLICKED(IDC_BUSCAR_OBRA, OnBnClickedBuscarObra)
END_MESSAGE_MAP()


/*******************************************************************************************************/
BOOL CDlgEleccionObra::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgBusquedaDirEnv.SetConexion(m_db);

	return FALSE;
}
/*******************************************************************************************************/
void CDlgEleccionObra::SetCliente(CString strAux)
{
	strCliente=strAux;
}
/*******************************************************************************************************/
void CDlgEleccionObra::SetConexion(CDatabase *db)
{
	m_db=db;
}
/*******************************************************************************************************/
void CDlgEleccionObra::OnEnKillfocusObra()
{
	CString strAux=m_strObra;
	GetDlgItem(IDC_OBRA)->GetWindowText(m_strObra);
	if (m_strObra.IsEmpty())
	{return;}
	CDirEnv rsDirEnv(m_db);
	rsDirEnv.m_strFilter="CLIENTE LIKE '" + strCliente + "' AND DIRENV LIKE '" + m_strObra + "'" ;
	if (!rsDirEnv.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}
	if (rsDirEnv.m_DIRENV.IsEmpty())
	{
		m_strObra=strAux;
		GetDlgItem(IDC_OBRA)->SetWindowText(m_strObra);
	}
	else
	{
		m_strDesObra=rsDirEnv.m_NOMDIRENV.TrimRight();
		GetDlgItem(IDC_DES_OBRA)->SetWindowText(m_strDesObra);
	}
}
/*******************************************************************************************************/
void CDlgEleccionObra::OnBnClickedBuscarObra()
{
	INT_PTR Estado;
	m_dlgBusquedaDirEnv.SetTipo(CDialogBusqueda::DIRENV);
	Estado=m_dlgBusquedaDirEnv.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strObra=m_dlgBusquedaDirEnv.GetCodigo();
	GetDlgItem(IDC_OBRA)->SetWindowText(m_strObra);
	m_strDesObra=m_dlgBusquedaDirEnv.GetDescripcion();
	GetDlgItem(IDC_DES_OBRA)->SetWindowText(m_strDesObra);
}
