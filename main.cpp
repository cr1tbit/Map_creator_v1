#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#define BLOCK_SQUARE_SIZE 20
#define MAP_BLOCK_NUM 20
using namespace std;



class g_map_block
{
public:
    static int id;      //na przysz³oœæ
    int size_x;
    int size_y;
    int pos_x;
    int pos_y;
    int block_id;

    char* blob;         //WskaŸnik do tablicy charów zawierajacej zawartosc bloku mapy;

    g_map_block(int s_x,int s_y,int p_x,int p_y,char fillwith = 0)
    {
        size_x = s_x;
        size_y = s_y;
        pos_x = p_x;
        pos_y = p_y;
        blob = new char[s_x*s_y];
        for(int i = 0;i<s_x*s_y;i++)
        {
            *(blob+i) = fillwith;
        }
        //block_id = id++;
    }
    ~g_map_block()
    {
        delete[] blob;
    }
    void c_view()
    {
        cout <<"\n|";
        for(int i =0;i<size_x*size_y;i++)
        {
            cout<<""<<*(blob+i)<<" ";
            if(!((i+1)%size_x))
                cout<<"|\n|";
        }
    }
    void setblock(int x,int y,char l)
    {
        *(blob+x*size_y + y) = l;
    }
};



class g_map
{
public:
    g_map_block* block_ptr[MAP_BLOCK_NUM];          //tablica blokow
    g_map()
    {
        for(int i = 0;i<MAP_BLOCK_NUM;i++)          //zerowanie tablicy wskaznikow
        {
            block_ptr[i] = NULL;
        }
    }
    int create_block(int s_x,int s_y,int p_x,int p_y,char fillwith = 0)//tworzenie bloku i zapisanie go w tablicy obiektów obiektu mapy
    {
        for(int i=0;i<MAP_BLOCK_NUM;i++)    //skanujemy po tablicy bloków
        {
            if (block_ptr[i] == 0)           //czy ten wskaznik jest wolny?
            {                               //uuu super. to tworze w jego miejscu blok
                block_ptr[i] = new g_map_block(s_x,s_y,p_x,p_y,fillwith);
                return 1;                   //udalo sie zapisac obiekt, uciekamy z petli!
            }
        }
        return 0;//jesli tu doszlismy to znaczy ze nie ma juz miejsca na kolejne bloki :(
    }
    void delete_block(int id)
    {
        delete block_ptr[id];
        block_ptr[id] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////DO PRZEPISANIA POZNIEJ:
    int* get_block_map()    //funkcja potrzeba jest aby zdobyc mape bloków. Jak sie ja ogarnie, to powinna mocno
    {                       //pomoc w obrobce wszystkiego.
        int max_x = 0;
        int max_y = 0;
        for(int i=0;i<MAP_BLOCK_NUM;i++)
        {
            if(block_ptr[i]->pos_x>max_x)max_x = block_ptr[i]->pos_x;
            if(block_ptr[i]->pos_y>max_y)max_y = block_ptr[i]->pos_y;
        }//po przejsciu tej petli max_x i max_y powinny miec wartosc najbardziej wychylonych elementow
         //tworze tu tablice tego wlasnie rozmiaru + 2, poniewaz 2 pierwsze liczby oznaczac beda rozmiar
         //tej tablicy.
        int* ptr = new int[max_x*max_y + 2];
        *(ptr+0) = max_x;                               //dwie pierwsze liczby sa wymiarami calej tablicy
        *(ptr+1) = max_y;
        for(int i=0;i<MAP_BLOCK_NUM;i++)                //skanuje znowu wszystkie bloki nalezace do mapy
        {                                               //gdy pointer nie pokazuje na 0, to znaczy ze na
            if(block_ptr[i] != 0)                       //drugim koncu powinien byc jakis obiekt :) zbieramy
            {                                           //jego pozycje x i y, a nastepnie wspolrzednym x,y(+2)
                int dim_x = block_ptr[i]->pos_x;            //w tablicy get_block_map nadajemy wartosc jego
                int dim_y = block_ptr[i]->pos_y;            //miejsca w tablicy wskazników na obiekty g_map_block.
                *(ptr + 2 + max_y*dim_x + dim_y) = i;   //w ten sposob bezproblemowo mozna narysowac minimape
            }                                           //projektu, i szybko mozna skoczyc do konkretnego bloku.
        }
        return ptr;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////EOT
};
int main()
{
    cout << "Hello world!" << endl;
    //blok0::id = 0;
    g_map mapa0;
    //cout << mapa0.block_num;
    mapa0.create_block(BLOCK_SQUARE_SIZE,BLOCK_SQUARE_SIZE,0,0);
    mapa0.create_block(BLOCK_SQUARE_SIZE,BLOCK_SQUARE_SIZE,0,1);
    //int* test = mapa0.get_block_map();
    //cout << mapa0.block_ptr[0];
    mapa0.block_ptr[0]->c_view();
    //cout <<test[0]<<"\n";
    //cout <<test[1]<<"\n";
    //cout <<test[2]<<"\n";
    //cout <<test[3]<<"\n";
    //g_map_block blok0
    //blok0.setblock(5,10,'O');
    //blok0.c_viev();
    return 0;
}
