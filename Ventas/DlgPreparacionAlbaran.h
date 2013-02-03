#pragma once

#include "resource.h"


// Cuadro de diálogo de CDlgPreparacionAlbaran

class CDlgPreparacionAlbaran : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreparacionAlbaran)

public:
	CDlgPreparacionAlbaran(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgPreparacionAlbaran();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PREPARACION_ALBARAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

private:
	CDatabase *m_db;

	DECLARE_MESSAGE_MAP()
public:
	int m_iTipoAlb;
	afx_msg void OnBnClickedRbtnEntrega();
	afx_msg void OnBnClickedRbtnRecogida();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRbtnDespiece();
	afx_msg void OnBnClickedRbtnDespieceRecogida();
};
