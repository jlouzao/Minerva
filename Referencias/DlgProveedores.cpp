// DlgProveedores.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgProveedores.h"
#include ".\dlgproveedores.h"

/***************************************************************************************/
// Cuadro de diálogo de CDlgProveedores
/***************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgProveedores, CDialog)
CDlgProveedores::CDlgProveedores(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProveedores::IDD, pParent)
	, m_strCodArti(_T(""))
	, m_strDesArti(_T(""))
{
}

/***************************************************************************************/
CDlgProveedores::~CDlgProveedores()
{
}

/***************************************************************************************/
void CDlgProveedores::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CODIGO, m_strCodArti);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDesArti);
	DDX_Control(pDX, IDC_LIST_PROVE, m_lstProve);
}

/***************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgProveedores, CDialog)
	ON_BN_CLICKED(ID_ELIMINAR, OnBnClickedEliminar)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROVE, OnNMClickListProve)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_PROVE, OnNMSetfocusListProve)
//	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_PROVE, OnNMKillfocusListProve)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/***************************************************************************************/
// Controladores de mensajes de CDlgProveedores
/***************************************************************************************/
BOOL CDlgProveedores::OnInitDialog()
{
	CDialog::OnInitDialog();

	CProveArti rsProveArti(m_db);

	// Si la lista no ha sido cargada y ya ha sido seleccionado algún artículo
	if (m_pProve->IsEmpty() && !m_strCodArti.IsEmpty())
	{
		rsProveArti.m_strFilter = "ARTI LIKE '" + m_strCodArti + "'";
		if (!rsProveArti.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return FALSE;
		}

		while (!rsProveArti.IsEOF())
		{
			m_pProve->AddTail(rsProveArti);
			rsProveArti.MoveNext();
		}

		rsProveArti.Close();
	}

	// Se inicializa el listCtrl
	m_lstProve.SetGridLines(TRUE);
	m_lstProve.SetEditable(TRUE); // Allow sub-text edit

	// Se introducen los nombres de las columnas
	m_lstProve.InsertColumn(0,"Código", LVCFMT_LEFT, 80);			
	m_lstProve.InsertColumn(1,"Descripción", LVCFMT_LEFT, 220);
	m_lstProve.InsertColumn(2,"Su referencia", LVCFMT_LEFT, 85);
	m_lstProve.InsertColumn(3,"Tarifa", LVCFMT_LEFT, 70);
	m_lstProve.InsertColumn(4,"Descuento", LVCFMT_LEFT, 70);

	// Se muestra la lista de Proveedores en el listCtrl
	m_iNumProve = 0;
	POSITION pos = m_pProve->GetHeadPosition();
	while(pos)
	{
		rsProveArti = m_pProve->GetNext(pos);

		m_lstProve.InsertItem(m_iNumProve, _T(""));
		m_lstProve.SetItemText(m_iNumProve, 0, rsProveArti.m_CUENTA);
		m_lstProve.SetItemBkColor(m_iNumProve, 0, RGB(212, 208, 200), TRUE);
		m_lstProve.SetItemText(m_iNumProve, 1, rsProveArti.m_NOMPROVE);
		m_lstProve.SetItemBkColor(m_iNumProve, 1, RGB(212, 208, 200), TRUE);
		m_lstProve.SetItemText(m_iNumProve, 2, rsProveArti.m_SREF);
		m_lstProve.SetItemText(m_iNumProve, 3, rsProveArti.m_TARIFA);
		m_lstProve.SetItemText(m_iNumProve, 4, rsProveArti.m_DESCUENTO);
		m_iNumProve++;
	}

	// Se inicializa el seiguiente item a vacío para permitir escribir en él
	InsertaRegistroVacio();

	// Se inicializa la conexion de la clase para la búsqueda
	m_dlgBusquedaProve.SetConexion(m_db);

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	// Se pone el foco en el listCtrl 
	m_lstProve.SetFocus();
	m_lstProve.EndEdit();
	m_lstProve.StartEdit(m_iNumProve, 0);	

	return FALSE;
}

/******************************************************************************************/
void CDlgProveedores::OnNMSetfocusListProve(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Si no era un código correcto hay que devolverle el foco
	CString strCodeProve = m_lstProve.GetItemText(m_lstProve.m_ptEditting.x, 0);
	if (m_lstProve.m_ptEditting.y == 1 && strCodeProve.IsEmpty())
	{
		m_lstProve.EndEdit();
		m_lstProve.StartEdit(m_iNumProve, 0);			
	}

	*pResult = 0;
}

/******************************************************************************************/
LRESULT CDlgProveedores::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr = 0;

	// Si el foco va a la primera columna y es una fila vacía
	if (m_lstProve.m_ptEditting.y == 0 && m_lstProve.m_ptEditting.x == m_iNumProve)
	{
		CString strCodProve;
		/* Se coge el código del artículo */
		int len = m_lstProve.GetEditControl()->LineLength(m_lstProve.GetEditControl()->LineIndex(0));
		if (len > 0)
		{
			m_lstProve.GetEditControl()->GetLine(0, strCodProve.GetBuffer(len), len);
			strCodProve.ReleaseBuffer(len);
			if (!strCodProve.IsEmpty())
				BuscaProve(strCodProve);
		}
	}	

	// Se obtiene lo que contiene la primera columna
	CString strCod = m_lstProve.GetItemText(m_lstProve.m_ptEditting.x, 0);

	// En las columnas que deben estar inactivas se pone el textbox a readonly
	if (m_lstProve.m_ptEditting.y == 1 || (m_lstProve.m_ptEditting.y == 0 && !strCod.IsEmpty()))
		m_lstProve.GetEditControl()->SetReadOnly(TRUE);
	else
		m_lstProve.GetEditControl()->SetReadOnly(FALSE);

	// Si estamos en la columna de Tarifas o de Descuento hay que comprobar si es un número
	if (m_lstProve.m_ptEditting.y == 3 || m_lstProve.m_ptEditting.y == 4)
	{
		CString strNumero;
		int len = m_lstProve.GetEditControl()->LineLength(m_lstProve.GetEditControl()->LineIndex(0));
		if (len > 0)
		{
			m_lstProve.GetEditControl()->GetLine(0, strNumero.GetBuffer(len), len);
			strNumero.ReleaseBuffer(len);

			if (!strNumero.IsEmpty())
			{
				if (m_lstProve.m_ptEditting.y == 3)
				{
					if (!(EsNum(strNumero)))
						m_lstProve.SetItemTextCB(m_lstProve.m_ptEditting.x, 3, m_strOldTarifa);
					else
					{
						m_lstProve.SetItemTextCB(m_lstProve.m_ptEditting.x, 3, strNumero);
						m_strOldTarifa = strNumero;
					}
				}
				if (m_lstProve.m_ptEditting.y == 4)
				{
					if (!(EsNum(strNumero)))
						m_lstProve.SetItemTextCB(m_lstProve.m_ptEditting.x, 4, m_strOldDescuento);
					else
					{
						m_lstProve.SetItemTextCB(m_lstProve.m_ptEditting.x, 4, strNumero);
						m_strOldDescuento = strNumero;
					}
				}
			}
		}
	}

	return hErr;
}

/******************************************************************************************/
void CDlgProveedores::OnBnClickedEliminar()
{
	int iIndex;

	POSITION pos = m_lstProve.GetFirstSelectedItemPosition();
	iIndex = m_lstProve.GetNextSelectedItem(pos);            
	m_lstProve.DeleteItem(iIndex);

	m_iNumProve--;

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
}

/******************************************************************************************/
void CDlgProveedores::OnNMClickListProve(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_lstProve.GetFirstSelectedItemPosition();
	int iIndex = m_lstProve.GetNextSelectedItem(pos);            

	if (m_lstProve.GetSelectedCount() > 0 && iIndex != m_lstProve.GetItemCount()-1)
		GetDlgItem(ID_ELIMINAR)->EnableWindow(TRUE);
	else
		GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
	
	*pResult = 0;
}

/******************************************************************************************/
void CDlgProveedores::OnBnClickedBuscar()
{
	INT_PTR status;

	m_dlgBusquedaProve.SetTipo(CDialogBusqueda::PROVEEDORES);
	status = m_dlgBusquedaProve.DoModal();
	if (status == IDOK)
	{
		CString strCodProve, strDesProve;
		strCodProve = m_dlgBusquedaProve.GetCodigo();
		strDesProve = m_dlgBusquedaProve.GetDescripcion();

		/* Se comprueba si ese artículo ya está en el CListCtrl. Para ello se busca el
		elemento, si lo encuentra devuelve el índice de la fila donde lo encontro y si
		no, devuelve el indice de la última fila o -1 */
		LVFINDINFO info;
		int iIndex;
		
		info.flags = LVFI_STRING | LVFI_WRAP;
		info.psz = strCodProve;
		iIndex = m_lstProve.FindItem(&info);
		if ( iIndex != m_iNumProve && iIndex != -1)
		{
			m_lstProve.SetItemText(m_iNumProve, 0, "");
			AfxMessageBox(IDS_PROVE_YA_EN_LISTA);
			return;
		}

		// Se escribe en el listCtrl
		m_lstProve.SetItemText(m_iNumProve, 0, strCodProve);
		m_lstProve.SetItemBkColor(m_iNumProve, 0, RGB(212, 208, 200), TRUE);
		m_lstProve.SetItemText(m_iNumProve, 1, strDesProve);
		m_lstProve.SetItemBkColor(m_iNumProve, 1, RGB(212, 208, 200), TRUE);
		m_iNumProve++;
		InsertaRegistroVacio();
	}
}

/******************************************************************************************/
void CDlgProveedores::OnBnClickedOk()
{		
	// Se borra la lista de proveedores que pudiera haber y se crea de nuevo para asegurar
	// que se va a guardar cualquier posible cambio
	m_pProve->RemoveAll();

	for (int i=0; i < m_lstProve.GetItemCount(); i++)
	{	
		CProveArti rsProveArti(m_db);

		// El item vacío no debe procesarse
		if (m_lstProve.GetItemText(i, 0) == "")
			continue;

		rsProveArti.m_ARTI = m_strCodArti;
		rsProveArti.m_CUENTA = m_lstProve.GetItemText(i, 0);
		rsProveArti.m_NOMPROVE = m_lstProve.GetItemText(i, 1);
		rsProveArti.m_SREF = m_lstProve.GetItemText(i, 2);
		rsProveArti.m_TARIFA = atof(m_lstProve.GetItemText(i, 3));
		rsProveArti.m_DESCUENTO = atof(m_lstProve.GetItemText(i, 4));

		m_pProve->AddTail(rsProveArti);
	}

	OnOK();
}

/******************************************************************************************/
/**                                     FUNCIONES                                        **/
/******************************************************************************************/
void CDlgProveedores::SetConexion(CDatabase *db)
{
	m_db = db;
}

/***************************************************************************************/
void CDlgProveedores::SetCodArticulo(CString strCodArti)
{
	m_strCodArti = strCodArti;
}

/***************************************************************************************/
void CDlgProveedores::SetDesArticulo(CString strDesArti)
{
	m_strDesArti = strDesArti;
}

/***************************************************************************************/
void CDlgProveedores::SetProveedores(CList <CProveArti, CProveArti&> *pProve)
{
	m_pProve = pProve;
}

/***************************************************************************************/
void CDlgProveedores::GetProveedores(CList <CProveArti, CProveArti&> *pProve)
{
	pProve = m_pProve;
}

/******************************************************************************************/
void CDlgProveedores::InsertaRegistroVacio()
{
	m_lstProve.InsertItem(m_iNumProve, _T(""));
	m_lstProve.SetItemText(m_iNumProve, 0, "");
	m_lstProve.SetItemText(m_iNumProve, 1, "");
	m_lstProve.SetItemText(m_iNumProve, 2, "");
	m_lstProve.SetItemText(m_iNumProve, 3, "");

	m_strOldTarifa = "0";
	m_strOldDescuento = "0";
}

/******************************************************************************************/
void CDlgProveedores::BuscaProve(CString strCodProve)
{
	/* Se comprueba si ese artículo ya está en el CListCtrl. Para ello se busca el
	elemento, si lo encuentra devuelve el índice de la fila donde lo encontro y si
	no, devuelve el indice de la última fila o -1 */
	LVFINDINFO info;
	int iIndex;
	
	info.flags = LVFI_STRING | LVFI_WRAP;
	info.psz = strCodProve;
	iIndex = m_lstProve.FindItem(&info);
	if ( iIndex != m_iNumProve && iIndex != -1)
	{
		m_lstProve.SetItemText(m_iNumProve, 0, "");
		AfxMessageBox(IDS_PROVE_YA_EN_LISTA);
		return;
	}

	CCuentas rsCuentas(m_db);

	rsCuentas.m_strFilter = "CUENTA LIKE '" + strCodProve + "'";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	if (rsCuentas.m_CUENTA.IsEmpty())
	{
		m_lstProve.SetItemText(m_iNumProve, 0, "");
		AfxMessageBox(IDS_PROVE_NO_EXISTS);
		return;
	}

	m_lstProve.SetItemText(m_iNumProve, 0, rsCuentas.m_CUENTA.Trim());
	m_lstProve.SetItemBkColor(m_iNumProve, 0, RGB(212, 208, 200), TRUE);
	m_lstProve.SetItemText(m_iNumProve, 1, rsCuentas.m_NOMBRE.Trim());
	m_lstProve.SetItemBkColor(m_iNumProve, 1, RGB(212, 208, 200), TRUE);
	m_iNumProve++;
	InsertaRegistroVacio();

	return;
}

/******************************************************************************************/
BOOL CDlgProveedores::EsNum(CString strNumero)
{
	BOOL bPunto = FALSE;	
	for (int i = 0; i<strNumero.GetLength(); i++)
	{
		if ((strNumero.GetAt(i) < '0' || strNumero.GetAt(i) > '9') && (strNumero.GetAt(i) != '-' || (strNumero.GetAt(i) == '-' && i != 0))) 
		{				
			if (strNumero.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}
	return TRUE;
}
