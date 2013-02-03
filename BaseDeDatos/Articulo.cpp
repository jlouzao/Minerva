// Articulo.h: implementación de la clase CArticulo



// Implementación de CArticulo

// código generado el miércoles, 15 de junio de 2005, 9:31

#include "stdafx.h"
#include "Articulo.h"
IMPLEMENT_DYNAMIC(CArticulo, CRecordset)

CArticulo::CArticulo(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ARTI = "";
	m_DESARTI = "";
	m_CODALT = "";
	m_TARI1 = 0.0;
	m_TARI2 = 0.0;
	m_IVARTI = 0.0;
	m_DTOARTI = 0.0;
	m_PA = "";
	m_CODFAM = "";
	m_CODSEC = "";
	m_PROVE = "";
	m_MARCA = "";
	m_OBSER = "";
	m_TIPO = 0.0;
	m_PESO = 0.0;
	m_UNI = "";
	m_COSLIFO = 0.0;
	m_COSFIFO = 0.0;
	m_COSPMC = 0.0;
	m_COMISI = 0.0;
	m_COMIPTS = 0.0;
	m_FABRI = "";
	m_FECHATA1;
	m_FECHATA2;
	m_COSMCOM = 0.0;
	m_FECHAMPC;
	m_NUMFACMPC = "";
	m_CALIA1 = "";
	m_CALIA2 = "";
	m_CALIA3 = "";
	m_CALIA4 = "";
	m_CALIA5 = "";
	m_TARIA2 = 0.0;
	m_TARIA3 = 0.0;
	m_TARIA4 = 0.0;
	m_TARIA5 = 0.0;
	m_NUMCAJAS = 0.0;
	m_METCAJAS = 0.0;
	m_METPALET = 0.0;
	m_CALIB1 = "";
	m_CALIB2 = "";
	m_CALIB3 = "";
	m_CALIB4 = "";
	m_CALIB5 = "";
	m_TARIB1 = 0.0;
	m_TARIB2 = 0.0;
	m_TARIB3 = 0.0;
	m_TARIB4 = 0.0;
	m_TARIB5 = 0.0;
	m_CALIC1 = "";
	m_CALIC2 = "";
	m_CALIC3 = "";
	m_CALIC4 = "";
	m_CALIC5 = "";
	m_TARIC1 = 0.0;
	m_TARIC2 = 0.0;
	m_TARIC3 = 0.0;
	m_TARIC4 = 0.0;
	m_TARIC5 = 0.0;
	m_TARVEN = 0.0;
	m_CUENTA = "";
	m_DTOARCO = 0.0;
	m_STKMIN = 0.0;
	m_CANTREP = 0.0;
	m_PROVE1 = "";
	m_PROVE2 = "";
	m_PROVE3 = "";
	m_FECHAA;
	m_FECHAB;
	m_FECHAC;
	m_TARI2A = 0.0;
	m_TARI2B = 0.0;
	m_TARI2C = 0.0;
	m_DTOARTA = 0.0;
	m_DTOARTB = 0.0;
	m_DTOARTC = 0.0;
	m_NOMPRO1 = "";
	m_NOMPRO2 = "";
	m_NOMPRO3 = "";
	m_DESARTI1 = "";
	m_PZMETRO = 0.0;
	m_CTAVTA = "";
	m_SUPLEM = 0.0;
	m_DESARTI2 = "";
	m_DESARTI3 = "";
	m_RECARGO = 0.0;
	m_FECALTA;
	m_FECBAJA;
	m_UBIX = "";
	m_UBIY = "";
	m_UBIZ = "";
	m_ARTCAR10 = "";
	m_ART1CAR = "";
	m_ARTNUMER = 0.0;
	m_DSUPLEM = "";
	m_ARTNUME2 = 0.0;
	m_ARTNUME3 = 0.0;
	m_ARTNUME4 = 0.0;
	m_PROPOR = "";
	m_ALQUILER = "";
	m_FECALQ;
	m_FECFIN;
	m_CONTRATO = "";
	m_TIPOALQ = "";
	m_ULTIFACT;
	m_CLIENTE = "";
	m_NUMALB = "";
	m_ALQUIDES1 = "";
	m_ALQUIDES2 = "";
	m_ALQUIDES3 = "";
	m_ALQUIDES4 = "";
	m_ALQUIDES5 = "";
	m_ALQUINUM1 = 0.0;
	m_ALQUINUM2 = 0.0;
	m_ALQUINUM3 = 0.0;
	m_ALQUINUM4 = 0.0;
	m_ALQUINUM5 = 0.0;
	m_APLICADA = 0.0;
	m_DTOAPLI = 0.0;
	m_MOVALM = "";
	m_GENERICO = 0;
	m_PROPOROL = "";
	m_EAPLICADA = 0.0;
	m_EALQUINUM1 = 0.0;
	m_EALQUINUM2 = 0.0;
	m_EALQUINUM3 = 0.0;
	m_EALQUINUM4 = 0.0;
	m_EALQUINUM5 = 0.0;
	m_CODPROV = "";
	m_DESPROV = "";
	m_DESARTIOLD = "";
	m_CTAALQ = "";
	m_ALQUILADO = "";
	m_ETARI1 = 0.0;
	m_ETARIB1 = 0.0;
	m_ETARIC1 = 0.0;
	m_CFAMI = "";
	m_FORMATO = "";
	m_SERIE = "";
	m_PASTA = "";
	m_ETARI2 = 0.0;
	m_ECOSLIFO = 0.0;
	m_ECOSFIFO = 0.0;
	m_ECOSPMC = 0.0;
	m_BLOQUEO = 0.0;
	m_DESARMEMO = "";
	m_CSUBFAM = "";
	m_DTOTAR1 = 0.0;
	m_DTOTARB1 = 0.0;
	m_DTOTARC1 = 0.0;
	m_PTOVERDE = 0.0;
	m_ETARID1 = 0.0;
	m_ETARIE1 = 0.0;
	m_ETARIF1 = 0.0;
	m_ETARIG1 = 0.0;
	m_ETARIH1 = 0.0;
	m_ETARII1 = 0.0;
	m_DTOTARD1 = 0.0;
	m_DTOTARE1 = 0.0;
	m_DTOTARF1 = 0.0;
	m_DTOTARG1 = 0.0;
	m_DTOTARH1 = 0.0;
	m_DTOTARI1 = 0.0;
	m_TARID5 = 0.0;
	m_TARIE5 = 0.0;
	m_TARIF5 = 0.0;
	m_TARIG5 = 0.0;
	m_TARIH5 = 0.0;
	m_TARII5 = 0.0;
	m_TARIJ5 = 0.0;
	m_DTOARTD = 0.0;
	m_DTOARTE = 0.0;
	m_DTOARTF = 0.0;
	m_DTOARTG = 0.0;
	m_DTOARTH = 0.0;
	m_DTOARTII = 0.0;
	m_DTOARTJ = 0.0;
	m_PROVE4 = "";
	m_PROVE5 = "";
	m_PROVE6 = "";
	m_PROVE7 = "";
	m_PROVE8 = "";
	m_PROVE9 = "";
	m_PROVE10 = "";
	m_UA = "";
	m_APLIDCTOS = "";
	m_APLIDCTOS2 = "";
	m_APLIDCTOS3 = "";
	m_APLIDCTOS4 = "";
	m_APLIPP = "";
	m_EUROSUV = 0.0;
	m_nFields = 191;
	m_nDefaultType = dynaset;
}
//#error Problema de seguridad: la cadena de conexión puede contener una contraseña
// La cadena de conexión siguiente puede contener contraseñas de texto sin formato/u
// otro tipo de información reservada. Quite #error después de revisar
// la cadena de conexión relacionada con los problemas de seguridad. Puede que desee
// almacenar la contraseña en otro formulario o utilizar una autenticación de usuario diferente.
CString CArticulo::GetDefaultConnect()
{
	return _T("DSN=minerva;Description=minerva;APP=Microsoft\x00ae Visual Studio .NET;WSID=AUXSIS-003;Trusted_Connection=Yes");
}

CString CArticulo::GetDefaultSQL()
{
	return _T("[dbo].[ARTICULO]");
}

void CArticulo::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Las macros como RFX_Text() y RFX_Int() dependen del
// tipo de variable miembro, no del tipo de campo de base de datos.
// ODBC intentará convertir automáticamente el valor de columna en el tipo solicitado
	RFX_Text(pFX, _T("[ARTI]"), m_ARTI);
	RFX_Text(pFX, _T("[DESARTI]"), m_DESARTI);
	RFX_Text(pFX, _T("[CODALT]"), m_CODALT);
	RFX_Double(pFX, _T("[TARI1]"), m_TARI1);
	RFX_Double(pFX, _T("[TARI2]"), m_TARI2);
	RFX_Double(pFX, _T("[IVARTI]"), m_IVARTI);
	RFX_Double(pFX, _T("[DTOARTI]"), m_DTOARTI);
	RFX_Text(pFX, _T("[PA]"), m_PA);
	RFX_Text(pFX, _T("[CODFAM]"), m_CODFAM);
	RFX_Text(pFX, _T("[CODSEC]"), m_CODSEC);
	RFX_Text(pFX, _T("[PROVE]"), m_PROVE);
	RFX_Text(pFX, _T("[MARCA]"), m_MARCA);
	RFX_Text(pFX, _T("[OBSER]"), m_OBSER);
	RFX_Double(pFX, _T("[TIPO]"), m_TIPO);
	RFX_Double(pFX, _T("[PESO]"), m_PESO);
	RFX_Text(pFX, _T("[UNI]"), m_UNI);
	RFX_Double(pFX, _T("[COSLIFO]"), m_COSLIFO);
	RFX_Double(pFX, _T("[COSFIFO]"), m_COSFIFO);
	RFX_Double(pFX, _T("[COSPMC]"), m_COSPMC);
	RFX_Double(pFX, _T("[COMISI]"), m_COMISI);
	RFX_Double(pFX, _T("[COMIPTS]"), m_COMIPTS);
	RFX_Text(pFX, _T("[FABRI]"), m_FABRI);
	RFX_Date(pFX, _T("[FECHATA1]"), m_FECHATA1);
	RFX_Date(pFX, _T("[FECHATA2]"), m_FECHATA2);
	RFX_Double(pFX, _T("[COSMCOM]"), m_COSMCOM);
	RFX_Date(pFX, _T("[FECHAMPC]"), m_FECHAMPC);
	RFX_Text(pFX, _T("[NUMFACMPC]"), m_NUMFACMPC);
	RFX_Text(pFX, _T("[CALIA1]"), m_CALIA1);
	RFX_Text(pFX, _T("[CALIA2]"), m_CALIA2);
	RFX_Text(pFX, _T("[CALIA3]"), m_CALIA3);
	RFX_Text(pFX, _T("[CALIA4]"), m_CALIA4);
	RFX_Text(pFX, _T("[CALIA5]"), m_CALIA5);
	RFX_Double(pFX, _T("[TARIA2]"), m_TARIA2);
	RFX_Double(pFX, _T("[TARIA3]"), m_TARIA3);
	RFX_Double(pFX, _T("[TARIA4]"), m_TARIA4);
	RFX_Double(pFX, _T("[TARIA5]"), m_TARIA5);
	RFX_Double(pFX, _T("[NUMCAJAS]"), m_NUMCAJAS);
	RFX_Double(pFX, _T("[METCAJAS]"), m_METCAJAS);
	RFX_Double(pFX, _T("[METPALET]"), m_METPALET);
	RFX_Text(pFX, _T("[CALIB1]"), m_CALIB1);
	RFX_Text(pFX, _T("[CALIB2]"), m_CALIB2);
	RFX_Text(pFX, _T("[CALIB3]"), m_CALIB3);
	RFX_Text(pFX, _T("[CALIB4]"), m_CALIB4);
	RFX_Text(pFX, _T("[CALIB5]"), m_CALIB5);
	RFX_Double(pFX, _T("[TARIB1]"), m_TARIB1);
	RFX_Double(pFX, _T("[TARIB2]"), m_TARIB2);
	RFX_Double(pFX, _T("[TARIB3]"), m_TARIB3);
	RFX_Double(pFX, _T("[TARIB4]"), m_TARIB4);
	RFX_Double(pFX, _T("[TARIB5]"), m_TARIB5);
	RFX_Text(pFX, _T("[CALIC1]"), m_CALIC1);
	RFX_Text(pFX, _T("[CALIC2]"), m_CALIC2);
	RFX_Text(pFX, _T("[CALIC3]"), m_CALIC3);
	RFX_Text(pFX, _T("[CALIC4]"), m_CALIC4);
	RFX_Text(pFX, _T("[CALIC5]"), m_CALIC5);
	RFX_Double(pFX, _T("[TARIC1]"), m_TARIC1);
	RFX_Double(pFX, _T("[TARIC2]"), m_TARIC2);
	RFX_Double(pFX, _T("[TARIC3]"), m_TARIC3);
	RFX_Double(pFX, _T("[TARIC4]"), m_TARIC4);
	RFX_Double(pFX, _T("[TARIC5]"), m_TARIC5);
	RFX_Text(pFX, _T("[CUENTA]"), m_CUENTA);
	RFX_Double(pFX, _T("[DTOARCO]"), m_DTOARCO);
	RFX_Double(pFX, _T("[STKMIN]"), m_STKMIN);
	RFX_Double(pFX, _T("[CANTREP]"), m_CANTREP);
	RFX_Text(pFX, _T("[PROVE1]"), m_PROVE1);
	RFX_Text(pFX, _T("[PROVE2]"), m_PROVE2);
	RFX_Text(pFX, _T("[PROVE3]"), m_PROVE3);
	RFX_Date(pFX, _T("[FECHAA]"), m_FECHAA);
	RFX_Date(pFX, _T("[FECHAB]"), m_FECHAB);
	RFX_Date(pFX, _T("[FECHAC]"), m_FECHAC);
	RFX_Double(pFX, _T("[TARI2A]"), m_TARI2A);
	RFX_Double(pFX, _T("[TARI2B]"), m_TARI2B);
	RFX_Double(pFX, _T("[TARI2C]"), m_TARI2C);
	RFX_Double(pFX, _T("[DTOARTA]"), m_DTOARTA);
	RFX_Double(pFX, _T("[DTOARTB]"), m_DTOARTB);
	RFX_Double(pFX, _T("[DTOARTC]"), m_DTOARTC);
	RFX_Text(pFX, _T("[NOMPRO1]"), m_NOMPRO1);
	RFX_Text(pFX, _T("[NOMPRO2]"), m_NOMPRO2);
	RFX_Text(pFX, _T("[NOMPRO3]"), m_NOMPRO3);
	RFX_Text(pFX, _T("[DESARTI1]"), m_DESARTI1);
	RFX_Double(pFX, _T("[PZMETRO]"), m_PZMETRO);
	RFX_Text(pFX, _T("[CTAVTA]"), m_CTAVTA);
	RFX_Double(pFX, _T("[SUPLEM]"), m_SUPLEM);
	RFX_Text(pFX, _T("[DESARTI2]"), m_DESARTI2);
	RFX_Text(pFX, _T("[DESARTI3]"), m_DESARTI3);
	RFX_Double(pFX, _T("[RECARGO]"), m_RECARGO);
	RFX_Date(pFX, _T("[FECALTA]"), m_FECALTA);
	RFX_Date(pFX, _T("[FECBAJA]"), m_FECBAJA);
	RFX_Text(pFX, _T("[UBIX]"), m_UBIX);
	RFX_Text(pFX, _T("[UBIY]"), m_UBIY);
	RFX_Text(pFX, _T("[UBIZ]"), m_UBIZ);
	RFX_Text(pFX, _T("[ARTCAR10]"), m_ARTCAR10);
	RFX_Text(pFX, _T("[ART1CAR]"), m_ART1CAR);
	RFX_Double(pFX, _T("[ARTNUMER]"), m_ARTNUMER);
	RFX_Text(pFX, _T("[DSUPLEM]"), m_DSUPLEM);
	RFX_Double(pFX, _T("[ARTNUME2]"), m_ARTNUME2);
	RFX_Double(pFX, _T("[ARTNUME3]"), m_ARTNUME3);
	RFX_Double(pFX, _T("[ARTNUME4]"), m_ARTNUME4);
	RFX_Text(pFX, _T("[PROPOR]"), m_PROPOR);
	RFX_Text(pFX, _T("[ALQUILER]"), m_ALQUILER);
	RFX_Date(pFX, _T("[FECALQ]"), m_FECALQ);
	RFX_Date(pFX, _T("[FECFIN]"), m_FECFIN);
	RFX_Text(pFX, _T("[CONTRATO]"), m_CONTRATO);
	RFX_Text(pFX, _T("[TIPOALQ]"), m_TIPOALQ);
	RFX_Date(pFX, _T("[ULTIFACT]"), m_ULTIFACT);
	RFX_Text(pFX, _T("[CLIENTE]"), m_CLIENTE);
	RFX_Text(pFX, _T("[NUMALB]"), m_NUMALB);
	RFX_Text(pFX, _T("[ALQUIDES1]"), m_ALQUIDES1);
	RFX_Text(pFX, _T("[ALQUIDES2]"), m_ALQUIDES2);
	RFX_Text(pFX, _T("[ALQUIDES3]"), m_ALQUIDES3);
	RFX_Text(pFX, _T("[ALQUIDES4]"), m_ALQUIDES4);
	RFX_Text(pFX, _T("[ALQUIDES5]"), m_ALQUIDES5);
	RFX_Double(pFX, _T("[ALQUINUM1]"), m_ALQUINUM1);
	RFX_Double(pFX, _T("[ALQUINUM2]"), m_ALQUINUM2);
	RFX_Double(pFX, _T("[ALQUINUM3]"), m_ALQUINUM3);
	RFX_Double(pFX, _T("[ALQUINUM4]"), m_ALQUINUM4);
	RFX_Double(pFX, _T("[ALQUINUM5]"), m_ALQUINUM5);
	RFX_Double(pFX, _T("[APLICADA]"), m_APLICADA);
	RFX_Double(pFX, _T("[DTOAPLI]"), m_DTOAPLI);
	RFX_Text(pFX, _T("[MOVALM]"), m_MOVALM);
	RFX_Long(pFX, _T("[GENERICO]"), m_GENERICO);
	RFX_Text(pFX, _T("[PROPOROL]"), m_PROPOROL);
	RFX_Double(pFX, _T("[EAPLICADA]"), m_EAPLICADA);
	RFX_Double(pFX, _T("[EALQUINUM1]"), m_EALQUINUM1);
	RFX_Double(pFX, _T("[EALQUINUM2]"), m_EALQUINUM2);
	RFX_Double(pFX, _T("[EALQUINUM3]"), m_EALQUINUM3);
	RFX_Double(pFX, _T("[EALQUINUM4]"), m_EALQUINUM4);
	RFX_Double(pFX, _T("[EALQUINUM5]"), m_EALQUINUM5);
	RFX_Text(pFX, _T("[CODPROV]"), m_CODPROV);
	RFX_Text(pFX, _T("[DESPROV]"), m_DESPROV);
	RFX_Text(pFX, _T("[DESARTIOLD]"), m_DESARTIOLD);
	RFX_Text(pFX, _T("[CTAALQ]"), m_CTAALQ);
	RFX_Text(pFX, _T("[ALQUILADO]"), m_ALQUILADO);
	RFX_Double(pFX, _T("[ETARI1]"), m_ETARI1);
	RFX_Double(pFX, _T("[ETARIB1]"), m_ETARIB1);
	RFX_Double(pFX, _T("[ETARIC1]"), m_ETARIC1);
	RFX_Text(pFX, _T("[CFAMI]"), m_CFAMI);
	RFX_Text(pFX, _T("[FORMATO]"), m_FORMATO);
	RFX_Text(pFX, _T("[SERIE]"), m_SERIE);
	RFX_Text(pFX, _T("[PASTA]"), m_PASTA);
	RFX_Double(pFX, _T("[ETARI2]"), m_ETARI2);
	RFX_Double(pFX, _T("[ECOSLIFO]"), m_ECOSLIFO);
	RFX_Double(pFX, _T("[ECOSFIFO]"), m_ECOSFIFO);
	RFX_Double(pFX, _T("[ECOSPMC]"), m_ECOSPMC);
	RFX_Double(pFX, _T("[BLOQUEO]"), m_BLOQUEO);
	RFX_Text(pFX, _T("[DESARMEMO]"), m_DESARMEMO);
	RFX_Text(pFX, _T("[CSUBFAM]"), m_CSUBFAM);
	RFX_Double(pFX, _T("[DTOTAR1]"), m_DTOTAR1);
	RFX_Double(pFX, _T("[DTOTARB1]"), m_DTOTARB1);
	RFX_Double(pFX, _T("[DTOTARC1]"), m_DTOTARC1);
	RFX_Double(pFX, _T("[PTOVERDE]"), m_PTOVERDE);
	RFX_Double(pFX, _T("[ETARID1]"), m_ETARID1);
	RFX_Double(pFX, _T("[ETARIE1]"), m_ETARIE1);
	RFX_Double(pFX, _T("[ETARIF1]"), m_ETARIF1);
	RFX_Double(pFX, _T("[ETARIG1]"), m_ETARIG1);
	RFX_Double(pFX, _T("[ETARIH1]"), m_ETARIH1);
	RFX_Double(pFX, _T("[ETARII1]"), m_ETARII1);
	RFX_Double(pFX, _T("[DTOTARD1]"), m_DTOTARD1);
	RFX_Double(pFX, _T("[DTOTARE1]"), m_DTOTARE1);
	RFX_Double(pFX, _T("[DTOTARF1]"), m_DTOTARF1);
	RFX_Double(pFX, _T("[DTOTARG1]"), m_DTOTARG1);
	RFX_Double(pFX, _T("[DTOTARH1]"), m_DTOTARH1);
	RFX_Double(pFX, _T("[DTOTARI1]"), m_DTOTARI1);
	RFX_Double(pFX, _T("[TARID5]"), m_TARID5);
	RFX_Double(pFX, _T("[TARIE5]"), m_TARIE5);
	RFX_Double(pFX, _T("[TARIF5]"), m_TARIF5);
	RFX_Double(pFX, _T("[TARIG5]"), m_TARIG5);
	RFX_Double(pFX, _T("[TARIH5]"), m_TARIH5);
	RFX_Double(pFX, _T("[TARII5]"), m_TARII5);
	RFX_Double(pFX, _T("[TARIJ5]"), m_TARIJ5);
	RFX_Double(pFX, _T("[TARVEN]"), m_TARVEN);
	RFX_Double(pFX, _T("[DTOARTD]"), m_DTOARTD);
	RFX_Double(pFX, _T("[DTOARTE]"), m_DTOARTE);
	RFX_Double(pFX, _T("[DTOARTF]"), m_DTOARTF);
	RFX_Double(pFX, _T("[DTOARTG]"), m_DTOARTG);
	RFX_Double(pFX, _T("[DTOARTH]"), m_DTOARTH);
	RFX_Double(pFX, _T("[DTOARTII]"), m_DTOARTII);
	RFX_Double(pFX, _T("[DTOARTJ]"), m_DTOARTJ);
	RFX_Text(pFX, _T("[PROVE4]"), m_PROVE4);
	RFX_Text(pFX, _T("[PROVE5]"), m_PROVE5);
	RFX_Text(pFX, _T("[PROVE6]"), m_PROVE6);
	RFX_Text(pFX, _T("[PROVE7]"), m_PROVE7);
	RFX_Text(pFX, _T("[PROVE8]"), m_PROVE8);
	RFX_Text(pFX, _T("[PROVE9]"), m_PROVE9);
	RFX_Text(pFX, _T("[PROVE10]"), m_PROVE10);
	RFX_Text(pFX, _T("[UA]"), m_UA);
	RFX_Text(pFX, _T("[APLIDCTOS]"), m_APLIDCTOS);
	RFX_Text(pFX, _T("[APLIDCTOS2]"), m_APLIDCTOS2);
	RFX_Text(pFX, _T("[APLIDCTOS3]"), m_APLIDCTOS3);
	RFX_Text(pFX, _T("[APLIDCTOS4]"), m_APLIDCTOS4);
	RFX_Text(pFX, _T("[APLIPP]"), m_APLIPP);
	RFX_Double(pFX, _T("[EUROSUV]"), m_EUROSUV);
}
/////////////////////////////////////////////////////////////////////////////
// CArticulo diagnósticos

#ifdef _DEBUG
void CArticulo::AssertValid() const
{
	CRecordset::AssertValid();
}

void CArticulo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
////// FUNCIONES
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/****************************************************************************/
CArticulo& CArticulo::operator =(CArticulo& Other)
{
    m_ARTI = Other.m_ARTI;
	m_DESARTI = Other.m_DESARTI;
	m_DESARMEMO = Other.m_DESARMEMO;
    m_DESPROV = Other.m_DESPROV;
	m_CODFAM=Other.m_CODFAM;
	m_CSUBFAM=Other.m_CSUBFAM;
    m_CTAVTA = Other.m_CTAVTA;
    m_CUENTA = Other.m_CUENTA;
    m_PTOVERDE = Other.m_PTOVERDE;
	m_IVARTI = Other.m_IVARTI;
	m_RECARGO=Other.m_RECARGO;
    m_FECALTA = Other.m_FECALTA;
    m_FECBAJA = Other.m_FECBAJA;
	m_PESO=Other.m_PESO;
	m_STKMIN=Other.m_STKMIN;
	m_MOVALM=Other.m_MOVALM;
	m_ALQUILADO=Other.m_ALQUILADO;
	m_ETARI1=Other.m_ETARI1;
	m_ETARIB1=Other.m_ETARIB1;
	m_ETARIC1=Other.m_ETARIC1;
	m_ETARID1=Other.m_ETARID1;
	m_ETARIE1=Other.m_ETARIE1;
	m_ETARIF1=Other.m_ETARIF1;
	m_ETARIG1=Other.m_ETARIG1;
	m_ETARIH1=Other.m_ETARIH1;
	m_ETARII1=Other.m_ETARII1;
	m_DTOTAR1=Other.m_DTOTAR1;
	m_DTOTARB1=Other.m_DTOTARB1;
	m_DTOTARC1=Other.m_DTOTARC1;
	m_DTOTARD1=Other.m_DTOTARD1;
	m_DTOTARE1=Other.m_DTOTARE1;
	m_DTOTARF1=Other.m_DTOTARE1;
	m_DTOTARG1=Other.m_DTOTARG1;
	m_DTOTARH1=Other.m_DTOTARH1;
	m_DTOTARI1=Other.m_DTOTARI1;
	m_CTAALQ=Other.m_CTAALQ;
	m_ALQUILER=Other.m_ALQUILER;
	m_TIPOALQ=Other.m_TIPOALQ;
	m_ETARI2=Other.m_ETARI2;
	m_DTOARCO=Other.m_DTOARCO;
	m_TARVEN=Other.m_TARVEN;

    return(*this);
}

/****************************************************************************/
/* Inserta un registro en la tabla ARTICULO                                 */
/****************************************************************************/
HRESULT CArticulo::Insert()
{
	HRESULT hErr = S_OK;

	/* Se preparan las cadenas con las fechas */
	CString strFechaAlta;
	CString strFechaBaja;

	if (m_FECALTA == 0)
		strFechaAlta = "NULL";
	else
		strFechaAlta = "'" + m_FECALTA.Format("%d/%m/%Y") + "'";

	if (m_FECBAJA == 0)
		strFechaBaja = "NULL";
	else
		strFechaBaja = "'" + m_FECBAJA.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("INSERT INTO ARTICULO (ARTI, DESARTI, DESARMEMO, DESPROV, CODFAM, CSUBFAM," \
		"CTAVTA, CUENTA, PTOVERDE, IVARTI, RECARGO, FECALTA, FECBAJA, PESO, STKMIN, MOVALM," \
		"ALQUILADO, ETARI1, ETARIB1, ETARIC1, ETARID1, ETARIE1, ETARIF1, ETARIG1, ETARIH1, ETARII1," \
		"DTOTAR1, DTOTARB1, DTOTARC1, DTOTARD1, DTOTARE1, DTOTARF1, DTOTARG1, DTOTARH1, DTOTARI1," \
		"CTAALQ, ALQUILER, TIPOALQ, ETARI2, DTOARCO, PROVE1, PROVE2, PROVE3, PROVE4, PROVE5, " \
		"PROVE6, PROVE7, PROVE8, PROVE9, PROVE10, TARIA5, TARIB5, TARIC5, TARID5, TARIE5, TARIF5, " \
		"TARIG5, TARIH5, TARII5, TARIJ5, DTOARTA, DTOARTB, DTOARTC, DTOARTD, DTOARTE, DTOARTF," \
		"DTOARTG, DTOARTH, DTOARTII, DTOARTJ, TARVEN) VALUES ('%s', '%s', '%s', '%s','%s', '%s', '%s', '%s', " \
		"%f, %f, %f, %s, %s, %f, %f, '%s', '%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, " \
		"%f, %f, %f, %f, %f, %f, '%s', '%s', '%s', %f, %f, '%s', '%s', '%s', '%s','%s', '%s', '%s', " \
		"'%s', '%s', '%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f)",
		m_ARTI, m_DESARTI, m_DESARMEMO, m_DESPROV, m_CODFAM, m_CSUBFAM, m_CTAVTA, m_CUENTA, m_PTOVERDE, m_IVARTI,
		m_RECARGO, strFechaAlta, strFechaBaja, m_PESO, m_STKMIN, m_MOVALM, m_ALQUILADO, m_ETARI1, m_ETARIB1, m_ETARIC1,
		m_ETARID1, m_ETARIE1, m_ETARIF1, m_ETARIG1, m_ETARIH1, m_ETARII1, m_DTOTAR1, m_DTOTARB1, m_DTOTARC1,
		m_DTOTARD1, m_DTOTARE1, m_DTOTARF1, m_DTOTARG1, m_DTOTARH1, m_DTOTARI1, m_CTAALQ, m_ALQUILER, m_TIPOALQ,
		m_ETARI2, m_DTOARCO, m_PROVE1, m_PROVE2, m_PROVE3, m_PROVE4, m_PROVE5, m_PROVE6, m_PROVE7, m_PROVE8,
		m_PROVE9, m_PROVE10, m_TARIA5, m_TARIB5, m_TARIC5, m_TARID5, m_TARIE5, m_TARIF5, m_TARIG5, m_TARIH5,
		m_TARII5, m_TARIJ5, m_DTOARTA, m_DTOARTB, m_DTOARTC, m_DTOARTD, m_DTOARTE, m_DTOARTF, 
		m_DTOARTG, m_DTOARTH, m_DTOARTII, m_DTOARTJ, m_TARVEN);

	TRY
	{
		m_pDatabase->ExecuteSQL(strSql);		
	}

	CATCH(CDBException, exp)
	{
		AfxMessageBox(exp->m_strError);
		hErr = exp->m_nRetCode;
	}

	END_CATCH

	return (hErr);
}

/****************************************************************************/
/* Actualiza un registro en la tabla ARTICULO                               */
/****************************************************************************/
HRESULT CArticulo::UpdateRegistro()
{
	HRESULT hErr = S_OK;

	/* Se preparan las cadenas con las fechas */
	CString strFechaAlta;
	CString strFechaBaja;

	if (m_FECALTA == 0)
		strFechaAlta = "NULL";
	else
		strFechaAlta = "'" + m_FECALTA.Format("%d/%m/%Y") + "'";

	if (m_FECBAJA == 0)
		strFechaBaja = "NULL";
	else
		strFechaBaja = "'" + m_FECBAJA.Format("%d/%m/%Y") + "'";

	/* Se prepara la instrucción */
	CString strSql;

	strSql.Format("UPDATE ARTICULO SET DESARTI = '%s', DESARMEMO = '%s', DESPROV = '%s', " \
		"CODFAM = '%s', CSUBFAM = '%s', CTAVTA = '%s', CUENTA = '%s', PTOVERDE = %f, IVARTI = %f, RECARGO = %f, " \
		"FECALTA = %s, FECBAJA = %s, PESO = %f, STKMIN = %f, MOVALM = '%s', ALQUILADO = '%s', ETARI1 = %f, " \
		"ETARIB1 = %f, ETARIC1 = %f, ETARID1 = %f, ETARIE1 = %f, ETARIF1 = %f, ETARIG1 = %f, ETARIH1 = %f, " \
		"ETARII1 = %f, DTOTAR1 = %f, DTOTARB1 = %f, DTOTARC1 = %f, DTOTARD1 = %f, DTOTARE1 = %f, DTOTARF1 = %f, " \
		"DTOTARG1 = %f, DTOTARH1 = %f, DTOTARI1 = %f, CTAALQ = '%s', ALQUILER = '%s', TIPOALQ = '%s', " \
		"ETARI2 = %f, DTOARCO = %f, TARVEN = %f WHERE ARTI LIKE '%s'", 
		m_DESARTI, m_DESARMEMO, m_DESPROV, m_CODFAM, m_CSUBFAM, m_CTAVTA, m_CUENTA, m_PTOVERDE, m_IVARTI,
		m_RECARGO, strFechaAlta, strFechaBaja, m_PESO, m_STKMIN, m_MOVALM, m_ALQUILADO, m_ETARI1, m_ETARIB1, m_ETARIC1,
		m_ETARID1, m_ETARIE1, m_ETARIF1, m_ETARIG1, m_ETARIH1, m_ETARII1, m_DTOTAR1, m_DTOTARB1, m_DTOTARC1,
		m_DTOTARD1, m_DTOTARE1, m_DTOTARF1, m_DTOTARG1, m_DTOTARH1, m_DTOTARI1, m_CTAALQ, m_ALQUILER, m_TIPOALQ,
		m_ETARI2, m_DTOARCO, m_TARVEN, m_ARTI);

	TRY
	{
		m_pDatabase->ExecuteSQL(strSql);		
	}

	CATCH(CDBException, exp)
	{
		AfxMessageBox(exp->m_strError);
		hErr = exp->m_nRetCode;
	}

	END_CATCH

	return (hErr);
}


