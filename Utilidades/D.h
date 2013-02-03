#pragma once


// Cuadro de diálogo de D

class D : public CDialog
{
	DECLARE_DYNAMIC(D)

public:
	D(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~D();

// Datos del cuadro de diálogo
	enum { IDD = 50319 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
};
