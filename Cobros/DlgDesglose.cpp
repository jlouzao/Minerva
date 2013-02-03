// DlgDesglose.cpp: archivo de implementación
//
/******************************************************************************************/

#include "stdafx.h"
#include "DlgDesglose.h"
#include ".\dlgdesglose.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgDesglose
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgDesglose, CDialog)
CDlgDesglose::CDlgDesglose(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDesglose::IDD, pParent)
	, m_strNumEfec(_T(""))
	, m_strNumEfec2(_T(""))
	, m_strNumEfec3(_T(""))
	, m_strFCobro(_T(""))
	, m_strDesFCobro(_T(""))
	, m_strImporte(_T(""))
	, m_fechaVenci(0)
	, m_strObservaciones(_T(""))
	, m_fechaRecep()
{
}

/******************************************************************************************/
CDlgDesglose::~CDlgDesglose()
{
}

/******************************************************************************************/
void CDlgDesglose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUMEFEC, m_strNumEfec);
	DDX_Text(pDX, IDC_EDIT_NUMEFEC2, m_strNumEfec2);
	DDX_Text(pDX, IDC_EDIT_NUMEFEC3, m_strNumEfec3);
	DDX_Text(pDX, IDC_EDIT_FCOBRO, m_strFCobro);
	DDV_MaxChars(pDX, m_strFCobro, 3);
	DDX_Text(pDX, IDC_EDIT_DESFCOBRO, m_strDesFCobro);
	DDX_Text(pDX, IDC_IMPORTE, m_strImporte);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_VENCI, m_fechaVenci);
	DDX_Text(pDX, IDC_OBSERVACIONES, m_strObservaciones);
	DDV_MaxChars(pDX, m_strObservaciones, 35);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_RECEP, m_fechaRecep);
}


BEGIN_MESSAGE_MAP(CDlgDesglose, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_FCOBRO, OnEnKillfocusEditFcobro)
	ON_BN_CLICKED(IDC_BTN_FCOBRO, OnBnClickedBtnFcobro)
	ON_EN_KILLFOCUS(IDC_IMPORTE, OnEnKillfocusImporte)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgDesglose
/******************************************************************************************/

/******************************************************************************************/
BOOL CDlgDesglose::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetSeguienteCobroDesglosado();

	m_dlgBusquedaFCobro.SetConexion(m_db);

	return FALSE;
}

/******************************************************************************************/
void CDlgDesglose::OnEnKillfocusEditFcobro()
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
void CDlgDesglose::OnBnClickedBtnFcobro()
{
	INT_PTR status;

	m_dlgBusquedaFCobro.SetTipo(CDialogBusqueda::FPAGCOB);
	status = m_dlgBusquedaFCobro.DoModal();
	if (status == IDOK)
	{
		m_strFCobro = m_dlgBusquedaFCobro.GetCodigo();
		m_strDesFCobro = m_dlgBusquedaFCobro.GetDescripcion();
	}

	GetDlgItem(IDC_EDIT_FCOBRO)->SetWindowText(m_strFCobro);
	GetDlgItem(IDC_EDIT_DESFCOBRO)->SetWindowText(m_strDesFCobro);
}

/******************************************************************************************/
void CDlgDesglose::OnEnKillfocusImporte()
{
	CString strImporteAux;

	GetDlgItem(IDC_IMPORTE)->GetWindowText(strImporteAux);
	if (!CompruebaNumero(strImporteAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		GetDlgItem(IDC_IMPORTE)->SetWindowText(m_strImporte);
		GetDlgItem(IDC_IMPORTE)->SetFocus();
	}
	else
		m_strImporte = strImporteAux;

	GetDlgItem(IDC_IMPORTE)->SetWindowText(m_strImporte);
}

/******************************************************************************************/
void CDlgDesglose::OnBnClickedOk()
{
	UpdateData();

	RellenaCobro();

	HRESULT hErr = m_rsCobro.Insert();

	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgDesglose::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsCobro.m_pDatabase = db;
}

/******************************************************************************************/
void CDlgDesglose::SetCobroPadre(CCobros *rsCobrosPadre)
{
	m_rsCobrosPadre = rsCobrosPadre;
}

/******************************************************************************************/
void CDlgDesglose::GetSeguienteCobroDesglosado()
{
	CString strNumEfecPadre = m_rsCobrosPadre->m_NUMEFEC.Trim();
	m_strNumEfec = strNumEfecPadre.Left(strNumEfecPadre.Find("/"));
	m_strNumEfec2 = strNumEfecPadre.Mid(strNumEfecPadre.Find("/")+1, 1);
	m_strNumEfec3 = strNumEfecPadre.Right(strNumEfecPadre.GetLength() - strNumEfecPadre.ReverseFind('/') - 1);
	m_strNumEfec3.Format("%d", atoi(m_strNumEfec3) + 1);
		
	m_rsCobro.m_NUMEFEC = m_strNumEfec.Trim() + "/" + m_strNumEfec2.Trim() + "/" + m_strNumEfec3.Trim();

	// Se rellenan los datos que vienen los cobro padre
	m_rsCobro.m_NUMFAC = m_rsCobrosPadre->m_NUMFAC.Trim();
	m_rsCobro.m_CUENTA = m_rsCobrosPadre->m_CUENTA.Trim();
	m_rsCobro.m_FECHLIBRA = m_rsCobrosPadre->m_FECHLIBRA;
	m_rsCobro.m_CENTRO = m_rsCobrosPadre->m_CENTRO.Trim();
	m_rsCobro.m_ESTADO = COBRO_PENDIENTE;

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgDesglose::RellenaCobro()
{
	m_rsCobro.m_FCOBRO = m_strFCobro;
	m_rsCobro.m_EUROS = atof(m_strImporte);
	m_rsCobro.m_FECHA = m_fechaVenci;
	m_rsCobro.m_FRECEP = m_fechaRecep;
	m_rsCobro.m_OBSCOBRO = m_strObservaciones;
}
	
/******************************************************************************************/
BOOL CDlgDesglose::BuscaFCobro()
{
	BOOL bExists = FALSE;
	CFPagCob rsFCobro(m_db);

	rsFCobro.m_strFilter = "FCOBRO LIKE '" + m_strFCobro + "'";
	if (!rsFCobro.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la forma de cobro existe se rellena la descripción 
	if (!rsFCobro.m_FCOBRO.IsEmpty())
	{
		m_strDesFCobro = rsFCobro.m_DFCOBRO.Trim();
		bExists = TRUE;
	}

	rsFCobro.Close();

	UpdateData(FALSE);

	return bExists;
}


/************************************************************************************************************/
/** Comprueba que en la cadena no hay mas que números y como mucho un punto                                **/    
/************************************************************************************************************/
BOOL CDlgDesglose::CompruebaNumero(CString strNumero)
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




