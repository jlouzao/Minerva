// DlgCalendario.cpp: archivo de implementación
//
/********************************************************************************/

#include "stdafx.h"
#include "Ventas.h"
#include "DlgCalendario.h"
#include ".\DlgCalendario.h"
#include "FacturaPedidos.h"

#define NUMBOTONES 37

/********************************************************************************/
CButtonEx::CButtonEx()
{
	m_bFestivo = FALSE;
}

/********************************************************************************/
void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UINT uStyle = DFCS_BUTTONPUSH;

   // This code only works with buttons.
   ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

   // If drawing selected, add the pushed style to DrawFrameControl.
   if (lpDrawItemStruct->itemState & ODS_SELECTED)
      uStyle |= DFCS_PUSHED;

   // Draw the button frame.
   ::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
      DFC_BUTTON, uStyle);

   // Get the button's text.
   CString strText;
   GetWindowText(strText);

   // Draw the button text using the text color red.
   COLORREF crOldColor;
   if (m_bFestivo)
		crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255, 0, 0));
   else
	   	crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(0, 0, 0));

   ::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
      &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
   ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}

/********************************************************************************/
// Cuadro de diálogo de CDlgCalendario
/********************************************************************************/
IMPLEMENT_DYNAMIC(CDlgCalendario, CDialog)
CDlgCalendario::CDlgCalendario(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalendario::IDD, pParent)
{
}

/********************************************************************************/
CDlgCalendario::~CDlgCalendario()
{
}

/********************************************************************************/
void CDlgCalendario::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalendario)

	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_BUTTON1, m_botones[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_botones[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_botones[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_botones[3]);
	DDX_Control(pDX, IDC_BUTTON5, m_botones[4]);
	DDX_Control(pDX, IDC_BUTTON6, m_botones[5]);
	DDX_Control(pDX, IDC_BUTTON7, m_botones[6]);
	DDX_Control(pDX, IDC_BUTTON8, m_botones[7]);
	DDX_Control(pDX, IDC_BUTTON9, m_botones[8]);
	DDX_Control(pDX, IDC_BUTTON10, m_botones[9]);
	DDX_Control(pDX, IDC_BUTTON11, m_botones[10]);
	DDX_Control(pDX, IDC_BUTTON12, m_botones[11]);
	DDX_Control(pDX, IDC_BUTTON13, m_botones[12]);
	DDX_Control(pDX, IDC_BUTTON14, m_botones[13]);
	DDX_Control(pDX, IDC_BUTTON15, m_botones[14]);
	DDX_Control(pDX, IDC_BUTTON16, m_botones[15]);
	DDX_Control(pDX, IDC_BUTTON17, m_botones[16]);
	DDX_Control(pDX, IDC_BUTTON18, m_botones[17]);
	DDX_Control(pDX, IDC_BUTTON19, m_botones[18]);
	DDX_Control(pDX, IDC_BUTTON20, m_botones[19]);
	DDX_Control(pDX, IDC_BUTTON21, m_botones[20]);
	DDX_Control(pDX, IDC_BUTTON22, m_botones[21]);
	DDX_Control(pDX, IDC_BUTTON23, m_botones[22]);
	DDX_Control(pDX, IDC_BUTTON24, m_botones[23]);
	DDX_Control(pDX, IDC_BUTTON25, m_botones[24]);
	DDX_Control(pDX, IDC_BUTTON26, m_botones[25]);
	DDX_Control(pDX, IDC_BUTTON27, m_botones[26]);
	DDX_Control(pDX, IDC_BUTTON28, m_botones[27]);
	DDX_Control(pDX, IDC_BUTTON29, m_botones[28]);
	DDX_Control(pDX, IDC_BUTTON30, m_botones[29]);
	DDX_Control(pDX, IDC_BUTTON31, m_botones[30]);
	DDX_Control(pDX, IDC_BUTTON32, m_botones[31]);
	DDX_Control(pDX, IDC_BUTTON33, m_botones[32]);
	DDX_Control(pDX, IDC_BUTTON34, m_botones[33]);
	DDX_Control(pDX, IDC_BUTTON35, m_botones[34]);
	DDX_Control(pDX, IDC_BUTTON36, m_botones[35]);
	DDX_Control(pDX, IDC_BUTTON37, m_botones[36]);
	DDX_Control(pDX, IDC_CMB_MESES, m_cmbMeses);
	DDX_Control(pDX, IDC_DATE_AGNO, m_fechaAgno);
}


/********************************************************************************/
BEGIN_MESSAGE_MAP(CDlgCalendario, CDialog)
	ON_CBN_SELCHANGE(IDC_CMB_MESES, OnCbnSelchangeCmbMeses)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_AGNO, OnDtnDatetimechangeDateAgno)
	ON_COMMAND_RANGE(IDC_BUTTON1, IDC_BUTTON37, OnBnClickedButtons)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/********************************************************************************/
BOOL CDlgCalendario::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cmbMeses.AddString("Enero");
	m_cmbMeses.AddString("Febrero");
	m_cmbMeses.AddString("Marzo");
	m_cmbMeses.AddString("Abril");
	m_cmbMeses.AddString("Mayo");
	m_cmbMeses.AddString("Junio");
	m_cmbMeses.AddString("Julio");
	m_cmbMeses.AddString("Agosto");
	m_cmbMeses.AddString("Septiembre");
	m_cmbMeses.AddString("Octubre");
	m_cmbMeses.AddString("Noviembre");
	m_cmbMeses.AddString("Diciembre");

	m_fechaAgno.SetFormat("yyyy");

	CTime hoy = CTime::GetCurrentTime();
	m_iAgno = hoy.GetYear();
	m_iMes = hoy.GetMonth();

	// Se guarda el ID del primer boton
	m_iCtrlIDIni = m_botones[0].GetDlgCtrlID();
	
	// Se indica en los botones que ocupan el fin de semana que son dias festivos
	m_botones[5].m_bFestivo = TRUE;
	m_botones[6].m_bFestivo = TRUE;
	m_botones[12].m_bFestivo = TRUE;
	m_botones[13].m_bFestivo = TRUE;
	m_botones[19].m_bFestivo = TRUE;
	m_botones[20].m_bFestivo = TRUE;
	m_botones[26].m_bFestivo = TRUE;
	m_botones[27].m_bFestivo = TRUE;
	m_botones[33].m_bFestivo = TRUE;
	m_botones[34].m_bFestivo = TRUE;

	EscribeCalendario();

	m_cmbMeses.SetCurSel(m_iMes - 1);

	return TRUE;
}

/******************************************************************************************/
void CDlgCalendario::OnCbnSelchangeCmbMeses()
{
	m_iMes = m_cmbMeses.GetCurSel() + 1;
	EscribeCalendario();
}

/******************************************************************************************/
void CDlgCalendario::OnDtnDatetimechangeDateAgno(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	m_iAgno = pDTChange->st.wYear;
	EscribeCalendario();

	*pResult = 0;
}

/******************************************************************************************/
void CDlgCalendario::OnBnClickedButtons(UINT nBtn)
{
	// Se resta el identificador del botón pulsado con el identificador del primer
	// boton. La diferencia será el índice en el array
	int iIndex = nBtn - m_iCtrlIDIni;

	// Si es sábado o domingo no se hace nada, siempre será festivo
	if (iIndex == 5 || iIndex == 6 || iIndex == 12 || iIndex == 13 || iIndex == 19 ||
		iIndex == 20 || iIndex == 26 || iIndex == 27 || iIndex == 33 || iIndex == 34)
		return;

	if (!m_botones[iIndex].m_bFestivo)
		m_botones[iIndex].m_bFestivo = TRUE;
	else
		m_botones[iIndex].m_bFestivo = FALSE;

	m_botones[iIndex].RedrawWindow();
}

/******************************************************************************************/
void CDlgCalendario::OnBnClickedOk()
{
	// Se buscan los días de fiesta del mes en cuestion
	HRESULT hErr = S_OK;
	CFestivos rsFestivos(m_db);
	CStringList lDiasFestivos;
	CString strDia;
	BOOL bYaFestivo;

	// Se guardan los días de fiesta indicados y se eliminan los que se hayan podido
	// quitar

	ObtenerFestivos(lDiasFestivos);

	if (!m_db->BeginTrans())
		return;

	for (int i=0; i<NUMBOTONES && hErr == S_OK; i++)
	{
		bYaFestivo = FALSE;

		// Se busca si el día está ya en la tabla
		m_botones[i].GetWindowText(strDia);
		if ( (lDiasFestivos.Find(strDia)) != NULL)
			bYaFestivo = TRUE;		

		// Se inserta en la tabla si es y todavía no está en la tabla
		if (m_botones[i].m_bFestivo && !bYaFestivo)
		{
			// Si es sábado o domingo no se guardan en la tabla
			if (i != 5 && i != 6 && i != 12 && i != 13 && i != 19 &&
				i != 20 && i != 26 && i != 27 && i != 33 && i != 34)
			{
				CTime festivo(m_iAgno, m_iMes, atoi(strDia), 0, 0, 0);
				rsFestivos.m_DIA = festivo;
				hErr = rsFestivos.Insert();
			}
		}
		// Si no es festivo y está en la tabla se elimina de ella
		else if (!m_botones[i].m_bFestivo && bYaFestivo)
		{
			CTime NoFestivo(m_iAgno, m_iMes, atoi(strDia), 0, 0, 0);
			rsFestivos.m_DIA = NoFestivo;
			hErr = rsFestivos.DeleteFestivo();
		}
	}

	if (hErr == S_OK)
		m_db->CommitTrans();
	else
		m_db->Rollback();

	//OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgCalendario::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgCalendario::EscribeCalendario()
{
	int iPosInicio = 0;
	CFacturaPedidos facturaPedidos;
	facturaPedidos.SetConexion(m_db);
	CStringList lDiasFestivos;

	InicializaBotones();

	ObtenerFestivos(lDiasFestivos);

	CTime fecha(m_iAgno, m_iMes, 1, 0, 0, 0);

	// Lunes (2), Martes (3), Miércoles (4), Jueves (5) , Viernes (6),
	// Sábado (7), Domingo (1)
	int iDiaSemana = fecha.GetDayOfWeek();

	// Si el día de la semana es el domingo (1) irá en la posición 6. Si no, basta
	// con restarle 2 para obtener la posición deseada del array
	if (iDiaSemana == 1)
		iPosInicio = 6;
	else 
		iPosInicio = iDiaSemana - 2;

	CString strNumDia;
	int iNumDia = 1;
	int iNumDiasMes = facturaPedidos.CalculaDiasMes(m_iMes, m_iAgno);

	for (int i=0; i<NUMBOTONES; i++)
	{
		if ( i < iPosInicio || i >= iPosInicio + iNumDiasMes)
			//m_botones[i].ShowWindow(SW_HIDE);
			m_botones[i].SetWindowText("");
		else
		{	
			// Si está en la lista de festivos se indica
			CString strDia;
			strDia.Format("%d", iNumDia);
			if ( (lDiasFestivos.Find(strDia)) != NULL)
				m_botones[i].m_bFestivo = TRUE;

			m_botones[i].ShowWindow(SW_SHOW);
			strNumDia.Format("%d", iNumDia);	
			m_botones[i].SetWindowText(strNumDia);

			iNumDia++;
		}			
	}
}

/******************************************************************************************/
void CDlgCalendario::InicializaBotones()
{
	m_botones[0].m_bFestivo = FALSE;
	m_botones[1].m_bFestivo = FALSE;
	m_botones[2].m_bFestivo = FALSE;
	m_botones[3].m_bFestivo = FALSE;
	m_botones[4].m_bFestivo = FALSE;

	m_botones[7].m_bFestivo = FALSE;
	m_botones[8].m_bFestivo = FALSE;
	m_botones[9].m_bFestivo = FALSE;
	m_botones[10].m_bFestivo = FALSE;
	m_botones[11].m_bFestivo = FALSE;

	m_botones[14].m_bFestivo = FALSE;
	m_botones[15].m_bFestivo = FALSE;
	m_botones[16].m_bFestivo = FALSE;
	m_botones[17].m_bFestivo = FALSE;
	m_botones[18].m_bFestivo = FALSE;

	m_botones[21].m_bFestivo = FALSE;
	m_botones[22].m_bFestivo = FALSE;
	m_botones[23].m_bFestivo = FALSE;
	m_botones[24].m_bFestivo = FALSE;
	m_botones[25].m_bFestivo = FALSE;

	m_botones[28].m_bFestivo = FALSE;
	m_botones[29].m_bFestivo = FALSE;
	m_botones[30].m_bFestivo = FALSE;
	m_botones[31].m_bFestivo = FALSE;
	m_botones[32].m_bFestivo = FALSE;

	m_botones[35].m_bFestivo = FALSE;
	m_botones[36].m_bFestivo = FALSE;
}

/******************************************************************************************/
void CDlgCalendario::ObtenerFestivos(CStringList &lDiasFestivos)
{
	CFacturaPedidos facturaPedidos;
	facturaPedidos.SetConexion(m_db);
	CFestivos rsFestivos(m_db);
	CString strFechaIni, strFechaFin;

	int iNumDiasMes = facturaPedidos.CalculaDiasMes(m_iMes, m_iAgno);
	CTime fechaIni (m_iAgno, m_iMes, 1, 0, 0, 0);
	CTime fechaFin (m_iAgno, m_iMes, iNumDiasMes, 0, 0, 0);

	strFechaIni = fechaIni.Format("%d/%m/%Y");
	strFechaFin = fechaFin.Format("%d/%m/%Y");

	rsFestivos.m_strFilter = "DIA >= '" + strFechaIni + "' AND DIA <= '" + strFechaFin + "'";

	if (!rsFestivos.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	CString strDia;
	while (!rsFestivos.IsEOF())
	{
		int iDia = rsFestivos.m_DIA.GetDay();
		strDia.Format("%d", iDia);
		lDiasFestivos.AddTail(strDia);
		rsFestivos.MoveNext();
	}

	rsFestivos.Close();

	return;
}