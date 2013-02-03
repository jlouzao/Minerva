/*************************************************************************************/
// MinervaDlg.cpp: archivo de implementación
/*************************************************************************************/

#include "stdafx.h"
#include "Minerva.h"
#include "MinervaDlg.h"
#include "DlgEmpresas.h"
#include "DlgEjercicio.h"
#include ".\minervadlg.h"
#include "admin.h"
#include "DlgUsuario.h"
#include "GestionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Fuente de datos
#define DATA_SOURCE  "minerva"

// Perfiles de usuarios
#define ID_SUPERUSUARIO  1
#define ID_COMERCIAL     2
#define ID_PRODUCCION    3
#define ID_ALMACEN       4
#define ID_FACTURACION   5

/*************************************************************************************/
// Cuadro de diálogo de CMinervaDlg
/*************************************************************************************/

/*************************************************************************************/
CMinervaDlg::CMinervaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMinervaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

/*************************************************************************************/
CMinervaDlg::~CMinervaDlg()
{
	if (m_db.IsOpen())
		m_db.Close();
}

/*************************************************************************************/
void CMinervaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

/*************************************************************************************/
BEGIN_MESSAGE_MAP(CMinervaDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_ADM_CREARUSUARIO, OnAdmCrearusuario)
	ON_COMMAND(ID_UTIL_CAMBIAREMPRESA, OnUtilCambiarempresa)
	ON_COMMAND(ID_GESTI_GESTI, OnGestiGesti)
	ON_COMMAND(ID_ALMACEN_REGULARIZACIONES, OnAlmacenRegularizaciones)
	ON_COMMAND(ID_GESTI_GESTI32799, OnGestiGestiFamilia)
	ON_COMMAND(ID_GESTI_GESTI32800, OnGestiGestiSubFamilia)
	ON_COMMAND(ID_ALMACEN_TRANSFERENCIASALMAC, OnAlmacenTransferencias)
	ON_COMMAND(ID_GESTI_GESTI32803, OnGestionCuentas)
	ON_COMMAND(ID_EXISTENCIAS_EXISTENCIASPORART, OnAlmacenExistenciasPorArticulo)
	ON_COMMAND(ID_VENTAS_GESTIONOFERTAS, OnVentasGestionOfertas)
	ON_COMMAND(ID_VENTAS_GESTION_PEDIDOS, OnVentasGestionPedidos)
	ON_COMMAND(ID_VENTAS_ACEPTA_OFERTA, OnVentasAceptaOferta)
	ON_COMMAND(ID_GESTION_IDIOMAS, OnGestionIdiomas)
	ON_COMMAND(ID_GESTION_PAISES, OnGestionPaises)
	ON_COMMAND(ID_GESTION_DIVISAS, OnGestionDivisas)
	ON_COMMAND(ID_GESTION_ZONAS, OnGestionZonas)
	ON_COMMAND(ID_GESTION_SEGUROS, OnGestionSeguros)
	ON_COMMAND(ID_GESTION_CONCEPTOS, OnGestionConceptos)
	ON_COMMAND(ID_GESTION_RUTRANS, OnGestionRutrans)
	ON_COMMAND(ID_GESTION_GESTIONDEFORMASDEPAGO, OnGestionGestiondeformasdepago)
	ON_COMMAND(ID_GESTION_CENTROS, OnGestionCentros)
	ON_COMMAND(ID_VENTAS_GESTION_ALBARANES, OnVentasGestionAlbaranes)
	//ON_COMMAND(ID_COMPRAS_GESTION, OnComprasGestion)
	//ON_COMMAND(ID_COMPRAS_ALBARANES, OnComprasAlbaranes)
	ON_COMMAND(ID_VENTAS_PREALBARANES, OnVentasPrealbaranes)
	ON_COMMAND(ID_GESTIONALBARANES_RECEPCI, OnGestionalbaranesRecepci)
	ON_COMMAND(ID_GESTI_GESTIONCOMPRA, OnGestiGestioncompra)
	ON_COMMAND(ID_GESTIONALBARANES_GESTIONALBARANES, OnGestionalbaranesGestionalbaranes)
	ON_COMMAND(ID_VENTAS_ALTA_OBRAS, OnVentasAltaObras)
	ON_COMMAND(ID_VENTAS_CIERRE_OBRAS, OnVentasCierreObras)
	ON_COMMAND(ID_VENTAS_CONSULTA_OBRA, OnVentasConsultaObra)
	ON_COMMAND(ID_VENTAS_FACTURACION, OnVentasFacturacion)
	ON_COMMAND(ID_VENTAS_MODIFICAFACTURAS, OnVentasModificafacturas)
	ON_COMMAND(ID_VENTAS_CALENDARIOLABORAL, OnVentasCalendariolaboral)
	ON_COMMAND(ID_VENTAS_EMITIR_OFERTAS, OnVentasEmitirOfertas)
	ON_COMMAND(ID_VENTAS_EMITIR_PEDIDOS, OnVentasEmitirPedidos)
	ON_COMMAND(ID_VENTAS_EMITIR_ALBARANES, OnVentasEmitirAlbaranes)
	ON_COMMAND(ID_VENTAS_EMITIR_FACTURAS, OnVentasEmitirFacturas)
	ON_COMMAND(ID_VENTAS_EMITIR_FACTURAS_ORIGEN, OnVentasEmitirFacturasOrigen)
	ON_COMMAND(ID_GESTION_MODIFICACION_COBRO, OnGestionModificacionCobro)
	ON_COMMAND(ID_GESTION_NUEVOCOBRO, OnGestionNuevocobro)
	ON_COMMAND(ID_COBROS_INTRO_COBROS, OnCobrosIntroCobros)
	ON_COMMAND(ID_RECEPCIONDEFACTURAS, OnRecepciondefacturas)
	ON_COMMAND(ID_COBROS_RECEP_ACEPTOS, OnCobrosRecepAceptos)
	ON_COMMAND(ID_COBROS_INFORMES, OnCobrosInformes)
END_MESSAGE_MAP()

/*************************************************************************************/
// Controladores de mensaje de CMinervaDlg
/*************************************************************************************/
BOOL CMinervaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	ShowWindow(SW_MAXIMIZE);

	IniciarEmpresa();

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

/*************************************************************************************/
// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CMinervaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/*************************************************************************************/
// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CMinervaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************************************/
void CMinervaDlg::InicializaConexiones()
{
	m_administracion.Init(&m_db, this);
	m_referencias.Init(&m_db, this);
	m_almacen.Init(&m_db, this);
	m_gestionCuentas.Init(&m_db, this);
	m_ventas.Init(&m_db, this);
	m_compras.Init(&m_db, this);
	m_cobros.Init(&m_db, this);
}

/*************************************************************************************/
// MENÚ ADMINISTRACIÓN
/*************************************************************************************/
void CMinervaDlg::OnAdmCrearusuario()
{
	m_administracion.GestionUsuarios();	
}

/*************************************************************************************/
// MENÚ UTILIDADES
/*************************************************************************************/
void CMinervaDlg::OnUtilCambiarempresa()
{
	IniciarEmpresa();
}

/*************************************************************************************/
// MENÚ REFERENCIAS
/*************************************************************************************/
void CMinervaDlg::OnGestiGesti()
{
	m_referencias.GestionReferencia();
}
/*************************************************************************************/
void CMinervaDlg::OnGestiGestiFamilia()
{
	m_referencias.GestionFamilia();
}

/*************************************************************************************/
void CMinervaDlg::OnGestiGestiSubFamilia()
{
	m_referencias.GestionSubFamilia();
}

/*************************************************************************************/
// MENÚ ALMACEN
/*************************************************************************************/

/*************************************************************************************/
void CMinervaDlg::OnAlmacenExistenciasPorArticulo()
{
	m_almacen.ExistenciasPorArticulo();
}

/*************************************************************************************/
void CMinervaDlg::OnAlmacenRegularizaciones()
{
	m_almacen.Regularizaciones();
}

/*************************************************************************************/
void CMinervaDlg::OnAlmacenTransferencias()
{
	m_almacen.Transferencias();
}

/*************************************************************************************/
// MENÚ GESTION CUENTAS
/*************************************************************************************/
void CMinervaDlg::OnGestionCuentas()
{
	m_gestionCuentas.GestionCuentas();
}
/********************************************************************/
void CMinervaDlg::OnGestionIdiomas()
{
	CDlgIdiomas rsIdiomas;
	rsIdiomas.SetUpdate(FALSE);
	rsIdiomas.SetConexion(&m_db);
	rsIdiomas.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionPaises()
{
	CDlgPais rsPais;
	rsPais.SetUpdate(FALSE);
	rsPais.SetConexion(&m_db);
	rsPais.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionDivisas()
{
	CDlgDivisas rsDivisa;
	rsDivisa.SetUpdate(FALSE);
	rsDivisa.SetConexion(&m_db);
	rsDivisa.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionZonas()
{
	CDlgZona rsZona;
	rsZona.SetUpdate(FALSE);
	rsZona.SetConexion(&m_db);
	rsZona.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionSeguros()
{
	CDlgSeguros rsSeguro;
	rsSeguro.SetUpdate(FALSE);
	rsSeguro.SetConexion(&m_db);
	rsSeguro.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionConceptos()
{
	CDlgConcepto rsConcepto;
	rsConcepto.SetUpdate(FALSE);
	rsConcepto.SetConexion(&m_db);
	rsConcepto.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionRutrans()
{
	CDlgRutran rsRutran;
	rsRutran.SetUpdate(FALSE);
	rsRutran.SetConexion(&m_db);
	rsRutran.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionGestiondeformasdepago()
{
	CDlgFPagCob rsFPagCob;
	rsFPagCob.SetUpdate(FALSE);
	rsFPagCob.SetConexion(&m_db);
	rsFPagCob.DoModal();
}
/********************************************************************/
void CMinervaDlg::OnGestionCentros()
{
	CDlgCentros rsCentro;
	rsCentro.SetUpdate(FALSE);
	rsCentro.SetConexion(&m_db);
	rsCentro.DoModal();
}
/*************************************************************************************/
// MENÚ VENTAS
/*************************************************************************************/
void CMinervaDlg::OnVentasGestionOfertas()
{
	m_ventas.GestionOfertas();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasAceptaOferta()
{
	m_ventas.AceptaOferta();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasGestionPedidos()
{
	m_ventas.GestionPedidos();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasGestionAlbaranes()
{
	m_ventas.GestionAlbaranes();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasPrealbaranes()
{
	m_ventas.PreparacionAlbaranes();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasAltaObras()
{
	m_ventas.AltaModObra();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasCierreObras()
{
	m_ventas.CierreObra();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasConsultaObra()
{
	m_ventas.ConsultaObra();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasFacturacion()
{
	m_ventas.Facturacion();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasModificafacturas()
{
	m_ventas.ModificaFactura();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasCalendariolaboral()
{
	m_ventas.CalendarioLaboral();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasEmitirOfertas()
{
	m_ventas.EmitirOfertas();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasEmitirPedidos()
{
	m_ventas.EmitirPedidos();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasEmitirAlbaranes()
{
	m_ventas.EmitirAlbaranes();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasEmitirFacturas()
{
	m_ventas.EmitirFacturas();
}

/*************************************************************************************/
void CMinervaDlg::OnVentasEmitirFacturasOrigen()
{
	m_ventas.EmitirFacturasOrigen();
}

/*************************************************************************************/
// MENÚ COMPRAS
/*************************************************************************************/
void CMinervaDlg::OnGestiGestioncompra()
{
	m_compras.GestionCompras();
}
/*************************************************************************************/
void CMinervaDlg::OnGestionalbaranesGestionalbaranes()
{
	m_compras.GestionAlbaranes();
}
/*************************************************************************************/
void CMinervaDlg::OnGestionalbaranesRecepci()
{
	m_compras.GestionPedidos();
}
/*************************************************************************************/
void CMinervaDlg::OnRecepciondefacturas()
{
	m_compras.GestionFacturas();
}
/*************************************************************************************/
// MENÚ COBROS
/*************************************************************************************/
void CMinervaDlg::OnGestionModificacionCobro()
{
	m_cobros.ModificacionCobro();
}

/*************************************************************************************/
void CMinervaDlg::OnGestionNuevocobro()
{
	m_cobros.NuevoCobro();
}

/*************************************************************************************/
void CMinervaDlg::OnCobrosIntroCobros()
{
	m_cobros.IntroCobros();
}

/*************************************************************************************/
void CMinervaDlg::OnCobrosRecepAceptos()
{
	m_cobros.RecepAceptos();
}

/*************************************************************************************/
void CMinervaDlg::OnCobrosInformes()
{
	m_cobros.InformeCobros();
}

/*************************************************************************************/
/* FUNCIONES                                                                         */
/*************************************************************************************/

void CMinervaDlg::IniciarEmpresa()
{
	INT_PTR cerrar;           //Para comprobar si se debe cerrar todo el programa
	BOOL bPrimeraVez = TRUE;

	/* Si ya hay una conexión de base de datos abierta es porque no es la primera vez que
	   se llama a esta función de selección de empresa y ejercicio */
	if (m_db.IsOpen())
		bPrimeraVez = FALSE;

	/* Se selecciona la empresa */
	CDlgEmpresas dlgEmpresas;                        //Creamos y llamamos al dialogo Empresas
	dlgEmpresas.SetPrimeraVez(bPrimeraVez); //Indica si es la primera vez que se muestra el diálogo
	                                        //Si es así, al pulsar Cancelar se abandona la aplicación.                                     
	cerrar = dlgEmpresas.DoModal();
 	m_strIdEmpresa = dlgEmpresas.GetIdEmpresa();     //recogemos el identificador de empresa
	m_strNombreEmpresa = dlgEmpresas.GetNombreEmpresa();
	//comprueba si debe cerrar el programa
	if (cerrar == IDCANCEL && bPrimeraVez)
	{
		OnCancel();
		return;
		
	} 
	// Se cierra la ventana empresa pero no el programa
	else if (cerrar == IDCANCEL && !bPrimeraVez)
		return;

	/* Se selecciona el ejercicio */
	CDlgEjercicio dlgEjercicio;               //Creamos y llamamos al dialogo Ejercicio
	dlgEjercicio.SetEmpresa(m_strIdEmpresa);  //Enviamos el identificador de empresa
	dlgEjercicio.SetPrimeraVez(bPrimeraVez); //Indica si es la primera vez que se muestra el diálogo
	                                         //Si es así, al pulsar Cancelar se abandona la aplicación.                                     
	cerrar = (BOOL)dlgEjercicio.DoModal();
	//comprueba si debe cerrar el programa
	if (cerrar == IDCANCEL && bPrimeraVez)
	{
		OnCancel();
		return;
	} 
	 // Se cierra la ventana ejercicio pero no el programa
	else if (cerrar == IDCANCEL && !bPrimeraVez)
		return;
	
	/* Se conecta a la base de datos correspondiente a la empresa seleccionada */	
	CString strConnect;
	strConnect.Format("DSN=%s;DATABASE=%s", DATA_SOURCE, m_strIdEmpresa);

	/* Si la conexión ya ha sido iniciada anteriormente por otra empresa se cierra */
	if (m_db.IsOpen())
		m_db.Close();

	if (!m_db.OpenEx(strConnect))
	{
		AfxMessageBox(IDC_ERROR_BD);//mensaje de error
		return;
	}

	/* Se indica en el título de la ventana la Base de Datos */
	SetWindowText("Minerva Gestión  -  " + m_strNombreEmpresa);

	/* Se inicializa en el resto de las clases la conexión a la Base de Datos */
	InicializaConexiones();

	/* Se pide el usuario de conexión */
	CDlgUsuario dlgUsuario;
	dlgUsuario.SetConexion(&m_db);
	dlgUsuario.SetPrimeraVez(bPrimeraVez); //Indica si es la primera vez que se muestra el diálogo
	                                         //Si es así, al pulsar Cancelar se abandona la aplicación.                                     
	cerrar = (BOOL)dlgUsuario.DoModal();
	//comprueba si debe cerrar el programa
	if (cerrar==IDCANCEL && bPrimeraVez)
	{
		OnCancel();
		return;
	}
	// Se cierra la ventana usuario pero no el programa
	else if (cerrar == IDCANCEL && !bPrimeraVez)
		return;

	m_strUsuario = dlgUsuario.GetUsuario();
	m_iPerfil = dlgUsuario.GetPerfil();;

	/* Se carga el menú correspondiente según el perfil del usuario */
	UINT uiPerfil;
	switch (m_iPerfil)
	{
		case ID_SUPERUSUARIO:
			uiPerfil = IDR_MENU_SUPERUSUARIO;
			break;
		case ID_COMERCIAL:
			uiPerfil = IDR_MENU_COMERCIAL;
			break;
		case ID_PRODUCCION:
			uiPerfil = IDR_MENU_PRODUCCION;
			break;
		case ID_ALMACEN:
			uiPerfil = IDR_MENU_ALMACEN;
			break;
		case ID_FACTURACION:
			uiPerfil = IDR_MENU_FACTURACION;
			break;		
		default:
			uiPerfil = -1;
			break;
	}

	if (uiPerfil != -1)
	{
		CMenu menu;
		menu.LoadMenu(uiPerfil);
		SetMenu(&menu);
	}

	return;
}

