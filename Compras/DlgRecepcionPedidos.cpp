// DlgRecepcionPedidos.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Compras.h"
#include "DlgRecepcionPedidos.h"
#include ".\dlgrecepcionpedidos.h"


// Cuadro de diálogo de CDlgRecepcionPedidos

IMPLEMENT_DYNAMIC(CDlgRecepcionPedidos, CDialog)
CDlgRecepcionPedidos::CDlgRecepcionPedidos(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecepcionPedidos::IDD, pParent)
	, m_strCuenta(_T(""))
	, m_strPedido(_T(""))
	, m_strObservaciones(_T(""))
	, m_strNombre(_T(""))
	, m_strAlbaranes(_T(""))
{
}

CDlgRecepcionPedidos::~CDlgRecepcionPedidos()
{
}

void CDlgRecepcionPedidos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ARTICULOS, m_lstArticulos);
	DDX_Text(pDX, IDC_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_PEDIDO, m_strPedido);
	DDV_MaxChars(pDX, m_strPedido, 9);
	DDX_Text(pDX, IDC_OBSERVACIONES, m_strObservaciones);
	DDX_Text(pDX, IDC_NOMBRE, m_strNombre);
	DDX_Text(pDX, IDC_ALBARANES, m_strAlbaranes);
}


BEGIN_MESSAGE_MAP(CDlgRecepcionPedidos, CDialog)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_BN_CLICKED(IDC_BTN_PEDIDO, OnBnClickedBtnPedido)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_CUENTA, OnEnKillfocusCuenta)
	ON_EN_KILLFOCUS(IDC_PEDIDO, OnEnKillfocusPedido)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ARTICULOS, OnNMSetfocusListArticulos)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ARTICULOS, OnLvnItemchangedListArticulos)
END_MESSAGE_MAP()

/********************************************************************************/
BOOL CDlgRecepcionPedidos::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece el estilo	
	m_lstArticulos.SetGridLines(TRUE);

	// Añadiendo la lista de imágenes se consigue hacer cada casilla más grande
	/*CImageList m_ImageList;
	m_ImageList.Create(1, 16, ILC_COLOR,1,1); */
	CImageList m_ImageList;
	m_ImageList.Create(1, 16, ILC_COLOR,1,1); 
	m_lstArticulos.SetImageList(&m_ImageList); 

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 75);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 182);
	m_lstArticulos.InsertColumn(2,"Pedido", LVCFMT_LEFT, 65);
	m_lstArticulos.InsertColumn(3,"Recibido", LVCFMT_LEFT, 65);
	m_lstArticulos.InsertColumn(4,"Ingreso", LVCFMT_LEFT, 65);
	m_lstArticulos.InsertColumn(5,"Pendiente", LVCFMT_LEFT, 65);

	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit

	m_lOldEnvio.RemoveAll();

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaProveedores.SetConexion(m_db);
	m_dlgBusquedaPedidos.SetConexion(m_db);

	GetDlgItem(IDC_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;
}
/********************************************************************************/
void CDlgRecepcionPedidos::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsCompras.m_pDatabase = db;
//	m_rsAlbaranC.m_pDatabase = db;
	m_rsArtiCompra.m_pDatabase = db;
}
/********************************************************************************/
/*********************************  GRID  ***************************************/
/********************************************************************************/
LRESULT CDlgRecepcionPedidos::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr  = 0;

	// Si es la casilla de Envío y no es de sólo lectura se pone editable
	if (m_lstArticulos.m_ptEditting.y == 4 )
		m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);
	else if (m_lstArticulos.m_ptEditting.y != -1)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);

	// Si se han cambiadon los enviados se actualizan los pendientes
	if (m_lstArticulos.m_ptEditting.y == 4 )
	{	
		int iFila = m_lstArticulos.m_ptEditting.x;
		CambiaCantidadRecibido();
		/*if ( m_lstArticulos.GetItemText(iFila, 5) == "-")
		{
			m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
			m_lstArticulos.SetItemBkColor(iFila, 4, RGB(183, 183, 183), TRUE);
		}*/
	}
	return hErr;
}
/******************************************************************************************/
void CDlgRecepcionPedidos::CambiaCantidadRecibido()
{
	// Se comprueba si en la cantidad de envío son todo dígitos
	CString strRecibido;
	double dRecibido, dOldRecibido;
	int iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	m_lstArticulos.GetEditControl()->GetLine(0, strRecibido.GetBuffer(len), len);
	strRecibido.ReleaseBuffer(len);
	//strRecibido = m_lstArticulos.GetItemText(iFila, 5);

	dOldRecibido = m_lOldEnvio.GetAt(m_lOldEnvio.FindIndex(iFila));
	CString strOldEnvio;
	strOldEnvio.Format("%g", dOldRecibido);

	// Se comprueba si en la cantidad de envío son todo números enteros
	for (int i = 0; i<strRecibido.GetLength(); i++)
	{
		if (strRecibido.GetAt(i) < '0' || strRecibido.GetAt(i) > '9') 
		{
			m_lstArticulos.SetItemTextCB(iFila, 4, strOldEnvio);
			return;
		}
	}

	// Si cantidad recibida no tiene nada se considera cero
	if (strRecibido.IsEmpty())
	{
		dRecibido = 0;
		m_lstArticulos.SetItemText(iFila, 4, dRecibido);
	}
	else
		dRecibido = atoi(strRecibido);

	// Si la cantidad no ha cambiado abandonamos la función
	if (dRecibido == dOldRecibido)
		return;
	
	// Se actualiza la cantidad de artículos pendientes
	CString strPedidos = m_lstArticulos.GetItemText(iFila, 2);
	CString strRecibidos = m_lstArticulos.GetItemText(iFila, 3);
	CString strRecibidosHoy = m_lstArticulos.GetItemText(iFila, 4);
	// Se actualiza pendientes 
	double dPendientes = atof(strPedidos)-(atof(strRecibidos)+atof(strRecibidosHoy));
	/*if (dPendientes<0)
		AfxMessageBox(IDS_MAS_RECIBIDO);*/
	CString strPendientes;
	strPendientes.Format("%g",dPendientes);
	
	if (strPendientes == "0" || dPendientes < 0)
		strPendientes = "-";		
	m_lstArticulos.SetItemText(iFila, 5, strPendientes);
	m_lOldEnvio.SetAt(m_lOldEnvio.FindIndex(iFila), dRecibido);
}
/******************************************************************************************/
void CDlgRecepcionPedidos::OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}
/******************************************************************************************/
void CDlgRecepcionPedidos::BuscaArticulosPedido()
{
	if (m_rsArtiCompra.IsOpen())
		m_rsArtiCompra.Close();

	m_rsArtiCompra.m_strFilter = "NPEDCOM LIKE '" + m_strPedido + "'";
	if (!m_rsArtiCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	m_lstArticulos.DeleteAllItems();
//	m_lEnvioSoloLectura.RemoveAll();

	// Si el pedido tiene artículos se rellena el listCtrl
	int iIndice = 0;
	while (!m_rsArtiCompra.IsEOF())
	{
		m_lstArticulos.InsertItem(iIndice, _T(""));
		m_lstArticulos.SetItemText(iIndice, 0, m_rsArtiCompra.m_ARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);

		m_lstArticulos.SetItemText(iIndice, 1, m_rsArtiCompra.m_DESARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);

		// Se escribe la cantidad pedida
		CString strPedidos;
		strPedidos.Format("%g", m_rsArtiCompra.m_CANTI);
		m_lstArticulos.SetItemText(iIndice, 2, strPedidos);
		m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);

		// Se escribe la cantidad Recibida hasta el momento		
		CString strRecibidos;
		strRecibidos.Format("%g", m_rsArtiCompra.m_RECIBIDOS);
		m_lstArticulos.SetItemText(iIndice, 3, strRecibidos);
		m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);
		
		//Se escribe la cantidad recibida hoy(se inicializa a cero)
		m_lstArticulos.SetItemText(iIndice, 4, "0");

		double dPendientes = atof(strPedidos) - atof(strRecibidos);

		if (dPendientes == 0 || dPendientes < 0)
		{	//si no hay pendientes se pone el guion y se bloquea los recibidos
			m_lstArticulos.SetItemText(iIndice, 5, "-");		
			m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
			//m_lstArticulos.SetItemBkColor(iIndice, 4, RGB(183, 183, 183), TRUE);
			bSoloLectura = TRUE;//si al finalizar de cargar todos los articulos es TRUE, no se activa IDOK
		}
		else
		{	// Se escribe la cantidad pendiente
			CString strPendientes;
			strPendientes.Format("%g", dPendientes);
			m_lstArticulos.SetItemText(iIndice, 5, strPendientes);
			m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
			bSoloLectura = FALSE;
		}

		m_lOldEnvio.AddTail((double)0);

		iIndice ++;
		m_rsArtiCompra.MoveNext();
	}
	m_rsArtiCompra.Close();
}
/********************************************************************************/
/******************************** FUNCIONES *************************************/
/********************************************************************************/
void CDlgRecepcionPedidos::OnBnClickedBtnCuenta()
{
	INT_PTR status;

	m_dlgBusquedaProveedores.SetTipo(CDialogBusqueda::PROVEEDORES);
		status = m_dlgBusquedaProveedores.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana();

		m_strCuenta = m_dlgBusquedaProveedores.GetCodigo();
		m_strNombre = m_dlgBusquedaProveedores.GetDescripcion();

		GetDlgItem(IDC_PEDIDO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(TRUE);

		UpdateData(FALSE);
	}
}
/********************************************************************************/
void CDlgRecepcionPedidos::OnBnClickedBtnPedido()
{
	INT_PTR status;
	CString cadena;

	GetDlgItem(IDC_CUENTA)->GetWindowText(m_strCuenta);
	/*if (m_strCuenta.IsEmpty())
		cadena= "NPEDCOM LIKE '" + m_strPedido + "'";
	else
	{
		
		cadena =
	}*/
	m_dlgBusquedaPedidos.SetCliente(m_strCuenta);
	m_dlgBusquedaPedidos.SetTipo(CDialogBusqueda::PEDIDOSPROVE);
	status = m_dlgBusquedaPedidos.DoModal();
	if (status == IDOK)
	{
		m_strObservaciones.Empty();
		m_strPedido = m_dlgBusquedaPedidos.GetCodigo();
		BuscaPedido();
		GetDlgItem(IDC_PEDIDO)->SetWindowText(m_strPedido);
		GetDlgItem(IDOK)->EnableWindow(TRUE);

		CAlbCompra rsAlbaranes(m_db);
		rsAlbaranes.m_strFilter = "NPEDCOM LIKE '" + m_strPedido + "' AND CUENTA LIKE'" + m_strCuenta + "'";
		if (!rsAlbaranes.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDS_ERROR_BD);
			return;
		}
		BOOL bPrimeraVez = TRUE;
		while (!rsAlbaranes.IsEOF())
		{
			if (bPrimeraVez)
				bPrimeraVez = FALSE;
			else
				m_strAlbaranes += " / ";

			m_strAlbaranes += rsAlbaranes.m_NALBCOM.Trim();
		
			rsAlbaranes.MoveNext();
		}
		//m_strAlbaranes.Format("%s", m_strAlbaranes.GetLength()-1);
		GetDlgItem(IDC_ALBARANES)->SetWindowText(m_strAlbaranes);
	}
}
/********************************************************************************/
void CDlgRecepcionPedidos::OnBnClickedOk()
{
	// Si alguna casilla del CListCtrl se ha quedado editable se quita
	if (m_lstArticulos.m_ptEditting.x != -1)
		m_lstArticulos.EndEdit();

	GuardaAlbaran();

	//OnOK();
}
/********************************************************************************/
void CDlgRecepcionPedidos::OnEnKillfocusCuenta()
{
	CString strCuentaOld = m_strCuenta;

	GetDlgItem(IDC_CUENTA)->GetWindowText(m_strCuenta);

	if (m_strCuenta == strCuentaOld)
		return;

	if (!m_strCuenta.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCliente())
		{
//			AfxMessageBox(IDS_CLIENTE_NO_EXISTE);
			m_strCuenta = strCuentaOld;
			GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
			return;
		}
	}
	else
		LimpiaVentana();
}
/********************************************************************************/
void CDlgRecepcionPedidos::OnEnKillfocusPedido()
{
	CString strPedidoOld = m_strPedido;

	GetDlgItem(IDC_PEDIDO)->GetWindowText(m_strPedido);
	m_strPedido = m_strPedido.Trim();

	if (!m_strPedido.IsEmpty())
	{
		// Si el pedido no existe se deja el anterior y se da un mensaje de error
		if (!BuscaPedido())
		{
			AfxMessageBox(IDS_COMPRA_NO_EXISTE);
			m_strPedido = strPedidoOld;
			GetDlgItem(IDC_PEDIDO)->SetFocus();
		}
	}
}
/********************************************************************************/
BOOL CDlgRecepcionPedidos::BuscaCliente()
{
	BOOL bExists = FALSE;
	CProve rsProveedores(m_db);

	rsProveedores.m_strFilter = "CUENTA LIKE '" + m_strCuenta + "'";
	if (!rsProveedores.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el cliente existe se rellenan sus campos 
	if (!rsProveedores.m_CUENTA.IsEmpty())
	{
		LimpiaVentana();

		m_strCuenta = rsProveedores.m_CUENTA.Trim();
		m_strNombre = rsProveedores.m_NOMBRE.Trim();

		GetDlgItem(IDC_PEDIDO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(TRUE);

		bExists = TRUE;

	}

	rsProveedores.Close();

	UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
BOOL CDlgRecepcionPedidos::BuscaPedido()
{
	BOOL bExists = FALSE;

	if (m_rsCompras.IsOpen())
		m_rsCompras.Close();

	m_rsCompras.m_strFilter = "NPEDCOM = '" + m_strPedido + "' AND CUENTA = '" + m_strCuenta + "'";
	if (!m_rsCompras.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se indica
	if (!m_rsCompras.m_NPEDCOM.IsEmpty())
	{
		BuscaArticulosPedido();
		// Si  se habilita el botón de Aceptar
		if (bSoloLectura == FALSE)
			GetDlgItem(IDOK)->EnableWindow(TRUE);

		bExists = TRUE;
	}

	m_rsCompras.Close();
	
	return bExists;
}

/******************************************************************************************/
void CDlgRecepcionPedidos::LimpiaVentana()
{
	m_strCuenta.Empty();
	m_strNombre.Empty();
	m_strPedido.Empty();
	m_strAlbaranes.Empty();
	m_strObservaciones.Empty();

	m_lstArticulos.DeleteAllItems();

	GetDlgItem(IDC_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_dlgBusquedaPedidos.InicializarListas();
//	m_lEnvioSoloLectura.RemoveAll();
	m_lOldEnvio.RemoveAll();

	UpdateData(FALSE);
}
/************************************************************************************************************/
void CDlgRecepcionPedidos::RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario,int iFila, CString strNAlbCom)
{
	rsAlmacen->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsAlmacen->m_CANTI = atof(m_lstArticulos.GetItemText(iFila, 4));
	rsAlmacen->m_CANTITOTAL = rsInventario->m_UNITOTAL;
	rsAlmacen->m_CANTIDISPONIBLE = rsInventario->m_UNIDISPONIBLE;
	rsAlmacen->m_NDOC= atof(strNAlbCom.Trim());
	rsAlmacen->m_FECHA = CTime::GetCurrentTime();
	rsAlmacen->m_TIPOMOV = "AL1";//concepto Albaran
	rsAlmacen->m_CUENTA = m_strCuenta.Trim();
	rsAlmacen->m_OBSER = m_strObservaciones.Trim();
}
/************************************************************************************************************/
void CDlgRecepcionPedidos::RellenaArtiAlbaran(CArtiAlbCompra *rsArtiAlbCompra, int iFila, CString strNAlbCom)
{
	rsArtiAlbCompra->m_NALBCOM = strNAlbCom.Trim();
	rsArtiAlbCompra->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsArtiAlbCompra->m_DESARTI = m_rsArtiCompra.m_DESARTI.Trim();
	rsArtiAlbCompra->m_CANTI = atof(m_lstArticulos.GetItemText(iFila, 4));
	rsArtiAlbCompra->m_IMPOARTI = m_rsArtiCompra.m_IMPOARTI;
	rsArtiAlbCompra->m_DTOARTI = m_rsArtiCompra.m_DTOARTI;
	rsArtiAlbCompra->m_IVARTI = m_rsArtiCompra.m_IVARTI;
	rsArtiAlbCompra->m_DESARMEMO = m_rsArtiCompra.m_DESARMEMO.Trim();
}
/************************************************************************************************************/
void CDlgRecepcionPedidos::RellenaAlbaran(CAlbCompra *rsAlbaran)
{
	CCompras rsCompras(m_db);
	rsCompras.m_strFilter = "NPEDCOM = '" + m_strPedido + "'";
	if (!rsCompras.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	rsAlbaran->m_EXPORTA = rsCompras.m_EXPORTA;
	rsAlbaran->m_CUENTA = rsCompras.m_CUENTA;
	rsAlbaran->m_ALMACEN = rsCompras.m_ALMACEN;
	rsAlbaran->m_FCOBRO = rsCompras.m_FCOBRO;
	rsAlbaran->m_NCOBROS = rsCompras.m_NCOBROS;
	rsAlbaran->m_VTO1 = rsCompras.m_VTO1;
	rsAlbaran->m_DIA1 = rsCompras.m_DIA1;
	rsAlbaran->m_DIA2 = rsCompras.m_DIA2;
	rsAlbaran->m_DIA3 = rsCompras.m_DIA3;
	rsAlbaran->m_DCTO2 = rsCompras.m_DCTO2;
	rsAlbaran->m_DCTO3 = rsCompras.m_DCTO3;
	rsAlbaran->m_DCTOS = rsCompras.m_DCTOS;
	rsAlbaran->m_PP = rsCompras.m_PP;
	rsAlbaran->m_FECHALB = CTime::GetCurrentTime();
	rsAlbaran->m_CENTRO = rsCompras.m_CENTRO;
	rsAlbaran->m_SREF = rsCompras.m_SREF;
	rsAlbaran->m_OBSALB = m_strObservaciones.Trim();
    
	rsCompras.Close();
}
/******************************************************************************************/
void CDlgRecepcionPedidos::GuardaAlbaran()
{	
	UpdateData(TRUE);

	CConta rsConta(m_db);
	CAlbCompra rsAlbaran(m_db);
	CArtiAlbCompra rsArtiAlbCompra(m_db);
	CAlmacen rsAlmacen(m_db);
	CInventario rsInventario(m_db);
	HRESULT hErr;
		
	if (!m_db->BeginTrans())
		return;
	//Se obtiene el siguiente número de albaran y se guarda
	CString strNextNumAlbaran;
	hErr = rsConta.GetNextNumAlbCompra(strNextNumAlbaran);
	//Se obtiene el número del pedido de compra
	CString strNPedCom;
	strNPedCom = m_rsCompras.m_NPEDCOM.Trim();

	if (hErr == S_OK)
	{//Se rellena e inserta el Albaran
		RellenaAlbaran(&rsAlbaran);
		rsAlbaran.m_NPEDCOM = strNPedCom.Trim();
		rsAlbaran.m_NALBCOM = strNextNumAlbaran.Trim();
		hErr = rsAlbaran.Insert();
	}
	if (hErr == S_OK)
	{//Se inserta cada uno de los articulos recibidos(que aun esten pendientes)
		int iIndex = 0;
		if (m_rsArtiCompra.IsOpen())
			m_rsArtiCompra.Close();
		m_rsArtiCompra.m_strFilter = "NPEDCOM LIKE '" + strNPedCom + "'";
		if (!m_rsArtiCompra.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDS_ERROR_BD);
			return;
		}
		while (!m_rsArtiCompra.IsEOF())
		{// Si el artículo ya no tiene pendientes o no se ha recibido nada, no se debe insertar en el albarán
			if (atoi(m_lstArticulos.GetItemText(iIndex, 4)) == 0 
				|| m_rsArtiCompra.m_CANTI == m_rsArtiCompra.m_RECIBIDOS)
			{
				iIndex++;
				m_rsArtiCompra.MoveNext();
				continue;
			}
			RellenaArtiAlbaran(&rsArtiAlbCompra, iIndex, strNextNumAlbaran);
			hErr = rsArtiAlbCompra.Insert();			
			if (hErr == S_OK)
			{// Se actualiza el número de recibidos del pedido 
				m_rsArtiCompra.m_RECIBIDOS += atof(m_lstArticulos.GetItemText(iIndex, 4));
				hErr = m_rsArtiCompra.UpdateRecibidos();
			}
			if (hErr == S_OK)
			{// Se insertan los movimientos del almacén y se actualizan las unidades disponibles del inventario
				rsInventario.m_strFilter = "ARTI LIKE '" + m_rsArtiCompra.m_ARTI.Trim() + "' AND " \
					"ALMACEN LIKE '" + rsAlbaran.m_ALMACEN.Trim() + "'";
				if (!rsInventario.Open(CRecordset::dynaset))
				{
					AfxMessageBox(IDS_ERROR_BD);
					return;
				}	
				rsInventario.m_UNIDISPONIBLE += atoi(m_lstArticulos.GetItemText(iIndex, 4));
				rsInventario.m_UNITOTAL += atoi(m_lstArticulos.GetItemText(iIndex, 4));
				if (rsInventario.m_ARTI.IsEmpty())
				{
					rsInventario.m_ARTI = m_rsArtiCompra.m_ARTI.Trim();
					rsInventario.m_ALMACEN = rsAlbaran.m_ALMACEN.Trim();
					hErr = rsInventario.Insert();
				}
				else
				{
					hErr = rsInventario.UpdateUniDisponible();
					hErr = rsInventario.UpdateUniTotal();
				}
				//////////////////////////////////////////////////////
				rsAlmacen.m_ALMACEN = rsAlbaran.m_ALMACEN.Trim();		
				RellenaAlmacen(&rsAlmacen, &rsInventario, iIndex, strNextNumAlbaran);
				hErr = rsAlmacen.Insert();
				//////////////////////////////////////////////////////
				rsInventario.Close();
				rsInventario.m_ARTI.Empty();
				rsInventario.m_ALMACEN.Empty();
				rsInventario.m_UNIDISPONIBLE=0;
				rsInventario.m_UNITOTAL=0;
			}
			iIndex++;
			m_rsArtiCompra.MoveNext();	
		}
		m_rsArtiCompra.Close();
	}
	if (hErr == S_OK)
	{
		m_db->CommitTrans();

		CString strMsg;
		strMsg.Format(IDS_ALBARAN, rsAlbaran.m_NALBCOM.Trim()); 
		AfxMessageBox(strMsg, MB_ICONINFORMATION);
	}
	else
		m_db->Rollback();
	
	LimpiaVentana();
}
/******************************************************************************************/
void CDlgRecepcionPedidos::OnLvnItemchangedListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Agregue aquí su código de controlador de notificación de control
	*pResult = 0;
}