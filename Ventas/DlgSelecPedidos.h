#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "BD.h"
#include "utilidades.h"

// Cuadro de diálogo de CDlgSelecPedidos

class CDlgSelecPedidos : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelecPedidos)

public:
	CDlgSelecPedidos(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgSelecPedidos();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetPedidos(CPedidos *rsPedidos);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_FACPEDIDOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CPedidos *m_rsPedidos;
	CList <CPedidos, CPedidos&> m_lPedidos;

	void RellenaPedidos();
	void PedidosSeleccionados();

public:
	CListCtrl m_lstPedidos;

	BOOL m_bTodos;
	afx_msg void OnBnClickedCheckTodos();	
	afx_msg void OnBnClickedOk();
};
