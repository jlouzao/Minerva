// DlgDatosPago.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgDatosPago.h"
#include ".\dlgdatospago.h"



// Cuadro de diálogo de CDlgDatosPago

IMPLEMENT_DYNAMIC(CDlgDatosPago, CDialog)
CDlgDatosPago::CDlgDatosPago(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDatosPago::IDD, pParent)
	, m_strDivisa(_T(""))
	, m_strFormaPago(_T(""))
	, m_strVencimientos(_T(""))
	, m_strPrimerVen(_T(""))
	, m_strEntre(_T(""))
	, m_strDias1(_T(""))
	, m_strDias2(_T(""))
	, m_strDias3(_T(""))
	, m_strBanco(_T(""))
	, m_strEntidad(_T(""))
	, m_strIban(_T(""))
	, m_strCC1(_T(""))
	, m_strCC2(_T(""))
	, m_strDC(_T(""))
	, m_strCC3(_T(""))
	, m_strDesFormaPago(_T(""))
	, m_strDesDivisa(_T(""))
	, m_strDesBanco(_T(""))
{
}

CDlgDatosPago::~CDlgDatosPago()
{
}

void CDlgDatosPago::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DIVISA, m_strDivisa);
	DDX_Text(pDX, IDC_FORMAPAGO, m_strFormaPago);
	DDX_Text(pDX, IDC_VENCIMIENTOS, m_strVencimientos);
	DDX_Text(pDX, IDC_PRIMER_VEN, m_strPrimerVen);
	DDX_Text(pDX, IDC_ENTRE, m_strEntre);
	DDX_Text(pDX, IDC_DIAS1, m_strDias1);
	DDX_Text(pDX, IDC_DIAS2, m_strDias2);
	DDX_Text(pDX, IDC_DIAS3, m_strDias3);
	DDX_Text(pDX, IDC_BANCO, m_strBanco);
	DDX_Text(pDX, IDC_ENTIDAD, m_strEntidad);
	DDV_MaxChars(pDX, m_strEntidad, 35);
	DDX_Text(pDX, IDC_IBAN, m_strIban);
	DDV_MaxChars(pDX, m_strIban, 24);
	DDX_Text(pDX, IDC_NCUENTACORRIENTE, m_strCC1);
	DDV_MaxChars(pDX, m_strCC1, 4);
	DDX_Text(pDX, IDC_NCUENTACORRIENTE2, m_strCC2);
	DDV_MaxChars(pDX, m_strCC2, 4);
	DDX_Text(pDX, IDC_NCUENTACORRIENTE3, m_strDC);
	DDV_MaxChars(pDX, m_strDC, 2);
	DDX_Text(pDX, IDC_NCUENTACORRIENTE4, m_strCC3);
	DDV_MaxChars(pDX, m_strCC3, 10);
	DDX_Text(pDX, IDC_DES_FORMAPAGO, m_strDesFormaPago);
	DDX_Text(pDX, IDC_DES_DIVISA, m_strDesDivisa);
	DDX_Text(pDX, IDC_DES_BANCO, m_strDesBanco);
	DDX_Control(pDX, IDC_DIVISA, m_ctrlDivisa);
	DDX_Control(pDX, IDC_FORMAPAGO, m_ctrlFormaPago);
	DDX_Control(pDX, IDC_BANCO, m_ctrlBanco);
}


BEGIN_MESSAGE_MAP(CDlgDatosPago, CDialog)
	ON_BN_CLICKED(IDC_BOTON_DIVISA, OnBnClickedBotonDivisa)
	ON_BN_CLICKED(IDC_BOTON_FORMAPAGO, OnBnClickedBotonFormapago)
	ON_BN_CLICKED(IDC_BOTON_BANCO, OnBnClickedBotonBanco)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_DIVISA, OnEnKillfocusDivisa)
	ON_EN_KILLFOCUS(IDC_FORMAPAGO, OnEnKillfocusFormapago)
	ON_EN_KILLFOCUS(IDC_BANCO, OnEnKillfocusBanco)
	ON_EN_CHANGE(IDC_PRIMER_VEN, OnEnChangePrimerVen)
END_MESSAGE_MAP()


/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
BOOL CDlgDatosPago::OnInitDialog()
{
	CDialog::OnInitDialog();
	/******* CARGA LAS BUSQUEDAS PARA AHORRAR TIEMPO ********/
	m_dlgBusquedaBanco.SetConexion(m_db); 
	m_dlgBusquedaDivisas.SetConexion(m_db);
	m_dlgBusquedaFormaPago.SetConexion(m_db);
	/******* CARGA LOS DATOS EN LOS CAMPOS ********/
	m_strDivisa=m_rsProve->m_DIVISA.TrimRight();
	if (!m_strDivisa.IsEmpty())
		BuscaDivisa(m_strDivisa);
	m_strFormaPago=m_rsProve->m_FCOBRO.TrimRight();
	if (!m_strFormaPago.IsEmpty())
		BuscaPago(m_strFormaPago);
	m_strVencimientos.Format("%.0f",m_rsProve->m_NCOBROS);
	m_strPrimerVen.Format("%.0f",m_rsProve->m_VTO1);
	m_strEntre.Format("%.0f",m_rsProve->m_DVTO);
	m_strDias1.Format("%.0f",m_rsProve->m_DIA1);
	m_strDias2.Format("%.0f",m_rsProve->m_DIA2);
	m_strDias3.Format("%.0f",m_rsProve->m_DIA3);
	m_strBanco=m_rsProve->m_CTABANCO.TrimRight();
	BuscaBanco(m_strBanco);
	if (!m_strBanco.IsEmpty())
		m_strEntidad=m_rsProve->m_NOMBCO.TrimRight();
	m_strIban=m_rsProve->m_IBAN.TrimRight();
	m_strCC1=m_rsProve->m_CC1.TrimRight();
	m_strCC2=m_rsProve->m_CC2.TrimRight();
	m_strDC=m_rsProve->m_DC.TrimRight();
	m_strCC3=m_rsProve->m_CTACORR.TrimRight();

	UpdateData(FALSE);
	
	return FALSE;
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::OnBnClickedBotonDivisa()
{
	INT_PTR Estado;
	m_dlgBusquedaDivisas.SetTipo(CDialogBusqueda::DIVISAS);
	Estado=m_dlgBusquedaDivisas.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strDivisa.TrimRight()=m_dlgBusquedaDivisas.GetCodigo();
	m_strDesDivisa.TrimRight()=m_dlgBusquedaDivisas.GetDescripcion();
	GetDlgItem(IDC_DIVISA)->SetWindowText(m_strDivisa);
	GetDlgItem(IDC_DES_DIVISA)->SetWindowText(m_strDesDivisa);
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::OnBnClickedBotonFormapago()
{
	INT_PTR Estado;
	m_dlgBusquedaFormaPago.SetTipo(CDialogBusqueda::FPAGCOB);
	Estado=m_dlgBusquedaFormaPago.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strFormaPago.TrimRight()=m_dlgBusquedaFormaPago.GetCodigo();
	m_strDesFormaPago.TrimRight()=m_dlgBusquedaFormaPago.GetDescripcion();
	GetDlgItem(IDC_FORMAPAGO)->SetWindowText(m_strFormaPago);
	GetDlgItem(IDC_DES_FORMAPAGO)->SetWindowText(m_strDesFormaPago);
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::OnBnClickedBotonBanco()
{
	INT_PTR Estado;
	m_dlgBusquedaBanco.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaBanco.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strBanco=m_dlgBusquedaBanco.GetCodigo();
	m_strDesBanco=m_dlgBusquedaBanco.GetDescripcion();
	GetDlgItem(IDC_BANCO)->SetWindowText(m_strBanco);
	GetDlgItem(IDC_DES_BANCO)->SetWindowText(m_strDesBanco);
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_rsProve->m_DIVISA=m_strDivisa;
	m_rsProve->m_FCOBRO=m_strFormaPago;
	m_rsProve->m_NCOBROS=atof(m_strVencimientos);
	m_rsProve->m_VTO1=atof(m_strPrimerVen);
	m_rsProve->m_DVTO=atof(m_strEntre);
	m_rsProve->m_DIA1=atof(m_strDias1);
	m_rsProve->m_DIA2=atof(m_strDias2);
	m_rsProve->m_DIA3=atof(m_strDias3); 
	m_rsProve->m_CTABANCO=m_strBanco;
	m_rsProve->m_NOMBCO=m_strEntidad;
	m_rsProve->m_IBAN=m_strIban;
	m_rsProve->m_CC1=m_strCC1;
	m_rsProve->m_CC2=m_strCC2;
	m_rsProve->m_DC=m_strDC;
	m_rsProve->m_CTACORR=m_strCC3;

	OnOK();
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::SetProve(CProve *rsProve )
{
	m_rsProve=rsProve;	
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsProve->m_pDatabase=m_db;
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::OnEnKillfocusDivisa()
{
	CString strAux=m_strDivisa;
	GetDlgItem(IDC_DIVISA)->GetWindowText(m_strDivisa);
	if (m_strDivisa.IsEmpty())
	{
		m_strDesDivisa.Empty();
		GetDlgItem(IDC_DES_DIVISA)->SetWindowText(m_strDesDivisa);
		return;
	}
	if (BuscaDivisa(m_strDivisa)==FALSE)
	{
		m_strDivisa=strAux;
		GetDlgItem(IDC_DIVISA)->SetWindowText(m_strDivisa.TrimRight());
		GetDlgItem(IDC_DES_DIVISA)->SetWindowText(m_strDesDivisa.TrimRight());
		m_ctrlDivisa.SetFocus();
	}
	else
	{	GetDlgItem(IDC_DES_DIVISA)->SetWindowText(m_strDesDivisa.TrimRight());	}
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::OnEnKillfocusFormapago()
{
	CString strAux=m_strFormaPago;
	GetDlgItem(IDC_FORMAPAGO)->GetWindowText(m_strFormaPago);
	if (m_strFormaPago.IsEmpty())
	{
		m_strDesFormaPago.Empty();
		GetDlgItem(IDC_DES_FORMAPAGO)->SetWindowText(m_strDesFormaPago);
		return;
	}
	if (BuscaPago(m_strFormaPago)==FALSE)
	{
		m_strFormaPago=strAux;
		GetDlgItem(IDC_FORMAPAGO)->SetWindowText(m_strFormaPago.TrimRight());
		GetDlgItem(IDC_DES_FORMAPAGO)->SetWindowText(m_strDesFormaPago.TrimRight());
		m_ctrlFormaPago.SetFocus();
	}
	else
	{	GetDlgItem(IDC_DES_FORMAPAGO)->SetWindowText(m_strDesFormaPago.TrimRight());	}
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
void CDlgDatosPago::OnEnKillfocusBanco()
{
	CString strAux=m_strBanco;
	GetDlgItem(IDC_BANCO)->GetWindowText(m_strBanco);
	if (m_strBanco.IsEmpty())
	{
		m_strDesBanco.Empty();
		GetDlgItem(IDC_DES_BANCO)->SetWindowText(m_strDesBanco);
		return;
	}
	if (BuscaBanco(m_strBanco)==FALSE)
	{
		m_strBanco=strAux;
		GetDlgItem(IDC_BANCO)->SetWindowText(m_strBanco.TrimRight());
		GetDlgItem(IDC_DES_BANCO)->SetWindowText(m_strDesBanco.TrimRight());
		m_ctrlBanco.SetFocus();
	}
	else
	{	GetDlgItem(IDC_DES_BANCO)->SetWindowText(m_strDesBanco.TrimRight());	}
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
BOOL CDlgDatosPago::BuscaDivisa(CString cadena)
{
	CDivisas rsDivisa(m_db);
	rsDivisa.m_strFilter="DIVISA LIKE '" + cadena + "'";//filtro de busqueda
	if (!rsDivisa.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsDivisa.m_DDIVISA.IsEmpty())//no existe el registro
	{	
		return FALSE;
	}
	else//existe
	{	
		m_strDesDivisa=rsDivisa.m_DDIVISA.TrimRight();
		return TRUE;
	}
	rsDivisa.Close();
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
BOOL CDlgDatosPago::BuscaBanco(CString cadena)
{
	CCuentas rsCuenta(m_db);
	rsCuenta.m_strFilter="CUENTA LIKE '" + cadena + "'";//filtro de busqueda
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsCuenta.m_CUENTA.IsEmpty())//no existe el registro
	{	return FALSE;	}
	else//existe
	{	
		m_strDesBanco=rsCuenta.m_NOMBRE.TrimRight();
		return TRUE;
	}
	rsCuenta.Close();
}
/*********************************************************************************************************/
/***                                                                                                   ***/
/*********************************************************************************************************/
BOOL CDlgDatosPago::BuscaPago(CString cadena)
{
	CFPagCob rsPago(m_db);
	rsPago.m_strFilter="FCOBRO LIKE '" + cadena + "'";//filtro de busqueda
	if (!rsPago.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsPago.m_FCOBRO.IsEmpty())//no existe el registro
	{	
		return FALSE;
	}
	else//existe
	{	
		m_strDesFormaPago=rsPago.m_DFCOBRO.TrimRight();
		return TRUE;
	}
	rsPago.Close();
}
void CDlgDatosPago::OnEnChangePrimerVen()
{
	// TODO:  Si éste es un control RICHEDIT, el control no
	// enviará esta notificación a menos que se anule la función CDialog::OnInitDialog()
	// y se llame a CRichEditCtrl().SetEventMask()
	// con el indicador ENM_CHANGE ORed en la máscara.

	// TODO:  Agregue aquí el controlador de notificación de controles
}
