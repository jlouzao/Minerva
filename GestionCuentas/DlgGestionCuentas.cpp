// DlgGestionCuentas.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgGestionCuentas.h"
#include ".\dlggestioncuentas.h"


// Cuadro de diálogo de CDlgGestionCuentas

IMPLEMENT_DYNAMIC(CDlgGestionCuentas, CDialog)
CDlgGestionCuentas::CDlgGestionCuentas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGestionCuentas::IDD, pParent)
	, m_strCuenta(_T(""))
	, m_strDescripcion(_T(""))
{
	bUpdate = FALSE;
}

CDlgGestionCuentas::~CDlgGestionCuentas()
{
	m_rsCuentas.Close();
}

void CDlgGestionCuentas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUENTA, m_ctrlCuenta);
	DDX_Text(pDX, IDC_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
}

BEGIN_MESSAGE_MAP(CDlgGestionCuentas, CDialog)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDC_NUEVO, OnBnClickedNuevo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUSCAR_CUENTAS, OnBnClickedBuscarCuentas)
	ON_EN_KILLFOCUS(IDC_CUENTA, OnEnKillfocusCuenta)
END_MESSAGE_MAP()

BOOL CDlgGestionCuentas::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_rsCuentas.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		//AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	m_dlgBusquedaCuenta.SetConexion(m_db);

	/*********** CARGA LOS BOTONES ***********
	VERIFY(m_botonIni.AutoLoad(IDC_INI, this));
	VERIFY(m_botonSig.AutoLoad(IDC_SIG, this));
	VERIFY(m_botonAnt.AutoLoad(IDC_ANT, this));
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));
	/********** CARGA LOS DATOS **************/
	if(!bUpdate)
	{
		bInicial=TRUE;
		GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
		GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	else
	{
		if (m_strCuenta.IsEmpty())
		{
			GetDlgItem(IDC_INI)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		}
		else
			ChequeaPosicion();
	}
	/*****************************************/
	m_rsCuentas.MoveLast();
	strUltimo=m_rsCuentas.m_CUENTA.TrimRight();
	m_rsCuentas.MoveFirst();
	strPrimero=m_rsCuentas.m_CUENTA.TrimRight();
	/*****************************************/
	GetDlgItem(IDC_CUENTA)->SetFocus();
	return FALSE;
}
/***************************************************************************************************************/
/*******	                             FUNCIONES                                                       *******/
/***************************************************************************************************************/
void CDlgGestionCuentas::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsCuentas.m_pDatabase = m_db;
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnEnKillfocusCuenta()
{
	CString strCodigoAux=m_strCuenta;
	GetDlgItem(IDC_CUENTA)->GetWindowText(m_strCuenta);
	//si el codigo anterior es igual al nuevo, no hace chequeo//
	if (m_strCuenta.IsEmpty())
		return;
	if (m_strCuenta==strCodigoAux)
		return;
	////////////////////////////////////////////////////////////
	if (BuscaRegistro()==TRUE)//si encuentra el codigo
	{
		GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);//pintala
		ChequeaPosicion();//comprueba que no es ni el primero ni el ultimo
		bUpdate=TRUE;//si se debe actualizar en caso de pulsar OK
	}
	else//sino se encuentra 
	{
		m_strDescripcion.Empty();//vacia la variable
		GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);//pintala
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
		GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
		bUpdate=FALSE;//se debe insertar en caso de pulsar OK
	}
	if (m_strCuenta.GetLength() == 9 && m_strCuenta.GetAt(0) == '4')
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(TRUE);
	GetDlgItem(IDC_NUEVO)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}
/***************************************************************************************************************/
BOOL CDlgGestionCuentas::BuscaRegistro()
{
	CString strAux;
	m_rsCuentas.MoveFirst();
	while (!m_rsCuentas.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsCuentas.m_CUENTA.TrimRight();//elimina el texto vacio por detras
		if (m_strCuenta==strAux)//si encuentra la referencia
		{
			bUpdate=TRUE;
			m_strDescripcion=m_rsCuentas.m_NOMBRE.TrimRight();
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			GetDlgItem(IDC_NUEVO)->EnableWindow(TRUE);
			return TRUE;
		}
		m_rsCuentas.MoveNext();
	}
	return FALSE;
}
/***************************************************************************************************************/
void CDlgGestionCuentas::RellenaCampos(CCuentas* rsAux)
{
	m_strDescripcion=rsAux->m_NOMBRE.TrimRight();
	GetDlgItem(IDC_NUEVO)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}
/**************************************************************************************************************/
void CDlgGestionCuentas::LimpiarRegistro()
{
	m_rsCuentas.m_CUENTA="";
	m_rsCuentas.m_NOMBRE="";
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedIni()
{
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//y de siguiente
	
	m_rsCuentas.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCuenta=m_rsCuentas.m_CUENTA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCuentas.m_NOMBRE.TrimRight();//lo guarda en la variable
	UpdateData(FALSE);//actualiza la variable
	if (m_strCuenta.GetLength() == 9 && m_strCuenta.GetAt(0) == '4')
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(TRUE);
	GetDlgItem(IDC_NUEVO)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_CUENTA)->SetFocus();
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedAnt()
{
	m_rsCuentas.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCuenta=m_rsCuentas.m_CUENTA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCuentas.m_NOMBRE.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	if (m_strCuenta.GetLength() == 9 && m_strCuenta.GetAt(0) == '4')
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(TRUE);
	GetDlgItem(IDC_NUEVO)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_CUENTA)->SetFocus();
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedSig()
{
	if (m_strCuenta.IsEmpty() && bInicial)//si está vacio y es el vacio inicial
	{
		OnBnClickedIni();
		bInicial=FALSE;
		return;
	}
	if (!m_strCuenta.IsEmpty() && !bUpdate)//sino está vacio y es nuevo
	{
		OnBnClickedIni();
		return;
	}
	m_rsCuentas.MoveNext();//me muevo al Siguiente
	m_strCuenta=m_rsCuentas.m_CUENTA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCuentas.m_NOMBRE.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	if (m_strCuenta.GetLength() == 9 && m_strCuenta.GetAt(0) == '4')
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(TRUE);
	GetDlgItem(IDC_NUEVO)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_CUENTA)->SetFocus();
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedFin()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente
	
	m_rsCuentas.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCuenta=m_rsCuentas.m_CUENTA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCuentas.m_NOMBRE.TrimRight();//lo guarda en la variable
	UpdateData(FALSE);//actualiza la variable
	if (m_strCuenta.GetLength()!=9 && m_strCuenta.GetAt(0)!='4' )//&& m_strCuenta.GetAt(1)!='1' || 
		//m_strCuenta.GetAt(1)!='2' || m_strCuenta.GetAt(1)!='3')
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(FALSE);
	GetDlgItem(IDC_NUEVO)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_CUENTA)->SetFocus();
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedNuevo()
{
	m_strCuenta="";
	m_strDescripcion="";
	GetDlgItem(IDC_DESCRIPCION)->EnableWindow(FALSE);
	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_NUEVO)->EnableWindow(FALSE);
	//bTotalBuscado=FALSE;
	bInicial=TRUE;
	m_rsCuentas.MoveFirst();
	GetDlgItem(IDC_CUENTA)->SetFocus();

}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedOk()
{
	//UpdateData(TRUE);
	GetDlgItem(IDC_CUENTA)->GetWindowText(m_strCuenta);
	GetDlgItem(IDC_DESCRIPCION)->GetWindowText(m_strDescripcion);
	if (m_strCuenta.IsEmpty())
		return;
	if(m_strCuenta.GetAt(0)=='4')
	{
		if(m_strCuenta.GetAt(1)=='0'||m_strCuenta.GetAt(1)=='1')
		{//abre proveedores
			INT_PTR Estado;
			CDlgProveedores m_dlgProveedores;
			m_dlgProveedores.EsNuevo(bOp);
			m_dlgProveedores.SetConexion(m_db);
			m_dlgProveedores.SetCodigo(m_strCuenta);
			m_dlgProveedores.EsNuevo(bUpdate);
			Estado=m_dlgProveedores.DoModal();
			m_dlgBusquedaCuenta.InicializarListas();
			m_rsCuentas.Close();
			//m_rsCuentas.m_strSort="CUENTA";
			if (!m_rsCuentas.Open(CRecordset::dynaset))
			{
				AfxMessageBox(IDC_ERROR_BD);
				return;
			}
			/*if (Estado==IDCANCEL)
			{
				return;
			}*/
			OnBnClickedNuevo();
			return;
		}
		if(m_strCuenta.GetAt(1)=='3')
		{//abre clientes
			INT_PTR Estado;
			CDlgCliente m_dlgCliente;
			m_dlgCliente.EsNuevo(bOp);
			m_dlgCliente.SetConexion(m_db);
			m_dlgCliente.SetCodigo(m_strCuenta);
			m_dlgCliente.EsNuevo(bUpdate);
			Estado=m_dlgCliente.DoModal();
			m_dlgBusquedaCuenta.InicializarListas();
			m_rsCuentas.Close();
			if (!m_rsCuentas.Open(CRecordset::dynaset))
			{
				AfxMessageBox(IDC_ERROR_BD);
				return;
			}
			/*if (Estado==IDCANCEL)
			{
				return;
			}*/
			OnBnClickedNuevo();
			return;
		}
	}
	else
	{//es cuenta contable
		m_rsCuentas.m_CUENTA=m_strCuenta;
		m_rsCuentas.m_NOMBRE=m_strDescripcion;
		if (bUpdate==FALSE)
		{
			m_rsCuentas.Insert();
		}
		else
		{
			m_rsCuentas.UpdateRegistro();
		}
		m_rsCuentas.Close();
		//m_rsCuentas.m_strSort="CUENTA";
		if (!m_rsCuentas.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return;
		}
		OnBnClickedNuevo();
	}
	/*****Vuelve a cargar el primer registro y el ultimo*****/
	m_rsCuentas.MoveLast();
	strUltimo=m_rsCuentas.m_CUENTA.TrimRight();
	m_rsCuentas.MoveFirst();
	strPrimero=m_rsCuentas.m_CUENTA.TrimRight();
	/* despues de insertar o actualizar ya sea clientes, proveedores o lo que sea, actualiza las listas*/
	m_dlgBusquedaCuenta.InicializarListas();
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedCancel()
{
	OnCancel();
}
/***************************************************************************************************************/
void CDlgGestionCuentas::OnBnClickedBuscarCuentas()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusquedaCuenta.SetTipo(CDialogBusqueda::CUENTAS);
	m_dlgBusquedaCuenta.SetGestionar(FALSE);
	Estado=m_dlgBusquedaCuenta.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	m_strCuenta=m_dlgBusquedaCuenta.GetCodigo();
	m_strDescripcion=m_dlgBusquedaCuenta.GetDescripcion();
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
	GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
	BuscaRegistro();
	ChequeaPosicion();
	if (m_strCuenta.GetLength() == 9 && m_strCuenta.GetAt(0) == '4')
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_DESCRIPCION)->EnableWindow(TRUE);
}
/***************************************************************************************************************/
void CDlgGestionCuentas::ChequeaPosicion()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if (m_strCuenta==strPrimero)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	if (m_strCuenta==strUltimo)
	{
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	}
}
