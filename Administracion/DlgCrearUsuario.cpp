// DlgCrearUsuario.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgCrearUsuario.h"
#include ".\dlgcrearusuario.h"
#include "BD.h"
#include "Encriptar.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgCrearUsuario
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgCrearUsuario, CDialog)
CDlgCrearUsuario::CDlgCrearUsuario(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrearUsuario::IDD, pParent)
	, m_strUsuario(_T(""))
	, m_strPassword(_T(""))
	, m_strPassword2(_T(""))
{
}

/******************************************************************************************/
CDlgCrearUsuario::~CDlgCrearUsuario()
{
}

/******************************************************************************************/
void CDlgCrearUsuario::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUsuario);
	DDX_Text(pDX, IDC_EDIT_PASSW, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PASSW2, m_strPassword2);
	DDX_Control(pDX, IDC_COMBO_PERFIL, m_cmbPerfiles);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgCrearUsuario, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_PERFIL, OnCbnSelchangeComboPerfil)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


/******************************************************************************************/
BOOL CDlgCrearUsuario::OnInitDialog()
{
	CDialog::OnInitDialog();

	/* Se carga el combo con los perfiles con los perfiles de la tabla PERFILES */
	CPerfiles rsPerfiles(m_db);

	if (!rsPerfiles.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	while (!rsPerfiles.IsEOF())
	{
		m_cmbPerfiles.AddString(rsPerfiles.m_DESCRIPCION);
		rsPerfiles.MoveNext();
	}

	rsPerfiles.Close();

	/* Se selecciona por defecto el primer elemento del combo */
	m_cmbPerfiles.SetCurSel(0);
	m_cmbPerfiles.GetLBText (0, m_strPerfil);

	return TRUE;  // devolver TRUE a menos que se establezca el foco en un control
}

/******************************************************************************************/
// Controladores de mensajes de CDlgCrearUsuario
/******************************************************************************************/

void CDlgCrearUsuario::OnCbnSelchangeComboPerfil()
{
	/* Obtenemos el perfil que ha sido seleccionado */
	int pos = m_cmbPerfiles.GetCurSel();
	m_cmbPerfiles.GetLBText (pos, m_strPerfil);
}


/******************************************************************************************/
void CDlgCrearUsuario::OnBnClickedOk()
{
	UpdateData(TRUE); 

	/* Se comprueba si se ha introducido el usuario*/
	if (m_strUsuario.IsEmpty())
	{
		AfxMessageBox(IDS_NO_USUARIO);
		return;
	}

	/* Se comprueba que se haya introducido la contraseña */
	if (m_strPassword.IsEmpty())
	{
		AfxMessageBox(IDS_NO_PASSW);
		return;
	}

	/* Se comprueba que se haya introducido la comprobación de la contraseña */
	if (m_strPassword2.IsEmpty())
	{
		AfxMessageBox(IDS_NO_PASSW2);
		return;
	}

	/* Se comprueba que el usuario no haya excedido de 8 caracteres */
	if (m_strUsuario.GetLength() > LONG_USUARIO)
	{
		AfxMessageBox(IDS_USUARIO_LARGO);
		return;
	}

	/* Se comprueba que no la contraseña y su comprobación son iguales */
	if (m_strPassword != m_strPassword2)
	{	
		AfxMessageBox(IDS_INVALID_PASSW);
		return;
	}

	/* Se comprueba que la contraseña no exceda de 8 caracteres */
	if (m_strPassword.GetLength() > LONG_USUARIO)
	{
		AfxMessageBox(IDS_PASSW_LARGA);
		return;
	}

	/* Se obtiene el identificador del perfil */
	CPerfiles rsPerfiles(m_db);
	m_strPerfil = m_strPerfil.Trim();
	rsPerfiles.m_strFilter = "DESCRIPCION LIKE '" + m_strPerfil + "'";
	if (!rsPerfiles.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}
	if (rsPerfiles.GetRecordCount() != 1)
	{
		AfxMessageBox(IDC_INVALID_PERFIL);
		return;
	}
	int iIdPerfil = rsPerfiles.m_ID;
	rsPerfiles.Close();

	/* Se inserta el usuario en la tabla de Usuario */
	CUsuario rsUsuario(m_db);
	rsUsuario.m_USUARIO = m_strUsuario;

	/* Se cifra la contraseña */
	CEncriptar cEncriptar;
	CString strPasswCifrada = m_strPassword;
	cEncriptar.Encriptar (strPasswCifrada);
	strPasswCifrada.Replace("'", "''");

	rsUsuario.m_PASSWORD = strPasswCifrada;
	rsUsuario.m_IDPERFIL = iIdPerfil;
	HRESULT hErr = rsUsuario.Insert();

	OnOK();
}

/******************************************************************************************/
void CDlgCrearUsuario::OnBnClickedCancel()
{
	OnCancel();
}

/******************************************************************************************/
// FUNCIONES
/******************************************************************************************/
void CDlgCrearUsuario::SetConexion(CDatabase *db)
{
	m_db = db;
}


