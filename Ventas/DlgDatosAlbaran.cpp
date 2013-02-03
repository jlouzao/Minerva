/**************************************************************************************/
// DlgDatosAlbaran.cpp: archivo de implementación
//
/**************************************************************************************/

#include "stdafx.h"
#include "DlgDatosAlbaran.h"
#include ".\dlgdatosalbaran.h"

/**************************************************************************************/
// Cuadro de diálogo de CDlgDatosAlbaran
/**************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgDatosAlbaran, CDialog)
CDlgDatosAlbaran::CDlgDatosAlbaran(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDatosAlbaran::IDD, pParent)
	, m_timeIniAlquiler(0)
	, m_strObsAlbaran(_T(""))
{
	m_timeIniAlquiler = CTime::GetCurrentTime();
}

/**************************************************************************************/
CDlgDatosAlbaran::~CDlgDatosAlbaran()
{
}

/**************************************************************************************/
void CDlgDatosAlbaran::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_INI_ALQUILER, m_timeIniAlquiler);
	DDX_Text(pDX, IDC_OBSER_ALBARAN, m_strObsAlbaran);
	DDV_MaxChars(pDX, m_strObsAlbaran, 100);
}

/**************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgDatosAlbaran, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgDatosAlbaran
/**************************************************************************************/

/**************************************************************************************/

void CDlgDatosAlbaran::OnBnClickedOk()
{
	UpdateData();
	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgDatosAlbaran::SetConexion(CDatabase *db)
{
	m_db = db;
}


/******************************************************************************************/
CString CDlgDatosAlbaran::GetObservaciones()
{
	return m_strObsAlbaran;
}

/******************************************************************************************/
CTime CDlgDatosAlbaran::GetFechaIniAlq()
{
	return m_timeIniAlquiler;
}
