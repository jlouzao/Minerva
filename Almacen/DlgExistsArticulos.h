#pragma once
#include "afxcmn.h"

#include "resource.h"
#include "afxwin.h"


// Cuadro de diálogo de CDlgExistsArticulos

class CDlgExistsArticulos : public CDialog
{
	DECLARE_DYNAMIC(CDlgExistsArticulos)

public:
	CDlgExistsArticulos(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgExistsArticulos();

	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetCodArticulo(CString &strCodArti);
	void SetDesArticulo(CString &strDesArti);
	void SetFecha(CTime timeFecha);
	void CargarExistencias();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_EXITS_ARTICULOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CString m_strCodArti;
	CString m_strDesArti;
	CString m_strFecha;
	CTime m_timeFecha;
	CString m_strSumaTotales;
	CString m_strSumaDisponibles;

public:
	//CString m_strArticulo;
	CListCtrl m_lstExistencias;
};
