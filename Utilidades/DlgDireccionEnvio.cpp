// DlgDireccionEnvio.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgDireccionEnvio.h"
#include ".\dlgdireccionenvio.h"
//#include "DialogBusqueda.h"

#define INICIAL 0
#define BUSCADO 1

#define NO 0
#define SI 1

IMPLEMENT_DYNAMIC(CDlgDireccionEnvio, CDialog)
CDlgDireccionEnvio::CDlgDireccionEnvio(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDireccionEnvio::IDD, pParent)
	, m_strObra(_T(""))
	, m_strNombre(_T(""))
	, m_strDireccion(_T(""))
	, m_strCP(_T(""))
	, m_strPoblacion(_T(""))
	, m_strProvincia(_T(""))
	, m_strDistancia(_T(""))
	, m_strContacto(_T(""))
	, m_strTelefono(_T(""))
	, m_FechAlta(0)
	, m_FechBaja(0)
	, m_bCerrada(FALSE)
	, m_strCliente(_T(""))
	, m_strDesCliente(_T(""))
	, bUpdate(FALSE)//por defecto se inserta, no actualiza
	, bBuscado(FALSE)
{
}

CDlgDireccionEnvio::~CDlgDireccionEnvio()
{
//	m_rsDirEnv.Close();
}

void CDlgDireccionEnvio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OBRA, m_strObra);
	DDV_MaxChars(pDX, m_strObra, 3);
	DDX_Text(pDX, IDC_NOMBRE, m_strNombre);
	DDV_MaxChars(pDX, m_strNombre, 35);
	DDX_Text(pDX, IDC_DIRECCION, m_strDireccion);
	DDV_MaxChars(pDX, m_strDireccion, 50);
	DDX_Text(pDX, IDC_CP, m_strCP);
	DDV_MaxChars(pDX, m_strCP, 5);
	DDX_Text(pDX, IDC_POBLACION, m_strPoblacion);
	DDV_MaxChars(pDX, m_strPoblacion, 25);
	DDX_Text(pDX, IDC_PROVINCIA, m_strProvincia);
	DDV_MaxChars(pDX, m_strProvincia, 15);
	DDX_Text(pDX, IDC_DISTANCIA, m_strDistancia);
	DDX_Text(pDX, IDC_CONTACTO, m_strContacto);
	DDV_MaxChars(pDX, m_strContacto, 35);
	DDX_Text(pDX, IDC_TELEFONO, m_strTelefono);
	DDV_MaxChars(pDX, m_strTelefono, 15);
	DDX_DateTimeCtrl(pDX, IDC_FECHALTA, m_FechAlta);
	DDX_DateTimeCtrl(pDX, IDC_FECHBAJA, m_FechBaja);
	DDX_Control(pDX, IDC_OBRA, m_ctrlObra);
	DDX_Control(pDX, IDC_DISTANCIA, m_ctrlDistancia);
	//DDX_Radio(pDX, IDC_CERRADA1, m_bCerrada);
	DDX_Text(pDX, IDC_CLIENTE, m_strCliente);
	DDX_Text(pDX, IDC_DES_CLIENTE, m_strDesCliente);
	DDX_Control(pDX, IDC_NOMBRE, m_ctrlNombre);
}


BEGIN_MESSAGE_MAP(CDlgDireccionEnvio, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_LIMPIAR, OnBnClickedLimpiar)
	ON_BN_CLICKED(IDC_BUSCAR, OnBnClickedBuscar)
	ON_EN_KILLFOCUS(IDC_DISTANCIA, OnEnKillfocusDistancia)
	ON_EN_KILLFOCUS(IDC_OBRA, OnEnKillfocusObra)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
END_MESSAGE_MAP()


/*************************************************************************************/
/*****                                                                           *****/
/*************************************************************************************/
BOOL CDlgDireccionEnvio::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgBusquedaDirEnv.SetConexion(m_db);

	m_rsDirEnv.m_strFilter="CLIENTE LIKE '" + m_strCliente + "'";
	if (!m_rsDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	if(m_strDesCliente.IsEmpty())
	{
		CClientes rsCli(m_db);
		rsCli.m_strFilter="CUENTA LIKE '"+ m_strCliente + "'";
		if (!rsCli.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDS_ERROR_BD);
			return FALSE;
		}
		m_strDesCliente=rsCli.m_NOMBRE.TrimRight();
		rsCli.Close();
	}
	m_FechAlta=CTime::GetCurrentTime();
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	if (bUpdate==FALSE)//si viene de agregar
	{
		if(m_rsDirEnv.GetRecordCount()==0)
		{
			m_strObra="1";
			GetDlgItem(IDC_OBRA)->SetWindowText(m_strObra);
			GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
			//GetDlgItem(IDC_LIMPIAR)->EnableWindow(FALSE);
			//GetDlgItem(IDOK)->EnableWindow(FALSE);
			return FALSE;
		}
		BuscarUltimoDirEnv();
	}
	else//si viene de modificar
	{
//	if(!m_rsDirEnv.m_CLIENTE.IsEmpty())//sino está vacio(carga uno por defecto)
//	{
		BuscarDirEnv();
		RellenaCampos();
		m_rsDirEnv.MoveLast();
		strUltimo=m_rsDirEnv.m_DIRENV.TrimRight();
		m_rsDirEnv.MoveFirst();
		strPrimero=m_rsDirEnv.m_DIRENV.TrimRight();
		ChequeaPosicion();
		UpdateData(FALSE);

		return FALSE;	
	}
	//si viene vacio
	UpdateData(FALSE);
	
	return FALSE;
}
// Controladores de mensajes de CDlgDireccionEnvio
/*************************************************************************************/
/*****                                                                           *****/ 
/*************************************************************************************/
void CDlgDireccionEnvio::SetCliente(CString cliente, CString descripcion)
{
	m_strCliente=cliente;
	m_strDesCliente=descripcion;
}
/*************************************************************************************/
/*****                                                                           *****/
/*************************************************************************************/
void CDlgDireccionEnvio::SetTipo(BOOL bOpcion)
{
	bUpdate=bOpcion;
}
/*************************************************************************************/
/*****                                                                           *****/
/*************************************************************************************/
void CDlgDireccionEnvio::SetObra(CString strObra)
{
	m_strObra=strObra;
}
/*************************************************************************************/
/*****                                                                           *****/
/*************************************************************************************/
void CDlgDireccionEnvio::SetConexion(CDatabase* db)
{
	m_db=db;
	m_rsDirEnv.m_pDatabase=m_db;
}
/*************************************************************************************/
/*****                                                                           *****/
/*************************************************************************************/
void CDlgDireccionEnvio::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_strObra.IsEmpty())
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_OBRA)->SetFocus();
		return;
	}
	if (m_strNombre.IsEmpty())
	{
		AfxMessageBox(IDS_DIRENV_NOMBRE);
		m_ctrlNombre.SetFocus();
		return;
	}
	m_rsDirEnv.m_DIRENV=m_strObra.TrimRight();
	m_rsDirEnv.m_NOMDIRENV=m_strNombre.TrimRight();
	m_rsDirEnv.m_DDIRENV=m_strDireccion.TrimRight();
	m_rsDirEnv.m_CP=m_strCP;
	m_rsDirEnv.m_POBL=m_strPoblacion.TrimRight();
	m_rsDirEnv.m_PROV=m_strProvincia.TrimRight();
	m_rsDirEnv.m_DISTANCIA=atof(m_strDistancia);
	m_rsDirEnv.m_CONTACTO=m_strContacto.TrimRight();
	m_rsDirEnv.m_TELEFONO=m_strTelefono.TrimRight();
	m_rsDirEnv.m_FECHALTA=m_FechAlta;
	m_rsDirEnv.m_FECHBAJA=m_FechBaja;
	m_rsDirEnv.m_CLIENTE=m_strCliente.TrimRight();
	if (m_bCerrada==SI)
		m_rsDirEnv.m_OBRACERRA='S';
	else
		m_rsDirEnv.m_OBRACERRA='N';

	if (bUpdate==FALSE && bBuscado==FALSE)
	{
		m_rsDirEnv.Insert();
		bCreado=TRUE;//---->Se ha creado un registro
	}
	else
	{
		m_rsDirEnv.UpdateDirEnv();
	} 
	m_rsDirEnv.Close();
	m_rsDirEnv.m_strFilter="CLIENTE LIKE '" + m_strCliente + "'";
	if (!m_rsDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}	
	m_strObra.Empty();
	m_dlgBusquedaDirEnv.InicializarListas();
	Limpia();
	m_rsDirEnv.MoveLast();
	strUltimo=m_rsDirEnv.m_DIRENV.TrimRight();
	m_rsDirEnv.MoveFirst();
	strPrimero=m_rsDirEnv.m_DIRENV.TrimRight();
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//habilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente
	BuscarUltimoDirEnv();
}
/*************************************************************************************/
void CDlgDireccionEnvio::OnBnClickedCancel()
{
	m_rsDirEnv.Close();
	OnCancel();
}
/*************************************************************************************/
void CDlgDireccionEnvio::OnBnClickedLimpiar()
{
	m_strObra.Empty();
	Limpia();
	bUpdate = FALSE;
	iEstado=INICIAL;
	if(m_rsDirEnv.GetRecordCount()==0)
	{
		m_strObra="1";
		GetDlgItem(IDC_OBRA)->SetWindowText(m_strObra);	
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	}
	else
	{
		BuscarUltimoDirEnv();
		GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	}
}
/*************************************************************************************/
void CDlgDireccionEnvio::BuscarUltimoDirEnv()
{
	CDirEnv AuxDirEnv(m_db);
	AuxDirEnv.m_strSort=" {fn LENGTH(DIRENV)}, DIRENV";
	AuxDirEnv.m_strFilter="CLIENTE LIKE '" + m_strCliente + "'";
	if (!AuxDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	AuxDirEnv.MoveLast();
	m_strObra.Format("%d",atoi(AuxDirEnv.m_DIRENV) + 1);
	AuxDirEnv.Close();
	GetDlgItem(IDC_OBRA)->SetWindowText(m_strObra);
}
/*************************************************************************************/
void CDlgDireccionEnvio::OnBnClickedBuscar()
{
	INT_PTR Estado;
	m_dlgBusquedaDirEnv.SetTipo(CDialogBusqueda::DIRENV);
	m_dlgBusquedaDirEnv.SetCliente(m_strCliente);
	m_dlgBusquedaDirEnv.SetGestionar(FALSE);
	m_dlgBusquedaDirEnv.SetConexion(m_db);
	Estado=m_dlgBusquedaDirEnv.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strObra=m_dlgBusquedaDirEnv.GetCodigo();
	RellenaCampos();
	bUpdate=TRUE;
}
/***************************************************************************************************/
void CDlgDireccionEnvio::OnEnKillfocusObra()
{
	CString strAux=m_strObra;
	GetDlgItem(IDC_OBRA)->GetWindowText(m_strObra);
	if(m_strObra.IsEmpty())
	{
		Limpia();
		return;
	}
	if(RellenaCampos()==FALSE)
	{
		strAux=m_strObra;
		Limpia();
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
}
/***************************************************************************************************/
/******        RELLENA TODOS LOS CAMPOS DE LA TABLA CON LAS VARIABLES DE LA BASE DE DATOS     ******/
/***************************************************************************************************/
BOOL CDlgDireccionEnvio::RellenaCampos()
{
	CDirEnv rsDir(m_db);
	rsDir.m_strFilter="CLIENTE LIKE '" + m_strCliente + "' AND DIRENV LIKE '" + m_strObra + "'";
	if (!rsDir.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_strNombre=rsDir.m_NOMDIRENV.TrimRight();
	/*if (m_strNombre.IsEmpty())
	{
		return FALSE;
	}*/
	//m_strNombre=rsDir.m_NOMDIRENV.TrimRight();
	m_strDireccion=rsDir.m_DDIRENV.TrimRight();
	m_strCP=rsDir.m_CP;
	m_strPoblacion=rsDir.m_POBL.TrimRight();
	m_strProvincia=rsDir.m_PROV.TrimRight();
	m_strDistancia.Format("%.3f",rsDir.m_DISTANCIA);
	m_strContacto=rsDir.m_CONTACTO.TrimRight();
	m_strTelefono=rsDir.m_TELEFONO.TrimRight();
	m_FechAlta=rsDir.m_FECHALTA;
	m_FechBaja=rsDir.m_FECHBAJA;
	if (rsDir.m_OBRACERRA=='S')
		m_bCerrada=SI;
	else
		m_bCerrada=NO;

	UpdateData(FALSE);
	bUpdate = TRUE;
	rsDir.Close();
	ChequeaPosicion();
	GetDlgItem(IDC_LIMPIAR)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	return TRUE;
}
/***************************************************************************************************/
/******        PARA COMPROBAR QUE LA DISTANCIA SOLO TIENE NUMEROS Y UN UNICO PUNTO            ******/
/***************************************************************************************************/
void CDlgDireccionEnvio::OnEnKillfocusDistancia()
{
	CString strAux=m_strDistancia;
	GetDlgItem(IDC_DISTANCIA)->GetWindowText(m_strDistancia);
	if(ChequeaNumeros(m_strDistancia)==FALSE)
	{
		m_strDistancia=strAux;
		GetDlgItem(IDC_DISTANCIA)->SetWindowText(m_strDistancia);
		m_ctrlDistancia.SetFocus();
	}
}

/*************************************************************************************/
BOOL CDlgDireccionEnvio::ChequeaNumeros(CString cadena)
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
/******                               BOTONES DE NAVEGACION                                   ******/
/***************************************************************************************************/
void CDlgDireccionEnvio::OnBnClickedIni()//va al inicio de los registros
{
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//deshabilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//habilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente
	
	m_rsDirEnv.MoveFirst();//se mueve al primero
	m_strObra=m_rsDirEnv.m_DIRENV.TrimRight();     //los guarda en la variable
	m_strNombre=m_rsDirEnv.m_NOMDIRENV.TrimRight();//para pasarlos al dialogo
	m_strDireccion=m_rsDirEnv.m_DDIRENV.TrimRight();
	m_strCP=m_rsDirEnv.m_CP;
	m_strPoblacion=m_rsDirEnv.m_POBL.TrimRight();
	m_strProvincia=m_rsDirEnv.m_PROV.TrimRight();
	m_strDistancia.Format("%.3f",m_rsDirEnv.m_DISTANCIA);
	m_strContacto=m_rsDirEnv.m_CONTACTO.TrimRight();
	m_strTelefono=m_rsDirEnv.m_TELEFONO.TrimRight();
	m_FechAlta=m_rsDirEnv.m_FECHALTA;
	m_FechBaja=m_rsDirEnv.m_FECHBAJA;
	if (m_rsDirEnv.m_OBRACERRA=='S')
		m_bCerrada=SI;
	else
		m_bCerrada=NO;
	UpdateData(FALSE);//actualiza la variable
}
/***************************************************************************************************/
void CDlgDireccionEnvio::OnBnClickedFin()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente
	
	m_rsDirEnv.MoveLast();
	m_strObra=m_rsDirEnv.m_DIRENV.TrimRight();     //los guarda en la variable
	m_strNombre=m_rsDirEnv.m_NOMDIRENV.TrimRight();//para pasarlos al dialogo
	m_strDireccion=m_rsDirEnv.m_DDIRENV.TrimRight();
	m_strCP=m_rsDirEnv.m_CP;
	m_strPoblacion=m_rsDirEnv.m_POBL.TrimRight();
	m_strProvincia=m_rsDirEnv.m_PROV.TrimRight();
	m_strDistancia.Format("%.3f",m_rsDirEnv.m_DISTANCIA);
	m_strContacto=m_rsDirEnv.m_CONTACTO.TrimRight();
	m_strTelefono=m_rsDirEnv.m_TELEFONO.TrimRight();
	m_FechAlta=m_rsDirEnv.m_FECHALTA;
	m_FechBaja=m_rsDirEnv.m_FECHBAJA;
	if (m_rsDirEnv.m_OBRACERRA=='S')
		m_bCerrada=SI;
	else
		m_bCerrada=NO;
	UpdateData(FALSE);//actualiza la variable
}
//****************************************************************************************************
void CDlgDireccionEnvio::OnBnClickedAnt()
{
	/*if (bBuscado==false)
	{
		m_rsDirEnv.MoveFirst();
		bBuscado=true;
	}
	else
	{*/
		if (iEstado == BUSCADO)
			m_rsDirEnv.MovePrev();//me muevo al Siguiente
		if (!bUpdate)	
			bUpdate=TRUE;
	//}
	m_strObra=m_rsDirEnv.m_DIRENV.TrimRight();     //los guarda en la variable
	m_strNombre=m_rsDirEnv.m_NOMDIRENV.TrimRight();//para pasarlos al dialogo
	m_strDireccion=m_rsDirEnv.m_DDIRENV.TrimRight();
	m_strCP=m_rsDirEnv.m_CP;
	m_strPoblacion=m_rsDirEnv.m_POBL.TrimRight();
	m_strProvincia=m_rsDirEnv.m_PROV.TrimRight();
	m_strDistancia.Format("%.3f",m_rsDirEnv.m_DISTANCIA);
	m_strContacto=m_rsDirEnv.m_CONTACTO.TrimRight();
	m_strTelefono=m_rsDirEnv.m_TELEFONO.TrimRight();
	m_FechAlta=m_rsDirEnv.m_FECHALTA;
	m_FechBaja=m_rsDirEnv.m_FECHBAJA;
	if (m_rsDirEnv.m_OBRACERRA=='S')
		m_bCerrada=SI;
	else
		m_bCerrada=NO;
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_OBRA)->SetFocus();	
	/*
	UpdateData(TRUE);//actualiza la variable

	CString strAux;

	if (bBuscado==FALSE)//sino está buscado el registro
	{
		BuscarDirEnv();
	}
	if (bBuscado==TRUE)//si está buscado
	{
		m_rsDirEnv.MovePrev();
		m_strObra=m_rsDirEnv.m_DIRENV.TrimRight();     //los guarda en la variable
		m_strNombre=m_rsDirEnv.m_NOMDIRENV.TrimRight();//para pasarlos al dialogo
		m_strDireccion=m_rsDirEnv.m_DDIRENV.TrimRight();
		m_strCP=m_rsDirEnv.m_CP;
		m_strPoblacion=m_rsDirEnv.m_POBL.TrimRight();
		m_strProvincia=m_rsDirEnv.m_PROV.TrimRight();
		m_strDistancia.Format("%.3f",m_rsDirEnv.m_DISTANCIA);
		m_strContacto=m_rsDirEnv.m_CONTACTO.TrimRight();
		m_strTelefono=m_rsDirEnv.m_TELEFONO.TrimRight();
		m_FechAlta=m_rsDirEnv.m_FECHALTA;
		m_FechBaja=m_rsDirEnv.m_FECHBAJA;
		if (m_rsDirEnv.m_OBRACERRA=='S')
			m_bCerrada=SI;
		else
			m_bCerrada=NO;
 		UpdateData(FALSE);
		//********* COMPRUEBA QUE NO SEA EL ÚLTIMO REGISTRO*********
		ChequeaPosicion();
	}
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//Habilito el boton de sigueinte
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//y final*/
}
//**************************************************************************************************
void CDlgDireccionEnvio::OnBnClickedSig()
{
	/*if (bBuscado==false)
	{
		m_rsDirEnv.MoveFirst();
		bBuscado=true;
	}
	else
	{*/
		if (iEstado == BUSCADO)
			m_rsDirEnv.MoveNext();//me muevo al Siguiente
		if (!bUpdate)	
			bUpdate=TRUE;
	//}
	m_strObra=m_rsDirEnv.m_DIRENV.TrimRight();     //los guarda en la variable
	m_strNombre=m_rsDirEnv.m_NOMDIRENV.TrimRight();//para pasarlos al dialogo
	m_strDireccion=m_rsDirEnv.m_DDIRENV.TrimRight();
	m_strCP=m_rsDirEnv.m_CP;
	m_strPoblacion=m_rsDirEnv.m_POBL.TrimRight();
	m_strProvincia=m_rsDirEnv.m_PROV.TrimRight();
	m_strDistancia.Format("%.3f",m_rsDirEnv.m_DISTANCIA);
	m_strContacto=m_rsDirEnv.m_CONTACTO.TrimRight();
	m_strTelefono=m_rsDirEnv.m_TELEFONO.TrimRight();
	m_FechAlta=m_rsDirEnv.m_FECHALTA;
	m_FechBaja=m_rsDirEnv.m_FECHBAJA;
	if (m_rsDirEnv.m_OBRACERRA=='S')
		m_bCerrada=SI;
	else
		m_bCerrada=NO;
	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_OBRA)->SetFocus();
	iEstado=BUSCADO;
	/*UpdateData(TRUE);//actualiza la variable

	CString strAux;
	if (bBuscado==FALSE)//sino está buscado el registro
	{
		if(m_strObra.IsEmpty())
		{
			m_rsDirEnv.MoveFirst();
		}
		else
			BuscarDirEnv();
	}
	if (bBuscado==TRUE)//si está buscado
	{
		m_rsDirEnv.MoveNext();
	}
	m_strObra=m_rsDirEnv.m_DIRENV.TrimRight();     //los guarda en la variable
	m_strNombre=m_rsDirEnv.m_NOMDIRENV.TrimRight();//para pasarlos al dialogo
	m_strDireccion=m_rsDirEnv.m_DDIRENV.TrimRight();
	m_strCP=m_rsDirEnv.m_CP;
	m_strPoblacion=m_rsDirEnv.m_POBL.TrimRight();
	m_strProvincia=m_rsDirEnv.m_PROV.TrimRight();
	m_strDistancia.Format("%.3f",m_rsDirEnv.m_DISTANCIA);
	m_strContacto=m_rsDirEnv.m_CONTACTO.TrimRight();
	m_strTelefono=m_rsDirEnv.m_TELEFONO.TrimRight();
	m_FechAlta=m_rsDirEnv.m_FECHALTA;
	m_FechBaja=m_rsDirEnv.m_FECHBAJA;
	if (m_rsDirEnv.m_OBRACERRA=='S')
		m_bCerrada=SI;
	else
		m_bCerrada=NO;
		UpdateData(FALSE);
	//********* COMPRUEBA QUE NO SEA EL ÚLTIMO REGISTRO*********
	ChequeaPosicion();*/
}
//*****************************************************************************************************************
void CDlgDireccionEnvio::ChequeaPosicion()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if (m_strObra==strPrimero)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	if (m_strObra==strUltimo)
	{
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIMPIAR)->EnableWindow(TRUE);
}
/****************************************************************************/
void CDlgDireccionEnvio::BuscarDirEnv()
{
	CString strAux;
	m_rsDirEnv.MoveFirst();
	while (!m_rsDirEnv.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsDirEnv.m_DIRENV.TrimRight();//elimina el texto vacio por detras
		if (m_strObra==strAux)//si encuentra la referencia
		{
			bBuscado=true;
			GetDlgItem(IDC_LIMPIAR)->EnableWindow(TRUE);
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			iEstado=BUSCADO;
			break;//sal del bucle;
		}
		m_rsDirEnv.MoveNext();
	}
	return;
}
/****************************************************************************/
void CDlgDireccionEnvio::SetCreado(BOOL Creado)
{
	bCreado=Creado;
}
/****************************************************************************/
BOOL CDlgDireccionEnvio::GetCreado()
{
	return bCreado;
}
/*****************************************************************************/
void CDlgDireccionEnvio::Limpia()
{
	m_strNombre.Empty();
	m_strDireccion.Empty();
	m_strCP.Empty();
	m_strPoblacion.Empty();
	m_strProvincia.Empty();
	m_strDistancia.Empty();
	m_strContacto.Empty();
	m_strTelefono.Empty();	
	m_FechBaja=NULL;
	m_bCerrada=FALSE;
	m_FechAlta=CTime::GetCurrentTime();
	bUpdate=FALSE;

	bBuscado=FALSE;
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	UpdateData(FALSE);
	//GetDlgItem(IDC_LIMPIAR)->EnableWindow(FALSE);
	//GetDlgItem(IDOK)->EnableWindow(FALSE);
}
/*****************************************************************************/