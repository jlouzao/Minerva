// DlgGestionVentas.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgGestionVentas.h"
#include "BD.h"
#include "DlgObservaciones.h"
#include "DlgBuscaVenta.h"
#include "DlgDatosAlbaran.h"
#include ".\dlggestionventas.h"
#include "Etiquetas.h"
#include "FacturaPedidos.h"
#include "DlgOpcionesFac.h"

#define TITULO_OFERTAS     "Gestión de ofertas"
#define TITULO_PEDIDOS     "Gestión de pedidos"
#define TITULO_ALBARANES   "Gestión de albaranes"

/***********************************************************************************************/
// Cuadro de diálogo de CDlgOfertas
/***********************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgGestionVentas, CDialog)
CDlgGestionVentas::CDlgGestionVentas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGestionVentas::IDD, pParent)
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
	, m_timeFecha2(NULL)
	, m_strReferencia(_T(""))
	, m_strAtencion(_T(""))
	, m_strTotalBruto(_T(""))
	, m_strTotalPeso(_T(""))
	, m_iTipoNacional(0)
	, m_strEstado(_T(""))
	, m_strAlmacen(_T(""))
	, m_strDesAlmacen(_T(""))
	, m_bEmitir1(FALSE)
	, m_bEmitir2(FALSE)
	, m_dIVA(16)
	, m_bEmitir3(FALSE)
//	, m_bMovAlmacen(FALSE)
	, m_iTipoPedido(0)
{
	m_iNumArti = 0;
	m_dTotalPeso = 0;
	m_dTotalBruto = 0;
	m_bReadOnly = FALSE;
	m_bNuevo = TRUE;
}

/***********************************************************************************************/
CDlgGestionVentas::~CDlgGestionVentas()
{
}

/***********************************************************************************************/
void CDlgGestionVentas::DoDataExchange(CDataExchange* pDX)
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
	DDX_DateTimeCtrl(pDX, IDC_FECHA2, m_timeFecha2);
	DDX_Text(pDX, IDC_EDIT_REFERENCIA, m_strReferencia);
	DDV_MaxChars(pDX, m_strReferencia, 50);
	DDX_Text(pDX, IDC_EDIT_ATN, m_strAtencion);
	DDV_MaxChars(pDX, m_strAtencion, 35);
	DDX_Control(pDX, IDC_LIST_ARTICULOS, m_lstArticulos);
	DDX_Text(pDX, IDC_EDIT_TOTAL_BRUTO, m_strTotalBruto);
	DDX_Text(pDX, IDC_EDIT_TOTAL_PESO, m_strTotalPeso);
	DDX_Radio(pDX, IDC_RB_NACIONAL, m_iTipoNacional);
	DDX_Text(pDX, IDC_EDIT_ESTADO, m_strEstado);
	DDX_Control(pDX, IDC_EDIT_TELEFONO, m_cTelefono);
	DDX_Control(pDX, IDC_EDIT_FAX, m_cFax);
	DDX_Control(pDX, IDC_EDIT_CUENTA, m_cCuenta);
	DDX_Control(pDX, IDC_EDIT_OBRA, m_cObra);
	DDX_Control(pDX, IDC_EDIT_REPRE, m_cRepre);
	DDX_Control(pDX, IDC_EDIT_COMISIONREPRE, m_cComisionRepre);
	DDX_Control(pDX, IDC_EDIT_SUBREPRE, m_cSubRepre);
	DDX_Control(pDX, IDC_EDIT_COMISIONSUBREPRE, m_cComisionSubRepre);
	DDX_Control(pDX, IDC_EDIT_CENTRO, m_cCentro);
	DDX_Control(pDX, IDC_EDIT_REFERENCIA, m_cReferencia);
	DDX_Control(pDX, IDC_EDIT_ATN, m_cAtn);
	DDX_Text(pDX, IDC_EDIT_ALMACEN, m_strAlmacen);
	DDV_MaxChars(pDX, m_strAlmacen, 9);
	DDX_Text(pDX, IDC_EDIT_DESALMACEN, m_strDesAlmacen);
	DDX_Check(pDX, IDC_CHECK_EMITIR1, m_bEmitir1);
	DDX_Check(pDX, IDC_CHECK_EMITIR2, m_bEmitir2);
	DDX_Control(pDX, IDC_EDIT_ALMACEN, m_cAlmacen);
	DDX_Control(pDX, IDC_EDIT_DESCUENTO1, m_cDtos1);
	DDX_Control(pDX, IDC_EDIT_PRONTOPAGO, m_cProntoPago);
	DDX_Text(pDX, IDC_EDIT_IVA, m_dIVA);
	DDX_Control(pDX, IDC_EDIT_IVA, m_cIVA);
	DDX_Check(pDX, IDC_CHECK_EMITIR3, m_bEmitir3);
	DDX_Control(pDX, IDC_CHECK_EMITIR2, m_btnEmitir2);
//	DDX_Control(pDX, IDC_CHECK_MOV_ALMACEN, m_btnMovAlmacen);
//	DDX_Check(pDX, IDC_CHECK_MOV_ALMACEN, m_bMovAlmacen);
	DDX_Radio(pDX, IDC_RB_ANDAMIO, m_iTipoPedido);
}

/***********************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgGestionVentas, CDialog)
//	ON_WM_VSCROLL()
//	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_BN_CLICKED(IDC_RB_EXPORTACION, OnBnClickedRbExportacion)
	ON_BN_CLICKED(IDC_RB_NACIONAL, OnBnClickedRbNacional)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA, OnEnKillfocusEditCuenta)
	ON_BN_CLICKED(IDC_BTN_OBRA, OnBnClickedBtnObra)
	ON_EN_KILLFOCUS(IDC_EDIT_OBRA, OnEnKillfocusEditObra)
	ON_BN_CLICKED(IDC_BTN_CENTRO, OnBnClickedBtnCentro)
	ON_EN_KILLFOCUS(IDC_EDIT_CENTRO, OnEnKillfocusEditCentro)
	ON_BN_CLICKED(ID_BUSCAR, OnBnClickedBuscar)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ARTICULOS, OnNMSetfocusListArticulos)
	ON_EN_KILLFOCUS(IDC_EDIT_ATN, OnEnKillfocusEditAtn)
	ON_BN_CLICKED(ID_NUEVO, OnBnClickedNuevo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ARTICULOS, OnNMClickListArticulos)
	ON_BN_CLICKED(ID_ELIMINAR, OnBnClickedEliminar)
	ON_BN_CLICKED(ID_DATOS_COBRO, OnBnClickedDatosCobro)
	ON_BN_CLICKED(ID_OBSERVACIONES, OnBnClickedObservaciones)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_MODIFICAR, OnBnClickedModificar)
	ON_BN_CLICKED(IDC_BTN_CUENTAREPRE, OnBnClickedBtnCuentarepre)
	ON_EN_KILLFOCUS(IDC_EDIT_REPRE, OnEnKillfocusEditRepre)
	ON_BN_CLICKED(IDC_BTN_CUENTASUBREPRE, OnBnClickedBtnCuentasubrepre)
	ON_EN_KILLFOCUS(IDC_EDIT_SUBREPRE, OnEnKillfocusEditSubrepre)
	ON_EN_KILLFOCUS(IDC_EDIT_COMISIONREPRE, OnEnKillfocusEditComisionrepre)
	ON_EN_KILLFOCUS(IDC_EDIT_COMISIONSUBREPRE, OnEnKillfocusEditComisionsubrepre)
	ON_EN_KILLFOCUS(IDC_EDIT_TELEFONO, OnEnKillfocusEditTelefono)
	ON_EN_KILLFOCUS(IDC_EDIT_FAX, OnEnKillfocusEditFax)
	ON_EN_KILLFOCUS(IDC_EDIT_ALMACEN, OnEnKillfocusEditAlmacen)
	ON_BN_CLICKED(IDC_BTN_ALMACEN, OnBnClickedBtnAlmacen)
	ON_BN_CLICKED(IDC_CHECK_EMITIR1, OnBnClickedCheckEmitir1)
	ON_BN_CLICKED(IDC_CHECK_EMITIR2, OnBnClickedCheckEmitir2)
	ON_BN_CLICKED(IDC_CHECK_EMITIR3, OnBnClickedCheckEmitir3)
	ON_EN_SETFOCUS(IDC_EDIT_ATN, OnEnSetfocusEditAtn)
	ON_EN_KILLFOCUS(IDC_EDIT_DESCUENTO1, OnEnKillfocusEditDescuento1)
	ON_EN_KILLFOCUS(IDC_EDIT_PRONTOPAGO, OnEnKillfocusEditProntopago)
	ON_EN_KILLFOCUS(IDC_EDIT_IVA, OnEnKillfocusEditIva)
	ON_BN_CLICKED(IDC_CHECK_MOV_ALMACEN, OnBnClickedCheckMovAlmacen)
	ON_BN_CLICKED(IDC_RB_ANDAMIO, OnBnClickedRbAndamio)
	ON_BN_CLICKED(IDC_RB_MAQUINARIA, OnBnClickedRbMaquinaria)
END_MESSAGE_MAP()

/***********************************************************************************************/
// Controladores de mensajes de CDlgGestionVentas
/***********************************************************************************************/
BOOL CDlgGestionVentas::OnInitDialog()
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
	m_lstArticulos.InsertColumn(6,"Tarifa", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(7,"Dto", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(8,"IVA", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(9,"Descripción detallada", LVCFMT_LEFT, 200);

	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit

	// Se inicializa el primer item todo vacío para permitir escribir en él
	InsertaRegistroVacio();

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaObras.SetConexion(m_db);
	m_dlgBusquedaCentros.SetConexion(m_db);
	m_dlgBusquedaArticulos.SetConexion(m_db);
	m_dlgBusquedaCuentas.SetConexion(m_db);
	m_dlgBusquedaAlmacen.SetConexion(m_db);
	m_dlgBusquedaVentas.SetConexion(m_db);

	// Se inicializa el tipo de oferta
	m_iTipoNacional = NACIONAL;

	m_iTipoPedido = TIPO_ANDAMIO;

	// Se inicializa los array para saber los Tipo de Venta y Alquiler
	m_strTipo.AddTail("S"); m_strTipo.AddTail(ALQUILER);
	m_strTipo.AddTail("V"); m_strTipo.AddTail(VENTA);
	m_strTipo.AddTail("N"); m_strTipo.AddTail(OTROS);
	m_strTipo.AddTail("E"); m_strTipo.AddTail(ENTREGA);
	m_strTipo.AddTail("R"); m_strTipo.AddTail(RECOGIDA);

	m_strTipoAlquiler.AddTail("M"); m_strTipoAlquiler.AddTail(MENSUAL);
	m_strTipoAlquiler.AddTail("D"); m_strTipoAlquiler.AddTail(DIA_LABORABLE);
	m_strTipoAlquiler.AddTail("N"); m_strTipoAlquiler.AddTail(DIA_NATURAL);

	// Se inicializa el array para obtener los diferentes estados
	m_strTiposEstado.AddTail("A"); m_strTiposEstado.AddTail(PENDIENTE);
	m_strTiposEstado.AddTail("E"); m_strTiposEstado.AddTail(ACEPTADA);
	m_strTiposEstado.AddTail("R"); m_strTiposEstado.AddTail(DENEGADA);
	m_strTiposEstado.AddTail("O"); m_strTiposEstado.AddTail(ETIQUETA_FACTURADO);
	m_strTiposEstado.AddTail("P"); m_strTiposEstado.AddTail(ETIQUETA_ALQ_PENDIENTE);
	m_strTiposEstado.AddTail("I"); m_strTiposEstado.AddTail(ETIQUETA_NO_FACTURADO);

	// Se inicializa el flag
	m_bFocusListCtrl = FALSE;
	m_bAtenCli = FALSE;
	m_bTabAtenCli = FALSE;

	m_bAlbaranPed = FALSE;

	// Se inicializa la variable con el título y se activan o desactivan los editbox
	// según el tipo
	if (m_iTipo == OFERTA)
	{
		m_strTitulo = TITULO_OFERTAS;

		// Se habilita el estado y se deshabilita el almacén
		//GetDlgItem(IDC_STATIC_GRUPO)->SetWindowText("Estado oferta");
		//GetDlgItem(IDC_STATIC_ESTADO)->ShowWindow(SW_SHOW);
		//GetDlgItem(IDC_EDIT_ESTADO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_ALMACEN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ALMACEN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_ALMACEN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DESALMACEN)->ShowWindow(SW_HIDE);

		// Se oculta el emitir albarán y se adapta el tamaño del rectángulo del grupo
		GetDlgItem(IDC_CHECK_EMITIR2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_EMITIR3)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CHECK_MOV_ALMACEN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_EMITIR1)->SetWindowText("Emitir oferta");

		CRect rectEmitir1;
		GetDlgItem(IDC_CHECK_EMITIR1)->GetWindowRect(&rectEmitir1);

		CRect rectEmision;
		GetDlgItem(IDC_STATIC_EMISION)->GetWindowRect(&rectEmision);	
		rectEmision.right = rectEmitir1.right + 5;
		ScreenToClient(rectEmision);
		GetDlgItem(IDC_STATIC_EMISION)->MoveWindow(rectEmision);
	}
	else 
	{
		if (m_iTipo == PEDIDO)
		{
			m_strTitulo = TITULO_PEDIDOS;

			GetDlgItem(IDC_STATIC_FECHA2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FECHA2)->ShowWindow(SW_HIDE);
		}
		else if (m_iTipo == ALBARAN)
		{
			m_strTitulo = TITULO_ALBARANES;

			GetDlgItem(IDC_STATIC_FECHA2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_FECHA2)->ShowWindow(SW_SHOW);
			m_timeFecha2 = CTime::GetCurrentTime();

			// Se cambia el nombre de la fecha a fecha entrega y fecha de caducidad
			// a fecha de inicio de alquiler
			GetDlgItem(IDC_STATIC_FECHA1)->SetWindowText("Fecha entrega:");
			GetDlgItem(IDC_STATIC_FECHA2)->SetWindowText("Fecha inicio alquiler:");

			// Se muetra un único Emitir albarán y se adapta el tamaño del rectángulo del grupo
			GetDlgItem(IDC_CHECK_EMITIR2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECK_EMITIR3)->ShowWindow(SW_HIDE);
			//m_bMovAlmacen = TRUE;
			GetDlgItem(IDC_CHECK_EMITIR1)->SetWindowText("Emitir albarán");

			CRect rectEmitir1;
			GetDlgItem(IDC_CHECK_EMITIR1)->GetWindowRect(&rectEmitir1);

			CRect rectEmision;
			GetDlgItem(IDC_STATIC_EMISION)->GetWindowRect(&rectEmision);	
			rectEmision.right = rectEmitir1.right + 5;
			ScreenToClient(rectEmision);
			GetDlgItem(IDC_STATIC_EMISION)->MoveWindow(rectEmision);
		}

		// Se habilita el almacén y se deshabilita el estado
		//GetDlgItem(IDC_STATIC_GRUPO)->SetWindowText("Almacén");
		GetDlgItem(IDC_EDIT_ALMACEN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_ALMACEN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DESALMACEN)->ShowWindow(SW_SHOW);

		//GetDlgItem(IDC_STATIC_ESTADO)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_EDIT_ESTADO)->ShowWindow(SW_HIDE);

		// Se oculta la Fecha de caducidad y se deshabilita el Teléfono y Fax
		//m_cTelefono.SetReadOnly();
		//m_cFax.SetReadOnly();	

		/*CRect rectCliente;
		GetDlgItem(IDC_STATIC_CLIENTE)->GetWindowRect(&rectCliente);
		CRect rectTipo;
		GetDlgItem(IDC_STATIC_TIPO)->GetWindowRect(&rectTipo);	
		rectTipo.right = rectCliente.right;
		ScreenToClient(rectTipo);
		GetDlgItem(IDC_STATIC_TIPO)->MoveWindow(rectTipo);*/
	}

	SetWindowText(m_strTitulo);

	// Se deshabilita el botón de Buscar, Eliminar, Aceptar, Datos Cobro y Observaciones
	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(ID_DATOS_COBRO)->EnableWindow(FALSE);
	GetDlgItem(ID_OBSERVACIONES)->EnableWindow(FALSE);

	m_lCodArtiNoDisponible.RemoveAll();
	m_lIniCantidad.RemoveAll();
	m_lIniTipo.RemoveAll();
	m_lArtiEliminados.RemoveAll();
	m_lOldCantidad.RemoveAll();
	m_lOldTarifa.RemoveAll();
	m_lOldDto.RemoveAll();

	UpdateData(FALSE);

	return TRUE;
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedRbAndamio()
{
	m_iTipoPedido = TIPO_ANDAMIO;
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedRbMaquinaria()
{
	m_iTipoPedido = TIPO_MAQUINARIA;
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedRbNacional()
{
	m_iTipoNacional = NACIONAL;
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedRbExportacion()
{
	m_iTipoNacional = EXPORTACION;
}

/***********************************************************************************************/
void CDlgGestionVentas::OnBnClickedBtnCuenta()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCuenta = m_dlgBusquedaClientes.GetCodigo();

		/* Busca el artículo y lo escribe en el listCtrl */
		if (!m_strCuenta.IsEmpty())
		{
			if (!m_bNuevo) // Si estamos en una oferta/pedido/albarán ya creado sólo ponemos los datos personales
				BuscaDatosPersonalesCliente();
			else
				BuscaCliente();
		}
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditCuenta()
{
	CString strCuentaOld = m_strCuenta;

	GetDlgItem(IDC_EDIT_CUENTA)->GetWindowText(m_strCuenta);

	if (m_strCuenta == strCuentaOld)
		return;

	if (!m_strCuenta.IsEmpty())
	{
		BOOL bExists = FALSE;
		if (!m_bNuevo) // Si estamos en una oferta/pedido/albarán ya creado sólo ponemos los datos personales
			bExists = BuscaDatosPersonalesCliente();
		else
			bExists = BuscaCliente();

		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!bExists)
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCuenta = strCuentaOld;
			GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
		}
	}
	else
		LimpiaVentana();
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedBtnObra()
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
void CDlgGestionVentas::OnEnKillfocusEditObra()
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
void CDlgGestionVentas::OnBnClickedBtnCuentarepre()
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
void CDlgGestionVentas::OnEnKillfocusEditRepre()
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
void CDlgGestionVentas::OnBnClickedBtnCuentasubrepre()
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
void CDlgGestionVentas::OnEnKillfocusEditSubrepre()
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
void CDlgGestionVentas::OnEnKillfocusEditComisionrepre()
{
	CString strComisionAux;
	CString strComision;
	
	strComision.Format("%g", m_dComisionRepre);

	GetDlgItem(IDC_EDIT_COMISIONREPRE)->GetWindowText(strComisionAux);

	if (strComisionAux.IsEmpty())
	{
		m_dComisionRepre = 0;
		GetDlgItem(IDC_EDIT_COMISIONREPRE)->SetWindowText("0");
	}
	else if (!CompruebaNumero(strComisionAux))
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
void CDlgGestionVentas::OnEnKillfocusEditComisionsubrepre()
{
	CString strComisionAux;
	CString strComision;
	
	strComision.Format("%g", m_dComisionSubRepre);

	GetDlgItem(IDC_EDIT_COMISIONSUBREPRE)->GetWindowText(strComisionAux);

	if (strComisionAux.IsEmpty())
	{
		m_dComisionSubRepre = 0;
		GetDlgItem(IDC_EDIT_COMISIONSUBREPRE)->SetWindowText("0");
	}
	else if (!CompruebaNumero(strComisionAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		GetDlgItem(IDC_EDIT_COMISIONSUBREPRE)->SetWindowText(strComision);
		GetDlgItem(IDC_EDIT_COMISIONSUBREPRE)->SetFocus();
		return;
	}
	else
		m_dComisionSubRepre = atof(strComisionAux);
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedBtnCentro()
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
void CDlgGestionVentas::OnEnKillfocusEditCentro()
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
void CDlgGestionVentas::OnBnClickedBuscar()
{
	INT_PTR status;

	if (m_strCuenta.IsEmpty())
	{
		AfxMessageBox(IDC_NO_CLIENTE);
		return;
	}

	if (m_iTipo != OFERTA && m_strAlmacen.IsEmpty())
	{
		AfxMessageBox(IDC_NO_ALMACEN);
		return;
	}


	m_dlgBusquedaArticulos.SetTipo(CDialogBusqueda::ARTICULOS);

	//TRY
	//{
		status = m_dlgBusquedaArticulos.DoModal();
	//}
	/*CATCH (CDBException, exp)
	{
		CString strError;
		exp->GetErrorMessage(strError.GetBuffer(60), 15);
		strError.ReleaseBuffer(60);
	}
	END_CATCH*/

	if (status == IDOK)
	{
		CString strCodArti = m_dlgBusquedaArticulos.GetCodigo();

		/* Busca la obra y se escribe en el listCtrl */
		if (!strCodArti.IsEmpty())
			BuscaArticulo(strCodArti);
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Se comprueba si se ha seleccionado una Cuenta o un Almacén
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

		// Si es un pedido o un albarán se debe seleccionar un almacén obligatoriamente
		if ((m_iTipo == PEDIDO || m_iTipo == ALBARAN) && m_strAlmacen.IsEmpty())
		{
			AfxMessageBox(IDC_NO_ALMACEN);
			m_lstArticulos.EndEdit();
			m_bFocusListCtrl = FALSE;
			return;
		}
	}

	// Si se ha pulsado tabulador y venimos de Atn. al Cliente se activa la primera casilla
	if (((m_iTipo == OFERTA && !m_strCuenta.IsEmpty()) || 
		(m_iTipo != OFERTA && !m_strCuenta.IsEmpty() && !m_strAlmacen.IsEmpty())) &&		
		m_bTabAtenCli)
	{
		m_lstArticulos.EndItem();
		m_lstArticulos.StartEdit(m_iNumArti, 0);						
		m_bAtenCli = FALSE;
		m_bTabAtenCli = FALSE;
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
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y != 3 && m_lstArticulos.m_ptEditting.y != 4)
		m_lstArticulos.GetEditControl()->SetLimitText(255);

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	*pResult = 0;
}

/******************************************************************************************/
LRESULT CDlgGestionVentas::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
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

	// En las columnas que deben estar inactivas se pone el textbox a readonly o si el
	// flag de m_bReadOnly está a TRUE
	if (m_bReadOnly)
	{
		if (m_lstArticulos.m_ptEditting.y == 3 || m_lstArticulos.m_ptEditting.y == 4)
			m_lstArticulos.GetComboControl()->EnableWindow(FALSE);
		else if (m_lstArticulos.m_ptEditting.y != -1) // Para todos los demás
			m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	}
	else if ((m_lstArticulos.m_ptEditting.y == 0 && !strCod.IsEmpty()) || m_lstArticulos.m_ptEditting.y == 1
		 || m_lstArticulos.m_ptEditting.y == 2)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	else if (m_lstArticulos.m_ptEditting.y != -1 && m_lstArticulos.m_ptEditting.y != 3 &&
		     m_lstArticulos.m_ptEditting.y != 4)
			m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);

	// Si se cambia la cantidad de artículos se debe recalcular el peso y el precio total
	if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 5)
		CambiaCantidad();
	
	// Si se cambia la tarifa de un artículo se debe recalcular el precio total
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 6)
		CambiaTarifa();

	// Si se cambia el descuento de un artículo se debe recalcular el precio total
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 7)
		CambiaDescuento();

	// Se comprueba si el iva es un número
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 8)
		CompruebaIva();

	return hErr;
}

/******************************************************************************************/
void CDlgGestionVentas::OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Se deshabilita el botón de Eliminar si hay algún elemento seleccionado
	POSITION pos = m_lstArticulos.GetFirstSelectedItemPosition();
	int iIndex = m_lstArticulos.GetNextSelectedItem(pos);            

	if (m_lstArticulos.GetSelectedCount() > 0 && iIndex != m_lstArticulos.GetItemCount()-1 && !m_bReadOnly)
		GetDlgItem(ID_ELIMINAR)->EnableWindow(TRUE);
	else
		GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	*pResult = 0;
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnSetfocusEditAtn()
{
	//if (m_bFocusListCtrl)
	m_bAtenCli = TRUE;
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditAtn()
{
	//if (m_bFocusListCtrl)
	//	m_bFocusListCtrl = FALSE; 	
}

/******************************************************************************************/
BOOL CDlgGestionVentas::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if  (pMsg->wParam == VK_TAB)
		{
			// Si se ha pulsado el tabulador y venimos de la casilla de atención
			// al cliente, se debe editar la casilla del listCtrl
			if (m_bAtenCli)
				m_bTabAtenCli = TRUE;
		}
	}

	return(CDialog::PreTranslateMessage(pMsg));
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedNuevo()
{
	LimpiaVentana();
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedEliminar()
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

	m_strTotalPeso.Empty();
	m_strTotalPeso.Format("%.3f", m_dTotalPeso);
	GetDlgItem(IDC_EDIT_TOTAL_PESO)->SetWindowText(m_strTotalPeso);

	////////////////////////////////////////////////////////////////////////////////

	// Se resta el PRECIO del total
	double dTarifa = atof(m_lstArticulos.GetItemText(iIndex, 6));
	double dDto = atof(m_lstArticulos.GetItemText(iIndex, 7));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior = iCantidad * dTarifa * (1 - (dDto / 100));
	m_dTotalBruto -= dPrecioAnterior;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	////////////////////////////////////////////////////////////////////////////////

	// Se elimina de la lista de cantidades iniciales
	if (m_iTipo == PEDIDO || m_iTipo == ALBARAN)
	{		
		// Si es un PEDIDO y ya tiene un albarán asociado, se debe incluir en la 
		// lista de artículos eliminados para luego volver a sumar al almacén estas
		// unidades
		if (m_iTipo == PEDIDO && m_bAlbaranPed)
		{
			// Cada Elemento llevará Código del artículo, tipo y cantidad
			int iIniCantidad = m_lIniCantidad.GetAt(m_lIniCantidad.FindIndex(iIndex));
			CString strIniTipo = m_lIniTipo.GetAt(m_lIniTipo.FindIndex(iIndex));
			m_lArtiEliminados.AddTail(m_lstArticulos.GetItemText(iIndex, 0));
			m_lArtiEliminados.AddTail(strIniTipo);
			CString strIniCantidad;
			strIniCantidad.Format("%i", iIniCantidad);
			m_lArtiEliminados.AddTail(strIniCantidad);
		}

		// Si el elemento que vamos a eliminar está en la lista de los elementos no disponibles,
		// se elimina de ella porque ya no hay que tenerlo en cuenta.
		POSITION pos;
		if ((pos = m_lCodArtiNoDisponible.Find(m_lstArticulos.GetItemText(iIndex, 0))) != NULL)
			m_lCodArtiNoDisponible.RemoveAt(pos);

		m_lIniCantidad.RemoveAt(m_lIniCantidad.FindIndex(iIndex));
		m_lIniTipo.RemoveAt(m_lIniTipo.FindIndex(iIndex));
	}

	// Se elimina de las listas de cantidades antiguas
	m_lOldCantidad.RemoveAt(m_lOldCantidad.FindIndex(iIndex));
	m_lOldTarifa.RemoveAt(m_lOldTarifa.FindIndex(iIndex));
	m_lOldDto.RemoveAt(m_lOldDto.FindIndex(iIndex));

	// Se elimina el artículo
	m_lstArticulos.DeleteItem(iIndex);

	m_iNumArti--;

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedDatosCobro()
{
	CDlgDatosCobro dlgDatosCobro;
	dlgDatosCobro.SetConexion(m_db);
	dlgDatosCobro.SetDatosCobro(&m_datosCobro);

	// Si es una oferta denegada o aceptada no se podrá modificar
	//if ((m_iTipo == OFERTA && !m_bNuevo && m_strEstado != PENDIENTE) ||
	//	(m_iTipo == ALBARAN && !m_rsAlbaran.m_NUMPEDIDO.Trim().IsEmpty()))
	if (m_bReadOnly)
		dlgDatosCobro.SetReadOnly();

	dlgDatosCobro.DoModal();
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedObservaciones()
{
	CDlgObservaciones dlgObservaciones;
	dlgObservaciones.SetConexion(m_db);
	dlgObservaciones.SetObsCliente(m_strObservaciones);

	if (m_iTipo == OFERTA)
	{
		// Si es una oferta denegada o aceptada no se podrá modificar
		if (!m_bNuevo && m_strEstado != PENDIENTE)
			dlgObservaciones.SetReadOnly();

		dlgObservaciones.SetTitulo("Oferta");
		dlgObservaciones.SetObservaciones(m_rsProforma.m_OBSPROF.Trim());
	}
	else if (m_iTipo == PEDIDO)
	{
		dlgObservaciones.SetTitulo("Pedido");
		dlgObservaciones.SetObservaciones(m_rsPedido.m_OBSPED.Trim());
	}
	else if (m_iTipo == ALBARAN)
	{
		dlgObservaciones.SetTitulo("Albarán");
		dlgObservaciones.SetObservaciones(m_rsAlbaran.m_OBSALB.Trim());
	}

	dlgObservaciones.DoModal();

	if (m_iTipo == OFERTA)
		m_rsProforma.m_OBSPROF = dlgObservaciones.GetObservaciones();
	else if (m_iTipo == PEDIDO)
		m_rsPedido.m_OBSPED = dlgObservaciones.GetObservaciones();
	else if (m_iTipo == ALBARAN)
		m_rsAlbaran.m_OBSALB = dlgObservaciones.GetObservaciones();
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedCheckEmitir1()
{
	if (m_bEmitir1)
		m_bEmitir1 = FALSE;
	else
		m_bEmitir1 = TRUE;
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedCheckEmitir2()
{
	if (m_bEmitir2)
	{
		m_bEmitir2 = FALSE;
		//m_bMovAlmacen = FALSE; 
		//m_btnMovAlmacen.SetCheck(BST_UNCHECKED);
	}
	else
	{
		m_bEmitir2 = TRUE;
		//m_bMovAlmacen = TRUE; // Al hacer un albarán se marca por defecto mov. de almacén
		//m_btnMovAlmacen.SetCheck(BST_CHECKED);
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedCheckEmitir3()
{
	if (m_bEmitir3)
		m_bEmitir3 = FALSE;
	else
	{
		m_bEmitir3 = TRUE;
		m_bEmitir2 = TRUE; // Siempre que se emita factura se debe emitir antes el albarán
		m_btnEmitir2.SetCheck(BST_CHECKED);
		//m_bMovAlmacen = TRUE; // Al hacer un albarán se marca por defecto mov. de almacén
		//m_btnMovAlmacen.SetCheck(BST_CHECKED);
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedCheckMovAlmacen()
{
	/*if (m_bMovAlmacen)
		m_bMovAlmacen = FALSE;
	else
		m_bMovAlmacen = TRUE;*/
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedOk()
{
	HRESULT hErr = S_OK;

	// Si alguna casilla del CListCtrl se ha quedado editable se quita
	if (m_lstArticulos.m_ptEditting.x != -1)
		m_lstArticulos.EndItem();

	// Se recoge el contenido de todos los campos
	UpdateData();

	// Se inicializará la lista de búsqueda para que incluya los nuevos elementos
	if (m_bNuevo)
		m_dlgBusquedaVentas.InicializarListas();

	if (m_iTipo == OFERTA)
	{
		hErr = GuardaOferta();

		// Se comprueba si hay que emitir la oferta
		if (hErr == S_OK && m_bEmitir1)
		{
			CDlgInformes dlgInformes;
			dlgInformes.SetDatos(m_db, m_iTipo);
			dlgInformes.SetFormula(m_rsProforma.m_NUMPROFOR.Trim(), m_rsProforma.m_NUMPROFOR.Trim());
			dlgInformes.DoModal();
		}

	}
	else if (m_iTipo == PEDIDO)
	{
		// Aseguramos que si se va a hacer una factura, se emita también el albarán.
		if (m_bEmitir3)
			m_bEmitir2 = TRUE;

		hErr = GuardaPedido();

		CString strNumFactura;
		// Se crea la factura
		if (hErr == S_OK && m_bEmitir3)
		{
			// Se llama al diálogo para las opciones de facturación
			CDlgOpcionesFac dlgOpcionesFac;
			dlgOpcionesFac.SetConexion(m_db);
			dlgOpcionesFac.SetFacturacion(FALSE);
			dlgOpcionesFac.DoModal();

			CFacturaPedidos facturaPedidos;
			facturaPedidos.SetConexion(m_db);
			facturaPedidos.SetFinAlq(dlgOpcionesFac.GetFechaFinAlq());
			facturaPedidos.SetTipoFac(CONTRATO);
			facturaPedidos.SetContador(dlgOpcionesFac.GetContador());

			hErr = facturaPedidos.FacturaPedido(&m_rsPedido);

			if (hErr == S_OK)
			{
				// Se guarda el número de factura creada
				strNumFactura = facturaPedidos.GetFacturaIni();

				// Se escribe un mensaje informando del número de pedido, albarán y factura
				CString strMsg;
				strMsg.Format(IDC_PEDIDOALBARANFACTURA, m_rsPedido.m_NUMPEDIDO.Trim(), m_rsAlbaran.m_NUMALB.Trim(), strNumFactura); 
				AfxMessageBox(strMsg);
			}

		}

		if (hErr == S_OK)
		{
			if(m_bEmitir1)
			{
				CDlgInformes dlgInformes;
				dlgInformes.SetDatos(m_db, m_iTipo);
				dlgInformes.SetFormula(m_rsPedido.m_NUMPEDIDO.Trim(), m_rsPedido.m_NUMPEDIDO.Trim());
				dlgInformes.DoModal();
			}

			if (m_bEmitir2)
			{
				CDlgInformes dlgInformes;
				dlgInformes.SetDatos(m_db, ALBARAN);
				dlgInformes.SetFormula(m_rsAlbaran.m_NUMALB.Trim(), m_rsAlbaran.m_NUMALB.Trim());
				dlgInformes.DoModal();
			}

			if (m_bEmitir3)
			{
				CDlgInformes dlgInformes;
				dlgInformes.SetDatos(m_db, FACTURA);
				dlgInformes.SetFormula(strNumFactura, strNumFactura);
				dlgInformes.DoModal();
			}
		}
	}

	else if (m_iTipo == ALBARAN)
	{
		hErr = GuardaAlbaran();

		// Se comprueba si hay que emitir la oferta
		if (hErr == S_OK && m_bEmitir1)
		{
			CDlgInformes dlgInformes;
			dlgInformes.SetDatos(m_db, m_iTipo);
			dlgInformes.SetFormula(m_rsAlbaran.m_NUMALB.Trim(), m_rsAlbaran.m_NUMALB.Trim());
			dlgInformes.DoModal();
		}
	}

	LimpiaVentana();
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditTelefono()
{
	CString strTelefonoOld = m_strTelefono;

	GetDlgItem(IDC_EDIT_TELEFONO)->GetWindowText(m_strTelefono);

	if (!m_strTelefono.IsEmpty() && m_strTelefono.GetLength() > 10)
	{
		AfxMessageBox(IDC_TELEFONO_LARGO);
		m_strTelefono = strTelefonoOld;
		GetDlgItem(IDC_EDIT_TELEFONO)->SetWindowText(m_strTelefono);
		m_cTelefono.SetFocus();
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditFax()
{
	CString strFaxOld = m_strFax;

	GetDlgItem(IDC_EDIT_FAX)->GetWindowText(m_strFax);

	if (!m_strFax.IsEmpty() && m_strFax.GetLength() > 10)
	{
		AfxMessageBox(IDC_TELEFONO_LARGO);
		m_strFax = strFaxOld;
		GetDlgItem(IDC_EDIT_FAX)->SetWindowText(m_strFax);
		m_cFax.SetFocus();
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedModificar()
{
	INT_PTR status;

	CDlgBuscaVenta dlgBuscaVenta;
	dlgBuscaVenta.SetConexion(m_db);
	dlgBuscaVenta.SetTipo(m_iTipo);
	dlgBuscaVenta.SetLista(&m_dlgBusquedaVentas);
	status = dlgBuscaVenta.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana();
		CString strNumVenta = dlgBuscaVenta.GetNumVenta();

		if (m_iTipo == OFERTA)
		{
			if (BuscaOferta(strNumVenta))
			{
				m_bNuevo = FALSE;
				// Se indica en el título de la ventana el número de oferta		
				SetWindowText(m_strTitulo + "  -  " + "Número de Oferta: " + strNumVenta);

				// Si está aceptada o denegada se deben deshabilitar los campos editables ya
				// que no se podrá modificar
				m_bReadOnly = FALSE;
				if (m_strEstado == ACEPTADA || m_strEstado == DENEGADA)
					SoloLectura();			
			}
		}
		else if (m_iTipo == PEDIDO)
		{
			CString strTituloCompleto;

			if (BuscaPedido(strNumVenta))
			{
				m_bNuevo = FALSE;
				// Se indica en el título de la ventana el número de pedido		
				if (!m_bAlbaranPed)
					strTituloCompleto = m_strTitulo + "  -  Número de Pedido: " + strNumVenta;
				else
					strTituloCompleto = m_strTitulo + "  -  Número de Pedido: " + strNumVenta + " / Número de Albarán: " + m_rsPedido.m_NUMALB.Trim();

				m_bReadOnly = FALSE;
				if (m_rsPedido.m_ESTADO != NO_FACTURADO)
				{
					SoloLectura();
					//strTituloCompleto += " / Pedido facturado";					
				}

				SetWindowText(strTituloCompleto);

				// Si el pedido ya tiene asociado un albarán no se podrá cambiar el almacén
				if (m_bAlbaranPed || m_bReadOnly)
				{
					m_cAlmacen.SetReadOnly();
					GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(FALSE);
				}
			}
		}
		else if (m_iTipo == ALBARAN)
		{
			if (BuscaAlbaran(strNumVenta))
			{
				m_bNuevo = FALSE;

				CString strPedido;
				if (!m_rsAlbaran.m_NUMPEDIDO.Trim().IsEmpty())
					strPedido = " / Número de Pedido: " + m_rsAlbaran.m_NUMPEDIDO.Trim();

				// Se indica en el título de la ventana el número de albarán
				if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_ENTREGA)
				{				
					GetDlgItem(IDC_STATIC_FECHA2)->SetWindowText("Fecha inicio alquiler:");

					if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA)
						SetWindowText(m_strTitulo + "  -  " + "Albarán de entrega: " + strNumVenta + strPedido);
					else
						SetWindowText(m_strTitulo + "  -  " + "Albarán despiece de entrega: " + strNumVenta + strPedido);
					
				}
				else if (m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_RECOGIDA)
				{
					// Si es albarán de recogida se pone como fecha fin de alquiler
					GetDlgItem(IDC_STATIC_FECHA2)->SetWindowText("Fecha fin alquiler:");				

					if (m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA)
						SetWindowText(m_strTitulo + "  -  " + "Albarán de recogida: " + strNumVenta + strPedido);
					else
						SetWindowText(m_strTitulo + "  -  " + "Albarán de despiece de recogida: " + strNumVenta + strPedido);
					
				}

				// Si está asociada a un pedido y no es albarán de despiece, 
				// será sólo de lectura
				m_bReadOnly = FALSE;
				m_rsAlbaran.m_NUMPEDIDO = m_rsAlbaran.m_NUMPEDIDO.Trim();
				if (!m_rsAlbaran.m_NUMPEDIDO.Trim().IsEmpty() && (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA ||
					m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA))
					SoloLectura();			
			
				// Si el almacén está relleno se deshabilita
				m_rsAlbaran.m_ALMACEN = m_rsAlbaran.m_ALMACEN.Trim();
				if (!m_rsAlbaran.m_ALMACEN.IsEmpty())
				{
					m_cAlmacen.SetReadOnly();
					GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(FALSE);
				}
			}
		}
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditAlmacen()
{
	CString strOldAlmacen = m_strAlmacen;

	GetDlgItem(IDC_EDIT_ALMACEN)->GetWindowText(m_strAlmacen);

	if (!m_strAlmacen.IsEmpty())
	{
		// Si el almacen no existe se deja el anterior 
		if (!BuscaAlmacen())
		{	
			m_strAlmacen = strOldAlmacen;
			GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strAlmacen);
		}
		else
		{
			GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);

			// Si hubiera ya artículos se comprueba si hay disponibilidad de ellos
			CompruebaDisponibilidadArticulos();
			MuestraAviso();
		}
	}
	else
	{
		m_strDesAlmacen.Empty();

		GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strAlmacen);
		GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);
	}
}

/******************************************************************************************/
void CDlgGestionVentas::OnBnClickedBtnAlmacen()
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

	if (!m_strAlmacen.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_ALMACEN)->SetWindowText(m_strAlmacen);
		GetDlgItem(IDC_EDIT_DESALMACEN)->SetWindowText(m_strDesAlmacen);

		// El botón de buscar se habilita si es un pedido o albarán
		// y también hay cliente
		if (!m_strCuenta.IsEmpty())
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);

		// Si hubiera ya artículos se comprueba si hay disponibilidad de ellos
		CompruebaDisponibilidadArticulos();
		MuestraAviso();
	}

}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditDescuento1()
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
		m_dDtos1 = atof(strDescuento1Aux);
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditProntopago()
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
		m_dProntoPago = atof(strProntoPagoAux);
}

/******************************************************************************************/
void CDlgGestionVentas::OnEnKillfocusEditIva()
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
		m_dIVA = atof(strIVAAux);
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgGestionVentas::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsProforma.m_pDatabase = db;
	m_rsPedido.m_pDatabase = db;
	m_rsAlbaran.m_pDatabase = db;
}

/******************************************************************************************/
void CDlgGestionVentas::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}

/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaCliente()
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
		CString strCuentaAux = m_strCuenta;
		int iTipoPedido = m_iTipoPedido;
		LimpiaVentana();
		m_strCuenta = strCuentaAux;
		m_iTipoPedido = iTipoPedido;

		m_strNomRepre.Empty();
		m_strNomSubRepre.Empty();

		if (m_iTipo == OFERTA)
			m_strEstado = PENDIENTE;
		else if (m_iTipo == PEDIDO || m_iTipo == ALBARAN)
			m_strEstado = ETIQUETA_NO_FACTURADO;

		m_strNombre = rsClientes.m_NOMBRE.Trim();
		m_strDireccion = rsClientes.m_DIRECCION.Trim();
		m_strNumero = rsClientes.m_NUMERO.Trim();
		m_strCP = rsClientes.m_CP.Trim();
		m_strPoblacion = rsClientes.m_POBLACION.Trim();
		m_strObservaciones = rsClientes.m_OBSER1.Trim();
		m_strTelefono = rsClientes.m_TELEFONO.Trim();
		m_strFax = rsClientes.m_FAX.Trim();
		m_strTarifa = rsClientes.m_TARIFA.Trim();
		m_dDtos1 = rsClientes.m_DCTOS2;
		m_dDtos2 = rsClientes.m_DCTOS3;
		m_dDtos3 = rsClientes.m_DCTOS;
		m_dProntoPago = rsClientes.m_PP;
		m_dIVA = 16;
		m_strGFacturacion = rsClientes.m_GRUFAC.Trim();
		m_dRConcedido = rsClientes.m_ERIESCLI;
		m_dRActual = rsClientes.m_ERIACCLI;
		m_strRepre = rsClientes.m_REPRE.Trim();
		m_strSubRepre = rsClientes.m_REPRE2.Trim();
		m_dComisionRepre = rsClientes.m_COMISION;
		m_dComisionSubRepre = rsClientes.m_COMISION2;

		m_datosCobro.m_FCOBRO = rsClientes.m_FCOBRO.Trim();
		m_datosCobro.m_NCOBROS = rsClientes.m_NCOBROS;
		m_datosCobro.m_VTO1 = rsClientes.m_VTO1;
		m_datosCobro.m_DVTO = rsClientes.m_DVTO;
		m_datosCobro.m_DIA1 = rsClientes.m_DIA1;
		m_datosCobro.m_DIA2 = rsClientes.m_DIA2;
		m_datosCobro.m_DIA3 = rsClientes.m_DIA3;
		m_datosCobro.m_RETENFIS = rsClientes.m_PORRETE;

		if (m_iTipo == OFERTA)
			m_timeFecha2 = NULL;

		// Se busca la descripción del Representante y Subrepresentante
		if (!m_strRepre.IsEmpty() || !m_strSubRepre.IsEmpty())
			BuscaDescripcionCuenta();
		
		bExists = TRUE;

		// Se habilita el botón de Aceptar, Datos Cobro y Observaciones
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(ID_DATOS_COBRO)->EnableWindow(TRUE);
		GetDlgItem(ID_OBSERVACIONES)->EnableWindow(TRUE);

		// El botón de buscar se habilita si es oferta y si es un pedido o albarán
		// y también hay almacén
		if (m_iTipo == OFERTA || (m_iTipo != OFERTA && !m_strAlmacen.IsEmpty()))
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);
	}

	rsClientes.Close();

	UpdateData(FALSE);

	return bExists;
	
}

/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaDatosPersonalesCliente()
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
		CString strRConcedido;
		strRConcedido.Format("%g", m_dRConcedido);
		GetDlgItem(IDC_EDIT_RCONCEDIDO)->SetWindowText(strRConcedido);
		CString strRActual;
		strRActual.Format("%g", m_dRActual);
		GetDlgItem(IDC_EDIT_RACTUAL)->SetWindowText(strRActual);
		bExists = TRUE;

		m_dlgBusquedaObras.InicializarListas();
	}

	rsClientes.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaOferta(CString strNumOferta)
{
	BOOL bExists = FALSE;

	//NO// m_rsProforma.m_strFilter = "NUMPROFOR LIKE '" + strNumOferta + "'";
	// Select para que funcione con la tabla de PROFORMA tal y como está ahora, con una 
	// entrada por artículo
	//CString strSQL = "SELECT * FROM PROFORMA WHERE NUMPROFOR = " + strNumOferta + " AND CLAVE = " \
	//	"(SELECT MAX(CLAVE) FROM PROFORMA WHERE NUMPROFOR = " + strNumOferta + ")";
	//if (!m_rsProforma.Open(CRecordset::dynaset, strSQL))

	m_rsProforma.m_strFilter = "NUMPROFOR = " + strNumOferta;
	if (!m_rsProforma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la oferta existe se rellenan sus campos 
	if (!m_rsProforma.m_NUMPROFOR.IsEmpty())
	{
		m_strNomRepre.Empty();
		m_strNomSubRepre.Empty();

		if (m_rsProforma.m_EXPORTA.Trim() == "N")
			m_iTipoNacional = NACIONAL;
		else if (m_rsProforma.m_EXPORTA.Trim() == "S")
			m_iTipoNacional = EXPORTACION;

		if (m_rsProforma.m_TIPO.Trim() == ANDAMIO)
			m_iTipoPedido = TIPO_ANDAMIO;
		else if (m_rsProforma.m_TIPO.Trim() == MAQUINARIA)
			m_iTipoPedido = TIPO_MAQUINARIA;

		// Se busca el estado de la proforma
		POSITION pos = m_strTiposEstado.Find(m_rsProforma.m_ESTADO);	
		if (pos != NULL)
		{
			m_strTiposEstado.GetNext(pos);
			m_strEstado = m_strTiposEstado.GetNext(pos);
		}
		else
			m_strEstado.Empty();

		m_strCuenta = m_rsProforma.m_CUENTA.Trim();
		m_strTelefono = m_rsProforma.m_TELEF1.Trim();
		m_strFax = m_rsProforma.m_TELEF2.Trim();
		m_strTarifa = m_rsProforma.m_TARIFA.Trim();
		m_dDtos1 = m_rsProforma.m_DCTOS;
		m_dDtos2 =  m_rsProforma.m_DCTOS2;
		m_dDtos3 =  m_rsProforma.m_DCTOS3;
		m_dProntoPago =  m_rsProforma.m_PP;
		m_dIVA =  m_rsProforma.m_IVA;
		m_strGFacturacion = m_rsProforma.m_GRUFAC.Trim();
		m_strRepre = m_rsProforma.m_REPRE.Trim();
		m_strSubRepre = m_rsProforma.m_SUBREP.Trim();
		m_strObra = m_rsProforma.m_DIRENV.Trim();
		m_dComisionRepre = m_rsProforma.m_COMISION;
		m_dComisionSubRepre = m_rsProforma.m_COMISION2;
		m_strCentro = m_rsProforma.m_CENTRO.Trim();
		m_strReferencia = m_rsProforma.m_SREF.Trim();
		m_strAtencion = m_rsProforma.m_ATENCLI.Trim();

		m_datosCobro.m_FCOBRO = m_rsProforma.m_FCOBRO.Trim();
		m_datosCobro.m_NCOBROS = m_rsProforma.m_NCOBROS;
		m_datosCobro.m_VTO1 = m_rsProforma.m_VTO1;
		m_datosCobro.m_DVTO = m_rsProforma.m_DVTO;
		m_datosCobro.m_DIA1 = m_rsProforma.m_DIA1;
		m_datosCobro.m_DIA2 = m_rsProforma.m_DIA2;
		m_datosCobro.m_DIA3 = m_rsProforma.m_DIA3;
		m_datosCobro.m_RETENFIS = m_rsProforma.m_RETENFIS;

		m_timeFecha = m_rsProforma.m_FECHPROF;
		m_timeFecha2 = m_rsProforma.m_FECHCADU;

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

		// Se insertan los artículos que tuviera en la oferta
		BuscaArticulosProfor(strNumOferta);

		bExists = TRUE;

		// Se habilita el botón de Buscar, Aceptar, Datos Cobro y Observaciones
		GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);

		GetDlgItem(ID_DATOS_COBRO)->EnableWindow(TRUE);
		GetDlgItem(ID_OBSERVACIONES)->EnableWindow(TRUE);
	}

	m_rsProforma.Close();

	UpdateData(FALSE);

	return bExists;
	
}

/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaPedido(CString strNumPedido)
{
	BOOL bExists = FALSE;

	//NO// m_rsProforma.m_strFilter = "NUMPROFOR LIKE '" + strNumOferta + "'";
	// Select para que funcione con la tabla de PROFORMA tal y como está ahora, con una 
	// entrada por artículo
	//CString strSQL = "SELECT * FROM PROFORMA WHERE NUMPROFOR = " + strNumOferta + " AND CLAVE = " \
	//	"(SELECT MAX(CLAVE) FROM PROFORMA WHERE NUMPROFOR = " + strNumOferta + ")";
	//if (!m_rsProforma.Open(CRecordset::dynaset, strSQL))

	m_rsPedido.m_strFilter = "NUMPEDIDO = " + strNumPedido;
	if (!m_rsPedido.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se rellenan sus campos 
	if (!m_rsPedido.m_NUMPEDIDO.IsEmpty())
	{
		m_strNomRepre.Empty();
		m_strNomSubRepre.Empty();

		if (m_rsPedido.m_TIPO.Trim() == ANDAMIO)
			m_iTipoPedido = TIPO_ANDAMIO;
		else if (m_rsPedido.m_TIPO.Trim() == MAQUINARIA)
			m_iTipoPedido = TIPO_MAQUINARIA;

		if (m_rsPedido.m_EXPORTA.Trim() == "N")
			m_iTipoNacional = NACIONAL;
		else if (m_rsPedido.m_EXPORTA.Trim() == "S")
			m_iTipoNacional = EXPORTACION;

		// Se busca el estado del pedido
		POSITION pos = m_strTiposEstado.Find(m_rsPedido.m_ESTADO);	
		if (pos != NULL)
		{
			m_strTiposEstado.GetNext(pos);
			m_strEstado = m_strTiposEstado.GetNext(pos);
		}
		else
			m_strEstado.Empty();

		m_strCuenta = m_rsPedido.m_CUENTA.Trim();
		m_strAlmacen = m_rsPedido.m_ALMACEN.Trim();
		m_strTelefono = m_rsPedido.m_TELEF1.Trim();
		m_strFax = m_rsPedido.m_TELEF2.Trim();
		m_strTarifa = m_rsPedido.m_TARIFA.Trim();
		m_dDtos1 = m_rsPedido.m_DCTOS;
		m_dDtos2 =  m_rsPedido.m_DCTOS2;
		m_dDtos3 =  m_rsPedido.m_DCTOS3;
		m_dProntoPago =  m_rsPedido.m_PP;
		m_dIVA =  m_rsPedido.m_IVA;
		m_strGFacturacion = m_rsPedido.m_GRUFAC.Trim();
		m_strRepre = m_rsPedido.m_REPRE.Trim();
		m_strSubRepre = m_rsPedido.m_SUBREP.Trim();
		m_strObra = m_rsPedido.m_DIRENV.Trim();
		m_dComisionRepre = m_rsPedido.m_COMISION;
		m_dComisionSubRepre = m_rsPedido.m_COMISION2;
		m_strCentro = m_rsPedido.m_CENTRO.Trim();
		m_strReferencia = m_rsPedido.m_SREF.Trim();
		m_strAtencion = m_rsPedido.m_ATENCLI.Trim();

		m_datosCobro.m_FCOBRO = m_rsPedido.m_FCOBRO.Trim();
		m_datosCobro.m_NCOBROS = m_rsPedido.m_NCOBROS;
		m_datosCobro.m_VTO1 = m_rsPedido.m_VTO1;
		m_datosCobro.m_DVTO = m_rsPedido.m_DVTO;
		m_datosCobro.m_DIA1 = m_rsPedido.m_DIA1;
		m_datosCobro.m_DIA2 = m_rsPedido.m_DIA2;
		m_datosCobro.m_DIA3 = m_rsPedido.m_DIA3;
		m_datosCobro.m_RETENFIS = m_rsPedido.m_RETENFIS;

		m_timeFecha = m_rsPedido.m_FECHPED;

		// Se busca la descripción del almacén si lo hay
		if (!m_strAlmacen.IsEmpty())
			BuscaAlmacen();

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

		// Se insertan los artículos que tuviera el pedido
		BuscaArticulosPedido(strNumPedido);

		bExists = TRUE;

		// Se habilita el botón de Aceptar, Datos Cobro y Observaciones
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(ID_DATOS_COBRO)->EnableWindow(TRUE);
		GetDlgItem(ID_OBSERVACIONES)->EnableWindow(TRUE);

		// El botón de buscar se habilita si existe el cliente y el almacén
		if (!m_strCuenta.IsEmpty() && !m_strAlmacen.IsEmpty())
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);

		// Si el pedido ya tiene un albarán asociado se indica en un flag
		m_rsPedido.m_NUMALB = m_rsPedido.m_NUMALB.Trim();
		if (m_rsPedido.m_NUMALB.IsEmpty())
			m_bAlbaranPed = FALSE;
		else
			m_bAlbaranPed = TRUE;
	}

	m_rsPedido.Close();

	UpdateData(FALSE);

	// Si hubiera ya artículos se comprueba si hay disponibilidad de ellos
	CompruebaDisponibilidadArticulos();
	MuestraAviso();

	return bExists;
	
}

/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaAlbaran(CString strNumAlbaran)
{
	BOOL bExists = FALSE;

	m_rsAlbaran.m_strFilter = "NUMALB = " + strNumAlbaran;
	if (!m_rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el albarán existe se rellenan sus campos 
	if (!m_rsAlbaran.m_NUMALB.IsEmpty())
	{
		m_strNomRepre.Empty();
		m_strNomSubRepre.Empty();

		if (m_rsAlbaran.m_TIPOPED.Trim() == ANDAMIO)
			m_iTipoPedido = TIPO_ANDAMIO;
		else if (m_rsAlbaran.m_TIPOPED.Trim() == MAQUINARIA)
			m_iTipoPedido = TIPO_MAQUINARIA;

		if (m_rsAlbaran.m_EXPORTA.Trim() == "N")
			m_iTipoNacional = NACIONAL;
		else if (m_rsAlbaran.m_EXPORTA.Trim() == "S")
			m_iTipoNacional = EXPORTACION;

		// Se busca el estado del pedido
		POSITION pos = m_strTiposEstado.Find(m_rsAlbaran.m_ESTADO);	
		if (pos != NULL)
		{
			m_strTiposEstado.GetNext(pos);
			m_strEstado = m_strTiposEstado.GetNext(pos);
		}
		else
			m_strEstado.Empty();

		m_strCuenta = m_rsAlbaran.m_CUENTA.Trim();
		m_strAlmacen = m_rsAlbaran.m_ALMACEN.Trim();
		m_strTelefono = m_rsAlbaran.m_TELEF1.Trim();
		m_strFax = m_rsAlbaran.m_TELEF2.Trim();
		m_strTarifa = m_rsAlbaran.m_TARIFA.Trim();
		m_dDtos1 = m_rsAlbaran.m_DCTOS;
		m_dDtos2 =  m_rsAlbaran.m_DCTOS2;
		m_dDtos3 =  m_rsAlbaran.m_DCTOS3;
		m_dProntoPago =  m_rsAlbaran.m_PP;
		m_dIVA =  m_rsAlbaran.m_IVA;
		m_strGFacturacion = m_rsAlbaran.m_GRUFAC.Trim();
		m_strRepre = m_rsAlbaran.m_REPRE.Trim();
		m_strSubRepre = m_rsAlbaran.m_SUBREP.Trim();
		m_strObra = m_rsAlbaran.m_DIRENV.Trim();
		m_dComisionRepre = m_rsAlbaran.m_COMISION;
		m_dComisionSubRepre = m_rsAlbaran.m_COMISION2;
		m_strCentro = m_rsAlbaran.m_CENTRO.Trim();
		m_strReferencia = m_rsAlbaran.m_SREF.Trim();
		m_strAtencion = m_rsAlbaran.m_ATENCLI.Trim();

		m_datosCobro.m_FCOBRO = m_rsAlbaran.m_FCOBRO.Trim();
		m_datosCobro.m_NCOBROS = m_rsAlbaran.m_NCOBROS;
		m_datosCobro.m_VTO1 = m_rsAlbaran.m_VTO1;
		m_datosCobro.m_DVTO = m_rsAlbaran.m_DVTO;
		m_datosCobro.m_DIA1 = m_rsAlbaran.m_DIA1;
		m_datosCobro.m_DIA2 = m_rsAlbaran.m_DIA2;
		m_datosCobro.m_DIA3 = m_rsAlbaran.m_DIA3;
		m_datosCobro.m_RETENFIS = m_rsAlbaran.m_RETENFIS;

		m_timeFecha = m_rsAlbaran.m_FECHALB;

		if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_ENTREGA)
			 m_timeFecha2 = m_rsAlbaran.m_FECINIALQ;
		else if (m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_RECOGIDA)
			 m_timeFecha2 = m_rsAlbaran.m_FECFINALQ;

		// Se busca la descripción del almacén si lo hay
		if (!m_strAlmacen.IsEmpty())
			BuscaAlmacen();

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

		// Se insertan los artículos que tuviera el albarán
		BuscaArticulosAlbaran(strNumAlbaran);

		bExists = TRUE;

		// Se habilita el botón de Aceptar, Datos Cobro y Observaciones
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(ID_DATOS_COBRO)->EnableWindow(TRUE);
		GetDlgItem(ID_OBSERVACIONES)->EnableWindow(TRUE);

		// El botón de buscar se habilita si existe el cliente y el almacén
		if (!m_strCuenta.IsEmpty() && !m_strAlmacen.IsEmpty())
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);
	}

	m_rsAlbaran.Close();

	UpdateData(FALSE);

	// Si hubiera ya artículos se comprueba si hay disponibilidad de ellos
	CompruebaDisponibilidadArticulos();

	return bExists;
	
}

/******************************************************************************************/
void CDlgGestionVentas::BuscaDescripcionCuenta()
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
BOOL CDlgGestionVentas::BuscaAlmacen()
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

		// El botón de buscar se habilita si es oferta y si es un pedido o albarán
		// y también hay cliente
		if (m_iTipo == OFERTA || (m_iTipo != OFERTA && !m_strCuenta.IsEmpty()))
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);
	}
	
	return bStatus;
}

/******************************************************************************************/
void CDlgGestionVentas::LimpiaVentana()
{
	// Si estaba a Read Only se vuelven a inicializar el flag
	if (m_bReadOnly)
	{
		m_bReadOnly = FALSE;
		// Si alguna casilla del CListCtrl se ha quedado editable se quita
		if (m_lstArticulos.m_ptEditting.x != -1)
			m_lstArticulos.EndItem();
	}

	m_strEstado.Empty();
	m_strCuenta.Empty();
	m_strAlmacen.Empty();
	m_strDesAlmacen.Empty();
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
	m_dIVA = 16;
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
	if (m_iTipo == ALBARAN)
		m_timeFecha2 = CTime::GetCurrentTime();
	else
		m_timeFecha2 = NULL;
	m_strReferencia.Empty();
	m_strAtencion.Empty();
	m_strTotalBruto.Empty();
	m_strTotalPeso.Empty();
	
	// Se limpian tambien los datos de cobro
	m_datosCobro.m_FCOBRO.Empty();
	m_datosCobro.m_NCOBROS = 0;
	m_datosCobro.m_VTO1 = 0;
	m_datosCobro.m_DVTO = 0;
	m_datosCobro.m_DIA1 = 0;
	m_datosCobro.m_DIA2 = 0;
	m_datosCobro.m_DIA3 = 0;
	m_datosCobro.m_RETENFIS = 0;

	m_lstArticulos.DeleteAllItems();

	m_iTipoNacional = NACIONAL;

	m_iTipoPedido = TIPO_ANDAMIO;

	m_iNumArti = 0;

	m_bNuevo = TRUE;

	m_lIniCantidad.RemoveAll();
	m_lIniTipo.RemoveAll();
	m_lArtiEliminados.RemoveAll();
	m_lOldCantidad.RemoveAll();
	m_lOldTarifa.RemoveAll();
	m_lOldDto.RemoveAll();
	
	// Se inicializa el primer item todo vacío para permitir escribir en él
	InsertaRegistroVacio();

	// Se indica en el título de la ventana
	SetWindowText(m_strTitulo);

	// Se limpian los recordSet
	if (m_iTipo == OFERTA)
		LimpiaOferta();
	else if (m_iTipo == PEDIDO)
		LimpiaPedido();
	else if (m_iTipo == ALBARAN)
		LimpiaAlbaran();

	m_bAlbaranPed = FALSE;

	m_dlgBusquedaObras.InicializarListas();

	UpdateData(FALSE);

	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	GetDlgItem(ID_DATOS_COBRO)->EnableWindow(FALSE);
	GetDlgItem(ID_OBSERVACIONES)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaObra()
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
void CDlgGestionVentas::LimpiaObra()
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

	//UpdateData(FALSE);
}

/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaCuenta(CString strCuenta, CString &strNomCuenta)
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
		strNomCuenta = /*m_rsProforma.m_REPRE.Trim() =*/ rsCuentas.m_NOMBRE.Trim();
		bExists = TRUE;
	}

	rsCuentas.Close();

	return bExists;
}
/******************************************************************************************/
BOOL CDlgGestionVentas::BuscaCentro()
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

	//UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
void CDlgGestionVentas::LimpiaCentro()
{
	m_strCentro.Empty();
	m_strNomCentro.Empty();

	GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_EDIT_NOMBRECENTRO)->SetWindowText(m_strNomCentro);

	//UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgGestionVentas::BuscaArticulosProfor(CString strNumOferta)
{
	CArtiProforma rsArtiProforma(m_db);

	rsArtiProforma.m_strFilter = "NUMPROFOR LIKE '" + strNumOferta + "'";
	if (!rsArtiProforma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si la Proforma tiene artículos se rellena el listCtrl
	m_dTotalPeso = 0;
	m_dTotalBruto = 0;
	int iIndice = 0;
	while (!rsArtiProforma.IsEOF())
	{
		m_lstArticulos.InsertItem(iIndice, _T(""));
		m_lstArticulos.SetItemText(iIndice, 0, rsArtiProforma.m_ARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);

		m_lstArticulos.SetItemText(iIndice, 1, rsArtiProforma.m_DESARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);

		CString strPeso;
		strPeso.Format("%g", rsArtiProforma.m_PESO);
		m_lstArticulos.SetItemText(iIndice, 2, strPeso);
		m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);

		// Se busca el tipo de venta y de alquiler
		POSITION pos = m_strTipo.Find(rsArtiProforma.m_ALQUILER);	
		if (pos != NULL)
		{
			m_strTipo.GetNext(pos);
			m_lstArticulos.SetItemText(iIndice, 3, m_strTipo.GetNext(pos));
		}
		else
			m_lstArticulos.SetItemText(iIndice, 3, "");

		if (rsArtiProforma.m_ALQUILER == "S") // Se busca el tipo de alquiler sólo si es tipo Alquiler
		{
			pos = m_strTipoAlquiler.Find(rsArtiProforma.m_TIPOALQ);	
			if (pos != NULL)
			{
				m_strTipoAlquiler.GetNext(pos);
				m_lstArticulos.SetItemText(iIndice, 4, m_strTipoAlquiler.GetNext(pos));
			}
			else
				m_lstArticulos.SetItemText(iIndice, 4, "");
		}
		else
			m_lstArticulos.SetItemText(iIndice, 4, "");


		// Se escribe la cantidad
		CString strCantidad;
		strCantidad.Format("%g", rsArtiProforma.m_CANTI);
		m_lstArticulos.SetItemText(iIndice, 5, strCantidad);
		m_lOldCantidad.AddTail((int)rsArtiProforma.m_CANTI);

		CString strTarifa;
		strTarifa.Format("%g", rsArtiProforma.m_IMPOARTI);
		m_lstArticulos.SetItemText(iIndice, 6, strTarifa);
		m_lOldTarifa.AddTail(rsArtiProforma.m_IMPOARTI);

		CString strDto;
		strDto.Format("%g", rsArtiProforma.m_DTOARTI);
		m_lstArticulos.SetItemText(iIndice, 7, strDto);
		m_lOldDto.AddTail(rsArtiProforma.m_DTOARTI);

		m_dTotalPeso += abs(rsArtiProforma.m_CANTI) * rsArtiProforma.m_PESO;
		m_dTotalBruto += rsArtiProforma.m_CANTI * rsArtiProforma.m_IMPOARTI * (1 - (rsArtiProforma.m_DTOARTI / 100));;

		CString strIVA;
		strIVA.Format("%g", rsArtiProforma.m_IVARTI);
		m_lstArticulos.SetItemText(iIndice, 8, strIVA);

		m_lstArticulos.SetItemText(iIndice, 9, rsArtiProforma.m_DESARMEMO.Trim());

		// Si es Aceptada o Denegada se ponen todos los campos a sólo lectura
		if (m_strEstado == ACEPTADA || m_strEstado == DENEGADA)
		{
			m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 4, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 6, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 7, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 8, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 9, RGB(183, 183, 183), TRUE);
		}

		iIndice ++;
		m_iNumArti++;
		rsArtiProforma.MoveNext();
	}

	rsArtiProforma.Close();

	m_strTotalPeso.Empty();
	m_strTotalPeso.Format("%.3f", m_dTotalPeso);

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
}

/******************************************************************************************/
void CDlgGestionVentas::BuscaArticulosPedido(CString strNumPedido)
{
	CArtiVenta rsArtiVenta(m_db);

	rsArtiVenta.m_strFilter = "NUMPEDIDO LIKE '" + strNumPedido + "'";
	if (!rsArtiVenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si el pedido tiene artículos se rellena el listCtrl
	m_dTotalPeso = 0;
	m_dTotalBruto = 0;
	int iIndice = 0;
	while (!rsArtiVenta.IsEOF())
	{
		m_lstArticulos.InsertItem(iIndice, _T(""));
		m_lstArticulos.SetItemText(iIndice, 0, rsArtiVenta.m_ARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);

		m_lstArticulos.SetItemText(iIndice, 1, rsArtiVenta.m_DESARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);

		CString strPeso;
		strPeso.Format("%g", rsArtiVenta.m_PESO);
		m_lstArticulos.SetItemText(iIndice, 2, strPeso);
		m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);

		// Se busca el tipo de venta y de alquiler
		POSITION pos = m_strTipo.Find(rsArtiVenta.m_ALQUILER);	
		if (pos != NULL)
		{
			m_strTipo.GetNext(pos);
			m_lstArticulos.SetItemText(iIndice, 3, m_strTipo.GetNext(pos));
		}
		else
			m_lstArticulos.SetItemText(iIndice, 3, "");

		if (rsArtiVenta.m_ALQUILER == "S") // Se busca el tipo de alquiler sólo si es tipo Alquiler
		{
			pos = m_strTipoAlquiler.Find(rsArtiVenta.m_TIPOALQ);	
			if (pos != NULL)
			{
				m_strTipoAlquiler.GetNext(pos);
				m_lstArticulos.SetItemText(iIndice, 4, m_strTipoAlquiler.GetNext(pos));
			}
			else
				m_lstArticulos.SetItemText(iIndice, 4, "");
		}
		else
			m_lstArticulos.SetItemText(iIndice, 4, "");

		m_lIniTipo.AddTail(rsArtiVenta.m_ALQUILER);

		// Se escribe la cantidad
		CString strCantidad;
		strCantidad.Format("%g", rsArtiVenta.m_CANTI);
		m_lstArticulos.SetItemText(iIndice, 5, strCantidad);
		m_lOldCantidad.AddTail((int)rsArtiVenta.m_CANTI);
		m_lIniCantidad.AddTail((int)rsArtiVenta.m_CANTI);

		CString strTarifa;
		strTarifa.Format("%g", rsArtiVenta.m_IMPOARTI);
		m_lstArticulos.SetItemText(iIndice, 6, strTarifa);
		m_lOldTarifa.AddTail(rsArtiVenta.m_IMPOARTI);

		CString strDto;
		strDto.Format("%g", rsArtiVenta.m_DTOARTI);
		m_lstArticulos.SetItemText(iIndice, 7, strDto);
		m_lOldDto.AddTail(rsArtiVenta.m_DTOARTI);

		m_dTotalPeso += abs(rsArtiVenta.m_CANTI) * rsArtiVenta.m_PESO;
		m_dTotalBruto += rsArtiVenta.m_CANTI * rsArtiVenta.m_IMPOARTI * (1 - (rsArtiVenta.m_DTOARTI / 100));;

		CString strIVA;
		strIVA.Format("%g", rsArtiVenta.m_IVARTI);
		m_lstArticulos.SetItemText(iIndice, 8, strIVA);

		m_lstArticulos.SetItemText(iIndice, 9, rsArtiVenta.m_DESARMEMO.Trim());

		// Si el pedido está facturado sería de sólo lectura
		if (m_rsPedido.m_ESTADO != NO_FACTURADO)
		{
			m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 4, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 6, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 7, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 8, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 9, RGB(183, 183, 183), TRUE);
		}

		iIndice ++;
		m_iNumArti++;
		rsArtiVenta.MoveNext();
	}

	rsArtiVenta.Close();

	m_strTotalPeso.Empty();
	m_strTotalPeso.Format("%.3f", m_dTotalPeso);

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
}

/******************************************************************************************/
void CDlgGestionVentas::BuscaArticulosAlbaran(CString strNumAlbaran)
{
	CArtiAlbaran rsArtiAlbaran(m_db);

	rsArtiAlbaran.m_strFilter = "NUMALB LIKE '" + strNumAlbaran + "'";
	if (!rsArtiAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si el albarán tiene artículos se rellena el listCtrl
	m_dTotalPeso = 0;
	m_dTotalBruto = 0;
	int iIndice = 0;
	while (!rsArtiAlbaran.IsEOF())
	{
		m_lstArticulos.InsertItem(iIndice, _T(""));
		m_lstArticulos.SetItemText(iIndice, 0, rsArtiAlbaran.m_ARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);

		m_lstArticulos.SetItemText(iIndice, 1, rsArtiAlbaran.m_DESARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);

		CString strPeso;
		strPeso.Format("%g", rsArtiAlbaran.m_PESO);
		m_lstArticulos.SetItemText(iIndice, 2, strPeso);
		m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);

		// Se busca el tipo de venta y de alquiler
		POSITION pos = m_strTipo.Find(rsArtiAlbaran.m_ALQUILER);	
		if (pos != NULL)
		{
			m_strTipo.GetNext(pos);
			m_lstArticulos.SetItemText(iIndice, 3, m_strTipo.GetNext(pos));
		}
		else
			m_lstArticulos.SetItemText(iIndice, 3, "");

		if (rsArtiAlbaran.m_ALQUILER == "S") // Se busca el tipo de alquiler sólo si es tipo Alquiler
		{
			pos = m_strTipoAlquiler.Find(rsArtiAlbaran.m_TIPOALQ);	
			if (pos != NULL)
			{
				m_strTipoAlquiler.GetNext(pos);
				m_lstArticulos.SetItemText(iIndice, 4, m_strTipoAlquiler.GetNext(pos));
			}
			else
				m_lstArticulos.SetItemText(iIndice, 4, "");
		}
		else
			m_lstArticulos.SetItemText(iIndice, 4, "");

		m_lIniTipo.AddTail(rsArtiAlbaran.m_ALQUILER);


		// Se escribe la cantidad
		CString strCantidad;
		strCantidad.Format("%g", rsArtiAlbaran.m_CANTI);
		m_lstArticulos.SetItemText(iIndice, 5, strCantidad);
		m_lOldCantidad.AddTail((int)rsArtiAlbaran.m_CANTI);
		m_lIniCantidad.AddTail((int)rsArtiAlbaran.m_CANTI);

		CString strTarifa;
		strTarifa.Format("%g", rsArtiAlbaran.m_IMPOARTI);
		m_lstArticulos.SetItemText(iIndice, 6, strTarifa);
		m_lOldTarifa.AddTail(rsArtiAlbaran.m_IMPOARTI);

		CString strDto;
		strDto.Format("%g", rsArtiAlbaran.m_DTOARTI);
		m_lstArticulos.SetItemText(iIndice, 7, strDto);
		m_lOldDto.AddTail(rsArtiAlbaran.m_DTOARTI);

		m_dTotalPeso += abs(rsArtiAlbaran.m_CANTI) * rsArtiAlbaran.m_PESO;
		m_dTotalBruto += rsArtiAlbaran.m_CANTI * rsArtiAlbaran.m_IMPOARTI * (1 - (rsArtiAlbaran.m_DTOARTI / 100));;

		CString strIVA;
		strIVA.Format("%g", rsArtiAlbaran.m_IVARTI);
		m_lstArticulos.SetItemText(iIndice, 8, strIVA);

		m_lstArticulos.SetItemText(iIndice, 9, rsArtiAlbaran.m_DESARMEMO.Trim());

		// Si el albarán lleva asociado un pedido será sólo de lectura
		if (!m_rsAlbaran.m_NUMPEDIDO.Trim().IsEmpty() && (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA ||
		m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA))
		{
			m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 4, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 6, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 7, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 8, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iIndice, 9, RGB(183, 183, 183), TRUE);
		}

		iIndice ++;
		m_iNumArti++;
		rsArtiAlbaran.MoveNext();
	}

	rsArtiAlbaran.Close();

	m_strTotalPeso.Empty();
	m_strTotalPeso.Format("%.3f", m_dTotalPeso);

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
}

/******************************************************************************************/
void CDlgGestionVentas::InsertaRegistroVacio()
{
	m_lstArticulos.InsertItem(m_iNumArti, _T(""));
	m_lstArticulos.SetItemText(m_iNumArti, 0, "");
	m_lstArticulos.SetItemText(m_iNumArti, 1, "");
	m_lstArticulos.SetItemText(m_iNumArti, 2, "");
	m_lstArticulos.SetItemText(m_iNumArti, 3, "");
	m_lstArticulos.SetItemText(m_iNumArti, 4, "");
	m_lstArticulos.SetItemText(m_iNumArti, 5, "");
	m_lstArticulos.SetItemText(m_iNumArti, 6, "");
	m_lstArticulos.SetItemText(m_iNumArti, 7, "");
	m_lstArticulos.SetItemText(m_iNumArti, 8, "");
	m_lstArticulos.SetItemText(m_iNumArti, 9, "");

	m_lstArticulos.EnsureVisible(m_iNumArti, FALSE);

}

/******************************************************************************************/
void CDlgGestionVentas::BuscaArticulo(CString strCodArti)
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

	m_lIniTipo.AddTail("");

	// Se escribe la cantidad
	m_lstArticulos.SetItemText(m_iNumArti, 5, "0");
	m_lOldCantidad.AddTail((int)0);

	if (m_iTipo == PEDIDO || m_iTipo == ALBARAN)
		m_lIniCantidad.AddTail((int)0);

	// Se busca la tarifa. Si el campo tarifa está vacío no se pone ninguna
	double dTarifa = 0, dDto = 0;
	if (!m_strTarifa.IsEmpty())
		ObtenerTarifa(&rsArticulo, dTarifa, dDto);

	m_lstArticulos.SetItemText(m_iNumArti, 6, dTarifa);
	m_lstArticulos.SetItemText(m_iNumArti, 7, dDto);
	m_lstArticulos.SetItemText(m_iNumArti, 8, rsArticulo.m_IVARTI);
	m_lstArticulos.SetItemText(m_iNumArti, 9, rsArticulo.m_DESARMEMO.Trim());

	//m_lstArticulos.EnsureVisible(m_iNumArti, FALSE);

	// Se añade Tarifa y Dto a la lista de valores iniciales
	m_lOldTarifa.AddTail(dTarifa);
	m_lOldDto.AddTail(dDto);

	/**CString strTarifa, strDto;
	strTarifa.Format("%f", dTarifa);
	strDto.Format("%f", dDto);
	m_lOldTarifa.AddTail(strTarifa);
	m_lOldDto.AddTail(strTarifa);*/

	rsArticulo.Close();

	m_iNumArti++;

	InsertaRegistroVacio();

	// Se deshabilita el botón de Buscar y Eliminar
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
}

/******************************************************************************************/
void CDlgGestionVentas::ObtenerTarifa(CArticulo *rsArticulo, double &dTarifa, double &dDto)
{
	switch(m_strTarifa.GetAt(0))
	{
		case 'A':  dTarifa = rsArticulo->m_ETARI1;
			       dDto = rsArticulo->m_DTOTAR1;
				   break;

		case 'B':  dTarifa = rsArticulo->m_ETARIB1;
			       dDto = rsArticulo->m_DTOTARB1;
				   break;

		case 'C':  dTarifa = rsArticulo->m_ETARIC1;
			       dDto = rsArticulo->m_DTOTARC1;
				   break;

		case 'D':  dTarifa = rsArticulo->m_ETARID1;
			       dDto = rsArticulo->m_DTOTARD1;
				   break;

		case 'E':  dTarifa = rsArticulo->m_ETARIE1;
			       dDto = rsArticulo->m_DTOTARE1;
				   break;

		case 'F':  dTarifa = rsArticulo->m_ETARIF1;
			       dDto = rsArticulo->m_DTOTARF1;
				   break;

		case 'G':  dTarifa = rsArticulo->m_ETARIG1;
			       dDto = rsArticulo->m_DTOTARG1;
				   break;

		case 'H':  dTarifa = rsArticulo->m_ETARIH1;
			       dDto = rsArticulo->m_DTOTARH1;
				   break;

		case 'I':  dTarifa = rsArticulo->m_ETARII1;
			       dDto = rsArticulo->m_DTOTARI1;
				   break;
	}
}

/******************************************************************************************/
/*  Si cambia la cantidad se debe recalcular el Peso y el Total Bruto                     */
/******************************************************************************************/
void CDlgGestionVentas::CambiaCantidad()
{
	// Se comprueba si en la cantidad son todo dígitos
	CString strCantidad /*, strOldCantidad*/;
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
			m_lstArticulos.SetItemText(iFila, 5, iOldCantidad);
			return;
		}
	}

	// Si cantidad no tiene nada se considera 0
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

//	m_lstArticulos.SetItemTextCB(iFila, 5, strCantidad);

	// Se recalcula el PESO
	double dPeso = atof(m_lstArticulos.GetItemText(iFila, 2));

	// Primero se debe restar el peso que suponía con la cantidad anterior.
	double dPesoAnterior = abs(iOldCantidad) * dPeso;
	m_dTotalPeso -= dPesoAnterior;

	// Se calcula el nuevo peso total
	m_dTotalPeso += abs(iCantidad) * dPeso;

	m_strTotalPeso.Empty();
	m_strTotalPeso.Format("%.3f", m_dTotalPeso);
	GetDlgItem(IDC_EDIT_TOTAL_PESO)->SetWindowText(m_strTotalPeso);

	// Se recalcula el PRECIO
	double dTarifa = atof(m_lstArticulos.GetItemText(iFila, 6));
	double dDto = atof(m_lstArticulos.GetItemText(iFila, 7));

	// Primero se debe restar el peso que suponía con la cantidad anterior.
	double dPrecioAnterior = iOldCantidad * dTarifa * (1 - (dDto / 100));
	m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio total
	m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	m_lOldCantidad.SetAt(m_lOldCantidad.FindIndex(iFila), iCantidad);

	if ((m_iTipo == PEDIDO || m_iTipo == ALBARAN) ) //&& (strTipo == ALQUILER || strTipo == ALQUILER))
		CompruebaArtiDisponible(m_lstArticulos.GetItemText(iFila, 0), iFila, iCantidad);
}


/******************************************************************************************/
/*  Si cambia la tarifa se debe recalcular el Total Bruto                                 */
/******************************************************************************************/
void CDlgGestionVentas::CambiaTarifa()
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
		m_lstArticulos.SetItemText(iFila, 6, dOldTarifa);
		return;
	}

	// Si cantidad no tiene nada se cosidera 0
	if (strTarifa.IsEmpty())
	{
		dTarifa = 0;
		m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 6, dTarifa);
	}
	else
		dTarifa = atof(strTarifa);

	// Si la tarifa no ha cambiado abandonamos la función
	if (dTarifa == dOldTarifa)
		return;

//	m_lstArticulos.SetItemTextCB(iFila, 6, strTarifa);

	// Se recalcula el PRECIO
	int iCantidad = atoi(m_lstArticulos.GetItemText(iFila, 5));
	double dDto = atof(m_lstArticulos.GetItemText(iFila, 7));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior = iCantidad * dOldTarifa * (1 - (dDto / 100));
	m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio total
	m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	m_lOldTarifa.SetAt(m_lOldTarifa.FindIndex(iFila), dTarifa);
}

/******************************************************************************************/
/*  Si cambia el descuento debe recalcular el Total Bruto                                 */
/******************************************************************************************/
void CDlgGestionVentas::CambiaDescuento()
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
		m_lstArticulos.SetItemText(iFila, 7, dOldDto);
		return;
	}

	// Si el descuento está vacío se considera 0
	if (strDto.IsEmpty())
	{
		dDto = 0;
		m_lstArticulos.SetItemText(iFila, 7, dDto);
	}
	else
		dDto = atof(strDto);

	// Si el descuento no ha cambiado abandonamos la función
	if (dDto == dOldDto)
		return;

//	m_lstArticulos.SetItemTextCB(iFila, 7, strDto);

	// Se recalcula el PRECIO
	int iCantidad = atoi(m_lstArticulos.GetItemText(iFila, 5));
	double dTarifa = atof(m_lstArticulos.GetItemText(iFila, 6));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior = iCantidad * dTarifa * (1 - dOldDto / 100);
	m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio total
	m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_EDIT_TOTAL_BRUTO)->SetWindowText(m_strTotalBruto);

	m_lOldDto.SetAt(m_lOldDto.FindIndex(iFila), dDto);
}

/************************************************************************************************************/
void CDlgGestionVentas::CompruebaIva()
{
	// Se comprueba si el IVA son sólo números. Si no se pone el IVA por defecto que es 16
	CString strIVA = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 8);
		if (!CompruebaNumero(strIVA))
	{
		m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 8, "16");
		return;
	}
}

/************************************************************************************************************/
/** Comprueba que en la cadena no hay mas que números y como mucho un punto                                **/    
/************************************************************************************************************/
BOOL CDlgGestionVentas::CompruebaNumero(CString strNumero)
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
void CDlgGestionVentas::CompruebaArtiDisponible(CString strARTI, int iFila, int iCantidad)
{
	CInventario rsInventario(m_db);

	rsInventario.m_strFilter = "ARTI LIKE '" + strARTI + "' AND ALMACEN LIKE '" + m_strAlmacen + "'";
	if (!rsInventario.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si el articulo está en la tabla inventario
	if (rsInventario.m_ARTI.IsEmpty())
		rsInventario.m_UNIDISPONIBLE = 0;

	// Se comprueba si ya se habían cogido algunas unidades del artículo. Se hace si estamos
	// en Albarán os si estando en un Pedido, ese pedido ya tiene asociado un albarán.
	if (m_iTipo == ALBARAN || (m_iTipo == PEDIDO && m_bAlbaranPed))
	{
		// Si es de Entrega, Recogida u Otros como no ha habido movimiento de almacén, no se
		// le debe sumar la cantidad inicial
		CString strTipo = m_lIniTipo.GetAt(m_lIniTipo.FindIndex(iFila));
		if (strTipo == "S" || strTipo == "V")
		{
			int iIniCantidad = m_lIniCantidad.GetAt(m_lIniCantidad.FindIndex(iFila));
			rsInventario.m_UNIDISPONIBLE += iIniCantidad; // Se le suma las unidades de ese
															// artículo que ya hubiéramos reservado
		}
	}
	if (rsInventario.m_UNIDISPONIBLE < iCantidad)
	{
		// Si el elemento no está en la lista de elementos no disponibles se inserta
		if (m_lCodArtiNoDisponible.Find(strARTI) == NULL)
			m_lCodArtiNoDisponible.AddHead(strARTI);

		// Si el tipo es Alquiler o Venta se da un mensaje de error, si no simplemente se
		// guarda el artículo que no tenía disponibilidad. En la lista se guardan todos,
		// por si se tocan los combos de tipo sin haber variado la cantidad de artículos
		CString strTipo = m_lstArticulos.GetItemText(iFila, 3);
		if (strTipo == ALQUILER || strTipo == VENTA)
		{
			CString strMsg;
			strMsg.Format(IDC_NO_DISPONIBLE, m_strDesAlmacen, rsInventario.m_UNIDISPONIBLE);
			AfxMessageBox(strMsg);
		}

	}
	else
	{
		// Si el elemento estaba en la lista de elementos no disponibles se elimina
		POSITION pos;
		if ((pos = m_lCodArtiNoDisponible.Find(strARTI)) != NULL)
			m_lCodArtiNoDisponible.RemoveAt(pos);
	}

	return;
}

/************************************************************************************************************/
void CDlgGestionVentas::CompruebaDisponibilidadArticulos()
{
	// Si no hay artículos en el listCtrl se abandona la función
	if (m_lstArticulos.GetItemCount() == 0)
		return;

	m_lArtiNoDisponible.RemoveAll();
	m_lCodArtiNoDisponible.RemoveAll();

	int iCantidad = 0;
	CInventario rsInventario(m_db);

	for (int i=0; i<m_lstArticulos.GetItemCount()-1; i++)
	{		
		rsInventario.m_ARTI.Empty();
		rsInventario.m_strFilter = "ARTI LIKE '" + m_lstArticulos.GetItemText(i, 0) + "' AND ALMACEN LIKE '" + m_strAlmacen + "'";
		if (!rsInventario.Open(CRecordset::dynaset))
		{	
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}

		// Se obtiene la cantidad de artículos pedidos
		iCantidad = atoi(m_lstArticulos.GetItemText(i, 5));

		// Se comprueba si ya se habían cogido algunas unidades del artículo. Se hace si estamos
		// en Albarán os si estando en un Pedido, ese pedido ya tiene asociado un albarán.
		if (m_iTipo == ALBARAN || (m_iTipo == PEDIDO && m_bAlbaranPed))
		{
			// Si es de Entrega, Recogida u Otros como no ha habido movimiento de almacén, no se
			// le debe sumar la cantidad inicial
			CString strTipo = m_lstArticulos.GetItemText(i, 3);
			if (strTipo == ALQUILER || strTipo == VENTA)
			{
				int iIniCantidad = m_lIniCantidad.GetAt(m_lIniCantidad.FindIndex(i));
				rsInventario.m_UNIDISPONIBLE += iIniCantidad; // Se le suma las unidades de ese
													// artículo que ya hubiéramos reservado
			}
		}

		// Si el articulo no está en la tabla inventario se inicializa con 0
		if (rsInventario.m_ARTI.IsEmpty())
			rsInventario.m_UNIDISPONIBLE = 0;

		if (rsInventario.m_UNIDISPONIBLE < iCantidad)
		{
			m_lCodArtiNoDisponible.AddTail(m_lstArticulos.GetItemText(i, 0));

			// Sólo se meterá en la lista para dar el aviso si es Venta o Alquiler
			CString strTipo = m_lstArticulos.GetItemText(i, 3);
			if (strTipo == ALQUILER || strTipo == VENTA)
			{
				m_lArtiNoDisponible.AddTail(m_lstArticulos.GetItemText(i, 0));
				m_lArtiNoDisponible.AddTail(m_lstArticulos.GetItemText(i, 1));
				CString strCanti;
				strCanti.Format("%d", iCantidad);
				m_lArtiNoDisponible.AddTail(strCanti);
				CString strUniDisponible;
				strUniDisponible.Format("%d", rsInventario.m_UNIDISPONIBLE);
				m_lArtiNoDisponible.AddTail(strUniDisponible);
			}
		}

		rsInventario.Close();
	}

	return;
}

/******************************************************************************************/
void CDlgGestionVentas::MuestraAviso()
{
	CString strMsg;

	if (m_lArtiNoDisponible.IsEmpty())
		return;

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

/******************************************************************************************/
HRESULT CDlgGestionVentas::GuardaOferta()
{
	HRESULT hErr = S_OK;

	CConta rsConta(m_db);
	CArtiProforma rsArtiProforma(m_db);

	CString strNextNumProfor;

	// Se rellenan los campos de la Proforma con lo que contienen los editbox
	RellenaProforma();

	// Se crea la Proforma y luego se insertan cada uno de los artículos que la componen
	if (!m_db->BeginTrans())
		return -1;

	// Si es un nuevo registro se inserta, si ya existe se actualiza y se eliminan todos
	// los artículos que pudiera tener y se insertan los que tiene actualmente
	if (m_bNuevo)
	{
		// El estado será Pendiente
		m_rsProforma.m_ESTADO = TIPO_PENDIENTE;

		// Se coge el siguiente número de proforma
		hErr = rsConta.GetNextNumProfor(strNextNumProfor);

		if (hErr == S_OK)
		{
			m_rsProforma.m_NUMPROFOR = strNextNumProfor;
			hErr = m_rsProforma.Insert();
		}
	}
	else
	{
		hErr = m_rsProforma.UpdateProforma();
		if (hErr == S_OK)
		{
			rsArtiProforma.m_NUMPROFOR = m_rsProforma.m_NUMPROFOR;
			hErr = rsArtiProforma.DeleteArtiProforma();
		}
	}

	if (hErr == S_OK)
	{	
		POSITION pos;

		for (int i=0; i< m_lstArticulos.GetItemCount()-1 && hErr == S_OK;i++)
		{
			rsArtiProforma.m_NUMPROFOR = m_rsProforma.m_NUMPROFOR;
			rsArtiProforma.m_ARTI = m_lstArticulos.GetItemText(i, 0);
			rsArtiProforma.m_DESARTI = m_lstArticulos.GetItemText(i, 1);
			rsArtiProforma.m_PESO = atof(m_lstArticulos.GetItemText(i, 2));

			pos = m_strTipo.Find(m_lstArticulos.GetItemText(i, 3));	
			if (pos != NULL)
			{
				m_strTipo.GetPrev(pos);
				rsArtiProforma.m_ALQUILER = m_strTipo.GetPrev(pos);
			}
			else
				rsArtiProforma.m_ALQUILER.Empty();

			pos = m_strTipoAlquiler.Find(m_lstArticulos.GetItemText(i, 4));	
			if (pos != NULL)
			{
				m_strTipoAlquiler.GetPrev(pos);
				rsArtiProforma.m_TIPOALQ = m_strTipoAlquiler.GetPrev(pos);
			}
			else
				rsArtiProforma.m_TIPOALQ.Empty();

			rsArtiProforma.m_CANTI = atof(m_lstArticulos.GetItemText(i, 5));
			rsArtiProforma.m_IMPOARTI = atof(m_lstArticulos.GetItemText(i, 6));
			rsArtiProforma.m_DTOARTI = atof(m_lstArticulos.GetItemText(i, 7));
			rsArtiProforma.m_IVARTI = atof(m_lstArticulos.GetItemText(i, 8));
			rsArtiProforma.m_DESARMEMO = m_lstArticulos.GetItemText(i, 9);

			hErr = rsArtiProforma.Insert();
		}
	}

	if (hErr == S_OK)
	{
		m_db->CommitTrans();

		if (m_bNuevo)
		{
			CString strMsg;
			strMsg.Format(IDC_CREADA_OFERTA, strNextNumProfor); 
			AfxMessageBox(strMsg, MB_ICONINFORMATION);
		}
	}
	else
		m_db->Rollback();

	//LimpiaVentana();

	return hErr;
}

/************************************************************************************************************/
void CDlgGestionVentas::RellenaProforma()
{
	if (m_iTipoPedido == TIPO_ANDAMIO)
		m_rsProforma.m_TIPO = ANDAMIO;
	else if (m_iTipoPedido == TIPO_MAQUINARIA)
		m_rsProforma.m_TIPO = MAQUINARIA;

	if (m_iTipoNacional == 0)
		m_rsProforma.m_EXPORTA = "N";
	else if (m_iTipoNacional == 1)
		m_rsProforma.m_EXPORTA = "S";

	m_rsProforma.m_CUENTA = m_strCuenta.Trim();
	m_rsProforma.m_TELEF1 = m_strTelefono.Trim();
	m_rsProforma.m_TELEF2 = m_strFax.Trim();
	m_rsProforma.m_TARIFA = m_strTarifa.Trim();
	m_rsProforma.m_DCTOS = m_dDtos1;
	m_rsProforma.m_DCTOS2 = m_dDtos2;
	m_rsProforma.m_DCTOS3 = m_dDtos3;
	m_rsProforma.m_PP = m_dProntoPago;
	m_rsProforma.m_IVA = m_dIVA;
	m_rsProforma.m_GRUFAC = m_strGFacturacion.Trim();
	m_rsProforma.m_DIRENV = m_strObra.Trim();
	m_rsProforma.m_REPRE = m_strRepre.Trim();
	m_rsProforma.m_SUBREP = m_strSubRepre.Trim();
	m_rsProforma.m_COMISION = m_dComisionRepre;
	m_rsProforma.m_COMISION2 = m_dComisionSubRepre;
	m_rsProforma.m_FECHPROF = m_timeFecha;
	m_rsProforma.m_FECHCADU = m_timeFecha2;
	m_rsProforma.m_CENTRO = m_strCentro.Trim();
	m_rsProforma.m_SREF	= m_strReferencia.Trim();
	m_rsProforma.m_ATENCLI = m_strAtencion.Trim();

	m_rsProforma.m_FCOBRO =	m_datosCobro.m_FCOBRO.Trim();
	m_rsProforma.m_NCOBROS = m_datosCobro.m_NCOBROS;
	m_rsProforma.m_VTO1 = m_datosCobro.m_VTO1;
	m_rsProforma.m_DVTO = m_datosCobro.m_DVTO;
	m_rsProforma.m_DIA1 = m_datosCobro.m_DIA1;
	m_rsProforma.m_DIA2 = m_datosCobro.m_DIA2;
	m_rsProforma.m_DIA3 = m_datosCobro.m_DIA3;
	m_rsProforma.m_RETENFIS = m_datosCobro.m_RETENFIS;

/*	, m_strTotalBruto(_T(""))
	, m_strTotalPeso(_T(""))*/
}

/************************************************************************************************************/
void CDlgGestionVentas::LimpiaOferta()
{
	// Se limpian los campos de la Proforma
	m_rsProforma.m_NUMPROFOR.Empty();
	m_rsProforma.m_EXPORTA.Empty();
	m_rsProforma.m_TIPO.Empty();
	m_rsProforma.m_ESTADO.Empty();
	m_rsProforma.m_CUENTA.Empty();
	m_rsProforma.m_TARIFA.Empty();
	m_rsProforma.m_DCTOS = 0;
	m_rsProforma.m_DCTOS2 = 0;
	m_rsProforma.m_DCTOS3 = 0;
	m_rsProforma.m_PP = 0;
	m_rsProforma.m_GRUFAC.Empty();
	m_rsProforma.m_DIRENV.Empty();
	m_rsProforma.m_REPRE.Empty();
	m_rsProforma.m_SUBREP.Empty();
	m_rsProforma.m_COMISION = 0;
	m_rsProforma.m_COMISION2 = 0;
	m_rsProforma.m_FECHPROF = NULL;
	m_rsProforma.m_FECHCADU = NULL;
	m_rsProforma.m_CENTRO.Empty();
	m_rsProforma.m_SREF.Empty();
	m_rsProforma.m_ATENCLI.Empty();
	m_rsProforma.m_TELEF1.Empty();
	m_rsProforma.m_TELEF2.Empty();
	m_rsProforma.m_FCOBRO.Empty();
	m_rsProforma.m_NCOBROS = 0;
	m_rsProforma.m_VTO1 = 0;
	m_rsProforma.m_DVTO = 0;
	m_rsProforma.m_DIA1 = 0;
	m_rsProforma.m_DIA2 = 0;
	m_rsProforma.m_DIA3 = 0;
	m_rsProforma.m_RETENCOM = 0;
	m_rsProforma.m_RETENFIS = 0;
	m_rsProforma.m_OBSPROF.Empty();

	// Se habilitan los campos desactivados
	m_cCuenta.SetReadOnly(FALSE);
	m_cTelefono.SetReadOnly(FALSE);
	m_cFax.SetReadOnly(FALSE);
	m_cDtos1.SetReadOnly(FALSE);
	m_cProntoPago.SetReadOnly(FALSE);
	m_cIVA.SetReadOnly(FALSE);
	m_cObra.SetReadOnly(FALSE);
	m_cRepre.SetReadOnly(FALSE);
	m_cSubRepre.SetReadOnly(FALSE);
	m_cComisionRepre.SetReadOnly(FALSE);
	m_cComisionSubRepre.SetReadOnly(FALSE);
	m_cCentro.SetReadOnly(FALSE);
	m_cReferencia.SetReadOnly(FALSE);
	m_cAtn.SetReadOnly(FALSE);

	GetDlgItem(IDC_RB_NACIONAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RB_EXPORTACION)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA2)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_ARTICULOS)->EnableWindow(TRUE);

	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CUENTAREPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CUENTASUBREPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CENTRO)->EnableWindow(TRUE);

	m_bEmitir1 = FALSE;
}

/************************************************************************************************************/
void CDlgGestionVentas::SoloLectura()
{
	m_bReadOnly = TRUE;

	m_cCuenta.SetReadOnly();
	m_cTelefono.SetReadOnly();
	m_cFax.SetReadOnly();
	m_cDtos1.SetReadOnly();
	m_cProntoPago.SetReadOnly();
	m_cIVA.SetReadOnly();
	m_cObra.SetReadOnly();
	m_cRepre.SetReadOnly();
	m_cSubRepre.SetReadOnly();
	m_cComisionRepre.SetReadOnly();
	m_cComisionSubRepre.SetReadOnly();
	m_cCentro.SetReadOnly();
	m_cReferencia.SetReadOnly();
	m_cAtn.SetReadOnly();

	GetDlgItem(IDC_RB_NACIONAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RB_EXPORTACION)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA)->EnableWindow(FALSE);

	if (m_iTipo == OFERTA)
		GetDlgItem(IDC_FECHA2)->EnableWindow(FALSE);

	m_lstArticulos.DeleteItem(m_lstArticulos.GetItemCount()-1);
	//GetDlgItem(IDC_LIST_ARTICULOS)->EnableWindow(FALSE);

	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CUENTAREPRE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CUENTASUBREPRE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CENTRO)->EnableWindow(FALSE);

	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);

	if (m_iTipo == OFERTA || m_iTipo == PEDIDO)
		GetDlgItem(IDOK)->EnableWindow(FALSE);
}

/******************************************************************************************/
HRESULT CDlgGestionVentas::GuardaPedido()
{
	HRESULT hErr = S_OK;

	CConta rsConta(m_db);
	CArtiVenta rsArtiVenta(m_db);

	CString strNextNumPedido;
	CStringList lAlbaranes;

	// Se rellenan los campos del pedido con lo que contienen los editbox
	RellenaPedido();

	// Se crea el Pedido y luego se insertan cada uno de los artículos que lo componen
	if (!m_db->BeginTrans())
		return -1;

	// Si es un nuevo registro se inserta, si ya existe se actualiza y se eliminan todos
	// los artículos que pudiera tener y se insertan los que tiene actualmente
	if (m_bNuevo)
	{
		// Se coge el siguiente número de pedido
		hErr = rsConta.GetNextNumPedidoVenta(strNextNumPedido);

		if (hErr == S_OK)
		{
			m_rsPedido.m_NUMPEDIDO = strNextNumPedido.Trim();
			hErr = m_rsPedido.Insert();
		}
	}
	else
	{
		hErr = m_rsPedido.UpdatePedido();
		if (hErr == S_OK)
		{
			rsArtiVenta.m_NUMPEDIDO = m_rsPedido.m_NUMPEDIDO.Trim();
			hErr = rsArtiVenta.DeleteArtiVenta();
		}
	}

	if (hErr == S_OK)
	{	
		POSITION pos;

		for (int i=0; i< m_lstArticulos.GetItemCount()-1 && hErr == S_OK;i++)
		{
			rsArtiVenta.m_NUMPEDIDO = m_rsPedido.m_NUMPEDIDO.Trim();
			rsArtiVenta.m_ARTI = m_lstArticulos.GetItemText(i, 0);
			rsArtiVenta.m_DESARTI = m_lstArticulos.GetItemText(i, 1);
			rsArtiVenta.m_PESO = atof(m_lstArticulos.GetItemText(i, 2));

			pos = m_strTipo.Find(m_lstArticulos.GetItemText(i, 3));	
			if (pos != NULL)
			{
				m_strTipo.GetPrev(pos);
				rsArtiVenta.m_ALQUILER = m_strTipo.GetPrev(pos);
			}
			else
				rsArtiVenta.m_ALQUILER.Empty();

			pos = m_strTipoAlquiler.Find(m_lstArticulos.GetItemText(i, 4));	
			if (pos != NULL)
			{
				m_strTipoAlquiler.GetPrev(pos);
				rsArtiVenta.m_TIPOALQ = m_strTipoAlquiler.GetPrev(pos);
			}
			else
				rsArtiVenta.m_TIPOALQ.Empty();

			rsArtiVenta.m_CANTI = atof(m_lstArticulos.GetItemText(i, 5));
			rsArtiVenta.m_IMPOARTI = atof(m_lstArticulos.GetItemText(i, 6));
			rsArtiVenta.m_DTOARTI = atof(m_lstArticulos.GetItemText(i, 7));
			rsArtiVenta.m_IVARTI = atof(m_lstArticulos.GetItemText(i, 8));
			rsArtiVenta.m_DESARMEMO = m_lstArticulos.GetItemText(i, 9);

			hErr = rsArtiVenta.Insert();
		}
	}

	// Si hay algún fallo no se continúa, se termina la transaccion con RollBack
	if (hErr != S_OK)
		m_db->Rollback();

	// Si es nuevo y no hay que emitir albarán termina aquí la transacción
	// Si no es nuevo pero no tiene albarán asociado, también termina aquí
	else if ((m_bNuevo && !m_bEmitir2) || (!m_bNuevo && !m_bAlbaranPed && !m_bEmitir2))
	{
		m_db->CommitTrans();

		if (m_bNuevo)
		{
			CString strMsg;
			strMsg.Format(IDC_CREADO_PEDIDO, strNextNumPedido); 
			AfxMessageBox(strMsg, MB_ICONINFORMATION);
		}
	}

	// Si el pedido tiene asociado más de un albarán se eliminan todos los que tuviera
	else if (BuscaAlbaranes(&lAlbaranes))
	{
		hErr = EliminaAlbaranes(&lAlbaranes, m_rsPedido.m_ALMACEN);
		if (hErr == S_OK)
		{
			CString strMsg, strAlbaranes;
			for (int i=0; i<lAlbaranes.GetCount(); i+=2)
				strAlbaranes += " " + lAlbaranes.GetAt(lAlbaranes.FindIndex(i)).Trim() + "/";
			strAlbaranes = strAlbaranes.Left(strAlbaranes.GetLength()-1); // Se le quita la última coma
			strMsg.Format(IDC_ALBARANESPED_ELIMINADOS, m_rsPedido.m_NUMPEDIDO, strAlbaranes);
			AfxMessageBox(strMsg);

			// Si había que emitir factura ya no se debe emitir, al no haber albaranes
			if (m_bEmitir3)
				m_bEmitir3 = FALSE;
		}
	}

	// Si sólo tiene uno y hay emisión de albarán o ya existe se debe actualizar este
	else if (hErr == S_OK && (m_bEmitir2 || m_bAlbaranPed))
	{	
		// Si el albarán es nuevo se preguntan sus datos
		if (!m_bAlbaranPed)
		{
			CDlgDatosAlbaran dlgDatosAlbaran;
			dlgDatosAlbaran.SetConexion(m_db);
			dlgDatosAlbaran.DoModal();
			m_rsAlbaran.m_OBSALB = dlgDatosAlbaran.GetObservaciones();
			m_timeFecha2 = dlgDatosAlbaran.GetFechaIniAlq();
			m_bNuevo = TRUE;
		}		

		// Se guarda el albarán
		hErr = GuardaAlbaran();
	}

	//LimpiaVentana();

	return hErr;
}

/************************************************************************************************************/
void CDlgGestionVentas::RellenaPedido()
{
	if (m_iTipoPedido == TIPO_ANDAMIO)
		m_rsPedido.m_TIPO = ANDAMIO;
	else if (m_iTipoPedido == TIPO_MAQUINARIA)
		m_rsPedido.m_TIPO = MAQUINARIA;

	if (m_iTipoNacional == 0)
		m_rsPedido.m_EXPORTA = "N";
	else if (m_iTipoNacional == 1)
		m_rsPedido.m_EXPORTA = "S";

	m_rsPedido.m_CUENTA = m_strCuenta.Trim();
	m_rsPedido.m_ESTADO = NO_FACTURADO;
	m_rsPedido.m_ALMACEN = m_strAlmacen;
	m_rsPedido.m_TELEF1 = m_strTelefono.Trim();
	m_rsPedido.m_TELEF2 = m_strFax.Trim();
	m_rsPedido.m_TARIFA = m_strTarifa.Trim();
	m_rsPedido.m_DCTOS = m_dDtos1;
	m_rsPedido.m_DCTOS2 = m_dDtos2;
	m_rsPedido.m_DCTOS3 = m_dDtos3;
	m_rsPedido.m_PP = m_dProntoPago;
	m_rsPedido.m_IVA = m_dIVA;
	m_rsPedido.m_GRUFAC = m_strGFacturacion.Trim();
	m_rsPedido.m_DIRENV = m_strObra.Trim();
	m_rsPedido.m_REPRE = m_strRepre.Trim();
	m_rsPedido.m_SUBREP = m_strSubRepre.Trim();
	m_rsPedido.m_COMISION = m_dComisionRepre;
	m_rsPedido.m_COMISION2 = m_dComisionSubRepre;
	m_rsPedido.m_FECHPED = m_timeFecha;
	m_rsPedido.m_CENTRO = m_strCentro.Trim();
	m_rsPedido.m_SREF	= m_strReferencia.Trim();
	m_rsPedido.m_ATENCLI = m_strAtencion.Trim();

	m_rsPedido.m_FCOBRO =	m_datosCobro.m_FCOBRO.Trim();
	m_rsPedido.m_NCOBROS = m_datosCobro.m_NCOBROS;
	m_rsPedido.m_VTO1 = m_datosCobro.m_VTO1;
	m_rsPedido.m_DVTO = m_datosCobro.m_DVTO;
	m_rsPedido.m_DIA1 = m_datosCobro.m_DIA1;
	m_rsPedido.m_DIA2 = m_datosCobro.m_DIA2;
	m_rsPedido.m_DIA3 = m_datosCobro.m_DIA3;
	m_rsPedido.m_RETENFIS = m_datosCobro.m_RETENFIS;
}

/************************************************************************************************************/
void CDlgGestionVentas::LimpiaPedido()
{
	// Se limpian los campos del Pedido
	m_rsPedido.m_NUMPEDIDO.Empty();
	m_rsPedido.m_EXPORTA.Empty();
	m_rsPedido.m_TIPO.Empty();
	m_rsPedido.m_CUENTA.Empty();
	m_rsPedido.m_ALMACEN.Empty();
	m_rsPedido.m_TARIFA.Empty();
	m_rsPedido.m_DCTOS = 0;
	m_rsPedido.m_DCTOS2 = 0;
	m_rsPedido.m_DCTOS3 = 0;
	m_rsPedido.m_PP = 0;
	m_rsPedido.m_GRUFAC.Empty();
	m_rsPedido.m_DIRENV.Empty();
	m_rsPedido.m_REPRE.Empty();
	m_rsPedido.m_SUBREP.Empty();
	m_rsPedido.m_COMISION = 0;
	m_rsPedido.m_COMISION2 = 0;
	m_rsPedido.m_FECHPED = NULL;
	m_rsPedido.m_CENTRO.Empty();
	m_rsPedido.m_SREF.Empty();
	m_rsPedido.m_ATENCLI.Empty();
	m_rsPedido.m_TELEF1.Empty();
	m_rsPedido.m_TELEF2.Empty();
	m_rsPedido.m_FCOBRO.Empty();
	m_rsPedido.m_NCOBROS = 0;
	m_rsPedido.m_VTO1 = 0;
	m_rsPedido.m_DVTO = 0;
	m_rsPedido.m_DIA1 = 0;
	m_rsPedido.m_DIA2 = 0;
	m_rsPedido.m_DIA3 = 0;
	m_rsPedido.m_RETENCOM = 0;
	m_rsPedido.m_RETENFIS = 0;
	m_rsPedido.m_OBSPED.Empty();
	m_bEmitir1 = FALSE;
	m_bEmitir2 = FALSE;
	m_bEmitir3 = FALSE;
	//m_bMovAlmacen = FALSE;

	// Se habilitan los campos desactivados
	m_cCuenta.SetReadOnly(FALSE);
	m_cDtos1.SetReadOnly(FALSE);
	m_cProntoPago.SetReadOnly(FALSE);
	m_cIVA.SetReadOnly(FALSE);
	m_cObra.SetReadOnly(FALSE);
	m_cRepre.SetReadOnly(FALSE);
	m_cSubRepre.SetReadOnly(FALSE);
	m_cComisionRepre.SetReadOnly(FALSE);
	m_cComisionSubRepre.SetReadOnly(FALSE);
	m_cCentro.SetReadOnly(FALSE);
	m_cReferencia.SetReadOnly(FALSE);
	m_cAtn.SetReadOnly(FALSE);

	GetDlgItem(IDC_RB_NACIONAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RB_EXPORTACION)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA2)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_ARTICULOS)->EnableWindow(TRUE);

	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CUENTAREPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CUENTASUBREPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CENTRO)->EnableWindow(TRUE);

	m_cAlmacen.SetReadOnly(FALSE);
	GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(TRUE);
}

/******************************************************************************************/
HRESULT CDlgGestionVentas::GuardaAlbaran()
{
	HRESULT hErr = S_OK;

	CConta rsConta(m_db);
	CArtiAlbaran rsArtiAlbaran(m_db);
	CAlmacen rsAlmacen(m_db);
	CInventario rsInventario(m_db);
	CArtiVenta rsArtiVenta(m_db);

	CString strNextNumAlbaran;

	// Esta función es necesaria para evitar que un artículo que se ha marcado como no disponible
	// por ser Alquiler o Venta, se cambie el combo a tipo Entrega, Recogida u Otros, y ya no 
	// debe ser comprobado. Y para aquellos que no están en la lista pero deberían por ser
	// de Entrega, Recogida u Otros y luego se ha cambiado a Venta o Alquiler
	RevisaArtiDisponibles();

	if (!m_lCodArtiNoDisponible.IsEmpty())
	{
		// Si el albarán no existe y no hay disponibilidad de alguno de los artículos, se avisa de que no se puede 
		// crear el albarán
		if (m_iTipo == ALBARAN)
			AfxMessageBox(IDC_ALBARAN_NO_CREADO);
		else if (m_iTipo == PEDIDO)
		{
			if (!m_bAlbaranPed)
			{
				CString strMsg;
				strMsg.Format(IDC_ALBARANPED_NO_CREADO, m_rsPedido.m_NUMPEDIDO);
				AfxMessageBox(strMsg);

				// Como venimos de pedido todavía no hemos cerrado la transacción
				if (hErr == S_OK)
					m_db->CommitTrans();
			}
			else
			{
				CStringList lAlbaranes;
				lAlbaranes.AddTail(m_rsPedido.m_NUMALB.Trim());
				lAlbaranes.AddTail(ALB_ENTREGA);
				hErr = EliminaAlbaranes(&lAlbaranes, m_strAlmacen);
				if (hErr == S_OK)
				{
					CString strMsg;
					strMsg.Format(IDC_ALBARANPED_ELIMINADO, m_rsPedido.m_NUMPEDIDO, m_rsAlbaran.m_NUMALB);
					AfxMessageBox(strMsg);
				}
			}
		}

		return hErr;
	}

	// Se rellenan los campos del albaran con lo que contienen los editbox
	RellenaAlbaran();

	// Se crea el albarán y luego se insertan cada uno de los artículos que lo componen
	// Si venimos de pedido la transaccion ya está abierta
	if (m_iTipo == ALBARAN)
	{
		if (!m_db->BeginTrans())
			return -1;
	}

	// Si es un nuevo registro se inserta, si ya existe se actualiza y se eliminan todos
	// los artículos que pudiera tener y se insertan los que tiene actualmente
	if (m_bNuevo)
	{
		// Si venimos de un pedido se le asigna el número de pedido
		if (m_iTipo == PEDIDO)
			m_rsAlbaran.m_NUMPEDIDO = m_rsPedido.m_NUMPEDIDO.Trim();

		// Se coge el siguiente número de albarán
		hErr = rsConta.GetNextNumAlbaran(strNextNumAlbaran);

		if (hErr == S_OK)
		{
			m_rsAlbaran.m_NUMALB = strNextNumAlbaran.Trim();
			hErr = m_rsAlbaran.Insert();
		}
	}
	else
	{
		// Si venimos de un pedido se le asigna el número de pedido y de albarán
		if (m_iTipo == PEDIDO)
		{
			m_rsAlbaran.m_NUMPEDIDO = m_rsPedido.m_NUMPEDIDO.Trim();
			m_rsAlbaran.m_NUMALB = m_rsPedido.m_NUMALB.Trim();
		}

		hErr = m_rsAlbaran.UpdateAlbaran();

		// Antes de eliminar los articulos se comprueba si ha habido algún cambio
		// en el tipo de Venta, Alquiler... en este caso se debe devolver al stock
		// las unidades correspondientes
		if (hErr == S_OK)
			hErr = CompruebaCambioTipo();

		// Se eliminan los artículos del albarán
		if (hErr == S_OK)
		{
			rsArtiAlbaran.m_NUMALB = m_rsAlbaran.m_NUMALB;
			hErr = rsArtiAlbaran.DeleteArtiAlbaran();
		}

		// Si venimos de un pedido y es de tipo andamio no se debe crear movimiento de almacén
		if (hErr == S_OK && ActualizaAlmacen())
		{
			rsAlmacen.m_NDOC = atof(m_rsAlbaran.m_NUMALB);
			hErr = rsAlmacen.DeleteMovientosAlbaran();
		}
	}

	if (hErr == S_OK)
	{
		// Si los hay, se actualizan las unidades disponibles de los elementos eliminados que anteriormente
		// ya hayan sido incluidos en el pedido. Sólo se lleva a cabo en el caso de 
		// los artículos que sean de Venta o Alquiler
		for (int i = 0; i < m_lArtiEliminados.GetCount() && hErr == S_OK; i+=3)
		{
			CString strTipo = m_lArtiEliminados.GetAt(m_lArtiEliminados.FindIndex(i+1));

			if (strTipo == "S" || strTipo == "V")
			{
				rsInventario.m_ALMACEN = m_strAlmacen;
				rsInventario.m_ARTI = m_lArtiEliminados.GetAt(m_lArtiEliminados.FindIndex(i));
				
				rsInventario.m_strFilter = "ARTI LIKE '" + rsInventario.m_ARTI + "' AND ALMACEN LIKE '" \
				+ rsInventario.m_ALMACEN + "'";

				if (!rsInventario.Open(CRecordset::dynaset))
					hErr = S_FALSE;

				if (hErr == S_OK)
				{
					rsInventario.m_UNIDISPONIBLE += atoi(m_lArtiEliminados.GetAt(m_lArtiEliminados.FindIndex(i+2)));
					rsInventario.Close();

					hErr = rsInventario.UpdateUniDisponible();

					// Si es Venta también se deben volver a sumar en totales
					if (hErr == S_OK && strTipo == "V")
					{
						rsInventario.m_UNITOTAL += atoi(m_lArtiEliminados.GetAt(m_lArtiEliminados.FindIndex(i+2)));
						hErr = rsInventario.UpdateUniTotal();
					}
				}
			}
		}
	}

	if (hErr == S_OK)
	{	
		int iNumArticulos = m_lstArticulos.GetItemCount();
		// Si la ventana es de sólo lectura, debemos recorrer un registro menos que será
		// el registro vacío
		if (!m_bReadOnly)
			iNumArticulos--;

		for (int i=0; i< iNumArticulos && hErr == S_OK;i++)
		{
			// Se insertan los artículos del albarán
			RellenaArtiAlbaran(&rsArtiAlbaran, i);

			// Sólo se incluyen en el albarán los artículos de venta o de alquiler
			if (rsArtiAlbaran.m_ALQUILER == "S" || rsArtiAlbaran.m_ALQUILER == "V")
			{
				hErr = rsArtiAlbaran.Insert();

				// Se actualiza el número de enviados del pedido
				if (hErr == S_OK && m_iTipo == PEDIDO)
				{
					rsArtiVenta.m_ARTI = rsArtiAlbaran.m_ARTI;
					rsArtiVenta.m_ENVIADOS = rsArtiAlbaran.m_CANTI;
					rsArtiVenta.m_NUMPEDIDO = m_rsPedido.m_NUMPEDIDO;
					hErr = rsArtiVenta.UpdateEnviados();
				}

				// Se actualiza el almacén y el inventario, sólo si el artículo es de
				// Venta o de Alquiler
				//if (hErr == S_OK && (rsArtiAlbaran.m_ALQUILER == "S" || rsArtiAlbaran.m_ALQUILER == "V"))

				// Si venimos de un pedido y es de tipo andamio no se debe crear movimiento de almacén
				// Si estamos en albarán pero si lleva un pedido asociado y es de andamio tampoco se
				// actualiza el almacén
				if (hErr == S_OK && ActualizaAlmacen())
				{
					RellenaAlmacen(&rsAlmacen, &rsInventario, &rsArtiAlbaran, i);
					hErr = rsAlmacen.Insert();

					if (hErr == S_OK)
						hErr = rsInventario.UpdateUniDisponible();

					if (hErr == S_OK && rsArtiAlbaran.m_ALQUILER == "V")
						hErr = rsInventario.UpdateUniTotal();
				}
			}
		}
	}

	// Si todo ha ido bien y el albarán ha sido creado a partir de un pedido, se actualiza
	// el número del nuevo albarán creado en el pedido
	if (hErr == S_OK && m_iTipo == PEDIDO && m_bNuevo)
	{
		m_rsPedido.m_NUMALB = m_rsAlbaran.m_NUMALB;
		hErr = m_rsPedido.UpdateNumAlbaran();
	}

	if (hErr == S_OK)
	{
		m_db->CommitTrans();

		if (m_bNuevo)
		{
			CString strMsg;
			if (m_iTipo == PEDIDO  && !m_bEmitir3) // Si se emite factura todavía no se muestra la ventana)
				strMsg.Format(IDC_PEDIDOALBARAN, m_rsPedido.m_NUMPEDIDO.Trim(), strNextNumAlbaran.Trim()); 
			else if (m_iTipo == ALBARAN)
				strMsg.Format(IDC_CREADO_ALBARAN, strNextNumAlbaran.Trim()); 
			if (!strMsg.IsEmpty())
				AfxMessageBox(strMsg, MB_ICONINFORMATION);
		}
	}
	else
		m_db->Rollback();

	//LimpiaVentana();

	return hErr;
}

/************************************************************************************************************/
void CDlgGestionVentas::RellenaAlbaran()
{
	// si no tiene tipo se considera albarán de entrega
	if (m_rsAlbaran.m_TIPO.Trim().IsEmpty())
		m_rsAlbaran.m_TIPO = ALB_ENTREGA;

	if (m_rsAlbaran.m_TIPOPED.Trim().IsEmpty())
	{		
		if (m_iTipoPedido == TIPO_ANDAMIO)
			m_rsAlbaran.m_TIPOPED = ANDAMIO;
		else if (m_iTipoPedido == TIPO_MAQUINARIA)
			m_rsAlbaran.m_TIPOPED = MAQUINARIA;
	}
		
	if (m_iTipoNacional == 0)
		m_rsAlbaran.m_EXPORTA = "N";
	else if (m_iTipoNacional == 1)
		m_rsAlbaran.m_EXPORTA = "S";

	m_rsAlbaran.m_ESTADO = NO_FACTURADO;

	m_rsAlbaran.m_CUENTA = m_strCuenta.Trim();
	m_rsAlbaran.m_ALMACEN = m_strAlmacen;
	m_rsAlbaran.m_TELEF1 = m_strTelefono.Trim();
	m_rsAlbaran.m_TELEF2 = m_strFax.Trim();
	m_rsAlbaran.m_TARIFA = m_strTarifa.Trim();
	m_rsAlbaran.m_DCTOS = m_dDtos1;
	m_rsAlbaran.m_DCTOS2 = m_dDtos2;
	m_rsAlbaran.m_DCTOS3 = m_dDtos3;
	m_rsAlbaran.m_PP = m_dProntoPago;
	m_rsAlbaran.m_IVA = m_dIVA;
	m_rsAlbaran.m_GRUFAC = m_strGFacturacion.Trim();
	m_rsAlbaran.m_DIRENV = m_strObra.Trim();
	m_rsAlbaran.m_REPRE = m_strRepre.Trim();
	m_rsAlbaran.m_SUBREP = m_strSubRepre.Trim();
	m_rsAlbaran.m_COMISION = m_dComisionRepre;
	m_rsAlbaran.m_COMISION2 = m_dComisionSubRepre;
	m_rsAlbaran.m_FECHALB = m_timeFecha;
	m_rsAlbaran.m_FECHPED = m_timeFecha;

	if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_ENTREGA)
		m_rsAlbaran.m_FECINIALQ = m_timeFecha2;
	else if (m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_RECOGIDA)
		m_rsAlbaran.m_FECFINALQ = m_timeFecha2;

	m_rsAlbaran.m_CENTRO = m_strCentro.Trim();
	m_rsAlbaran.m_SREF	= m_strReferencia.Trim();
	m_rsAlbaran.m_ATENCLI = m_strAtencion.Trim();
	m_rsAlbaran.m_FCOBRO =	m_datosCobro.m_FCOBRO.Trim();
	m_rsAlbaran.m_NCOBROS = m_datosCobro.m_NCOBROS;
	m_rsAlbaran.m_VTO1 = m_datosCobro.m_VTO1;
	m_rsAlbaran.m_DVTO = m_datosCobro.m_DVTO;
	m_rsAlbaran.m_DIA1 = m_datosCobro.m_DIA1;
	m_rsAlbaran.m_DIA2 = m_datosCobro.m_DIA2;
	m_rsAlbaran.m_DIA3 = m_datosCobro.m_DIA3;
	m_rsAlbaran.m_RETENFIS = m_datosCobro.m_RETENFIS;
}

/************************************************************************************************************/
void CDlgGestionVentas::RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila)
{
		rsArtiAlbaran->m_NUMALB = m_rsAlbaran.m_NUMALB;
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
		rsArtiAlbaran->m_IMPOARTI = atof(m_lstArticulos.GetItemText(iFila, 6));
		rsArtiAlbaran->m_DTOARTI = atof(m_lstArticulos.GetItemText(iFila, 7));
		rsArtiAlbaran->m_IVARTI = atof(m_lstArticulos.GetItemText(iFila, 8));
		rsArtiAlbaran->m_DESARMEMO = m_lstArticulos.GetItemText(iFila, 9);
}

/************************************************************************************************************/
void CDlgGestionVentas::RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila)
{
	rsAlmacen->m_NDOC = atof(m_rsAlbaran.m_NUMALB);
	rsAlmacen->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsAlmacen->m_ALMACEN = m_strAlmacen.Trim();
	rsAlmacen->m_FECHA = m_timeFecha;
	rsAlmacen->m_TIPOMOV = GetTipoMov();
	rsAlmacen->m_OBSER = m_rsAlbaran.m_OBSALB.Trim();
	rsAlmacen->m_CUENTA = m_rsAlbaran.m_CUENTA;

	if (m_rsAlbaran.m_TIPO == ALB_ENTREGA || ALB_DESPIECE_ENTREGA)
		rsAlmacen->m_CANTI = - atof(m_lstArticulos.GetItemText(iFila, 5));
	else if (m_rsAlbaran.m_TIPO == ALB_RECOGIDA  || ALB_DESPIECE_RECOGIDA)
		rsAlmacen->m_CANTI = atof(m_lstArticulos.GetItemText(iFila, 5));

	// Se comprueba si en la tabla Inventario está ya el articulo y el almacén o no
	rsInventario->m_strFilter = "ARTI LIKE '" + m_lstArticulos.GetItemText(iFila, 0) + "' AND ALMACEN LIKE '" \
		+ m_strAlmacen + "'";

	if (!rsInventario->Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	// Si no es un pedido sin albarán, se debe compruebar si ya se habían cogido algunas unidades
	// del artículo, si es así deben sumarse al total de unidades disponibles
	int iIniCantidad;
	if (m_iTipo == PEDIDO && !m_bAlbaranPed)
		iIniCantidad = 0;
	else
		iIniCantidad = m_lIniCantidad.GetAt(m_lIniCantidad.FindIndex(iFila));

	// Se actualizan las unidades disponibles del artículo y del almacén
	rsInventario->m_ARTI = m_lstArticulos.GetItemText(iFila, 0);
	rsInventario->m_ALMACEN = m_strAlmacen;
	rsInventario->m_UNIDISPONIBLE = rsInventario->m_UNIDISPONIBLE + iIniCantidad - atol(m_lstArticulos.GetItemText(iFila, 5));

	// Si es una venta también se debe restar del total de artículos
	if (rsArtiAlbaran->m_ALQUILER == "V")
		rsInventario->m_UNITOTAL = rsInventario->m_UNITOTAL  + iIniCantidad - atol(m_lstArticulos.GetItemText(iFila, 5));

	rsAlmacen->m_CANTIDISPONIBLE = rsInventario->m_UNIDISPONIBLE;
	rsAlmacen->m_CANTITOTAL = rsInventario->m_UNITOTAL;

	rsInventario->Close();
}

/******************************************************************************************/
CString CDlgGestionVentas::GetTipoMov()
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
/************************************************************************************************************/
void CDlgGestionVentas::LimpiaAlbaran()
{
	// Se limpian los campos del Albaran
	m_rsAlbaran.m_NUMPEDIDO.Empty();
	m_rsAlbaran.m_NUMALB.Empty();
	m_rsAlbaran.m_EXPORTA.Empty();
	m_rsAlbaran.m_TIPO.Empty();
	m_rsAlbaran.m_TIPOPED.Empty();
	m_rsAlbaran.m_CUENTA.Empty();
	m_rsAlbaran.m_ALMACEN.Empty();
	m_rsProforma.m_ESTADO.Empty();
	m_rsAlbaran.m_TARIFA.Empty();
	m_rsAlbaran.m_DCTOS = 0;
	m_rsAlbaran.m_DCTOS2 = 0;
	m_rsAlbaran.m_DCTOS3 = 0;
	m_rsAlbaran.m_PP = 0;
	m_rsAlbaran.m_GRUFAC.Empty();
	m_rsAlbaran.m_DIRENV.Empty();
	m_rsAlbaran.m_REPRE.Empty();
	m_rsAlbaran.m_SUBREP.Empty();
	m_rsAlbaran.m_COMISION = 0;
	m_rsAlbaran.m_COMISION2 = 0;
	m_rsAlbaran.m_FECHPED = NULL;
	m_rsAlbaran.m_FECHALB = NULL;
	m_rsAlbaran.m_FECINIALQ = NULL;
	m_rsAlbaran.m_CENTRO.Empty();
	m_rsAlbaran.m_SREF.Empty();
	m_rsAlbaran.m_ATENCLI.Empty();
	m_rsAlbaran.m_TELEF1.Empty();
	m_rsAlbaran.m_TELEF2.Empty();
	m_rsAlbaran.m_FCOBRO.Empty();
	m_rsAlbaran.m_NCOBROS = 0;
	m_rsAlbaran.m_VTO1 = 0;
	m_rsAlbaran.m_DVTO = 0;
	m_rsAlbaran.m_DIA1 = 0;
	m_rsAlbaran.m_DIA2 = 0;
	m_rsAlbaran.m_DIA3 = 0;
	m_rsAlbaran.m_RETENCOM = 0;
	m_rsAlbaran.m_RETENFIS = 0;
	m_rsAlbaran.m_OBSPED.Empty();

	//m_bMovAlmacen = TRUE;

	// Se habilitan los campos desactivados
	m_cCuenta.SetReadOnly(FALSE);
	m_cDtos1.SetReadOnly(FALSE);
	m_cProntoPago.SetReadOnly(FALSE);
	m_cIVA.SetReadOnly(FALSE);
	m_cObra.SetReadOnly(FALSE);
	m_cRepre.SetReadOnly(FALSE);
	m_cSubRepre.SetReadOnly(FALSE);
	m_cComisionRepre.SetReadOnly(FALSE);
	m_cComisionSubRepre.SetReadOnly(FALSE);
	m_cCentro.SetReadOnly(FALSE);
	m_cReferencia.SetReadOnly(FALSE);
	m_cAtn.SetReadOnly(FALSE);

	GetDlgItem(IDC_RB_NACIONAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RB_EXPORTACION)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA2)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_ARTICULOS)->EnableWindow(TRUE);

	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CUENTAREPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CUENTASUBREPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CENTRO)->EnableWindow(TRUE);

	m_cAlmacen.SetReadOnly(FALSE);
	GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(TRUE);

	GetDlgItem(IDC_STATIC_FECHA2)->SetWindowText("Fecha inicio alquiler:");

	/*if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA)
		GetDlgItem(IDC_STATIC_FECHA2)->SetWindowText("Fecha inicio alquiler:");
	else if (m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA)
		GetDlgItem(IDC_STATIC_FECHA2)->SetWindowText("Fecha fin alquiler:");				*/

}

/************************************************************************************************************/
HRESULT CDlgGestionVentas::EliminaAlbaranes(CStringList *lAlbaran, CString strAlmacen)
{
	HRESULT hErr = S_OK;
	CInventario rsInventario(m_db);
	CArtiAlbaran rsArtiAlbaran(m_db);
	CArtiVenta rsArtiVenta(m_db);
	CAlmacen rsAlmacen(m_db);

	// Está ya abierta la transaccion puesto que venimos de GuardaPedido y no se ha hecho
	// commit ni rollback
	//if (!m_db->BeginTrans())
	//	return -1;

	for (int iIndex=0; iIndex<lAlbaran->GetCount() && hErr == S_OK; iIndex+=2)
	{
		m_rsAlbaran.m_NUMALB = lAlbaran->GetAt(lAlbaran->FindIndex(iIndex));
		m_rsAlbaran.m_NUMALB = m_rsAlbaran.m_NUMALB.Trim();
		m_rsAlbaran.m_TIPO = lAlbaran->GetAt(lAlbaran->FindIndex(iIndex+1));
		
		// Se elimina el albarán de la tabla
		hErr = m_rsAlbaran.DeleteAlbaran();

		// Se actualiza el inventario, devolviendo las unidades que se habían cogido de cada
		// articulo.
		rsArtiAlbaran.m_strFilter = "NUMALB = '" + m_rsAlbaran.m_NUMALB + "'";
		if (!rsArtiAlbaran.Open(CRecordset::dynaset))
			hErr = -1;

		if (hErr == S_OK)
		{
			for (int i=0; i<rsArtiAlbaran.GetRecordCount() && hErr == S_OK; i++)
			{
				// Si es de Recogida siempre se actualiza el inventario porque sólo están
				// los articulos alquilados. Si es de Entrega sólo se actualiza el 
				// inventario si es Alquiler o Venta
				CString strTipo = rsArtiAlbaran.m_ALQUILER.Trim();

				if (((m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_ENTREGA) && (strTipo == "S" || strTipo == "V"))
					|| m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_RECOGIDA)
				{
					rsInventario.m_strFilter = "ARTI = '" + rsArtiAlbaran.m_ARTI.Trim() + "' AND ALMACEN = '" + strAlmacen + "'";
					if (!rsInventario.Open(CRecordset::dynaset))
						hErr = -1;
					
					if (hErr == S_OK)
					{		
						if (!rsInventario.m_ARTI.IsEmpty())
						{							
							if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_ENTREGA)
								rsInventario.m_UNIDISPONIBLE += (int)rsArtiAlbaran.m_CANTI;
							else if (m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA || m_rsAlbaran.m_TIPO.Trim() == ALB_DESPIECE_RECOGIDA)
								rsInventario.m_UNIDISPONIBLE -= (int)rsArtiAlbaran.m_CANTI;

							hErr = rsInventario.UpdateUniDisponible();

							if (hErr == S_OK && m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA && strTipo == "V")
							{
								rsInventario.m_UNITOTAL += (int)rsArtiAlbaran.m_CANTI;
								hErr = rsInventario.UpdateUniTotal();
							}
						}
					}

					rsInventario.Close();
				}

				rsArtiVenta.m_NUMPEDIDO = m_rsPedido.m_NUMPEDIDO;
				rsArtiVenta.m_ARTI = rsArtiAlbaran.m_ARTI.Trim();

				// Si es de entrega se inicializan a 0 los enviados del Pedido
				if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA)
				{
					rsArtiVenta.m_ENVIADOS = 0;
					hErr = rsArtiVenta.UpdateEnviados();
				}
				// Si es de recogida se inicializan a 0 los recogidos
				else if (m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA)
				{
					rsArtiVenta.m_RECOGIDOS = 0;
					hErr = rsArtiVenta.UpdateRecogidos();
				}

				rsArtiAlbaran.MoveNext();
			}

			rsArtiAlbaran.Close();
		}

		// Se eliminan los artículos del albarán
		if (hErr == S_OK)
		{
			rsArtiAlbaran.m_NUMALB = m_rsAlbaran.m_NUMALB;
			hErr = rsArtiAlbaran.DeleteArtiAlbaran();
		}

		// Se eliminan los movimientos de albarán del albarán
		if (hErr == S_OK)
		{
			rsAlmacen.m_NDOC =  atof(m_rsAlbaran.m_NUMALB);
			hErr = rsAlmacen.DeleteMovientosAlbaran();
		}
	}

	// Se actualiza a vacío el campo albarán del pedido
	if (hErr == S_OK && lAlbaran->GetCount()>0)
	{
		m_rsPedido.m_NUMALB.Empty();
		hErr = m_rsPedido.UpdateNumAlbaran();
	}

	if (hErr == S_OK)
		m_db->CommitTrans();
	else
		m_db->Rollback();

	return hErr;

}

/************************************************************************************************************/
BOOL CDlgGestionVentas::BuscaAlbaranes(CStringList *lAlbaranes)
{
	BOOL bExists = FALSE;

	CAlbaran rsAlbaran(m_db);

	rsAlbaran.m_strFilter = "NUMPEDIDO LIKE '" + m_rsPedido.m_NUMPEDIDO + "'";
	if (!rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	while (!rsAlbaran.IsEOF())
	{
		lAlbaranes->AddTail(rsAlbaran.m_NUMALB);
		lAlbaranes->AddTail(rsAlbaran.m_TIPO);

		// Se aprovecha para inicializar la fecha de Inicio de Alquiler del albarán. Si hubiera
		// más de uno este dato no sirve para nada porque se borran todos. Sirve para cuando hay
		// un único albarán.
		m_timeFecha2 = rsAlbaran.m_FECINIALQ;

		rsAlbaran.MoveNext();
	}

	// Si al menos hay 2 albaranes para el pedido se indica con el flag
	if ((lAlbaranes->GetCount()/2) >= 2)
		bExists = TRUE;

	return bExists;
}

/************************************************************************************************************/
HRESULT CDlgGestionVentas::CompruebaCambioTipo()
{
	HRESULT hErr = S_OK;

	CArtiAlbaran rsArtiAlbaran(m_db);
	CInventario rsInventario(m_db);

	CString strOldTipo, strNewTipo;
	for (int iIndex=0; iIndex<m_lstArticulos.GetItemCount()-1; iIndex++)
	{
		strOldTipo = m_lIniTipo.GetAt(m_lIniTipo.FindIndex(iIndex));

		// Si está vacío es que es un nuevo elemento que no fue guardado anteriormente
		if (strOldTipo.IsEmpty())
			continue;

		// Se busca el actual tipo
		POSITION pos = m_strTipo.Find(m_lstArticulos.GetItemText(iIndex, 3));	
		if (pos != NULL)
		{
			m_strTipo.GetPrev(pos);
			strNewTipo = m_strTipo.GetPrev(pos);
		}
		else
			strNewTipo.Empty();

		if (strOldTipo != strNewTipo)
		{
			// Si el tipo antiguo era Alquiler se deben sumar las unidades a los articulos
			// disponibles, y si es Venta a los disponibles y a los totales
			if (strOldTipo == "S" || strOldTipo == "V")
			{
				rsInventario.m_ARTI.Empty();
				rsInventario.m_strFilter = "ARTI LIKE '" + m_lstArticulos.GetItemText(iIndex, 0) + 
					"' AND ALMACEN LIKE '" + m_strAlmacen + "'";
				if (!rsInventario.Open(CRecordset::dynaset))
				{	
					AfxMessageBox(IDC_ERROR_BD);
					return S_FALSE;
				}

				if (!rsInventario.m_ARTI.IsEmpty())
				{
					rsInventario.m_UNIDISPONIBLE += m_lIniCantidad.GetAt(m_lIniCantidad.FindIndex(iIndex));;
					hErr = rsInventario.UpdateUniDisponible();

					// Si es Venta también se deben volver a sumar en totales
					if (hErr == S_OK && strOldTipo == "V")
					{
						rsInventario.m_UNITOTAL += m_lIniCantidad.GetAt(m_lIniCantidad.FindIndex(iIndex));
						hErr = rsInventario.UpdateUniTotal();
					}
				}

				rsInventario.Close();
			}

			// Se inicializa a 0 la cantidad de articulos que ya estaban pedidos
			m_lIniCantidad.SetAt(m_lIniCantidad.FindIndex(iIndex), 0);
		}
	}

	return hErr;
}

/************************************************************************************************************/
void CDlgGestionVentas::RevisaArtiDisponibles()
{
	CString strTipo;

	// Se eliminan de la lista los elementos cuyo tipo actual sea Recogida, Entrega u Otros
	// Se recorre la lista de atrás adelante para que no haya problemas al eliminar
	for (int i=(int)m_lCodArtiNoDisponible.GetCount()-1; i>=0; i--)
	{
		// Se busca el código en la lista para obtener su tipo actual
		LVFINDINFO info;
		int iFila;
	
		info.flags = LVFI_STRING | LVFI_WRAP;
		info.psz = m_lCodArtiNoDisponible.GetAt(m_lCodArtiNoDisponible.FindIndex(i));
		iFila = m_lstArticulos.FindItem(&info);
		if ( iFila != -1)
		{
			strTipo = m_lstArticulos.GetItemText(iFila, 3);
			if (strTipo == RECOGIDA || strTipo == ENTREGA || strTipo == OTROS)
				m_lCodArtiNoDisponible.RemoveAt(m_lCodArtiNoDisponible.FindIndex(i));
		}

	}
}

/************************************************************************************************************/
BOOL CDlgGestionVentas::ActualizaAlmacen()
{
	BOOL bActualiza = FALSE;

	// Si es un pedido y es de tipo ANDAMIO no se actualiza el almacén
	if (m_iTipo == PEDIDO)
	{
		if (m_iTipoPedido == TIPO_ANDAMIO)
			bActualiza = FALSE;
		else
			bActualiza = TRUE;
	}
	else if (m_iTipo == ALBARAN)
	{
		// Si no tiene pedido asociado, dependerá de qué tipo se seleccione
		if (m_rsAlbaran.m_NUMPEDIDO.Trim().IsEmpty())
		{
			if (m_iTipoPedido == TIPO_ANDAMIO)
				bActualiza = FALSE;
			else if (m_iTipoPedido == TIPO_MAQUINARIA)
				bActualiza = TRUE;
		}
		
		else
		{
			if (m_rsAlbaran.m_TIPOPED.Trim() == ANDAMIO)
				bActualiza = FALSE;
			else
				bActualiza = TRUE;
		}

		/*// Si no va asociado a ningún pedido se debe actualizar siempre
		if (m_rsAlbaran.m_NUMPEDIDO.Trim().IsEmpty())
			return TRUE;
		// Si va asociado se debe comprobar el tipo de pedido (andamio o maquinaria)
		else
		{
			m_rsPedido.m_strFilter = "NUMPEDIDO = " + m_rsAlbaran.m_NUMPEDIDO.Trim();
			if (!m_rsPedido.Open(CRecordset::dynaset))
			{
				AfxMessageBox(IDC_ERROR_BD);
				return FALSE;
			}

			// Si el pedido es de Maquinaria lleva movimiento de almacén. Si no, si es
			// un albarán de despiece llevará movimiento, si no no.
			if (!m_rsPedido.m_NUMPEDIDO.IsEmpty())
			{
				if (m_rsPedido.m_TIPO.Trim() == ANDAMIO)
				{
					if (m_rsAlbaran.m_TIPO.Trim() == ALB_ENTREGA || m_rsAlbaran.m_TIPO.Trim() == ALB_RECOGIDA)
						bActualiza = FALSE;
					else
						bActualiza = TRUE;
				}
				else if (m_rsPedido.m_TIPO.Trim() == MAQUINARIA)
					bActualiza = TRUE;
			}

			m_rsPedido.Close();
		}*/
	}

	return bActualiza;
}



