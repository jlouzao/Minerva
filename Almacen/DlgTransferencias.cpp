// DlgTransferencias.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgTransferencias.h"
#include "BD.h"
#include ".\dlgtransferencias.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgTransferencias
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgTransferencias, CDialog)
CDlgTransferencias::CDlgTransferencias(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransferencias::IDD, pParent)
	, m_timeFecha(0)
	, m_strCodAlmacenOrig(_T(""))
	, m_strDesAlmacenOrig(_T(""))
	, m_strCodAlmacenDest(_T(""))
	, m_strDesAlmacenDest(_T(""))
	, m_strCodDoc(_T(""))
	, m_strObservaciones(_T(""))
	, m_strDesDoc(_T(""))
{
	m_iNumArti = 0;
	m_strCodArti = " ";
	m_strTransferenciaOld = "0";
}

/******************************************************************************************/
CDlgTransferencias::~CDlgTransferencias()
{
}

/******************************************************************************************/
void CDlgTransferencias::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_FECHA, m_timeFecha);
	DDX_Text(pDX, IDC_EDIT_ALMACEN, m_strCodAlmacenOrig);
	DDX_Text(pDX, IDC_EDIT_DESALMACEN, m_strDesAlmacenOrig);
	DDX_Text(pDX, IDC_EDIT_ALMACEN2, m_strCodAlmacenDest);
	DDX_Text(pDX, IDC_EDIT_DESALMACEN2, m_strDesAlmacenDest);
	DDX_Text(pDX, IDC_EDIT_DOCUMENTO, m_strCodDoc);
	DDX_Text(pDX, IDC_EDIT_OBSERVACIONES, m_strObservaciones);
	DDX_Control(pDX, IDC_LSTARTICULOS, m_lstArticulos);
	DDX_Text(pDX, IDC_EDIT_DESDOC, m_strDesDoc);
	DDV_MaxChars(pDX, m_strObservaciones, 35);
	DDX_Control(pDX, IDC_EDIT_ALMACEN, m_ctrlAlmacenOrig);
	DDX_Control(pDX, IDC_EDIT_OBSERVACIONES, m_ctrlObservaciones);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgTransferencias, CDialog)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
	ON_NOTIFY(NM_SETFOCUS, IDC_LSTARTICULOS, OnNMSetfocusLstarticulos)
	ON_BN_CLICKED(IDC_BTN_ELIMINAR, OnBnClickedEliminar)
	ON_NOTIFY(NM_CLICK, IDC_LSTARTICULOS, OnNMClickLstarticulos)
	ON_BN_CLICKED(IDC_BTN_ALMACEN, OnBnClickedBtnAlmacen)
	ON_BN_CLICKED(IDC_BTN_DOCUMENTO, OnBnClickedBtnDocumento)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT_ALMACEN, OnEnKillfocusEditAlmacen)
	ON_EN_KILLFOCUS(IDC_EDIT_DOCUMENTO, OnEnKillfocusEditDocumento)
	ON_EN_KILLFOCUS(IDC_EDIT_OBSERVACIONES, OnEnKillfocusEditObservaciones)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LSTARTICULOS, OnLvnInsertitemLstarticulos)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	
	ON_BN_CLICKED(IDC_BTN_ALMACEN2, OnBnClickedBtnAlmacen2)
	ON_EN_KILLFOCUS(IDC_EDIT_ALMACEN2, OnEnKillfocusEditAlmacen2)
END_MESSAGE_MAP()


/******************************************************************************************/
// Controladores de mensajes de CDlgTransferencias
/******************************************************************************************/

BOOL CDlgTransferencias::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece el estilo	
	m_lstArticulos.SetGridLines(TRUE);

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 105);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 202);
	m_lstArticulos.InsertColumn(2,"Existencias", LVCFMT_LEFT, 78);
	m_lstArticulos.InsertColumn(3,"Disponibles", LVCFMT_LEFT, 78);
	m_lstArticulos.InsertColumn(4,"Transferir", LVCFMT_LEFT, 78);

	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit

	// Se inicializa el primer item todo vacío para permitir escribir en él
	InsertaRegistroVacio();

	// Se deshabilita el botón de Buscar, Eliminar y Aceptar
	GetDlgItem(IDBUSCAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	// Se inicializa la conexion de las clases para la búsqueda
	m_dlgBusquedaArticulo.SetConexion(m_db);
	m_dlgBusquedaAlmacen.SetConexion(m_db);
	m_dlgBusquedaDocumento.SetConexion(m_db);

	// Se inicializa la fecha
	m_timeFecha = CTime::GetCurrentTime();

	// Se inicializa el documento
	IniDocumento();

	// Se inicializa la variable
	m_strTransferenciaOld = "0";

	// Se inicializa el flag
	m_bFocusListCtrl = FALSE;

	m_ctrlAlmacenOrig.SetFocus();

	UpdateData(FALSE);

	return FALSE; // Devuelve TRUE  a menos que establezca el foco en un control
}

/******************************************************************************************/
void CDlgTransferencias::OnBnClickedBuscar()
{
	INT_PTR status;

	m_dlgBusquedaArticulo.SetTipo(CDialogBusqueda::ARTICULOS);
	status = m_dlgBusquedaArticulo.DoModal();
	if (status == IDOK)
	{
		m_strCodArti = m_dlgBusquedaArticulo.GetCodigo();

		/* Busca el artículo y lo escribe en el listCtrl */
		if (!m_strCodArti.IsEmpty())
			BuscaArticulo();
	}
}
/******************************************************************************************/
BOOL CDlgTransferencias::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

/******************************************************************************************/

void CDlgTransferencias::OnNMSetfocusLstarticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Se pone editable el editbox del artículo
	/*if (this->IsWindowVisible() && m_lstArticulos.m_ptEditting.x == -1 && 
		m_lstArticulos.m_ptEditting.y == -1 && /*(m_lstArticulos.GetEditControl()->GetSafeHwnd() == NULL))*/
	/*	m_iNumArti == 0)
	{
		m_lstArticulos.EndEdit();
		m_lstArticulos.StartEdit(m_iNumArti, 0);	
	}*/

	if (!m_bFocusListCtrl)
	{
		m_bFocusListCtrl = TRUE;
		m_lstArticulos.EndEdit();
		m_lstArticulos.StartEdit(m_iNumArti, 0);		
	}

	// Si vamos a la casilla de la descripción pero no hay código se devuelve el foco
	CString strCod = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 0);
	//if (m_lstArticulos.m_ptEditting.y == 1 && strCod.IsEmpty())

	if (m_lstArticulos.m_ptEditting.y != -1 && m_lstArticulos.m_ptEditting.y != 0 && strCod.IsEmpty())
	{
		m_lstArticulos.EndEdit();
		m_lstArticulos.StartEdit(m_iNumArti, 0);			
	}
			
	// Se habilita el botón de Buscar
//	if (m_lstArticulos.m_ptEditting.y == 0 && m_lstArticulos.m_ptEditting.x == m_iNumArti)
//	GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);

	GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);

	*pResult = 0;
}

/******************************************************************************************/
LRESULT CDlgTransferencias::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr  = 0;

	// Si el foco va a la primera columna y es una fila vacía
	if (m_lstArticulos.m_ptEditting.y == 0 && m_lstArticulos.m_ptEditting.x == m_iNumArti)
	{
		/* Se coge el código del artículo */
		int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
		m_lstArticulos.GetEditControl()->GetLine(0, m_strCodArti.GetBuffer(len), len);
		m_strCodArti.ReleaseBuffer(len);
		if (!m_strCodArti.IsEmpty())
			BuscaArticulo();
	}	

	// Se obtiene lo que contiene la primera columna
	CString strCod = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 0);

	// En las columnas que deben estar inactivas se pone el textbox a readonly
	if (m_lstArticulos.m_ptEditting.y == 1 || m_lstArticulos.m_ptEditting.y == 2 ||
		m_lstArticulos.m_ptEditting.y == 3)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	// Si estamos en la primera columna y ya tiene algo no se puede modificar
	else if (m_lstArticulos.m_ptEditting.y == 0 && !strCod.IsEmpty())
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	else if	(m_lstArticulos.m_ptEditting.y == 0 || m_lstArticulos.m_ptEditting.y == 4)
		m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);

	// Se comprueba si hay unidades disponibles para hacer la transferencia
	if (m_lstArticulos.m_ptEditting.y == 4 && !strCod.IsEmpty())
		ComprobarTransferencia();

//	if (m_lstArticulos.m_ptEditting.y != 0)
//	GetDlgItem(IDBUSCAR)->EnableWindow(FALSE);

	return hErr;
}

/******************************************************************************************/
void CDlgTransferencias::OnNMClickLstarticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Se deshabilita el botón de Eliminar si hay algún elemento seleccionado
	POSITION pos = m_lstArticulos.GetFirstSelectedItemPosition();
	int iIndex = m_lstArticulos.GetNextSelectedItem(pos);            

	if (m_lstArticulos.GetSelectedCount() > 0 && iIndex != m_lstArticulos.GetItemCount()-1)
		GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);

//	if (iIndex == -1)
//		GetDlgItem(IDBUSCAR)->EnableWindow(FALSE);

	*pResult = 0;
}

/******************************************************************************************/
void CDlgTransferencias::OnBnClickedEliminar()
{
	int iIndex;

	POSITION pos = m_lstArticulos.GetFirstSelectedItemPosition();
	iIndex = m_lstArticulos.GetNextSelectedItem(pos);            
	m_lstArticulos.DeleteItem(iIndex);

	m_iNumArti--;

	GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);

	if (m_iNumArti == 0)
		GetDlgItem(IDOK)->EnableWindow(FALSE);
}

/******************************************************************************************/
void CDlgTransferencias::OnEnKillfocusEditAlmacen()
{
	CompruebaAlmacenOrig();
}

/******************************************************************************************/
void CDlgTransferencias::OnEnKillfocusEditAlmacen2()
{
	CompruebaAlmacenDest();
}

/******************************************************************************************/
void CDlgTransferencias::OnBnClickedBtnAlmacen()
{
	INT_PTR status;
	CString strOldCodAlmacen;

	strOldCodAlmacen = m_strCodAlmacenOrig;

	m_dlgBusquedaAlmacen.SetTipo(CDialogBusqueda::ALMACEN);
	status = m_dlgBusquedaAlmacen.DoModal();
	if (status == IDOK)
	{
		m_strCodAlmacenOrig = m_dlgBusquedaAlmacen.GetCodigo();
		m_strCodAlmacenOrig = m_strCodAlmacenOrig.Trim();
		m_strDesAlmacenOrig = m_dlgBusquedaAlmacen.GetDescripcion();

		if (!m_strCodAlmacenDest.IsEmpty() && m_strCodAlmacenDest == m_strCodAlmacenOrig)
		{
			AfxMessageBox(IDS_MISMO_ALMACEN);
			return;
		}

		// Si es la primera vez que se elige un almacén se escribe en los textbox
		if (strOldCodAlmacen.IsEmpty())
		{
			GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strCodAlmacenOrig);
			GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacenOrig);
		}
		else if (m_strCodAlmacenOrig == m_strCodAlmacenDest)
		{
			AfxMessageBox(IDS_MISMO_ALMACEN);
			m_strCodAlmacenOrig = strOldCodAlmacen;
			GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strCodAlmacenOrig);
			return;
		}
		else if (strOldCodAlmacen != m_strCodAlmacenOrig)
			LimpiaVentana(FALSE);  // Con FALSE no limpia los campos del almacen

		if (!m_strCodAlmacenOrig.IsEmpty() && !m_strCodAlmacenDest.IsEmpty())
			GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);
	}	
}

/******************************************************************************************/
void CDlgTransferencias::OnBnClickedBtnAlmacen2()
{
	INT_PTR status;
	CString strOldCodAlmacen;

	strOldCodAlmacen = m_strCodAlmacenDest;

	m_dlgBusquedaAlmacen.SetTipo(CDialogBusqueda::ALMACEN);
	status = m_dlgBusquedaAlmacen.DoModal();
	if (status == IDOK)
	{
		m_strCodAlmacenDest = m_dlgBusquedaAlmacen.GetCodigo();
		m_strCodAlmacenDest = m_strCodAlmacenDest.Trim();
		m_strDesAlmacenDest = m_dlgBusquedaAlmacen.GetDescripcion();

		if (!m_strCodAlmacenOrig.IsEmpty() && m_strCodAlmacenOrig == m_strCodAlmacenDest)
		{
			AfxMessageBox(IDS_MISMO_ALMACEN);
			return;
		}

		// Si es la primera vez que se elige un almacén se escriba en los textbox
		if (strOldCodAlmacen.IsEmpty())
		{
			GetDlgItem(IDC_EDIT_ALMACEN2)->SetWindowText(m_strCodAlmacenDest);
			GetDlgItem(IDC_EDIT_DESALMACEN2)->SetWindowText(m_strDesAlmacenDest);
		}
		else if (m_strCodAlmacenOrig == m_strCodAlmacenDest)
		{
			AfxMessageBox(IDS_MISMO_ALMACEN);
			m_strCodAlmacenDest = strOldCodAlmacen;
			GetDlgItem(IDC_EDIT_ALMACEN2)->SetWindowText(m_strCodAlmacenDest);
			return;
		}
		else if (strOldCodAlmacen != m_strCodAlmacenDest)
			LimpiaVentana(FALSE);  // Con FALSE no limpia los campos del almacen

		if (!m_strCodAlmacenOrig.IsEmpty() && !m_strCodAlmacenDest.IsEmpty())
			GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);

	}	
}

/******************************************************************************************/
void CDlgTransferencias::OnEnKillfocusEditDocumento()
{
	CompruebaDocumento();
}

/******************************************************************************************/
void CDlgTransferencias::OnBnClickedBtnDocumento()
{
	INT_PTR status;

	m_dlgBusquedaDocumento.SetTipo(CDialogBusqueda::CONCEPTOS);
	status = m_dlgBusquedaDocumento.DoModal();
	if (status == IDOK)
	{
		m_strCodDoc = m_dlgBusquedaDocumento.GetCodigo();
		m_strDesDoc = m_dlgBusquedaDocumento.GetDescripcion();
		UpdateData(FALSE);
	}	
}

/******************************************************************************************/
void CDlgTransferencias::OnEnKillfocusEditObservaciones()
{
	m_bFocusListCtrl = TRUE;
	if (!CompruebaObservaciones())	
		m_ctrlObservaciones.SetFocus();
	else
		m_bFocusListCtrl = FALSE;
}

/******************************************************************************************/
void CDlgTransferencias::OnLvnInsertitemLstarticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// Si un elemento se activa el botón aceptar
	if (m_lstArticulos.GetItemCount() > 0)
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	
	*pResult = 0;
}

/******************************************************************************************/
void CDlgTransferencias::OnBnClickedOk()
{
	HRESULT hErr;

	// Se comprueba que todos los datos sean datos existentes
	if (!CompruebaAlmacenOrig())
		return;
	if (!CompruebaAlmacenDest())
		return;
	if (!CompruebaDocumento())
		return;
	if (!CompruebaObservaciones())
		return;

	// Se recogen los datos de los controles
	UpdateData(TRUE);

	CAlmacen rsAlmacenOrig(m_db);
	CAlmacen rsAlmacenDest(m_db);

	// Se inicializan los campos comunes de ambos almacenes
	rsAlmacenOrig.m_ALMACEN = m_strCodAlmacenOrig.Trim();
	rsAlmacenOrig.m_FECHA = m_timeFecha;
	rsAlmacenOrig.m_TIPOMOV = m_strCodDoc.Trim();
	rsAlmacenOrig.m_OBSER = m_strObservaciones.Trim();
	rsAlmacenOrig.m_NDOC = 0;

	rsAlmacenDest.m_ALMACEN = m_strCodAlmacenDest.Trim();
	rsAlmacenDest.m_FECHA = m_timeFecha;
	rsAlmacenDest.m_TIPOMOV = m_strCodDoc.Trim();
	rsAlmacenDest.m_OBSER = m_strObservaciones.Trim();
	rsAlmacenDest.m_NDOC = 0;

	BOOL bInsertarOrig = FALSE;
	BOOL bInsertarDest = FALSE;

	for (int i=0; i < m_lstArticulos.GetItemCount(); i++)
	{	
		CArticulo rsArticulo(m_db);
		CInventario rsInventarioOrig(m_db);
		CInventario rsInventarioDest(m_db);

		// El item vacío no debe procesarse
		if (m_lstArticulos.GetItemText(i, 0) == "")
			continue;

		rsAlmacenOrig.m_ARTI = m_lstArticulos.GetItemText(i, 0);
		rsAlmacenDest.m_ARTI = m_lstArticulos.GetItemText(i, 0);

		// La cantidad de movimiento del almacén serán los articulos a transferir
		int iTransferidas = abs(atoi(m_lstArticulos.GetItemText(i, 4)));
		
		// Si no hay unidades a transferir no hay movimiento
		if (iTransferidas == 0)
			continue;

		rsAlmacenOrig.m_CANTI = -iTransferidas;
		rsAlmacenDest.m_CANTI = iTransferidas;

		rsArticulo.m_strFilter = "ARTI LIKE '" + rsAlmacenOrig.m_ARTI + "'";
		if (!rsArticulo.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// La cuenta será la cuenta de ventas o de alquiler. Se coge la que esté rellena
		// de las 2 o si lo están las dos, se coge la de ventas
		if (!rsArticulo.m_CTAVTA.IsEmpty())
		{
			rsAlmacenOrig.m_CUENTA = rsArticulo.m_CTAVTA.Trim();
			rsAlmacenDest.m_CUENTA = rsArticulo.m_CTAVTA.Trim();
		}
		else if (!rsArticulo.m_CTAALQ.IsEmpty())
		{
			rsAlmacenDest.m_CUENTA = rsArticulo.m_CTAALQ.Trim();
			rsAlmacenDest.m_CUENTA = rsArticulo.m_CTAALQ.Trim();
		}

		rsArticulo.Close();

		// Se rellenan los campos para insertar en la tabla INVENTARIO

		// Se rellenan los campos para el almacén ORIGEN
		/////////////////////////////////////////////////////////////////////////////////////
		// Se comprueba si en la tabla Inventario está ya el articulo y el almacén o no
		rsInventarioOrig.m_strFilter = "ARTI LIKE '" + rsAlmacenOrig.m_ARTI + "' AND ALMACEN LIKE '" \
			+ m_strCodAlmacenOrig + "'";

		if (!rsInventarioOrig.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// Si no lo encuentra se inserta
		bInsertarOrig = FALSE;
		if (rsInventarioOrig.m_ARTI.IsEmpty())
		{
			bInsertarOrig = TRUE;
			rsInventarioOrig.m_ARTI = m_lstArticulos.GetItemText(i, 0);
			rsInventarioOrig.m_ALMACEN = m_strCodAlmacenOrig.Trim();
		}

		rsInventarioOrig.Close();

		// Se actualizan las unidades totales y disponibles del artículo y del almacen Origen
		rsInventarioOrig.m_UNITOTAL = rsInventarioOrig.m_UNITOTAL - iTransferidas;
		rsInventarioOrig.m_UNIDISPONIBLE = rsInventarioOrig.m_UNIDISPONIBLE - iTransferidas;

		rsAlmacenOrig.m_CANTITOTAL = rsInventarioOrig.m_UNITOTAL;
		rsAlmacenOrig.m_CANTIDISPONIBLE = rsInventarioOrig.m_UNIDISPONIBLE;
		/////////////////////////////////////////////////////////////////////////////////////


		// Se rellenan los campos para el almacén DESTINO
		/////////////////////////////////////////////////////////////////////////////////////
		// Se comprueba si en la tabla Inventario está ya el articulo y el almacén o no
		rsInventarioDest.m_strFilter = "ARTI LIKE '" + rsAlmacenDest.m_ARTI + "' AND ALMACEN LIKE '" \
			+ m_strCodAlmacenDest + "'";

		if (!rsInventarioDest.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// Si no lo encuentra se inserta
		bInsertarDest = FALSE;
		if (rsInventarioDest.m_ARTI.IsEmpty())
		{
			bInsertarDest = TRUE;
			rsInventarioDest.m_ARTI = m_lstArticulos.GetItemText(i, 0);
			rsInventarioDest.m_ALMACEN = m_strCodAlmacenDest.Trim();
		}

		rsInventarioDest.Close();

		// Se actualizan las unidades totales y disponibles del artículo y del almacen
		rsInventarioDest.m_UNITOTAL = rsInventarioDest.m_UNITOTAL + iTransferidas;
		rsInventarioDest.m_UNIDISPONIBLE = rsInventarioDest.m_UNIDISPONIBLE + iTransferidas;

		rsAlmacenDest.m_CANTITOTAL = rsInventarioDest.m_UNITOTAL;
		rsAlmacenDest.m_CANTIDISPONIBLE = rsInventarioDest.m_UNIDISPONIBLE;
		/////////////////////////////////////////////////////////////////////////////////////

		// Se inserta el movimiento de almacén en la tabla ALMACEN y el número de
		// unidades totales del articulo en la tabla ARTICULO

		if ( !m_db->BeginTrans())
	        return;

		hErr = rsAlmacenOrig.Insert();
		if (hErr == S_OK)
			hErr = rsAlmacenDest.Insert();

		if (hErr == S_OK)
		{
			if (bInsertarOrig)
				hErr = rsInventarioOrig.Insert();
			else
			{
				hErr = rsInventarioOrig.UpdateUniDisponible();
				if (hErr == S_OK)
					rsInventarioOrig.UpdateUniTotal();
			}		

			if (hErr == S_OK)
			{
				if (bInsertarDest)
					hErr = rsInventarioDest.Insert();
				else
				{
					hErr = rsInventarioDest.UpdateUniDisponible();
					if (hErr == S_OK)
						rsInventarioDest.UpdateUniTotal();
				}		
			}
		}

		if (hErr == S_OK)
			m_db->CommitTrans();
		else
			m_db->Rollback();
	}

	LimpiaVentana(TRUE);

	//OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgTransferencias::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgTransferencias::BuscaArticulo()
{
	/* Se carga el listCtrl con el código, la descripción y el número de exitencias  */
	CArticulo rsArticulo(m_db);
	CInventario rsInventario(m_db);

	// Se recogen los datos de los controles
	UpdateData(TRUE);

	// Se comprueba si el articulo está en la tabla inventario. Si no hay ningún almacen
	// seleccionado se sale y se da error
	if (m_strCodAlmacenOrig.IsEmpty())
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_NO_ALMACEN_ORIG);
		return;
	}

	// Se comprueba si el articulo está en la tabla inventario. Si no hay ningún almacen
	// seleccionado se sale y se da error
	if (m_strCodAlmacenDest.IsEmpty())
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_NO_ALMACEN_DEST);
		return;
	}

	/* Se comprueba si ese artículo ya está en el CListCtrl. Para ello se busca el
	elemento, si lo encuentra devuelve el índice de la fila donde lo encontro y si
	no, devuelve el indice de la última fila o -1 */
	LVFINDINFO info;
	int iIndex;
	
	info.flags = LVFI_STRING | LVFI_WRAP;
	info.psz = m_strCodArti;
	iIndex = m_lstArticulos.FindItem(&info);
	if ( iIndex != m_iNumArti && iIndex != -1)
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_ARTI_YA_EN_LISTA);
		return;
	}

	// Se busca el artículo
	rsArticulo.m_strFilter = "ARTI LIKE '" + m_strCodArti + "'";
	if (!rsArticulo.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si el articulo no se encuentra salimos reseteando el campo
	if (rsArticulo.m_ARTI.IsEmpty())
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_ARTI_NO_EXISTS);
		return;
	}

	rsInventario.m_strFilter = "ARTI LIKE '" + m_strCodArti + "' AND ALMACEN LIKE '" + m_strCodAlmacenOrig + "'";
	if (!rsInventario.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_lstArticulos.SetItemText(m_iNumArti, 0, rsArticulo.m_ARTI.Trim());
	m_lstArticulos.SetItemBkColor(m_iNumArti, 0, RGB(183, 183, 183), TRUE);
	m_lstArticulos.SetItemText(m_iNumArti, 1, rsArticulo.m_DESARTI.Trim());
	m_lstArticulos.SetItemBkColor(m_iNumArti, 1, RGB(183, 183, 183), TRUE);

	// Si no hay entrada en la tabla de inventario las unidades serán 0
	CString strUniTotal, strUniDisponible;
	if (!rsInventario.m_ARTI.IsEmpty())
	{
		strUniTotal.Format("%d", rsInventario.m_UNITOTAL);
		strUniDisponible.Format("%d", rsInventario.m_UNIDISPONIBLE);
	}
	else
	{
		strUniTotal = "0";
		strUniDisponible = "0";
	}

	m_lstArticulos.SetItemText(m_iNumArti, 2, strUniTotal);
	m_lstArticulos.SetItemBkColor(m_iNumArti, 2, RGB(183, 183, 183), TRUE);
	m_lstArticulos.SetItemText(m_iNumArti, 3, strUniDisponible);
	m_lstArticulos.SetItemBkColor(m_iNumArti, 3, RGB(183, 183, 183), TRUE);
	m_lstArticulos.SetItemText(m_iNumArti, 4, "0");

	rsArticulo.Close();
	rsInventario.Close();

	m_iNumArti++;

	m_strTransferenciaOld = "0";

	InsertaRegistroVacio();

	// Se deshabilita el botón de Buscar y Eliminar
//	GetDlgItem(IDBUSCAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);
}

/******************************************************************************************/
BOOL CDlgTransferencias::BuscaAlmacen(BOOL bOrigen)
{
	CCuentas rsCuentas(m_db);
	BOOL bStatus;
	CString strCodAlmacen;

	if (bOrigen)
		strCodAlmacen = m_strCodAlmacenOrig;
	else
		strCodAlmacen = m_strCodAlmacenDest;
	
	rsCuentas.m_strFilter = "CUENTA LIKE '" + strCodAlmacen + "'";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el almacén no se encuentra salimos reseteando el campo
	if (rsCuentas.m_CUENTA.IsEmpty())
	{
		AfxMessageBox(IDS_ALMACEN_NO_EXISTS);
		bStatus = FALSE;
	}
	else
	{	
		// Se comprueba que realmente sea una cuenta de almacén. Para ello debe empezar
		// por 3 y tener 9 dígitos
		if (strCodAlmacen.Left(1) == '3' && strCodAlmacen.GetLength() == 9)
		{
			if (bOrigen)
				m_strDesAlmacenOrig = rsCuentas.m_NOMBRE.Trim();	
			else
				m_strDesAlmacenDest = rsCuentas.m_NOMBRE.Trim();		
			bStatus = TRUE;
		}
		else
		{
			AfxMessageBox(IDS_ALMACEN_NO_VALIDO);
			bStatus = FALSE;
		}
	}
	
	return bStatus;
}

/******************************************************************************************/
BOOL CDlgTransferencias::BuscaDocumento()
{
	CConcepto rsConcepto(m_db);

	rsConcepto.m_strFilter = "CONCEPTO LIKE '" + m_strCodDoc + "'";
	if (!rsConcepto.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el almacén no se encuentra salimos reseteando el campo
	if (rsConcepto.m_CONCEPTO.IsEmpty())
	{
		AfxMessageBox(IDS_DOC_NO_EXISTS);
		return FALSE;
	}
	else
	{
		m_strDesDoc = rsConcepto.m_DCONCEPTO;
		return TRUE;
	}
}

/******************************************************************************************/
BOOL CDlgTransferencias::CompruebaAlmacenOrig()
{
	BOOL bRes = TRUE;
	CString strOldCodAlmacenOrig;

	strOldCodAlmacenOrig = m_strCodAlmacenOrig;

	GetDlgItem(IDC_EDIT_ALMACEN)->GetWindowText(m_strCodAlmacenOrig);

	if (strOldCodAlmacenOrig != m_strCodAlmacenOrig)
	{
		if (BuscaAlmacen(TRUE))
		{
			if (!m_strCodAlmacenDest.IsEmpty() && m_strCodAlmacenDest == m_strCodAlmacenOrig)
			{
				AfxMessageBox(IDS_MISMO_ALMACEN);
				bRes = FALSE;
			}
			else
			{
				if (!strOldCodAlmacenOrig.IsEmpty())
					LimpiaVentana(FALSE);  // Con FALSE no limpia los campos del almacen
				else
					GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacenOrig);

				if (!m_strCodAlmacenDest.IsEmpty())
					GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);

				bRes = TRUE;
			}
		}
		else
			bRes = FALSE;
	}	

	if (!bRes)
	{
		m_strCodAlmacenOrig = strOldCodAlmacenOrig;
		GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strCodAlmacenOrig);
	}

	return bRes;
}

/******************************************************************************************/
BOOL CDlgTransferencias::CompruebaAlmacenDest()
{
	BOOL bRes = TRUE;
	CString strOldCodAlmacenDest;

	strOldCodAlmacenDest = m_strCodAlmacenDest;

	GetDlgItem(IDC_EDIT_ALMACEN2)->GetWindowText(m_strCodAlmacenDest);

	if (strOldCodAlmacenDest != m_strCodAlmacenDest)
	{
		if (BuscaAlmacen(FALSE))
		{
			if (!m_strCodAlmacenOrig.IsEmpty() && m_strCodAlmacenOrig == m_strCodAlmacenDest)
			{
				AfxMessageBox(IDS_MISMO_ALMACEN);
				bRes = FALSE;
			}
			else 
			{
				if (!strOldCodAlmacenDest.IsEmpty())
					LimpiaVentana(FALSE);  // Con FALSE no limpia los campos del almacen
				else
					GetDlgItem(IDC_EDIT_DESALMACEN2)->SetWindowText(m_strDesAlmacenDest);

				if (!m_strCodAlmacenOrig.IsEmpty())
					GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);

				bRes = TRUE;
			}
		}
		else
			bRes = FALSE;
	}	

	if (!bRes)
	{
		m_strCodAlmacenDest = strOldCodAlmacenDest;
		GetDlgItem(IDC_EDIT_ALMACEN2)->SetWindowText(m_strCodAlmacenDest);
	}

	return bRes;
}

/******************************************************************************************/
BOOL CDlgTransferencias::CompruebaDocumento()
{
	CString strOldCodDoc;

	strOldCodDoc = m_strCodDoc;

	GetDlgItem(IDC_EDIT_DOCUMENTO)->GetWindowText(m_strCodDoc);

	if (strOldCodDoc != m_strCodDoc)
	{
		if (BuscaDocumento())
			return TRUE;		
		else
		{
			m_strCodDoc = strOldCodDoc;
			UpdateData(FALSE);
			return FALSE;
		}

	}

	return TRUE;
}

/******************************************************************************************/
BOOL CDlgTransferencias::CompruebaObservaciones()
{
	GetDlgItem(IDC_EDIT_OBSERVACIONES)->GetWindowText(m_strObservaciones);
	if (m_strObservaciones.GetLength() > 35)
	{
		m_strObservaciones.Empty();
		GetDlgItem(IDC_EDIT_OBSERVACIONES)->SetWindowText(m_strObservaciones);
		AfxMessageBox(IDS_OBSER_LARGO);
		return FALSE;
	}
	return TRUE;
}

/******************************************************************************************/
void CDlgTransferencias::InsertaRegistroVacio()
{
	m_lstArticulos.InsertItem(m_iNumArti, _T(""));
	m_lstArticulos.SetItemText(m_iNumArti, 0, "");
	m_lstArticulos.SetItemText(m_iNumArti, 1, "");
	m_lstArticulos.SetItemText(m_iNumArti, 2, "");
	m_lstArticulos.SetItemText(m_iNumArti, 3, "");
	m_lstArticulos.SetItemText(m_iNumArti, 4, "");

	m_lstArticulos.EnsureVisible(m_iNumArti, FALSE);
}

/******************************************************************************************/
void CDlgTransferencias::LimpiaVentana(BOOL bAlmacen)
{
	m_timeFecha = CTime::GetCurrentTime();
	IniDocumento();
	m_strObservaciones.Empty();
	m_lstArticulos.DeleteAllItems();	

	if (bAlmacen)
	{
		m_strCodAlmacenOrig.Empty();
		m_strDesAlmacenOrig.Empty();
		m_strCodAlmacenDest.Empty();
		m_strDesAlmacenDest.Empty();
		GetDlgItem(IDBUSCAR)->EnableWindow(FALSE);
	}

	m_iNumArti = 0;

	UpdateData(FALSE);

	InsertaRegistroVacio();

	// Se deshabilita el botón de Buscar y Eliminar y Aceptar
	GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}


/******************************************************************************************/
void CDlgTransferencias::IniDocumento()
{
	CConcepto rsConcepto(m_db);

	rsConcepto.m_strSort = "CONCEPTO";
	rsConcepto.m_strFilter = "CONCEPTO LIKE 'RG%'";
	if (!rsConcepto.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si el almacén no se encuentra salimos reseteando el campo
	if (rsConcepto.m_CONCEPTO.IsEmpty())
	{
		m_strCodDoc.Empty();
		m_strDesDoc.Empty();
	}
	else
	{
		m_strCodDoc = rsConcepto.m_CONCEPTO;
		m_strDesDoc = rsConcepto.m_DCONCEPTO;
	}	
}

/******************************************************************************************/
void CDlgTransferencias::ComprobarTransferencia()
{
	CString strTransferencia;

	int iUniDisponible = atoi(m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 3));

	/* Se cogen las unidades a transferir */
	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	m_lstArticulos.GetEditControl()->GetLine(0, strTransferencia.GetBuffer(len), len);
	strTransferencia.ReleaseBuffer(len);

	//strTransferencia = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 4);

	// Primero se debe comprobar si efectivamente es un dígito (como puede ser negativo
	// se da por válido el carácter '-' si es el primero
	for (int i = 0; i<strTransferencia.GetLength(); i++)
	{
		if ((strTransferencia.GetAt(i) < '0' || strTransferencia.GetAt(i) > '9') && 
			(strTransferencia.GetAt(i) != '-' || (strTransferencia.GetAt(i) == '-' && i != 0)))
		{
			m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 4, m_strTransferenciaOld);
			return;
		}
	}

	int iTransferencia = abs(atoi(strTransferencia));			

//	if (iTransferencia != 0)
//	{
		if (iUniDisponible - iTransferencia < 0)
		{
			// Para evitar que entre una segunda vez
			if (m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 4) != "0")
			{
				m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, 4, "0");	
				AfxMessageBox(IDS_NO_TRANSFERENCIA);
			}
		}
		else
		{
			m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, 4, strTransferencia);	
			m_strTransferenciaOld = strTransferencia;
		}
//	}
}


