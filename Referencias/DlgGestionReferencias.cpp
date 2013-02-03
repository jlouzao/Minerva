.// DlgGestionReferencias.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgGestionReferencias.h"
#include ".\dlggestionreferencias.h"
#include "DlgTarifasVentas.h"
#include "DlgTarifasCompras.h"
#include "DlgProveedores.h"
#include "BD.h"


// Cuadro de diálogo de CDlgGestionReferencias

IMPLEMENT_DYNAMIC(CDlgGestionReferencias, CDialog)
CDlgGestionReferencias::CDlgGestionReferencias(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGestionReferencias::IDD, pParent)
	, m_strCodReferencia(_T(""))
	, m_strNombre(_T(""))
	, m_strNombreLargo(_T(""))
	, m_strDescripcion(_T(""))
	, m_strFamilia(_T(""))
	, m_strDesFamilia(_T(""))
	, m_strDesSubfami(_T(""))
	, m_strSubfami(_T(""))
	, m_strCuentasventa(_T(""))
	, m_strCuentascompra(_T(""))
	, m_strPuntoVerde(_T(""))
	, m_strIVA(_T(""))
	, m_strRecargo(_T(""))
	, m_strPeso(_T(""))
	, m_strMinimo(_T(""))
	, m_timeBaja(0)
	, m_chMovAlmacen(_T("Si"))
	, m_chAlquilado(_T("No"))
	, m_strDesCompras(_T(""))
	, m_strDesVentas(_T(""))
	, bInicial(TRUE)
	,bUpdate(FALSE)
	,m_timeAlta(CTime::GetCurrentTime())
{
}

CDlgGestionReferencias::~CDlgGestionReferencias()
{
	m_rsArticulo.Close();
}

void CDlgGestionReferencias::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDT_COD_REFERENCIA, m_strCodReferencia);
		DDV_MaxChars(pDX, m_strCodReferencia, 15);
	DDX_Text(pDX, IDT_NOMBRE, m_strNombre);
		DDV_MaxChars(pDX, m_strNombre, 100);
	DDX_Text(pDX, IDT_NOMBRE_LARGO, m_strNombreLargo);
		DDV_MaxChars(pDX, m_strDescripcion, 225);
//	DDX_Text(pDX, IDT_DESCRIPCION, m_strDescripcion);
//		DDV_MaxChars(pDX, m_strDescripcion, 35);
	DDX_Text(pDX, IDT_FAMILIA, m_strFamilia);
		DDV_MaxChars(pDX, m_strFamilia, 3);
	DDX_Text(pDX, IDT_FAM_DES, m_strDesFamilia);
	DDX_Text(pDX, IDT_SUBFAMILIA, m_strSubfami);
		DDV_MaxChars(pDX, m_strSubfami, 3);
	DDX_Text(pDX, IDT_SUBFAM_DES, m_strDesSubfami);
	DDX_Text(pDX, IDT_CUENTAS_VENTAS, m_strCuentasventa);
		//DDV_MaxChars(pDX, m_strCuentasventa, 3);
	DDX_Text(pDX, IDT_CUENTAS_COMPRAS, m_strCuentascompra);
		//DDV_MaxChars(pDX, m_strCuentascompra, 3);
	DDX_Text(pDX, IDT_PUNTOVERDE, m_strPuntoVerde);
	DDX_Text(pDX, IDT_IVA, m_strIVA);
	DDX_Text(pDX, IDT_RECARGO, m_strRecargo);
	DDX_Text(pDX, IDT_PESO, m_strPeso);
	DDX_Text(pDX, IDT_MINIMO, m_strMinimo);
	DDX_DateTimeCtrl(pDX, IDF_FECHA_ALTA, m_timeAlta);
	DDX_DateTimeCtrl(pDX, IDF_FECHA_BAJA, m_timeBaja);
	DDX_CBString(pDX, IDCOM_MOV_ALMACEN, m_chMovAlmacen);
	DDX_CBString(pDX, IDCOM_ALQUILADO, m_chAlquilado);
	DDX_Control(pDX, IDCOM_MOV_ALMACEN, m_ctrlMovAlmacen);
	DDX_Control(pDX, IDCOM_ALQUILADO, m_ctrlAlquilado);
	DDX_Control(pDX, IDT_COD_REFERENCIA, m_ctrlCodReferencia);
	DDX_Text(pDX, IDC_DES_COMPRAS, m_strDesCompras);
	DDX_Text(pDX, IDC_DES_VENTAS, m_strDesVentas);
	DDX_Control(pDX, IDT_FAMILIA, m_ctrlFam);
	DDX_Control(pDX, IDT_SUBFAMILIA, m_ctrlSubFam);
	DDX_Control(pDX, IDT_CUENTAS_VENTAS, m_ctrlVentas);
	DDX_Control(pDX, IDT_CUENTAS_COMPRAS, m_ctrlCompras);
	DDX_Control(pDX, IDT_NOMBRE, m_ctrlNombre);
	DDX_Control(pDX, IDT_NOMBRE_LARGO, m_ctrlNombreLargo);
	//DDX_Control(pDX, IDT_DESCRIPCION, m_ctrlDescripcion);
	DDX_Control(pDX, IDT_PUNTOVERDE, m_ctrlPuntoVerde);
	DDX_Control(pDX, IDT_IVA, m_ctrlIVA);
	DDX_Control(pDX, IDT_RECARGO, m_ctrlRecargo);
	DDX_Control(pDX, IDT_PESO, m_ctrlPeso);
}


BEGIN_MESSAGE_MAP(CDlgGestionReferencias, CDialog)
	ON_BN_CLICKED(IDB_BUSQUEDA_REFERENCIA, OnBnClickedBusquedaReferencia)
	ON_BN_CLICKED(IDB_CANCELAR, OnBnClickedCancelar)
	ON_BN_CLICKED(IDB_NUEVO, OnBnClickedNuevo)
	ON_BN_CLICKED(IDB_BUSQUEDA_FAMILIAS, OnBnClickedBusquedaFamilias)
	ON_BN_CLICKED(IDB_BUSQUEDA_SUBFAMILIAS, OnBnClickedBusquedaSubfamilias)
	ON_BN_CLICKED(IDB_BUSQUEDA_CUENTAS_VENTAS, OnBnClickedBusquedaCuentasVentas)
	ON_BN_CLICKED(IDB_BUSQUEDA_CUENTAS_COMPRAS, OnBnClickedBusquedaCuentasCompras)
	ON_EN_KILLFOCUS(IDT_COD_REFERENCIA, OnEnKillfocusCodReferencia)
	ON_BN_CLICKED(IDB_TARIFAS_VENTAS, OnBnClickedTarifasVentas)
	ON_BN_CLICKED(IDB_ACEPTAR, OnBnClickedAceptar)
	ON_EN_KILLFOCUS(IDT_FAMILIA, OnEnKillfocusFamilia)
	ON_EN_KILLFOCUS(IDT_SUBFAMILIA, OnEnKillfocusSubfamilia)
	ON_EN_KILLFOCUS(IDT_CUENTAS_VENTAS, OnEnKillfocusCuentasVentas)
	ON_EN_KILLFOCUS(IDT_CUENTAS_COMPRAS, OnEnKillfocusCuentasCompras)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDB_TARIFAS_COMPRAS, OnBnClickedTarifasCompras)
	ON_EN_KILLFOCUS(IDT_NOMBRE_LARGO, OnEnKillfocusNombreLargo)
	ON_EN_KILLFOCUS(IDT_DESCRIPCION, OnEnKillfocusDescripcion)
	ON_EN_KILLFOCUS(IDT_PUNTOVERDE, OnEnKillfocusPuntoverde)
	ON_EN_KILLFOCUS(IDT_IVA, OnEnKillfocusIva)
	ON_EN_KILLFOCUS(IDT_RECARGO, OnEnKillfocusRecargo)
	ON_EN_KILLFOCUS(IDT_PESO, OnEnKillfocusPeso)
	ON_BN_CLICKED(IDB_PROVEEDORES, OnBnClickedProveedores)
	ON_EN_KILLFOCUS(IDT_NOMBRE, OnEnKillfocusNombre)
END_MESSAGE_MAP()

BOOL CDlgGestionReferencias::OnInitDialog()
{
	CDialog::OnInitDialog();
	//************************Abre la Tabla Articulos***********************************
	m_rsArticulo.m_strSort="ARTI";
	if (!m_rsArticulo.Open(CRecordset::dynaset))//,NULL, CRecordset::useBookmarks )) 
	{
		AfxMessageBox(IDC_ERROR_BD);
		return false;
	}
	//**********************************************************************************
	m_ctrlMovAlmacen.AddString("Si");
	m_ctrlMovAlmacen.AddString("No");
	m_ctrlAlquilado.AddString("Si");
	m_ctrlAlquilado.AddString("No");
	//*********Pone la fecha de hoy(sino saldria la fecha NULL:01/01/1970)**************                         
	m_timeAlta=CTime::GetCurrentTime();
	/*VERIFY(m_botonIni.AutoLoad(IDC_INI, this));
	VERIFY(m_botonSig.AutoLoad(IDC_SIG, this));
	VERIFY(m_botonAnt.AutoLoad(IDC_ANT, this));
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));*/
	//******************Carga los dialogos de busqueda para ahorrar tiempo**************
	m_dlgBusquedaCuentas.SetConexion(m_db);
	m_dlgBusquedaFamilia.SetConexion(m_db);
	m_dlgBusquedaSubFami.SetConexion(m_db);
	m_dlgBusquedaRef.SetConexion(m_db);
	//**********************************************************************************
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	//Si no hay registros desactiva los botones de siguiente y final
	if(m_rsArticulo.GetRecordCount()==0 || m_rsArticulo.GetRecordCount()==-1)
	{
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		return FALSE;
	}
	//si hay al menos un registro
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	m_rsArticulo.MoveFirst();
	strPrimero=m_rsArticulo.m_ARTI.TrimRight();
	m_rsArticulo.MoveLast();
	strUltimo=m_rsArticulo.m_ARTI.TrimRight();
	
	GetDlgItem(IDT_FAMILIA)->SetFocus();
	return FALSE;  // Devuelve TRUE a menos que establezca el foco en un control
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnPaint() 
{
	CDialog::OnPaint();
}

                       // Controladores de mensajes de CDlgGestionReferencias //
/***********************************************************************************************************/
/****                                   ACCIONES DE LOS BOTONES                                         ****/
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedBusquedaReferencia()//el boton para buscar por referencia
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusquedaRef.SetTipo(CDialogBusqueda::ARTICULOS);
	Estado = m_dlgBusquedaRef.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	LimpiarCampos();
	m_strCodReferencia = m_dlgBusquedaRef.GetCodigo();
	BuscaArticulo();
	RellenaCampos(&m_rsArticulo);
	BuscaFamilia();
	BuscaSubFamilia();
	BuscaCuenta(m_strCuentasventa,1);
	BuscaCuenta(m_strCuentascompra,0);
	UpdateData(FALSE);
	ChequeaPosicion();
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedBusquedaFamilias()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusquedaFamilia.SetTipo(CDialogBusqueda::FAMILIAS);
	Estado=m_dlgBusquedaFamilia.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	m_strFamilia=m_dlgBusquedaFamilia.GetCodigo();
	GetDlgItem(IDT_FAMILIA)->SetWindowText(m_strFamilia);
	m_strDesFamilia=m_dlgBusquedaFamilia.GetDescripcion();
	GetDlgItem(IDT_FAM_DES)->SetWindowText(m_strDesFamilia);
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedBusquedaSubfamilias()
{
	INT_PTR Estado;
	m_dlgBusquedaSubFami.SetTipo(CDialogBusqueda::SUBFAMILIAS);
	GetDlgItem(IDT_FAMILIA)->GetWindowText(m_strFamilia);
	m_dlgBusquedaSubFami.SetCodFamilia(m_strFamilia);
	m_dlgBusquedaSubFami.InicializarListas();
	Estado=m_dlgBusquedaSubFami.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	m_strSubfami=m_dlgBusquedaSubFami.GetCodigo();
	GetDlgItem(IDT_SUBFAMILIA)->SetWindowText(m_strSubfami);
	m_strDesSubfami=m_dlgBusquedaSubFami.GetDescripcion();
	GetDlgItem(IDT_SUBFAM_DES)->SetWindowText(m_strDesSubfami);	
	m_strCodReferencia=m_strSubfami;
	GetDlgItem(IDT_COD_REFERENCIA)->SetWindowText(m_strCodReferencia);
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedBusquedaCuentasVentas()
{	
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuentas.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	m_strCuentasventa=m_dlgBusquedaCuentas.GetCodigo();
	GetDlgItem(IDT_CUENTAS_VENTAS)->SetWindowText(m_strCuentasventa);
	m_strDesVentas=m_dlgBusquedaCuentas.GetDescripcion();
	GetDlgItem(IDC_DES_VENTAS)->SetWindowText(m_strDesVentas);		
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedBusquedaCuentasCompras()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuentas.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	m_strCuentascompra=m_dlgBusquedaCuentas.GetCodigo();
	GetDlgItem(IDT_CUENTAS_COMPRAS)->SetWindowText(m_strCuentascompra);
	m_strDesCompras = m_dlgBusquedaCuentas.GetDescripcion();
	GetDlgItem(IDC_DES_COMPRAS)->SetWindowText(m_strDesCompras);		
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedCancelar()
{
	OnCancel();
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedNuevo()
{	
	bUpdate=FALSE;
	m_strCodReferencia="";
	m_strFamilia="";
	m_strDesFamilia="";
	m_strSubfami="";
	m_strDesSubfami="";
	LimpiarCampos();//aqui se hace un UpdateData(FALSE)
	bInicial=TRUE;//al limpiar se inicializa
	m_rsArticulo.MoveFirst();
	LimpiarArticulo();
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDT_FAMILIA)->SetFocus();
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedTarifasVentas()
{
	//maneja unos campos de la tabla asique le pasamos un puntero
	//y no necesitamos retornas valores
	INT_PTR Estado;
	CDlgTarifasVentas dlgTarVentas;
 	if (bUpdate==TRUE)
		dlgTarVentas.SetNuevo(FALSE);
	else
		dlgTarVentas.SetNuevo(TRUE);
	dlgTarVentas.SetArticulo(&m_rsArticulo);
	dlgTarVentas.SetConexion(m_db);
	Estado = dlgTarVentas.DoModal();
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedTarifasCompras()
{
	INT_PTR Estado;
	CDlgTarifasCompras dlgTarCompras;
	if (bUpdate==TRUE)
		dlgTarCompras.setNuevo(FALSE);
	else
		dlgTarCompras.setNuevo(TRUE);
	dlgTarCompras.SetArticulo(&m_rsArticulo);
	dlgTarCompras.SetConexion(m_db);
	Estado = dlgTarCompras.DoModal();
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedAceptar()
{
	UpdateData(TRUE);
	///////////////////si no hay nada escrito/////////////////
	if (m_strCodReferencia.IsEmpty())
	{
		AfxMessageBox(IDC_CODIGO_NO_VACIO);
		GetDlgItem(IDT_COD_REFERENCIA)->SetFocus();
		return;
	}
	/////////////////////////////////////////////////////////
	m_rsArticulo.m_ARTI=m_strCodReferencia.TrimRight();
	m_rsArticulo.m_DESARTI=m_strNombre.TrimRight();
	m_rsArticulo.m_DESARMEMO=m_strNombreLargo.TrimRight();
	m_rsArticulo.m_DESPROV=m_strDescripcion.TrimRight();
	m_rsArticulo.m_CODFAM=m_strFamilia.TrimRight();
	m_rsArticulo.m_CSUBFAM=m_strSubfami.TrimRight();
	m_rsArticulo.m_CTAVTA=m_strCuentasventa.TrimRight();
	m_rsArticulo.m_CUENTA=m_strCuentascompra.TrimRight();
	m_rsArticulo.m_PTOVERDE=atof(m_strPuntoVerde);
	m_rsArticulo.m_IVARTI=atof(m_strIVA);
	m_rsArticulo.m_RECARGO=atof(m_strRecargo);
	m_rsArticulo.m_PESO=atof(m_strPeso);
	m_rsArticulo.m_STKMIN=atof(m_strMinimo);
	m_rsArticulo.m_FECALTA=m_timeAlta;
	m_rsArticulo.m_FECBAJA=m_timeBaja;
	if (m_rsArticulo.m_ALQUILER.IsEmpty())
	{
		m_rsArticulo.m_ALQUILER='S';
		m_rsArticulo.m_TIPOALQ='M';
	}
	/************************************/
	if (m_chMovAlmacen=="No")
		m_rsArticulo.m_MOVALM='N';
	else
		m_rsArticulo.m_MOVALM='S';
	if (m_chAlquilado=="Si")
		m_rsArticulo.m_ALQUILADO='S';
	else
		m_rsArticulo.m_ALQUILADO='N';

	/****************** SI TIENE LOS CAMPOS OBLIGATORIOS **********************/
	/*if ((!m_rsArticulo.m_DESARTI.IsEmpty()) && (!m_rsArticulo.m_CTAVTA.IsEmpty())
		|| (!m_rsArticulo.m_DESARTI.IsEmpty())&& (!m_rsArticulo.m_CUENTA.IsEmpty()))
	{*/
		if(bUpdate==TRUE)//si es conocido, debe ser actualizado
		{
			HRESULT hErr = S_OK;

			if ( !m_db->BeginTrans())
				return;
			hErr = m_rsArticulo.UpdateRegistro(); //actualiza
			// Se insertan los proveedores. Primero se elimina lo que hubiera por si
			// se ha borrado alguno
			if (hErr == S_OK)
			{
				if (m_pProve.GetCount() > 0)
				{
					CProveArti rsProveArti(m_db);
					rsProveArti.m_ARTI = m_rsArticulo.m_ARTI;
					hErr = rsProveArti.DeleteProveArti();

					if (hErr == S_OK)
					{
						POSITION pos = m_pProve.GetHeadPosition();						
						for (int i=0;i< m_pProve.GetCount() && hErr == S_OK;i++)
						{
							rsProveArti = m_pProve.GetNext(pos);
							rsProveArti.m_ARTI = m_rsArticulo.m_ARTI;
							hErr = rsProveArti.Insert();
						}
					}
				}
			}
			/*** Si todo sale bien, realiza la transacción ***/
			if (hErr == S_OK)
				m_db->CommitTrans();
			else
			/*** Si no realiza un rollback***/
				m_db->Rollback();
		}
		else//si no es conocido, debe ser insertado
		{
			HRESULT hErr = S_OK;

			if ( !m_db->BeginTrans())
				return;

			hErr = m_rsArticulo.Insert();
			// Se insertan los proveedores. Primero se elimina lo que hubiera por si
			// se ha borrado alguno
			if (hErr == S_OK)
			{	
				CProveArti rsProveArti(m_db);
				POSITION pos = m_pProve.GetHeadPosition();						
				for (int i=0;i< m_pProve.GetCount() && hErr == S_OK;i++)
				{
					rsProveArti = m_pProve.GetNext(pos);
					rsProveArti.m_ARTI = m_rsArticulo.m_ARTI;
					hErr = rsProveArti.Insert();
				}
				m_db->CommitTrans();
				// Se inicializa la lista del diálogo de búsqueda para que meta el nuevo
				// articulo
				m_dlgBusquedaRef.InicializarListas();
			}
			else
			m_db->Rollback();				
		}
		//Cierra y abre el objeto m_rsIdioma para tener el objeto recien insertado
		m_rsArticulo.Close();
		if (!m_rsArticulo.Open(CRecordset::dynaset)) 
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}
	/*}
	else//sino tiene los campos obligatorios
	{
		AfxMessageBox(IDC_CAMPOS_OBLIGATORIOS);
		return;
	}*/
	/***********Limpia los campos*************/
	m_strCodReferencia.Empty();
	OnBnClickedNuevo();
	//LimpiarCampos();
	bInicial=TRUE;//al limpiar se inicializa
	m_rsArticulo.MoveLast();
	strUltimo=m_rsArticulo.m_ARTI.TrimRight();
	m_rsArticulo.MoveFirst();
	strPrimero=m_rsArticulo.m_ARTI.TrimRight();
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
}
/***********************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedProveedores()
{
	CDlgProveedores dlgProveedores;
	dlgProveedores.SetConexion(m_db);
	dlgProveedores.SetCodArticulo(m_strCodReferencia);
	CString strNombre;
	GetDlgItem(IDT_NOMBRE)->GetWindowText(strNombre);
	dlgProveedores.SetDesArticulo(strNombre);
	dlgProveedores.SetProveedores(&m_pProve);	
	dlgProveedores.DoModal();
}

/***********************************************************************************************************/
/****                                            FUNCIONES                                              ****/
/***********************************************************************************************************/
void CDlgGestionReferencias::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsArticulo.m_pDatabase = m_db;
}
/******************************BUSCA EL REGISTRO PARA VER SI EXISTE*****************************************
BOOL  CDlgGestionReferencias::BuscaRegistro()
{
	LimpiarArticulo();
	m_rsArticulo.m_strFilter = "ARTI LIKE '" + m_strCodReferencia + "'";	//filtro de busqueda
	if (!m_rsArticulo.Open(CRecordset::dynaset)) //comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	CString strArti = m_rsArticulo.m_ARTI.TrimRight();
	m_rsArticulo.Close();
	//m_rsArticulo.SetBookmark(BookMark);
	if (strArti == "")
		{return FALSE;}
	else
		{return TRUE;}
}
/**************************INSERTA LOS DATOS DE TABLA "ARTICULO" EN EL FORMULARIO **************************/
void CDlgGestionReferencias::RellenaCampos(CArticulo* m_AuxArti)
{	
	m_strNombre=m_AuxArti->m_DESARTI.TrimRight();	//Nombre
	m_strNombreLargo=m_AuxArti->m_DESARMEMO.TrimRight();	//Nombre Largo
	m_strDescripcion=m_AuxArti->m_DESPROV.TrimRight();	//Descripción
	m_strFamilia=m_AuxArti->m_CODFAM.TrimRight();	//Codigo familia
	m_strSubfami=m_AuxArti->m_CSUBFAM.TrimRight();	//Codigo familia
	m_timeAlta=m_AuxArti->m_FECALTA;	//Fecha de alta
	m_timeBaja=m_AuxArti->m_FECBAJA;
	m_strCuentasventa=m_AuxArti->m_CTAVTA.TrimRight();
	m_strCuentascompra=m_AuxArti->m_CUENTA.TrimRight();
	m_strPuntoVerde.Format("%.3f",m_AuxArti->m_PTOVERDE);
	m_strIVA.Format("%.3f",m_AuxArti->m_IVARTI);
	m_strRecargo.Format("%.3f",m_AuxArti->m_RECARGO);
	m_strMinimo.Format("%.0f",m_AuxArti->m_STKMIN);
	m_strPeso.Format("%.3f",m_AuxArti->m_PESO);
	
	if (m_AuxArti->m_MOVALM=="N")
		m_chMovAlmacen="No";
	else
		m_chMovAlmacen="Si";
	if (m_AuxArti->m_ALQUILADO=="S")
		m_chAlquilado="Si";
	else
		m_chAlquilado="No";
}
/*****************INSERTA LOS DATOS DE TABLA "FAMILIA" EN EL FORMULARIO ************************************/
BOOL CDlgGestionReferencias::BuscaFamilia()
{
	CFamilias rsFamilia(m_db);
	rsFamilia.m_strFilter = "CFAMILIA LIKE '" + m_strFamilia + "'";	//filtro de busqueda
	if (!rsFamilia.Open(CRecordset::dynaset)) //comprueva si se puede abrir la tabla
	{
		AfxMessageBox(IDC_ERROR_BD);
		rsFamilia.Close();
		return false;
	}
	if (rsFamilia.m_DFAMILIA.IsEmpty())
	{
		m_strDesFamilia.Empty();
		rsFamilia.Close();
		return false;
	}
	m_strDesFamilia=rsFamilia.m_DFAMILIA;
	rsFamilia.Close();
	return true;
}
/***************************INSERTA LOS DATOS DE TABLA "SUBFAMI" EN EL FORMULARIO****************************/
BOOL CDlgGestionReferencias::BuscaSubFamilia()
{

	CSubfami rsSubfami(m_db);
	rsSubfami.m_strFilter = "CSUBFAM LIKE '" + m_strSubfami + "' AND CFAMILIA LIKE '" + m_strFamilia + "'";
	if (!rsSubfami.Open(CRecordset::dynaset)) //comprueva si se puede abrir la tabla
	{
		AfxMessageBox(IDC_ERROR_BD);
		rsSubfami.Close();
		return false;
	}
	if (rsSubfami.m_DSUBFAM.IsEmpty())
	{
		m_strDesSubfami.Empty();
		rsSubfami.Close();
		return false;
	}
	m_strDesSubfami=rsSubfami.m_DSUBFAM;
	rsSubfami.Close();
	return true;
}
/*********************INSERTA LOS DATOS DE TABLA "CUENTAS" EN EL FORMULARIO**********************************/
bool CDlgGestionReferencias::BuscaCuenta(CString codCuenta, BOOL bOpcion)
{
	CCuentas rsCuenta(m_db);
	rsCuenta.m_strFilter = "CUENTA LIKE '" + codCuenta + "'";	//filtro de busqueda
	if (!rsCuenta.Open(CRecordset::dynaset)) //comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDC_ERROR_BD);
		rsCuenta.Close();
		return FALSE;
	}
	if (rsCuenta.m_CUENTA.IsEmpty())
	{
		switch (bOpcion)
		{
			case 1://cuentas ventas
			{
				m_strDesVentas.Empty();
				break;
			}
			case 0://cuentas Compras
			{
				m_strDesCompras.Empty();
				break;
			}
		}
		rsCuenta.Close();
		return false;
	}
	switch (bOpcion)
	{
		case 1://cuentas ventas
		{
			m_strDesVentas=rsCuenta.m_NOMBRE;
			break;
		}
		case 0://cuentas Compras
		{
			m_strDesCompras=rsCuenta.m_NOMBRE;
			break;
		}
	}
	rsCuenta.Close();
	return true;
}
/**********************************************************************************/
void CDlgGestionReferencias::LimpiarCampos()
{
	m_strNombre="";
	m_strNombreLargo="";
	m_strDescripcion="";
	m_strCuentasventa="";
	m_strDesVentas="";
	m_strCuentascompra="";
	m_strDesCompras="";
	m_strPuntoVerde="";
	m_strIVA="";
	m_strRecargo="";
	m_strPeso="";
	m_strMinimo="";
	m_timeAlta=CTime::GetCurrentTime();//pone la fecha de hoy(sino saldria la fecha NULL:01/01/1970)
	m_timeBaja=0;
	m_chMovAlmacen="Si";
	m_chAlquilado="No";
	m_pProve.RemoveAll();//no tocar, preguntar a Irene
	//bInicial=TRUE;//al limpiar se inicializa
	UpdateData(FALSE);
}
/*********************************************************************************************/
void CDlgGestionReferencias::OnEnKillfocusCodReferencia()
{
	if (m_rsArticulo.GetRecordCount()==0)
		return;
	CString strAuxCodReferencia=m_strCodReferencia;
	GetDlgItem(IDT_COD_REFERENCIA)->GetWindowText(m_strCodReferencia);
	//si está vacio limpia el articulo
	//si el codigo anterior es igual al nuevo, no hace chequeo//
	//if (m_strCodReferencia==strAuxCodReferencia)
	//	return;
	////////////////////////////////////////////////////////////
	LimpiarCampos();//limpia todos 
	if (BuscaArticulo()==TRUE)//si encuentra el código
	{
		RellenaCampos(&m_rsArticulo);//pintalo
		BuscaCuenta(m_strCuentascompra,0);
		BuscaCuenta(m_strCuentasventa, 1);
		BuscaFamilia();
		BuscaSubFamilia();
		ChequeaPosicion();//comprueba que no es ni el primero ni el ultimo
		bUpdate=TRUE;//si se debe actualizar en caso de pulsar OK
		UpdateData(FALSE);
	}
	else//si no lo encuentra
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
		GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
		LimpiarArticulo();
		bUpdate=FALSE;//se debe insertar en caso de pulsar OK
		//m_rsArticulo.MoveFirst();
	}
}
/*********************************************************************************************/
void CDlgGestionReferencias::OnEnKillfocusNombreLargo()
{
	CString strAux;
	GetDlgItem(IDT_NOMBRE_LARGO)->GetWindowText(strAux);
	if (strAux.GetLength()>255)
	{
		GetDlgItem(IDT_NOMBRE_LARGO)->SetWindowText(m_strNombreLargo);
		AfxMessageBox(IDC_CAMPOLARGO255);
		m_ctrlNombreLargo.SetFocus();
	}
}
/*********************************************************************************************/
void CDlgGestionReferencias::OnEnKillfocusDescripcion()
{
	CString strAux;
	GetDlgItem(IDT_DESCRIPCION)->GetWindowText(strAux);
	if (strAux.GetLength()>35)
	{
		GetDlgItem(IDT_DESCRIPCION)->SetWindowText(m_strDescripcion);
		AfxMessageBox(IDC_CAMPOLARGO35);
		m_ctrlDescripcion.SetFocus();
	}
}
//**************************************************************************************************
void CDlgGestionReferencias::OnEnKillfocusFamilia()
{
	CString strFamiliaAux=m_strFamilia;//para luego poder retornar sino existe el registro
	GetDlgItem(IDT_FAMILIA)->GetWindowText(m_strFamilia);
	if(m_strFamilia==strFamiliaAux)//si es el mismo que tenia, no hagas nada
		return;
	if(m_strFamilia.IsEmpty())	//sino está vacio 
	{
		m_strDesFamilia.Empty();
		GetDlgItem(IDT_FAM_DES)->SetWindowText(m_strDesFamilia);
		return;
	}
	if (BuscaFamilia()==TRUE)	//si encuentra el registro
	{
		GetDlgItem(IDT_FAM_DES)->SetWindowText(m_strDesFamilia);
		m_strSubfami.Empty();
		GetDlgItem(IDT_SUBFAMILIA)->SetWindowText(m_strSubfami);
		m_strDesSubfami.Empty();
		GetDlgItem(IDT_SUBFAM_DES)->SetWindowText(m_strDesSubfami);
	}
	else//sino pone el registro anterior
	{
		m_strFamilia=strFamiliaAux;
		GetDlgItem(IDT_FAMILIA)->SetWindowText(m_strFamilia);
		AfxMessageBox(IDC_CUENTA_NO_VALIDA);
		m_ctrlFam.SetFocus();
	}
}
//*************************************************************************************************
void CDlgGestionReferencias::OnEnKillfocusSubfamilia()
{
	CString strSubfamiAux=m_strSubfami;//para luego poder retornar sino existe el registro
	GetDlgItem(IDT_SUBFAMILIA)->GetWindowText(m_strSubfami);
	if(m_strSubfami==strSubfamiAux)//si es el mismo que tenia, no hagas nada
		return;
	if(m_strSubfami.IsEmpty())	//si está vacio, vacia la descripción
	{
		m_strDesSubfami="";
		GetDlgItem(IDT_SUBFAM_DES)->SetWindowText(m_strDesSubfami);
		return;
	}
	if (BuscaSubFamilia()==TRUE)//si encuentra el registro
	{
		GetDlgItem(IDT_SUBFAM_DES)->SetWindowText(m_strDesSubfami);
		m_strCodReferencia=m_strSubfami;
		GetDlgItem(IDT_COD_REFERENCIA)->SetWindowText(m_strCodReferencia);
	}
	else//sino pone el registro anterior
	{
		m_strSubfami=strSubfamiAux;
		GetDlgItem(IDT_SUBFAMILIA)->SetWindowText(m_strSubfami);
		AfxMessageBox(IDC_CUENTA_NO_VALIDA);
		m_ctrlSubFam.SetFocus();
	}
}
//************************************************************************************************
void CDlgGestionReferencias::OnEnKillfocusCuentasVentas()
{
	CString strCuentasVentasAux=m_strCuentasventa;//para luego poder retornar sino existe el registro
	GetDlgItem(IDT_CUENTAS_VENTAS)->GetWindowText(m_strCuentasventa);
	if(m_strCuentasventa==strCuentasVentasAux)//si es el mismo que tenia, no hagas nada
		return;
	if(m_strCuentasventa.IsEmpty())	//si está vacio 
	{
		m_strDesVentas="";
		GetDlgItem(IDC_DES_VENTAS)->SetWindowText(m_strDesVentas);
		return;
	}
	if (BuscaCuenta(m_strCuentasventa,1)==TRUE)	//si encuentra el registro
	{
		GetDlgItem(IDC_DES_VENTAS)->SetWindowText(m_strDesVentas);
	}
	else//sino pone el registro anterior
	{
		m_strCuentasventa=strCuentasVentasAux;
		GetDlgItem(IDT_CUENTAS_VENTAS)->SetWindowText(m_strCuentasventa);
		AfxMessageBox(IDC_CUENTA_NO_VALIDA);
		m_ctrlVentas.SetFocus();
	}
}
//**************************************************************************************************
void CDlgGestionReferencias::OnEnKillfocusCuentasCompras()
{
	CString strCuentasComprasAux=m_strCuentascompra;//para luego poder retornar sino existe el registro
	GetDlgItem(IDT_CUENTAS_COMPRAS)->GetWindowText(m_strCuentascompra);
	if(m_strCuentascompra==strCuentasComprasAux)//si es el mismo que tenia, no hagas nada
		return;
	if(m_strCuentascompra.IsEmpty())	//sino está vacio 
	{
		m_strDesCompras="";
		GetDlgItem(IDC_DES_COMPRAS)->SetWindowText(m_strDesCompras);
		return;
	}
	if (BuscaCuenta(m_strCuentascompra,0)==TRUE)	//si encuentra el registro
	{
		GetDlgItem(IDC_DES_COMPRAS)->SetWindowText(m_strDesCompras);
	}
	else//sino lo encuentra pone el registro anterior
	{
		m_strCuentascompra=strCuentasComprasAux;
		GetDlgItem(IDT_CUENTAS_COMPRAS)->SetWindowText(m_strCuentascompra);
		AfxMessageBox(IDC_CUENTA_NO_VALIDA);
		m_ctrlCompras.SetFocus();
	}
}
//****************************************************************************************************
void CDlgGestionReferencias::OnBnClickedIni()//va al inicio de los registros
{
	LimpiarCampos();

	/*GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente*/
	
	m_rsArticulo.MoveFirst();
	m_strCodReferencia=m_rsArticulo.m_ARTI.TrimRight();

	//Rellena todos los campos
	RellenaCampos(&m_rsArticulo);
	m_strCodReferencia=m_rsArticulo.m_ARTI.TrimRight();
	BuscaFamilia();
	BuscaSubFamilia();							
	BuscaCuenta(m_strCuentasventa,1);
	BuscaCuenta(m_strCuentascompra,0);
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
}
/***************************************************************************************************/
void CDlgGestionReferencias::OnBnClickedFin()
{
	LimpiarCampos();

	GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente
	
	m_rsArticulo.MoveLast();
	m_strCodReferencia=m_rsArticulo.m_ARTI.TrimRight();
	
	//Rellena todos los campos
	RellenaCampos(&m_rsArticulo);
	m_strCodReferencia=m_rsArticulo.m_ARTI.TrimRight();
	BuscaFamilia();
	BuscaSubFamilia();							
	BuscaCuenta(m_strCuentasventa,1);
	BuscaCuenta(m_strCuentascompra,0);
	UpdateData(FALSE);//actualiza la variable
}
//****************************************************************************************************
void CDlgGestionReferencias::OnBnClickedAnt()
{
	m_rsArticulo.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	//Rellena todos los campos
	m_strCodReferencia=m_rsArticulo.m_ARTI.TrimRight();
	LimpiarCampos();//limpia todos 
	RellenaCampos(&m_rsArticulo);
	BuscaFamilia();
	BuscaSubFamilia();							
	BuscaCuenta(m_strCuentasventa,1);
	BuscaCuenta(m_strCuentascompra,0);
	UpdateData(FALSE);//actualiza la variable
	ChequeaPosicion();
	GetDlgItem(IDT_COD_REFERENCIA)->SetFocus();
}
//**************************************************************************************************
void CDlgGestionReferencias::OnBnClickedSig()
{
	GetDlgItem(IDT_COD_REFERENCIA)->SetFocus();
	if (m_strCodReferencia.IsEmpty() && bInicial)//si está vacio y es el vacio inicial
	{
		OnBnClickedIni();
		bInicial=FALSE;
		return;
	}
	if (!m_strCodReferencia.IsEmpty() && !bUpdate)//sino está vacio y es nuevo
	{
		OnBnClickedIni();
		return;
	}
	if (!bUpdate)	
		bUpdate=TRUE;
	//sino está vacio y es conocido
	m_rsArticulo.MoveNext();//me muevo al Siguiente
	m_strCodReferencia=m_rsArticulo.m_ARTI.TrimRight();
	//Rellena todos los campos
	LimpiarCampos();//limpia todos 
	RellenaCampos(&m_rsArticulo);
	BuscaFamilia();
	BuscaSubFamilia();							
	BuscaCuenta(m_strCuentasventa,1);
	BuscaCuenta(m_strCuentascompra,0);
	UpdateData(FALSE);
	ChequeaPosicion();
	//GetDlgItem(IDT_COD_REFERENCIA)->SetFocus();
}
//*****************************************************************************************************************
void CDlgGestionReferencias::ChequeaPosicion()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if (m_strCodReferencia==strPrimero)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	if (m_strCodReferencia==strUltimo)
	{
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	}
}
//*****************************************************************************************************************
void CDlgGestionReferencias::LimpiarArticulo()
{
	m_rsArticulo.m_ARTI = "";
	m_rsArticulo.m_DESARTI = "";
	m_rsArticulo.m_CODALT = "";
	m_rsArticulo.m_TARI1 = 0.0;
	m_rsArticulo.m_TARI2 = 0.0;
	m_rsArticulo.m_IVARTI = 0.0;
	m_rsArticulo.m_DTOARTI = 0.0;
	m_rsArticulo.m_CODFAM = "";
	m_rsArticulo.m_CODSEC = "";
	m_rsArticulo.m_PROVE = "";
	m_rsArticulo.m_MARCA = "";
	m_rsArticulo.m_OBSER = "";
	m_rsArticulo.m_TIPO = 0.0;
	m_rsArticulo.m_PESO = 0.0;
	m_rsArticulo.m_UNI = "";
	m_rsArticulo.m_COSLIFO = 0.0;
	m_rsArticulo.m_COSFIFO = 0.0;
	m_rsArticulo.m_COSPMC = 0.0;
	m_rsArticulo.m_COMISI = 0.0;
	m_rsArticulo.m_COMIPTS = 0.0;
	m_rsArticulo.m_FABRI = "";
	m_rsArticulo.m_FECHATA1;
	m_rsArticulo.m_FECHATA2;
	m_rsArticulo.m_COSMCOM = 0.0;
	m_rsArticulo.m_FECHAMPC;
	m_rsArticulo.m_NUMFACMPC = "";
	m_rsArticulo.m_CALIA1 = "";
	m_rsArticulo.m_CALIA2 = "";
	m_rsArticulo.m_CALIA3 = "";
	m_rsArticulo.m_CALIA4 = "";
	m_rsArticulo.m_CALIA5 = "";
	m_rsArticulo.m_TARIA2 = 0.0;
	m_rsArticulo.m_TARIA3 = 0.0;
	m_rsArticulo.m_TARIA4 = 0.0;
	m_rsArticulo.m_TARIA5 = 0.0;
	m_rsArticulo.m_NUMCAJAS = 0.0;
	m_rsArticulo.m_METCAJAS = 0.0;
	m_rsArticulo.m_METPALET = 0.0;
	m_rsArticulo.m_CALIB1 = "";
	m_rsArticulo.m_CALIB2 = "";
	m_rsArticulo.m_CALIB3 = "";
	m_rsArticulo.m_CALIB4 = "";
	m_rsArticulo.m_CALIB5 = "";
	m_rsArticulo.m_TARIB1 = 0.0;
	m_rsArticulo.m_TARIB2 = 0.0;
	m_rsArticulo.m_TARIB3 = 0.0;
	m_rsArticulo.m_TARIB4 = 0.0;
	m_rsArticulo.m_TARIB5 = 0.0;
	m_rsArticulo.m_CALIC1 = "";
	m_rsArticulo.m_CALIC2 = "";
	m_rsArticulo.m_CALIC3 = "";
	m_rsArticulo.m_CALIC4 = "";
	m_rsArticulo.m_CALIC5 = "";
	m_rsArticulo.m_TARIC1 = 0.0;
	m_rsArticulo.m_TARIC2 = 0.0;
	m_rsArticulo.m_TARIC3 = 0.0;
	m_rsArticulo.m_TARIC4 = 0.0;
	m_rsArticulo.m_TARIC5 = 0.0;
	m_rsArticulo.m_CUENTA = "";
	m_rsArticulo.m_DTOARCO = 0.0;
	m_rsArticulo.m_STKMIN = 0.0;
	m_rsArticulo.m_CANTREP = 0.0;
	m_rsArticulo.m_PROVE1 = "";
	m_rsArticulo.m_PROVE2 = "";
	m_rsArticulo.m_PROVE3 = "";
	m_rsArticulo.m_FECHAA;
	m_rsArticulo.m_FECHAB;
	m_rsArticulo.m_FECHAC;
	m_rsArticulo.m_TARI2A = 0.0;
	m_rsArticulo.m_TARI2B = 0.0;
	m_rsArticulo.m_TARI2C = 0.0;
	m_rsArticulo.m_DTOARTA = 0.0;
	m_rsArticulo.m_DTOARTB = 0.0;
	m_rsArticulo.m_DTOARTC = 0.0;
	m_rsArticulo.m_NOMPRO1 = "";
	m_rsArticulo.m_NOMPRO2 = "";
	m_rsArticulo.m_NOMPRO3 = "";
	m_rsArticulo.m_DESARTI1 = "";
	m_rsArticulo.m_PZMETRO = 0.0;
	m_rsArticulo.m_CTAVTA = "";
	m_rsArticulo.m_SUPLEM = 0.0;
	m_rsArticulo.m_DESARTI2 = "";
	m_rsArticulo.m_DESARTI3 = "";
	m_rsArticulo.m_RECARGO = 0.0;
	m_rsArticulo.m_FECALTA;
	m_rsArticulo.m_FECBAJA;
	m_rsArticulo.m_UBIX = "";
	m_rsArticulo.m_UBIY = "";
	m_rsArticulo.m_UBIZ = "";
	m_rsArticulo.m_ARTCAR10 = "";
	m_rsArticulo.m_ART1CAR = "";
	m_rsArticulo.m_ARTNUMER = 0.0;
	m_rsArticulo.m_DSUPLEM = "";
	m_rsArticulo.m_ARTNUME2 = 0.0;
	m_rsArticulo.m_ARTNUME3 = 0.0;
	m_rsArticulo.m_ARTNUME4 = 0.0;
	m_rsArticulo.m_PROPOR = "";
	m_rsArticulo.m_ALQUILER = "";
	m_rsArticulo.m_FECALQ;
	m_rsArticulo.m_FECFIN;
	m_rsArticulo.m_CONTRATO = "";
	m_rsArticulo.m_TIPOALQ = "";
	m_rsArticulo.m_ULTIFACT;
	m_rsArticulo.m_CLIENTE = "";
	m_rsArticulo.m_NUMALB = "";
	m_rsArticulo.m_ALQUIDES1 = "";
	m_rsArticulo.m_ALQUIDES2 = "";
	m_rsArticulo.m_ALQUIDES3 = "";
	m_rsArticulo.m_ALQUIDES4 = "";
	m_rsArticulo.m_ALQUIDES5 = "";
	m_rsArticulo.m_ALQUINUM1 = 0.0;
	m_rsArticulo.m_ALQUINUM2 = 0.0;
	m_rsArticulo.m_ALQUINUM3 = 0.0;
	m_rsArticulo.m_ALQUINUM4 = 0.0;
	m_rsArticulo.m_ALQUINUM5 = 0.0;
	m_rsArticulo.m_APLICADA = 0.0;
	m_rsArticulo.m_DTOAPLI = 0.0;
	m_rsArticulo.m_MOVALM = "";
	m_rsArticulo.m_GENERICO = 0;
	m_rsArticulo.m_PROPOROL = "";
	m_rsArticulo.m_EAPLICADA = 0.0;
	m_rsArticulo.m_EALQUINUM1 = 0.0;
	m_rsArticulo.m_EALQUINUM2 = 0.0;
	m_rsArticulo.m_EALQUINUM3 = 0.0;
	m_rsArticulo.m_EALQUINUM4 = 0.0;
	m_rsArticulo.m_EALQUINUM5 = 0.0;
	m_rsArticulo.m_CODPROV = "";
	m_rsArticulo.m_DESPROV = "";
	m_rsArticulo.m_DESARTIOLD = "";
	m_rsArticulo.m_CTAALQ = "";
	m_rsArticulo.m_ALQUILADO = "";
	m_rsArticulo.m_CFAMI = "";
	m_rsArticulo.m_FORMATO = "";
	m_rsArticulo.m_SERIE = "";
	m_rsArticulo.m_PASTA = "";
	m_rsArticulo.m_ETARI2 = 0.0;
	m_rsArticulo.m_ECOSLIFO = 0.0;
	m_rsArticulo.m_ECOSFIFO = 0.0;
	m_rsArticulo.m_ECOSPMC = 0.0;
	m_rsArticulo.m_BLOQUEO = 0.0;
	m_rsArticulo.m_DESARMEMO = "";
	m_rsArticulo.m_CSUBFAM = "";
	m_rsArticulo.m_PTOVERDE = 0.0;
	m_rsArticulo.m_ETARI1 = 0.0;
	m_rsArticulo.m_ETARIB1 = 0.0;
	m_rsArticulo.m_ETARIC1 = 0.0;
	m_rsArticulo.m_ETARID1 = 0.0;
	m_rsArticulo.m_ETARIE1 = 0.0;
	m_rsArticulo.m_ETARIF1 = 0.0;
	m_rsArticulo.m_ETARIG1 = 0.0;
	m_rsArticulo.m_ETARIH1 = 0.0;
	m_rsArticulo.m_ETARII1 = 0.0;
	m_rsArticulo.m_DTOTAR1 = 0.0;
	m_rsArticulo.m_DTOTARB1 = 0.0;
	m_rsArticulo.m_DTOTARC1 = 0.0;
	m_rsArticulo.m_DTOTARD1 = 0.0;
	m_rsArticulo.m_DTOTARE1 = 0.0;
	m_rsArticulo.m_DTOTARF1 = 0.0;
	m_rsArticulo.m_DTOTARG1 = 0.0;
	m_rsArticulo.m_DTOTARH1 = 0.0;
	m_rsArticulo.m_DTOTARI1 = 0.0;
	m_rsArticulo.m_TARID5 = 0.0;
	m_rsArticulo.m_TARIE5 = 0.0;
	m_rsArticulo.m_TARIF5 = 0.0;
	m_rsArticulo.m_TARIG5 = 0.0;
	m_rsArticulo.m_TARIH5 = 0.0;
	m_rsArticulo.m_TARII5 = 0.0;
	m_rsArticulo.m_TARIJ5 = 0.0;
	m_rsArticulo.m_DTOARTD = 0.0;
	m_rsArticulo.m_DTOARTE = 0.0;
	m_rsArticulo.m_DTOARTF = 0.0;
	m_rsArticulo.m_DTOARTG = 0.0;
	m_rsArticulo.m_DTOARTH = 0.0;
	m_rsArticulo.m_DTOARTII = 0.0;
	m_rsArticulo.m_DTOARTJ = 0.0;
	m_rsArticulo.m_PROVE4 = "";
	m_rsArticulo.m_PROVE5 = "";
	m_rsArticulo.m_PROVE6 = "";
	m_rsArticulo.m_PROVE7 = "";
	m_rsArticulo.m_PROVE8 = "";
	m_rsArticulo.m_PROVE9 = "";
	m_rsArticulo.m_PROVE10 = "";
	m_rsArticulo.m_UA = "";
	m_rsArticulo.m_APLIDCTOS = "";
	m_rsArticulo.m_APLIDCTOS2 = "";
	m_rsArticulo.m_APLIDCTOS3 = "";
	m_rsArticulo.m_APLIDCTOS4 = "";
	m_rsArticulo.m_APLIPP = "";
	m_rsArticulo.m_EUROSUV = 0.0;
	m_rsArticulo.m_TARVEN = 0.0;

	m_pProve.RemoveAll();
}
/**********************************************************************************************/
BOOL CDlgGestionReferencias::PreTranslateMessage(MSG* pMsg) 
{
     if (pMsg->message == WM_KEYDOWN)
      {
           switch (pMsg->wParam)
           {
                   case VK_RETURN:
					   pMsg->message=VK_TAB;
                    default:
                                break;    
            }
       }
 
     return CDialog::PreTranslateMessage(pMsg);
}
/**************************************************************************************************/
BOOL CDlgGestionReferencias::BuscaArticulo()
{
	CString strAux;
	m_rsArticulo.MoveFirst();
	while (!m_rsArticulo.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsArticulo.m_ARTI.TrimRight();//elimina el texto vacio por detras
		if (m_strCodReferencia==strAux)//si encuentra la referencia
		{
			bUpdate=true;
			return TRUE;
		}
		m_rsArticulo.MoveNext();
	}
	bUpdate=FALSE;
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CDlgGestionReferencias::ChequeaNumeros(CString cadena)
{
	BOOL bPunto = FALSE;	
	for (int i = 0; i<cadena.GetLength(); i++)
	{
		if ((cadena.GetAt(i) < '0' || cadena.GetAt(i) > '9') && (cadena.GetAt(i) != '-' 
			|| (cadena.GetAt(i) == '-' && i != 0))) 
		{				
			if (cadena.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionReferencias::OnEnKillfocusPuntoverde()
{
	CString strAux=m_strPuntoVerde;
	GetDlgItem(IDT_PUNTOVERDE)->GetWindowText(m_strPuntoVerde);
	if (strAux==m_strPuntoVerde)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strPuntoVerde)==TRUE)
	{
		GetDlgItem(IDT_PUNTOVERDE)->SetWindowText(m_strPuntoVerde);
	}
	else
	{
		GetDlgItem(IDT_PUNTOVERDE)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strPuntoVerde=strAux;
		m_ctrlPuntoVerde.SetFocus();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionReferencias::OnEnKillfocusIva()
{
	CString strAux=m_strIVA;
	GetDlgItem(IDT_IVA)->GetWindowText(m_strIVA);
	if (strAux==m_strIVA)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strIVA)==TRUE)
	{
		GetDlgItem(IDT_IVA)->SetWindowText(m_strIVA);
	}
	else
	{
		GetDlgItem(IDT_IVA)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strIVA=strAux;
		m_ctrlIVA.SetFocus();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionReferencias::OnEnKillfocusRecargo()
{
	CString strAux=m_strRecargo;
	GetDlgItem(IDT_RECARGO)->GetWindowText(m_strRecargo);
	if (strAux==m_strRecargo)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strRecargo)==TRUE)
	{
		GetDlgItem(IDT_RECARGO)->SetWindowText(m_strRecargo);
	}
	else
	{
		GetDlgItem(IDT_RECARGO)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strRecargo=strAux;
		m_ctrlRecargo.SetFocus();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionReferencias::OnEnKillfocusPeso()
{
	CString strAux=m_strPeso;
	GetDlgItem(IDT_PESO)->GetWindowText(m_strPeso);
	if (strAux==m_strPeso)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strPeso)==TRUE)
	{
		GetDlgItem(IDT_PESO)->SetWindowText(m_strPeso);
	}
	else
	{
		GetDlgItem(IDT_PESO)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strPeso=strAux;
		m_ctrlPeso.SetFocus();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionReferencias::OnEnKillfocusNombre()
{
	GetDlgItem(IDT_NOMBRE_LARGO)->GetWindowText(m_strNombreLargo);
	if (m_strNombreLargo.IsEmpty())
	{
		GetDlgItem(IDT_NOMBRE)->GetWindowText(m_strNombre);
		m_strNombreLargo = m_strNombre;
		GetDlgItem(IDT_NOMBRE_LARGO)->SetWindowText(m_strNombreLargo);
	}
}
