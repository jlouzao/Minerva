// DlgFactura.cpp: archivo de implementación
/******************************************************************************************/

#include "stdafx.h"
#include "Ventas.h"
#include "DlgFactura.h"
#include ".\dlgfactura.h"
#include "dlgObservaciones.h"
#include "FacturaPedidos.h"
#include "Etiquetas.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgFactura
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgFactura, CDialog)
CDlgFactura::CDlgFactura(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFactura::IDD, pParent)
	, m_strCuenta(_T(""))
	, m_strNombre(_T(""))
	, m_strDireccion(_T(""))
	, m_strNumero(_T(""))
	, m_strCP(_T(""))
	, m_strPoblacion(_T(""))
	, m_strObservaciones(_T(""))
	, m_strTelefono(_T(""))
	, m_strFax(_T(""))
	, m_strTarifa(_T(""))
	, m_dDtos1(0)
	, m_dDtos2(0)
	, m_dDtos3(0)
	, m_dProntoPago(0)
	, m_strGFacturacion(_T(""))
	, m_dRConcedido(0)
	, m_dRActual(0)
	, m_strObra(_T(""))
	, m_strNomObra(_T(""))
	, m_strDireccionObra(_T(""))
	, m_strPoblacionObra(_T(""))
	, m_strCPObra(_T(""))
	, m_strRepre(_T(""))
	, m_strNomRepre(_T(""))
	, m_strSubRepre(_T(""))
	, m_strNomSubRepre(_T(""))
	, m_dComisionRepre(0)
	, m_dComisionSubRepre(0)
	, m_strCentro(_T(""))
	, m_strNomCentro(_T(""))
	, m_timeFecha(CTime::GetCurrentTime())
	, m_strReferencia(_T(""))
	, m_strTotalBruto(_T(""))
	, m_dIVA(0)
	, m_strNumFac(_T(""))
	, m_strTipoFac(_T(""))
{
	m_dTotalBruto = 0;
	m_nCobros = 0;
}

/******************************************************************************************/
CDlgFactura::~CDlgFactura()
{
}

/******************************************************************************************/
void CDlgFactura::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_EDIT_NOMBRE, m_strNombre);
	DDV_MaxChars(pDX, m_strNombre, 35);
	DDX_Text(pDX, IDC_EDIT_DIRECCION, m_strDireccion);
	DDV_MaxChars(pDX, m_strDireccion, 50);
	DDX_Text(pDX, IDC_EDIT_NUMERO, m_strNumero);
	DDX_Text(pDX, IDC_EDIT_CP, m_strCP);
	DDX_Text(pDX, IDC_EDIT_POBLACION, m_strPoblacion);
	DDX_Text(pDX, IDC_EDIT_OBSERVACIONES, m_strObservaciones);
	DDX_Text(pDX, IDC_EDIT_TELEFONO, m_strTelefono);
	DDV_MaxChars(pDX, m_strTelefono, 10);
	DDX_Text(pDX, IDC_EDIT_FAX, m_strFax);
	DDV_MaxChars(pDX, m_strFax, 10);
	DDX_Text(pDX, IDC_EDIT_TARIFA, m_strTarifa);
	DDX_Text(pDX, IDC_EDIT_DESCUENTO1, m_dDtos1);
	DDX_Text(pDX, IDC_EDIT_DESCUENTO2, m_dDtos2);
	DDX_Text(pDX, IDC_EDIT_DESCUENTO3, m_dDtos3);
	DDX_Text(pDX, IDC_EDIT_PRONTOPAGO, m_dProntoPago);
	DDX_Text(pDX, IDC_EDIT_GFACTURACION, m_strGFacturacion);
	DDX_Text(pDX, IDC_EDIT_RCONCEDIDO, m_dRConcedido);
	DDX_Text(pDX, IDC_EDIT_RACTUAL, m_dRActual);
	DDX_Text(pDX, IDC_EDIT_OBRA, m_strObra);
	DDV_MaxChars(pDX, m_strObra, 3);
	DDX_Text(pDX, IDC_EDIT_NOMBREOBRA, m_strNomObra);
	DDX_Text(pDX, IDC_EDIT_DIRECCIONOBRA, m_strDireccionObra);
	DDX_Text(pDX, IDC_EDIT_POBLACIONOBRA, m_strPoblacionObra);
	DDX_Text(pDX, IDC_EDIT_CPOBRA, m_strCPObra);
	DDX_Text(pDX, IDC_EDIT_REPRE, m_strRepre);
	DDV_MaxChars(pDX, m_strRepre, 9);
	DDX_Text(pDX, IDC_EDIT_SUBREPRE, m_strSubRepre);
	DDV_MaxChars(pDX, m_strSubRepre, 9);
	DDX_Text(pDX, IDC_EDIT_NOMREPRE, m_strNomRepre);
	DDX_Text(pDX, IDC_EDIT_COMISIONREPRE, m_dComisionRepre);
	DDX_Text(pDX, IDC_EDIT_NOMSUBREPRE, m_strNomSubRepre);
	DDX_Text(pDX, IDC_EDIT_COMISIONSUBREPRE, m_dComisionSubRepre);
	DDX_Text(pDX, IDC_EDIT_CENTRO, m_strCentro);
	DDV_MaxChars(pDX, m_strCentro, 3);
	DDX_Text(pDX, IDC_EDIT_NOMBRECENTRO, m_strNomCentro);
	DDX_DateTimeCtrl(pDX, IDC_FECHA, m_timeFecha);
	DDX_Text(pDX, IDC_EDIT_REFERENCIA, m_strReferencia);
	DDV_MaxChars(pDX, m_strReferencia, 50);
	DDX_Control(pDX, IDC_LIST_ARTICULOS, m_lstArticulos);
	DDX_Text(pDX, IDC_EDIT_TOTAL_BRUTO, m_strTotalBruto);
	DDX_Text(pDX, IDC_EDIT_TOTAL_NETO, m_strTotalNeto);
	DDX_Control(pDX, IDC_EDIT_CUENTA, m_cCuenta);
	DDX_Control(pDX, IDC_EDIT_OBRA, m_cObra);
	DDX_Control(pDX, IDC_EDIT_REPRE, m_cRepre);
	DDX_Control(pDX, IDC_EDIT_COMISIONREPRE, m_cComisionRepre);
	DDX_Control(pDX, IDC_EDIT_SUBREPRE, m_cSubRepre);
	DDX_Control(pDX, IDC_EDIT_COMISIONSUBREPRE, m_cComisionSubRepre);
	DDX_Control(pDX, IDC_EDIT_CENTRO, m_cCentro);
	DDX_Control(pDX, IDC_EDIT_REFERENCIA, m_cReferencia);
	DDX_Control(pDX, IDC_EDIT_DESCUENTO1, m_cDtos1);
	DDX_Control(pDX, IDC_EDIT_PRONTOPAGO, m_cProntoPago);
	DDX_Text(pDX, IDC_EDIT_IVA, m_dIVA);
	DDX_Control(pDX, IDC_EDIT_IVA, m_cIVA);
	DDX_Text(pDX, IDC_EDIT_NUMFAC, m_strNumFac);
	DDV_MaxChars(pDX, m_strNumFac, 10);
	DDX_Control(pDX, IDC_CMB_PEDIDOS, m_cmbPedidos);
	DDX_Text(pDX, IDC_EDIT1, m_strTipoFac);
	DDX_Text(pDX, IDC_EDIT_PEDIDO, m_strPedido);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgFactura, CDialog)
	ON_BN_CLICKED(ID_BUSCAR, OnBnClickedBuscar)
	ON_EN_KILLFOCUS(IDC_EDIT_NUMFAC, OnEnKillfocusEditNumfac)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA, OnEnKillfocusEditCuenta)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_EN_KILLFOCUS(IDC_EDIT_OBRA, OnEnKillfocusEditObra)
	ON_BN_CLICKED(IDC_BTN_OBRA, OnBnClickedBtnObra)
	ON_EN_KILLFOCUS(IDC_EDIT_REPRE, OnEnKillfocusEditRepre)
	ON_BN_CLICKED(IDC_BTN_CUENTAREPRE, OnBnClickedBtnCuentarepre)
	ON_EN_KILLFOCUS(IDC_EDIT_SUBREPRE, OnEnKillfocusEditSubrepre)
	ON_BN_CLICKED(IDC_BTN_CUENTASUBREPRE, OnBnClickedBtnCuentasubrepre)
	ON_EN_KILLFOCUS(IDC_EDIT_CENTRO, OnEnKillfocusEditCentro)
	ON_BN_CLICKED(IDC_BTN_CENTRO, OnBnClickedBtnCentro)
	ON_EN_KILLFOCUS(IDC_EDIT_DESCUENTO1, OnEnKillfocusEditDescuento1)
	ON_EN_KILLFOCUS(IDC_EDIT_PRONTOPAGO, OnEnKillfocusEditProntopago)
	ON_EN_KILLFOCUS(IDC_EDIT_IVA, OnEnKillfocusEditIva)
	ON_EN_KILLFOCUS(IDC_EDIT_COMISIONREPRE, OnEnKillfocusEditComisionrepre)
	ON_EN_KILLFOCUS(IDC_EDIT_COMISIONSUBREPRE, OnEnKillfocusEditComisionsubrepre)
	ON_BN_CLICKED(ID_DATOS_COBRO, OnBnClickedDatosCobro)
	ON_BN_CLICKED(ID_OBSERVACIONES, OnBnClickedObservaciones)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ARTICULOS, OnNMSetfocusListArticulos)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_CBN_SELCHANGE(IDC_CMB_PEDIDOS, OnCbnSelchangeCmbPedidos)
	ON_BN_CLICKED(ID_OK, OnBnClickedOk)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgFactura
/******************************************************************************************/

/******************************************************************************************/
BOOL CDlgFactura::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece el estilo	
	m_lstArticulos.SetGridLines(TRUE);

	// Añadiendo la lista de imágenes se consigue hacer cada casilla más grande
	CImageList m_ImageList;
	m_ImageList.Create(1, 17, ILC_COLOR,1,1); 
	m_lstArticulos.SetImageList(&m_ImageList); 

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 105);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 198);
	m_lstArticulos.InsertColumn(2,"Tipo", LVCFMT_LEFT, 75);
	m_lstArticulos.InsertColumn(3,"Tipo Alquiler", LVCFMT_LEFT, 75);
	m_lstArticulos.InsertColumn(4,"Fecha Inicio", LVCFMT_LEFT, 80);
	m_lstArticulos.InsertColumn(5,"Fecha Fin", LVCFMT_LEFT, 80);
	m_lstArticulos.InsertColumn(6,"Nº dias", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(7,"Cantidad", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(8,"Tarifa", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(9,"Dto", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(10,"IVA", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(11,"Descripción detallada", LVCFMT_LEFT, 200);

	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaFacturas.SetConexion(m_db);
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaObras.SetConexion(m_db);
	m_dlgBusquedaCentros.SetConexion(m_db);
	m_dlgBusquedaCuentas.SetConexion(m_db);

	// Se inicializa los array para saber los Tipo de Venta y Alquiler
	m_strTipo.AddTail("S"); m_strTipo.AddTail(ALQUILER);
	m_strTipo.AddTail("V"); m_strTipo.AddTail(VENTA);
	m_strTipo.AddTail("N"); m_strTipo.AddTail(OTROS);
	m_strTipo.AddTail("E"); m_strTipo.AddTail(ENTREGA);
	m_strTipo.AddTail("R"); m_strTipo.AddTail(RECOGIDA);

	m_strTipoAlquiler.AddTail("M"); m_strTipoAlquiler.AddTail(MENSUAL);
	m_strTipoAlquiler.AddTail("D"); m_strTipoAlquiler.AddTail(DIA_LABORABLE);
	m_strTipoAlquiler.AddTail("N"); m_strTipoAlquiler.AddTail(DIA_NATURAL);

	// Se inicializan las listas
	m_lOldCantidad.RemoveAll();
	m_lOldTarifa.RemoveAll();
	m_lOldDto.RemoveAll();

	SoloLectura(TRUE);

	return TRUE;
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditNumfac()
{
	CString strNumFacOld = m_strNumFac;

	GetDlgItem(IDC_EDIT_NUMFAC)->GetWindowText(m_strNumFac);

	if (m_strNumFac == strNumFacOld)
		return;

	if (!m_strNumFac.IsEmpty())
	{
		LimpiaVentana();

		if (!BuscaFactura())
		{
			AfxMessageBox(IDC_FACTURA_NO_EXISTS);
			m_strNumFac = strNumFacOld;
			GetDlgItem(IDC_EDIT_NUMFAC)->SetWindowText(m_strNumFac);
		}
	}
	else
		LimpiaVentana(TRUE);
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedBuscar()
{
	INT_PTR status;

	m_dlgBusquedaFacturas.SetTipo(CDialogBusqueda::FACTURAS);
	status = m_dlgBusquedaFacturas.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana(TRUE);

		m_strNumFac = m_dlgBusquedaFacturas.GetCodigo();

		/* Busca la factura y la muestra */
		if (!m_strNumFac.IsEmpty())
			BuscaFactura();
	}
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditCuenta()
{
	CString strCuentaOld = m_strCuenta;

	GetDlgItem(IDC_EDIT_CUENTA)->GetWindowText(m_strCuenta);

	if (m_strCuenta == strCuentaOld)
		return;

	if (!m_strCuenta.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaDatosPersonalesCliente())
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCuenta = strCuentaOld;
			GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
		}
	}
	else
		LimpiaCliente();
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedBtnCuenta()
{
		INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCuenta = m_dlgBusquedaClientes.GetCodigo();

		/* Busca el artículo y lo escribe en el listCtrl */
		if (!m_strCuenta.IsEmpty())
			BuscaDatosPersonalesCliente();
	}
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditObra()
{
	if (m_strCuenta.IsEmpty())
	{
		AfxMessageBox(IDC_NO_CLIENTE);
		m_strObra.Empty();
		GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
		return;
	}

	CString strObraOld = m_strObra;

	GetDlgItem(IDC_EDIT_OBRA)->GetWindowText(m_strObra);

	if (m_strObra == strObraOld)
		return;

	if (!m_strObra.IsEmpty())
	{
		// Si la Obra no existe se deja la anterior y se da un mensaje de error
		if (!BuscaObra())
		{
			AfxMessageBox(IDC_OBRA_NO_EXISTS);
			m_strObra = strObraOld;
			GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
		}
	}
	else
		LimpiaObra();
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedBtnObra()
{
	INT_PTR status;

	if (m_strCuenta.IsEmpty())
	{
		AfxMessageBox(IDC_NO_CLIENTE);
		return;
	}
	m_dlgBusquedaObras.SetTipo(CDialogBusqueda::DIRENV);
	m_dlgBusquedaObras.SetCliente(m_strCuenta);
	status = m_dlgBusquedaObras.DoModal();
	if (status == IDOK)
	{
		m_strObra = m_dlgBusquedaObras.GetCodigo();

		/* Busca la obra y se escribe en el listCtrl */
		if (!m_strObra.IsEmpty())
			BuscaObra();
	}
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditRepre()
{
	CString strRepreOld = m_strRepre;

	GetDlgItem(IDC_EDIT_REPRE)->GetWindowText(m_strRepre);

	if (!m_strRepre.IsEmpty())
	{
		// Si el Representante no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCuenta(m_strRepre, m_strNomRepre))
		{
			AfxMessageBox(IDC_CUENTA_NO_EXISTS);
			m_strRepre = strRepreOld;
			GetDlgItem(IDC_EDIT_REPRE)->SetWindowText(m_strRepre);
		}
		else
		{
			GetDlgItem(IDC_EDIT_REPRE)->SetWindowText(m_strRepre);
			GetDlgItem(IDC_EDIT_NOMREPRE)->SetWindowText(m_strNomRepre);
		}
	}
	else
	{
		m_strNomRepre.Empty();
		GetDlgItem(IDC_EDIT_NOMREPRE)->SetWindowText(m_strNomRepre);
	}
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedBtnCuentarepre()
{
	INT_PTR status;

	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	status = m_dlgBusquedaCuentas.DoModal();
	if (status == IDOK)
	{
		m_strRepre = m_dlgBusquedaCuentas.GetCodigo();
		m_strNomRepre = m_dlgBusquedaCuentas.GetDescripcion();
	}

	GetDlgItem(IDC_EDIT_REPRE)->SetWindowText(m_strRepre);
	GetDlgItem(IDC_EDIT_NOMREPRE)->SetWindowText(m_strNomRepre);
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditSubrepre()
{
	CString strSubRepreOld = m_strSubRepre;

	GetDlgItem(IDC_EDIT_SUBREPRE)->GetWindowText(m_strSubRepre);

	if (!m_strSubRepre.IsEmpty())
	{
		// Si el Surpresentante no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCuenta(m_strSubRepre, m_strNomSubRepre))
		{
			AfxMessageBox(IDC_CUENTA_NO_EXISTS);
			m_strSubRepre = strSubRepreOld;
			GetDlgItem(IDC_EDIT_SUBREPRE)->SetWindowText(m_strSubRepre);
		}
		else
		{
			GetDlgItem(IDC_EDIT_SUBREPRE)->SetWindowText(m_strSubRepre);
			GetDlgItem(IDC_EDIT_NOMSUBREPRE)->SetWindowText(m_strNomSubRepre);
		}
	}
	else
	{
		m_strNomSubRepre.Empty();
		GetDlgItem(IDC_EDIT_NOMSUBREPRE)->SetWindowText(m_strNomSubRepre);
	}
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedBtnCuentasubrepre()
{
	INT_PTR status;

	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	status = m_dlgBusquedaCuentas.DoModal();
	if (status == IDOK)
	{
		m_strSubRepre = m_dlgBusquedaCuentas.GetCodigo();
		m_strNomSubRepre = m_dlgBusquedaCuentas.GetDescripcion();
	}

	GetDlgItem(IDC_EDIT_SUBREPRE)->SetWindowText(m_strSubRepre);
	GetDlgItem(IDC_EDIT_NOMSUBREPRE)->SetWindowText(m_strNomSubRepre);
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditCentro()
{
	CString strCentroOld = m_strCentro;

	GetDlgItem(IDC_EDIT_CENTRO)->GetWindowText(m_strCentro);

	if (!m_strCentro.IsEmpty())
	{
		// Si el Centro no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCentro())
		{
			AfxMessageBox(IDC_CENTRO_NO_EXISTS);
			m_strCentro = strCentroOld;
			GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
		}
	}
	else
		LimpiaCentro();
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedBtnCentro()
{
	INT_PTR status;

	m_dlgBusquedaCentros.SetTipo(CDialogBusqueda::CENTROS);
	status = m_dlgBusquedaCentros.DoModal();
	if (status == IDOK)
	{
		m_strCentro = m_dlgBusquedaCentros.GetCodigo();
		m_strNomCentro = m_dlgBusquedaCentros.GetDescripcion();
	}

	GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_EDIT_NOMBRECENTRO)->SetWindowText(m_strNomCentro);
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditDescuento1()
{
	CString strDescuento1Aux;

	GetDlgItem(IDC_EDIT_DESCUENTO1)->GetWindowText(strDescuento1Aux);
	if (!CompruebaNumero(strDescuento1Aux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		CString strDtos1;
		strDtos1.Format("%g", m_dDtos1);
		GetDlgItem(IDC_EDIT_DESCUENTO1)->SetWindowText(strDtos1);
		m_cDtos1.SetFocus();
		return;
	}
	else
	{
		m_dDtos1 = atof(strDescuento1Aux);
		m_rsFactura.m_DCTOS = m_dDtos1;
		CalculaPrecioNeto();
	}
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditProntopago()
{
	CString strProntoPagoAux;

	GetDlgItem(IDC_EDIT_PRONTOPAGO)->GetWindowText(strProntoPagoAux);
	if (!CompruebaNumero(strProntoPagoAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		CString strPP;
		strPP.Format("%g", m_dProntoPago);
		GetDlgItem(IDC_EDIT_PRONTOPAGO)->SetWindowText(strPP);
		m_cProntoPago.SetFocus();
		return;
	}
	else
	{
		m_dProntoPago = atof(strProntoPagoAux);
		m_rsFactura.m_PP = m_dProntoPago;
		CalculaPrecioNeto();
	}
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditIva()
{
	CString strIVAAux;

	GetDlgItem(IDC_EDIT_IVA)->GetWindowText(strIVAAux);
	if (!CompruebaNumero(strIVAAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		CString strIVA;
		strIVA.Format("%g", m_dIVA);
		GetDlgItem(IDC_EDIT_IVA)->SetWindowText(strIVA);
		m_cIVA.SetFocus();
		return;
	}
	else
	{
		m_dIVA = atof(strIVAAux);
		m_rsFactura.m_IVA = m_dIVA;
		CalculaPrecioNeto();
	}
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditComisionrepre()
{
	CString strComisionAux;
	CString strComision;
	
	strComision.Format("%g", m_dComisionRepre);

	GetDlgItem(IDC_EDIT_COMISIONREPRE)->GetWindowText(strComisionAux);
	if (!CompruebaNumero(strComisionAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		GetDlgItem(IDC_EDIT_COMISIONREPRE)->SetWindowText(strComision);
		GetDlgItem(IDC_EDIT_COMISIONREPRE)->SetFocus();
		return;
	}
	else
		m_dComisionRepre = atof(strComisionAux);
}

/******************************************************************************************/
void CDlgFactura::OnEnKillfocusEditComisionsubrepre()
{
	CString strComisionAux;
	CString strComision;
	
	strComision.Format("%g", m_dComisionSubRepre);

	GetDlgItem(IDC_EDIT_COMISIONSUBREPRE)->GetWindowText(strComisionAux);
	if (!CompruebaNumero(strComisionAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		GetDlgItem(IDC_EDIT_COMISIONSUBREPRE)->SetWindowText(strComision);
		GetDlgItem(IDC_EDIT_COMISIONSUBREPRE)->SetFocus();
		return;
	}
	else
		m_dComisionSubRepre = atof(strComisionAux);
}

/************************************************************************************************************/
/** Comprueba que en la cadena no hay mas que números y como mucho un punto                                **/    
/************************************************************************************************************/
BOOL CDlgFactura::CompruebaNumero(CString strNumero)
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

/******************************************************************************************/
void CDlgFactura::OnBnClickedDatosCobro()
{
	CDlgDatosCobro dlgDatosCobro;
	dlgDatosCobro.SetConexion(m_db);
	dlgDatosCobro.SetDatosCobro(&m_datosCobro);
	dlgDatosCobro.DoModal();

	// Si ha cambiado la retención fiscal se recalcula el precio neto
	if (m_datosCobro.m_RETENFIS != m_rsFactura.m_RETENFIS)
	{
		m_rsFactura.m_RETENFIS = m_datosCobro.m_RETENFIS;
		CalculaPrecioNeto();
	}
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedObservaciones()
{
	CDlgObservaciones dlgObservaciones;
	dlgObservaciones.SetConexion(m_db);
	dlgObservaciones.SetObsCliente(m_strObservaciones);

	dlgObservaciones.SetTitulo("Factura");
	dlgObservaciones.SetObservaciones(m_rsFactura.m_OBSFAC.Trim());
	dlgObservaciones.DoModal();

	m_rsFactura.m_OBSFAC = dlgObservaciones.GetObservaciones();
}

/******************************************************************************************/
void CDlgFactura::OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_lstArticulos.m_ptEditting.y == 11)
		m_lstArticulos.GetEditControl()->SetLimitText(255);

	*pResult = 0;
}

/******************************************************************************************/
LRESULT CDlgFactura::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr  = 0;

	if ( (m_lstArticulos.m_ptEditting.y >= 0 && m_lstArticulos.m_ptEditting.y <= 3)
		 || m_lstArticulos.m_ptEditting.y == 6)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	else if (m_lstArticulos.m_ptEditting.y == 4 || m_lstArticulos.m_ptEditting.y == 5)
	{
		//if (m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 2) != "Alquiler")
		//{
			//m_lstArticulos.GetDateTimeControl()->EnableWindow(FALSE);
			//m_lstArticulos.EndDateTimeCtrl();
		//}
		/*else
			m_lstArticulos.GetDateTimeControl()->EnableWindow(TRUE);*/
	}
	else if (m_lstArticulos.m_ptEditting.y != -1)
		m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);

	// Si se cambia la cantidad de artículos se debe recalcular el peso y el precio total
	if (m_lstArticulos.m_ptEditting.y == 7)
			CambiaCantidad();

	// Si se cambia la fecha de inicio o de fin de alquiler se debe recalcular el 
	// número total de días alquilado y por lo tanto el precio total
	else if (m_lstArticulos.m_ptEditting.y == 4 || m_lstArticulos.m_ptEditting.y == 5)
	{
		// Si no es de alquiler no hay que hacer nada
		if (m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 2) != "Alquiler")
			m_lstArticulos.SetItemTextCB(m_lstArticulos.m_ptEditting.x, m_lstArticulos.m_ptEditting.y, "");
		else
			CambiaFecha();
	}
	
	// Si se cambia la tarifa de un artículo se debe recalcular el precio total
	else if (m_lstArticulos.m_ptEditting.y == 8)
		CambiaTarifa();

	// Si se cambia el descuento de un artículo se debe recalcular el precio total
	else if (m_lstArticulos.m_ptEditting.y == 9)
		CambiaDescuento();

	// Se comprueba si el iva es un número
	else if (m_lstArticulos.m_ptEditting.y == 10)
		CompruebaIva();

	return hErr;
}

/******************************************************************************************/
void CDlgFactura::OnCbnSelchangeCmbPedidos()
{
	BuscaArticulosFactura();
}

/******************************************************************************************/
void CDlgFactura::OnBnClickedOk()
{
	m_lstArticulos.EndItem();

	GuardaFactura();
}


/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgFactura::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsFactura.m_pDatabase = db;
	m_rsArtiFactura.m_pDatabase = db;
	m_rsCobro.m_pDatabase = db;
}

/******************************************************************************************/
void CDlgFactura::SoloLectura(BOOL bReadOnly)
{
	m_cCuenta.SetReadOnly(bReadOnly);
	m_cDtos1.SetReadOnly(bReadOnly);
	m_cProntoPago.SetReadOnly(bReadOnly);
	m_cIVA.SetReadOnly(bReadOnly);
	m_cObra.SetReadOnly(bReadOnly);
	m_cRepre.SetReadOnly(bReadOnly);
	m_cSubRepre.SetReadOnly(bReadOnly);
	m_cComisionRepre.SetReadOnly(bReadOnly);
	m_cComisionSubRepre.SetReadOnly(bReadOnly);
	m_cCentro.SetReadOnly(bReadOnly);
	m_cReferencia.SetReadOnly(bReadOnly);

	GetDlgItem(IDC_FECHA)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_BTN_CUENTA)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_BTN_CUENTAREPRE)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_BTN_CUENTASUBREPRE)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_BTN_CENTRO)->EnableWindow(!bReadOnly);

	GetDlgItem(ID_DATOS_COBRO)->EnableWindow(!bReadOnly);
	GetDlgItem(ID_OBSERVACIONES)->EnableWindow(!bReadOnly);
	GetDlgItem(ID_OK)->EnableWindow(!bReadOnly);
}

/******************************************************************************************/
BOOL CDlgFactura::BuscaFactura()
{
	BOOL bExists = FALSE;

	SoloLectura(FALSE);

	m_rsFactura.m_strFilter = "NUMFAC LIKE '" + m_strNumFac + "'";
	if (!m_rsFactura.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la factura existe se rellenan sus campos 
	if (!m_rsFactura.m_NUMFAC.IsEmpty())
	{
		m_strCuenta = m_rsFactura.m_CUENTA.Trim();
		m_strTelefono = m_rsFactura.m_TELEF1.Trim();
		m_strFax = m_rsFactura.m_TELEF2.Trim();
		m_strTarifa = m_rsFactura.m_TARIFA.Trim();
		m_dDtos1 = m_rsFactura.m_DCTOS;
		m_dProntoPago =  m_rsFactura.m_PP;
		m_dIVA =  m_rsFactura.m_IVA;
		m_strGFacturacion = m_rsFactura.m_GRUFAC.Trim();
		m_strRepre = m_rsFactura.m_REPRE.Trim();
		m_strSubRepre = m_rsFactura.m_SUBREP.Trim();
		m_strObra = m_rsFactura.m_DIRENV.Trim();
		m_dComisionRepre = m_rsFactura.m_COMISION;
		m_dComisionSubRepre = m_rsFactura.m_COMISION2;
		m_strCentro = m_rsFactura.m_CENTRO.Trim();
		m_strReferencia = m_rsFactura.m_SREF.Trim();

		m_datosCobro.m_FCOBRO = m_rsFactura.m_FCOBRO.Trim();
		m_datosCobro.m_NCOBROS = m_rsFactura.m_NCOBROS;
		m_nCobros = (int)m_rsFactura.m_NCOBROS;
		m_datosCobro.m_VTO1 = m_rsFactura.m_VTO1;
		m_datosCobro.m_DVTO = m_rsFactura.m_DVTO;
		m_datosCobro.m_DIA1 = m_rsFactura.m_DIA1;
		m_datosCobro.m_DIA2 = m_rsFactura.m_DIA2;
		m_datosCobro.m_DIA3 = m_rsFactura.m_DIA3;
		m_datosCobro.m_RETENFIS = m_rsFactura.m_RETENFIS;

		m_timeFecha = m_rsFactura.m_FECHFAC;

		// Se busca la descripción del Representante y Subrepresentante
		if (!m_strRepre.IsEmpty() || !m_strSubRepre.IsEmpty())
			BuscaDescripcionCuenta();

		// Si tiene una obra asignada se buscan sus datos
		if (!m_strObra.IsEmpty())
			BuscaObra();

		// Si tiene una centro asignado se buscan sus datos
		if (!m_strCentro.IsEmpty())
			BuscaCentro();

		// Se buscan los datos del cliente
		BuscaDatosPersonalesCliente();

		// Se escribe el tipo de factura y el/los pedido/s que se facturan
		if (m_rsFactura.m_TIPO == POR_CONTRATO)
		{
			m_strTipoFac = TEXT_POR_CONTRATO;

			GetDlgItem(IDC_CMB_PEDIDOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_PEDIDO)->ShowWindow(SW_SHOW);

			m_strPedido = m_rsFactura.m_NUMPEDIDO.Trim();
		}
		else if (m_rsFactura.m_TIPO == POR_OBRA)
		{
			m_strTipoFac = TEXT_POR_OBRA;

			GetDlgItem(IDC_CMB_PEDIDOS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_PEDIDO)->ShowWindow(SW_HIDE);

			// Se obtienen los diferentes pedidos
			CArtiFactura artiFactura(m_db);
		
			//artiFactura.m_strFilter = "NUMFAC LIKE '" + m_strNumFac + "'";
			CString strSQL = "SELECT DISTINCT NUMPED FROM ARTIFACTURA WHERE NUMFAC LIKE '" + m_strNumFac + "'";
			if (!artiFactura.Open(CRecordset::dynaset, strSQL))
			{
				AfxMessageBox(IDC_ERROR_BD);
				return FALSE;
			}

			m_cmbPedidos.ResetContent();
			while (!artiFactura.IsEOF())
			{
				m_cmbPedidos.AddString(artiFactura.m_NUMPED.Trim());
				artiFactura.MoveNext();
			}

			if (m_cmbPedidos.GetCount() > 0)
				m_cmbPedidos.SetCurSel(0);

			artiFactura.Close();
		}

		// Se insertan los artículos que tuviera la factura
		BuscaArticulosFactura();

		bExists = TRUE;
	}

	m_rsFactura.Close();

	// Si la factura existe se busca el cobro/s correspondiente/s para también modificarlo/s
	if (bExists)
	{
		m_rsCobro.m_strFilter = "NUMFAC LIKE '" + m_strNumFac + "'";
		if (!m_rsCobro.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return FALSE;
		}	
		//m_rsCobro.Close();
	}

	UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
void CDlgFactura::LimpiaVentana(BOOL bLimpiaNumFac)
{
	if (bLimpiaNumFac)
		m_strNumFac.Empty();

	m_strTipoFac.Empty();
	m_strPedido.Empty();
	m_cmbPedidos.ResetContent();
	m_strCuenta.Empty();
	m_strNombre.Empty();
	m_strDireccion.Empty();
	m_strNumero.Empty();
	m_strCP.Empty();
	m_strPoblacion.Empty();
	m_strObservaciones.Empty();
	m_strTelefono.Empty();
	m_strFax.Empty();
	m_strTarifa.Empty();
	m_dDtos1 = 0;
	m_dDtos2 = 0;
	m_dDtos3 = 0;
	m_dProntoPago = 0;
	m_dIVA = 0;
	m_strGFacturacion.Empty();
	m_dRConcedido = 0;
	m_dRActual = 0;
	m_strObra.Empty();
	m_strNomObra.Empty();
	m_strDireccionObra.Empty();
	m_strPoblacionObra.Empty();
	m_strCPObra.Empty();
	m_strRepre.Empty();
	m_strNomRepre.Empty();
	m_strSubRepre.Empty();
	m_strNomSubRepre.Empty();
	m_dComisionRepre = 0;
	m_dComisionSubRepre = 0;
	m_strCentro.Empty();
	m_strNomCentro.Empty();
	m_timeFecha = CTime::GetCurrentTime();
	m_strReferencia.Empty();
	m_strTotalBruto.Empty();
	m_strTotalNeto.Empty();
	
	// Se limpian tambien los datos de cobro
	m_datosCobro.m_FCOBRO.Empty();
	m_datosCobro.m_NCOBROS = 0;
	m_nCobros = 0;
	m_datosCobro.m_VTO1 = 0;
	m_datosCobro.m_DVTO = 0;
	m_datosCobro.m_DIA1 = 0;
	m_datosCobro.m_DIA2 = 0;
	m_datosCobro.m_DIA3 = 0;
	m_datosCobro.m_RETENFIS = 0;

	m_lstArticulos.DeleteAllItems();

	// Se limpian los campos de la factura
	m_rsFactura.m_NUMFAC.Empty();
	m_rsFactura.m_CUENTA.Empty();
	m_rsFactura.m_TARIFA.Empty();
	m_rsFactura.m_DCTOS = 0;
	m_rsFactura.m_DCTOS2 = 0;
	m_rsFactura.m_DCTOS3 = 0;
	m_rsFactura.m_PP = 0;
	m_rsFactura.m_GRUFAC.Empty();
	m_rsFactura.m_DIRENV.Empty();
	m_rsFactura.m_REPRE.Empty();
	m_rsFactura.m_SUBREP.Empty();
	m_rsFactura.m_COMISION = 0;
	m_rsFactura.m_COMISION2 = 0;
	m_rsFactura.m_FECHFAC = NULL;
	m_rsFactura.m_CENTRO.Empty();
	m_rsFactura.m_SREF.Empty();
	m_rsFactura.m_TELEF1.Empty();
	m_rsFactura.m_TELEF2.Empty();
	m_rsFactura.m_FCOBRO.Empty();
	m_rsFactura.m_NCOBROS = 0;
	m_rsFactura.m_VTO1 = 0;
	m_rsFactura.m_DVTO = 0;
	m_rsFactura.m_DIA1 = 0;
	m_rsFactura.m_DIA2 = 0;
	m_rsFactura.m_DIA3 = 0;
	m_rsFactura.m_RETENCOM = 0;
	m_rsFactura.m_RETENFIS = 0;
	m_rsFactura.m_OBSFAC.Empty();

	if (m_rsArtiFactura.IsOpen())
		m_rsArtiFactura.Close();

	// Se inicializan las listas
	m_lOldCantidad.RemoveAll();
	m_lOldTarifa.RemoveAll();
	m_lOldDto.RemoveAll();

	m_dlgBusquedaObras.InicializarListas();

	UpdateData(FALSE);

	GetDlgItem(ID_DATOS_COBRO)->EnableWindow(FALSE);
	GetDlgItem(ID_OBSERVACIONES)->EnableWindow(FALSE);
	GetDlgItem(ID_OK)->EnableWindow(FALSE);
}

/******************************************************************************************/
void CDlgFactura::BuscaDescripcionCuenta()
{
	CCuentas rsCuentas(m_db);

	rsCuentas.m_strFilter = "CUENTA LIKE '" + m_strRepre + "' OR CUENTA LIKE '" + m_strSubRepre + "'";

	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	while (!rsCuentas.IsEOF())
	{
		if (rsCuentas.m_CUENTA.Trim() == m_strRepre)
			m_strNomRepre = rsCuentas.m_NOMBRE.Trim();
		if (rsCuentas.m_CUENTA.Trim() == m_strSubRepre)
			m_strNomSubRepre = rsCuentas.m_NOMBRE.Trim();

		rsCuentas.MoveNext();
	}

	rsCuentas.Close();
}

/******************************************************************************************/
BOOL CDlgFactura::BuscaObra()
{
	BOOL bExists = FALSE;
	CDirEnv rsDirEnv(m_db);

	rsDirEnv.m_strFilter = "CLIENTE LIKE '" + m_strCuenta + "' AND DIRENV = '" + m_strObra + "'";
	if (!rsDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la obra existe se rellenan sus campos 
	if (!rsDirEnv.m_CLIENTE.IsEmpty())
	{
		//m_rsProforma.m_DIRENV.Trim() = rsDirEnv.m_DIRENV.Trim();
		m_strNomObra = rsDirEnv.m_NOMDIRENV.Trim();
		m_strDireccionObra = rsDirEnv.m_DDIRENV.Trim();
		m_strPoblacionObra = rsDirEnv.m_POBL.Trim();
		m_strCPObra = rsDirEnv.m_CP.Trim();

		bExists = TRUE;
	}

	rsDirEnv.Close();

	GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
	GetDlgItem(IDC_EDIT_NOMBREOBRA)->SetWindowText(m_strNomObra);
	GetDlgItem(IDC_EDIT_DIRECCIONOBRA)->SetWindowText(m_strDireccionObra);
	GetDlgItem(IDC_EDIT_POBLACIONOBRA)->SetWindowText(m_strPoblacionObra);
	GetDlgItem(IDC_EDIT_CPOBRA)->SetWindowText(m_strCPObra);
	//UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
void CDlgFactura::LimpiaObra()
{
	m_strObra.Empty();
	m_strNomObra.Empty();
	m_strDireccionObra.Empty();
	m_strPoblacionObra.Empty();
	m_strCPObra.Empty();

	GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
	GetDlgItem(IDC_EDIT_NOMBREOBRA)->SetWindowText(m_strNomObra);
	GetDlgItem(IDC_EDIT_DIRECCIONOBRA)->SetWindowText(m_strDireccionObra);
	GetDlgItem(IDC_EDIT_POBLACIONOBRA)->SetWindowText(m_strPoblacionObra);
	GetDlgItem(IDC_EDIT_CPOBRA)->SetWindowText(m_strCPObra);
}

/******************************************************************************************/
BOOL CDlgFactura::BuscaCentro()
{
	BOOL bExists = FALSE;
	CCentros rsCentros(m_db);

	rsCentros.m_strFilter = "CCENTRO LIKE '" + m_strCentro + "'";
	if (!rsCentros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el centro existe se rellena la descripción 
	if (!rsCentros.m_CCENTRO.IsEmpty())
	{
		m_strNomCentro = /*m_rsProforma.m_CENTRO.Trim() =*/ rsCentros.m_DCENTRO.Trim();
		bExists = TRUE;
	}

	rsCentros.Close();

	GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_EDIT_NOMBRECENTRO)->SetWindowText(m_strNomCentro);

	return bExists;
}

/******************************************************************************************/
void CDlgFactura::LimpiaCentro()
{
	m_strCentro.Empty();
	m_strNomCentro.Empty();

	GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_EDIT_NOMBRECENTRO)->SetWindowText(m_strNomCentro);

}

/******************************************************************************************/
BOOL CDlgFactura::BuscaDatosPersonalesCliente()
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
		m_strNombre = rsClientes.m_NOMBRE.Trim();
		m_strDireccion = rsClientes.m_DIRECCION.Trim();
		m_strNumero = rsClientes.m_NUMERO.Trim();
		m_strCP = rsClientes.m_CP.Trim();
		m_strPoblacion = rsClientes.m_POBLACION.Trim();
		m_strObservaciones = rsClientes.m_OBSER1.Trim();
		m_dRConcedido = rsClientes.m_ERIESCLI;
		m_dRActual = rsClientes.m_ERIACCLI;

		GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
		GetDlgItem(IDC_EDIT_NOMBRE)->SetWindowText(m_strNombre);
		GetDlgItem(IDC_EDIT_DIRECCION)->SetWindowText(m_strDireccion);
		GetDlgItem(IDC_EDIT_NUMERO)->SetWindowText(m_strNumero);
		GetDlgItem(IDC_EDIT_CP)->SetWindowText(m_strCP);
		GetDlgItem(IDC_EDIT_POBLACION)->SetWindowText(m_strPoblacion);
		GetDlgItem(IDC_EDIT_OBSERVACIONES)->SetWindowText(m_strObservaciones);
		CString strRConcedido, strRActual;
		strRConcedido.Format("%g", m_dRConcedido);
		GetDlgItem(IDC_EDIT_RCONCEDIDO)->SetWindowText(strRConcedido);
		strRActual.Format("%g", m_dRActual);
		GetDlgItem(IDC_EDIT_RACTUAL)->SetWindowText(strRActual);

		m_dlgBusquedaObras.InicializarListas();

		bExists = TRUE;
	}

	rsClientes.Close();

	return bExists;
}

/******************************************************************************************/
void CDlgFactura::LimpiaCliente()
{
	m_strNombre.Empty();
	m_strDireccion.Empty();
	m_strNumero.Empty();
	m_strCP.Empty();
	m_strPoblacion.Empty();
	m_strObservaciones.Empty();
	m_dRConcedido = 0;
	m_dRActual = 0;

	GetDlgItem(IDC_EDIT_NOMBRE)->SetWindowText(m_strNombre);
	GetDlgItem(IDC_EDIT_DIRECCION)->SetWindowText(m_strDireccion);
	GetDlgItem(IDC_EDIT_NUMERO)->SetWindowText(m_strNumero);
	GetDlgItem(IDC_EDIT_CP)->SetWindowText(m_strCP);
	GetDlgItem(IDC_EDIT_POBLACION)->SetWindowText(m_strPoblacion);
	GetDlgItem(IDC_EDIT_OBSERVACIONES)->SetWindowText(m_strObservaciones);
	CString strRConcedido, strRActual;
	strRConcedido.Format("%g", m_dRConcedido);
	GetDlgItem(IDC_EDIT_RCONCEDIDO)->SetWindowText(strRConcedido);
	strRActual.Format("%g", m_dRActual);
	GetDlgItem(IDC_EDIT_RACTUAL)->SetWindowText(strRActual);

}

/******************************************************************************************/
void CDlgFactura::BuscaArticulosFactura()
{
	BOOL bExists = FALSE;
	CString strPedido;

	if (m_rsFactura.m_TIPO == POR_CONTRATO)
		strPedido = m_strPedido;
	else if (m_rsFactura.m_TIPO == POR_OBRA)
		m_cmbPedidos.GetLBText(m_cmbPedidos.GetCurSel(), strPedido);
	else 
		strPedido.Empty();

	if (m_rsArtiFactura.IsOpen())
		m_rsArtiFactura.Close();

	//m_rsArtiFactura.m_strFilter = "NUMFAC LIKE '" + m_rsFactura.m_NUMFAC.Trim() + "' AND NUMPED LIKE '" + strPedido.Trim() + "'";
	m_rsArtiFactura.m_strFilter = "NUMFAC LIKE '" + m_rsFactura.m_NUMFAC.Trim() + "'";
	m_rsArtiFactura.m_strSort = "ARTI";
	if (!m_rsArtiFactura.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_lstArticulos.DeleteAllItems();

	m_dTotalBruto = 0;
	m_dTotalNeto = 0;
	int iIndice = 0;
	while(!m_rsArtiFactura.IsEOF())
	{
		if (m_rsFactura.m_TIPO == POR_CONTRATO || (m_rsFactura.m_TIPO == POR_OBRA && 
			m_rsArtiFactura.m_NUMPED.Trim() == strPedido.Trim()))
		{
			m_lstArticulos.InsertItem(iIndice, _T(""));
			m_lstArticulos.SetItemText(iIndice, 0, m_rsArtiFactura.m_ARTI.Trim());
			m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);

			m_lstArticulos.SetItemText(iIndice, 1, m_rsArtiFactura.m_DESARTI.Trim());
			m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);

			// Se busca el tipo de venta y de alquiler
			POSITION pos = m_strTipo.Find(m_rsArtiFactura.m_ALQUILER);	
			if (pos != NULL)
			{
				m_strTipo.GetNext(pos);
				m_lstArticulos.SetItemText(iIndice, 2, m_strTipo.GetNext(pos));
			}
			else
				m_lstArticulos.SetItemText(iIndice, 2, "");

			if (m_rsArtiFactura.m_ALQUILER == "S") // Se busca el tipo de alquiler sólo si es tipo Alquiler
			{
				pos = m_strTipoAlquiler.Find(m_rsArtiFactura.m_TIPOALQ);	
				if (pos != NULL)
				{
					m_strTipoAlquiler.GetNext(pos);
					m_lstArticulos.SetItemText(iIndice, 3, m_strTipoAlquiler.GetNext(pos));
				}
				else
					m_lstArticulos.SetItemText(iIndice, 3, "");
			}
			else
				m_lstArticulos.SetItemText(iIndice, 3, "");

			m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);

			if (m_rsArtiFactura.m_FECINIALQ != NULL)
				m_lstArticulos.SetItemText(iIndice, 4, m_rsArtiFactura.m_FECINIALQ.Format("%d/%m/%Y"));
			if (m_rsArtiFactura.m_FECFINALQ != NULL)
				m_lstArticulos.SetItemText(iIndice, 5, m_rsArtiFactura.m_FECFINALQ.Format("%d/%m/%Y"));

			CString strNDias;
			strNDias.Format("%d", m_rsArtiFactura.m_NDIASALQ);
			m_lstArticulos.SetItemText(iIndice, 6, strNDias);
			m_lstArticulos.SetItemBkColor(iIndice, 6, RGB(183, 183, 183), TRUE);

			// Se escribe la cantidad
			CString strCantidad;
			strCantidad.Format("%g", m_rsArtiFactura.m_CANTI);
			m_lstArticulos.SetItemText(iIndice, 7, strCantidad);
			m_lOldCantidad.AddTail((int)m_rsArtiFactura.m_CANTI);

			CString strTarifa;
			strTarifa.Format("%g", m_rsArtiFactura.m_IMPOARTI);
			m_lstArticulos.SetItemText(iIndice, 8, strTarifa);
			m_lOldTarifa.AddTail(m_rsArtiFactura.m_IMPOARTI);

			CString strDto;
			strDto.Format("%g", m_rsArtiFactura.m_DTOARTI);
			m_lstArticulos.SetItemText(iIndice, 9, strDto);
			m_lOldDto.AddTail(m_rsArtiFactura.m_DTOARTI);

			CString strIVA;
			strIVA.Format("%g", m_rsArtiFactura.m_IVARTI);
			m_lstArticulos.SetItemText(iIndice, 10, strIVA);

			m_lstArticulos.SetItemText(iIndice, 11, m_rsArtiFactura.m_DESARMEMO.Trim());

			iIndice ++;
		}

		if (m_rsArtiFactura.m_NDIASALQ > 0)
			m_dTotalBruto +=  m_rsArtiFactura.m_NDIASALQ * m_rsArtiFactura.m_CANTI * m_rsArtiFactura.m_IMPOARTI * (1 - (m_rsArtiFactura.m_DTOARTI / 100));
		else
			m_dTotalBruto +=  m_rsArtiFactura.m_CANTI * m_rsArtiFactura.m_IMPOARTI * (1 - (m_rsArtiFactura.m_DTOARTI / 100));;
		
		m_rsArtiFactura.MoveNext();
	}

	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	CalculaPrecioNeto();

	//rsArtiFactura.Close();
}

/******************************************************************************************/
BOOL CDlgFactura::BuscaCuenta(CString strCuenta, CString &strNomCuenta)
{
	BOOL bExists = FALSE;
	CCuentas rsCuentas(m_db);

	rsCuentas.m_strFilter = "CUENTA LIKE '" + strCuenta + "'";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la cuenta existe se rellena la descripción 
	if (!rsCuentas.m_CUENTA.IsEmpty())
	{
		strNomCuenta = rsCuentas.m_NOMBRE.Trim();
		bExists = TRUE;
	}

	rsCuentas.Close();

	return bExists;
}

/******************************************************************************************/
void CDlgFactura::CambiaCantidad()
{
	// Se comprueba si en la cantidad son todo dígitos
	CString strCantidad ;
	int iCantidad, iOldCantidad, iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	if (len > 0)
	{
		m_lstArticulos.GetEditControl()->GetLine(0, strCantidad.GetBuffer(len), len);
		strCantidad.ReleaseBuffer(len);
	}

	iOldCantidad = m_lOldCantidad.GetAt(m_lOldCantidad.FindIndex(iFila));

	// Se comprueba si en la cantidad son todo números enteros
	for (int i = 0; i<strCantidad.GetLength(); i++)
	{
		if ((strCantidad.GetAt(i) < '0' || strCantidad.GetAt(i) > '9') && 
			(strCantidad.GetAt(i) == '-' && i != 0)) // El '-' sólo puede estar en la 1ª posición (negativo)
		{
			m_lstArticulos.SetItemText(iFila, 7, iOldCantidad);
			return;
		}
	}

	// Si cantidad no tiene nada se considera 0
	if (strCantidad.IsEmpty())
	{
		iCantidad = 0;
		m_lstArticulos.SetItemText(iFila, 7, iCantidad);
	}
	else
		iCantidad = atoi(strCantidad);

	// Si la cantidad no ha cambiado abandonamos la función
	if (iCantidad == iOldCantidad)
		return;

	// Se recalcula el total bruto
	int iNDiasAlq = atoi(m_lstArticulos.GetItemText(iFila, 6));
	if (iNDiasAlq == 0)
		iNDiasAlq = 1;
	double dTarifa = atof(m_lstArticulos.GetItemText(iFila, 8));
	double dDto = atof(m_lstArticulos.GetItemText(iFila, 9));

	// Primero se debe restar el peso que suponía con la cantidad anterior.
	double dPrecioAnterior = iOldCantidad * iNDiasAlq * dTarifa * (1 - (dDto / 100));
	m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio bruto total
	m_dTotalBruto += iCantidad * iNDiasAlq * dTarifa * (1 - (dDto / 100));;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	// Se calcula el precio neto total
	CalculaPrecioNeto();

	m_lOldCantidad.SetAt(m_lOldCantidad.FindIndex(iFila), iCantidad);
}

/******************************************************************************************/
void CDlgFactura::CambiaFecha()
{
	CDateTimeCtrl *dateTimeCtrl;
	CTime fechaIniAlq, fechaFinAlq;
	int iDiasAlquiler, iOldDiasAlquiler;

	int iFila = m_lstArticulos.m_ptEditting.x;

	if ((m_lstArticulos.GetItemText(iFila, 4)).IsEmpty() || (m_lstArticulos.GetItemText(iFila, 5)).IsEmpty())
		return;

	dateTimeCtrl = m_lstArticulos.GetDateTimeControl();

	if (m_lstArticulos.m_ptEditting.y == 4) // Se ha cambiado la fecha inicial
	{
		dateTimeCtrl->GetTime(fechaIniAlq);
		fechaFinAlq = ObtenerFecha(m_lstArticulos.GetItemText(iFila, 5));		
	}
	else if (m_lstArticulos.m_ptEditting.y == 5) // Se ha cambiado la fecha final
	{
		dateTimeCtrl->GetTime(fechaFinAlq);
		fechaIniAlq = ObtenerFecha(m_lstArticulos.GetItemText(iFila, 4));		
	}

	// Se busca el tipo de alquiler
	CString strTipoAlq;
	POSITION pos = m_strTipoAlquiler.Find(m_lstArticulos.GetItemText(iFila, 3));	
	if (pos != NULL)
	{
		m_strTipoAlquiler.GetPrev(pos);
		strTipoAlq = m_strTipoAlquiler.GetPrev(pos);
	}

	CFacturaPedidos facturaPedidos;
	facturaPedidos.SetConexion(m_db);
	iDiasAlquiler = facturaPedidos.CalculaDiasAlquiler(fechaIniAlq, fechaFinAlq, strTipoAlq);
	
	// Se recalcula el PRECIO
	iOldDiasAlquiler = atoi(m_lstArticulos.GetItemText(iFila, 6));
	if (iDiasAlquiler == 0 && fechaIniAlq < fechaFinAlq)
		iDiasAlquiler = 1;
	int iCantidad = atoi(m_lstArticulos.GetItemText(iFila, 7));
	double dTarifa = atof(m_lstArticulos.GetItemText(iFila, 8));
	double dDto = atof(m_lstArticulos.GetItemText(iFila, 9));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior = iCantidad * iOldDiasAlquiler * dTarifa * (1 - (dDto / 100));
	m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio total
	m_dTotalBruto += iCantidad * iDiasAlquiler * dTarifa * (1 - (dDto / 100));

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	// Se calcula el precio neto total
	CalculaPrecioNeto();

	// Se actualiza el número de días de alquiler
	CString strDiasAlquiler;
	strDiasAlquiler.Format("%d", iDiasAlquiler);
	m_lstArticulos.SetItemTextCB(iFila, 6, strDiasAlquiler);
}

/******************************************************************************************/
void CDlgFactura::CambiaTarifa()
{
	CString strTarifa;
	double dTarifa, dOldTarifa;
	int iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	if (len > 0)
	{
		m_lstArticulos.GetEditControl()->GetLine(0, strTarifa.GetBuffer(len), len);
		strTarifa.ReleaseBuffer(len);
	}

	dOldTarifa = m_lOldTarifa.GetAt(m_lOldTarifa.FindIndex(iFila));

	// Se comprueba si en la tarifa son sólo números
	if (!CompruebaNumero(strTarifa))
	{
		m_lstArticulos.SetItemText(iFila, 8, dOldTarifa);
		return;
	}

	// Si cantidad no tiene nada se cosidera 0
	if (strTarifa.IsEmpty())
	{
		dTarifa = 0;
		m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 8, dTarifa);
	}
	else
		dTarifa = atof(strTarifa);

	// Si la tarifa no ha cambiado abandonamos la función
	if (dTarifa == dOldTarifa)
		return;

	// Se recalcula el PRECIO
	int iCantidad = atoi(m_lstArticulos.GetItemText(iFila, 7));
	int iNDiasAlq = atoi(m_lstArticulos.GetItemText(iFila, 6));
	if (iNDiasAlq == 0)
		iNDiasAlq = 1;
	double dDto = atof(m_lstArticulos.GetItemText(iFila, 9));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior = iCantidad * iNDiasAlq * dOldTarifa * (1 - (dDto / 100));
	m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio total
	m_dTotalBruto += iCantidad * iNDiasAlq * dTarifa * (1 - (dDto / 100));;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	// Se calcula el precio neto total
	CalculaPrecioNeto();

	m_lOldTarifa.SetAt(m_lOldTarifa.FindIndex(iFila), dTarifa);
}

/******************************************************************************************/
void CDlgFactura::CambiaDescuento()
{
	CString strDto;
	double dDto, dOldDto;
	int iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	if (len > 0)
	{
		m_lstArticulos.GetEditControl()->GetLine(0, strDto.GetBuffer(len), len);
		strDto.ReleaseBuffer(len);
	}

	dOldDto = m_lOldDto.GetAt(m_lOldDto.FindIndex(iFila));

	// Se comprueba si en la tarifa con sólo números
	if (!CompruebaNumero(strDto))
	{
		m_lstArticulos.SetItemText(iFila, 9, dOldDto);
		return;
	}

	// Si el descuento está vacío se considera 0
	if (strDto.IsEmpty())
	{
		dDto = 0;
		m_lstArticulos.SetItemText(iFila, 9, dDto);
	}
	else
		dDto = atof(strDto);

	// Si el descuento no ha cambiado abandonamos la función
	if (dDto == dOldDto)
		return;

	// Se recalcula el PRECIO
	int iCantidad = atoi(m_lstArticulos.GetItemText(iFila, 7));
	int iNDiasAlq = atoi(m_lstArticulos.GetItemText(iFila, 6));
	if (iNDiasAlq == 0)
		iNDiasAlq = 1;
	double dTarifa = atof(m_lstArticulos.GetItemText(iFila, 8));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior = iCantidad * iNDiasAlq * dTarifa * (1 - dOldDto / 100);
	m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio total
	m_dTotalBruto += iCantidad * iNDiasAlq * dTarifa * (1 - (dDto / 100));;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	// Se calcula el precio neto total
	CalculaPrecioNeto();

	m_lOldDto.SetAt(m_lOldDto.FindIndex(iFila), dDto);
}


/************************************************************************************************************/
void CDlgFactura::CompruebaIva()
{
	// Se comprueba si el IVA son sólo números. Si no se pone el IVA por defecto que es 16
	CString strIVA = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 10);
	if (!CompruebaNumero(strIVA))
	{
		m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 10, "16");
		return;
	}
}

/******************************************************************************************/
void CDlgFactura::CalculaPrecioNeto()
{
	double dDtoComercial, dProntoPago, dRetFiscal, dIVA;
	dDtoComercial = (m_dTotalBruto * m_rsFactura.m_DCTOS) / 100;
	dProntoPago = (m_dTotalBruto * m_rsFactura.m_PP) / 100;
	dRetFiscal = (m_dTotalBruto * m_rsFactura.m_RETENFIS) / 100;
	dIVA = (m_dTotalBruto * m_rsFactura.m_IVA) / 100;
	m_dTotalNeto = m_dTotalBruto - dDtoComercial - dProntoPago - dRetFiscal + dIVA;
	
	m_strTotalNeto.Format("%.2f", m_dTotalNeto);
	GetDlgItem(IDC_EDIT_TOTAL_NETO)->SetWindowText(m_strTotalNeto);
}

/******************************************************************************************/
CTime CDlgFactura::ObtenerFecha(CString strFecha)
{
	int iDay = atoi(strFecha.Left(2));
	int iMes = atoi(strFecha.Mid(3, 2));
	int iAgno = atoi(strFecha.Right(4));
	CTime date(iAgno, iMes, iDay, 0, 0, 0);

	return (date);
}


/******************************************************************************************/
void CDlgFactura::GuardaFactura()
{
	HRESULT hErr = S_OK;

	//CArtiFactura rsArtiFactura(m_db);

	// Se rellenan los campos de la Factura con lo que contienen los editbox
	RellenaFactura();

	if (!m_db->BeginTrans())
		return;

	hErr = m_rsFactura.UpdateFactura();

	// Se actualizan los artículos de la factura
	if (hErr == S_OK)
	{	
		if (m_rsArtiFactura.IsOpen())
		{
			CString strPedido;
			if (m_rsFactura.m_TIPO == POR_CONTRATO)
				strPedido = m_strPedido;
			else if (m_rsFactura.m_TIPO == POR_OBRA)
				m_cmbPedidos.GetLBText(m_cmbPedidos.GetCurSel(), strPedido);

			m_rsArtiFactura.MoveFirst();
			int iIndex = 0;

			while (!m_rsArtiFactura.IsEOF() && hErr == S_OK)
			{
				if (m_rsArtiFactura.m_NUMPED.Trim() == strPedido.Trim())
				{
					if (!m_lstArticulos.GetItemText(iIndex, 4).IsEmpty())
						m_rsArtiFactura.m_FECINIALQ = ObtenerFecha(m_lstArticulos.GetItemText(iIndex, 4));
					else
						m_rsArtiFactura.m_FECINIALQ = NULL;

					if (!m_lstArticulos.GetItemText(iIndex, 5).IsEmpty())
						m_rsArtiFactura.m_FECFINALQ = ObtenerFecha(m_lstArticulos.GetItemText(iIndex, 5));
					else
						m_rsArtiFactura.m_FECFINALQ = NULL;

					m_rsArtiFactura.m_NDIASALQ = atoi(m_lstArticulos.GetItemText(iIndex, 6));
					m_rsArtiFactura.m_CANTI = atoi(m_lstArticulos.GetItemText(iIndex, 7));
					m_rsArtiFactura.m_IMPOARTI = atof(m_lstArticulos.GetItemText(iIndex, 8));
					m_rsArtiFactura.m_DTOARTI = atof(m_lstArticulos.GetItemText(iIndex, 9));
					m_rsArtiFactura.m_IVARTI = atof(m_lstArticulos.GetItemText(iIndex, 10));
					m_rsArtiFactura.m_DESARMEMO = m_lstArticulos.GetItemText(iIndex, 11);

					hErr = m_rsArtiFactura.UpdateArtiFactura();

					iIndex++;
				}

				m_rsArtiFactura.MoveNext();
			}

			m_rsArtiFactura.Close();
		}
	}

	// Si todo ha ido bien también se modifica el cobro/s asociado/s
	if (hErr == S_OK)
		hErr = ModificaCobros();

	if (hErr == S_OK)
		m_db->CommitTrans();
	else
		m_db->Rollback();

	LimpiaVentana(TRUE);
}

/*******************************************************************************************************/
void CDlgFactura::RellenaFactura()
{
	UpdateData();

	m_rsFactura.m_CUENTA = m_strCuenta.Trim();
	m_rsFactura.m_TELEF1 = m_strTelefono.Trim();
	m_rsFactura.m_TELEF2 = m_strFax.Trim();
	m_rsFactura.m_TARIFA = m_strTarifa.Trim();
	m_rsFactura.m_DCTOS = m_dDtos1;
	m_rsFactura.m_PP = m_dProntoPago;
	m_rsFactura.m_IVA = m_dIVA;
	m_rsFactura.m_GRUFAC = m_strGFacturacion.Trim();
	m_rsFactura.m_DIRENV = m_strObra.Trim();
	m_rsFactura.m_REPRE = m_strRepre.Trim();
	m_rsFactura.m_SUBREP = m_strSubRepre.Trim();
	m_rsFactura.m_COMISION = m_dComisionRepre;
	m_rsFactura.m_COMISION2 = m_dComisionSubRepre;
	m_rsFactura.m_FECHFAC = m_timeFecha;
	m_rsFactura.m_CENTRO = m_strCentro.Trim();
	m_rsFactura.m_SREF = m_strReferencia.Trim();

	m_rsFactura.m_FCOBRO =	m_datosCobro.m_FCOBRO.Trim();
	m_rsFactura.m_NCOBROS = m_datosCobro.m_NCOBROS;
	m_rsFactura.m_VTO1 = m_datosCobro.m_VTO1;
	m_rsFactura.m_DVTO = m_datosCobro.m_DVTO;
	m_rsFactura.m_DIA1 = m_datosCobro.m_DIA1;
	m_rsFactura.m_DIA2 = m_datosCobro.m_DIA2;
	m_rsFactura.m_DIA3 = m_datosCobro.m_DIA3;
	m_rsFactura.m_RETENFIS = m_datosCobro.m_RETENFIS;
}

/*******************************************************************************************************/
HRESULT CDlgFactura::ModificaCobros()
{
	HRESULT hErr = S_OK;

	// Si el nº de cobros no ha cambiado, se actualizan los cobros. Si cambia se
	// eliminan los cobros que hubiera y se insertan los nuevos
	if (m_nCobros == m_rsFactura.m_NCOBROS)
	{
		BOOL bPrimero = TRUE;
		CTime fechaOld;
		while (!m_rsCobro.IsEOF() && hErr == S_OK)
		{
			m_rsCobro.m_FCOBRO = m_rsFactura.m_FCOBRO.Trim();
			m_rsCobro.m_CUENTA = m_rsFactura.m_CUENTA.Trim();
			m_rsCobro.m_FECHLIBRA = m_rsFactura.m_FECHFAC;
			m_rsCobro.m_CENTRO = m_rsFactura.m_CENTRO.Trim();

			if (bPrimero)
			{
				bPrimero = FALSE;
				CTimeSpan diasVTO1((LONG)m_rsFactura.m_VTO1, 0, 0, 0);
				m_rsCobro.m_FECHA = m_rsFactura.m_FECHFAC + diasVTO1;
			}
			else
			{
				CTimeSpan diasDVTO((LONG)m_rsFactura.m_DVTO, 0, 0, 0);
				m_rsCobro.m_FECHA = fechaOld + diasDVTO;
			}

			fechaOld = m_rsCobro.m_FECHA;

			m_rsCobro.m_EUROS = m_dTotalNeto / m_rsFactura.m_NCOBROS;
			hErr = m_rsCobro.UpdateCobros();

			m_rsCobro.MoveNext();
		}

		m_rsCobro.Close();
	}

	else
	{
		m_rsCobro.Close();

		// Se eliminan los cobros que ya tuviera la factura
		hErr = m_rsCobro.DeleteCobros();

		// Se generan nuevos cobros
		if (hErr == S_OK)
		{
			CFacturaPedidos facturaPedidos;
			facturaPedidos.SetConexion(m_db);
			hErr = facturaPedidos.GuardaCobros(&m_rsFactura, m_dTotalNeto);
		}
	}

	return hErr;
}
