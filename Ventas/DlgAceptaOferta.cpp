/******************************************************************************************/
// DlgAceptaOferta.cpp: archivo de implementación
/******************************************************************************************/

#include "stdafx.h"
#include "DlgAceptaOferta.h"
#include "BD.h"
#include ".\dlgaceptaoferta.h"
#include "Etiquetas.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgAceptaOferta
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgAceptaOferta, CDialog)
CDlgAceptaOferta::CDlgAceptaOferta(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAceptaOferta::IDD, pParent)
	, m_strNumOferta(_T(""))
	, m_strEstado(_T(""))
	, m_fechaPedido(0)
	, m_strMotivo(_T(""))
	, m_iAccion(0)
	, m_strAlmacen(_T(""))
	, m_strDesAlmacen(_T(""))
{
}

/******************************************************************************************/
CDlgAceptaOferta::~CDlgAceptaOferta()
{
}

/******************************************************************************************/
void CDlgAceptaOferta::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMOFERTA, m_strNumOferta);
	DDV_MaxChars(pDX, m_strNumOferta, 10);
	DDX_Text(pDX, IDC_ESTADO, m_strEstado);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_PEDIDO, m_fechaPedido);
	DDX_Text(pDX, IDC_MOTIVO, m_strMotivo);
	DDV_MaxChars(pDX, m_strMotivo, 35);
	DDX_Radio(pDX, IDC_ACEPTAR, m_iAccion);
	DDX_Text(pDX, IDC_EDIT_ALMACEN, m_strAlmacen);
	DDV_MaxChars(pDX, m_strAlmacen, 9);
	DDX_Text(pDX, IDC_EDIT_DESALMACEN, m_strDesAlmacen);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgAceptaOferta, CDialog)
	ON_BN_CLICKED(IDC_BTN_OFERTA, OnBnClickedBtnOferta)
	ON_BN_CLICKED(IDC_ACEPTAR, OnBnClickedAceptar)
	ON_BN_CLICKED(IDC_DENEGAR, OnBnClickedDenegar)
	ON_EN_KILLFOCUS(IDC_NUMOFERTA, OnEnKillfocusNumoferta)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT_ALMACEN, OnEnKillfocusEditAlmacen)
	ON_BN_CLICKED(IDC_BTN_ALMACEN, OnBnClickedBtnAlmacen)
//	ON_NOTIFY(NM_KILLFOCUS, 1000, OnNMKillfocusFechaPedido)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgAceptaOferta
/******************************************************************************************/

BOOL CDlgAceptaOferta::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se inicializa el array para obtener los diferentes estados
	m_strTiposEstado.AddTail("A"); m_strTiposEstado.AddTail(PENDIENTE);
	m_strTiposEstado.AddTail("E"); m_strTiposEstado.AddTail(ACEPTADA);
	m_strTiposEstado.AddTail("R"); m_strTiposEstado.AddTail(DENEGADA);

	// Se establece la Base de Datos para el diálogo de búsqueda
	m_dlgBusquedaOfertas.SetConexion(m_db);
	m_dlgBusquedaAlmacen.SetConexion(m_db);

	// Se inicializa la fecha de pedido
	m_fechaPedido = CTime::GetCurrentTime();

	// Se inicializa el tipo de acción
	m_iAccion = ACEPTAR;

	GetDlgItem(IDC_STATIC_MOTIVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_MOTIVO)->EnableWindow(FALSE);

	UpdateData(FALSE);

	GetDlgItem(IDC_NUMOFERTA)->SetFocus();

	return FALSE;
}

/******************************************************************************************/
void CDlgAceptaOferta::OnBnClickedBtnOferta()
{
	INT_PTR status;

	m_dlgBusquedaOfertas.SetTipo(CDialogBusqueda::OFERTAS);
	status = m_dlgBusquedaOfertas.DoModal();
	if (status == IDOK)
	{
		m_strNumOferta = m_dlgBusquedaOfertas.GetCodigo();
		BuscaNumOferta();
		//m_strCuenta = m_dlgBusquedaOfertas.GetDescripcion();
	}

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgAceptaOferta::OnEnKillfocusNumoferta()
{
	CString strNumOfertaOld = m_strNumOferta;

	GetDlgItem(IDC_NUMOFERTA)->GetWindowText(m_strNumOferta);
	m_strNumOferta = m_strNumOferta.Trim();

	if (!m_strNumOferta.IsEmpty())
	{
		// Si la oferta no existe se deja la anterior y se da un mensaje de error
		if (!BuscaNumOferta())
		{
			AfxMessageBox(IDC_OFERTA_NO_EXISTS);
			m_strNumOferta = strNumOfertaOld;
			GetDlgItem(IDC_NUMOFERTA)->SetFocus();
		}
	}
	else
		m_strEstado.Empty();

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgAceptaOferta::OnEnKillfocusEditAlmacen()
{
	CString strOldAlmacen = m_strAlmacen;

	GetDlgItem(IDC_EDIT_ALMACEN)->GetWindowText(m_strAlmacen);

	if (!m_strAlmacen.IsEmpty())
	{
		// Si el almacen no existe se deja el anterior y se da un mensaje de error
		if (!BuscaAlmacen())
		{
			//AfxMessageBox(IDC_ALMACEN_NO_EXISTS);
			m_strAlmacen = strOldAlmacen;
			GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strAlmacen);
		}
		else
			GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);
	}
	else
	{
		m_strDesAlmacen.Empty();

		GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strAlmacen);
		GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);
	}
}

/******************************************************************************************/
void CDlgAceptaOferta::OnBnClickedBtnAlmacen()
{
	INT_PTR status;

	m_dlgBusquedaAlmacen.SetTipo(CDialogBusqueda::ALMACEN);
	status = m_dlgBusquedaAlmacen.DoModal();
	if (status == IDOK)
	{
		m_strAlmacen = m_dlgBusquedaAlmacen.GetCodigo();
		m_strAlmacen = m_strAlmacen.Trim();
		m_strDesAlmacen = m_dlgBusquedaAlmacen.GetDescripcion();
	}	

	GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strAlmacen);
	GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);
}

/******************************************************************************************/
void CDlgAceptaOferta::OnBnClickedAceptar()
{
	m_iAccion = ACEPTAR;

	GetDlgItem(IDC_STATIC_FECHA)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA_PEDIDO)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_ALMACEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ALMACEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DESALMACEN)->EnableWindow(TRUE);

	GetDlgItem(IDC_STATIC_MOTIVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_MOTIVO)->EnableWindow(FALSE);
}

/******************************************************************************************/
void CDlgAceptaOferta::OnBnClickedDenegar()
{
	m_iAccion = DENEGAR;

	GetDlgItem(IDC_STATIC_MOTIVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MOTIVO)->EnableWindow(TRUE);

	GetDlgItem(IDC_STATIC_FECHA)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_PEDIDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_ALMACEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ALMACEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DESALMACEN)->EnableWindow(FALSE);

}

/******************************************************************************************/
void CDlgAceptaOferta::OnBnClickedOk()
{
	HRESULT hErr = S_OK;

	UpdateData();

	if (m_strNumOferta.IsEmpty())
	{
		AfxMessageBox(IDC_NO_OFERTA);
		return;
	}
	
	if (m_iAccion == ACEPTAR)
	{
		// Se comprueba si el estado de la oferta no está a PENDIENTE se sale con error
		if (m_strEstado == ACEPTADA)
		{
			AfxMessageBox(IDC_YA_ACEPTADA);
			return;
		}
		else if (m_strEstado == DENEGADA)
		{
			AfxMessageBox(IDC_DENEGADA);
			return;
		}

		// Se comprueba que se haya introducido un almacén
		if (m_strAlmacen.IsEmpty())
		{
			AfxMessageBox(IDC_NO_ALMACEN);
			return;
		}

		// Se actualiza el estado de la oferta y se crea el pedido
		if (!m_db->BeginTrans())
			return;
	
		// Se crea el pedido de venta
		CPedidos rsPedidos(m_db);
		CConta rsConta(m_db);
		CArtiProforma rsArtiProforma(m_db);
		CArtiVenta rsArtiVenta(m_db);

		// Se coge el siguiente número de pedido de venta
		CString strNextNumPedido;
		hErr = rsConta.GetNextNumPedidoVenta(strNextNumPedido);

		if (hErr == S_OK)
		{
			rsPedidos.m_NUMPEDIDO = strNextNumPedido;
			RellenaPedido(&rsPedidos);
			hErr = rsPedidos.Insert();

			// Se crean los articulos del pedido
			if (hErr == S_OK)
			{
				hErr = ObtenerArticulos(&rsArtiProforma);		

				if (hErr == S_OK)
				{
					for (int i=0; i<rsArtiProforma.GetRecordCount()&& hErr == S_OK; i++)
					{
						// Se comprueba si hay articulos disponibles, si no se da una advertencia
						// Sólo se comprueba si son artículos de Alquiler o Venta
						if (rsArtiProforma.m_ALQUILER == "S" || rsArtiProforma.m_ALQUILER == "V")
							CompruebaArtiDisponible(&rsArtiProforma);

						rsArtiVenta.m_NUMPEDIDO = strNextNumPedido;
						RellenaArtiVenta(&rsArtiProforma, &rsArtiVenta);
						hErr = rsArtiVenta.Insert();
						rsArtiProforma.MoveNext();
					}
				}

			}
		}

		// Se cambia el estado a Aceptada
		if (hErr == S_OK)
		{
			m_rsProforma.m_ESTADO = TIPO_ACEPTADA;
			hErr = m_rsProforma.UpdateEstadoProforma();
		}

		// Se actualiza el número del nuevo pedido creado en la Oferta
		if (hErr == S_OK)
		{
			m_rsProforma.m_NUMPEDIDO = strNextNumPedido;
			hErr = m_rsProforma.UpdateNumPedido();
		}
			
		if (hErr == S_OK)
			m_db->CommitTrans();
		else
			m_db->Rollback();	

		// Si no hay disponibilidad de algún artículo, se advierte
		if (!m_lArtiNoDisponible.IsEmpty())
			MuestraAviso();

		if (hErr == S_OK)
		{
			CString strMsg;
			strMsg.Format(IDC_CREADO_PEDIDO, strNextNumPedido); 
			AfxMessageBox(strMsg, MB_ICONINFORMATION);
		}

	}

	// Si la oferta es denegada se le cambia el estado y se introducen los comentarios
	else if (m_iAccion == DENEGAR)
	{
		// Se comprueba si el estado de la oferta es PENDIENTE, nunca DENEGADO o ACEPTADA
		if (m_strEstado == ACEPTADA)
		{
			AfxMessageBox(IDC_ACEPTADA);
			return;
		}

		if (m_strEstado == DENEGADA)
		{
			AfxMessageBox(IDC_YA_DENEGADA);
			return;
		}

		// Se actualiza el estado de la oferta y el comentario de la denegacion
		if (!m_db->BeginTrans())
			return;

		m_rsProforma.m_ESTADO = TIPO_DENEGADA;
		m_rsProforma.m_OBSDENEGA = m_strMotivo;

		hErr = m_rsProforma.UpdateEstadoProforma();
		if (hErr == S_OK)
			m_rsProforma.UpdateObsDenegaProforma();

		if (hErr == S_OK)
			m_db->CommitTrans();
		else
			m_db->Rollback();
	}

	LimpiaVentana();
	//OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgAceptaOferta::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsProforma.m_pDatabase = db;
}

/******************************************************************************************/
BOOL CDlgAceptaOferta::BuscaNumOferta()
{
	BOOL bExists = FALSE;

	m_rsProforma.m_NUMPROFOR.Empty();

	//m_rsProforma.m_strFilter = "NUMPROFOR LIKE '" + m_strNumOferta + "'";
	//if (!m_rsProforma.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPROFOR, NUMPEDIDO, NUMALB, FECHPROF, FECHPRE, FECHALB, FECHFAC, FECHENT, CUENTA FROM PROFORMA"))
	m_rsProforma.m_strFilter = "NUMPROFOR = " + m_strNumOferta;
	if (!m_rsProforma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la oferta existe se busca el nombre del Cliente
	if (!m_rsProforma.m_NUMPROFOR.IsEmpty())
	{
		m_strNumOferta = m_rsProforma.m_NUMPROFOR.Trim();
		
		// Se busca el estado de la proforma
		POSITION pos = m_strTiposEstado.Find(m_rsProforma.m_ESTADO);	
		if (pos != NULL)
		{
			m_strTiposEstado.GetNext(pos);
			m_strEstado = m_strTiposEstado.GetNext(pos);

			// Si el estado es denegado se escribe el comentario de denegacion si lo tuviera
			if (m_strEstado == DENEGADA)
				m_strMotivo = m_rsProforma.m_OBSDENEGA.Trim();
			else
				m_strMotivo.Empty();
		}
		else
			m_strEstado.Empty();		

		bExists = TRUE;
	}

	m_rsProforma.Close();

	return bExists;
}

/******************************************************************************************/
void CDlgAceptaOferta::RellenaPedido(CPedidos *rsPedidos)
{
	rsPedidos->m_EXPORTA = m_rsProforma.m_EXPORTA.Trim();
	rsPedidos->m_TIPO = m_rsProforma.m_TIPO.Trim();
	rsPedidos->m_CUENTA = m_rsProforma.m_CUENTA.Trim();
	rsPedidos->m_ALMACEN = m_strAlmacen;
	rsPedidos->m_ESTADO = NO_FACTURADO;
	rsPedidos->m_TARIFA = m_rsProforma.m_TARIFA.Trim();
	rsPedidos->m_DCTOS = m_rsProforma.m_DCTOS;
	rsPedidos->m_DCTOS2 = m_rsProforma.m_DCTOS2;
	rsPedidos->m_DCTOS3 = m_rsProforma.m_DCTOS3;
	rsPedidos->m_PP = m_rsProforma.m_PP;
	rsPedidos->m_IVA = m_rsProforma.m_IVA;
	rsPedidos->m_GRUFAC = m_rsProforma.m_GRUFAC.Trim();
	rsPedidos->m_DIRENV = m_rsProforma.m_DIRENV.Trim();
	rsPedidos->m_REPRE = m_rsProforma.m_REPRE.Trim();
	rsPedidos->m_SUBREP = m_rsProforma.m_SUBREP.Trim();
	rsPedidos->m_COMISION = m_rsProforma.m_COMISION;
	rsPedidos->m_COMISION2 = m_rsProforma.m_COMISION2;
	rsPedidos->m_FECHPED = m_fechaPedido;
	rsPedidos->m_CENTRO = m_rsProforma.m_CENTRO.Trim();
	rsPedidos->m_SREF = m_rsProforma.m_SREF.Trim();
	rsPedidos->m_ATENCLI = m_rsProforma.m_ATENCLI.Trim();
	rsPedidos->m_TELEF1 = m_rsProforma.m_TELEF1.Trim();
	rsPedidos->m_TELEF2 = m_rsProforma.m_TELEF2.Trim();
	rsPedidos->m_FCOBRO = m_rsProforma.m_FCOBRO.Trim();
	rsPedidos->m_NCOBROS = m_rsProforma.m_NCOBROS;
	rsPedidos->m_VTO1 = m_rsProforma.m_VTO1;
	rsPedidos->m_DVTO = m_rsProforma.m_DVTO;
	rsPedidos->m_DIA1 = m_rsProforma.m_DIA1;
	rsPedidos->m_DIA2 = m_rsProforma.m_DIA2;
	rsPedidos->m_DIA3 = m_rsProforma.m_DIA3;
	rsPedidos->m_RETENCOM = m_rsProforma.m_RETENCOM;
	rsPedidos->m_RETENFIS = m_rsProforma.m_RETENFIS;
}


/******************************************************************************************/
HRESULT CDlgAceptaOferta::ObtenerArticulos(CArtiProforma *rsArtiProforma)
{
	HRESULT hErr = S_OK;

	rsArtiProforma->m_strFilter = "NUMPROFOR = " + m_rsProforma.m_NUMPROFOR;
	if (!rsArtiProforma->Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	return hErr;
}

/******************************************************************************************/
void CDlgAceptaOferta::CompruebaArtiDisponible(CArtiProforma *rsArtiProforma)
{
	CInventario rsInventario(m_db);

	rsInventario.m_strFilter = "ARTI LIKE '" + rsArtiProforma->m_ARTI.Trim() + "' AND ALMACEN LIKE '" + m_strAlmacen + "'";
	if (!rsInventario.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si el articulo está en la tabla inventario
	if (rsInventario.m_ARTI.IsEmpty())
		rsInventario.m_UNIDISPONIBLE = 0;

	if (rsInventario.m_UNIDISPONIBLE < rsArtiProforma->m_CANTI)
	{
		m_lArtiNoDisponible.AddTail(rsArtiProforma->m_ARTI.Trim());
		m_lArtiNoDisponible.AddTail(rsArtiProforma->m_DESARTI.Trim());
		CString strCanti;
		strCanti.Format("%.0f", rsArtiProforma->m_CANTI);
		m_lArtiNoDisponible.AddTail(strCanti);
		CString strUniDisponible;
		strUniDisponible.Format("%d", rsInventario.m_UNIDISPONIBLE);
		m_lArtiNoDisponible.AddTail(strUniDisponible);
	}
}

/******************************************************************************************/
void CDlgAceptaOferta::RellenaArtiVenta(CArtiProforma *rsArtiProforma, CArtiVenta *rsArtiVenta)
{	
	rsArtiVenta->m_ARTI  = rsArtiProforma->m_ARTI.Trim();
	rsArtiVenta->m_DESARTI  = rsArtiProforma->m_DESARTI.Trim();
	rsArtiVenta->m_PESO  = rsArtiProforma->m_PESO;
	rsArtiVenta->m_ALQUILER  = rsArtiProforma->m_ALQUILER.Trim();
	rsArtiVenta->m_TIPOALQ  = rsArtiProforma->m_TIPOALQ.Trim();
	rsArtiVenta->m_CANTI  = rsArtiProforma->m_CANTI;
	rsArtiVenta->m_IMPOARTI  = rsArtiProforma->m_IMPOARTI;
	rsArtiVenta->m_DTOARTI  = rsArtiProforma->m_DTOARTI;
	rsArtiVenta->m_IVARTI  = rsArtiProforma->m_IVARTI;
	rsArtiVenta->m_DESARMEMO  = rsArtiProforma->m_DESARMEMO.Trim();
}

/******************************************************************************************/
void CDlgAceptaOferta::LimpiaVentana()
{
	// Se inicializa la fecha de pedido
	m_fechaPedido = CTime::GetCurrentTime();

	// Se inicializa el tipo de acción
	m_iAccion = ACEPTAR;

	//Se inicializa el resto de variables
	m_strNumOferta.Empty();
	m_strEstado.Empty();
	m_strAlmacen.Empty();
	m_strDesAlmacen.Empty();
	m_strMotivo.Empty();
	m_lArtiNoDisponible.RemoveAll();

	GetDlgItem(IDC_STATIC_MOTIVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_MOTIVO)->EnableWindow(FALSE);

	UpdateData(FALSE);

	GetDlgItem(IDC_NUMOFERTA)->SetFocus();
}

/******************************************************************************************/
BOOL CDlgAceptaOferta::BuscaAlmacen()
{
	CCuentas rsCuentas(m_db);
	BOOL bStatus;

	rsCuentas.m_strFilter = "CUENTA LIKE '" + m_strAlmacen + "'";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el almacén no se encuentra salimos reseteando el campo
	if (rsCuentas.m_CUENTA.IsEmpty())
	{
		AfxMessageBox(IDC_ALMACEN_NO_EXISTS);
		bStatus = FALSE;
	}
	else
	{	
		// Se comprueba que realmente sea una cuenta de almacén. Para ello debe empezar
		// por 3 y tener 9 dígitos
		if (m_strAlmacen.Left(1) == '3' && m_strAlmacen.GetLength() == 9)
		{
			m_strDesAlmacen = rsCuentas.m_NOMBRE.Trim();		
			bStatus = TRUE;
		}
		else
		{
			AfxMessageBox(IDC_ALMACEN_NO_VALIDO);
			bStatus = FALSE;
		}
	}
	
	return bStatus;
}

/******************************************************************************************/
void CDlgAceptaOferta::MuestraAviso()
{
	CString strMsg;

	if (m_lArtiNoDisponible.GetCount() == 4)
		strMsg = "No hay disponibilidad del artículo: \n\n";
	else
		strMsg = "No hay disponibilidad de los siguientes artículos: \n\n";

	for (int i=0; i<m_lArtiNoDisponible.GetCount(); i+=4)
	{
		CString strIndex;
		strIndex.Format("%d", (i/4)+1);
		strMsg += strIndex + ". " + m_lArtiNoDisponible.GetAt(m_lArtiNoDisponible.FindIndex(i))
				  + " - " + m_lArtiNoDisponible.GetAt(m_lArtiNoDisponible.FindIndex(i+1))
			      + " => PEDIDOS: " + m_lArtiNoDisponible.GetAt(m_lArtiNoDisponible.FindIndex(i+2))
				  + " / DISPONIBLES: " + m_lArtiNoDisponible.GetAt(m_lArtiNoDisponible.FindIndex(i+3)) + "\n";
	}

	AfxMessageBox(strMsg);
}

/*void CDlgAceptaOferta::OnNMKillfocusFechaPedido(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	*pResult = 0;
}*/
