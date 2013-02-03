// DlgCliente.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgCliente.h"
#include ".\dlgcliente.h"
#include "DlgDatosCobro.h"
#include "DlgDatosFacturacionClientes.h"
#include "DlgEleccionObra.h"
#include "GestionDlg.h"

#define M 0
#define D 1

#define NACIONAL 0
#define INTRACOMUNITARIO 1
#define TERCEROS 2

// Cuadro de diálogo de CDlgCliente

IMPLEMENT_DYNAMIC(CDlgCliente, CDialog)
CDlgCliente::CDlgCliente(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCliente::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strNombreC(_T(""))
	, m_strNombre(_T(""))
	, m_strCIF(_T(""))
	, m_strDireccion(_T(""))
	, m_strNumero(_T(""))
	, m_strCP(_T(""))
	, m_strSG(_T(""))
	, m_strPoblacion(_T(""))
	, m_strProvincia(_T(""))
	, m_strPais(_T(""))
	, m_strDesPais(_T(""))
	, m_strTelefono(_T(""))
	, m_strTelefono2(_T(""))
	, m_strFax(_T(""))
	, m_strEmail(_T(""))
	, m_iDetaMayo(0)
	, m_strIdentificador(_T(""))
	, m_iTipo(0)
	, m_strContacto(_T(""))
	, m_strIdioma(_T(""))
	, m_strDesIdioma(_T(""))
	, m_strDesZona(_T(""))
	, m_strZona(_T(""))
	, m_strObservaciones(_T(""))
	, m_CTimeAlta(0)
	, m_CTimeBaja(0)
	, m_strRepresentante(_T(""))
	, m_strDesRepresentante(_T(""))
	, m_strComision1(_T(""))
	, m_strSubRepresentante(_T(""))
	, m_strDesSubRepresentante(_T(""))
	, m_strComision2(_T(""))
	, m_strTransportista(_T(""))
	, m_strDesTransportista(_T(""))
	, m_strMatricula(_T(""))
	, m_strTelefonoTrans(_T(""))
	, m_strDNI(_T(""))
{
	m_bUpdate = FALSE;
	//bUpdate = FALSE;
}

CDlgCliente::~CDlgCliente()
{
}

void CDlgCliente::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 9);
	DDX_Text(pDX, IDC_NOMBREC, m_strNombreC);
	DDV_MaxChars(pDX, m_strNombreC, 35);
	DDX_Text(pDX, IDC_NOMBRE, m_strNombre);
	//	DDX_Control(pDX, IDC_CIF, m_strCIF);
	DDV_MaxChars(pDX, m_strNombre, 50);
	DDX_Text(pDX, IDC_CIF, m_strCIF);
	DDV_MaxChars(pDX, m_strCIF, 15);
	DDX_Text(pDX, IDC_DIRECCION, m_strDireccion);
	DDV_MaxChars(pDX, m_strDireccion, 50);
	DDX_Text(pDX, IDC_NUMERO, m_strNumero);
	DDV_MaxChars(pDX, m_strNumero, 3);
	DDX_Text(pDX, IDC_CP, m_strCP);
	DDV_MaxChars(pDX, m_strCP, 5);
	DDX_Text(pDX, IDC_SG, m_strSG);
	DDV_MaxChars(pDX, m_strSG, 2);
	DDX_Text(pDX, IDC_POBLACION, m_strPoblacion);
	DDV_MaxChars(pDX, m_strPoblacion, 25);
	DDX_Text(pDX, IDC_PROVINCIA, m_strProvincia);
	DDV_MaxChars(pDX, m_strProvincia, 15);
	DDX_Text(pDX, IDC_PAIS, m_strPais);
	DDV_MaxChars(pDX, m_strPais, 3);
	DDX_Text(pDX, IDC_DES_PAIS, m_strDesPais);
	DDV_MaxChars(pDX, m_strDesPais, 35);
	DDX_Text(pDX, IDC_TELEFONO, m_strTelefono);
	DDV_MaxChars(pDX, m_strTelefono, 10);
	DDX_Text(pDX, IDC_TELEFONO2, m_strTelefono2);
	DDV_MaxChars(pDX, m_strTelefono2, 10);
	DDX_Text(pDX, IDC_FAX, m_strFax);
	DDV_MaxChars(pDX, m_strFax, 10);
	DDX_Text(pDX, IDC_EMAIL, m_strEmail);
	DDV_MaxChars(pDX, m_strEmail, 50);
	DDX_Radio(pDX, IDC_MAYORISTA, m_iDetaMayo);
	DDX_Text(pDX, IDC_IDENTIFICADOR, m_strIdentificador);
	DDV_MaxChars(pDX, m_strIdentificador, 14);
	DDX_Radio(pDX, IDC_NACIONAL, m_iTipo);
	DDX_Text(pDX, IDC_CONTACTO, m_strContacto);
	DDV_MaxChars(pDX, m_strContacto, 35);
	DDX_Text(pDX, IDC_IDIOMA, m_strIdioma);
	DDV_MaxChars(pDX, m_strIdioma, 3);
	DDX_Text(pDX, IDC_DES_IDIOMA, m_strDesIdioma);
	DDV_MaxChars(pDX, m_strDesIdioma, 35);
	DDX_Text(pDX, IDC_DES_ZONA, m_strDesZona);
	DDV_MaxChars(pDX, m_strDesZona, 35);
	DDX_Text(pDX, IDC_ZONA, m_strZona);
	DDV_MaxChars(pDX, m_strZona, 3);
	DDX_Text(pDX, IDC_OBSERVACIONES, m_strObservaciones);
	DDV_MaxChars(pDX, m_strObservaciones, 50);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_ALTA, m_CTimeAlta);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_BAJA, m_CTimeBaja);
	DDX_Text(pDX, IDC_REPRESENTANTE, m_strRepresentante);
	DDV_MaxChars(pDX, m_strRepresentante, 9);
	DDX_Text(pDX, IDC_DES_REPRESENTANTE, m_strDesRepresentante);
	DDV_MaxChars(pDX, m_strDesRepresentante, 35);
	DDX_Text(pDX, IDC_COMISION_1, m_strComision1);
	DDX_Text(pDX, IDC_SUBREPRESENTANTE, m_strSubRepresentante);
	DDV_MaxChars(pDX, m_strSubRepresentante, 9);
	DDX_Text(pDX, IDC_DES_SUBREPRESENTANTE, m_strDesSubRepresentante);
	DDV_MaxChars(pDX, m_strDesSubRepresentante, 35);
	DDX_Text(pDX, IDC_COMISION_2, m_strComision2);
	DDX_Text(pDX, IDC_TRANSPORTISTA, m_strTransportista);
	DDV_MaxChars(pDX, m_strTransportista, 3);
	DDX_Text(pDX, IDC_DES_TRANSPORTISTA, m_strDesTransportista);
	DDV_MaxChars(pDX, m_strDesTransportista, 35);
	DDX_Text(pDX, IDC_TELEFONO_TRANS, m_strTelefonoTrans);
	DDV_MaxChars(pDX, m_strTelefonoTrans, 15);
	DDX_Text(pDX, IDC_MATRICULA, m_strMatricula);
	DDV_MaxChars(pDX, m_strMatricula, 15);
	DDX_Text(pDX, IDC_DNI, m_strDNI);
	DDV_MaxChars(pDX, m_strDNI, 9);
	DDX_Control(pDX, IDC_PAIS, m_ctrlPais);
	DDX_Control(pDX, IDC_IDIOMA, m_ctrlIdioma);
	DDX_Control(pDX, IDC_ZONA, m_ctrlZona);
	DDX_Control(pDX, IDC_REPRESENTANTE, m_ctrlRepresentante);
	DDX_Control(pDX, IDC_SUBREPRESENTANTE, m_ctrlSubRepresentante);
	DDX_Control(pDX, IDC_TRANSPORTISTA, m_ctrlTransportista);
	DDX_Control(pDX, IDC_COMISION_1, m_ctrlComision1);
	DDX_Control(pDX, IDC_COMISION_2, m_ctrlComision2);
}


BEGIN_MESSAGE_MAP(CDlgCliente, CDialog)
	ON_BN_CLICKED(IDC_BOTON_PAIS, OnBnClickedBotonPais)
	ON_BN_CLICKED(IDC_BOTON_IDIOMA, OnBnClickedBotonIdioma)
	ON_BN_CLICKED(IDC_BOTON_ZONA, OnBnClickedBotonZona)
	ON_BN_CLICKED(IDC_BOTON_REPRESENTANTE, OnBnClickedBotonRepresentante)
	ON_BN_CLICKED(IDC_BOTON_SUBREPRESENTANTE, OnBnClickedBotonSubrepresentante)
	ON_BN_CLICKED(IDC_BOTON_TRANSPORTISTA, OnBnClickedBotonTransportista)
	ON_BN_CLICKED(IDC_BOTON_COBRO, OnBnClickedBotonCobro)
	ON_BN_CLICKED(IDC_FACTURACION, OnBnClickedFacturacion)
	ON_EN_KILLFOCUS(IDC_PAIS, OnEnKillfocusPais)
	ON_EN_KILLFOCUS(IDC_IDIOMA, OnEnKillfocusIdioma)
	ON_EN_KILLFOCUS(IDC_ZONA, OnEnKillfocusZona)
	ON_EN_KILLFOCUS(IDC_REPRESENTANTE, OnEnKillfocusRepresentante)
	ON_EN_KILLFOCUS(IDC_SUBREPRESENTANTE, OnEnKillfocusSubrepresentante)
	ON_EN_KILLFOCUS(IDC_TRANSPORTISTA, OnEnKillfocusTransportista)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_COMISION_1, OnEnKillfocusComision1)
	ON_EN_KILLFOCUS(IDC_COMISION_2, OnEnKillfocusComision2)
	ON_BN_CLICKED(IDC_DIRECCION_ENVIO, OnBnClickedDireccionEnvio)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

/*************************************************************************************************************/
BOOL CDlgCliente::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bCreado=FALSE;
	m_CTimeAlta = CTime::GetCurrentTime();
	/******* CARGA LAS BUSQUEDAS PARA AHORRAR TIEMPO ********/
	m_dlgBusquedaPais.SetConexion(m_db); 
	m_dlgBusquedaIdioma.SetConexion(m_db);
	m_dlgBusquedaZona.SetConexion(m_db);
	m_dlgBusquedaCuenta.SetConexion(m_db);
	m_dlgBusquedaTransportista.SetConexion(m_db);
	/*******************************************************/
	/***********      RELLENA LOS CAMPOS      **************/
	/*******************************************************/
	m_rsCliente.m_strFilter="CUENTA LIKE '" + m_strCodigo + "'";//filtro de busqueda
	if (!m_rsCliente.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (!m_rsCliente.m_CUENTA.IsEmpty())
	{
		m_strNombreC=m_rsCliente.m_NOMBRE.TrimRight();
		m_strNombre=m_rsCliente.m_NOMFICHA.TrimRight();
		m_strCIF=m_rsCliente.m_CIF.TrimRight();
		m_strDireccion=m_rsCliente.m_DIRECCION.TrimRight();
		m_strNumero=m_rsCliente.m_NUMERO.TrimRight();
		m_strCP=m_rsCliente.m_CP.TrimRight();
		m_strSG=m_rsCliente.m_SG.TrimRight();
		m_strPoblacion=m_rsCliente.m_POBLACION.TrimRight();
		m_strProvincia=m_rsCliente.m_PROVINCIA.TrimRight();
		m_strPais=m_rsCliente.m_CPAIS.TrimRight();
		m_strTelefono=m_rsCliente.m_TELEFONO.TrimRight();
		m_strTelefono2=m_rsCliente.m_TEL2.TrimRight();
		m_strFax=m_rsCliente.m_FAX.TrimRight();
		m_strEmail=m_rsCliente.m_EMAIL.TrimRight();
		m_strIdentificador=m_rsCliente.m_IVAIDEN.TrimRight();
		//////////////////////////
		if(m_rsCliente.m_IVA=='D')
		{m_iDetaMayo=D;}
		if(m_rsCliente.m_IVA=='M')
		{m_iDetaMayo=M;}
		//////////////////////////
		if(m_rsCliente.m_TIPO==' ')
		{m_iTipo=NACIONAL;}
		if(m_rsCliente.m_TIPO=='J')
		{m_iTipo=INTRACOMUNITARIO;}
		if(m_rsCliente.m_TIPO=='S')
		{m_iTipo=TERCEROS;}
		//////////////////////////
		m_strContacto=m_rsCliente.m_CONTACTO.TrimRight();
		m_strIdioma=m_rsCliente.m_IDIOMA;
		m_strZona=m_rsCliente.m_ZONA;
		m_strObservaciones=m_rsCliente.m_OBSER1;
		m_strRepresentante=m_rsCliente.m_REPRE.TrimRight();
		m_strComision1.Format("%.2f",m_rsCliente.m_COMISION);
		m_strSubRepresentante=m_rsCliente.m_REPRE2.TrimRight();
		m_strComision2.Format("%.2f",m_rsCliente.m_COMISION2);
		m_strTransportista=m_rsCliente.m_CTRANS.TrimRight();
		m_strTelefonoTrans=m_rsCliente.m_TELTRAN.TrimRight();
		m_strDNI=m_rsCliente.m_DNI.TrimRight();
		if(m_rsCliente.m_MATRICULA.TrimRight().IsEmpty())
		{
			EncuentraMatricula(m_strTransportista);
		}
		else
		{
			m_strMatricula=m_rsCliente.m_MATRICULA.TrimRight();
		}

		m_CTimeAlta=m_rsCliente.m_FECHALTA;
		m_CTimeBaja=m_rsCliente.m_FECHBAJA;

		/**********CARGA LAS DESCRIPCIONES***********/
		EncuentraPais(m_strPais);
		EncuentraZona(m_strZona);
		EncuentraIdioma(m_strIdioma);
		EncuentraTransportista(m_strTransportista);
		EncuentraCuenta(m_strRepresentante,true);
		EncuentraCuenta(m_strSubRepresentante,false);
		/********************************************/
	}
	UpdateData(FALSE);
	return FALSE;
}	
/****************************************************************************************************/
/***                                        FUNCIONES
/****************************************************************************************************/
void CDlgCliente::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsCliente.m_pDatabase=m_db;
}
/****************************************************************************************************/
void CDlgCliente::SetCodigo(CString strAux)
{
	m_strCodigo=strAux;
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedBotonPais()
{
	INT_PTR Estado;
	m_dlgBusquedaPais.SetTipo(CDialogBusqueda::PAIS);
	Estado=m_dlgBusquedaPais.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strPais=m_dlgBusquedaPais.GetCodigo();
	GetDlgItem(IDC_PAIS)->SetWindowText(m_strPais);
	m_strDesPais=m_dlgBusquedaPais.GetDescripcion();
	GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedBotonIdioma()
{
	INT_PTR Estado;
	m_dlgBusquedaIdioma.SetTipo(CDialogBusqueda::IDIOMA);
	Estado=m_dlgBusquedaIdioma.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strIdioma=m_dlgBusquedaIdioma.GetCodigo();
	GetDlgItem(IDC_IDIOMA)->SetWindowText(m_strIdioma);
	m_strDesIdioma=m_dlgBusquedaIdioma.GetDescripcion();
	GetDlgItem(IDC_DES_IDIOMA)->SetWindowText(m_strDesIdioma);

}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedBotonZona()
{
	INT_PTR Estado;
	m_dlgBusquedaZona.SetTipo(CDialogBusqueda::ZONA);
	Estado=m_dlgBusquedaZona.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strZona=m_dlgBusquedaZona.GetCodigo();
	GetDlgItem(IDC_ZONA)->SetWindowText(m_strZona);
	m_strDesZona=m_dlgBusquedaZona.GetDescripcion();
	GetDlgItem(IDC_DES_ZONA)->SetWindowText(m_strDesZona);
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedBotonRepresentante()
{
	INT_PTR Estado;
	m_dlgBusquedaCuenta.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuenta.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strRepresentante=m_dlgBusquedaCuenta.GetCodigo();
	GetDlgItem(IDC_REPRESENTANTE)->SetWindowText(m_strRepresentante);
	m_strDesRepresentante=m_dlgBusquedaCuenta.GetDescripcion();
	GetDlgItem(IDC_DES_REPRESENTANTE)->SetWindowText(m_strDesRepresentante);
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedBotonSubrepresentante()
{
	INT_PTR Estado;
	m_dlgBusquedaCuenta.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuenta.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strSubRepresentante=m_dlgBusquedaCuenta.GetCodigo();
	GetDlgItem(IDC_SUBREPRESENTANTE)->SetWindowText(m_strSubRepresentante);
	m_strDesSubRepresentante=m_dlgBusquedaCuenta.GetDescripcion();
	GetDlgItem(IDC_DES_SUBREPRESENTANTE)->SetWindowText(m_strDesSubRepresentante);
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedBotonTransportista()
{
	INT_PTR Estado;
	m_dlgBusquedaTransportista.SetTipo(CDialogBusqueda::RUTRAN);
	Estado=m_dlgBusquedaTransportista.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strTransportista=m_dlgBusquedaTransportista.GetCodigo();
	GetDlgItem(IDC_TRANSPORTISTA)->SetWindowText(m_strTransportista);
	m_strDesTransportista=m_dlgBusquedaTransportista.GetDescripcion();
	GetDlgItem(IDC_DES_TRANSPORTISTA)->SetWindowText(m_strDesTransportista);
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedBotonCobro()
{
	CDlgDatosCobro dlgCobros;
	dlgCobros.SetUpdate(m_bUpdate);
	dlgCobros.SetCliente(&m_rsCliente);
	dlgCobros.SetConexion(m_db);
	dlgCobros.DoModal();
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedFacturacion()
{
	CDlgDatosFacturacionClientes dlgFacturacion;
	dlgFacturacion.SetUpdate(m_bUpdate);
	dlgFacturacion.SetCliente(&m_rsCliente);
	dlgFacturacion.SetConexion(m_db);
	dlgFacturacion.DoModal();
}
/****************************************************************************************************/
void CDlgCliente::OnBnClickedDireccionEnvio()
{
	CDlgDireccionEnvio dlgDireccionEnvio;
	dlgDireccionEnvio.SetConexion(m_db);
	dlgDireccionEnvio.SetCliente(m_strCodigo,m_strNombreC);
	dlgDireccionEnvio.SetCreado(m_bCreado);
	dlgDireccionEnvio.DoModal();
	m_bCreado=dlgDireccionEnvio.GetCreado();
}
/***************************************************************************************************/
void CDlgCliente::OnBnClickedOk()
{
	UpdateData(TRUE);
	if(m_strNombreC.IsEmpty())
	{
		AfxMessageBox(IDC_NO_DESCRIPCION);
		GetDlgItem(IDC_NOMBREC)->SetFocus();
		return;
	}
	m_rsCliente.m_CUENTA=m_strCodigo.TrimRight();
	m_rsCliente.m_NOMBRE=m_strNombreC.TrimRight();
	m_rsCliente.m_NOMFICHA=m_strNombre.TrimRight();
	m_rsCliente.m_CIF=m_strCIF.TrimRight();
	m_rsCliente.m_DIRECCION=m_strDireccion.TrimRight();
	m_rsCliente.m_NUMERO=m_strNumero.TrimRight();
	m_rsCliente.m_CP=m_strCP.TrimRight();
	m_rsCliente.m_SG=m_strSG.TrimRight();
	m_rsCliente.m_POBLACION=m_strPoblacion.TrimRight();
	m_rsCliente.m_PROVINCIA=m_strProvincia.TrimRight();
	m_rsCliente.m_CPAIS=m_strPais.TrimRight();
	m_rsCliente.m_TELEFONO=m_strTelefono.TrimRight();
	m_rsCliente.m_TEL2=m_strTelefono2.TrimRight();
	m_rsCliente.m_FAX=m_strFax.TrimRight();
	m_rsCliente.m_EMAIL=m_strEmail.TrimRight();
	m_rsCliente.m_IVAIDEN=m_strIdentificador.TrimRight();
	m_rsCliente.m_CONTACTO=m_strContacto.TrimRight();
	m_rsCliente.m_IDIOMA=m_strIdioma.TrimRight();
	m_rsCliente.m_ZONA=m_strZona.TrimRight();
	m_rsCliente.m_OBSER1=m_strObservaciones.TrimRight();
	m_rsCliente.m_REPRE=m_strRepresentante.TrimRight();
	m_rsCliente.m_COMISION=atof(m_strComision1);
	m_rsCliente.m_REPRE2=m_strSubRepresentante.TrimRight();
	m_rsCliente.m_COMISION2=atof(m_strComision2);
	m_rsCliente.m_CTRANS=m_strTransportista.TrimRight();
	m_rsCliente.m_TELTRAN=m_strTelefonoTrans.TrimRight();
	m_rsCliente.m_DNI=m_strDNI.TrimRight();
	m_rsCliente.m_MATRICULA=m_strMatricula.TrimRight();
	m_rsCliente.m_FECHALTA=m_CTimeAlta;
	m_rsCliente.m_FECHBAJA=m_CTimeBaja;
	//////////////////////////
	if(m_iDetaMayo==D)
	{m_rsCliente.m_IVA='D';}
	if(m_iDetaMayo==M)
	{m_rsCliente.m_IVA='M';}
	switch (m_iTipo)          
	{
		case NACIONAL:
			{m_rsCliente.m_TIPO=' ';
			break;}
		case INTRACOMUNITARIO:
			{m_rsCliente.m_TIPO='J';
			break;}
		case TERCEROS:
			{m_rsCliente.m_TIPO='S';
			break;}
	}
	//////////////////////////
	if (m_bUpdate==FALSE)
	{
		if (!m_db->BeginTrans())
	        return;
		HRESULT hErr = S_OK;
		hErr = m_rsCliente.Insert();
		if (hErr == S_OK)
		{
			CCuentas rsCuentas(m_db);
			rsCuentas.m_CUENTA=m_strCodigo;
			rsCuentas.m_NOMBRE=m_strNombreC;
			hErr = rsCuentas.Insert();
			//rsCuentas.Close();
		}
		if (hErr == S_OK)
			m_db->CommitTrans();
		else
			m_db->Rollback();
	}
	else
	{
		if (!m_db->BeginTrans())
	        return;
		HRESULT hErr = S_OK;
		hErr = m_rsCliente.UpdateClientes();
		if (hErr == S_OK)
		{
			CCuentas rsCuentas(m_db);
			rsCuentas.m_CUENTA=m_strCodigo;
			rsCuentas.m_NOMBRE=m_strNombreC;
			hErr = rsCuentas.UpdateRegistro();
			//rsCuentas.Close();
		}
		if (hErr == S_OK)
			m_db->CommitTrans();
		else
			m_db->Rollback();
	}
	m_rsCliente.Close();
	OnOK();
}
/****************************************************************************************************/
void CDlgCliente::EsNuevo(BOOL resp)
{
	m_bUpdate=resp;
}
/***************************************************************************************************/
BOOL CDlgCliente::EncuentraPais(CString cadena)
{
	if (cadena.IsEmpty())
		return FALSE;
	CPais rsPais(m_db);
	rsPais.m_strFilter="CPAIS LIKE '" + cadena + "'";
	if (!rsPais.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsPais.m_DPAIS.IsEmpty())
	{
		rsPais.Close();
		return FALSE;
	}
	else
	{
		m_strDesPais=rsPais.m_DPAIS.TrimRight();
		rsPais.Close();
		return TRUE;
	}
}
/***************************************************************************************************/
BOOL CDlgCliente::EncuentraIdioma(CString cadena)
{
	CIdiomas rsIdioma(m_db);
	rsIdioma.m_strFilter="IDIOMA LIKE '" + cadena + "'";
	if (!rsIdioma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsIdioma.m_DIDIOMA.IsEmpty())
	{
		rsIdioma.Close();
		return FALSE;
	}
	else
	{
		m_strDesIdioma=rsIdioma.m_DIDIOMA.TrimRight();
		rsIdioma.Close();
		return TRUE;
	}
}
/***************************************************************************************************/
BOOL CDlgCliente::EncuentraZona(CString cadena)
{
	CZona rsZona(m_db);
	rsZona.m_strFilter="ZONA LIKE '" + cadena + "'";
	if (!rsZona.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsZona.m_DZONA.IsEmpty())
	{
		rsZona.Close();
		return FALSE;
	}
	else
	{
		m_strDesZona=rsZona.m_DZONA.TrimRight();
		rsZona.Close();
		return TRUE;
	}
}
/***************************************************************************************************/
BOOL CDlgCliente::EncuentraTransportista(CString cadena)
{
	CRuTran rsRutran(m_db);
	rsRutran.m_strFilter="CRUTRAN LIKE '" + cadena + "'";
	if (!rsRutran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsRutran.m_DRUTRAN.IsEmpty())
	{
		rsRutran.Close();
		return FALSE;
	}
	else
	{
		m_strDesTransportista=rsRutran.m_DRUTRAN.TrimRight();
		rsRutran.Close();
		return TRUE;
	}
}
/***************************************************************************************************/
void CDlgCliente::EncuentraMatricula(CString cadena)
{
	CRuTran rsRutran(m_db);
	rsRutran.m_strFilter="CRUTRAN LIKE '" + cadena + "'";
	if (!rsRutran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}
	m_strMatricula=rsRutran.m_MATRICULA.TrimRight();
}
/***************************************************************************************************/
BOOL CDlgCliente::EncuentraCuenta(CString cadena, bool repre)
{
	CCuentas rsCuenta(m_db);
	rsCuenta.m_strFilter="CUENTA LIKE '" + cadena + "'";
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsCuenta.m_NOMBRE.IsEmpty())
	{
		rsCuenta.Close();
		return FALSE;
	}
	else
	{
		if (repre==true)
		{m_strDesRepresentante=rsCuenta.m_NOMBRE.TrimRight();}
		if (repre==false)
		{m_strDesSubRepresentante=rsCuenta.m_NOMBRE.TrimRight();}
		rsCuenta.Close();
		return TRUE;
	}
}
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusPais()
{
	CString strAux=m_strPais;
	GetDlgItem(IDC_PAIS)->GetWindowText(m_strPais);
	if (m_strPais.IsEmpty())
	{
		m_strDesPais="";
		GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);
		return;
	}
	if (m_strPais==strAux)
	{return;}
	if (EncuentraPais(m_strPais)==FALSE)
	{
		m_strPais=strAux;
		GetDlgItem(IDC_PAIS)->SetWindowText(m_strPais);
		
	}
	else
	{GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);return;}
	m_ctrlPais.SetFocus();
}
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusIdioma()
{
	CString strAux=m_strIdioma;
	GetDlgItem(IDC_IDIOMA)->GetWindowText(m_strIdioma);
	if (m_strIdioma.IsEmpty())
	{
		m_strDesIdioma="";
		GetDlgItem(IDC_DES_IDIOMA)->SetWindowText(m_strDesIdioma);
		return;
	}
	if (m_strIdioma==strAux)
	{return;}
	if (EncuentraIdioma(m_strIdioma)==FALSE)
	{
		m_strIdioma=strAux;
		GetDlgItem(IDC_IDIOMA)->SetWindowText(m_strIdioma);
	}
	else
	{GetDlgItem(IDC_DES_IDIOMA)->SetWindowText(m_strDesIdioma);return;}
	m_ctrlIdioma.SetFocus();
}
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusZona()
{
	CString strAux=m_strZona;
	GetDlgItem(IDC_ZONA)->GetWindowText(m_strZona);
	if (m_strZona.IsEmpty())
	{
		m_strDesZona="";
		GetDlgItem(IDC_DES_ZONA)->SetWindowText(m_strDesZona);
		return;
	}
	if (m_strZona==strAux)
	{return;}
	if (EncuentraZona(m_strZona)==FALSE)
	{
		m_strZona=strAux;
		GetDlgItem(IDC_ZONA)->SetWindowText(m_strZona);
	}
	else
	{GetDlgItem(IDC_DES_ZONA)->SetWindowText(m_strDesZona);return;}
	m_ctrlZona.SetFocus();
}
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusRepresentante()
{
	CString strAux=m_strRepresentante;
	GetDlgItem(IDC_REPRESENTANTE)->GetWindowText(m_strRepresentante);
	if (m_strRepresentante.IsEmpty())
	{
		m_strDesRepresentante="";
		GetDlgItem(IDC_DES_REPRESENTANTE)->SetWindowText(m_strDesRepresentante);
		return;
	}
	if (m_strRepresentante==strAux)
	{return;}
	if (EncuentraCuenta(m_strRepresentante,true)==FALSE)
	{
		m_strRepresentante=strAux;
		GetDlgItem(IDC_REPRESENTANTE)->SetWindowText(m_strRepresentante);
	}
	else
	{GetDlgItem(IDC_DES_REPRESENTANTE)->SetWindowText(m_strDesRepresentante);return;}
	m_ctrlRepresentante.SetFocus();
}
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusSubrepresentante()
{
	CString strAux=m_strSubRepresentante;
	GetDlgItem(IDC_SUBREPRESENTANTE)->GetWindowText(m_strSubRepresentante);
	if (m_strSubRepresentante.IsEmpty())
	{
		m_strDesSubRepresentante="";
		GetDlgItem(IDC_DES_SUBREPRESENTANTE)->SetWindowText(m_strDesSubRepresentante);
		return;
	}
	if (m_strSubRepresentante==strAux)
	{return;}
	if (EncuentraCuenta(m_strSubRepresentante,false)==FALSE)
	{
		m_strSubRepresentante=strAux;
		GetDlgItem(IDC_SUBREPRESENTANTE)->SetWindowText(m_strSubRepresentante);	
	}
	else
	{GetDlgItem(IDC_DES_SUBREPRESENTANTE)->SetWindowText(m_strDesSubRepresentante);return;}
	m_ctrlSubRepresentante.SetFocus();
}
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusTransportista()
{
	CString strAux=m_strTransportista;
	GetDlgItem(IDC_TRANSPORTISTA)->GetWindowText(m_strTransportista);
	if (m_strTransportista.IsEmpty())
	{
		m_strDesTransportista="";
		GetDlgItem(IDC_DES_TRANSPORTISTA)->SetWindowText(m_strDesTransportista);
		return;
	}
	if (m_strDesTransportista==strAux)
	{return;}
	if (EncuentraTransportista(m_strTransportista)==FALSE)
	{
		m_strTransportista=strAux;
		GetDlgItem(IDC_TRANSPORTISTA)->SetWindowText(m_strTransportista);
		
	}
	else
	{GetDlgItem(IDC_DES_TRANSPORTISTA)->SetWindowText(m_strDesTransportista);return;}
	m_ctrlTransportista.SetFocus();
}
/***************************************************************************************************/
/******        PARA COMPROBAR QUE LA COMISION SOLO TIENE NUMEROS Y UN UNICO PUNTO             ******/
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusComision1()
{
	CString strAux=m_strComision1;
	GetDlgItem(IDC_COMISION_1)->GetWindowText(m_strComision1);
	if(m_strComision1.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strComision1)==FALSE)
	{
		m_strComision1=strAux;
		GetDlgItem(IDC_COMISION_1)->SetWindowText(m_strComision1);
		m_ctrlComision1.SetFocus();
		return;
	}
}
/***************************************************************************************************/
/******        PARA COMPROBAR QUE LA COMISION SOLO TIENE NUMEROS Y UN UNICO PUNTO             ******/
/***************************************************************************************************/
void CDlgCliente::OnEnKillfocusComision2()
{
	CString strAux=m_strComision2;
	GetDlgItem(IDC_COMISION_2)->GetWindowText(m_strComision2);
	if(m_strComision2.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strComision2)==FALSE)
	{
		m_strComision2=strAux;
		GetDlgItem(IDC_COMISION_2)->SetWindowText(m_strComision2);
		m_ctrlComision2.SetFocus();
		return;
	}
}
/***************************************************************************************************/
/******        PARA COMPROBAR QUE LA COMISION SOLO TIENE NUMEROS Y UN UNICO PUNTO             ******/
/***************************************************************************************************/
BOOL CDlgCliente::ChequeaNumeros(CString cadena)
{
	BOOL bPunto = FALSE; 
	for (int i = 0; i<cadena.GetLength(); i++)
	{
		if ((cadena.GetAt(i) < '0' || cadena.GetAt(i) > '9')) 
		{ 
			if (cadena.GetAt(i)== '.' && bPunto == FALSE)
			bPunto = TRUE;
			else
			return FALSE;
		}
	}
	return TRUE;
}
/***************************************************************************************************/
void CDlgCliente::OnBnClickedCancel()
{
	if (m_bCreado==TRUE && m_bUpdate==TRUE)
	{
		CDirEnv rsDir(m_db);
		rsDir.m_CLIENTE=m_strCodigo.TrimRight();
		rsDir.DeleteDirEnv();
	}
	OnCancel();
}
