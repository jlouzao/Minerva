// DlgPreAlbEntrega.cpp: archivo de implementación
//
/******************************************************************************************/

#include "stdafx.h"
#include "DlgPreAlbEntrega.h"
#include ".\dlgprealbentrega.h"
#include "BD.h"
#include "Utilidades.h"
#include "DlgDatosAlbaran.h"
#include "Etiquetas.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgPreAlbEntrega
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgPreAlbEntrega, CDialog)
CDlgPreAlbEntrega::CDlgPreAlbEntrega(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAlbEntrega::IDD, pParent)
	, m_strCuenta(_T(""))
	, m_strNombre(_T(""))
	, m_strPedido(_T(""))
	, m_dTotalPeso(0)
	, m_strAlbaranes(_T(""))
	, m_timeFechaIni(CTime::GetCurrentTime())
	, m_strObservaciones(_T(""))
	, m_strNombreAlmacen(_T(""))
{
}

/******************************************************************************************/
CDlgPreAlbEntrega::~CDlgPreAlbEntrega()
{
}

/******************************************************************************************/
void CDlgPreAlbEntrega::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ARTICULOS, m_lstArticulos);
	DDX_Text(pDX, IDC_EDIT_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_EDIT_NOMBRE, m_strNombre);
	DDX_Text(pDX, IDC_PEDIDO, m_strPedido);
	DDV_MaxChars(pDX, m_strPedido, 10);
	DDX_Text(pDX, IDC_EDIT_TOTAL_PESO, m_dTotalPeso);
	DDX_Text(pDX, IDC_ALBARANES, m_strAlbaranes);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_INI_ALQUILER, m_timeFechaIni);
	DDX_Text(pDX, IDC_OBSER_ALBARAN, m_strObservaciones);
	DDV_MaxChars(pDX, m_strObservaciones, 100);
	DDX_Text(pDX, IDC_ALMACEN, m_strAlmacen);
	DDX_Text(pDX, IDC_NOMBRE_ALMACEN, m_strNombreAlmacen);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgPreAlbEntrega, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA, OnEnKillfocusEditCuenta)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_EN_KILLFOCUS(IDC_PEDIDO, OnEnKillfocusNumpedido)
	ON_BN_CLICKED(IDC_BTN_PEDIDO, OnBnClickedBtnPedido)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ARTICULOS, OnNMSetfocusListArticulos)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgPreAlbEntrega


/***********************************************************************************************/
BOOL CDlgPreAlbEntrega::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece el estilo	
	m_lstArticulos.SetGridLines(TRUE);

	// Añadiendo la lista de imágenes se consigue hacer cada casilla más grande
	CImageList m_ImageList;
	m_ImageList.Create(1, 16, ILC_COLOR,1,1); 
	m_lstArticulos.SetImageList(&m_ImageList); 

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 100);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 175);
	m_lstArticulos.InsertColumn(2,"Peso", LVCFMT_LEFT, 50);
	m_lstArticulos.InsertColumn(3,"Pedido", LVCFMT_LEFT, 50);
	m_lstArticulos.InsertColumn(4,"Enviado", LVCFMT_LEFT, 50);
	m_lstArticulos.InsertColumn(5,"Envío", LVCFMT_LEFT, 60);
	m_lstArticulos.InsertColumn(6,"Pendiente", LVCFMT_LEFT, 60);

	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit

	m_lOldEnvio.RemoveAll();
	m_lTipo.RemoveAll();
	m_lEnvioSoloLectura.RemoveAll();

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaPedidosCli.SetConexion(m_db);

	GetDlgItem(IDC_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBSER_ALBARAN)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_INI_ALQUILER)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;
}

/******************************************************************************************/
void CDlgPreAlbEntrega::OnEnKillfocusEditCuenta()
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
void CDlgPreAlbEntrega::OnBnClickedBtnCuenta()
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
void CDlgPreAlbEntrega::OnEnKillfocusNumpedido()
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
void CDlgPreAlbEntrega::OnBnClickedBtnPedido()
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
void CDlgPreAlbEntrega::OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	*pResult = 0;
}

/******************************************************************************************/
LRESULT CDlgPreAlbEntrega::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr  = 0;

	// Si es la casilla de Envío y no es de sólo lectura se pone editable
	if (m_lstArticulos.m_ptEditting.y == 5 && 
		!(m_lEnvioSoloLectura.GetAt(m_lEnvioSoloLectura.FindIndex(m_lstArticulos.m_ptEditting.x))))
		m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);
	else if (m_lstArticulos.m_ptEditting.y != -1)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);

	// Si se han cambiadon los enviados se actualizan los pendientes
	if (m_lstArticulos.m_ptEditting.y == 5 && !(m_lEnvioSoloLectura.GetAt(m_lEnvioSoloLectura.FindIndex(m_lstArticulos.m_ptEditting.x))))
		CambiaCantidadEnvio();

	return hErr;
}

/******************************************************************************************/
void CDlgPreAlbEntrega::OnBnClickedOk()
{
	// Si alguna casilla del CListCtrl se ha quedado editable se quita
	if (m_lstArticulos.m_ptEditting.x != -1)
		m_lstArticulos.EndEdit();

	UpdateData();

	// Se comprueba si al menos en uno de los artículos se envía algo
	BOOL bHayCambios = FALSE;
	for (int i=0; i<m_lstArticulos.GetItemCount(); i++)
	{
		CString strEnvio = m_lstArticulos.GetItemText(i, 5);
		if (strEnvio != "0" && strEnvio != "-")
		{
			bHayCambios = TRUE;
			break;
		}

	}

	if (bHayCambios)
		GuardaAlbaran();

	//OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgPreAlbEntrega::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsPedido.m_pDatabase = db;
	m_rsAlbaran.m_pDatabase = db;
	m_rsArtiVenta.m_pDatabase = db;
}

/******************************************************************************************/
BOOL CDlgPreAlbEntrega::BuscaCliente()
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
BOOL CDlgPreAlbEntrega::BuscaPedido()
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
		BuscaArticulosPedido();

		// Se busca los posibles albaranes que ya puediera tener asociado
		BuscaAlbaranes();

		m_strAlmacen = m_rsPedido.m_ALMACEN.Trim();
		BuscaDesAlmacen();

		GetDlgItem(IDC_ALMACEN)->SetWindowText(m_strAlmacen);
		GetDlgItem(IDC_NOMBRE_ALMACEN)->SetWindowText(m_strNombreAlmacen);

		// Si no son todos de lectura se habilita el botón de Aceptar
		if ((m_lEnvioSoloLectura.Find(FALSE)) != NULL)
			GetDlgItem(IDOK)->EnableWindow(TRUE);

		bExists = TRUE;
	}

	m_rsPedido.Close();

	return bExists;
}

/******************************************************************************************/
void CDlgPreAlbEntrega::LimpiaVentana()
{
	m_strCuenta.Empty();
	m_strNombre.Empty();
	m_strPedido.Empty();
	m_strAlmacen.Empty();
	m_strNombreAlmacen.Empty();
	m_strAlbaranes.Empty();
	m_dTotalPeso = 0;
	m_timeFechaIni = CTime::GetCurrentTime();
	m_strObservaciones.Empty();

	m_lstArticulos.DeleteAllItems();

	GetDlgItem(IDC_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBSER_ALBARAN)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_INI_ALQUILER)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_dlgBusquedaPedidosCli.InicializarListas();
	m_lEnvioSoloLectura.RemoveAll();
	m_lOldEnvio.RemoveAll();
	m_lTipo.RemoveAll();

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgPreAlbEntrega::BuscaArticulosPedido()
{
	if (m_rsArtiVenta.IsOpen())
		m_rsArtiVenta.Close();

	m_rsArtiVenta.m_strFilter = "NUMPEDIDO LIKE '" + m_strPedido + "'";
	if (!m_rsArtiVenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_lstArticulos.DeleteAllItems();
	m_lEnvioSoloLectura.RemoveAll();

	// Si el pedido tiene artículos se rellena el listCtrl
	int iIndice = 0;
	while (!m_rsArtiVenta.IsEOF())
	{
		if (m_rsArtiVenta.m_ALQUILER == "S" || m_rsArtiVenta.m_ALQUILER == "V")
		{
			m_lstArticulos.InsertItem(iIndice, _T(""));
			m_lstArticulos.SetItemText(iIndice, 0, m_rsArtiVenta.m_ARTI.Trim());
			m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);

			m_lstArticulos.SetItemText(iIndice, 1, m_rsArtiVenta.m_DESARTI.Trim());
			m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);

			CString strPeso;
			strPeso.Format("%g", m_rsArtiVenta.m_PESO);
			m_lstArticulos.SetItemText(iIndice, 2, strPeso);
			m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);

			// Se escribe la cantidad pedida
			CString strPedidos;
			strPedidos.Format("%g", m_rsArtiVenta.m_CANTI);
			m_lstArticulos.SetItemText(iIndice, 3, strPedidos);
			m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);

			// Se escribe la cantidad enviada
			CString strEnviados;
			strEnviados.Format("%g", m_rsArtiVenta.m_ENVIADOS);
			m_lstArticulos.SetItemText(iIndice, 4, strEnviados);
			m_lstArticulos.SetItemBkColor(iIndice, 4, RGB(183, 183, 183), TRUE);

			double dPendientes = m_rsArtiVenta.m_CANTI - m_rsArtiVenta.m_ENVIADOS;

			// Si ya se han enviado todos se pone de sólo lectura
			if (dPendientes == 0)
			{
				m_lEnvioSoloLectura.AddTail(TRUE);
				m_lstArticulos.SetItemText(iIndice, 5, "-");
				m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
			}
			else
			{
				m_lstArticulos.SetItemText(iIndice, 5, "0");
				m_lEnvioSoloLectura.AddTail(FALSE);
			}

			m_lOldEnvio.AddTail((double)0);
			m_lTipo.AddTail(m_rsArtiVenta.m_ALQUILER);

			// Se escribe la cantidad pendiente
			CString strPendientes;
			strPendientes.Format("%g", dPendientes);
			m_lstArticulos.SetItemText(iIndice, 6, strPendientes);
			m_lstArticulos.SetItemBkColor(iIndice, 6, RGB(183, 183, 183), TRUE);

			iIndice ++;
		}

		//m_iNumArti++;
		m_rsArtiVenta.MoveNext();
	}

	//m_rsArtiVenta.Close();
}

/******************************************************************************************/
void CDlgPreAlbEntrega::BuscaAlbaranes()
{
	CAlbaran rsAlbaran(m_db);

	rsAlbaran.m_strFilter = "NUMPEDIDO LIKE '" + m_strPedido + "' AND TIPO = '" + ALB_ENTREGA + "'";
	if (!rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_strAlbaranes.Empty();
	BOOL bPrimeraVez = TRUE;
	while (!rsAlbaran.IsEOF())
	{
		if (bPrimeraVez)
			bPrimeraVez = FALSE;
		else
			m_strAlbaranes += ", ";

		m_strAlbaranes += rsAlbaran.m_NUMALB.Trim();

		rsAlbaran.MoveNext();
	}

	GetDlgItem(IDC_ALBARANES)->SetWindowText(m_strAlbaranes);

	rsAlbaran.Close();
}

/******************************************************************************************/
void CDlgPreAlbEntrega::CambiaCantidadEnvio()
{
	// Se comprueba si en la cantidad de envío son todo dígitos
	CString strEnvio;
	double dEnvio, dOldEnvio;
	int iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	/*int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	m_lstArticulos.GetEditControl()->GetLine(0, strEnvio.GetBuffer(len), len);
	strEnvio.ReleaseBuffer(len);*/
	strEnvio = m_lstArticulos.GetItemText(iFila, 5);

	dOldEnvio = m_lOldEnvio.GetAt(m_lOldEnvio.FindIndex(iFila));
	CString strOldEnvio;
	strOldEnvio.Format("%g", dOldEnvio);

	// Se comprueba si en la cantidad de envío son todo números enteros
	for (int i = 0; i<strEnvio.GetLength(); i++)
	{
		if (strEnvio.GetAt(i) < '0' || strEnvio.GetAt(i) > '9') 
		{
			m_lstArticulos.SetItemTextCB(iFila, 5, strOldEnvio);
			return;
		}
	}

	// Si cantidad de envío no tiene nada se considera 0
	if (strEnvio.IsEmpty())
	{
		dEnvio = 0;
		m_lstArticulos.SetItemText(iFila, 5, dEnvio);
	}
	else
		dEnvio = atoi(strEnvio);

	// Si la cantidad no ha cambiado abandonamos la función
	if (dEnvio == dOldEnvio)
		return;

	// Se actualiza la cantidad de artículos pendientes
	CString strPedidos = m_lstArticulos.GetItemText(iFila, 3);
	CString strEnviados = m_lstArticulos.GetItemText(iFila, 4);
	double dPendientes = atof(strPedidos) - atof(strEnviados) - dEnvio;

	if (dPendientes < 0 )
	{
		m_lstArticulos.SetItemTextCB(iFila, 5, strOldEnvio);
		AfxMessageBox(IDC_NO_ENVIO);
		return;
	}

	// Si es una venta o un alquiler se comprueba la disponibilidad, si no no.
	CString strTipo = m_lTipo.GetAt(m_lTipo.FindIndex(iFila));
	if (strTipo == "S" || strTipo == "V")
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

		if (rsInventario.m_UNIDISPONIBLE < dEnvio)
		{
			m_lstArticulos.SetItemTextCB(iFila, 5, strOldEnvio);
			CString strMsg;
			strMsg.Format(IDC_NO_DISPONIBLE, m_rsPedido.m_ALMACEN, rsInventario.m_UNIDISPONIBLE);
			AfxMessageBox(strMsg);
			return;

		}
	}

	// Se actualiza pendientes y peso
	CString strPendientes;
	strPendientes.Format("%g", dPendientes);
	m_lstArticulos.SetItemText(iFila, 6, strPendientes);

	// Primero se debe restar el peso que suponía con la cantidad anterior.
	double dPesoAnterior = dOldEnvio * atof(m_lstArticulos.GetItemText(iFila, 2));
	m_dTotalPeso -= dPesoAnterior;

	// Se calcula el nuevo peso total
	m_dTotalPeso += dEnvio * atof(m_lstArticulos.GetItemText(iFila, 2));

	CString strTotalPeso;
	strTotalPeso.Format("%.3f", m_dTotalPeso);
	GetDlgItem(IDC_EDIT_TOTAL_PESO)->SetWindowText(strTotalPeso);

	m_lOldEnvio.SetAt(m_lOldEnvio.FindIndex(iFila), dEnvio);
}

/******************************************************************************************/
void CDlgPreAlbEntrega::GuardaAlbaran()
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
		int iIndex = 0;
		m_rsArtiVenta.MoveFirst();
		while (!m_rsArtiVenta.IsEOF())
		{
			if (m_rsArtiVenta.m_ALQUILER == "S" || m_rsArtiVenta.m_ALQUILER == "V")
			{
				// Si los artículos pedidos es igual a enviados no se debe insertar en el albarán
				if (atof(m_lstArticulos.GetItemText(iIndex, 5)) == 0
					|| m_rsArtiVenta.m_CANTI == m_rsArtiVenta.m_ENVIADOS)
				{
					iIndex++;
					m_rsArtiVenta.MoveNext();
					continue;
				}

				//if (hErr == S_OK)
				//{
				RellenaArtiAlbaran(&rsArtiAlbaran, iIndex);
				hErr = rsArtiAlbaran.Insert();
				//}

				// Se actualiza el número de enviados del pedido si tuviera uno asociado
				if (hErr == S_OK)
				{
					m_rsArtiVenta.m_ENVIADOS += rsArtiAlbaran.m_CANTI;
					hErr = m_rsArtiVenta.UpdateEnviados();
				}

				// Se actualiza el almacén y el inventario, sólo si el artículo es de
				// Venta o de Alquiler
				//if (hErr == S_OK && (rsArtiAlbaran.m_ALQUILER == "S" || rsArtiAlbaran.m_ALQUILER == "V"))
				//{
				// Se insertan los movimientos del almacén y se actualizan las unidades 
				// disponibles del inventario

				// Si el tipo de pedido es de maquinaria se actualiza el almacén, si no no
				if (m_rsPedido.m_TIPO.Trim() == MAQUINARIA)
				{
					RellenaAlmacen(&rsAlmacen, &rsInventario, &rsArtiAlbaran, iIndex);
					hErr = rsAlmacen.Insert();

					if (hErr == S_OK)
						hErr = rsInventario.UpdateUniDisponible();

					if (hErr == S_OK && rsArtiAlbaran.m_ALQUILER == "V")
						hErr = rsInventario.UpdateUniTotal();
				}

				//}
				iIndex++;
			}
			
			m_rsArtiVenta.MoveNext();
		}

		m_rsArtiVenta.Close();
	}

	// Si todo ha ido bien y el albarán ha sido creado a partir de un pedido, se actualiza
	// el número del nuevo albarán creado en el pedido
	if (hErr == S_OK)
	{
		m_rsPedido.m_NUMALB = m_rsAlbaran.m_NUMALB;
		hErr = m_rsPedido.UpdateNumAlbaran();
	}

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
void CDlgPreAlbEntrega::RellenaAlbaran()
{
	m_rsAlbaran.m_TIPO = ALB_ENTREGA;
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
void CDlgPreAlbEntrega::RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila)
{
	rsArtiAlbaran->m_NUMALB = m_rsAlbaran.m_NUMALB.Trim();
	rsArtiAlbaran->m_ARTI = m_rsArtiVenta.m_ARTI.Trim();
	rsArtiAlbaran->m_DESARTI = m_rsArtiVenta.m_DESARTI.Trim();
	rsArtiAlbaran->m_PESO = m_rsArtiVenta.m_PESO;
	rsArtiAlbaran->m_ALQUILER = m_rsArtiVenta.m_ALQUILER;
	rsArtiAlbaran->m_TIPOALQ = m_rsArtiVenta.m_TIPOALQ;
	rsArtiAlbaran->m_CANTI = atof(m_lstArticulos.GetItemText(iFila, 5));
	rsArtiAlbaran->m_IMPOARTI = m_rsArtiVenta.m_IMPOARTI;
	rsArtiAlbaran->m_DTOARTI = m_rsArtiVenta.m_DTOARTI;
	rsArtiAlbaran->m_IVARTI = m_rsArtiVenta.m_IVARTI;
	rsArtiAlbaran->m_DESARMEMO = m_rsArtiVenta.m_DESARMEMO;
}

/************************************************************************************************************/
void CDlgPreAlbEntrega::RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila)
{
	rsAlmacen->m_NDOC = atof(m_rsAlbaran.m_NUMALB);
	rsAlmacen->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsAlmacen->m_ALMACEN = m_rsPedido.m_ALMACEN.Trim();
	rsAlmacen->m_FECHA = CTime::GetCurrentTime();  //m_rsPedido.m_FECHPED;
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
CString CDlgPreAlbEntrega::GetTipoMov()
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
void CDlgPreAlbEntrega::BuscaDesAlmacen()
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




