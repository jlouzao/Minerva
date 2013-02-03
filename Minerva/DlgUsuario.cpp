// DlgUsuario.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Minerva.h"
#include "DlgUsuario.h"
#include ".\dlgusuario.h"
#include "BD.h"

#define LONG_USUARIO   8
#define LONG_PASSWORD  8

// Cuadro de diálogo de CDlgUsuario

IMPLEMENT_DYNAMIC(CDlgUsuario, CDialog)

/**************************************************************************************/
CDlgUsuario::CDlgUsuario(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUsuario::IDD, pParent)
	, m_strUsuario(_T(""))
	, m_strPassword(_T(""))
{
	m_bPrimeraVez = FALSE;
}

/**************************************************************************************/
CDlgUsuario::~CDlgUsuario()
{
}

/**************************************************************************************/
void CDlgUsuario::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USUARIO, m_strUsuario);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDC_USUARIO, m_ctrlUsuario);
}

/**************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgUsuario, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

/**************************************************************************************/
// Controladores de mensajes de CDlgUsuario

void CDlgUsuario::OnBnClickedOk()
{	
	UpdateData(TRUE);  // Se recogen los valores de los cuadros de texto

	if (m_strUsuario.IsEmpty()) //si no tiene usuario
	{
		AfxMessageBox(IDC_ERROR_USU_VACIO);
		return;
	}

	if (m_strPassword.IsEmpty()) //si no tiene password
	{
		AfxMessageBox(IDC_ERROR_PASS_VACIO);
		return;
	}

	if (m_strUsuario.GetLength() > LONG_PASSWORD) //si el usuario sobrepasa los 8 caracteres
	{
		AfxMessageBox(IDC_ERROR_USU_LARGO);
		return;
	}

	if (m_strPassword.GetLength() > LONG_PASSWORD) //si la contraseña sobrepasa los 8 caracteres
	{
		AfxMessageBox(IDC_ERROR_PASSW_LARGA);
		return;
	}

	CUsuario rsUsuario(m_db);
	rsUsuario.m_strFilter = " USUARIO = '" + m_strUsuario +"'"; //filtro
	if (!rsUsuario.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	rsUsuario.m_USUARIO = rsUsuario.m_USUARIO.TrimRight();
	if (rsUsuario.m_USUARIO != m_strUsuario)//si no es el que buscamos
	{
		AfxMessageBox(IDC_ERROR_USU_NO);
		return;
	}

	rsUsuario.m_PASSWORD = rsUsuario.m_PASSWORD.Trim();
	Desencriptar(rsUsuario.m_PASSWORD);  
	if (rsUsuario.m_PASSWORD != m_strPassword)//si no es la password correcta
	{
		AfxMessageBox(IDC_ERROR_PASS_NO);
		return;
	}

	rsUsuario.Close();

	m_strUsuario = rsUsuario.m_USUARIO;
	m_iPerfil = rsUsuario.m_IDPERFIL;

	OnOK();
}

/**************************************************************************************/
void CDlgUsuario::OnBnClickedCancel()
{
	/* Si es la primera vez que se va a seleccionar una empresa se da mensaje de error
	   si se intenta cerrar la ventana sin haber seleccionado una */
	if (m_bPrimeraVez)
	{
		CString strMsg;
		strMsg.LoadString(IDS_CERRAR_APP);

		if (MessageBox(strMsg,"Minerva",MB_YESNO+MB_ICONQUESTION)==IDYES)
			OnCancel();
	}
	else
		OnCancel();
}

/**************************************************************************************/
/****     FUNCIONES                                                                ****/
/**************************************************************************************/
void CDlgUsuario::SetConexion(CDatabase *db)
{
	m_db = db;
}

/**************************************************************************************/
int CDlgUsuario::GetPerfil()
{
	return m_iPerfil; 
}

/**************************************************************************************/
CString CDlgUsuario::GetUsuario()
{
	return m_strUsuario; 
}

/**************************************************************************************/
void CDlgUsuario::SetPrimeraVez(BOOL bFlag)
{
	m_bPrimeraVez = bFlag;
}

/**************************************************************************************/
void CDlgUsuario::Desencriptar(CString &strPassw)
{
	char caract; //guardamos uno a uno los caracteres
	char valor;
	char cClave;
	CString Clave="zacarias";

	for (int i = 0; i<strPassw.GetLength(); i++)           
    {                                           
		caract=strPassw.GetAt(i);
		cClave=Clave.GetAt(i);
		valor = caract-cClave;
		strPassw.SetAt(i,valor);                   
    }

	return;
}
/**************************************************************************************/
BOOL CDlgUsuario::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ctrlUsuario.SetFocus();

	return FALSE;
}
