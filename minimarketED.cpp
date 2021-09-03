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


#define archivo "Articulos.txt"
#define archivo2 "Temporal.txt"
#define vaucher "Vaucher.txt"
#define clientes "Clientes.txt"
using namespace std;
int cant;
struct producto		//ESTRUCTURA DE LOS ARTÍCULOS EN VENTA. 
{	char nombre[30];	//Nombre del artículo. 
	int cod;
	int stock;			//Stock disponible por artículo. 
	float precio;		//Precio unitario de cada artículo. 
	float vend;			//Ventas unitarias por producto. 
}P[10],t;

FILE *f,*h;

/*                Estructura de los nodos de la cola de prioridad   
------------------------------------------------------------------------*/
struct nodo
{
    char dato[100];
    int priori;        // prioridad del nodo
    struct nodo *sgte;
}n;

/*                      Estructura de la cola      
------------------------------------------------------------------------*/
struct cola
{
    nodo *delante;
    nodo *atras;
}q;

/*                         Crear Nodo     
------------------------------------------------------------------------*/
struct nodo *crearNodo( char x[100], int pr)
{
    struct nodo *nuevoNodo = new(struct nodo);
    strcpy(nuevoNodo->dato,x);
    nuevoNodo->priori = pr;
    return nuevoNodo;
};

/*                        Encolar cacarter con prioridad      
------------------------------------------------------------------------*/
void encolar( struct cola &q, char valor[100], int priori )
{
     
     struct nodo *aux = crearNodo(valor, priori);
     aux->sgte = NULL;
     
    if( q.delante == NULL){
         q.delante = aux;   // encola el primero elemento
         cout<<"\nCliente registrado exitosamente..!"<<endl;
	}
     else{
         (q.atras)->sgte = aux;
         cout<<"\nCliente registrado exitosamente..!"<<endl;
	}
     q.atras = aux;        // puntero que siempre apunta al ultimo elemento 
}

/*                        Mostrar Cola       
------------------------------------------------------------------------*/
void muestraCola(cola q)
{
     struct nodo *aux;
     
     aux = q.delante;
     if(q.delante!=NULL){
		cout<<"\n\t\t\t\t\t============================================"<<endl;
		cout<<"\t\t\t\t\t            COLA DE CLIENTES"<<endl;
		cout<<"\t\t\t\t\t============================================"<<endl<<endl;    
	          
	     while( aux != NULL )
	     {
	            cout<<setw(50)<< aux->dato <<setw(10)<<"|"<<setw(15)<< aux->priori << endl;
	            aux = aux->sgte;
	     }         	
	 }else{
	 	cout<<"\n\tNo hay cola de clientes"<<endl;
	 }

}

/*         Ordenar  por prioridad( criterio de O. por Burbuja)    
------------------------------------------------------------------------*/
void ordenarPrioridad( struct cola &q )
{
     struct nodo *aux1, *aux2;
     int p_aux;
     char c_aux[100];
     
     aux1 = q.delante;
     
     while( aux1->sgte != NULL)
     {
            aux2 = aux1->sgte;
            
            while( aux2 != NULL)
            {
                   if( aux1->priori > aux2->priori )
                   {
                       p_aux = aux1->priori;
                       strcpy(c_aux,aux1->dato);
                       
                       aux1->priori = aux2->priori;
                       strcpy(aux1->dato,aux2->dato);
                       
                       aux2->priori = p_aux;
                       strcpy(aux2->dato,c_aux);
                   }
                   
                   aux2 = aux2->sgte;
            }
            
            aux1 = aux1->sgte;
     }
}
/*                Inserta cacacteres en una cola     
------------------------------------------------------------------------*/
void insertar( struct cola &q, char c[100], int pr )
{
     /* Encolando caracteres */
     encolar( q, c, pr );
     
     /* Ordenando por prioridad */
     ordenarPrioridad( q ); 
}
//DEPACHAR CLIENTES
struct nodo desencola(struct cola &q){ 
	struct nodo *p;
    p=q.delante;
    struct nodo n=*p;
    q.delante=(q.delante)->sgte;
    delete(p);
    return n;
}

// Core Cesta de comprar con lista ennlazadas
typedef producto PE;
struct NODO{
    NODO *sgte;
    PE compra;
}*la,*li;
NODO* crearNodo(PE dato){
   NODO *p;
   p= new NODO();
   if(p==NULL) {
      cout<<"\nNo Hay espacio en la mamoria..."<<endl;
      system("pause");
      exit(0);
      return(p);
   }
   else {
      p->compra=dato;
      p->sgte=NULL;
      return(p);
   }
}
void adicionaNodoFinal(PE dato){
   NODO *p, *q;
   p=crearNodo(dato);
   if(p==NULL) {
      cout<<"\nNo Hay espacio en la mamoria..."<<endl;
      system("pause");
      exit(0);
   }
   else {
      if(la==NULL) {
         p->sgte= la;
         la= p;

      }
      else {
         q=la;
         while(q->sgte!=NULL) {
            q=q->sgte;
         }
         q->sgte=p;

      }
   }
}
// Fin Core


	//PROTOTIPOS DE FUNCIÓN. 
void act_archivo();	
void act_vaucher();
int menu();		//MENÚ PRINCIPAL DE OPCIONES. 
int submenu1();	//SUBMENÚ DE LISTA DE PRODUCTOS. 
int menu2();	//SUBMENÚ DE VENTAS. 
int menu3();	//SUBMENÚ DE ESTADÍSTICAS. 
void rellenar(producto v[10]);	//VALORES DE LOS PRODUCTOS. 
void mostrar(producto v[10]);	//LISTA DE PRODUCTOS. 
void mostrar2(producto P[10]);	//MOSTRAR LA CANTIDAD DE PRODUCTOS VENDIDOS. 
void mostrar3(producto P[10]);	//MOSTRAR LA GANANCIA. 
void agregar(producto p[]);	//AGREGAR PRODUCTOS. 
void eliminar(producto p[]);	//ELIMINAR PRODUCTOS. 
void modificar(producto p[]);	//MODIFICAR EL PRODUCTO. 
void voucher(producto p[]);	//IMPRIMIR EL VOUCHER. 
void ingresarCliente(); //Registro de nombre y prioridad
void salvarClientes(); //guarda en un .txt los clientes
void recuperarClientes();
void agregar2();//agrega producto al inventario
bool buscarCod(int cod);
void editarStock();
void eliminarProducto();
void editarPrecio();
void caratula();		//PRESENTACIÓN DEL PROGRAMA. 
void gracias(); //AGRADECIMIENTOS POR USAR NUESTRO PROGRAMA. 
	//FUNCIÓN PRINCIPAL. 
int main(){
	system("color F0"); //Consola color blanco, con texto negro. 
	setlocale(LC_ALL, "spanish"); //Habilita tildes y 'ñ'. 
	char c;
	caratula();	//Presentación del grupo de proyecto. 
	int op, op2;
	int vendido[10]; //Guardar de una venta. 
	char x[100];
	rellenar(P);
	recuperarClientes();
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
							agregar2();
                			system("pause");
							break;
						case 3:		//FUNCION 3 
							editarStock();
							system("pause");
							break;							
						case 4:		//FUNCION 4 
							editarPrecio();
							system("pause");
							break;
						case 5:		//FUNCION 5 
							eliminarProducto();
							system("pause");
							break;
						case 6:		//FUNCION 6 
							
						   break;
						}																					
					}while(op2!=6);
				break;
			
			case 2:		//INGRESAR CLIENTE. 
				system("cls");
  			    ingresarCliente();
			    muestraCola(q);
			    system("pause");
				break;	
			case 3:		//INCIAR VENTA.
					system("cls");
					muestraCola(q);
					n=desencola(q);
					system("pause");
				do{ system("cls");
					cout<<"\n\t\t\t******ATENDIENDO PRIMERO EN LA COLA******"<<endl;
					cout<<"\n\t\t\tCliente: "<<n.dato;
					if(n.priori==1){
						cout<<"\n\t\t\tCliente VIP"<<endl;
					}else{
						cout<<"\n\t\t\tCliente normal"<<endl;
					}
					system("pause");
					op2 = menu3();
					switch (op2)
						{case 1:	//AGREGAR PRODUCTOS.  
							mostrar(P); agregar(P);
							break;
						case 2:		//MODIFICAR CANTIDAD. 
							modificar(P); 
							break;
						case 3:		//ELIMINAR PRODUCTO DEL CARRITO DE COMPRAS. 
							eliminar(P);
							break;		
						case 4:		//MOSTRAR VOUCHER. 
						    system("cls");
							voucher(P); 
							system("PAUSE");
							break;
						}
						
				}while(op2!=5 && op2!=4);
					la = NULL;
					remove(vaucher); //Eliminar los datos del vaucher para volver a llenar
					
				break;
			}

	}while(op!=4);
	if(op==4){
		if(q.delante!=NULL){
			cout<<"Desea guardar la cola de clientes?[s]/[n]"<<endl;
			do{
				fflush(stdin);
				cin>>c;	
				c=toupper(c);
			}while(c!='S'&&c!='N');
			if(c=='S'){
				salvarClientes();
			}			
		}		
	}
	gracias();
	return 0;
}
void act_archivo()
{
	PE pe;
	h=fopen(archivo,"rb+");
	f=fopen(archivo2,"wb+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	fread(&pe,sizeof(pe),1,h);
	while(!feof(h)){
		if(pe.cod==t.cod){
			fwrite(&t,sizeof(t),1,f);
		}else{
			fwrite(&pe,sizeof(pe),1,f);
		}
		fread(&pe,sizeof(pe),1,h);
	}
	fclose(f);
	fclose(h);
	remove(archivo);
	rename(archivo2,archivo);
}

void act_vaucher()
{
	NODO *p = la;
	PE a;
	f=fopen(archivo2,"ab+");
	h=fopen(vaucher,"rb+");
	if (f==NULL){
		cout<<"El archivo no existe!"<<endl;
	    getch();
	    return;
	}
	fread(&t,sizeof(t),1,h);
	if(p == NULL) {
	      cout<<"\nLista vacia..."<<endl;
	}
	else {
	while(p) {
			strcpy(a.nombre,p->compra.nombre );
			a.cod=p->compra.cod;
			a.precio=p->compra.precio;
			a.vend=p->compra.vend;
			fwrite(&a,sizeof(a),1,f);
         p = p->sgte;
      }
   }
	 fclose(f);
	 fclose(h);
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
		cout<<"\t______________________________________"<<endl;
		cout<<"\t======================================"<<endl;
		cout<<"\t| | | | | LISTA DE PRODUCTOS | | | | |"<<endl;
		cout<<"\t======================================"<<endl;
		cout<<"\t|\t\t\t\t     |"<<endl;
		cout<<"\t|  [1] Ver productos.\t\t     |"<<endl; 
		cout<<"\t|  [2] Agregar producto.\t     |"<<endl; 
		cout<<"\t|  [3] Modificar stock.\t\t     |"<<endl;	
		cout<<"\t|  [4] Modificar precio.\t     |"<<endl;	
		cout<<"\t|  [5] Eliminar producto.\t     |"<<endl;
		cout<<"\t|  [6] Volver al menú principal.    |"<<endl;
		cout<<"\t|\t\t\t\t     |"<<endl;
		cout<<"\t======================================"<<endl;
		cout<<endl;
		cout<<"\t-> INGRESE UNA OPCIÓN: [ ]\b\b";
		cin>>opcion;
	}while(opcion<1 || opcion>6);
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
		cout<<setw(3)<<t.cod<<setw(45)<<t.nombre<<setw(26)<<t.stock<<setw(16)<<t.precio<<endl;
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

	
	//AGREGAR PRODUCTOS. 
void agregar(producto p[])
	{int ind, cant, lim,encontrado=0;
	int vd[]={5,6};
	producto temporal;
	PE pe={"",0,0,0.0,0.0};
	char resp;	
	do{
    	do{	system("cls");	//ELEGIR LOS PRODUCTOS. 
			mostrar(p);
			do{
				f=fopen(archivo,"rb+");
				if(f==NULL){
					cout<<"\nNo se pudo abrir el archivo"<<endl;
				}
				cout<<"-> Ingrese el codigo del producto: "; cin>>ind;
				fread(&pe,sizeof(pe),1,f);
				
				while(!feof(f)){
					if(ind==pe.cod){
						encontrado=1;
						temporal=pe;
					}
					fread(&pe,sizeof(pe),1,f);
				}
				fclose(f);
				if(encontrado==0)
					cout<<"\t[Ese codigo de producto no existe]"<<endl<<endl;
			}while(encontrado==0);
		}while(encontrado==0);
		//Guardando datos de producto comprado en la estructura temporal;
		t=temporal;
		temporal.cod = ind;
		do{	cout<<"\tCantidad a comprar: ";		//INGRESAR LA CANTIDAD. 
			fflush(stdin);
			cin>>cant;
			if(cant>temporal.stock)
				cout<<"\t[Por favor ingrese una cantidad que no sobrepase la del stock]"<<endl;
			else if(cant<0)
				cout<<"\t[Por favor no ingrese una cantidad absurda]"<<endl;
		}while(cant<0||cant>temporal.stock);
		
		temporal.vend = cant;
		temporal.stock=temporal.stock-cant;
		cout<<"\nStock restante: "<<temporal.stock<<endl;
		t.stock=t.stock-cant;
		cout<<"\n\tEl subtotal es: "<<temporal.precio*temporal.vend<<endl;	//PRESENTAR EL SUBTOTAL. 
		act_archivo();
		getch();
		do{
			cout<<"\n¿Desea agregar más productos? Sí [s] o No [n]: [ ]\b\b";
			cin>>resp;
  	      	resp=toupper(resp);
  	  	}while(resp!='S' && resp!='N');
  	  		adicionaNodoFinal(temporal);
  	  	  act_vaucher();
		  
	}while(resp=='S');
}

	//ELIMINAR PRODUCTOS. 
void eliminar(producto p[])
	{int cant, ind, encontrado=0; 
	char resp;
	PE pe;
	NODO *ps=la, *l=la, *x, *anterior;
	do{	
		system("cls");
		cout<<"  ========================================="<<endl;
		cout<<"  | | | ELIMINAR PRODUCTO DE LA LISTA | | |"<<endl;
		cout<<"  ========================================="<<endl;
		cout<<"=============================================="<<endl;
		cout<<"CODIGO"<<setw(20)<<"PRODUCTO"<<setw(20)<<"CANTIDAD"<<endl;
		while(ps){
			if(ps->compra.vend>0)
				cout<<setw(5)<<ps->compra.cod
					<<setw(20)<<ps->compra.nombre
					<<setw(17)<<ps->compra.vend
				<<endl;
			ps = ps->sgte;
		}
			
		do{	
			x=la;
			anterior=NULL;
			cout<<"\n->Ingrese el codigo de producto a eliminar: ";cin>>ind;		    
			while(x!=NULL && x->compra.cod!=ind){
				anterior=x;				
				x=x->sgte;
			}
			t=x->compra;
			t.stock=t.stock+t.vend;
			t.vend=0;
			act_archivo(); 
			if(x==NULL)	{
				cout<<"\t[Por favor no ingrese un producto inexistente]\n";
			}else if(anterior==NULL){
				la=la->sgte;
				delete(x);
			}else{
				anterior->sgte=x->sgte;
				delete(x);
			}	
		}while(x==NULL);				
		// Eliminando de la lista	
		/*if(l == NULL) {
		cout<<"\nLista vacia..."<<endl;
		}
		else {
			while(l) {
			 if(l->compra.cod==ind){
			 	cout<<"\nEliminando"<<endl;
				--ind; //Para la posición en la que se encuentra en verdad. 
				if(l->compra.vend>0){
					t=l->compra;
					t.vend=0;
				}
			    l->compra=(l->sgte)->compra;
			    l->sgte=(l->sgte)->sgte;
			 }
			 l=l->sgte;
			}
		}*/
		cout<<"\n\t¡El producto ha sido eliminado con éxito!";
		getch();
		act_vaucher();
		
		do{
			cout<<"\n¿Desea eliminar otro registro? Sí [s] o No [n]: [ ]\b\b";
			cin>>resp;
			resp=toupper(resp);
        }while(resp!='S' && resp!='N');
        
		
	}while(resp=='S');
}

void ingresarCliente(){
	char cliente[100];
	int opc, priori;
	cout<<"\n******INGRESE DATOS DEL CLIENTE******"<<endl;
	cout<<"\nNombres y Apellidos:--> ";
	fflush(stdin);
	cin.getline(cliente,100);
	
	cout<<"\nTipo de cliente:"<<endl;
	cout<<"\n(1).VIP"<<endl;
	cout<<"\n(2).Normal"<<endl;
	do{
		cout<<"\nSeleccione su opción--> ";
		cin>>opc;
	}while(opc<1 || opc>2);	
	insertar(q,cliente,opc);
}
void salvarClientes(){
	char nombre[100];
	int priori;
	h=fopen(clientes,"w+");
	if (h==NULL){
		cout<<"No se pudo crear el archivo"<<endl;
	    getch();
	    return;
	}
     struct nodo *aux;
     
     aux = q.delante;
     while( aux != NULL )
     {
        strcpy(nombre,aux->dato);
     	priori=aux->priori;
	    fwrite(&nombre,sizeof(nombre),1,h); 
	    fwrite(&priori,sizeof(int),1,h);       	
     	
        aux = aux->sgte;     
     }  	
     fclose(h);
	cout<<"\nClientes guardados"<<endl;
	system("pause");
	
}
void recuperarClientes(){
	char nombre[100];
	int p;
	h=fopen(clientes,"rb+");
	if(h!=NULL){
		fread(&nombre,sizeof(nombre),1,h);
		fread(&p,sizeof(p),1,h);
		while(!feof(h)){
			insertar(q,nombre,p);
			fread(&nombre,sizeof(nombre),1,h);
			fread(&p,sizeof(p),1,h);
		}	
	}
	fclose(h);	

}
	//MODIFICAR EL PRODUCTO. 
void modificar(producto p[])
	{int cant, ind, encontrado=0; 
	char resp;
	PE pe;
	NODO *ps=la, *l=la, *x, *anterior;
	do{	
		system("cls");
		cout<<"  =========================================="<<endl;
		cout<<"  | | | MODIFICAR PRODUCTO DE LA LISTA | | |"<<endl;
		cout<<"  =========================================="<<endl;
		cout<<"==============================================="<<endl;
		cout<<"CODIGO"<<setw(20)<<"PRODUCTO"<<setw(20)<<"CANTIDAD"<<endl;
		while(ps){
			if(ps->compra.vend>0)
				cout<<setw(5)<<ps->compra.cod
					<<setw(20)<<ps->compra.nombre
					<<setw(17)<<ps->compra.vend
				<<endl;
			ps = ps->sgte;
		}
			
		do{	
			x=la;
			cout<<"\n->Ingrese el codigo de producto a editar cantidad: ";cin>>ind;		    
			while(x!=NULL && x->compra.cod!=ind){			
				x=x->sgte;
			}
			t=x->compra;
			if(x==NULL)	{
				cout<<"\t[Por favor no ingrese un producto inexistente]\n";
			}else{				
				do{
					cout<<"\nIngrese la nueva cantidad: ";cin>>cant;
				}while(t.stock<cant && cant<=0);
				x->compra.vend=cant;
				if(cant<t.vend){
					t.stock=t.stock+t.vend-cant;
					x->compra.stock=t.stock;
					t.vend=0;
				}else{
					t.stock=t.stock-(cant-t.vend);
					x->compra.stock=t.stock;
					t.vend=0;
				}
				act_archivo();
				act_vaucher();
			}			
		}while(x==NULL);				
		// Eliminando de la lista	
		/*if(l == NULL) {
		cout<<"\nLista vacia..."<<endl;
		}
		else {
			while(l) {
			 if(l->compra.cod==ind){
			 	cout<<"\nEliminando"<<endl;
				--ind; //Para la posición en la que se encuentra en verdad. 
				if(l->compra.vend>0){
					t=l->compra;
					t.vend=0;
				}
			    l->compra=(l->sgte)->compra;
			    l->sgte=(l->sgte)->sgte;
			 }
			 l=l->sgte;
			}
		}*/
		cout<<"\n\t¡La cantidad ha sido editada con éxito!";
		getch();		 
		do{
			cout<<"\n¿Desea editar otra cantidad? Sí [s] o No [n]: [ ]\b\b";
			cin>>resp;
			resp=toupper(resp);
        }while(resp!='S' && resp!='N');
        
		
	}while(resp=='S');
}

	//IMPRIMIR EL VOUCHER. 
void voucher(producto p[]){
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
	cout<<"[Cliente]-> "<<n.dato<<endl;
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
	cout<<"\t\t\t\t [AGOSTO 2021]"<<endl<<endl;
}
void agregar2(){
	PE prod={"",0,0,0.0,0.0};
	char resp;
	f=fopen(archivo,"ab+");
	do{
    	system("cls");
    	cout<<"\nIngrese el nombre del producto-> ";
    	fflush(stdin);
    	cin.getline(prod.nombre,30);
    	cout<<"\nIngrese el codigo del producto--> ";
    	cin>>prod.cod;
    	cout<<"\nIngrese el precio del producto--> ";
    	cin>>prod.precio;
    	cout<<"\nIngrese el stock del producto--> ";
    	cin>>prod.stock;
    	prod.vend=0;
    	fwrite(&prod,sizeof(prod),1,f);
    	cout<<"\nProducto guardado exitosamente..!"<<endl;
		do{
			cout<<"\n¿Desea agregar más productos? Sí [s] o No [n]: [ ]\b\b";
			cin>>resp;
  	      	resp=toupper(resp);
  	  	}while(resp!='S' && resp!='N');
	}while(resp=='S');	
	fclose(f);
}
void editarStock(){
	PE prod={"",0,0,0.0,0.0};
	int encontrado=0,cod,stock;
	FILE *g;
	mostrar(P);
	f=fopen(archivo,"rb+");
	g=fopen(archivo2,"wb+");
	cout<<"\nIngrese un codigo: ";
	cin>>cod;		
		
	cout<<"\nIngrese el stock nuevo: ";
	cin>>stock;
	fread(&prod,sizeof(prod),1,f);
	while(!feof(f)){
		if(prod.cod==cod){
			prod.stock=stock;
			fwrite(&prod,sizeof(prod),1,g);
			encontrado=1;
		}else{
			fwrite(&prod,sizeof(prod),1,g);
		}
		fread(&prod,sizeof(prod),1,f);
	}
	fclose(f);
	fclose(g);
	remove(archivo);
	rename(archivo2,archivo);
	if(encontrado==1){
		cout<<"\nSe encontro el codigo y se modifo el stock..!"<<endl;
	}else{
		cout<<"\nNo se encontro ese codigo.."<<endl;
	}

}
void editarPrecio(){
	system("cls");
	PE prod={"",0,0,0.0,0.0};
	int encontrado=0,cod;
	float precio;
	FILE *g;
	mostrar(P);
	f=fopen(archivo,"rb+");
	g=fopen(archivo2,"wb+");
	cout<<"\nIngrese un codigo: ";
	cin>>cod;		
		
	cout<<"\nIngrese el precio nuevo: ";
	cin>>precio;
	fread(&prod,sizeof(prod),1,f);
	while(!feof(f)){
		if(prod.cod==cod){
			prod.precio=precio;
			fwrite(&prod,sizeof(prod),1,g);
			encontrado=1;
		}else{
			fwrite(&prod,sizeof(prod),1,g);
		}
		fread(&prod,sizeof(prod),1,f);
	}
	fclose(f);
	fclose(g);
	remove(archivo);
	rename(archivo2,archivo);
	if(encontrado==1){
		cout<<"\nSe encontro el codigo y se modifo el precio..!"<<endl;
	}else{
		cout<<"\nNo se encontro ese codigo.."<<endl;
	}	
}
void eliminarProducto(){
	system("cls");
	PE prod={"",0,0,0.0,0.0};
	int encontrado=0,cod;
	float precio;
	FILE *g;
	mostrar(P);
	f=fopen(archivo,"rb+");
	g=fopen(archivo2,"wb+");
	cout<<"\nIngrese un codigo: ";
	cin>>cod;		
	fread(&prod,sizeof(prod),1,f);
	while(!feof(f)){
		if(prod.cod!=cod){
			fwrite(&prod,sizeof(prod),1,g);
			encontrado=1;
		}
		fread(&prod,sizeof(prod),1,f);
	}
	fclose(f);
	fclose(g);
	remove(archivo);
	rename(archivo2,archivo);
	if(encontrado==1){
		cout<<"\nSe encontro el codigo y se elimino el producto..!"<<endl;
	}else{
		cout<<"\nNo se encontro ese codigo.."<<endl;
	}
}
bool buscarCod(int cod){
	PE prod={"",0,0,0.0,0.0};
	int encontrado=0;
	f=fopen(archivo,"rb+");
	fread(&prod,sizeof(prod),1,f);
	while(!feof(f)){
		if(prod.cod==cod){
			encontrado=1;
			cant = prod.stock;
		}
		fread(&prod,sizeof(prod),1,f);
	}
	fclose(f);
	if(encontrado==1){
		return true;
	}else{
		return false;
	}
		
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
