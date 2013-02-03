// DlgDatosCobro.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgDatosCobro.h"
#include ".\dlgdatoscobro.h"
#include "BD.h"


/******************************************************************************************/
// Cuadro de diálogo de CDlgDatosCobro
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgDatosCobro, CDialog)
CDlgDatosCobro::CDlgDatosCobro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDatosCobro::IDD, pParent)
	, m_strFCobro(_T(""))
	, m_strDesFCobro(_T(""))
	, m_dNumCobros(0)
	, m_d1Vto(0)
	, m_dDiasVto(0)
	, m_dDiasPago1(0)
	, m_dDiasPago2(0)
	, m_dDiasPago3(0)
//	, m_strRetCom(_T(""))
	, m_strRetFiscal(_T(""))
{
	m_bReadOnly = FALSE;
}

/******************************************************************************************/
CDlgDatosCobro::~CDlgDatosCobro()
{
}

/******************************************************************************************/
void CDlgDatosCobro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FCOBRO, m_strFCobro);
	DDV_MaxChars(pDX, m_strFCobro, 1);
	DDX_Text(pDX, IDC_EDIT_DESFCOBRO, m_strDesFCobro);
	DDX_Text(pDX, IDC_EDIT_NUMCOBROS, m_dNumCobros);
	DDX_Text(pDX, IDC_EDIT_1VTO, m_d1Vto);
	DDX_Text(pDX, IDC_EDIT_DIAS_VTO, m_dDiasVto);
	DDX_Text(pDX, IDC_EDIT_DIAS_PAGO1, m_dDiasPago1);
	DDX_Text(pDX, IDC_EDIT_DIAS_PAGO2, m_dDiasPago2);
	DDX_Text(pDX, IDC_EDIT_DIAS_PAGO3, m_dDiasPago3);
	//	DDX_Text(pDX, IDC_EDIT_RET_COMERCIAL, m_strRetCom);
	DDX_Text(pDX, IDC_EDIT_RET_FISCAL, m_strRetFiscal);
	//	DDX_Control(pDX, IDC_EDIT_RET_COMERCIAL, m_cRetComercial);
	DDX_Control(pDX, IDC_EDIT_RET_FISCAL, m_cRetFiscal);
	DDX_Control(pDX, IDC_EDIT_FCOBRO, m_cFCobro);
	DDX_Control(pDX, IDC_EDIT_NUMCOBROS, m_cNumCobros);
	DDX_Control(pDX, IDC_EDIT_1VTO, m_c1Vto);
	DDX_Control(pDX, IDC_EDIT_DIAS_VTO, m_cDiasVto);
	DDX_Control(pDX, IDC_EDIT_DIAS_PAGO1, m_cDiasPago1);
	DDX_Control(pDX, IDC_EDIT_DIAS_PAGO2, m_cDiasPago2);
	DDX_Control(pDX, IDC_EDIT_DIAS_PAGO3, m_cDiasPago3);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgDatosCobro, CDialog)
	ON_BN_CLICKED(IDC_BTN_FCOBRO, OnBnClickedBtnFcobro)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT_FCOBRO, OnEnKillfocusEditFcobro)
//	ON_EN_KILLFOCUS(IDC_EDIT_RET_COMERCIAL, OnEnKillfocusEditRetComercial)
	ON_EN_KILLFOCUS(IDC_EDIT_RET_FISCAL, OnEnKillfocusEditRetFiscal)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgDatosCobro
/******************************************************************************************/

/******************************************************************************************/
BOOL CDlgDatosCobro::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strFCobro = m_datosCobro->m_FCOBRO;
	if (!m_strFCobro.IsEmpty())
		BuscaFCobro();

	m_dNumCobros = m_datosCobro->m_NCOBROS;
	m_d1Vto = m_datosCobro->m_VTO1;
	m_dDiasVto = m_datosCobro->m_DVTO;
	m_dDiasPago1 = m_datosCobro->m_DIA1;
	m_dDiasPago2 = m_datosCobro->m_DIA2;
	m_dDiasPago3 = m_datosCobro->m_DIA3;
//	m_strRetCom.Format("%g", m_datosCobro->m_RETENCOM);
	m_strRetFiscal.Format("%g", m_datosCobro->m_RETENFIS);

	// Se establecen la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaFCobros.SetConexion(m_db);

	if (m_bReadOnly)
	{
		m_cFCobro.SetReadOnly();
		m_cNumCobros.SetReadOnly();
		m_c1Vto.SetReadOnly();
		m_cDiasVto.SetReadOnly();
		m_cDiasPago1.SetReadOnly();
		m_cDiasPago2.SetReadOnly();
		m_cDiasPago3.SetReadOnly();
		m_cRetFiscal.SetReadOnly();

		GetDlgItem(IDC_BTN_FCOBRO)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);

	return FALSE;
}

/******************************************************************************************/
void CDlgDatosCobro::OnBnClickedBtnFcobro()
{
	INT_PTR status;

	m_dlgBusquedaFCobros.SetTipo(CDialogBusqueda::FPAGCOB);
	status = m_dlgBusquedaFCobros.DoModal();
	if (status == IDOK)
	{
		m_strFCobro = m_dlgBusquedaFCobros.GetCodigo();
		m_strDesFCobro = m_dlgBusquedaFCobros.GetDescripcion();
	}

	GetDlgItem(IDC_EDIT_FCOBRO)->SetWindowText(m_strFCobro);
	GetDlgItem(IDC_EDIT_DESFCOBRO)->SetWindowText(m_strDesFCobro);
}

/******************************************************************************************/
void CDlgDatosCobro::OnBnClickedOk()
{
	UpdateData();

	m_datosCobro->m_FCOBRO = m_strFCobro;
	m_datosCobro->m_NCOBROS = m_dNumCobros;
	m_datosCobro->m_VTO1 = m_d1Vto;
	m_datosCobro->m_DVTO = m_dDiasVto;
	m_datosCobro->m_DIA1 = m_dDiasPago1;
	m_datosCobro->m_DIA2 = m_dDiasPago2;
	m_datosCobro->m_DIA3 = m_dDiasPago3;
//	m_datosCobro->m_RETENCOM = atof(m_strRetCom);
	m_datosCobro->m_RETENFIS = atof(m_strRetFiscal);

	OnOK();
}

/******************************************************************************************/
void CDlgDatosCobro::OnEnKillfocusEditFcobro()
{
	CString strOldFCobro = m_strFCobro;

	GetDlgItem(IDC_EDIT_FCOBRO)->GetWindowText(m_strFCobro);

	if (!m_strFCobro.IsEmpty())
	{
		// Si la forma de cobro no existe se deja el anterior y se da un mensaje de error
		if (!BuscaFCobro())
		{
			AfxMessageBox(IDC_FCOBRO_NO_EXISTS);
			m_strFCobro = strOldFCobro;
			GetDlgItem(IDC_EDIT_FCOBRO)->SetWindowText(m_strFCobro);
		}
	}
	else
	{
		m_strDesFCobro.Empty();
		GetDlgItem(IDC_EDIT_DESFCOBRO)->SetWindowText(m_strDesFCobro);
	}
}

/******************************************************************************************/
/*void CDlgDatosCobro::OnEnKillfocusEditRetComercial()
{
	CString strRetComAux;

	GetDlgItem(IDC_EDIT_RET_COMERCIAL)->GetWindowText(strRetComAux);
	if (!CompruebaNumero(strRetComAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		GetDlgItem(IDC_EDIT_RET_COMERCIAL)->SetWindowText(m_strRetCom);
		m_cRetComercial.SetFocus();
		return;
	}
	else
		m_strRetCom = strRetComAux;
}
*/

/******************************************************************************************/
void CDlgDatosCobro::OnEnKillfocusEditRetFiscal()
{
	CString strRetFiscalAux;

	GetDlgItem(IDC_EDIT_RET_FISCAL)->GetWindowText(strRetFiscalAux);
	if (!CompruebaNumero(strRetFiscalAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		GetDlgItem(IDC_EDIT_RET_FISCAL)->SetWindowText(m_strRetFiscal);
		m_cRetFiscal.SetFocus();
		return;
	}
	else
		m_strRetFiscal = strRetFiscalAux;
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgDatosCobro::SetDatosCobro(CDatosCobro *datosCobro)
{
	m_datosCobro = datosCobro;
}

/****************************************************************************/
void CDlgDatosCobro::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgDatosCobro::SetReadOnly()
{
	m_bReadOnly = TRUE;
}

/******************************************************************************************/
BOOL CDlgDatosCobro::BuscaFCobro()
{
	BOOL bExists = FALSE;
	CFPagCob rsFPagCob(m_db);

	rsFPagCob.m_strFilter = "FCOBRO LIKE '" + m_strFCobro + "'";
	if (!rsFPagCob.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la forma de cobro existe se rellena la descripción 
	if (!rsFPagCob.m_FCOBRO.IsEmpty())
	{
		m_strDesFCobro = rsFPagCob.m_DFCOBRO.Trim();
		bExists = TRUE;
	}

	rsFPagCob.Close();

	UpdateData(FALSE);

	return bExists;
}

/************************************************************************************************************/
/** Comprueba que en la cadena no hay mas que números y como mucho un punto                                **/    
/************************************************************************************************************/
BOOL CDlgDatosCobro::CompruebaNumero(CString strNumero)
{
	BOOL bPunto = FALSE; 

	for (int i = 0; i<strNumero.GetLength(); i++)
	{
		if (strNumero.GetAt(i) < '0' || strNumero.GetAt(i) > '9')
		{ 
			if (strNumero.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}

	return TRUE;
}
