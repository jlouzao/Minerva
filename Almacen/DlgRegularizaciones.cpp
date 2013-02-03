// DlgRegularizaciones.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgRegularizaciones.h"
#include ".\dlgregularizaciones.h"
#include "BD.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgRegularizaciones
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgRegularizaciones, CDialog)
CDlgRegularizaciones::CDlgRegularizaciones(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRegularizaciones::IDD, pParent)
	, m_timeFecha(0)
	, m_strCodAlmacen(_T(""))
	, m_strDesAlmacen(_T(""))
	, m_strCodDoc(_T(""))
	, m_strObservaciones(_T(""))
	, m_strDesDoc(_T(""))
{
	m_strCodArti = " ";
	m_iNumArti = 0;
	m_strVariacionOld = "0";
}

/******************************************************************************************/
CDlgRegularizaciones::~CDlgRegularizaciones()
{
}

/******************************************************************************************/
void CDlgRegularizaciones::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_FECHA, m_timeFecha);
	DDX_Text(pDX, IDC_EDIT_ALMACEN, m_strCodAlmacen);
	DDX_Text(pDX, IDC_EDIT_DESALMACEN, m_strDesAlmacen);
	DDX_Text(pDX, IDC_EDIT_DOCUMENTO, m_strCodDoc);
	DDX_Text(pDX, IDC_EDIT_OBSERVACIONES, m_strObservaciones);
	DDX_Control(pDX, IDC_LSTARTICULOS, m_lstArticulos);
	DDX_Text(pDX, IDC_EDIT_DESDOC, m_strDesDoc);
	DDV_MaxChars(pDX, m_strObservaciones, 35);
	DDX_Control(pDX, IDC_EDIT_ALMACEN, m_ctrlAlmacen);
	DDX_Control(pDX, IDC_EDIT_OBSERVACIONES, m_ctrlObservaciones);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgRegularizaciones, CDialog)
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
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgRegularizaciones
/******************************************************************************************/

BOOL CDlgRegularizaciones::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece el estilo	
	//m_lstArticulos.SetExtendedStyle(m_lstArticulos.GetExtendedStyle()|LVS_EX_GRIDLINES);
	m_lstArticulos.SetGridLines(TRUE);

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 105);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 200);
	m_lstArticulos.InsertColumn(2,"Existencias", LVCFMT_LEFT, 74);
	m_lstArticulos.InsertColumn(3,"Disponibles", LVCFMT_LEFT, 73);
	m_lstArticulos.InsertColumn(4,"Variación", LVCFMT_LEFT, 73);
	m_lstArticulos.InsertColumn(5,"Regularizado", LVCFMT_LEFT, 74);

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

	UpdateData(FALSE);

	// Se inicializa el flag
	m_bFocusListCtrl = FALSE;

	m_ctrlAlmacen.SetFocus();

	return FALSE;  // Devuelve TRUE  a menos que establezca el foco en un control
}


/******************************************************************************************/
void CDlgRegularizaciones::OnBnClickedBuscar()
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
BOOL CDlgRegularizaciones::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

/******************************************************************************************/

void CDlgRegularizaciones::OnNMSetfocusLstarticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Se pone editable el editbox del artículo
	/*if (this->IsWindowVisible() && m_lstArticulos.m_ptEditting.x == -1 && 
		m_lstArticulos.m_ptEditting.y == -1 && /*(m_lstArticulos.GetEditControl()->GetSafeHwnd() == NULL)*/
		/*m_iNumArti == 0 && !m_bFocusListCtrl)*/
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

	GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);

	// Se habilita el botón de Buscar
//	if (m_lstArticulos.m_ptEditting.y == 0 && m_lstArticulos.m_ptEditting.x == m_iNumArti)
//	GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);

	*pResult = 0;
}

/******************************************************************************************/
LRESULT CDlgRegularizaciones::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
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
		m_lstArticulos.m_ptEditting.y == 3 || m_lstArticulos.m_ptEditting.y == 5)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	// Si estamos en la primera columna y ya tiene algo no se puede modificar
	else if (m_lstArticulos.m_ptEditting.y == 0 && !strCod.IsEmpty())
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	else if	(m_lstArticulos.m_ptEditting.y == 0 || m_lstArticulos.m_ptEditting.y == 4)
		m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);

	// Si estoy en la cuarta columna se actualiza el campo Regularizadas
	if (m_lstArticulos.m_ptEditting.y == 4 && !strCod.IsEmpty())
		ActualizaVariacion();

//	if (m_lstArticulos.m_ptEditting.y != 0)
//	GetDlgItem(IDBUSCAR)->EnableWindow(FALSE);

	return hErr;
}

/******************************************************************************************/
void CDlgRegularizaciones::OnNMClickLstarticulos(NMHDR *pNMHDR, LRESULT *pResult)
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
void CDlgRegularizaciones::OnBnClickedEliminar()
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
void CDlgRegularizaciones::OnEnKillfocusEditAlmacen()
{
	CompruebaAlmacen();
}

/******************************************************************************************/
void CDlgRegularizaciones::OnBnClickedBtnAlmacen()
{
	INT_PTR status;
	CString strOldCodAlmacen;

	strOldCodAlmacen = m_strCodAlmacen;

	m_dlgBusquedaAlmacen.SetTipo(CDialogBusqueda::ALMACEN);
	status = m_dlgBusquedaAlmacen.DoModal();
	if (status == IDOK)
	{
		m_strCodAlmacen = m_dlgBusquedaAlmacen.GetCodigo();
		m_strCodAlmacen = m_strCodAlmacen.Trim();
		m_strDesAlmacen = m_dlgBusquedaAlmacen.GetDescripcion();

		// Si es la primera vez que se elige un almacén se escriba en los textbox
		if (strOldCodAlmacen.IsEmpty())
		{
			GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strCodAlmacen);
			GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);
		}
		else if (strOldCodAlmacen != m_strCodAlmacen)
			LimpiaVentana(FALSE);  // Con FALSE no limpia los campos del almacen

		if (!m_strCodAlmacen.IsEmpty()) // Por si han dado a Aceptar pero no hay ninguno seleccionado
			GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);
	}	
}

/******************************************************************************************/
void CDlgRegularizaciones::OnEnKillfocusEditDocumento()
{
	CompruebaDocumento();
}

/******************************************************************************************/
void CDlgRegularizaciones::OnBnClickedBtnDocumento()
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
void CDlgRegularizaciones::OnEnKillfocusEditObservaciones()
{
	m_bFocusListCtrl = TRUE;
	if (!CompruebaObservaciones())	
		m_ctrlObservaciones.SetFocus();
	else
		m_bFocusListCtrl = FALSE;
}

/******************************************************************************************/
void CDlgRegularizaciones::OnLvnInsertitemLstarticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// Si un elemento se activa el botón aceptar
	if (m_lstArticulos.GetItemCount() > 0)
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	
	*pResult = 0;
}

/******************************************************************************************/
void CDlgRegularizaciones::OnBnClickedOk()
{
	HRESULT hErr;

	// Se comprueba que todos los datos sean datos existentes
	if (!CompruebaAlmacen())
		return;
	if (!CompruebaDocumento())
		return;
	if (!CompruebaObservaciones())
		return;

	// Se recogen los datos de los controles
	UpdateData(TRUE);

	// Indica que se cambio la variación de algún item y no se ha recogido el resultado así que
	// no se modificará ese articulo
	/*if (m_bCambioVariacion)
		m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 3, "0");*/

	CAlmacen rsAlmacen(m_db);

	// Se inicializan los campos comunes
	rsAlmacen.m_ALMACEN = m_strCodAlmacen.Trim();
	rsAlmacen.m_FECHA = m_timeFecha;
	rsAlmacen.m_TIPOMOV = m_strCodDoc.Trim();
	rsAlmacen.m_OBSER = m_strObservaciones.Trim();
	rsAlmacen.m_NDOC = 0;

	BOOL bInsertar = FALSE;

	for (int i=0; i < m_lstArticulos.GetItemCount(); i++)
	{	
		CArticulo rsArticulo(m_db);
		CInventario rsInventario(m_db);

		// El item vacío no debe procesarse
		if (m_lstArticulos.GetItemText(i, 0) == "")
			continue;

		rsAlmacen.m_ARTI = m_lstArticulos.GetItemText(i, 0);

		// La cantidad de movimiento del almacén será la variación. 
		int iExistencias = atoi(m_lstArticulos.GetItemText(i, 2));
		int iVariacion = atoi(m_lstArticulos.GetItemText(i, 4));
		int iRegularizadas = atoi(m_lstArticulos.GetItemText(i, 5));

		if (iVariacion == 0)
			continue;

		if ((iExistencias + iVariacion) != iRegularizadas && iVariacion != 0)
		{
			CString strMsg;
			strMsg.Format(IDS_NO_REGULARIZACION, rsAlmacen.m_ARTI);			
			AfxMessageBox(strMsg);
			continue;
		}

		// Se rellenan los campos para insertar en la tabla ALMACEN
		rsAlmacen.m_CANTI = iVariacion;

		rsArticulo.m_strFilter = "ARTI LIKE '" + rsAlmacen.m_ARTI + "'";
		if (!rsArticulo.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// La cuenta será la cuenta de ventas o de alquiler. Se coge la que esté rellena
		// de las 2 o si lo están las dos, se coge la de ventas
		if (!rsArticulo.m_CTAVTA.IsEmpty())
			rsAlmacen.m_CUENTA = rsArticulo.m_CTAVTA.Trim();
		else if (!rsArticulo.m_CTAALQ.IsEmpty())
			rsAlmacen.m_CUENTA = rsArticulo.m_CTAALQ.Trim();

		rsArticulo.Close();

		// Se rellenan los campos para insertar en la tabla INVENTARIO

		// Se comprueba si en la tabla Inventario está ya el articulo y el almacén o no
		rsInventario.m_strFilter = "ARTI LIKE '" + rsAlmacen.m_ARTI + "' AND ALMACEN LIKE '" \
			+ m_strCodAlmacen + "'";

		if (!rsInventario.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// Si no lo encuentra se inserta
		bInsertar = FALSE;
		if (rsInventario.m_ARTI.IsEmpty())
		{
			bInsertar = TRUE;
			rsInventario.m_ARTI = m_lstArticulos.GetItemText(i, 0);
			rsInventario.m_ALMACEN = m_strCodAlmacen.Trim();
		}

		rsInventario.Close();

		// Se actualizan las unidades totales y disponibles del artículo y del almacén
		rsInventario.m_UNITOTAL = rsInventario.m_UNITOTAL + iVariacion;
		rsInventario.m_UNIDISPONIBLE = rsInventario.m_UNIDISPONIBLE + iVariacion;

		rsAlmacen.m_CANTITOTAL = rsInventario.m_UNITOTAL;
		rsAlmacen.m_CANTIDISPONIBLE = rsInventario.m_UNIDISPONIBLE;

		// Se inserta el movimiento de almacén en la tabla ALMACEN y el número de
		// unidades totales del articulo en la tabla ARTICULO

		if ( !m_db->BeginTrans())
	        return;

		hErr = rsAlmacen.Insert();

		if (hErr == S_OK)
		{
			if (bInsertar)
				hErr = rsInventario.Insert();
			else
			{
				hErr = rsInventario.UpdateUniDisponible();
				if (hErr == S_OK)
					rsInventario.UpdateUniTotal();
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
void CDlgRegularizaciones::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgRegularizaciones::BuscaArticulo()
{
	// Se recogen los datos de los controles
	UpdateData(TRUE);

	//Si no hay ningún almacen seleccionado se sale y se da error
	if (m_strCodAlmacen.IsEmpty())
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_NO_ALMACEN);
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

	/* Se carga el listCtrl con el código, la descripción y el número de exitencias  */
	CArticulo rsArticulo(m_db);
	CInventario rsInventario(m_db);

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

	// Se comprueba si el articulo está en la tabla inventario. 
	rsInventario.m_strFilter = "ARTI LIKE '" + m_strCodArti + "' AND ALMACEN LIKE '" + m_strCodAlmacen + "'";
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
	CString strUniDisponible, strUniTotales;
	if (!rsInventario.m_ARTI.IsEmpty())
	{
		strUniTotales.Format("%d", rsInventario.m_UNITOTAL);
		strUniDisponible.Format("%d", rsInventario.m_UNIDISPONIBLE);
	}
	else
	{
		strUniTotales = "0";
		strUniDisponible = "0";
	}

	m_lstArticulos.SetItemText(m_iNumArti, 2, strUniTotales);
	m_lstArticulos.SetItemBkColor(m_iNumArti, 2, RGB(183, 183, 183), TRUE);
	m_lstArticulos.SetItemText(m_iNumArti, 3, strUniDisponible);
	m_lstArticulos.SetItemBkColor(m_iNumArti, 3, RGB(183, 183, 183), TRUE);
	m_lstArticulos.SetItemText(m_iNumArti, 4, "0");
	m_lstArticulos.SetItemText(m_iNumArti, 5, "0");
	m_lstArticulos.SetItemBkColor(m_iNumArti, 5, RGB(183, 183, 183), TRUE);

//	m_lstArticulos.SetItemStates(m_iNumArti, RC_ITEM_UNSELECTED);

	rsArticulo.Close();
	rsInventario.Close();
	
	m_iNumArti++;

	m_strVariacionOld = "0";

	InsertaRegistroVacio();

	// Se deshabilita el botón de Buscar y Eliminar
//	GetDlgItem(IDBUSCAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ELIMINAR)->EnableWindow(FALSE);
}

/******************************************************************************************/
BOOL CDlgRegularizaciones::BuscaAlmacen()
{
	CCuentas rsCuentas(m_db);
	BOOL bStatus;

	rsCuentas.m_strFilter = "CUENTA LIKE '" + m_strCodAlmacen + "'";
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
		if (m_strCodAlmacen.Left(1) == '3' && m_strCodAlmacen.GetLength() == 9)
		{
			m_strDesAlmacen = rsCuentas.m_NOMBRE.Trim();		
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
BOOL CDlgRegularizaciones::BuscaDocumento()
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
BOOL CDlgRegularizaciones::CompruebaAlmacen()
{
	CString strOldCodAlmacen;

	strOldCodAlmacen = m_strCodAlmacen;

	GetDlgItem(IDC_EDIT_ALMACEN)->GetWindowText(m_strCodAlmacen);

	if (strOldCodAlmacen != m_strCodAlmacen)
	{
		if (BuscaAlmacen())
		{
			if (!strOldCodAlmacen.IsEmpty())
				LimpiaVentana(FALSE);  // Con FALSE no limpia los campos del almacen
			else
				GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);

			GetDlgItem(IDBUSCAR)->EnableWindow(TRUE);
			return TRUE;
		}
		else
		{
			m_strCodAlmacen = strOldCodAlmacen;
			GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strCodAlmacen);
			return FALSE;
		}
	}	

	return TRUE;
}

/******************************************************************************************/
BOOL CDlgRegularizaciones::CompruebaDocumento()
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
BOOL CDlgRegularizaciones::CompruebaObservaciones()
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
void CDlgRegularizaciones::InsertaRegistroVacio()
{
	m_lstArticulos.InsertItem(m_iNumArti, _T(""));
	m_lstArticulos.SetItemText(m_iNumArti, 0, "");
	m_lstArticulos.SetItemText(m_iNumArti, 1, "");
	m_lstArticulos.SetItemText(m_iNumArti, 2, "");
	m_lstArticulos.SetItemText(m_iNumArti, 3, "");
	m_lstArticulos.SetItemText(m_iNumArti, 4, "");
	m_lstArticulos.SetItemText(m_iNumArti, 5, "");

	m_lstArticulos.EnsureVisible(m_iNumArti, FALSE);
}

/******************************************************************************************/
void CDlgRegularizaciones::LimpiaVentana(BOOL bAlmacen)
{
	m_timeFecha = CTime::GetCurrentTime();
	IniDocumento();
	m_strObservaciones.Empty();
	m_lstArticulos.DeleteAllItems();	

	if (bAlmacen)
	{
		m_strCodAlmacen.Empty();
		m_strDesAlmacen.Empty();
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
void CDlgRegularizaciones::IniDocumento()
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
void CDlgRegularizaciones::ActualizaVariacion()
{
	int iUniTotal, iUniDisponible, iVariacion;
	CString strVariacion, strRegularizadas;
		
	iUniTotal = atoi(m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 2));
	iUniDisponible = atoi(m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 3));

	/* Se coge la variacion */
	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	m_lstArticulos.GetEditControl()->GetLine(0, strVariacion.GetBuffer(len), len);
	strVariacion.ReleaseBuffer(len);

	// Primero se debe comprobar si efectivamente es un dígito (como puede ser negativo
	// se da por válido el carácter '-' si es el primero
	for (int i = 0; i<strVariacion.GetLength(); i++)
	{
		if ((strVariacion.GetAt(i) < '0' || strVariacion.GetAt(i) > '9') && 
			(strVariacion.GetAt(i) != '-' || (strVariacion.GetAt(i) == '-' && i != 0)))
		{
			m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 4, m_strVariacionOld);
			return;
		}
	}

	m_strVariacionOld = strVariacion;

	//strVariacion = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 3);
	iVariacion = atoi(strVariacion);			

	//if (iVariacion != 0 || (iVariacion == 0 && 
	//	m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 2)!= m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 5)))

	if (iVariacion != 0)
	{
		if (iUniDisponible + iVariacion >= 0)
		{
			strRegularizadas.Format("%d", iUniTotal + iVariacion);
			m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, 4, strVariacion);	
			m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, 5, strRegularizadas);	
		}			
		else
		{
			// Para evitar que entre una segunda vez
			if (m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 4) != "0")
			{
				m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, 4, "0");	
				m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, 5, "0");	
				AfxMessageBox(IDS_NO_REGULARIZACION2);
			}
		}
	}
	else
		m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, 5, "0");	

	return;
}


