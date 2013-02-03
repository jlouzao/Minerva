// DialogBusqueda.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DialogBusqueda.h"
#include ".\dialogbusqueda.h"
#include "BD.h"
#include "GestionDlg.h"

/******************************************************************************************/
// Cuadro de diálogo de CDialogBusqueda
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDialogBusqueda, CDialog)
CDialogBusqueda::CDialogBusqueda(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogBusqueda::IDD, pParent)
{
	m_bGestionar = TRUE;
}

/******************************************************************************************/
CDialogBusqueda::~CDialogBusqueda()
{
}

/******************************************************************************************/
void CDialogBusqueda::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BUSQUEDA, m_lstBusqueda);
}


/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDialogBusqueda, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BUSQUEDA, OnNMDblclkListBusqueda)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BUSQUEDA, OnLvnColumnclickListBusqueda)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDAGREGAR, OnBnClickedAgregar)
	ON_BN_CLICKED(IDMODIFICAR, OnBnClickedModificar)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDialogBusqueda
/******************************************************************************************/

BOOL CDialogBusqueda::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece el estilo
	m_lstBusqueda.SetExtendedStyle(m_lstBusqueda.GetExtendedStyle()|LVS_EX_FULLROWSELECT );

	// Se introducen los nombres de las columnas. Si el tipo es OFERTAS, PEDIDOS, ALBARANES se
	// cambia el nombre
	if (m_iTipo == OFERTAS || m_iTipo == PEDIDOS || m_iTipo == ALBARANES || m_iTipo == PEDIDOSCLI || m_iTipo == FACTURAS || m_iTipo == ALBARANESPEDIDOCLI || m_iTipo == COBROS)
	{
		m_lstBusqueda.InsertColumn(0,"Número");			
		m_lstBusqueda.InsertColumn(1,"Cliente");
	}
	else if (m_iTipo == COMPRAS || m_iTipo == ALBCOMPRA || m_iTipo == PEDIDOSPROVE)
	{
		m_lstBusqueda.InsertColumn(0,"Número");			
		m_lstBusqueda.InsertColumn(1,"Proveedor");
	}
	else
	{
		m_lstBusqueda.InsertColumn(0,"Código");			
		m_lstBusqueda.InsertColumn(1,"Descripción");
	}

	// Se establece su ancho
	m_lstBusqueda.SetColumnWidth(0,100);
	m_lstBusqueda.SetColumnWidth(1,228);

	// Se rellena el grid. Si el array está vacío se abandona la ejecución
	if (m_lstBusquedaPorCod.IsEmpty())
		CrearListaCodigo();

	POSITION pos = m_lstBusquedaPorCod.GetHeadPosition();
	int iIndice = 0;
	while(pos)
	{
		m_lstBusqueda.InsertItem(iIndice, _T(""));
		m_lstBusqueda.SetItemText(iIndice, 0, m_lstBusquedaPorCod.GetNext(pos));
		m_lstBusqueda.SetItemText(iIndice, 1, m_lstBusquedaPorCod.GetNext(pos));
		iIndice++;
	}

	// Ponemos el foco sobre la lista
	m_lstBusqueda.SetFocus();
	m_lstBusqueda.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	// Se inicializa el orden según el código
	m_bCodigo = TRUE;

	// Se inicializa el código seleccionado y la descripcion
	m_strCodigo.Empty();
	m_strDescripcion.Empty();

	// Los botones de Nuevo y Modificar, no deben aparecen en las búsquedas de: CUENTAS, PROVEEDORES,
	// CLIENTES, ALMACEN, ARTICULOS, FAMILIAS, SUBFAMILIAS, OFERTAS, PEDIDOS, ALBARANES, PEDIDOSCLI, COMPRAS
	if (m_iTipo == ARTICULOS || m_iTipo == FAMILIAS || m_iTipo == SUBFAMILIAS || m_iTipo == CUENTAS ||
		m_iTipo == ALMACEN || m_iTipo == PROVEEDORES || m_iTipo == CLIENTES || m_iTipo == OFERTAS || 
		m_iTipo == PEDIDOS || m_iTipo == ALBARANES || m_iTipo == PEDIDOSCLI || m_iTipo == COMPRAS || 
		m_iTipo == ALBCOMPRA || m_iTipo == PEDIDOSPROVE || m_iTipo == FACTURAS || 
		m_iTipo == ALBARANESPEDIDOCLI || m_iTipo == COBROS || m_iTipo == ESTADOS || !m_bGestionar)
	{
		GetDlgItem(IDAGREGAR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDMODIFICAR)->ShowWindow(SW_HIDE);
	}
	if(m_lstBusqueda.GetItemCount()==0)
	{
		GetDlgItem(IDMODIFICAR)->EnableWindow(FALSE);
	}
	return FALSE;
}

/******************************************************************************************/
void CDialogBusqueda::OnNMDblclkListBusqueda(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedOk();
	*pResult = 0;
}

/******************************************************************************************/
void CDialogBusqueda::OnBnClickedOk()
{
	int iItem, iSubItemCod, iSubItemDes;

	// Recoge el indice del campo seleccionado
	POSITION pos = m_lstBusqueda.GetFirstSelectedItemPosition();	
	iItem = m_lstBusqueda.GetNextSelectedItem(pos);              

	if (m_bCodigo)
	{
		iSubItemCod = 0;
		iSubItemDes = 1;
	}
	else
	{
		iSubItemCod = 1;
		iSubItemDes = 0;
	}

	m_strCodigo = m_lstBusqueda.GetItemText (iItem, iSubItemCod);
	m_strDescripcion = m_lstBusqueda.GetItemText (iItem, iSubItemDes);

	OnOK();
}

/******************************************************************************************/
void CDialogBusqueda::OnLvnColumnclickListBusqueda(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// Se comprueba si se debe cambiar el orden. Sólo se cambia si se pulsa la 2ª columna
	if (pNMLV->iSubItem == 0)
		return;

	// Se eliminan los items y las columnas
	m_lstBusqueda.DeleteAllItems();

	CHeaderCtrl* pHeaderCtrl = m_lstBusqueda.GetHeaderCtrl();
	while (pHeaderCtrl->GetItemCount() > 0)
		m_lstBusqueda.DeleteColumn(0);

	// Si está ordenado por código se debe cambiar a DESCRIPCION
	if (m_bCodigo) 
	{
		// Se introducen los nombres de las columnas. Si el tipo es OFERTAS, PEDIDOS, ALBARANES se
		// cambia el nombre
		if (m_iTipo == OFERTAS || m_iTipo == PEDIDOS || m_iTipo == ALBARANES || m_iTipo == PEDIDOSCLI || m_iTipo == FACTURAS  || m_iTipo == ALBARANESPEDIDOCLI || m_iTipo == COBROS)
		{
			m_lstBusqueda.InsertColumn(0,"Cliente");			
			m_lstBusqueda.InsertColumn(1,"Número");
		}
		else if (m_iTipo == COMPRAS || m_iTipo == ALBCOMPRA || m_iTipo == PEDIDOSPROVE)
		{
			m_lstBusqueda.InsertColumn(0,"Proveedor");			
			m_lstBusqueda.InsertColumn(1,"Número");
		}
		else
		{
			m_lstBusqueda.InsertColumn(0,"Descripción");			
			m_lstBusqueda.InsertColumn(1,"Código");
		}

		// Se establece su ancho
		m_lstBusqueda.SetColumnWidth(0,228);
		m_lstBusqueda.SetColumnWidth(1,100);

		if (m_lstBusquedaPorDes.IsEmpty())
			CrearListaDescripcion();

		if (!m_lstBusquedaPorDes.IsEmpty())
		{
			POSITION pos = m_lstBusquedaPorDes.GetHeadPosition();		
			int iIndice = 0;
			while(pos)
			{
				m_lstBusqueda.InsertItem(iIndice, _T(""));
				m_lstBusqueda.SetItemText(iIndice, 0, m_lstBusquedaPorDes.GetNext(pos));
				m_lstBusqueda.SetItemText(iIndice, 1, m_lstBusquedaPorDes.GetNext(pos));
				iIndice++;
			}
		}

		m_bCodigo = FALSE;
	}
	else
	{
		// Se introducen los nombres de las columnas. Si el tipo es OFERTAS, PEDIDOS, ALBARANES se
		// cambia el nombre
		if (m_iTipo == OFERTAS || m_iTipo == PEDIDOS || m_iTipo == ALBARANES || m_iTipo == PEDIDOSCLI || m_iTipo == FACTURAS || m_iTipo == ALBARANESPEDIDOCLI || m_iTipo == COBROS)
		{
			m_lstBusqueda.InsertColumn(0,"Número");			
			m_lstBusqueda.InsertColumn(1,"Cliente");
		}
		else if (m_iTipo == COMPRAS || m_iTipo == ALBCOMPRA || m_iTipo == PEDIDOSPROVE)
		{
			m_lstBusqueda.InsertColumn(0,"Número");			
			m_lstBusqueda.InsertColumn(1,"Proveedor");
		}
		else
		{
			m_lstBusqueda.InsertColumn(0,"Código");			
			m_lstBusqueda.InsertColumn(1,"Descripción");
		}

		// Se establece su ancho
		m_lstBusqueda.SetColumnWidth(0,100);
		m_lstBusqueda.SetColumnWidth(1,228);

		POSITION pos = m_lstBusquedaPorCod.GetHeadPosition();		
		int iIndice = 0;
		while(pos)
		{
			m_lstBusqueda.InsertItem(iIndice, _T(""));
			m_lstBusqueda.SetItemText(iIndice, 0, m_lstBusquedaPorCod.GetNext(pos));
			m_lstBusqueda.SetItemText(iIndice, 1, m_lstBusquedaPorCod.GetNext(pos));
			iIndice++;
		}

		m_bCodigo = TRUE;
	}

	// Se repintan los items
	m_lstBusqueda.RedrawItems(0, m_lstBusqueda.GetItemCount());

	// Ponemos el foco sobre la lista
	m_lstBusqueda.SetFocus();
	m_lstBusqueda.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	*pResult = 0;
}

/******************************************************************************************/
void CDialogBusqueda::ReCargaLista()
{
	// Se inicializan las listas
	InicializarListas();

	// Se eliminan los items y las columnas
	m_lstBusqueda.DeleteAllItems();

	// Si está ordenado por código se debe cambiar a DESCRIPCION
	if (m_bCodigo) 
	{
		CrearListaCodigo();

		if (!m_lstBusquedaPorCod.IsEmpty())
		{
			POSITION pos = m_lstBusquedaPorCod.GetHeadPosition();		
			int iIndice = 0;
			while(pos)
			{
				m_lstBusqueda.InsertItem(iIndice, _T(""));
				m_lstBusqueda.SetItemText(iIndice, 0, m_lstBusquedaPorCod.GetNext(pos));
				m_lstBusqueda.SetItemText(iIndice, 1, m_lstBusquedaPorCod.GetNext(pos));
				iIndice++;
			}
		}

		m_bCodigo = TRUE;
	}
	else
	{
		CrearListaDescripcion();

		if (!m_lstBusquedaPorDes.IsEmpty())
		{
			POSITION pos = m_lstBusquedaPorDes.GetHeadPosition();		
			int iIndice = 0;
			while(pos)
			{
				m_lstBusqueda.InsertItem(iIndice, _T(""));
				m_lstBusqueda.SetItemText(iIndice, 0, m_lstBusquedaPorDes.GetNext(pos));
				m_lstBusqueda.SetItemText(iIndice, 1, m_lstBusquedaPorDes.GetNext(pos));
				iIndice++;
			}
		}

		m_bCodigo = FALSE;
	}

	// Se repintan los items
	m_lstBusqueda.RedrawItems(0, m_lstBusqueda.GetItemCount());

	// Ponemos el foco sobre la lista
	m_lstBusqueda.SetFocus();
	m_lstBusqueda.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

//	*pResult = 0;
}

/******************************************************************************************/
void CDialogBusqueda::OnBnClickedAgregar()
{
	switch(m_iTipo)
	{
		case CONCEPTOS:   NuevaConcepto();
						  break;
		case IDIOMA:      NuevaIdioma();
						  break;
		case PAIS:        NuevaPais();
						  break;
		case DIVISAS:     NuevaDivisa();
						  break;
		case FPAGCOB:     NuevaFPagCob();
						  break;
		case DIRENV:      NuevaDirEnv();
						  break;
		case ZONA:        NuevaZona();
						  break;
		case RUTRAN:      NuevaRuTran();
						  break;
		case SEGURO:      NuevaSeguro();
						  break;
		case CENTROS:     NuevaCentros();
						  break;
	}

}
/******************************************************************************************/
void CDialogBusqueda::OnBnClickedModificar()
{
	// COMPROBAR QUE SE HA SELECCIONADO UNA!!!!
	int iItem, iSubItemCod, iSubItemDes;
	POSITION pos = m_lstBusqueda.GetFirstSelectedItemPosition();	
	iItem = m_lstBusqueda.GetNextSelectedItem(pos);              
	if (iItem!=NULL)
	{
		if (m_bCodigo)
		{
			iSubItemCod = 0;
			iSubItemDes = 1;
		}
		else
		{
			iSubItemCod = 1;
			iSubItemDes = 0;
		}
		strCodigo=m_lstBusqueda.GetItemText(iItem, iSubItemCod);
		m_strDescripcion = m_lstBusqueda.GetItemText (iItem, iSubItemDes);
		
	}
	else
	{
		if (m_bCodigo)
		{
			strCodigo = m_lstBusquedaPorCod.GetAt(m_lstBusquedaPorCod.FindIndex(0));
			m_strDescripcion = m_lstBusquedaPorCod.GetAt(m_lstBusquedaPorCod.FindIndex(1));
		}
		else
		{
			strCodigo = m_lstBusquedaPorDes.GetAt(m_lstBusquedaPorDes.FindIndex(1));
			m_strDescripcion = m_lstBusquedaPorDes.GetAt(m_lstBusquedaPorDes.FindIndex(0));
		}
		//return;
	}
	m_strCodigo=strCodigo;
	switch(m_iTipo)
	{
		case CONCEPTOS:   ModificarConcepto();
						  break;
		case IDIOMA:      ModificarIdioma();
						  break;
		case PAIS:        ModificarPais();
						  break;
		case DIVISAS:     ModificarDivisa();
						  break;
		case FPAGCOB:     ModificarFPagCob();
						  break;
		case DIRENV:      ModificarDirEnv();
						  break;
		case ZONA:        ModificarZona();
						  break;
		case RUTRAN:      ModificarRuTran();
						  break;
		case SEGURO:      ModificarSeguro();
						  break;
		case CENTROS:     ModificarCentros();
						  break;
	}

}
/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDialogBusqueda::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
 void CDialogBusqueda::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}

/******************************************************************************************/
void CDialogBusqueda::SetGestionar(BOOL bGestionar)
{
	m_bGestionar = bGestionar;
}

/******************************************************************************************/
void CDialogBusqueda::SetCodFamilia(CString CodFam)
{
	strCodFamilia = CodFam;
}

/******************************************************************************************/
void CDialogBusqueda::SetCliente(CString strCliente)
{
	m_strCliente = strCliente.Trim();
}

/******************************************************************************************/
void CDialogBusqueda::SetPedido(CString strPedido)
{
	m_strPedido = strPedido.Trim();
}

/******************************************************************************************/
void CDialogBusqueda::SetFactura(CString strFactura)
{
	m_strFactura = strFactura;
}

/******************************************************************************************/
void CDialogBusqueda::InicializarListas()
{
	m_lstBusquedaPorCod.RemoveAll();
	m_lstBusquedaPorDes.RemoveAll();
}

/******************************************************************************************/
CString CDialogBusqueda::GetCodigo()
{
	return m_strCodigo;
}
/******************************************************************************************/
CString CDialogBusqueda::GetDescripcion()
{
	return m_strDescripcion;
}
/******************************************************************************************/
void CDialogBusqueda::CrearListaCodigo()
{
	switch(m_iTipo)
	{
		case ARTICULOS:   CreaListaCodsArticulos();
						  break;
		case FAMILIAS:    CrearListaCodsFamilias();
						  break;
		case SUBFAMILIAS: CrearListaCodsSubFamilias();
						  break;
		case CUENTAS:     CrearListaCodsCuentas();
						  break;
		case ALMACEN:     CrearListaCodsAlmacen();
						  break;
		case PROVEEDORES: CrearListaCodsProveedores();
						  break;
		case CLIENTES:    CrearListaCodsClientes();
						  break;
		case CONCEPTOS:   CrearListaCodsConceptos();
						  break;
		case IDIOMA:      CrearListaCodsIdioma();
						  break;
		case PAIS:        CrearListaCodsPais();
						  break;
		case DIVISAS:     CrearListaCodsDivisas();
						  break;
		case FPAGCOB:     CrearListaCodsFPagCob();
						  break;
		case DIRENV:      CrearListaCodsDirEnv();
						  break;
		case ZONA:        CrearListaCodsZona();
						  break;
		case RUTRAN:      CrearListaCodsRuTran();
						  break;
		case SEGURO:      CrearListaCodsSeguro();
						  break;
		case CENTROS:     CrearListaCodsCentros();
						  break;
		case OFERTAS:     CrearListaCodsOfertas();
						  break;
		case PEDIDOS:     CrearListaCodsPedidos();
						  break;
		case ALBARANES:   CrearListaCodsAlbaranes();
						  break;
		case PEDIDOSCLI:  CrearListaCodsPedidosCli();
						  break;
		case COMPRAS:     CrearListaCodsCompras();
						  break;
		case ALBCOMPRA:   CrearListaCodsAlbCompra();
						  break;
		case PEDIDOSPROVE:CrearListaCodsPedidosProve();
						  break;
		case FACTURAS:    CrearListaCodsFacturas();
						  break;
		case ALBARANESPEDIDOCLI:CrearListaCodsAlbaranesPedidoCli();
							break;
		case COBROS:     CrearListaCodsCobros();
					     break;
		case ESTADOS:    CrearListaCodsEstados();
					     break;
	}
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDescripcion()
{
	switch(m_iTipo)
	{
		case ARTICULOS:   CreaListaDesArticulos();
						  break;
		case FAMILIAS:    CrearListaDesFamilias();
						  break;
		case SUBFAMILIAS: CrearListaDesSubFamilias();
						  break;
		case CUENTAS:     CrearListaDesCuentas();
						  break;
		case ALMACEN:     CrearListaDesAlmacen();
						  break;
		case PROVEEDORES: CrearListaDesProveedores();
						  break;
		case CLIENTES:    CrearListaDesClientes();
						  break;
		case CONCEPTOS:   CrearListaDesConceptos();
						  break;
		case IDIOMA:      CrearListaDesIdioma();
						  break;
		case PAIS:        CrearListaDesPais();
						  break;
		case DIVISAS:     CrearListaDesDivisas();
						  break;
		case FPAGCOB:     CrearListaDesFPagCob();
						  break;
		case DIRENV:      CrearListaDesDirEnv();
						  break;
		case ZONA:        CrearListaDesZona();
						  break;
		case RUTRAN:      CrearListaDesRuTran();
						  break;
		case SEGURO:      CrearListaDesSeguro();
						  break;
		case CENTROS:     CrearListaDesCentros();
						  break;
		case OFERTAS:     CrearListaDesOfertas();
						  break;
		case PEDIDOS:     CrearListaDesPedidos();
						  break;
		case ALBARANES:   CrearListaDesAlbaranes();
						  break;
		case PEDIDOSCLI:  CrearListaDesPedidosCli();
						  break;
		case COMPRAS:     CrearListaDesCompras();
						  break;
		case ALBCOMPRA:   CrearListaDesAlbCompra();
						  break;
		case PEDIDOSPROVE:CrearListaDesPedidosProve();
						  break;
		case FACTURAS:    CrearListaDesFacturas();
						  break;
		case ALBARANESPEDIDOCLI:CrearListaDesAlbaranesPedidoCli();
						  break;
		case COBROS:      CrearListaDesCobros();
					      break;
		case ESTADOS:    CrearListaDesEstados();
					     break;
	}
}

/******************************************************************************************/
void CDialogBusqueda::CreaListaCodsArticulos()
{
	CArticulo rsArticulo(m_db);

	//rsArticulo.m_strSort = "ARTI";
	//if (!rsArticulo.Open(CRecordset::dynaset))
	if (!rsArticulo.Open(CRecordset::dynaset, "SELECT ARTI, DESARTI FROM ARTICULO ORDER BY ARTI"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsArticulo.IsEOF())
	{	
		m_lstBusquedaPorCod.AddTail(rsArticulo.m_ARTI.Trim());
		m_lstBusquedaPorCod.AddTail(rsArticulo.m_DESARTI.Trim());
		rsArticulo.MoveNext();
	}

	rsArticulo.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CreaListaDesArticulos()
{
	CArticulo rsArticulo(m_db);

	//rsArticulo.m_strSort = "DESARTI";
	//if (!rsArticulo.Open(CRecordset::dynaset))
	if (!rsArticulo.Open(CRecordset::dynaset, "SELECT ARTI, DESARTI FROM ARTICULO ORDER BY DESARTI"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsArticulo.IsEOF())
	{
		m_lstBusquedaPorDes.AddTail(rsArticulo.m_DESARTI.Trim());
		m_lstBusquedaPorDes.AddTail(rsArticulo.m_ARTI.Trim());
		rsArticulo.MoveNext();
	}
	
	rsArticulo.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsFamilias()
{
	CFamilias rsFamilia(m_db);

	rsFamilia.m_strSort = "CFAMILIA";
	if (!rsFamilia.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsFamilia.IsEOF())
	{
		m_lstBusquedaPorCod.AddTail(rsFamilia.m_CFAMILIA);
		m_lstBusquedaPorCod.AddTail(rsFamilia.m_DFAMILIA);
		rsFamilia.MoveNext();
	}

	rsFamilia.Close();
}
/******************************************************************************************/
void CDialogBusqueda::CrearListaDesFamilias()
{
	CFamilias rsFamilia(m_db);

	rsFamilia.m_strSort = "DFAMILIA";
	if (!rsFamilia.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsFamilia.IsEOF())
	{
		m_lstBusquedaPorDes.AddTail(rsFamilia.m_DFAMILIA);
		m_lstBusquedaPorDes.AddTail(rsFamilia.m_CFAMILIA);
		rsFamilia.MoveNext();
	}

	rsFamilia.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsSubFamilias()
{
	CSubfami rsSubFami(m_db);

	rsSubFami.m_strSort = "CSUBFAM";
	rsSubFami.m_strFilter = "CFAMILIA LIKE '" + strCodFamilia + "'";
	if (!rsSubFami.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsSubFami.IsEOF())
	{
		m_lstBusquedaPorCod.AddTail(rsSubFami.m_CSUBFAM);
		m_lstBusquedaPorCod.AddTail(rsSubFami.m_DSUBFAM);
		rsSubFami.MoveNext();
	}

	rsSubFami.Close();
}
/******************************************************************************************/
void CDialogBusqueda::CrearListaDesSubFamilias()
{
	CSubfami rsSubFami(m_db);

	rsSubFami.m_strSort = "DSUBFAM";
	rsSubFami.m_strFilter = "CFAMILIA LIKE '" + strCodFamilia + "'";
	if (!rsSubFami.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsSubFami.IsEOF())
	{
		m_lstBusquedaPorDes.AddTail(rsSubFami.m_DSUBFAM);
		m_lstBusquedaPorDes.AddTail(rsSubFami.m_CSUBFAM);
		rsSubFami.MoveNext();
	}

	rsSubFami.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsCuentas()
{
	CCuentas rsCuenta(m_db);

	rsCuenta.m_strSort = "CUENTA";
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCuenta.IsEOF())
	{
		m_lstBusquedaPorCod.AddTail(rsCuenta.m_CUENTA.Trim());
		m_lstBusquedaPorCod.AddTail(rsCuenta.m_NOMBRE.Trim());
		rsCuenta.MoveNext();
	}

	rsCuenta.Close();
}
/******************************************************************************************/
void CDialogBusqueda::CrearListaDesCuentas()
{
	CCuentas rsCuenta(m_db);

	rsCuenta.m_strSort = "NOMBRE";
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCuenta.IsEOF())
	{
		m_lstBusquedaPorDes.AddTail(rsCuenta.m_NOMBRE.Trim());
		m_lstBusquedaPorDes.AddTail(rsCuenta.m_CUENTA.Trim());
		rsCuenta.MoveNext();
	}

	rsCuenta.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsAlmacen()
{
	CCuentas rsCuentas(m_db);

	rsCuentas.m_strSort = "CUENTA";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	CString strCuenta;
	while (!rsCuentas.IsEOF())	//inserta el código del articulo y su descripción
	{	
		strCuenta = rsCuentas.m_CUENTA;
		strCuenta = strCuenta.Trim();

		/* Para ser una cuenta de almacén debe empezar por 3 y tener 9 caracteres */
		if (strCuenta.Left(1) == "3" && strCuenta.GetLength() == 9)
		{
			m_lstBusquedaPorCod.AddTail(strCuenta);
			m_lstBusquedaPorCod.AddTail(rsCuentas.m_NOMBRE.Trim());
		}

		rsCuentas.MoveNext();
	}

	rsCuentas.Close();		//cierra la tabla 	

}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesAlmacen()
{
	CCuentas rsCuentas(m_db);

	rsCuentas.m_strSort = "NOMBRE";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	CString strCuenta;
	while (!rsCuentas.IsEOF())	//inserta el código del articulo y su descripción
	{	
		strCuenta = rsCuentas.m_CUENTA;
		strCuenta = strCuenta.Trim();

		/* Para ser una cuenta de almacén debe empezar por 3 y tener 9 caracteres */
		if (strCuenta.Left(1) == "3" && strCuenta.GetLength() == 9)
		{
			m_lstBusquedaPorDes.AddTail(rsCuentas.m_NOMBRE.Trim());
			m_lstBusquedaPorDes.AddTail(strCuenta);
		}

		rsCuentas.MoveNext();
	}

	rsCuentas.Close();		//cierra la tabla 	
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsConceptos()
{
	CConcepto rsConcepto(m_db);

	rsConcepto.m_strSort = "CONCEPTO";
	if (!rsConcepto.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsConcepto.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsConcepto.m_CONCEPTO.Trim());
		m_lstBusquedaPorCod.AddTail(rsConcepto.m_DCONCEPTO.Trim());
		rsConcepto.MoveNext();
	}

	rsConcepto.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesConceptos()
{
	CConcepto rsConcepto(m_db);

	rsConcepto.m_strSort = "DCONCEPTO";
	if (!rsConcepto.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsConcepto.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsConcepto.m_DCONCEPTO.Trim());
		m_lstBusquedaPorDes.AddTail(rsConcepto.m_CONCEPTO.Trim());
		rsConcepto.MoveNext();
	}

	rsConcepto.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsIdioma()
{
	CIdiomas rsIdioma(m_db);

	rsIdioma.m_strSort = "IDIOMA";
	if (!rsIdioma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsIdioma.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsIdioma.m_IDIOMA.Trim());
		m_lstBusquedaPorCod.AddTail(rsIdioma.m_DIDIOMA.Trim());
		rsIdioma.MoveNext();
	}

	rsIdioma.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesIdioma()
{
	CIdiomas rsIdioma(m_db);

	rsIdioma.m_strSort = "DIDIOMA";
	if (!rsIdioma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsIdioma.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsIdioma.m_DIDIOMA.Trim());
		m_lstBusquedaPorDes.AddTail(rsIdioma.m_IDIOMA.Trim());
		rsIdioma.MoveNext();
	}

	rsIdioma.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsPais()
{
	CPais rsPais(m_db);

	rsPais.m_strSort = "CPAIS";
	if (!rsPais.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsPais.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsPais.m_CPAIS.Trim());
		m_lstBusquedaPorCod.AddTail(rsPais.m_DPAIS.Trim());
		rsPais.MoveNext();
	}

	rsPais.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesPais()
{
	CPais rsPais(m_db);

	rsPais.m_strSort = "DPAIS";
	if (!rsPais.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsPais.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsPais.m_DPAIS.Trim());
		m_lstBusquedaPorDes.AddTail(rsPais.m_CPAIS.Trim());
		rsPais.MoveNext();
	}

	rsPais.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsDivisas()
{
	CDivisas rsDivisas(m_db);

	rsDivisas.m_strSort = "DIVISA";
	if (!rsDivisas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsDivisas.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsDivisas.m_DIVISA.Trim());
		m_lstBusquedaPorCod.AddTail(rsDivisas.m_DDIVISA.Trim());
		rsDivisas.MoveNext();
	}

	rsDivisas.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesDivisas()
{
	CDivisas rsDivisas(m_db);

	rsDivisas.m_strSort = "DDIVISA";
	if (!rsDivisas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsDivisas.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsDivisas.m_DDIVISA.Trim());
		m_lstBusquedaPorDes.AddTail(rsDivisas.m_DIVISA.Trim());
		rsDivisas.MoveNext();
	}

	rsDivisas.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsFPagCob()
{
	CFPagCob rsFPagCob(m_db);

	rsFPagCob.m_strSort = "FCOBRO";
	if (!rsFPagCob.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsFPagCob.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsFPagCob.m_FCOBRO.Trim());
		m_lstBusquedaPorCod.AddTail(rsFPagCob.m_DFCOBRO.Trim());
		rsFPagCob.MoveNext();
	}

	rsFPagCob.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesFPagCob()
{
	CFPagCob rsFPagCob(m_db);

	rsFPagCob.m_strSort = "DFCOBRO";
	if (!rsFPagCob.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsFPagCob.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsFPagCob.m_DFCOBRO.Trim());
		m_lstBusquedaPorDes.AddTail(rsFPagCob.m_FCOBRO.Trim());
		rsFPagCob.MoveNext();
	}

	rsFPagCob.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsDirEnv()
{
	CDirEnv rsDirEnv(m_db);

	rsDirEnv.m_strSort = "DIRENV";
	rsDirEnv.m_strFilter = "CLIENTE = '" + m_strCliente + "'";
	if (!rsDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsDirEnv.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsDirEnv.m_DIRENV.Trim());
		m_lstBusquedaPorCod.AddTail(rsDirEnv.m_NOMDIRENV.Trim());
		rsDirEnv.MoveNext();
	}

	rsDirEnv.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesDirEnv()
{
	CDirEnv rsDirEnv(m_db);

	rsDirEnv.m_strSort = "NOMDIRENV";
	rsDirEnv.m_strFilter = "CLIENTE = '" + m_strCliente + "'";
	if (!rsDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsDirEnv.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsDirEnv.m_NOMDIRENV.Trim());
		m_lstBusquedaPorDes.AddTail(rsDirEnv.m_DIRENV.Trim());
		rsDirEnv.MoveNext();
	}

	rsDirEnv.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsZona()
{
	CZona rsZona(m_db);

	rsZona.m_strSort = "ZONA";
	if (!rsZona.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsZona.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsZona.m_ZONA.Trim());
		m_lstBusquedaPorCod.AddTail(rsZona.m_DZONA.Trim());
		rsZona.MoveNext();
	}

	rsZona.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesZona()
{
	CZona rsZona(m_db);

	rsZona.m_strSort = "DZONA";
	if (!rsZona.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsZona.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsZona.m_DZONA.Trim());
		m_lstBusquedaPorDes.AddTail(rsZona.m_ZONA.Trim());
		rsZona.MoveNext();
	}

	rsZona.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsRuTran()
{
	CRuTran rsRuTran(m_db);

	rsRuTran.m_strSort = "CRUTRAN";
	if (!rsRuTran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsRuTran.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsRuTran.m_CRUTRAN.Trim());
		m_lstBusquedaPorCod.AddTail(rsRuTran.m_DRUTRAN.Trim());
		rsRuTran.MoveNext();
	}

	rsRuTran.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesRuTran()
{
	CRuTran rsRuTran(m_db);

	rsRuTran.m_strSort = "DRUTRAN";
	if (!rsRuTran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsRuTran.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsRuTran.m_DRUTRAN.Trim());
		m_lstBusquedaPorDes.AddTail(rsRuTran.m_CRUTRAN.Trim());
		rsRuTran.MoveNext();
	}

	rsRuTran.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsSeguro()
{
	CSeguro rsSeguro(m_db);

	rsSeguro.m_strSort = "SEGURO";
	if (!rsSeguro.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsSeguro.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsSeguro.m_SEGURO.Trim());
		m_lstBusquedaPorCod.AddTail(rsSeguro.m_DSEGURO.Trim());
		rsSeguro.MoveNext();
	}

	rsSeguro.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesSeguro()
{
	CSeguro rsSeguro(m_db);

	rsSeguro.m_strSort = "DSEGURO";
	if (!rsSeguro.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsSeguro.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsSeguro.m_DSEGURO.Trim());
		m_lstBusquedaPorDes.AddTail(rsSeguro.m_SEGURO.Trim());
		rsSeguro.MoveNext();
	}

	rsSeguro.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsProveedores()
{
	CProve rsProve(m_db);

	rsProve.m_strSort = "CUENTA";
	if (!rsProve.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsProve.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsProve.m_CUENTA.Trim());
		m_lstBusquedaPorCod.AddTail(rsProve.m_NOMBRE.Trim());
		rsProve.MoveNext();
	}

	rsProve.Close();


	/*CCuentas rsCuentas(m_db);

	rsCuentas.m_strSort = "CUENTA";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	CString strCuenta;
	while (!rsCuentas.IsEOF())	//inserta el código del articulo y su descripción
	{	
		strCuenta = rsCuentas.m_CUENTA;
		strCuenta = strCuenta.Trim();

		/* Para ser una cuenta de Proveedor debe empezar por 40 o 41 y tener 9 caracteres */
	/*	if ((strCuenta.Left(2) == "40" || strCuenta.Left(2) == "41") && strCuenta.GetLength() == 9)
		{
			m_lstBusquedaPorCod.AddTail(strCuenta);
			m_lstBusquedaPorCod.AddTail(rsCuentas.m_NOMBRE.Trim());
		}

		rsCuentas.MoveNext();
	}

	rsCuentas.Close();*/		//cierra la tabla 	
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesProveedores()
{
	CProve rsProve(m_db);

	rsProve.m_strSort = "NOMBRE";
	if (!rsProve.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsProve.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsProve.m_NOMBRE.Trim());
		m_lstBusquedaPorDes.AddTail(rsProve.m_CUENTA.Trim());
		rsProve.MoveNext();
	}

	rsProve.Close();

/*	CCuentas rsCuentas(m_db);

	rsCuentas.m_strSort = "NOMBRE";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	CString strCuenta;
	while (!rsCuentas.IsEOF())	//inserta el código del articulo y su descripción
	{	
		strCuenta = rsCuentas.m_CUENTA;
		strCuenta = strCuenta.Trim();

		/* Para ser una cuenta de Proveedor debe empezar por 40 o 41 y tener 9 caracteres */
/*		if ((strCuenta.Left(2) == "40" || strCuenta.Left(2) == "41") && strCuenta.GetLength() == 9)
		{
			m_lstBusquedaPorDes.AddTail(rsCuentas.m_NOMBRE.Trim());
			m_lstBusquedaPorDes.AddTail(strCuenta);
		}

		rsCuentas.MoveNext();
	}

	rsCuentas.Close();		//cierra la tabla 	*/
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsClientes()
{
	CClientes rsClientes(m_db);

	rsClientes.m_strSort = "CUENTA";
	if (!rsClientes.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsClientes.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsClientes.m_CUENTA.Trim());
		m_lstBusquedaPorCod.AddTail(rsClientes.m_NOMBRE.Trim());
		rsClientes.MoveNext();
	}

	rsClientes.Close();

/*	CCuentas rsCuentas(m_db);

	rsCuentas.m_strSort = "CUENTA";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	CString strCuenta;
	while (!rsCuentas.IsEOF())	//inserta el código del articulo y su descripción
	{	
		strCuenta = rsCuentas.m_CUENTA;
		strCuenta = strCuenta.Trim();

		/* Para ser una cuenta de Cliente debe empezar por 42 o 43 y tener 9 caracteres */
/*		if ((strCuenta.Left(2) == "42" || strCuenta.Left(2) == "43") && strCuenta.GetLength() == 9)
		{
			m_lstBusquedaPorCod.AddTail(strCuenta);
			m_lstBusquedaPorCod.AddTail(rsCuentas.m_NOMBRE.Trim());
		}

		rsCuentas.MoveNext();
	}

	rsCuentas.Close();		//cierra la tabla 	*/
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesClientes()
{
	CClientes rsClientes(m_db);

	rsClientes.m_strSort = "NOMBRE";
	if (!rsClientes.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsClientes.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsClientes.m_NOMBRE.Trim());
		m_lstBusquedaPorDes.AddTail(rsClientes.m_CUENTA.Trim());
		rsClientes.MoveNext();
	}

	rsClientes.Close();

/*	CCuentas rsCuentas(m_db);

	rsCuentas.m_strSort = "NOMBRE";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	CString strCuenta;
	while (!rsCuentas.IsEOF())	//inserta el código del articulo y su descripción
	{	
		strCuenta = rsCuentas.m_CUENTA;
		strCuenta = strCuenta.Trim();

			/* Para ser una cuenta de Cliente debe empezar por 42 o 43 y tener 9 caracteres */
/*		if (strCuenta.Left(2) == "43" && strCuenta.GetLength() == 9)
		{
			m_lstBusquedaPorDes.AddTail(rsCuentas.m_NOMBRE.Trim());
			m_lstBusquedaPorDes.AddTail(strCuenta);
		}

		rsCuentas.MoveNext();
	}

	rsCuentas.Close();		//cierra la tabla 	*/
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsCentros()
{
	CCentros rsCentros(m_db);

	rsCentros.m_strSort = "CCENTRO";
	if (!rsCentros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCentros.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsCentros.m_CCENTRO.Trim());
		m_lstBusquedaPorCod.AddTail(rsCentros.m_DCENTRO.Trim());
		rsCentros.MoveNext();
	}

	rsCentros.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesCentros()
{
	CCentros rsCentros(m_db);

	rsCentros.m_strSort = "DCENTRO";
	if (!rsCentros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCentros.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsCentros.m_DCENTRO.Trim());
		m_lstBusquedaPorDes.AddTail(rsCentros.m_CCENTRO.Trim());
		rsCentros.MoveNext();
	}

	rsCentros.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsOfertas()
{
	CProforma rsProforma(m_db);

	//rsProforma.m_strSort = "NUMPROFOR";
	// CUANDO SE MIGRE NO HACE FALTA EL DISTINCT. EL NÚMERO DE OFERTA SERÁ ÚNICO
	//if (!rsProforma.Open(CRecordset::dynaset))
	//if (!rsProforma.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPROFOR, NUMPEDIDO, NUMALB, FECHPROF, FECHPRE, FECHALB, FECHFAC, FECHENT, CUENTA FROM PROFORMA ORDER BY NUMPROFOR"))
	if (!rsProforma.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPROFOR, CUENTA FROM PROFORMA ORDER BY NUMPROFOR"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsProforma.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsProforma.m_NUMPROFOR.Trim());
		m_lstBusquedaPorCod.AddTail(rsProforma.m_CUENTA.Trim());
		rsProforma.MoveNext();
	}

	rsProforma.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesOfertas()
{
	CProforma rsProforma(m_db);

	//rsProforma.m_strSort = "CUENTA";
	// CUANDO SE MIGRE NO HACE FALTA EL DISTINCT. EL NÚMERO DE OFERTA SERÁ ÚNICO
	//if (!rsProforma.Open(CRecordset::dynaset))
	//if (!rsProforma.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPROFOR, NUMPEDIDO, NUMALB, FECHPROF, FECHPRE, FECHALB, FECHFAC, FECHENT, CUENTA FROM PROFORMA ORDER BY CUENTA"))
	if (!rsProforma.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPROFOR, CUENTA FROM PROFORMA ORDER BY CUENTA"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsProforma.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsProforma.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsProforma.m_NUMPROFOR.Trim());
		rsProforma.MoveNext();
	}

	rsProforma.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsPedidos()
{
	CPedidos rsPedidos(m_db);

	//rsPedidos.m_strSort = "NUMPEDIDO";
	// CUANDO SE MIGRE NO HACE FALTA EL DISTINCT. EL NÚMERO DE PEDIDO SERÁ ÚNICO
	//if (!rsPedidos.Open(CRecordset::dynaset))
	//if (!rsPedidos.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPEDIDO, NUMFAC, NUMALB, " \
	//	"FECHPED, FECHPRE, FECHALB, FECHFAC, FECHENT, CUENTA FROM PEDIDOS ORDER BY NUMPEDIDO"))
	if (!rsPedidos.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPEDIDO, CUENTA FROM PEDIDOS ORDER BY NUMPEDIDO"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsPedidos.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsPedidos.m_NUMPEDIDO.Trim());
		m_lstBusquedaPorCod.AddTail(rsPedidos.m_CUENTA.Trim());
		rsPedidos.MoveNext();
	}

	rsPedidos.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesPedidos()
{
	CPedidos rsPedidos(m_db);

	//rsPedidos.m_strSort = "CUENTA";
	// CUANDO SE MIGRE NO HACE FALTA EL DISTINCT. EL NÚMERO DE PEDIDO SERÁ ÚNICO
	//if (!rsPedidos.Open(CRecordset::dynaset))
	//if (!rsPedidos.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPEDIDO, NUMFAC, NUMALB, " \
	//	"FECHPED, FECHPRE, FECHALB, FECHFAC, FECHENT, CUENTA FROM PEDIDOS ORDER BY CUENTA"))
	if (!rsPedidos.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPEDIDO, CUENTA FROM PEDIDOS ORDER BY CUENTA"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsPedidos.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsPedidos.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsPedidos.m_NUMPEDIDO.Trim());
		rsPedidos.MoveNext();
	}

	rsPedidos.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsAlbaranes()
{
	CAlbaran rsAlbaran(m_db);

	//rsAlbaran.m_strSort = "NUMALB";
	// CUANDO SE MIGRE NO HACE FALTA EL DISTINCT. EL NÚMERO DE ALBARAN SERÁ ÚNICO
	//if (!rsAlbaran.Open(CRecordset::dynaset))
	if (!rsAlbaran.Open(CRecordset::dynaset, "SELECT DISTINCT NUMALB, CUENTA FROM ALBARANE ORDER BY NUMALB"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsAlbaran.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsAlbaran.m_NUMALB.Trim());
		m_lstBusquedaPorCod.AddTail(rsAlbaran.m_CUENTA.Trim());
		rsAlbaran.MoveNext();
	}

	rsAlbaran.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesAlbaranes()
{
	CAlbaran rsAlbaran(m_db);

	//rsAlbaran.m_strSort = "CUENTA";
	// CUANDO SE MIGRE NO HACE FALTA EL DISTINCT. EL NÚMERO DE ALBARAN SERÁ ÚNICO
	//if (!rsPedidos.Open(CRecordset::dynaset))
	if (!rsAlbaran.Open(CRecordset::dynaset, "SELECT DISTINCT NUMALB, CUENTA FROM ALBARANE ORDER BY CUENTA"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsAlbaran.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsAlbaran.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsAlbaran.m_NUMALB.Trim());
		rsAlbaran.MoveNext();
	}

	rsAlbaran.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsPedidosCli()
{
	CPedidos rsPedidos(m_db);

	CString strSQL = "SELECT DISTINCT NUMPEDIDO, CUENTA FROM PEDIDOS WHERE CUENTA = '" + m_strCliente + "' ORDER BY NUMPEDIDO";
	if (!rsPedidos.Open(CRecordset::dynaset, strSQL))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsPedidos.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsPedidos.m_NUMPEDIDO.Trim());
		m_lstBusquedaPorCod.AddTail(rsPedidos.m_CUENTA.Trim());
		rsPedidos.MoveNext();
	}

	rsPedidos.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesPedidosCli()
{
	CPedidos rsPedidos(m_db);

	CString strSQL = "SELECT DISTINCT NUMPEDIDO, CUENTA FROM PEDIDOS WHERE CUENTA = '" + m_strCliente + "' ORDER BY CUENTA";
	if (!rsPedidos.Open(CRecordset::dynaset, strSQL))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsPedidos.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsPedidos.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsPedidos.m_NUMPEDIDO.Trim());
		rsPedidos.MoveNext();
	}

	rsPedidos.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsCompras()
{
	CCompras rsCompras(m_db);

	if (!rsCompras.Open(CRecordset::dynaset, "SELECT DISTINCT NPEDCOM, CUENTA FROM COMPRAS ORDER BY NPEDCOM"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCompras.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsCompras.m_NPEDCOM.Trim());
		m_lstBusquedaPorCod.AddTail(rsCompras.m_CUENTA.Trim());
		rsCompras.MoveNext();
	}

	rsCompras.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesCompras()
{
	CCompras rsCompras(m_db);
	
	if (!rsCompras.Open(CRecordset::dynaset, "SELECT DISTINCT NPEDCOM, CUENTA FROM COMPRAS ORDER BY CUENTA"))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCompras.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsCompras.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsCompras.m_NPEDCOM.Trim());
		rsCompras.MoveNext();
	}

	rsCompras.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsAlbCompra()
{
	CAlbCompra rsAlbCompra(m_db);

	rsAlbCompra.m_strSort = "NALBCOM";
	if (!rsAlbCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsAlbCompra.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsAlbCompra.m_NALBCOM.Trim());
		m_lstBusquedaPorCod.AddTail(rsAlbCompra.m_CUENTA.Trim());
		rsAlbCompra.MoveNext();
	}

	rsAlbCompra.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesAlbCompra()
{
	CAlbCompra rsAlbCompra(m_db);

	rsAlbCompra.m_strSort = "CUENTA";
	if (!rsAlbCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsAlbCompra.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsAlbCompra.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsAlbCompra.m_NALBCOM.Trim());
		rsAlbCompra.MoveNext();
	}

	rsAlbCompra.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsPedidosProve()
{
	CCompras rsCompras(m_db);

	rsCompras.m_strFilter = "CUENTA = '" + m_strCliente + "'";
	rsCompras.m_strSort = "NPEDCOM";
	if (!rsCompras.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCompras.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsCompras.m_NPEDCOM.Trim());
		m_lstBusquedaPorCod.AddTail(rsCompras.m_CUENTA.Trim());
		rsCompras.MoveNext();
	}

	rsCompras.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesPedidosProve()
{
	CCompras rsCompras(m_db);

	rsCompras.m_strFilter = "CUENTA = '" + m_strCliente + "'";
	rsCompras.m_strSort = "CUENTA";
	if (!rsCompras.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCompras.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsCompras.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsCompras.m_NPEDCOM.Trim());
		rsCompras.MoveNext();
	}

	rsCompras.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsFacturas()
{
	CFacturas rsFactura(m_db);

	rsFactura.m_strSort = "NUMFAC";
	if (!rsFactura.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsFactura.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsFactura.m_NUMFAC.Trim());
		m_lstBusquedaPorCod.AddTail(rsFactura.m_CUENTA.Trim());
		rsFactura.MoveNext();
	}

	rsFactura.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesFacturas()
{
	CFacturas rsFactura(m_db);

	rsFactura.m_strSort = "CUENTA";
	if (!rsFactura.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsFactura.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsFactura.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsFactura.m_NUMFAC.Trim());
		rsFactura.MoveNext();
	}

	rsFactura.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsAlbaranesPedidoCli()
{
	CAlbaran rsAlbaran(m_db);

	CString strSQL = "SELECT DISTINCT NUMALB, CUENTA FROM ALBARANE WHERE CUENTA = '" + m_strCliente + "' AND NUMPEDIDO = '" + m_strPedido + "' AND TIPO = 'D' ORDER BY NUMALB";
	if (!rsAlbaran.Open(CRecordset::dynaset, strSQL))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsAlbaran.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsAlbaran.m_NUMALB.Trim());
		m_lstBusquedaPorCod.AddTail(rsAlbaran.m_CUENTA.Trim());
		rsAlbaran.MoveNext();
	}

	rsAlbaran.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesAlbaranesPedidoCli()
{
	CAlbaran rsAlbaran(m_db);

	CString strSQL = "SELECT DISTINCT NUMALB, CUENTA FROM ALBARANE WHERE CUENTA = '" + m_strCliente + "' AND NUMPEDIDO = '" + m_strPedido + "' AND TIPO = 'D' ORDER BY CUENTA";
	if (!rsAlbaran.Open(CRecordset::dynaset, strSQL))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsAlbaran.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsAlbaran.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsAlbaran.m_NUMALB.Trim());
		rsAlbaran.MoveNext();
	}

	rsAlbaran.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsCobros()
{
	CCobros rsCobros(m_db);

	rsCobros.m_strSort = "NUMEFEC";
	rsCobros.m_strFilter = "NUMFAC = '" + m_strFactura + "'";
	if (!rsCobros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCobros.IsEOF())	
	{	
		m_lstBusquedaPorCod.AddTail(rsCobros.m_NUMEFEC.Trim());
		m_lstBusquedaPorCod.AddTail(rsCobros.m_CUENTA.Trim());
		rsCobros.MoveNext();
	}

	rsCobros.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesCobros()
{
	CCobros rsCobros(m_db);

	rsCobros.m_strSort = "CUENTA";
	rsCobros.m_strFilter = "NUMFAC = '" + m_strFactura + "'";
	if (!rsCobros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	while (!rsCobros.IsEOF())	
	{	
		m_lstBusquedaPorDes.AddTail(rsCobros.m_CUENTA.Trim());
		m_lstBusquedaPorDes.AddTail(rsCobros.m_NUMEFEC.Trim());
		rsCobros.MoveNext();
	}

	rsCobros.Close();
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaCodsEstados()
{
	for (int i=0; i<iNumEstados; i++)
	{
		m_lstBusquedaPorCod.AddTail(lstEstados[i]);
		m_lstBusquedaPorCod.AddTail(lstDesEstados[i]);
	}
}

/******************************************************************************************/
void CDialogBusqueda::CrearListaDesEstados()
{
	for (int i=0; i<iNumEstados; i++)
	{
		m_lstBusquedaPorDes.AddTail(lstDesEstados[i]);
		m_lstBusquedaPorDes.AddTail(lstEstados[i]);
	}
}
/******************************************************************************************/
void CDialogBusqueda::NuevaDirEnv()
{
	CDlgDireccionEnvio rsDirEnv;
	rsDirEnv.SetConexion(m_db);
	rsDirEnv.SetCliente(m_strCliente, m_strDesCliente);
	rsDirEnv.SetTipo(FALSE);
	rsDirEnv.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarDirEnv()
{
	CDlgDireccionEnvio rsDirEnv;
	rsDirEnv.SetConexion(m_db);
	rsDirEnv.SetCliente(m_strCliente, m_strDesCliente);
	rsDirEnv.SetTipo(TRUE);
	rsDirEnv.SetObra(strCodigo);
	rsDirEnv.DoModal();
	InicializarListas();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaIdioma()
{
	CDlgIdiomas rsIdiomas;
	rsIdiomas.SetUpdate(FALSE);
	rsIdiomas.SetConexion(m_db);
	rsIdiomas.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarIdioma()
{
	CDlgIdiomas rsIdiomas;
	rsIdiomas.SetIdioma(m_strCodigo,m_strDescripcion);
	rsIdiomas.SetUpdate(TRUE);
	rsIdiomas.SetConexion(m_db);
	rsIdiomas.DoModal();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaPais()
{
	CDlgPais rsPais;
	rsPais.SetUpdate(FALSE);
	rsPais.SetConexion(m_db);
	rsPais.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarPais()
{
	CDlgPais rsPais;
	rsPais.SetPais(m_strCodigo,m_strDescripcion);
	rsPais.SetUpdate(TRUE);
	rsPais.SetConexion(m_db);
	rsPais.DoModal();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaFPagCob()
{
	CDlgFPagCob rsFPagCob;
	rsFPagCob.SetUpdate(FALSE);
	rsFPagCob.SetConexion(m_db);
	rsFPagCob.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarFPagCob()
{
	CDlgFPagCob rsFPagCob;
	rsFPagCob.SetFPagCob(m_strCodigo,m_strDescripcion);
	rsFPagCob.SetUpdate(TRUE);
	rsFPagCob.SetConexion(m_db);
	rsFPagCob.DoModal();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaSeguro()
{
	CDlgSeguros rsSeguro;
	rsSeguro.SetUpdate(FALSE);
	rsSeguro.SetConexion(m_db);
	rsSeguro.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarSeguro()
{
	CDlgSeguros rsSeguro;
	rsSeguro.SetSeguros(m_strCodigo,m_strDescripcion);
	rsSeguro.SetUpdate(TRUE);
	rsSeguro.SetConexion(m_db);
	rsSeguro.DoModal();
	InicializarListas();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaCentros()
{
	CDlgCentros rsCentro;
	rsCentro.SetUpdate(FALSE);
	rsCentro.SetConexion(m_db);
	rsCentro.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarCentros()
{
	CDlgCentros rsCentro;
	rsCentro.SetCentros(m_strCodigo,m_strDescripcion);
	rsCentro.SetUpdate(TRUE);
	rsCentro.SetConexion(m_db);
	rsCentro.DoModal();
	ReCargaLista();
	InicializarListas();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaConcepto()
{
	CDlgConcepto rsConcepto;
	rsConcepto.SetUpdate(FALSE);
	rsConcepto.SetConexion(m_db);
	rsConcepto.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarConcepto()
{
	CDlgConcepto rsConcepto;
	rsConcepto.SetConcepto(m_strCodigo,m_strDescripcion);
	rsConcepto.SetUpdate(TRUE);
	rsConcepto.SetConexion(m_db);
	rsConcepto.DoModal();
	InicializarListas();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaZona()
{
	CDlgConcepto rsZona;
	rsZona.SetUpdate(FALSE);
	rsZona.SetConexion(m_db);
	rsZona.DoModal();
	InicializarListas();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::ModificarZona()
{
	CDlgZona rsZona;
	rsZona.SetZona(m_strCodigo,m_strDescripcion);
	rsZona.SetUpdate(TRUE);
	rsZona.SetConexion(m_db);
	rsZona.DoModal();
	InicializarListas();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::ModificarRuTran()
{
	CDlgRutran rsRuTran;
	rsRuTran.SetRuTran(m_strCodigo,m_strDescripcion);
	rsRuTran.SetUpdate(TRUE);
	rsRuTran.SetConexion(m_db);
	rsRuTran.DoModal();
	InicializarListas();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaRuTran()
{
	CDlgRutran rsRuTran;
	rsRuTran.SetUpdate(FALSE);
	rsRuTran.SetConexion(m_db);
	rsRuTran.DoModal();
	InicializarListas();
	ReCargaLista();
}
/******************************************************************************************/
void CDialogBusqueda::NuevaDivisa()
{
	CDlgDivisas rsDivisa;
	rsDivisa.SetUpdate(FALSE);
	rsDivisa.SetConexion(m_db);
	rsDivisa.DoModal();
	InicializarListas();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::ModificarDivisa()
{
	CDlgDivisas rsDivisa;
	rsDivisa.SetDivisas(m_strCodigo,m_strDescripcion);
	rsDivisa.SetUpdate(TRUE);
	rsDivisa.SetConexion(m_db);
	rsDivisa.DoModal();
	ReCargaLista();
}

/******************************************************************************************/
void CDialogBusqueda::OnBnClickedCancel()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	OnCancel();
}
