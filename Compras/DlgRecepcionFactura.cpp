// DlgRecepcionFactura.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Compras.h"
#include "DlgRecepcionFactura.h"
#include ".\dlgrecepcionfactura.h"


// Cuadro de diálogo de CDlgRecepcionFactura

IMPLEMENT_DYNAMIC(CDlgRecepcionFactura, CDialog)
CDlgRecepcionFactura::CDlgRecepcionFactura(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecepcionFactura::IDD, pParent)
	, m_strPedido(_T(""))
	, m_strProveedor(_T(""))
	, m_strDesProveedor(_T(""))
	, m_strFactura(_T(""))
	, m_TimeRecepcion(0)
	, m_TimeFactura(0)
	, m_strIVA(_T(""))
	, m_strDesGen(_T(""))
	, m_strPP(_T(""))
	, m_strTotalBruto(_T(""))
	, m_strTotalNeto(_T(""))
{
}

CDlgRecepcionFactura::~CDlgRecepcionFactura()
{
}

void CDlgRecepcionFactura::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_lstArticulos);
	DDX_Text(pDX, IDC_PEDIDO, m_strPedido);
	DDV_MaxChars(pDX, m_strPedido, 10);
	DDX_Text(pDX, IDC_PROVEEDOR, m_strProveedor);
	DDX_Text(pDX, IDC_DES_PROVEEDOR, m_strDesProveedor);
	DDX_Text(pDX, IDC_FACTURA, m_strFactura);
	DDX_DateTimeCtrl(pDX, IDC_RECEPCION, m_TimeRecepcion);
	DDX_DateTimeCtrl(pDX, IDC_FECHFACTURA, m_TimeFactura);
	DDX_Text(pDX, IDC_IVA, m_strIVA);
	DDX_Text(pDX, IDC_GENERAL, m_strDesGen);
	DDX_Text(pDX, IDC_PP, m_strPP);
	DDX_Text(pDX, IDC_TOTAL, m_strTotalBruto);
	DDX_Text(pDX, IDC_TOTALNETO, m_strTotalNeto);
}


BEGIN_MESSAGE_MAP(CDlgRecepcionFactura, CDialog)
	ON_NOTIFY(NM_SETFOCUS, IDC_RECEPCION, OnNMSetfocusRecepcion)
	ON_BN_CLICKED(IDB_PEDIDO, OnBnClickedPedido)
	ON_EN_KILLFOCUS(IDC_IVA, OnEnKillfocusIva)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_EN_KILLFOCUS(IDC_PEDIDO, OnEnKillfocusPedido)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgRecepcionFactura

BOOL CDlgRecepcionFactura::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgBusquedaPedidos.SetConexion(m_db);

////////////////////SE DA FORMA AL GRID////////////////////
	//Se establece el estilo	
	m_lstArticulos.SetGridLines(TRUE);

	// Añadiendo la lista de imágenes se consigue hacer cada casilla más grande
	CImageList m_ImageList;
	m_ImageList.Create(1, 16, ILC_COLOR,1,1); 
	m_lstArticulos.SetImageList(&m_ImageList); 

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 105);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 180);
	m_lstArticulos.InsertColumn(2,"Pedidos", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(3,"Recibidos", LVCFMT_LEFT, 70);
	m_lstArticulos.InsertColumn(4,"Tarifa", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(5,"Dcto", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(6,"Importe", LVCFMT_LEFT, 55);
	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit
	// Se inicializa el flag
	m_bFocusListCtrl = FALSE;
	// Se inicializan las variables para controlar acciones
	m_bTabFecha = FALSE;
	m_TimeRecepcion=CTime::GetCurrentTime();
	m_TimeFactura=CTime::GetCurrentTime();

	return FALSE;
}
/*******************************************************************************************************/
BOOL CDlgRecepcionFactura::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if  (pMsg->wParam == VK_TAB)
		{
			// Si se ha pulsado el tabulador y venimos de la casilla de la fecha,
			//se debe editar la casilla del listCtrl
			if (m_bFecha)
				m_bTabFecha = TRUE;
		}
	}

	return(CDialog::PreTranslateMessage(pMsg));
}
/*******************************************************************************************************/
void CDlgRecepcionFactura::OnNMSetfocusRecepcion(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_bFecha=TRUE;
	*pResult = 0;
}
/********************************************************************************/
void CDlgRecepcionFactura::SetConexion(CDatabase *db)
{
	m_db = db;
}
/*****************************************************************************************/
LRESULT CDlgRecepcionFactura::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr  = 0;
	// Se obtiene lo que contiene la primera columna
	CString strCod = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 0);

	// En las columnas que deben estar inactivas se pone el textbox a readonly o si el
	// flag de m_bReadOnly está a TRUE
	/*if ((m_lstArticulos.m_ptEditting.y == 0 && !strCod.IsEmpty()) || m_lstArticulos.m_ptEditting.y == 1 
		|| m_lstArticulos.m_ptEditting.y == 2)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	else*/ if (m_lstArticulos.m_ptEditting.y != -1)
			m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	
	// Si se cambia la cantidad de artículos recibida
	/*if (m_lstArticulos.m_ptEditting.y ==3)
		CambiaCantidadRecibido();
	// Si se cambia la tarifa de un artículo
	else if (m_lstArticulos.m_ptEditting.y == 3)
		CambiaTarifa();

	// Si se cambia el descuento de un artículo 
	else if (m_lstArticulos.m_ptEditting.y == 4)
		CambiaDescuento();

	// Se comprueba el IVA
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 5)
		CompruebaIva();*/

	return hErr;
}

/******************************************************************************************************/
void CDlgRecepcionFactura::OnBnClickedPedido()
{
	INT_PTR status;

	m_dlgBusquedaPedidos.SetTipo(CDialogBusqueda::COMPRAS);
	status = m_dlgBusquedaPedidos.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana();
		m_strPedido = m_dlgBusquedaPedidos.GetCodigo();
		m_strProveedor = m_dlgBusquedaPedidos.GetDescripcion();
		BuscaCliente();
		BuscaPedido();
	}
}
/******************************************************************************************/
BOOL CDlgRecepcionFactura::BuscaPedido()
{
	BOOL bExists = FALSE;

	if (m_rsCompras.IsOpen())
		m_rsCompras.Close();

	m_rsCompras.m_strFilter = "NPEDCOM = '" + m_strPedido + "'";// AND CUENTA = '" + m_strProveedor + "'";
	if (!m_rsCompras.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se indica
	if (!m_rsCompras.m_NPEDCOM.IsEmpty())
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		m_strProveedor = m_rsCompras.m_CUENTA;
		m_strIVA.Format("%2.f",m_rsCompras.m_IVA);
		m_strDesGen.Format("%2.f",m_rsCompras.m_DCTOS);
		m_strPP.Format("%2.f",m_rsCompras.m_PP);
		BuscaArticulos();

		bExists = TRUE;
	}

	m_rsCompras.Close();
	
	return bExists;
}
/********************************************************************************/
BOOL CDlgRecepcionFactura::BuscaCliente()
{
	BOOL bExists = FALSE;
	CProve rsProveedores(m_db);

	rsProveedores.m_strFilter = "CUENTA LIKE '" + m_strProveedor + "'";
	if (!rsProveedores.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el cliente existe se rellenan sus campos 
	if (!rsProveedores.m_CUENTA.IsEmpty())
	{
		m_strDesProveedor = rsProveedores.m_NOMBRE.Trim();
	}
	else
	{
		m_strProveedor = "";
		AfxMessageBox(IDS_PROVEEDOR_NO_EXISTE);
	}
	rsProveedores.Close();

	//UpdateData(FALSE);

	return bExists;
}
/********************************************************************************/
void CDlgRecepcionFactura::LimpiaVentana()
{
	m_strPedido.Empty();
	m_strProveedor.Empty();
	m_strDesProveedor.Empty();
	m_strFactura.Empty();
	m_TimeRecepcion=CTime::GetCurrentTime();
	m_TimeFactura=NULL;
	m_lstArticulos.DeleteAllItems();
}
/********************************************************************************/
void CDlgRecepcionFactura::BuscaArticulos()
{
	CArtiCompra m_rsArtiCompra(m_db);

	m_rsArtiCompra.m_strFilter = "NPEDCOM LIKE '" + m_strPedido + "'";
	if (!m_rsArtiCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	m_lstArticulos.DeleteAllItems();
	m_dTotalBruto=0;
	m_dTotalNeto=0;
//	m_lEnvioSoloLectura.RemoveAll();

	// Si el pedido tiene artículos se rellena el listCtrl
	int iIndice = 0;
	m_rsArtiCompra.MoveFirst();
	while (!m_rsArtiCompra.IsEOF())
	{
		//Código del Articulo(No modificable)
		m_lstArticulos.InsertItem(iIndice, _T(""));
		m_lstArticulos.SetItemText(iIndice, 0, m_rsArtiCompra.m_ARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);
		//Descripción del Articulo(No modificable)
		m_lstArticulos.SetItemText(iIndice, 1, m_rsArtiCompra.m_DESARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);
		//Cantidad Pedida del Articulo(No modificable)
		m_lstArticulos.SetItemText(iIndice, 2, m_rsArtiCompra.m_CANTI);
		m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);
		//Cantidad Recibida del Articulo
		CString strPedidos;
		strPedidos.Format("%g", m_rsArtiCompra.m_RECIBIDOS);
		m_lstArticulos.SetItemText(iIndice, 3, strPedidos);
		m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);
		//Tarifa del Articulo
		CString strTarifa;
		strTarifa.Format("%g", m_rsArtiCompra.m_IMPOARTI);
		m_lstArticulos.SetItemText(iIndice, 4, strTarifa);
		m_lstArticulos.SetItemBkColor(iIndice, 4, RGB(183, 183, 183), TRUE);
		//Descuento del Articulo
		CString strDescuento;
		strDescuento.Format("%g", m_rsArtiCompra.m_DTOARTI);
		m_lstArticulos.SetItemText(iIndice, 5, strDescuento);
		m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
		//Importe total del Articulo
		CString strImporte;
		strImporte.Format("%g", m_rsArtiCompra.m_RECIBIDOS * m_rsArtiCompra.m_IMPOARTI * (1 - (m_rsArtiCompra.m_DTOARTI / 100)));
		m_lstArticulos.SetItemText(iIndice, 6, strImporte);
		m_lstArticulos.SetItemBkColor(iIndice, 6, RGB(183, 183, 183), TRUE);
		//////////////////
		//TOTAL BRUTO: 
		m_dTotalBruto += atof(strImporte);
		//TOTAL NETO:
		m_dTotalNeto = m_dTotalBruto;
		if(m_strIVA.Trim()!="0")
            m_dTotalNeto += m_dTotalBruto-(m_dTotalBruto * (1-(atof(m_strIVA)/100)));
		if (m_strPP.Trim()!="0")
			m_dTotalNeto -= m_dTotalBruto-(m_dTotalBruto * (1-(atof(m_strPP)/100)));
		if (m_strDesGen.Trim()!="0")
			m_dTotalNeto-= m_dTotalBruto-(m_dTotalBruto * (1-(atof(m_strDesGen)/100))); 
		iIndice ++;
		m_rsArtiCompra.MoveNext();
	}

	m_rsArtiCompra.Close();
	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTAL)->SetWindowText(m_strTotalBruto);
	m_strTotalNeto.Empty();
	m_strTotalNeto.Format("%.2f", m_dTotalNeto);
	GetDlgItem(IDC_TOTALNETO)->SetWindowText(m_strTotalNeto);
	UpdateData(FALSE);
}
/********************************************************************************/
void CDlgRecepcionFactura::OnEnKillfocusIva()
{
	CString Aux;
	Aux=m_strIVA;
	GetDlgItem(IDC_IVA)->GetWindowText(m_strIVA);
	if (CompruebaNumero(m_strIVA))
	{
		m_dTotalNeto = m_dTotalBruto;
		if(m_strIVA.Trim()!="0")
            m_dTotalNeto += m_dTotalBruto-(m_dTotalBruto * (1-(atof(m_strIVA)/100)));
		if (m_strPP.Trim()!="0")
			m_dTotalNeto -= m_dTotalBruto-(m_dTotalBruto * (1-(atof(m_strPP)/100)));
		if (m_strDesGen.Trim()!="0")
			m_dTotalNeto-= m_dTotalBruto-(m_dTotalBruto * (1-(atof(m_strDesGen)/100))); 
		m_strTotalNeto.Empty();
		m_strTotalNeto.Format("%.2f", m_dTotalNeto);
		GetDlgItem(IDC_TOTALNETO)->SetWindowText(m_strTotalNeto);
	}
	else
	{
		m_strIVA =Aux;
	}
	GetDlgItem(IDC_IVA)->SetWindowText(m_strIVA);
}
/********************************************************************************/
BOOL CDlgRecepcionFactura::CompruebaNumero(CString strNumero)
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
/********************************************************************************/
void CDlgRecepcionFactura::OnEnKillfocusPedido()
{
	CString Aux;
	Aux = m_strPedido;
	GetDlgItem(IDC_PEDIDO)->GetWindowText(m_strPedido);
	if (Aux == m_strPedido || m_strPedido.IsEmpty())
		return;
	if (BuscaPedido())
		BuscaCliente();
	else
	{
		m_strPedido=Aux;
		GetDlgItem(IDC_PEDIDO)->GetWindowText(m_strPedido);
		GetDlgItem(IDC_PEDIDO)->SetFocus();
	}
}
