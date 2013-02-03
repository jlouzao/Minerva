#include "stdafx.h"
#include "DlgInformes.h"
#include "crystalctrl.h"

// Cuadro de diálogo de CInformes

IMPLEMENT_DYNAMIC(CDlgInformes, CDialog)
CDlgInformes::CDlgInformes(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInformes::IDD, pParent)
	, iSalida(PANTALLA)
{
}
/************************************************************************************************/
CDlgInformes::~CDlgInformes()
{
}
/************************************************************************************************/
void CDlgInformes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_TIPO1, iSalida);
	DDX_Control(pDX, IDC_LISTA_INFORMES, m_listReportes);
}
/************************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgInformes, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_TIPO1, OnBnClickedTipo1)
	ON_BN_CLICKED(IDC_TIPO2, OnBnClickedTipo2)
//	ON_WM_SETFOCUS(50319, OnSetFocus)
END_MESSAGE_MAP()
/************************************************************************************************/
BOOL CDlgInformes::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch (m_iTipo)
	{
		case FACTURA:
			CrearListaFactura();
			break;
		case FACTURA_ORIGEN:
			CrearListaFacturaOrigen();
			break;
		case OFERTA:
			CrearListaOferta();
			break;
		case PEDIDO:
			CrearListaPedido();
			break;
		case ALBARAN:
			CrearListaAlbaran();
			break;
		case COBRO:
			CrearListaCobros();
			break;
	}
	DatosInforme datosInforme;
	for (int i=0; i<m_lInformes.GetCount(); i++)
	{
		datosInforme=m_lInformes.GetAt(m_lInformes.FindIndex(i));
		m_listReportes.AddString(datosInforme.strTexto);
	}
	m_listReportes.SetCurSel(0);
	UpdateData(FALSE);

	return TRUE;
}
/************************************************************************************************/
void CDlgInformes::OnBnClickedTipo1()
{
	iSalida=PANTALLA;
}
/************************************************************************************************/
void CDlgInformes::OnBnClickedTipo2()
{
	iSalida=IMPRESORA;
}
/************************************************************************************************/
void CDlgInformes::OnBnClickedOk()
{
	CString strNombre, strBD;
	strBD = m_db->GetDatabaseName();
	
	DatosInforme datosInforme;
	datosInforme=m_lInformes.GetAt(m_lInformes.FindIndex(m_listReportes.GetCurSel()));
	strNombre=datosInforme.strRPT;

	/**** Conseguir el path para los reportes ****/
	CString strAppDir = AfxGetApp()->m_pszHelpFilePath;
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\')+1) + PATH;
	
	strNombre=strAppDir + strNombre + strBD + ".rpt";//c:\\minervaapp\\bin
	
	CCrystalCtrl   *m_cryscontrol = ( CCrystalCtrl*)( GetDlgItem(IDC_CRYSTALREPORT1));
	
	m_cryscontrol->SetWindowTitle("Informes");
	m_cryscontrol->SetReportFileName(strNombre);
	m_cryscontrol->SetSelectionFormula(m_strFormula);
	m_cryscontrol->SetDestination(iSalida); //para pasarlo por pantalla, impresora o archivo
	m_cryscontrol->SetDiscardSavedData(TRUE);
	m_cryscontrol->SetAction(TRUE); 

	//while (m_cryscontrol->GetWindowState() == 3);
	//UpdateData(TRUE);

	//	while (m_cryscontrol != NULL);
	//	while (m_cryscontrol->IsWindowEnabled());

	//OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgInformes::SetDatos(CDatabase *db, int iTipo)
{
	m_db=db;
	m_iTipo = iTipo;
}

/******************************************************************************************/
void CDlgInformes::SetFormula(CString strElemento1, CString strElemento2, CTime fecha1, CTime fecha2,
	CString strCuenta1, CString strCuenta2, CString strCentro1, CString strCentro2, 
	CString strEstado1, CString strEstado2)
{
	CString strTabla, strCampoElem, strCampoFecha;

	switch (m_iTipo)
	{
		case OFERTA:
			strTabla = "PROFORMA";
			strCampoElem = "{PROFORMA.NUMPROFOR}";
			strCampoFecha = "{PROFORMA.FECHPROF}";
			break;

		case PEDIDO:
			strTabla = "PEDIDOS";
			strCampoElem = "{PEDIDOS.NUMPEDIDO}";
			strCampoFecha = "{PEDIDOS.FECHPED}";
			break;

		case ALBARAN:
			strTabla = "ALBARANE";
			strCampoElem = "{ALBARANE.NUMALB}";
			strCampoFecha = "{ALBARANE.FECHALB}";
			break;

		case FACTURA:
			strTabla = "FACTURAS";
			strCampoElem = "{FACTURAS.NUMFAC}";
			strCampoFecha = "{FACTURAS.FECHFAC}";
			break;

		case FACTURA_ORIGEN:
			strTabla = "FACTURAS";
			strCampoElem = "{FACTURAS.NUMFAC}";
			strCampoFecha = "{FACTURAS.FECHFAC}";
			break;

		case COBRO:
			strTabla = "COBROS";
			strCampoElem = "{COBROS.NUMFAC}";
			strCampoFecha = "{COBROS.FECHLIBRA}";
			break;
	}

	if (fecha1 != NULL || fecha2 != NULL)
	{
		if (fecha1 == NULL)
		{
			CTime fechaAux(1980, 1, 1, 0, 0, 0);
			fecha1 = fechaAux; // Se asigna una fecha menor que cualquier otra
		}

		if (fecha2 == NULL)
		{
			CTime fechaAux(2100, 1, 1, 0, 0, 0);
			fecha2 = fechaAux; // Se asigna una fecha mayor que cualquier otra
		}

		CString strFecha1, strFecha2;
		strFecha1.Format("(%d, %d, %d)", fecha1.GetYear(), fecha1.GetMonth(), fecha1.GetDay());
		strFecha2.Format("(%d, %d, %d)", fecha2.GetYear(), fecha2.GetMonth(), fecha2.GetDay());

		m_strFormula = strCampoFecha + " IN DATE " + strFecha1 + " TO DATE " + strFecha2;
	}

	if (!strElemento1.IsEmpty() || !strElemento2.IsEmpty())
	{
		if (strElemento1.IsEmpty())
			strElemento1 = " ";  // Se asigna un ascii inferior a cualquier número de factura

		if (strElemento2.IsEmpty())
			strElemento2 = "º";  // Se asigna un ascii mayor a cualquier número de factura

		if (!m_strFormula.IsEmpty())
			m_strFormula += " AND ";

		m_strFormula += strCampoElem + " IN '" + strElemento1 + "' TO '" + strElemento2 + "'";
	}

	if (!strCuenta1.IsEmpty() || !strCuenta2.IsEmpty())
	{
		if (strCuenta1.IsEmpty())
			strCuenta1 = " ";  // Se asigna un ascii inferior a cualquier número de cuenta

		if (strCuenta2.IsEmpty())
			strCuenta2 = "º";  // Se asigna un ascii mayor a cualquier número de cuenta

		if (!m_strFormula.IsEmpty())
			m_strFormula += " AND ";

		m_strFormula += "{" + strTabla + ".CUENTA} IN '" + strCuenta1 + "' TO '" + strCuenta2 + "'";
	}

	if (!strCentro1.IsEmpty() || !strCentro2.IsEmpty())
	{
		if (strCentro1.IsEmpty())
			strCentro1 = " ";  // Se asigna un ascii inferior a cualquier centro

		if (strCuenta2.IsEmpty())
			strCentro2 = "º";  // Se asigna un ascii mayor a cualquier centro

		if (!m_strFormula.IsEmpty())
			m_strFormula += " AND ";

		m_strFormula += "{" + strTabla + ".CENTRO} IN '" + strCentro1 + "' TO '" + strCentro2 + "'";
	}

	if (!strEstado1.IsEmpty() || !strEstado2.IsEmpty())
	{
		if (strEstado1.IsEmpty())
			strEstado1 = " ";  // Se asigna un ascii inferior a cualquier estado

		if (strEstado2.IsEmpty())
			strEstado2 = "º";  // Se asigna un ascii mayor a cualquier estado

		if (!m_strFormula.IsEmpty())
			m_strFormula += " AND ";

		m_strFormula += "{" + strTabla + ".ESTADO} IN '" + strEstado1 + "' TO '" + strEstado2 + "'";
	}
}

/******************************************************************************************/
void CDlgInformes::CrearListaFactura()
{
	DatosInforme datosInforme;

	datosInforme.strTexto = FAC1;
	datosInforme.strRPT = FACRTP1;

	m_lInformes.AddTail(datosInforme);
}

/******************************************************************************************/
void CDlgInformes::CrearListaFacturaOrigen()
{
	DatosInforme datosInforme;

	datosInforme.strTexto = FACORIG1;
	datosInforme.strRPT = FACORIGRTP1;

	m_lInformes.AddTail(datosInforme);
}

/************************************************************************************************/
void CDlgInformes::CrearListaAlbaran()
{
	DatosInforme datosInforme;

	datosInforme.strTexto = ALB1;
	datosInforme.strRPT = ALBRTP1;

	m_lInformes.AddTail(datosInforme);

	/*datosInforme.strTexto = ALB2;
	datosInforme.strRPT = ALBRTP2;

	m_lInformes.AddTail(datosInforme);*/
}
/************************************************************************************************/
void CDlgInformes::CrearListaOferta()
{
	DatosInforme datosInforme;

	datosInforme.strTexto = OFE1;
	datosInforme.strRPT = OFERTP1;

	m_lInformes.AddTail(datosInforme);
}
/************************************************************************************************/
void CDlgInformes::CrearListaPedido()
{
	DatosInforme datosInforme;

	datosInforme.strTexto = PED1;
	datosInforme.strRPT = PEDRTP1;

	m_lInformes.AddTail(datosInforme);

	datosInforme.strTexto = PED2;
	datosInforme.strRPT = PEDRTP2;

	m_lInformes.AddTail(datosInforme);

}

/************************************************************************************************/
void CDlgInformes::CrearListaCobros()
{
	DatosInforme datosInforme;

	datosInforme.strTexto = COBROS1;
	datosInforme.strRPT = COBROSRTP1;

	m_lInformes.AddTail(datosInforme);
}

/************************************************************************************************/
/*void CDlgInformes::OnSetFocus(CWnd* pOldWnd)
{
	//AfxMessageBox("Entro");
}*/