// DlgFacturando.cpp: archivo de implementación
/***********************************************************************************************/
#include "stdafx.h"
#include "Ventas.h"
#include "DlgFacturando.h"
#include "FacturaPedidos.h"
#include "DlgEmitirInformes.h"
#include ".\dlgfacturando.h"
#include "Etiquetas.h"

/***********************************************************************************************/
// Cuadro de diálogo de CDlgFacturando
/***********************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgFacturando, CDialog)
CDlgFacturando::CDlgFacturando(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFacturando::IDD, pParent)
	, m_strPedidos(_T(""))
	, m_strFacturas(_T(""))
	, m_strNumPedidos(_T(""))
	, m_strFecha(_T(""))
	, m_strTipo(_T(""))
	, m_strContador(_T(""))
{
}

/***********************************************************************************************/
CDlgFacturando::~CDlgFacturando()
{
}

/***********************************************************************************************/
void CDlgFacturando::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressBar);
	DDX_Text(pDX, IDC_STATIC_PEDIDO, m_strPedidos);
	DDX_Text(pDX, IDC_STATIC_FACTURAS, m_strFacturas);
	DDX_Text(pDX, IDC_NUMPEDIDO, m_strNumPedidos);
	DDX_Text(pDX, IDC_FECHA, m_strFecha);
	DDX_Text(pDX, IDC_TIPO, m_strTipo);
	DDX_Text(pDX, IDC_CONTADOR, m_strContador);
}
/***********************************************************************************************/

BEGIN_MESSAGE_MAP(CDlgFacturando, CDialog)
	ON_BN_CLICKED(IDC_BTN_INICIAR, OnBnClickedBtnIniciar)
END_MESSAGE_MAP()


/***********************************************************************************************/
// Controladores de mensajes de CDlgFacturando
/***********************************************************************************************/

/***********************************************************************************************/
BOOL CDlgFacturando::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se inicializa el progreso
	m_progressBar.SetPos(0);
	m_progressBar.SetRange(0, (short)m_lPedidos->GetCount());

	m_strNumPedidos.Format("%d",m_lPedidos->GetCount());
	m_strFecha = m_fechaFinAlq.Format("%d/%m/%Y");
	if (m_iTipoFac == CONTRATO)
		m_strTipo = TEXT_POR_CONTRATO;
	else if (m_iTipoFac == OBRA)
		m_strTipo = TEXT_POR_OBRA;

    if (m_iContador == CONTADOR_A)
		m_strContador = FACTURAS_A;
	else if (m_iContador == CONTADOR_B)
		m_strContador = FACTURAS_B;

	GetDlgItem(IDC_STATIC_PEDIDO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_FACTURAS)->ShowWindow(SW_HIDE);

	UpdateData(FALSE);

	return FALSE;
}

/******************************************************************************************/
void CDlgFacturando::OnBnClickedBtnIniciar()
{
	SetWindowText("Facturando...");

	// Se van facturando los pedidos selecccionados

	GetDlgItem(IDC_STATIC_PEDIDO)->ShowWindow(SW_SHOW);

	CFacturaPedidos facturaPedidos;
	facturaPedidos.SetConexion(m_db);
	facturaPedidos.SetPedidos(m_lPedidos);
	facturaPedidos.SetFinAlq(m_fechaFinAlq);
	facturaPedidos.SetTipoFac(m_iTipoFac);
	facturaPedidos.SetContador(m_iContador);

	// Se facturan todos los pedidos seleccionados
	for (int i=0; i<m_lPedidos->GetCount(); i++)
	{
		facturaPedidos.FacturaPedido(&(m_lPedidos->GetAt(m_lPedidos->FindIndex(i))));
		m_progressBar.SetPos(i+1);
		m_strPedidos.Format(IDC_PEDIDOS, i+1, m_lPedidos->GetCount());
		GetDlgItem(IDC_STATIC_PEDIDO)->SetWindowText(m_strPedidos);;
	}

	SetWindowText("Facturación completa");

	CString strFacturaIni = facturaPedidos.GetFacturaIni();
	CString strFacturaFin = facturaPedidos.GetFacturaFin();

	if (strFacturaIni == strFacturaFin) // Sólo se ha creado una factura
		m_strFacturas.Format(IDC_FACTURA, strFacturaIni);
	else
		m_strFacturas.Format(IDC_FACTURAS, strFacturaIni, strFacturaFin);

	GetDlgItem(IDC_STATIC_FACTURAS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_FACTURAS)->SetWindowText(m_strFacturas);

	// Se muestra los informes de cada una de las facturas
	if (!strFacturaIni.IsEmpty()) // Se comprueba si al menos hay una.
	{
		CDlgInformes dlgInformes;
		dlgInformes.SetDatos(m_db, FACTURA);
		dlgInformes.SetFormula(strFacturaIni, strFacturaFin);
		dlgInformes.DoModal();
	}
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgFacturando::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgFacturando::SetPedidos(CList <CPedidos, CPedidos&> *lPedidos)
{
	m_lPedidos = lPedidos;
}

/******************************************************************************************/
void CDlgFacturando::SetFinAlq(CTime fechaFinAlq)
{
	m_fechaFinAlq = fechaFinAlq;
}

/******************************************************************************************/
void CDlgFacturando::SetTipoFac(int iTipoFac)
{
	m_iTipoFac = iTipoFac;
}

/******************************************************************************************/
void CDlgFacturando::SetContador(int iContador)
{
	m_iContador = iContador;
}

/******************************************************************************************/
/*void CDlgFacturando::FacturaPedidos()
{
	GetDlgItem(IDC_STATIC_PEDIDO)->ShowWindow(SW_SHOW);

	CFacturaPedidos facturaPedidos;
	facturaPedidos.SetConexion(m_db);
	facturaPedidos.SetPedidos(m_lPedidos);
	facturaPedidos.SetFinAlq(m_fechaFinAlq);
	facturaPedidos.SetTipoFac(m_iTipoFac);
	facturaPedidos.SetContador(m_iContador);

	// Se facturan todos los pedidos seleccionados
	for (int i=0; i<m_lPedidos->GetCount(); i++)
	{
//		facturaPedidos.FacturaPedido(&(m_lPedidos->GetAt(m_lPedidos->FindIndex(i))));
		m_progressBar.SetPos(i+1);
		m_strPedidos.Format(IDC_PEDIDOS, i+1, m_lPedidos->GetCount());
		GetDlgItem(IDC_STATIC_PEDIDO)->SetWindowText(m_strPedidos);;
	}
}*/

