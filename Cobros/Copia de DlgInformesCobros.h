#pragma once


// Cuadro de di�logo de CDlgInformesCobros

class CDlgInformesCobros : public CDialog
{
	DECLARE_DYNAMIC(CDlgInformesCobros)

public:
	CDlgInformesCobros(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~CDlgInformesCobros();

// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_INFORMES_COBRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
};
