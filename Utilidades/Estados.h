// ESTADOS

#define COBRO_PENDIENTE     "0"
#define PENDIENTE_REMESAR   "1"
#define SELEC_REMESAR       "2"
#define DESCONTADO          "3"
#define GASTOS_CONT         "4"
#define IMPAGADO            "5"
#define COBRADO             "6"

#define TXT_COBRO_PENDIENTE     "Pendiente"
#define TXT_PENDIENTE_REMESAR   "Pendiente de remesar"
#define TXT_SELEC_REMESAR       "Seleccionado para remesar"
#define TXT_DESCONTADO          "Descontado"
#define TXT_GASTOS_CONT         "Gastos contabilizados"
#define TXT_IMPAGADO            "Impagado"
#define TXT_COBRADO             "Cobrado"

const int iNumEstados = 7;
const CString lstEstados[iNumEstados] = {COBRO_PENDIENTE, PENDIENTE_REMESAR, SELEC_REMESAR, DESCONTADO, GASTOS_CONT, IMPAGADO, COBRADO};
const CString lstDesEstados[iNumEstados] = {TXT_COBRO_PENDIENTE, TXT_PENDIENTE_REMESAR, TXT_SELEC_REMESAR, TXT_DESCONTADO, TXT_GASTOS_CONT, TXT_IMPAGADO, TXT_COBRADO};
