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

    char* blob;         //WskaŸnik do tablicy charów zawieraj¹cej zawartoœæ bloku mapy;

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
    void c_viev()
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
    g_map_block* block_ptr[MAP_BLOCK_NUM];
    g_map()
    {
        for(int i = 0;i<MAP_BLOCK_NUM;i++)  //zerowanie tablicy wskaznikow
        {
            block_ptr[i] = 0;
        }
    }
    void create_block()
    {

    }
};
int main()
{
    cout << "Hello world!" << endl;
    //g_map_block::id = 0;
    g_map_block blok0(BLOCK_SQUARE_SIZE,BLOCK_SQUARE_SIZE,0,0) ;
    blok0.setblock(5,10,'O');
    blok0.c_viev();
    return 0;
}
