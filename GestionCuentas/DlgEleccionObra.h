#pragma once
#include "afxwin.h"
#include "utilidades.h"
#include "BD.h"


// Cuadro de diálogo de CDlgEleccionObra

class CDlgEleccionObra : public CDialog
{
	DECLARE_DYNAMIC(CDlgEleccionObra)

public:
	CDlgEleccionObra(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgEleccionObra();

	virtual BOOL OnInitDialog();
	void SetCliente(CString strAux);//trae el codigo desde donde le llamen
	void SetConexion(CDatabase *db);
// Datos del cuadro de diálogo
	//enum { IDD = IDD_DLG_ELECCION_OBRA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_ctrlObra;
	
	CString strCliente;
	CString m_strObra;
	CString m_strDesObra;

	CDatabase *m_db;
	CDialogBusqueda m_dlgBusquedaDirEnv;

	afx_msg void OnEnKillfocusObra();
	afx_msg void OnBnClickedBuscarObra();
};
