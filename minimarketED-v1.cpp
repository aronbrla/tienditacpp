/*	
	GRUPO 3:
	INTEGRANTES: 
		- Huarhuachi Ortega, Andrea Mariana - 19200267
		- Blas Ruiz, Luis Aaron - 19200069
		- Lara Zatta, Jonathan Brain - 19200249
		- Palacios Barrutia Jeanpiere Julian - 19200274
		- Jimenez Davila Marcelo Antonio - 19200299
		- Benites Narrea Elvis Saul - 19200068
	PLANTEAMIENTO DEL PROBLEMA
		- Registrar venta de productos de la tienda. 
	OBJETIVOS
		- Mostrar lista de productos. 
		- Registrar ventas y actualizar lista. 
		- Ordenar detalles del producto según cantidad vendida y ganancia. 
	MÓDULOS
		- Ingresar productos. 
		- Mostrar lista de productos para el cliente. 
		- Agregar productos y actualizar lista. 
		- Modifiacar carrito y actualizar lista. 
		- Eliminar producto de carrito y actualizar lista. 
		- Mostrar voucher. 
		- Ordenar producto por mayor vendido, mayor ganancia. 
*/

#include <iostream> 
#include <string.h>	//Para strcpy(). 
#include <conio.h>	//Para getch(). 
#include <stdlib.h>	//Para system("pause"). 
#include <ctype.h>	//Para toupper(). 
#include <iomanip>	//Para setw(). 
#include <stdio.h>	//Para fflush(stdin). 
#include <locale.h> //Para setlocale(). Caracteres especiales (´, ¿, ñ). Buena ortografía. 

using namespace std;
#define archivo "Articulos.txt"
#define archivo2 "Temporal.txt"
#define vaucher "Vaucher.txt"

struct producto		//ESTRUCTURA DE LOS ARTÍCULOS EN VENTA. 
{	char nombre[30];	//Nombre del artículo. 
	int cod;
	int stock;			//Stock disponible por artículo. 
	float precio;		//Precio unitario de cada artículo. 
	float vend;			//Ventas unitarias por producto. 
}P[10],t;

FILE *f;

struct Nodo{
	producto p;
	Nodo *siguiente;
};

	//PROTOTIPOS DE FUNCIÓN. 
void act_archivo();	
void act_vaucher(int vd[]);
int menu();		//MENÚ PRINCIPAL DE OPCIONES. 
int submenu1();	//SUBMENÚ DE LISTA DE PRODUCTOS. 
int menu2();	//SUBMENÚ DE VENTAS. 
int menu3();	//SUBMENÚ DE ESTADÍSTICAS. 
void rellenar(producto v[10]);	//VALORES DE LOS PRODUCTOS. 
void mostrar(producto v[10]);	//LISTA DE PRODUCTOS. 
void mostrar2(producto P[10]);	//MOSTRAR LA CANTIDAD DE PRODUCTOS VENDIDOS. 
void mostrar3(producto P[10]);	//MOSTRAR LA GANANCIA. 
void agregar(producto p[], int vd[]);	//AGREGAR PRODUCTOS. 
void eliminar(producto p[], int vd[]);	//ELIMINAR PRODUCTOS. 
void modificar(producto p[], int vd[]);	//MODIFICAR EL PRODUCTO. 
void voucher(producto p[], int v[]);	//IMPRIMIR EL VOUCHER. 
void ordenarstock();	//ORDENAR POR STOCK. 
void mayorganancia();	//ORDENAR POR MAYOR GANANCIA (SOLES). 
void mayorcantidad();	//ORDENAR POR MAYOR CANTIDAD VENDIDA (UNIDADES). 
void caratula();		//PRESENTACIÓN DEL PROGRAMA. 
void gracias(); //AGRADECIMIENTOS POR USAR NUESTRO PROGRAMA. 

	//FUNCIÓN PRINCIPAL. 
int main(){
	system("color F0"); //Consola color blanco, con texto negro. 
	setlocale(LC_ALL, "spanish"); //Habilita tildes y 'ñ'. 
	
	caratula();	//Presentación del grupo de proyecto. 
	int op, op2;
	int vendido[10]; //Guardar de una venta. 
	rellenar(P);
	for(int i=0;i<10;i++)
		vendido[i]=0;
	do{	system("cls");
		op = menu();
		switch (op)
			{case 1:	//SUBMENÚ DE LISTA DE PRODUCTOS.  
				do{	system("cls");
					op2 = submenu1();
					switch (op2)
						{case 1:		//FUNCION 1
							mostrar(P);
							system("pause");
							break;
						case 2:		//FUNCION 2
              				
                			system("pause");
							break;
						case 3:		//FUNCION 3 
							
							system("pause");
							break;
						}
					}while(op2!=4);
				break;
			
			case 2:		//ESTADÍSTICAS. 
				do{	system("cls");
					op2 = menu2();
					switch (op2)
						{case 1:		//TABLA DE PRODUCTOS. 
							mostrar(P);
							system("pause");
							break;
						case 2:		//MAYOR CANTIDAD VENDIDA (UNIDADES). 
              				mayorcantidad();
             				mostrar2(P);
                			system("pause");
							break;
						case 3:		//MAYOR GANANCIA (SOLES). 
							mayorganancia();
							mostrar3(P);
							system("pause");
							break;
						}
					}while(op2!=4);
				break;
				
			case 3:		//INCIAR VENTA. 
				do{ system("cls");
					op2 = menu3();
					switch (op2)
						{case 1:	//AGREGAR PRODUCTOS.  
							mostrar(P); agregar(P,vendido);
							break;
						case 2:		//MODIFICAR CANTIDAD. 
							modificar(P,vendido); 
							break;
						case 3:		//ELIMINAR PRODUCTO DEL CARRITO DE COMPRAS. 
							eliminar(P,vendido);
							break;		
						case 4:		//MOSTRAR VOUCHER. 
						    system("cls");
							voucher(P,vendido); 
							system("PAUSE");
							break;
						}
						
				}while(op2!=5);
					remove(vaucher); //Eliminar los datos del vaucher para volver a llenar
					
				break;
			}
	}while(op!=4);
	gracias();
	return 0;
}
void act_archivo()
{
	f=fopen(archivo2,"ab+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	fread(&t,sizeof(t),1,f);
	for(int i=0;i<10;i++){
		t=P[i];
		fwrite(&t,sizeof(t),1,f);
	}
	 fclose(f);
	 remove(archivo);
	 rename(archivo2,archivo);
}

void act_vaucher(int vd[])
{
	f=fopen(archivo2,"ab+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	fread(&t,sizeof(t),1,f);
	for(int i=0;i<10;i++){
		if(vd[i]!=0)
		{
			strcpy(t.nombre,P[i].nombre);
			t.cod=P[i].cod;
			t.precio=P[i].precio;
			t.stock=P[i].stock;
			t.vend=vd[i];
			fwrite(&t,sizeof(t),1,f);
		}	
	}
	 fclose(f);
	 remove(vaucher);
	 rename(archivo2,vaucher);
}
//DESARROLLO DE LAS FUNCIONES. 
	//VALORES DE LOS PRODUCTOS. 
void rellenar(producto v[10]){
	for(int i=0;i<10;i++){
		v[i].cod=i+1;
		v[i].stock=50;
		v[i].vend=0;
		}										//Precio en soles. 
		strcpy(v[0].nombre,"Gaseosa Pepsi");	v[0].precio=1.80;
		strcpy(v[1].nombre,"Café");				v[1].precio=2.50;
		strcpy(v[2].nombre,"Chocolate");		v[2].precio=2.00;
		strcpy(v[3].nombre,"Papas Lays");		v[3].precio=1.00;
		strcpy(v[4].nombre,"Chicles");			v[4].precio=0.20;
		strcpy(v[5].nombre,"Desodorante");		v[5].precio=10.00;
		strcpy(v[6].nombre,"Pizza personal");	v[6].precio=4.50;
		strcpy(v[7].nombre,"Jabón");			v[7].precio=3.00;
		strcpy(v[8].nombre,"Shampoo");			v[8].precio=1.00;
		strcpy(v[9].nombre,"Galletas Oreo");	v[9].precio=1.00;
		//Crear el primer archivo
		
		f=fopen(archivo,"ab+");
		if (f==NULL){
			cout<<"El archivo no existe!"<<endl;
		    getch();
		    return;
		}
		fread(&t,sizeof(t),1,f);
		for(int i=0;i<10;i++){
			t=P[i];
			fwrite(&t,sizeof(t),1,f);
			//fread(&t,sizeof(t),1,f);
		}
	 fclose(f);
}

	//MENÚ PRINCIPAL DE OPCIONES. 
int menu()
	{int opcion;
	do
	{	system("cls"); 
		cout<<"\t__________________________________"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<"\t| | | | | MENÚ PRINCIPAL | | | | |"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<"\t|\t\t\t\t |"<<endl;
		cout<<"\t|    [1] Lista de productos.\t |"<<endl; 
		cout<<"\t|    [2] Ingresar cliente.\t |"<<endl; 
		cout<<"\t|    [3] Despachar cliente.\t |"<<endl; 
		cout<<"\t|    [4] FINALIZAR PROGRAMA.\t |"<<endl;
		cout<<"\t|\t\t\t\t |"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<endl;
		cout<<"\t-> INGRESE UNA OPCIÓN: [ ]\b\b";
		cin>>opcion;
	}while(opcion<1 || opcion>4);
	return opcion;
	}

	//SUBMENÚ DE LISTA DE PRODUCTOS. 
int submenu1()
	{int opcion;
	do
	{	system("cls");
		cout<<"\t__________________________________"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<"\t| | | | | INICIAR VENTA  | | | | |"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<"\t|\t\t\t\t |"<<endl;
		cout<<"\t|  [1] Ver productos.\t\t |"<<endl; 
		cout<<"\t|  [2] Modificar cantidad.\t |"<<endl; 
		cout<<"\t|  [4] Generar voucher.\t\t |"<<endl;	
		cout<<"\t|  [5] Volver al menú principal. |"<<endl;
		cout<<"\t|\t\t\t\t |"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<endl;
		cout<<"\t-> INGRESE UNA OPCIÓN: [ ]\b\b";
		cin>>opcion;
	}while(opcion<1 || opcion>5);
	return opcion;
	getch();
	}

	//SUBMENÚ DE ESTADÍSTICAS. 
int menu2()
	{int opcion;
	do
	{	system("cls");
		cout<<"\t___________________________________"<<endl;
		cout<<"\t==================================="<<endl;
		cout<<"\t| |  ESTADÍSTICAS DE PRODUCTOS  | |"<<endl;
		cout<<"\t==================================="<<endl;
		cout<<"\t|\t\t\t\t  |"<<endl;
		cout<<"\t| [1] Tabla de productos.\t  |"<<endl; 
		cout<<"\t| [2] Mostrar por mayor vendido.  |"<<endl; 
		cout<<"\t| [3] Mostrar por mayor ganancia. |"<<endl; 
		cout<<"\t| [4] Volver al menú principal.   |"<<endl;
		cout<<"\t|\t\t\t\t  |"<<endl;
		cout<<"\t==================================="<<endl;
		cout<<endl;
		cout<<"\t-> INGRESE UNA OPCIÓN: [ ]\b\b";
		cin>>opcion;
	}while(opcion<1 || opcion>4);
	return opcion;
	getch();
	}

	//SUBMENÚ DE VENTAS. 
int menu3()
	{int opcion;
	do
	{	system("cls");
		cout<<"\t__________________________________"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<"\t| | | | | INICIAR VENTA  | | | | |"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<"\t|\t\t\t\t |"<<endl;
		cout<<"\t|  [1] Agregar producto.\t |"<<endl; 
		cout<<"\t|  [2] Modificar cantidad.\t |"<<endl; 
		cout<<"\t|  [3] Eliminar producto.\t |"<<endl; 
		cout<<"\t|  [4] Generar voucher.\t\t |"<<endl;	
		cout<<"\t|  [5] Volver al menú principal. |"<<endl;
		cout<<"\t|\t\t\t\t |"<<endl;
		cout<<"\t=================================="<<endl;
		cout<<endl;
		cout<<"\t-> INGRESE UNA OPCIÓN: [ ]\b\b";
		cin>>opcion;
	}while(opcion<1 || opcion>5);
	return opcion;
	getch();
	}

	//ORDENAR POR MAYOR CANTIDAD VENDIDA (UNIDADES). 
void mayorcantidad(){
	for(int i = 10; i > 0; i--)
		for(int j = 0; j < i-1; j++)
			if(P[j].vend < P[j+1].vend){
				producto aux = P[j];
				P[j] = P[j+1];
				P[j+1] = aux;
            }
    act_archivo();
}

	//ORDENAR POR MAYOR GANANCIA (SOLES). 
void mayorganancia(){
	for(int i = 10; i > 0; i--)
		for(int j = 0; j < i-1; j++)
			if(P[j].vend*P[j].precio < P[j+1].vend*P[j+1].precio){
				producto aux = P[j];
				P[j] = P[j+1];
				P[j+1] = aux;
			}
		act_archivo();
}

	//LISTA DE PRODUCTOS. 
void mostrar(producto P[10]){
	system("cls");
	int i=0;
	f=fopen(archivo,"rb+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	
	cout<<"=============================================================================================="<<endl;
	cout<<setw(2)<<"CODIGO"<<setw(40)<<"PRODUCTO"<<setw(30)<<"STOCK"<<setw(16)<<"PRECIO"<<endl;
	cout<<"=============================================================================================="<<endl;
	fread(&t,sizeof(t),1,f);
	while(!feof(f)) 
	{
		cout<<setw(3)<<i+1<<setw(45)<<t.nombre<<setw(26)<<t.stock<<setw(16)<<t.precio<<endl;
		cout<<"----------------------------------------------------------------------------------------------"<<endl;
		i++;
		fread(&t,sizeof(t),1,f);
	}
	fclose(f);
	/*for(int i=0;i<10;i++)
		cout<<setw(3)<<i+1<<setw(45)<<P[i].nombre<<setw(26)<<P[i].stock<<setw(16)<<P[i].precio<<endl;*/
	cout<<"==============================================================================================\n"<<endl;	
}

	//MOSTRAR LA GANANCIA. 
void mostrar3(producto P[10]){
	system("cls");
	int i=0;
	float total=0;
	f=fopen(archivo,"rb+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	cout<<setw(12)<<"PRODUCTO"<<setw(30)<<"STOCK"<<setw(16)<<"PRECIO"<<setw(20)<<"GANANCIA"<<endl;
	cout<<"================================================================================"<<endl;
	
	fread(&t,sizeof(t),1,f);
	while(!feof(f)) 
	{
		cout<<setw(15)<<t.nombre<<setw(26)<<t.stock<<setw(16)<<t.precio<<setw(18)<<t.precio*t.vend<<endl;
		total=total+(t.precio*t.vend);
		cout<<"----------------------------------------------------------------------------------------------"<<endl;
		i++;
		fread(&t,sizeof(t),1,f);
	}
	fclose(f);
	/*for(int i=0;i<10;i++){
		cout<<setw(15)<<P[i].nombre<<setw(26)<<P[i].stock<<setw(16)<<P[i].precio<<setw(18)<<P[i].precio*P[i].vend<<endl;
		total=total+(P[i].precio*P[i].vend);
	}*/
	cout<<"================================================================================"<<endl;
	cout<<"    TOTAL (S/)"<<setw(61)<<total<<endl;
	cout<<"================================================================================\n"<<endl;	
}

	//MOSTRAR LA CANTIDAD DE PRODUCTOS VENDIDOS. 
void mostrar2(producto P[10]){
	system("cls");
	int i=0;
	float total2=0;
	f=fopen(archivo,"rb+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	cout<<setw(12)<<"PRODUCTO"<<setw(30)<<"STOCK"<<setw(16)<<"PRECIO"<<setw(20)<<"CANTIDAD"<<endl;
	cout<<"================================================================================"<<endl;
	
	fread(&t,sizeof(t),1,f);
	while(!feof(f)) 
	{
		cout<<setw(15)<<t.nombre<<setw(26)<<t.stock<<setw(16)<<t.precio<<setw(18)<<t.vend<<endl;
		total2=total2+t.vend;
		cout<<"-----------------------------------------------------------------------------"<<endl;
		i++;
		fread(&t,sizeof(t),1,f);
	}
	fclose(f);
	/*for(int i=0;i<10;i++){
		cout<<setw(15)<<P[i].nombre<<setw(26)<<P[i].stock<<setw(16)<<P[i].precio<<setw(18)<<P[i].vend<<endl;
		total2=total2+P[i].vend;
	}*/
	cout<<"================================================================================"<<endl;
	cout<<"    TOTAL (Und.)"<<setw(59)<<total2<<endl;
	cout<<"================================================================================\n"<<endl;
}

	//ORDENAR POR STOCK. 
void ordenarstock()
	{int i,j;
	producto t;
	for(i=0;i<10;i++)
		for(j=i+1;j<10;j++)
			if(P[i].stock<P[j].stock)
    			{t=P[j];
    			P[j]=P[i];
				P[i]=t;
    		}
}

	//AGREGAR PRODUCTOS. 
void agregar(producto p[], int vd[])
	{int ind, cant, lim;
	char resp;
	do{
    	do{	system("cls");	//ELEGIR LOS PRODUCTOS. 
			mostrar(p);
			do{
				cout<<"-> Ingrese el codigo del producto [1 - 10]: "; cin>>ind;
				if(ind<1 || ind>10)
					cout<<"\t[Ese codigo de producto no existe]"<<endl<<endl;
			}while(ind<1 || ind>10);
		}while(ind<1||ind>10);
		ind--;
		do{	cout<<"\tCantidad a comprar: ";		//INGRESAR LA CANTIDAD. 
			fflush(stdin);
			cin>>cant;
			lim=p[ind].stock;	//LIMITAR LA CANTIDAD A ESCOGER. 
			if(cant>lim)
				cout<<"\t[Por favor ingrese una cantidad que no sobrepase la del stock]"<<endl;
			else if(cant<0)
				cout<<"\t[Por favor no ingrese una cantidad absurda]"<<endl;
		}while(cant<0||cant>lim);
		vd[ind] = cant;
		p[ind].vend += cant;
		p[ind].stock -= cant;
		cout<<"\n\tEl subtotal es: "<<p[ind].precio*cant<<endl;	//PRESENTAR EL SUBTOTAL. 
		getch();
		do{
			cout<<"\n¿Desea agregar más productos? Sí [s] o No [n]: [ ]\b\b";
			cin>>resp;
  	      	resp=toupper(resp);
  	  	}while(resp!='S' && resp!='N');
  	  	  act_vaucher(vd);
		  act_archivo();
	}while(resp=='S');
}

	//ELIMINAR PRODUCTOS. 
void eliminar(producto p[], int vd[])
	{int cant, ind; 
	char resp;
	do{	
		system("cls");
		cout<<"  ========================================="<<endl;
		cout<<"  | | | ELIMINAR PRODUCTO DE LA LISTA | | |"<<endl;
		cout<<"  ========================================="<<endl;
		cout<<"=============================================="<<endl;
		cout<<"CODIGO"<<setw(20)<<"PRODUCTO"<<setw(20)<<"CANTIDAD"<<endl;
		for(int i=0; i<10; i++)
			if(vd[i]>0)
				cout<<setw(5)<<p[i].cod<<setw(20)<<p[i].nombre<<setw(17)<<vd[i]<<endl;
		do{	cout<<"\n->Ingrese el orden de producto a eliminar: ";cin>>ind;
			if(ind<1 || ind>10)
				cout<<"\t[Por favor no ingrese un producto inexistente]\n";
		}while(ind<1 || ind>10);
			--ind; //Para la posición en la que se encuentra en verdad. 
		if(vd[ind]>0){
			cant=vd[ind];
			vd[ind] -= cant;
			p[ind].vend -= cant;
			p[ind].stock += cant;
			cout<<"\n\t¡El producto ha sido eliminado con éxito!";
			getch();
		}
		else	cout<<"\t[Por favor no ingrese productos no añadidos]\n"<<endl;
		do{
			cout<<"\n¿Desea eliminar otro registro? Sí [s] o No [n]: [ ]\b\b";
			cin>>resp;
			resp=toupper(resp);
        }while(resp!='S' && resp!='N');
        act_vaucher(vd);
		act_archivo();  
	}while(resp=='S');
}

	//MODIFICAR EL PRODUCTO. 
void modificar(producto p[], int vd[])
	{int cant, ind; 
	char resp;
	do{	
		system("cls");
		cout<<"  =========================================="<<endl;
		cout<<"  | | | MODIFICAR PRODUCTO DE LA LISTA | | |"<<endl;
		cout<<"  =========================================="<<endl;
		cout<<"=============================================="<<endl;
		cout<<"CODIGO"<<setw(20)<<"PRODUCTO"<<setw(20)<<"CANTIDAD"<<endl;
		for(int i=0; i<10; i++)
			if(vd[i]>0)
				cout<<setw(5)<<p[i].cod<<setw(20)<<p[i].nombre<<setw(17)<<vd[i]<<endl;
		cout<<"=============================================="<<endl;
		do{	cout<<"\n-> Ingrese el orden de producto a modificar: ";cin>>ind;
			if(ind<1 || ind>10)
				cout<<"\t[Por favor no ingrese un producto inexistente]\n";
		}while(ind<1 || ind>10);
			--ind; //Para la posición en la que se encuentra en verdad. 
		if(vd[ind]>0){
			cant=vd[ind];
			vd[ind] -= cant;
			p[ind].vend -= cant;
			p[ind].stock += cant;
			do{		//PEDIR UNA NUEVA CANTIDAD. 
				cout<<"\tNueva cantidad: "; cin>>vd[ind];
				if(vd[ind]>p[ind].stock)
					cout<<"\t[Por favor ingrese una cantidad que no sobrepase la del stock]\n"<<endl;
			}while(vd[ind]<0 || vd[ind]>p[ind].stock);
			p[ind].vend += vd[ind];
			p[ind].stock -= vd[ind];
			cout<<"\n\t¡La cantidad ha sido cambiada con éxito!";
			getch();
		}
		else	cout<<"\t[Por favor no ingrese productos no añadidos]\n"<<endl;
		do{
			cout<<"\n¿Desea modificar otro producto? Sí [s] o No [n]: [ ]\b\b";
        	cin>>resp;
    	    resp=toupper(resp);
        }while(resp!='S' && resp!='N');
        act_vaucher(vd);
		act_archivo();   
	}while(resp=='S');
}

	//IMPRIMIR EL VOUCHER. 
void voucher(producto p[], int vd[]){
	int i=0;
	float total=0;
	f=fopen(vaucher,"ab+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	
	cout<<"===============================[VOUCHER DE COMPRA]===================================="<<endl<<endl;
	cout<<"\t\t\t\t  [UNMSM - FISI]"<<endl;
	cout<<"\t\t\t\t    [MóvilMart]"<<endl;
	cout<<"_________________________________________________________________________________________"<<endl;
	cout<<setw(9)<<"CODIGO"<<setw(15)<<"NOMBRE"<<setw(20)<<"PRECIO"<<setw(20)<<"VENDIDO"<<setw(25)<<"SUBTOTAL"<<endl;
	cout<<"========================================================================================="<<endl;
	
	fread(&t,sizeof(t),1,f);
	while(!feof(f))
	{
		cout<<setw(7)<<t.cod<<setw(17)<<t.nombre<<setw(19)<<t.precio<<setw(19)<<t.vend<<setw(25)<<t.vend*t.precio<<endl;
		total = total + t.vend*t.precio;
		cout<<"-----------------------------------------------------------------------------------------"<<endl;
		fread(&t,sizeof(t),1,f);
		i++;
	}
	 fclose(f);
	/*for(i=0;i<10;i++)
		if(vd[i]>0){	 
			cout<<setw(3)<<i+1<<setw(17)<<P[i].nombre<<setw(17)<<P[i].precio<<setw(17)<<P[i].vend<<setw(26)<<P[i].vend*P[i].precio<<endl;
			total = total + P[i].vend*P[i].precio;
			cout<<"-------------------------------------------------------------------------------"<<endl;
		}*/
	cout<<setw(3)<<"TOTAL (S/)"<<setw(77)<<total<<endl;
	cout<<"_________________________________________________________________________________________"<<endl<<endl;
	cout<<"\tFirma: _____________________"<<endl<<endl;
	cout<<"\t\t\t\t [SETIEMBRE 2020]"<<endl<<endl;
}


	//PRESENTACIÓN DEL GRUPO 3. 
void caratula(){
	cout<<"\t _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
	cout<<"\t>=========================================================<"<<endl<<endl;
	cout<<"\t  ||    ||  ||||    ||   ||||  ||||  ||||||||  ||||  ||||  "<<endl;
	cout<<"\t  ||    ||  || ||   ||   || |||| ||  ||        || |||| ||  "<<endl;
	cout<<"\t  ||    ||  ||  ||  ||   ||  ||  ||  ||||||||  ||  ||  ||  "<<endl;
	cout<<"\t  ||    ||  ||   || ||   ||      ||        ||  ||      ||  "<<endl;
	cout<<"\t  ||||||||  ||    ||||   ||      ||  ||||||||  ||      ||  "<<endl<<endl;
	cout<<"\t>=========================================================<"<<endl;
	cout<<"\t _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl<<endl;
	cout<<"\t====================={PROYECTO FINAL}======================"<<endl;
	cout<<"\t= = = = = = = = = = = = -MóvilMart- = = = = = = = = = = = ="<<endl;
	cout<<"\t>======================= [Grupo 3] =======================<"<<endl<<endl;
	cout<<"\t\t\t\tINTEGRANTES: "<<endl;
	cout<<"\t\t-> Huarhuachi Ortega, Andrea Mariana - 19200267"<<endl;
	cout<<"\t\t-> Blas Ruiz, Luis Aaron - 19200069"<<endl;
	cout<<"\t\t-> Lara Zatta, Jonathan Brain - 19200249"<<endl;
	cout<<"\t\t-> Palacios Barrutia Jeanpiere Julian - 19200274"<<endl;
	cout<<"\t\t-> Benites Narrea Elvis Saul - 19200068"<<endl;
	cout<<"\t\t-> Jimenez Davila Marcelo Antonio - 19200299"<<endl;
	cout<<"\t\t\t    [Lima, Perú - 2020]"<<endl;
	cout<<"\t  =======================================================  "<<endl;
	cout<<"\t>=========================================================<"<<endl<<endl;
	system("pause");
}

	//AGRADECIMIENTOS POR USAR NUESTRO PROGRAMA. 
void gracias(){
	system("cls");
	cout<<"\n\t\t\t\t\t======================================"<<endl;
	cout<<"\t\t\t\t\t¡¡¡GRACIAS POR COMPRAR EN MÓVILMART!!!"<<endl;
	cout<<"\t\t\t\t\t======================================"<<endl<<endl;
}
