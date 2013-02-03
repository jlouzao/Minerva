#pragma once

#include "resource.h"
#include "afxwin.h"
#include "Utilidades.h"
#include "afxcmn.h"

// Cuadro de diálogo de CDlgBuscaVenta

class CDlgBuscaVenta : public CDialog
{
	DECLARE_DYNAMIC(CDlgBuscaVenta)

public:
	CDlgBuscaVenta(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgBuscaVenta();
	virtual BOOL OnInitDialog();

	void SetConexion(CDatabase *db);
	void SetTipo(int iTipo);
	void SetLista(CDialogBusqueda *dlgBusqueda);
	CString GetNumVenta();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_BUSCAVENTA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	DECLARE_MESSAGE_MAP()

public:
	CString m_strNumVenta;
	CString m_strCuenta;
	//CEdit m_cNumOferta;
	afx_msg void OnEnKillfocusNumVenta();
	afx_msg void OnBnClickedBtnVenta();

private: 
	CDatabase *m_db;
	int m_iTipo;
	CDialogBusqueda *m_dlgBusqueda;

	BOOL BuscaNumOferta();
	BOOL BuscaNumPedido();
	BOOL BuscaNumAlbaran();
	void BuscaDesCuenta();
public:
	afx_msg void OnBnClickedOk();
	CString m_strDesCuenta;
};
