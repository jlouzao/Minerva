#pragma once

#include "resource.h"
#include "atltime.h"
#include "Utilidades.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgExistencias

class CDlgExistencias : public CDialog
{
	DECLARE_DYNAMIC(CDlgExistencias)

public:
	CDlgExistencias(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgExistencias();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

	CDialogBusqueda m_dlgBusquedaArticulo;

	BOOL BuscaArticulo();


// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_EXISTENCIAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCodArticulo;
	CString m_strDesArticulo;
	CTime m_timeFecha;

private:
	CDatabase *m_db;

public:
	afx_msg void OnBnClickedBtnArticulo();
	afx_msg void OnEnKillfocusEditCodarticulo();
	afx_msg void OnBnClickedOk();
	CEdit m_ctrlCodArticulo;
};
