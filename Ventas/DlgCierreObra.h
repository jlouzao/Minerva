#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "utilidades.h"

// Cuadro de di�logo de CDlgCierreObra

class CDlgCierreObra : public CDialog
{
	DECLARE_DYNAMIC(CDlgCierreObra)

public:
	CDlgCierreObra(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~CDlgCierreObra();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetConsulta(BOOL bConsulta);
	void SetDatos(CString strCliente, CString strObra);

// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_CIERRE_OBRA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CString m_strCliente;
	CString m_strObra;
	BOOL m_bConsulta;

	void CierreObra();

public:
	//CListCtrl m_lstArticulos;
	CReportCtrl m_lstArticulos;
};
