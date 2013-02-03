// Encriptar.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Encriptar.h"

// CEncriptar

IMPLEMENT_DYNAMIC(CEncriptar, CWnd)
CEncriptar::CEncriptar()
{
}

CEncriptar::~CEncriptar()
{
}


BEGIN_MESSAGE_MAP(CEncriptar, CWnd)
END_MESSAGE_MAP()



// Controladores de mensajes de CEncriptar

/******************************************************************************************/
/**       FUNCIONES                                                                       */
/******************************************************************************************/
void CEncriptar::Encriptar(CString &strPassw)
{
	char caract; //guardamos uno a uno los caracteres
	char valor;
	char cClave;
	CString Clave="zacarias";

	for (int i = 0; i<strPassw.GetLength(); i++)           
    {                         
		caract = strPassw.GetAt(i);
		cClave = Clave.GetAt(i);
		valor = caract+cClave;
		strPassw.SetAt(i,valor);     
    }

	return;
}

/**************************************************************************************/
void CEncriptar::Desencriptar(CString &strPassw)
{
	char caract; //guardamos uno a uno los caracteres
	char valor;
	char cClave;
	CString Clave="zacarias";

	for (int i = 0; i<strPassw.GetLength(); i++)           
    {                                           
		caract=strPassw.GetAt(i);
		cClave=Clave.GetAt(i);
		valor = caract-cClave;
		strPassw.SetAt(i,valor);                     
    }

	return;
}

