#pragma once
#include "atltime.h"

#include "resource.h"

// Cuadro de diálogo de CDlgDatosAlbaran

class CDlgDatosAlbaran : public CDialog
{
	DECLARE_DYNAMIC(CDlgDatosAlbaran)

public:
	CDlgDatosAlbaran(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDatosAlbaran();
	void SetConexion(CDatabase *db);
	CString GetObservaciones();
	CTime GetFechaIniAlq();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DATOS_ALBARAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CTime m_timeIniAlquiler;
	CString m_strObsAlbaran;
	afx_msg void OnBnClickedOk();

private:
	CDatabase *m_db;
};
