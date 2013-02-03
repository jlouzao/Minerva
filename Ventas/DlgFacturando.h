#pragma once

#include "BD.h"
#include "afxcmn.h"


// Cuadro de diálogo de CDlgFacturando

class CDlgFacturando : public CDialog
{
	DECLARE_DYNAMIC(CDlgFacturando)

public:
	CDlgFacturando(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgFacturando();
	virtual BOOL OnInitDialog();

	void SetConexion(CDatabase *db);
	void SetPedidos(CList <CPedidos, CPedidos&> *lPedidos);
	void SetFinAlq(CTime fechaFinAlq);
	void SetTipoFac(int iTipoFac);
	void SetContador(int iContador);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_FACTURANDO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CList <CPedidos, CPedidos&> *m_lPedidos;
	int m_iTipoFac;
	int m_iContador;
	CTime m_fechaFinAlq;
	int m_TotalFacturas;

	//void FacturaPedidos();

public:
	CProgressCtrl m_progressBar;
	CString m_strPedidos;
	CString m_strFacturas;
	afx_msg void OnBnClickedBtnIniciar();
	CString m_strNumPedidos;
	CString m_strFecha;
	CString m_strTipo;
	CString m_strContador;
};
