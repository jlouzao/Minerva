// DlgExistsArticulos.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Almacen.h"
#include "DlgExistsArticulos.h"
#include "BD.h"

/*************************************************************************************/
// Cuadro de diálogo de CDlgExistsArticulos
/*************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgExistsArticulos, CDialog)
CDlgExistsArticulos::CDlgExistsArticulos(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExistsArticulos::IDD, pParent)
	, m_strCodArti(_T(""))
	, m_strDesArti(_T(""))
	, m_strFecha(_T(""))
	, m_strSumaTotales(_T(""))
	, m_strSumaDisponibles(_T(""))
{
}

/*************************************************************************************/
CDlgExistsArticulos::~CDlgExistsArticulos()
{
}

/*************************************************************************************/
void CDlgExistsArticulos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EXISTENCIAS, m_lstExistencias);
	DDX_Text(pDX, IDC_EDIT1, m_strCodArti);
	DDX_Text(pDX, IDC_EDIT2, m_strDesArti);
	DDX_Text(pDX, IDC_EDIT3, m_strFecha);
	DDX_Text(pDX, IDC_EDIT4, m_strSumaTotales);
	DDX_Text(pDX, IDC_EDIT5, m_strSumaDisponibles);
}


/*************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgExistsArticulos, CDialog)
END_MESSAGE_MAP()

/*************************************************************************************/
// Controladores de mensajes de CDlgExistsArticulos
/*************************************************************************************/

BOOL CDlgExistsArticulos::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se inicializa el título
	//m_strArticulo.Format("CÓDIGO:  %s     DESCRIPCIÓN:  %s\nFECHA:  %s", m_strCodArti, m_strDesArti,
	//	m_timeFecha.Format("%d/%m/%Y"));

	// Se inicializa la fecha
	m_strFecha = m_timeFecha.Format("%d/%m/%Y");

	// Se inicializa el ListCtrl
	m_lstExistencias.SetExtendedStyle(m_lstExistencias.GetExtendedStyle()|LVS_EX_GRIDLINES);

	m_lstExistencias.InsertColumn(0,"Almacén", LVCFMT_CENTER, 140);			
	m_lstExistencias.InsertColumn(1,"Existencias", LVCFMT_CENTER, 140);
	m_lstExistencias.InsertColumn(2,"Disponibles", LVCFMT_CENTER, 140);

	CargarExistencias();

	UpdateData(FALSE);

	return FALSE;
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgExistsArticulos::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgExistsArticulos::SetCodArticulo(CString &strCodArti)
{
	m_strCodArti = strCodArti;
}

/******************************************************************************************/
void CDlgExistsArticulos::SetDesArticulo(CString &strDesArti)
{
	m_strDesArti = strDesArti;
}

/******************************************************************************************/
void CDlgExistsArticulos::SetFecha(CTime timeFecha)
{
	m_timeFecha = timeFecha;
}

/******************************************************************************************/
void CDlgExistsArticulos::CargarExistencias()
{
	CInventario rsInventario(m_db);

	rsInventario.m_strFilter = "ARTI LIKE '" + m_strCodArti + "'";
	if (!rsInventario.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	double iTotales = 0;
	double iDisponibles = 0;
	int iIndex = 0;

	while (!rsInventario.IsEOF())
	{
		CAlmacen rsAlmacen(m_db);

		// Se obtienen todos los almacenes en los que está el artículo
		rsAlmacen.m_strFilter = "CLAVE = (SELECT MAX(CLAVE) FROM ALMACEN WHERE ARTI LIKE '" 
			+ m_strCodArti + "' AND ALMACEN = '" + rsInventario.m_ALMACEN + "' AND FECHA <= '" + 
			m_timeFecha.Format("%d/%m/%Y") + "')";

		if (!rsAlmacen.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// Si no está en la tabla almacén no se hace nada más
		if (!rsAlmacen.m_ARTI.IsEmpty())
		{
			CString strCantiTotal, strCantiDisponible;
			
			// Sólo se mostrará si hay algún artículo en el almacén
			if (rsAlmacen.m_CANTITOTAL != 0)
			{
				strCantiTotal.Format("%.0f", rsAlmacen.m_CANTITOTAL);
				strCantiDisponible.Format("%.0f", rsAlmacen.m_CANTIDISPONIBLE);

				iTotales += rsAlmacen.m_CANTITOTAL;
				iDisponibles += rsAlmacen.m_CANTIDISPONIBLE;

				m_lstExistencias.InsertItem(iIndex, _T(""));
				m_lstExistencias.SetItemText(iIndex, 0, rsAlmacen.m_ALMACEN.Trim());
				m_lstExistencias.SetItemText(iIndex, 1, strCantiTotal);
				m_lstExistencias.SetItemText(iIndex, 2, strCantiDisponible);

				iIndex++;
			}
		}

		rsAlmacen.Close();
		rsInventario.MoveNext();
	}

	rsInventario.Close();
	
	// Se rellenan los totales
	m_strSumaTotales.Format("%.0f", iTotales);
	m_strSumaDisponibles.Format("%.0f", iDisponibles);

	return;
}