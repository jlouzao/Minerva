// DlgPreAlbDespiece.cpp: archivo de implementación
//
/******************************************************************************************/

#include "stdafx.h"
#include "Ventas.h"
#include "DlgPreAlbDespieceEntrega.h"
#include ".\dlgprealbdespieceEntrega.h"
#include "Etiquetas.h"


/******************************************************************************************/
// Cuadro de diálogo de CDlgPreAlbDespieceEntrega
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgPreAlbDespieceEntrega, CDialog)
CDlgPreAlbDespieceEntrega::CDlgPreAlbDespieceEntrega(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAlbDespieceEntrega::IDD, pParent)
	, m_strCuenta(_T(""))
	, m_strNombre(_T(""))
	, m_strPedido(_T(""))
	, m_timeFechaIni(CTime::GetCurrentTime())
	, m_strObservaciones(_T(""))
	, m_dTotalPeso(0)
	, m_strAlmacen(_T(""))
	, m_strNombreAlmacen(_T(""))
{
	m_iNumArti = 0;
}

/******************************************************************************************/
CDlgPreAlbDespieceEntrega::~CDlgPreAlbDespieceEntrega()
{
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ARTICULOS, m_lstArticulos);
	DDX_Text(pDX, IDC_EDIT_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_EDIT_NOMBRE, m_strNombre);
	DDX_Text(pDX, IDC_PEDIDO, m_strPedido);
	DDV_MaxChars(pDX, m_strPedido, 10);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_INI_ALQUILER, m_timeFechaIni);
	DDX_Text(pDX, IDC_OBSER_ALBARAN, m_strObservaciones);
	DDV_MaxChars(pDX, m_strObservaciones, 100);
	DDX_Text(pDX, IDC_EDIT_TOTAL_PESO, m_dTotalPeso);
	DDX_Text(pDX, IDC_ALMACEN, m_strAlmacen);
	DDX_Text(pDX, IDC_NOMBRE_ALMACEN, m_strNombreAlmacen);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgPreAlbDespieceEntrega, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA, OnEnKillfocusEditCuenta)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_EN_KILLFOCUS(IDC_PEDIDO, OnEnKillfocusPedido)
	ON_BN_CLICKED(IDC_BTN_PEDIDO, OnBnClickedBtnPedido)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_BN_CLICKED(ID_BUSCAR, OnBnClickedBuscar)
	ON_BN_CLICKED(ID_ELIMINAR, OnBnClickedEliminar)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ARTICULOS, OnNMClickListArticulos)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ARTICULOS, OnNMSetfocusListArticulos)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_SETFOCUS(IDC_OBSER_ALBARAN, OnEnSetfocusObserAlbaran)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgPreAlbDespieceEntrega
/******************************************************************************************/

/***********************************************************************************************/
BOOL CDlgPreAlbDespieceEntrega::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece el estilo	
	m_lstArticulos.SetGridLines(TRUE);

	// Añadiendo la lista de imágenes se consigue hacer cada casilla más grande
	CImageList m_ImageList;
	m_ImageList.Create(1, 16, ILC_COLOR,1,1); 
	m_lstArticulos.SetImageList(&m_ImageList); 

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 105);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 200);
	m_lstArticulos.InsertColumn(2,"Peso", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(3,"Tipo", LVCFMT_LEFT, 85);
	m_lstArticulos.InsertColumn(4,"Tipo Alquiler", LVCFMT_LEFT, 85);
	m_lstArticulos.InsertColumn(5,"Cantidad", LVCFMT_LEFT, 55);

	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit

	// Se inicializa el primer item todo vacío para permitir escribir en él
	InsertaRegistroVacio();

	m_lOldCantidad.RemoveAll();

	// Se inicializa los array para saber los Tipo de Venta y Alquiler
	m_strTipo.AddTail("S"); m_strTipo.AddTail(ALQUILER);
	m_strTipo.AddTail("V"); m_strTipo.AddTail(VENTA);
	m_strTipo.AddTail("N"); m_strTipo.AddTail(OTROS);
	m_strTipo.AddTail("E"); m_strTipo.AddTail(ENTREGA);
	m_strTipo.AddTail("R"); m_strTipo.AddTail(RECOGIDA);

	m_strTipoAlquiler.AddTail("M"); m_strTipoAlquiler.AddTail(MENSUAL);
	m_strTipoAlquiler.AddTail("D"); m_strTipoAlquiler.AddTail(DIA_LABORABLE);
	m_strTipoAlquiler.AddTail("N"); m_strTipoAlquiler.AddTail(DIA_NATURAL);

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaPedidosCli.SetConexion(m_db);
	m_dlgBusquedaArticulos.SetConexion(m_db);

	GetDlgItem(IDC_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBSER_ALBARAN)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_INI_ALQUILER)->EnableWindow(FALSE);
	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	// Se inicializa el flag
	m_bFocusListCtrl = FALSE;
	m_bObser = FALSE;
	m_bTabObser = FALSE;

	UpdateData(FALSE);

	return TRUE;
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnEnKillfocusEditCuenta()
{
	CString strCuentaOld = m_strCuenta;

	GetDlgItem(IDC_EDIT_CUENTA)->GetWindowText(m_strCuenta);

	if (m_strCuenta == strCuentaOld)
		return;

	if (!m_strCuenta.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCliente())
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCuenta = strCuentaOld;
			GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
			return;
		}
	}
	else
		LimpiaVentana();
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnBnClickedBtnCuenta()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana();

		m_strCuenta = m_dlgBusquedaClientes.GetCodigo();
		m_strNombre = m_dlgBusquedaClientes.GetDescripcion();

		GetDlgItem(IDC_PEDIDO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBSER_ALBARAN)->EnableWindow(TRUE);
		GetDlgItem(IDC_FECHA_INI_ALQUILER)->EnableWindow(TRUE);

		UpdateData(FALSE);
	}
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnEnKillfocusPedido()
{
	CString strPedidoOld = m_strPedido;

	GetDlgItem(IDC_PEDIDO)->GetWindowText(m_strPedido);
	m_strPedido = m_strPedido.Trim();

	if (!m_strPedido.IsEmpty())
	{
		// Si el pedido no existe se deja el anterior y se da un mensaje de error
		if (!BuscaPedido())
		{
			AfxMessageBox(IDC_PEDIDO_NO_EXISTS);
			m_strPedido = strPedidoOld;
			GetDlgItem(IDC_PEDIDO)->SetWindowText(m_strPedido);
		}
	}
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnBnClickedBtnPedido()
{
	INT_PTR status;

	m_dlgBusquedaPedidosCli.SetTipo(CDialogBusqueda::PEDIDOSCLI);
	m_dlgBusquedaPedidosCli.SetCliente(m_strCuenta);

	status = m_dlgBusquedaPedidosCli.DoModal();
	if (status == IDOK)
	{
		m_strPedido = m_dlgBusquedaPedidosCli.GetCodigo();
		BuscaPedido();
		GetDlgItem(IDC_PEDIDO)->SetWindowText(m_strPedido);
	}
}

/******************************************************************************************/
BOOL CDlgPreAlbDespieceEntrega::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if  (pMsg->wParam == VK_TAB)
		{
			// Si se ha pulsado el tabulador y venimos de la casilla de 
			// observaciones, se debe editar la casilla del listCtrl
			if (m_bObser)
				m_bTabObser = TRUE;
		}
	}

	return(CDialog::PreTranslateMessage(pMsg));
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnEnSetfocusObserAlbaran()
{
	m_bObser = TRUE;
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Se comprueba si se ha seleccionado un pedido
	if (!m_bFocusListCtrl)
	{
		m_bFocusListCtrl = TRUE;

		if (m_strCuenta.IsEmpty())
		{
			AfxMessageBox(IDC_NO_CLIENTE);
			m_lstArticulos.EndEdit();
			m_bFocusListCtrl = FALSE;
			return;
		}

		if (m_strPedido.IsEmpty())
		{
			AfxMessageBox(IDC_NO_PEDIDO);
			m_lstArticulos.EndEdit();
			m_bFocusListCtrl = FALSE;
			return;
		}
	}

	// Si se ha pulsado tabulador y venimos de Atn. al Cliente se activa la primera casilla
	if ( !m_strCuenta.IsEmpty() && !m_strPedido.IsEmpty() && m_bTabObser)
	{
		m_lstArticulos.EndItem();
		m_lstArticulos.StartEdit(m_iNumArti, 0);						
		m_bObser = FALSE;
		m_bTabObser = FALSE;
	}

	// Si vamos a la casilla de la descripción pero no hay código se devuelve el foco
	CString strCod = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 0);
	if (m_lstArticulos.m_ptEditting.y == 1 && strCod.IsEmpty())
	{
		m_lstArticulos.EndEdit();
		m_lstArticulos.StartEdit(m_iNumArti, 0);			
	}

	// Se asigna el límite de caracteres de la primer casilla, la del código, a 15 y del
	// resto a 255 que son los máximos que puede tener la descripción detallada
	if (m_lstArticulos.m_ptEditting.y == 0)
		m_lstArticulos.GetEditControl()->SetLimitText(15);

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	*pResult = 0;
}


/******************************************************************************************/
LRESULT CDlgPreAlbDespieceEntrega::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr  = 0;

	// Si el foco va a la primera columna y es una fila vacía
	if (m_lstArticulos.m_ptEditting.y == 0 && m_lstArticulos.m_ptEditting.x == m_iNumArti)
	{
		CString strCodArti;

		/* Se coge el código del artículo */
		int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
		if (len != 0)
		{
			m_lstArticulos.GetEditControl()->GetLine(0, strCodArti.GetBuffer(len), len);
			strCodArti.ReleaseBuffer(len);
			if (!strCodArti.IsEmpty())
				BuscaArticulo(strCodArti);
		}
	}

	// Se obtiene lo que contiene la primera columna
	CString strCod = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 0);

	if ((m_lstArticulos.m_ptEditting.y == 0 && !strCod.IsEmpty()) || m_lstArticulos.m_ptEditting.y == 1
		 || m_lstArticulos.m_ptEditting.y == 2)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	else if (m_lstArticulos.m_ptEditting.y != -1 && m_lstArticulos.m_ptEditting.y != 3 &&
		     m_lstArticulos.m_ptEditting.y != 4)
			m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);

	// Si se cambia la cantidad de artículos se debe recalcular el peso y el precio total
	if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 5)
		CambiaCantidad();

	return hErr;
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnBnClickedBuscar()
{
	m_dlgBusquedaArticulos.SetTipo(CDialogBusqueda::ARTICULOS);
	INT_PTR status = m_dlgBusquedaArticulos.DoModal();

	if (status == IDOK)
	{
		CString strCodArti = m_dlgBusquedaArticulos.GetCodigo();

		/* Busca la obra y se escribe en el listCtrl */
		if (!strCodArti.IsEmpty())
			BuscaArticulo(strCodArti);
	}
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnBnClickedEliminar()
{
	int iIndex;

	// Se busca el indice de la fila a eliminar
	POSITION pos = m_lstArticulos.GetFirstSelectedItemPosition();
	iIndex = m_lstArticulos.GetNextSelectedItem(pos);            

	// Se resta su PESO del total
	// Se descuenta del peso total el peso de este artículo
	double iPeso = atof(m_lstArticulos.GetItemText(iIndex, 2));
	int iCantidad = atoi(m_lstArticulos.GetItemText(iIndex, 5));

	// Primero se debe restar el peso que suponía con la cantidad anterior.
	double dPesoAEliminar = abs(iCantidad) * iPeso;
	m_dTotalPeso -= dPesoAEliminar;

	CString strTotalPeso;
	strTotalPeso.Format("%.3f", m_dTotalPeso);
	GetDlgItem(IDC_EDIT_TOTAL_PESO)->SetWindowText(strTotalPeso);

	// Se elimina de las listas de cantidades antiguas
	m_lOldCantidad.RemoveAt(m_lOldCantidad.FindIndex(iIndex));

	// Se elimina el artículo
	m_lstArticulos.DeleteItem(iIndex);

	m_iNumArti--;

	if (m_iNumArti == 0)
		GetDlgItem(IDOK)->EnableWindow(FALSE);

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Se deshabilita el botón de Eliminar si hay algún elemento seleccionado
	POSITION pos = m_lstArticulos.GetFirstSelectedItemPosition();
	int iIndex = m_lstArticulos.GetNextSelectedItem(pos);            

	if (m_lstArticulos.GetSelectedCount() > 0 && iIndex != m_lstArticulos.GetItemCount()-1)
		GetDlgItem(ID_ELIMINAR)->EnableWindow(TRUE);
	else
		GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	*pResult = 0;
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::OnBnClickedOk()
{
	UpdateData();

	// Si alguna casilla del CListCtrl se ha quedado editable se quita
	if (m_lstArticulos.m_ptEditting.x != -1)
		m_lstArticulos.EndEdit();

	// Se guarda el nuevo albarán
	GuardaAlbaran();

	//OnOK();
}


/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsPedido.m_pDatabase = db;
	m_rsAlbaran.m_pDatabase = db;
}

/******************************************************************************************/
BOOL CDlgPreAlbDespieceEntrega::BuscaCliente()
{
	BOOL bExists = FALSE;
	CClientes rsClientes(m_db);

	rsClientes.m_strFilter = "CUENTA LIKE '" + m_strCuenta + "'";
	if (!rsClientes.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el cliente existe se rellenan sus campos 
	if (!rsClientes.m_CUENTA.IsEmpty())
	{
		LimpiaVentana();

		m_strCuenta = rsClientes.m_CUENTA.Trim();
		m_strNombre = rsClientes.m_NOMBRE.Trim();

		GetDlgItem(IDC_PEDIDO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBSER_ALBARAN)->EnableWindow(TRUE);
		GetDlgItem(IDC_FECHA_INI_ALQUILER)->EnableWindow(TRUE);

		bExists = TRUE;

	}

	rsClientes.Close();

	UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
BOOL CDlgPreAlbDespieceEntrega::BuscaPedido()
{
	BOOL bExists = FALSE;

	if (m_rsPedido.IsOpen())
		m_rsPedido.Close();

	m_rsPedido.m_strFilter = "NUMPEDIDO = '" + m_strPedido + "' AND CUENTA = '" + m_strCuenta + "'";
	if (!m_rsPedido.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se indica
	if (!m_rsPedido.m_NUMPEDIDO.IsEmpty())
	{
		m_strAlmacen = m_rsPedido.m_ALMACEN.Trim();
		BuscaDesAlmacen();

		GetDlgItem(IDC_ALMACEN)->SetWindowText(m_strAlmacen);
		GetDlgItem(IDC_NOMBRE_ALMACEN)->SetWindowText(m_strNombreAlmacen);

		GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);

		bExists = TRUE;
	}

	m_rsPedido.Close();

	return bExists;
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::InsertaRegistroVacio()
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
void CDlgPreAlbDespieceEntrega::LimpiaVentana()
{
	m_strCuenta.Empty();
	m_strNombre.Empty();
	m_strPedido.Empty();
	m_strAlmacen.Empty();
	m_strNombreAlmacen.Empty();
	m_dTotalPeso = 0;
	m_timeFechaIni = CTime::GetCurrentTime();
	m_strObservaciones.Empty();

	m_lstArticulos.DeleteAllItems();
	m_iNumArti = 0;

	// Se inicializa el primer item todo vacío para permitir escribir en él
	InsertaRegistroVacio();

	GetDlgItem(IDC_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBSER_ALBARAN)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_INI_ALQUILER)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_dlgBusquedaPedidosCli.InicializarListas();

	m_lOldCantidad.RemoveAll();

	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::BuscaArticulo(CString strCodArti)
{
	/* Se carga el listCtrl con el Código, la Descripción, el Tipo, el Tipo de Alquiler
	y la tarifa */
	CArticulo rsArticulo(m_db);
	
	/* Se comprueba si ese artículo ya está en el CListCtrl. Para ello se busca el
	elemento, si lo encuentra devuelve el índice de la fila donde lo encontro y si
	no, devuelve el indice de la última fila o -1 */
	LVFINDINFO info;
	int iIndex;
	
	info.flags = LVFI_STRING | LVFI_WRAP;
	info.psz = strCodArti;
	iIndex = m_lstArticulos.FindItem(&info);
	if ( iIndex != m_iNumArti && iIndex != -1)
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_ARTI_YA_EN_LISTA);
		return;
	}

	// Se busca el artículo
	rsArticulo.m_strFilter = "ARTI LIKE '" + strCodArti + "'";
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

	// Si es si primer artículo ponemos el botón de aceptar a TRUE
	if (m_iNumArti == 0)
		GetDlgItem(IDOK)->EnableWindow(TRUE);

	m_lstArticulos.SetItemText(m_iNumArti, 0, rsArticulo.m_ARTI.Trim());
	m_lstArticulos.SetItemBkColor(m_iNumArti, 0, RGB(183, 183, 183), TRUE);
	m_lstArticulos.SetItemText(m_iNumArti, 1, rsArticulo.m_DESARTI.Trim());
	m_lstArticulos.SetItemBkColor(m_iNumArti, 1, RGB(183, 183, 183), TRUE);

	CString strPeso;
	strPeso.Format("%.3f", rsArticulo.m_PESO);
	m_lstArticulos.SetItemText(m_iNumArti, 2, strPeso);
	m_lstArticulos.SetItemBkColor(m_iNumArti, 2, RGB(183, 183, 183), TRUE);

	// Se busca el tipo de venta y de alquiler
	POSITION pos = m_strTipo.Find(rsArticulo.m_ALQUILER);	
	if (pos != NULL)
	{
		m_strTipo.GetNext(pos);
		m_lstArticulos.SetItemText(m_iNumArti, 3, m_strTipo.GetNext(pos));
	}
	else
		m_lstArticulos.SetItemText(m_iNumArti, 3, "");

	if (rsArticulo.m_ALQUILER == "S") // Se busca el tipo de alquiler sólo si es tipo Alquiler
	{
		pos = m_strTipoAlquiler.Find(rsArticulo.m_TIPOALQ);	
		if (pos != NULL)
		{
			m_strTipoAlquiler.GetNext(pos);
			m_lstArticulos.SetItemText(m_iNumArti, 4, m_strTipoAlquiler.GetNext(pos));
		}
		else
			m_lstArticulos.SetItemText(m_iNumArti, 4, "");
	}
	else
		m_lstArticulos.SetItemText(m_iNumArti, 4, "");

	// Se escribe la cantidad
	m_lstArticulos.SetItemText(m_iNumArti, 5, "0");
	m_lOldCantidad.AddTail((int)0);

	rsArticulo.Close();

	m_iNumArti++;

	InsertaRegistroVacio();

	// Se deshabilita el botón de Eliminar
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
}

/******************************************************************************************/
/*  Si cambia la cantidad se debe recalcular el Peso y el Total Bruto                     */
/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::CambiaCantidad()
{
	// Se comprueba si en la cantidad de envío son todo dígitos
	CString strCantidad;
	int iCantidad, iOldCantidad;
	int iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	strCantidad = m_lstArticulos.GetItemText(iFila, 5);

	iOldCantidad = m_lOldCantidad.GetAt(m_lOldCantidad.FindIndex(iFila));
	CString strOldCantidad;
	strOldCantidad.Format("%d", iOldCantidad);

	// Se comprueba si en la cantidad son todo números enteros
	for (int i = 0; i<strCantidad.GetLength(); i++)
	{
		if (strCantidad.GetAt(i) < '0' || strCantidad.GetAt(i) > '9') 
		{
			m_lstArticulos.SetItemTextCB(iFila, 5, strOldCantidad);
			return;
		}
	}

	// Si cantidad de envío no tiene nada se considera 0
	if (strCantidad.IsEmpty())
	{
		iCantidad = 0;
		m_lstArticulos.SetItemText(iFila, 5, iCantidad);
	}
	else
		iCantidad = atoi(strCantidad);

	// Si la cantidad no ha cambiado abandonamos la función
	if (iCantidad == iOldCantidad)
		return;

	// Si es una venta o un alquiler se comprueba la disponibilidad, si no no.
	CString strTipo = m_lstArticulos.GetItemText(iFila, 3);
	if (strTipo == ALQUILER || strTipo == VENTA)
	{
		// Se comprueba la disponibilidad del artículo
		CInventario rsInventario(m_db);

		rsInventario.m_strFilter = "ARTI LIKE '" + m_lstArticulos.GetItemText(iFila, 0) + "' AND ALMACEN LIKE '" + m_rsPedido.m_ALMACEN + "'";
		if (!rsInventario.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// Si el articulo está en la tabla inventario
		if (rsInventario.m_ARTI.IsEmpty())
			rsInventario.m_UNIDISPONIBLE = 0;

		if (rsInventario.m_UNIDISPONIBLE < iCantidad)
		{
			m_lstArticulos.SetItemTextCB(iFila, 5, strOldCantidad);
			CString strMsg;
			strMsg.Format(IDC_NO_DISPONIBLE, m_rsPedido.m_ALMACEN, rsInventario.m_UNIDISPONIBLE);
			AfxMessageBox(strMsg);			
			return;
		}
	}

	// Primero se debe restar el peso que suponía con la cantidad anterior.
	double dPesoAnterior = iOldCantidad * atof(m_lstArticulos.GetItemText(iFila, 2));
	m_dTotalPeso -= dPesoAnterior;

	// Se calcula el nuevo peso total
	m_dTotalPeso += iCantidad * atof(m_lstArticulos.GetItemText(iFila, 2));

	CString strTotalPeso;
	strTotalPeso.Format("%.3f", m_dTotalPeso);
	GetDlgItem(IDC_EDIT_TOTAL_PESO)->SetWindowText(strTotalPeso);

	m_lOldCantidad.SetAt(m_lOldCantidad.FindIndex(iFila), iCantidad);
}


/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::GuardaAlbaran()
{
	HRESULT hErr = S_OK;

	CConta rsConta(m_db);
	CArtiAlbaran rsArtiAlbaran(m_db);
	CAlmacen rsAlmacen(m_db);
	CInventario rsInventario(m_db);

	CString strNextNumAlbaran;

	// Se rellenan los campos del albaran con lo que contienen los editbox
	RellenaAlbaran();

	// Se crea el albarán y luego se insertan cada uno de los artículos que lo componen
	if (!m_db->BeginTrans())
		return;

	m_rsAlbaran.m_NUMPEDIDO = m_rsPedido.m_NUMPEDIDO.Trim();

	// Se coge el siguiente número de albarán
	hErr = rsConta.GetNextNumAlbaran(strNextNumAlbaran);

	if (hErr == S_OK)
	{
		m_rsAlbaran.m_NUMALB = strNextNumAlbaran.Trim();
		hErr = m_rsAlbaran.Insert();
	}

	if (hErr == S_OK)
	{	
		for(int i=0; i<m_lstArticulos.GetItemCount()-1; i++)
		{
			RellenaArtiAlbaran(&rsArtiAlbaran, i);
			hErr = rsArtiAlbaran.Insert();

			// Se actualiza el número de enviados del pedido si tuviera uno asociado
			/*if (hErr == S_OK)
			{
				m_rsArtiVenta.m_ENVIADOS += rsArtiAlbaran.m_CANTI;
				hErr = m_rsArtiVenta.UpdateEnviados();
			}*/

			// Se actualiza el almacén y el inventario, sólo si el artículo es de
			// Venta o de Alquiler
			if (hErr == S_OK && (rsArtiAlbaran.m_ALQUILER == "S" || rsArtiAlbaran.m_ALQUILER == "V"))
			{
				// Se insertan los movimientos del almacén y se actualizan las unidades 
				// disponibles del inventario
				RellenaAlmacen(&rsAlmacen, &rsInventario, &rsArtiAlbaran, i);
				hErr = rsAlmacen.Insert();

				if (hErr == S_OK)
					hErr = rsInventario.UpdateUniDisponible();

				if (hErr == S_OK && rsArtiAlbaran.m_ALQUILER == "V")
					hErr = rsInventario.UpdateUniTotal();

			}		
		}
	}

	// Si todo ha ido bien y el albarán ha sido creado a partir de un pedido, se actualiza
	// el número del nuevo albarán creado en el pedido
	/*if (hErr == S_OK)
	{
		m_rsPedido.m_NUMALB = m_rsAlbaran.m_NUMALB;
		hErr = m_rsPedido.UpdateNumAlbaran();
	}*/

	if (hErr == S_OK)
	{
		m_db->CommitTrans();

		CString strMsg;
		strMsg.Format(IDC_PEDIDOALBARAN, m_rsPedido.m_NUMPEDIDO.Trim(), strNextNumAlbaran.Trim()); 
		AfxMessageBox(strMsg, MB_ICONINFORMATION);
	}
	else
		m_db->Rollback();

	LimpiaVentana();
}

/************************************************************************************************************/
void CDlgPreAlbDespieceEntrega::RellenaAlbaran()
{
	m_rsAlbaran.m_TIPO = ALB_DESPIECE_ENTREGA;
	m_rsAlbaran.m_TIPOPED = m_rsPedido.m_TIPO.Trim();
	m_rsAlbaran.m_ESTADO = NO_FACTURADO;
	m_rsAlbaran.m_EXPORTA = m_rsPedido.m_EXPORTA.Trim();
	m_rsAlbaran.m_CUENTA = m_rsPedido.m_CUENTA.Trim();
	m_rsAlbaran.m_ALMACEN = m_rsPedido.m_ALMACEN.Trim();
	m_rsAlbaran.m_TELEF1 = m_rsPedido.m_TELEF1.Trim();
	m_rsAlbaran.m_TELEF2 = m_rsPedido.m_TELEF2.Trim();
	m_rsAlbaran.m_TARIFA = m_rsPedido.m_TARIFA.Trim();
	m_rsAlbaran.m_DCTOS = m_rsPedido.m_DCTOS;
	m_rsAlbaran.m_DCTOS2 = m_rsPedido.m_DCTOS2;
	m_rsAlbaran.m_DCTOS3 = m_rsPedido.m_DCTOS3;
	m_rsAlbaran.m_PP = m_rsPedido.m_PP;
	m_rsAlbaran.m_IVA = m_rsPedido.m_IVA;
	m_rsAlbaran.m_GRUFAC = m_rsPedido.m_GRUFAC.Trim();
	m_rsAlbaran.m_DIRENV = m_rsPedido.m_DIRENV.Trim();
	m_rsAlbaran.m_REPRE = m_rsPedido.m_REPRE.Trim();
	m_rsAlbaran.m_SUBREP = m_rsPedido.m_SUBREP.Trim();
	m_rsAlbaran.m_COMISION = m_rsPedido.m_COMISION;
	m_rsAlbaran.m_COMISION2 = m_rsPedido.m_COMISION2;
	m_rsAlbaran.m_FECHPED = m_rsPedido.m_FECHPED;
	m_rsAlbaran.m_FECHALB = CTime::GetCurrentTime(); //m_rsPedido.m_FECHPED;
	m_rsAlbaran.m_CENTRO = m_rsPedido.m_CENTRO.Trim();
	m_rsAlbaran.m_SREF	= m_rsPedido.m_SREF.Trim();
	m_rsAlbaran.m_ATENCLI = m_rsPedido.m_ATENCLI.Trim();
	m_rsAlbaran.m_FCOBRO =	m_rsPedido.m_FCOBRO.Trim();
	m_rsAlbaran.m_NCOBROS = m_rsPedido.m_NCOBROS;
	m_rsAlbaran.m_VTO1 = m_rsPedido.m_VTO1;
	m_rsAlbaran.m_DVTO = m_rsPedido.m_DVTO;
	m_rsAlbaran.m_DIA1 = m_rsPedido.m_DIA1;
	m_rsAlbaran.m_DIA2 = m_rsPedido.m_DIA2;
	m_rsAlbaran.m_DIA3 = m_rsPedido.m_DIA3;
	m_rsAlbaran.m_RETENFIS = m_rsPedido.m_RETENFIS;

	m_rsAlbaran.m_OBSALB = m_strObservaciones;
	m_rsAlbaran.m_FECINIALQ = m_timeFechaIni;

}

/************************************************************************************************************/
void CDlgPreAlbDespieceEntrega::RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila)
{
	rsArtiAlbaran->m_NUMALB = m_rsAlbaran.m_NUMALB.Trim();
	rsArtiAlbaran->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsArtiAlbaran->m_DESARTI = m_lstArticulos.GetItemText(iFila, 1);
	rsArtiAlbaran->m_PESO = atof(m_lstArticulos.GetItemText(iFila, 2));

	POSITION pos = m_strTipo.Find(m_lstArticulos.GetItemText(iFila, 3));	
	if (pos != NULL)
	{
		m_strTipo.GetPrev(pos);
		rsArtiAlbaran->m_ALQUILER = m_strTipo.GetPrev(pos);
	}
	else
		rsArtiAlbaran->m_ALQUILER.Empty();

	pos = m_strTipoAlquiler.Find(m_lstArticulos.GetItemText(iFila, 4));	
	if (pos != NULL)
	{
		m_strTipoAlquiler.GetPrev(pos);
		rsArtiAlbaran->m_TIPOALQ = m_strTipoAlquiler.GetPrev(pos);
	}
	else
		rsArtiAlbaran->m_TIPOALQ.Empty();

	rsArtiAlbaran->m_CANTI = atof(m_lstArticulos.GetItemText(iFila, 5));
	rsArtiAlbaran->m_IMPOARTI = 0;
	rsArtiAlbaran->m_DTOARTI = 0;
	rsArtiAlbaran->m_IVARTI = 0;
	rsArtiAlbaran->m_DESARMEMO =  m_lstArticulos.GetItemText(iFila, 1);
}

/************************************************************************************************************/
void CDlgPreAlbDespieceEntrega::RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila)
{
	rsAlmacen->m_NDOC = atof(m_rsAlbaran.m_NUMALB);
	rsAlmacen->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsAlmacen->m_ALMACEN = m_rsPedido.m_ALMACEN.Trim();
	rsAlmacen->m_FECHA = CTime::GetCurrentTime(); //m_rsPedido.m_FECHPED;
	rsAlmacen->m_TIPOMOV = GetTipoMov();
	rsAlmacen->m_OBSER = m_rsAlbaran.m_OBSALB.Trim();
	rsAlmacen->m_CUENTA = m_rsAlbaran.m_CUENTA;

	rsAlmacen->m_CANTI = - atof(m_lstArticulos.GetItemText(iFila, 5));

	// Se comprueba si en la tabla Inventario está ya el articulo y el almacén o no
	rsInventario->m_strFilter = "ARTI LIKE '" + m_lstArticulos.GetItemText(iFila, 0) + "' AND ALMACEN LIKE '" \
		+ rsAlmacen->m_ALMACEN + "'";

	if (!rsInventario->Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Se actualizan las unidades disponibles del artículo y del almacén
	rsInventario->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsInventario->m_ALMACEN = rsAlmacen->m_ALMACEN;
	rsInventario->m_UNIDISPONIBLE = rsInventario->m_UNIDISPONIBLE - atol(m_lstArticulos.GetItemText(iFila, 5));

	// Si es una venta también se debe restar del total de artículos
	if (rsArtiAlbaran->m_ALQUILER == "V")
		rsInventario->m_UNITOTAL = rsInventario->m_UNITOTAL - atol(m_lstArticulos.GetItemText(iFila, 5));

	rsAlmacen->m_CANTIDISPONIBLE = rsInventario->m_UNIDISPONIBLE;
	rsAlmacen->m_CANTITOTAL = rsInventario->m_UNITOTAL;

	rsInventario->Close();
}

/******************************************************************************************/
CString CDlgPreAlbDespieceEntrega::GetTipoMov()
{
	CString strTipoMov;
	CConcepto rsConcepto(m_db);

	strTipoMov.Empty();

	rsConcepto.m_strSort = "CONCEPTO";
	rsConcepto.m_strFilter = "CONCEPTO LIKE 'AL1%'";
	if (!rsConcepto.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return strTipoMov;
	}

	// Si el almacén no se encuentra salimos reseteando el campo
	if (rsConcepto.m_CONCEPTO.IsEmpty())
		strTipoMov.Empty();
	else
		strTipoMov = rsConcepto.m_CONCEPTO.Trim();

	rsConcepto.Close();

	return strTipoMov;
}

/******************************************************************************************/
void CDlgPreAlbDespieceEntrega::BuscaDesAlmacen()
{
	CCuentas rsCuentas(m_db);

	rsCuentas.m_strFilter = "CUENTA LIKE '" + m_strAlmacen + "'";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_strNombreAlmacen = rsCuentas.m_NOMBRE.Trim();		

	rsCuentas.Close();
}



