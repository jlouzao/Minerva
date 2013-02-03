/******************************************************************************************/
// DlgOpcionesFac.cpp: archivo de implementación
/******************************************************************************************/

#include "stdafx.h"
#include "Ventas.h"
#include "DlgOpcionesFac.h"
#include ".\dlgopcionesfac.h"
#include "DlgFacturando.h"
#include "Etiquetas.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgOpcionesFac
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgOpcionesFac, CDialog)
CDlgOpcionesFac::CDlgOpcionesFac(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOpcionesFac::IDD, pParent)
	, m_fechaAsiento(CTime::GetCurrentTime())
	, m_fechaFinAlq(CTime::GetCurrentTime())
	, m_iTipoFac(0)
{
	m_bFacturacion = TRUE;
}

/******************************************************************************************/
CDlgOpcionesFac::~CDlgOpcionesFac()
{
}

/******************************************************************************************/
void CDlgOpcionesFac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_fechaAsiento);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_fechaFinAlq);
	DDX_Radio(pDX, IDC_RBTN_CONTRATO, m_iTipoFac);
	DDX_Control(pDX, IDC_CMB_CONTADOR, m_cmbContadores);
}

/******************************************************************************************/

BEGIN_MESSAGE_MAP(CDlgOpcionesFac, CDialog)
	ON_BN_CLICKED(IDC_RBTN_CONTRATO, OnBnClickedRbtnContrato)
	ON_BN_CLICKED(IDC_RBTN_OBRA, OnBnClickedRbtnObra)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgOpcionesFac
/******************************************************************************************/

/***********************************************************************************************/
BOOL CDlgOpcionesFac::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se selecciona tipo de contrato por defecto
	m_iTipoFac = CONTRATO;

	// Si no estamos en facturación no se permite seleccionar la opción "Por Obra"
	if (!m_bFacturacion)
		GetDlgItem(IDC_RBTN_OBRA)->EnableWindow(FALSE);

	m_cmbContadores.AddString(FACTURAS_A);
	m_cmbContadores.AddString(FACTURAS_B);

	// Se selecciona por defecto la opción A
	m_cmbContadores.SetCurSel(0);

	UpdateData(FALSE);

	return TRUE;
}

/******************************************************************************************/
void CDlgOpcionesFac::OnBnClickedRbtnContrato()
{
	m_iTipoFac = CONTRATO;
}

/******************************************************************************************/
void CDlgOpcionesFac::OnBnClickedRbtnObra()
{
	m_iTipoFac = OBRA;
}

/******************************************************************************************/
void CDlgOpcionesFac::OnBnClickedOk()
{
	UpdateData();

	if (m_cmbContadores.GetCurSel() == 0)
		m_iContador = CONTADOR_A;
	else if (m_cmbContadores.GetCurSel() == 1)
		m_iContador = CONTADOR_B;

	if (m_bFacturacion)
	{
		// Se facturan los pedidos
		CDlgFacturando dlgFacturando;
		dlgFacturando.SetConexion(m_db);
		dlgFacturando.SetPedidos(m_lPedidos);
		dlgFacturando.SetFinAlq(m_fechaFinAlq);
		dlgFacturando.SetTipoFac(m_iTipoFac);
		dlgFacturando.SetContador(m_iContador);
		dlgFacturando.DoModal();
	}

	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgOpcionesFac::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgOpcionesFac::SetPedidos(CList <CPedidos, CPedidos&> *lPedidos)
{
	m_lPedidos = lPedidos;
}

/******************************************************************************************/
void CDlgOpcionesFac::SetFacturacion(BOOL bFacturacion)
{
	m_bFacturacion = bFacturacion;
}

/******************************************************************************************/
CTime CDlgOpcionesFac::GetFechaFinAlq()
{
	return m_fechaFinAlq;
}

/******************************************************************************************/
int CDlgOpcionesFac::GetContador()
{
	return m_iContador;
}



