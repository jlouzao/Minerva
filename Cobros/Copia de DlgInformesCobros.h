#pragma once


// Cuadro de diálogo de CDlgInformesCobros

class CDlgInformesCobros : public CDialog
{
	DECLARE_DYNAMIC(CDlgInformesCobros)

public:
	CDlgInformesCobros(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgInformesCobros();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_INFORMES_COBRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
};
