#pragma once
#include "afxdtctl.h"
#include "resource.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgCalendario

class CButtonEx : public CButton
{

public:
	CButtonEx();

	//{{AFX_VIRTUAL(CButtonEx)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

	BOOL m_bFestivo;
};

class CDlgCalendario : public CDialog
{
	DECLARE_DYNAMIC(CDlgCalendario)

public:
	CDlgCalendario(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgCalendario();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_CALENDARIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	int m_iAgno;
	int m_iMes;
	int m_iCtrlIDIni;
	UINT m_iEstilo;

	void EscribeCalendario();
	void InicializaBotones();
	void ObtenerFestivos(CStringList &lDiasFestivos);

public:
	CButtonEx m_botones[37];
	CComboBox m_cmbMeses;
	afx_msg void OnCbnSelchangeCmbMeses();
	CDateTimeCtrl m_fechaAgno;
	afx_msg void OnDtnDatetimechangeDateAgno(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtons(UINT nBtn);
	afx_msg void OnBnClickedOk();
};
