#include <iostream>

using namespace std;

struct FechaExp
{
    int mes;
    int anio;
};

struct cajero
{
    int NoCuenta;
    FechaExp fe;
    int NIP;
    float balance;
    float limite;
};

void AlmacenarDatos(cajero ca[], int tam);
void ImprimirDatos(cajero ca[], int pos);
int VerificarNcuenta(cajero ca[], int tam);
bool VerificarFechaExp(cajero ca[], int pos);
bool VerificarNIP(cajero ca[], int pos);
bool VerificarLimite(cajero ca[], int pos, int cant);
void VerificarBlance(cajero ca[], int pos, int cant);
void RealizarRetiro(cajero ca[], int pos);
void RealizarDeposito(cajero ca[], int pos);

int main()
{
    int tam = 1, pos, opc1, opc2;
    cajero ca[tam];
    bool  fexp, nip;

    //Almacenamiento de datos de los clientes
    AlmacenarDatos(ca, tam);
    cout<<"Los datos se han almacenado correctamente\n";
    system("pause");
    system("cls");

    do
    {
        cout<<"1) Realizar una transaccion \n";
        cout<<"2) Salir\n";
        cin >> opc1;
        switch(opc1)
        {
           case 1:  //Verificar numero de cuenta
                    pos = VerificarNcuenta(ca, tam);
                    if(pos >= 0)
                    {
                        fexp = VerificarFechaExp(ca, pos);
                        if(fexp)
                        {
                            nip = VerificarNIP(ca, pos);
                            if(nip)
                            {
                               do
                               {
                                    cout << "\n\t************************************";
                                    cout << "\n\t* Bienvenido a ATM de la clase AED *";
                                    cout << "\n\t*   1. Verificar Datos de la cuenta*";
                                    cout << "\n\t*   2. Retirar                     *";
                                    cout << "\n\t*   3. Depositar                   *";
                                    cout << "\n\t*   4. Salir                       *";
                                    cout << "\n\t*                                  *";
                                    cout << "\n\t************************************";
                                    cout << "\nSeleccione opcion:  ";
                                    cin >> opc2;
                                    system("cls");
                                    switch(opc2)
                                    {
                                        case 1: //Imprimir los datos de todos los clientes
                                                ImprimirDatos(ca, pos);
                                                system("cls");
                                                break;

                                        case 2: //Realizar retiro
                                                RealizarRetiro(ca, pos);
                                                system("cls");
                                                break;

                                        case 3: //Realizar Deposito
										        RealizarDeposito(ca,pos);
										        system("cls");
									          	break;
										
										case 4: 
										break;
										

                                        default: cout << "\nOpcion erronea - Intente de nuevo\n";
                                    }
                                } while (opc2 != 3);
                            }
                            else
                                cout << "\nNIP invalido\n";
                        }
                        else
                            cout << "\nFecha de expiracion de la tarjeta es invalido\n";
                    }
                    else
                        cout << "\nNumero de cuenta invalido\n";

            case 2: cout << "\nGracias por Utilizar nuestros servicios \n";
                    break;

            default: cout << "\nOpcion erronea - Intente de nuevo\n";

        }

    } while(opc1 != 2);

    return 0;
}

void AlmacenarDatos(cajero ca[], int tam)
{
    int i;
    for(i=0; i< tam; i++)
    {
        fflush(stdin);
        cout << "\n \t DATOS DE LA CUENTA ";
        cout << "\nIntroduzca numero de cuenta: ";
        cin >> ca[i].NoCuenta;
        cout << "\n\nIntroduzca fecha de expiracion de la tarjeta \n";
        fflush(stdin);
        cout << "\nIntroduzca mes: ";
        cin >> ca[i].fe.mes;
        fflush(stdin);
        cout << "Introduzca anio: ";
        cin >> ca[i].fe.anio;
        fflush(stdin);
        cout << "Introduzca numero NIP : ";
        cin >> ca[i].NIP;
        fflush(stdin);
        cout << "Introduzca balance: ";
        cin >> ca[i].balance;
        ca[i].limite = ca[i].balance - 1000;
    }

}


void ImprimirDatos(cajero ca[], int pos)
{
    cout << "NoCuenta:  " << ca[pos].NoCuenta <<"\n";
    cout << "Balance Actual:   " << ca[pos].balance << "\n";
    cout << "Usted puede retirar hasta:  "  <<ca[pos].limite << "\n";
    printf("\n");
}

//Localizar y retornar la posicion del NoCuenta
//Si retorna -1 el numero de cuenta no se encuentra
// si no retorna la posicion del NoCuenta verificado

int VerificarNcuenta(cajero ca[], int tam)
{
    int nc, pos = -1;

    cout << "\nIntroduzca su numero de cuenta: ";
    cin >> nc;
    for(int i=0; i< tam; i++)
        if(nc == ca[i].NoCuenta)
            return i;
    return pos;


}

bool VerificarFechaExp(cajero ca[], int pos)
{
    int m,a;

     //Verificar fecha de expiracion de su tarjeta

     cout << "\nIntroduzca mes de expiracion de la tarjeta: ";
     cin >> m;
     cout << "\nIntroduzca anio de expiracion de la tarjeta: ";
     cin >> a;
     if ((m == ca[pos].fe.mes) && (a == ca[pos].fe.anio))
        return true;
     else
        return false;
}

bool VerificarNIP(cajero ca[], int pos)
{
    int nip, intento = 1;

    //Verificar NIP
    do
    {
        cout << "\nIntroduca NIP: ";
        cin >> nip;
        if (nip == ca[pos].NIP)
            return true;
        else
        {
            cout << "\nNIP erroneo - Intente nuevamente\n";
            intento ++;
        }

    } while(intento <= 3);
    return false;
}

void RealizarRetiro(cajero ca[], int pos)
{

    int lim;
    float cant;
    cout << "\nDigite cantidad a retirar: ";
    cin >> cant;
    lim = VerificarLimite(ca, pos, cant);
    if (lim)
    {
        VerificarBlance(ca, pos, cant);
        cout << "\n** Retiro Exitoso ** \n";
        cout << "Balance Actual:   " << ca[pos].balance - cant << "\n";
    }
    else
    {
       cout << "\nSu retiro excede del limite establecido\n";
    }

}

void RealizarDeposito(cajero ca[], int pos)
{

    float cant;
    cout << "\nDigite cantidad a depositar: ";
    cin >> cant;
    
    VerificarBlance(ca,pos,cant);
    cout << "\n** Deposito Exitoso ** \n";
    cout << "Balance Actual:   " << ca[pos].balance  +  cant <<  "\n";

}

bool VerificarLimite(cajero ca[], int pos, int cant)
{
    if (cant <= ca[pos].limite )
        return true;
    else
        return false;
}

void VerificarBlance(cajero ca[], int pos, int cant)
{
    ca[pos].balance = ca[pos].balance - cant;
    ca[pos].limite = ca[pos].balance - 1000;
    ca[pos].balance = ca[pos].balance + cant;
}
