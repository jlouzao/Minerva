// DlgCambiarPassw.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgCambiarPassw.h"
#include ".\dlgcambiarpassw.h"
#include "Encriptar.h"
#include "BD.h"


/*****************************************************************************************/
// Cuadro de diálogo de CDlgCambiarPassw
/*****************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgCambiarPassw, CDialog)
CDlgCambiarPassw::CDlgCambiarPassw(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCambiarPassw::IDD, pParent)
	, m_strUsuario(_T(""))
	, m_strOldPassw(_T(""))
	, m_strNewPassw(_T(""))
	, m_strNewPassw2(_T(""))
{
}

/*****************************************************************************************/
CDlgCambiarPassw::~CDlgCambiarPassw()
{
}

/*****************************************************************************************/
void CDlgCambiarPassw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OLD_PASSW, m_strOldPassw);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSW, m_strNewPassw);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSW2, m_strNewPassw2);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUsuario);
}

/*****************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgCambiarPassw, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


/*****************************************************************************************/
// Controladores de mensajes de CDlgCambiarPassw
/*****************************************************************************************/
BOOL CDlgCambiarPassw::OnInitDialog()
{
	CDialog::OnInitDialog();

	/* Se inicializa el usuario */
	UpdateData(FALSE);

	return TRUE;
}
/******************************************************************************************/
void CDlgCambiarPassw::OnBnClickedOk()
{
	UpdateData(TRUE);

	/* Se comprueba si se ha introducido la antigua contraseña */
	if (m_strOldPassw.IsEmpty())
	{
		AfxMessageBox(IDS_NO_OLD_PASSW);
		return;
	}

	/* Se comprueba que se haya introducido la nueva contraseña */
	if (m_strNewPassw.IsEmpty())
	{
		AfxMessageBox(IDS_NO_NEW_PASSW);
		return;
	}

	/* Se comprueba que se haya introducido la comprobación de la nueva contraseña */
	if (m_strNewPassw2.IsEmpty())
	{
		AfxMessageBox(IDS_NO_NEW_PASSW2);
		return;
	}

	/* Se comprueba que ninguna de las contraseñas excedida de 8 caracteres */
	if (m_strOldPassw.GetLength() > LONG_PASSWORD || m_strNewPassw.GetLength() > LONG_PASSWORD ||
		  m_strNewPassw2.GetLength() > LONG_PASSWORD)
	{
		AfxMessageBox(IDS_PASSW_LARGA);
		return;
	}

	/* Se comprueba que la nueva contraseña y su confirmación sean iguales */
	if (m_strNewPassw != m_strNewPassw2)
	{
		AfxMessageBox(IDS_INVALID_PASSW);
		return;
	}

	/* Se comprueba que la contraseña del usuario es correcta */
	CUsuario rsUsuario(m_db);
	rsUsuario.m_strFilter = " USUARIO = '" + m_strUsuario +"'"; //filtro
	if (!rsUsuario.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}
	rsUsuario.m_USUARIO = rsUsuario.m_USUARIO.Trim();
	if (rsUsuario.m_USUARIO != m_strUsuario) //si no es el que buscamos
	{
		AfxMessageBox(IDC_INVALID_USER);
		return;
	}

	/* Si la contraseña introducida como antigua y la que hay en la Base de Datos no coinciden */
	CEncriptar cEncriptar;
	CString strPassw = rsUsuario.m_PASSWORD.Trim();
	cEncriptar.Desencriptar(strPassw);  
	if (strPassw != m_strOldPassw)
	{
		AfxMessageBox(IDC_INVALID_OLD_PASS);
		return;
	}

	/* Se inserta la nueva password encriptada */
	cEncriptar.Encriptar(m_strNewPassw);
	rsUsuario.m_USUARIO = m_strUsuario;
	rsUsuario.m_PASSWORD = m_strNewPassw;
	HRESULT hErr = rsUsuario.UpdatePassword();
	
	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgCambiarPassw::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgCambiarPassw::SetUsuario(CString strUsuario)
{
	m_strUsuario = strUsuario;
}