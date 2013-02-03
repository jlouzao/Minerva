// DlgExistencias.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Almacen.h"
#include "DlgExistencias.h"
#include ".\dlgexistencias.h"
#include "BD.h"
#include "DlgExistsArticulos.h"


/**********************************************************************************/
// Cuadro de diálogo de CDlgExistencias
/**********************************************************************************/

IMPLEMENT_DYNAMIC(CDlgExistencias, CDialog)
CDlgExistencias::CDlgExistencias(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExistencias::IDD, pParent)
	, m_strCodArticulo(_T(""))
	, m_strDesArticulo(_T(""))
	, m_timeFecha(0)
{
}

/**********************************************************************************/
CDlgExistencias::~CDlgExistencias()
{
}

/**********************************************************************************/
void CDlgExistencias::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CODARTICULO, m_strCodArticulo);
	DDV_MaxChars(pDX, m_strCodArticulo, 15);
	DDX_Text(pDX, IDC_EDIT_DESARTICULO, m_strDesArticulo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timeFecha);
	DDX_Control(pDX, IDC_EDIT_CODARTICULO, m_ctrlCodArticulo);
}

/**********************************************************************************/
BEGIN_MESSAGE_MAP(CDlgExistencias, CDialog)
	ON_BN_CLICKED(IDC_BTN_ARTICULO, OnBnClickedBtnArticulo)
	ON_EN_KILLFOCUS(IDC_EDIT_CODARTICULO, OnEnKillfocusEditCodarticulo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


/**********************************************************************************/
// Controladores de mensajes de CDlgExistencias
/**********************************************************************************/
BOOL CDlgExistencias::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se inicializa la conexion de las clases para la búsqueda
	m_dlgBusquedaArticulo.SetConexion(m_db);

	// Se inicializa la fecha
	m_timeFecha = CTime::GetCurrentTime();

	UpdateData(FALSE);

	m_ctrlCodArticulo.SetFocus();

	return FALSE;
}

/**********************************************************************************/
void CDlgExistencias::OnBnClickedBtnArticulo()
{
	INT_PTR status;

	m_dlgBusquedaArticulo.SetTipo(CDialogBusqueda::ARTICULOS);
	status = m_dlgBusquedaArticulo.DoModal();
	if (status == IDOK)
	{
		m_strCodArticulo = m_dlgBusquedaArticulo.GetCodigo();
		m_strCodArticulo = m_strCodArticulo.Trim();
		m_strDesArticulo = m_dlgBusquedaArticulo.GetDescripcion();
		GetDlgItem(IDC_EDIT_CODARTICULO)->SetWindowText(m_strCodArticulo);
		GetDlgItem(IDC_EDIT_DESARTICULO)->SetWindowText(m_strDesArticulo);
	}
}

/******************************************************************************************/
void CDlgExistencias::OnEnKillfocusEditCodarticulo()
{
	CString strOldCodArticulo;

	strOldCodArticulo = m_strCodArticulo;

	GetDlgItem(IDC_EDIT_CODARTICULO)->GetWindowText(m_strCodArticulo);

	if (strOldCodArticulo != m_strCodArticulo)
	{
		if (BuscaArticulo())
		{
			GetDlgItem(IDC_EDIT_DESARTICULO)->SetWindowText(m_strDesArticulo);
			return;		
		}
		else
		{
			m_strCodArticulo = strOldCodArticulo;
			GetDlgItem(IDC_EDIT_CODARTICULO)->SetWindowText(m_strCodArticulo);
			return;
		}
	}

	return;
}

/******************************************************************************************/

void CDlgExistencias::OnBnClickedOk()
{
	UpdateData (TRUE);
	CDlgExistsArticulos dlgExistsArticulos;
	dlgExistsArticulos.SetConexion(m_db);
	dlgExistsArticulos.SetCodArticulo(m_strCodArticulo);
	dlgExistsArticulos.SetDesArticulo(m_strDesArticulo);
	dlgExistsArticulos.SetFecha(m_timeFecha);
	dlgExistsArticulos.DoModal();

	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgExistencias::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
BOOL CDlgExistencias::BuscaArticulo()
{
	/* Se carga el listCtrl con el código, la descripción y el número de exitencias  */
	CArticulo rsArticulo(m_db);

	GetDlgItem(IDC_EDIT_CODARTICULO)->GetWindowText(m_strCodArticulo);
	m_strCodArticulo = m_strCodArticulo.Trim();

	rsArticulo.m_strFilter = "ARTI LIKE '" + m_strCodArticulo + "'";
	if (!rsArticulo.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el articulo no se encuentra salimos reseteando el campo
	if (rsArticulo.m_ARTI.IsEmpty())
	{		
		AfxMessageBox(IDS_ARTI_NO_EXISTS);
		return FALSE;
	}
	else
		m_strDesArticulo = rsArticulo.m_DESARTI.Trim();

	return TRUE;
}

