#include "bd.h"

// Constructeurs
/*Bd::Bd()
{

}*/

Bd::~Bd()
{

}

Bd::Bd(int _m[])
{

    for(int i=0;i<13;++i)
    {
        this->m_CurrentStimulus[i] = _m[i];
    }

    this->builddata();
}

// Construction de la base de connaissances
void Bd::builddata()
{
    /*
        Construction de la list_murV qui contient les Coordonnées de chaque mur
        en fonction de des 4 variables définissant le plateau. Ce sont bien les coordonnées des murs et non des cases*/
    for(int i=0;i<16;++i){
        for(int j=0;j<16;++j){
            list_murH[i][j]=list_murV[j][i]=false;
        }
    }

    target=m_CurrentStimulus[4];
    /* Base de connaissances
        Construction de la list_target qui contient les Coordonnées de chaque cible
        en fonction de des 4 variables définissant le plateau*/


    //carré du centre
    /*list_murH[6][7]=true;
    list_murH[8][7]=true;
    list_murH[6][8]=true;
    list_murH[8][8]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;*/

    if(m_CurrentStimulus[0]==1){
        //correct
        list_target[0]=Coordonnees(3,7);
        list_target[1]=Coordonnees(5,6);
        list_target[6]=Coordonnees(1,3);
        list_target[12]=Coordonnees(6,4);
        list_target[15]=Coordonnees(2,1);

    }else{
        //correct
        list_target[0]=Coordonnees(7,5);
        list_target[1]=Coordonnees(6,1);
        list_target[6]=Coordonnees(5,4);
        list_target[12]=Coordonnees(1,3);
        list_target[15]=Coordonnees(2,5);


    }
    if(m_CurrentStimulus[1]==1){
        //correct
        list_target[3]=Coordonnees(11,2);
        list_target[5]=Coordonnees(13,6);
        list_target[10]=Coordonnees(10,7);
        list_target[16]=Coordonnees(14,1);

    }else{

        //correct
        list_target[3]=Coordonnees(13,5);
        list_target[5]=Coordonnees(11,2);
        list_target[10]=Coordonnees(9,1);
        list_target[16]=Coordonnees(10,7);


    }
    if(m_CurrentStimulus[2]){
        //correct
        list_target[4]=Coordonnees(3,9);
        list_target[7]=Coordonnees(6,14);
        list_target[9]=Coordonnees(1,13);
        list_target[14]=Coordonnees(5,11);

    }else{

        //correct
        list_target[4]=Coordonnees(6,13);
        list_target[7]=Coordonnees(1,10);
        list_target[9]=Coordonnees(4,9);
        list_target[14]=Coordonnees(2,14);

    }
    if(m_CurrentStimulus[3]==1){

        //correct
        list_target[2]=Coordonnees(12,9);
        list_target[11]=Coordonnees(9,12);
        list_target[13]=Coordonnees(11,14);

    }else{
        //correct
        list_target[2]=Coordonnees(9,10);
        list_target[11]=Coordonnees(9,14);
        list_target[13]=Coordonnees(12,9);

    }

    //le cancer commence
    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==0)
    {
      list_murH[3][0]=true;
      list_murH[10][0]=true;
      list_murH[9][1]=true;
      list_murH[5][1]=true;
      list_murH[11][2]=true;
      list_murH[1][3]=true;
      list_murH[2][5]=true;
      list_murH[4][4]=true;
      list_murH[7][5]=true;
      list_murH[12][5]=true;
      list_murH[12][9]=true;
      list_murH[9][7]=true;
      list_murH[6][7]=true;
      list_murH[6][8]=true;
      list_murH[8][7]=true;
      list_murH[8][8]=true;
      list_murH[8][10]=true;
      list_murH[3][9]=true;
      list_murH[1][10]=true;
      list_murH[2][14]=true;
      list_murH[3][15]=true;
      list_murH[5][13]=true;
      list_murH[8][14]=true;
      list_murH[10][15]=true;
      list_murH[14][13]=true;

      list_murV[0][3]=true;
      list_murV[0][6]=true;
      list_murV[1][2]=true;
      list_murV[6][1]=true;
      list_murV[9][0]=true;
      list_murV[11][2]=true;
      list_murV[15][3]=true;
      list_murV[13][5]=true;
      list_murV[15][9]=true;
      list_murV[10][6]=true;
      list_murV[12][8]=true;
      list_murV[7][5]=true;
      list_murV[5][3]=true;
      list_murV[2][5]=true;
      list_murV[4][9]=true;
      list_murV[9][10]=true;
      list_murV[14][13]=true;
      list_murV[9][13]=true;
      list_murV[6][12]=true;
      list_murV[2][14]=true;
      list_murV[1][9]=true;
      list_murV[7][6]=true;
      list_murV[8][6]=true;
      list_murV[7][8]=true;
      list_murV[8][8]=true;
    }


    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==1)
    {
      list_murH[3][0]=true;
      list_murH[5][1]=true;
      list_murH[9][1]=true;
      list_murH[10][0]=true;
      list_murH[11][2]=true;
      list_murH[1][3]=true;
      list_murH[4][4]=true;
      list_murH[12][5]=true;
      list_murH[7][5]=true;
      list_murH[2][5]=true;
      list_murH[6][7]=true;
      list_murH[6][8]=true;
      list_murH[8][7]=true;
      list_murH[8][8]=true;
      list_murH[9][7]=true;
      list_murH[12][9]=true;
      list_murH[3][9]=true;
      list_murH[1][10]=true;
      list_murH[5][13]=true;
      list_murH[2][14]=true;
      list_murH[3][15]=true;
      list_murH[8][12]=true;
      list_murH[11][14]=true;
      list_murH[13][13]=true;
      list_murH[13][15]=true;

      list_murV[9][0]=true;
      list_murV[15][1]=true;
      list_murV[6][1]=true;
      list_murV[11][2]=true;
      list_murV[15][3]=true;
      list_murV[5][3]=true;
      list_murV[0][3]=true;
      list_murV[1][2]=true;
      list_murV[2][5]=true;
      list_murV[7][5]=true;
      list_murV[13][5]=true;
      list_murV[10][6]=true;
      list_murV[8][6]=true;
      list_murV[7][6]=true;
      list_murV[0][6]=true;
      list_murV[7][8]=true;
      list_murV[8][8]=true;
      list_murV[12][8]=true;
      list_murV[4][9]=true;
      list_murV[1][9]=true;
      list_murV[2][14]=true;
      list_murV[6][12]=true;
      list_murV[9][11]=true;
      list_murV[11][14]=true;
      list_murV[14][13]=true;
    }

    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==0)
    {
    //?
    list_murH[3][0]=true;
    list_murH[5][1]=true;
    list_murH[9][1]=true;
    list_murH[10][0]=true;
    list_murH[11][2]=true;
    list_murH[1][3]=true;
    list_murH[4][4]=true;
    list_murH[2][5]=true;
    list_murH[12][5]=true;
    list_murH[9][7]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[3][9]=true;
    list_murH[4][11]=true;
    list_murH[0][13]=true;
    list_murH[4][15]=true;
    list_murH[6][14]=true;
    list_murH[8][14]=true;
    list_murH[10][15]=true;
    list_murH[8][10]=true;
    list_murH[12][9]=true;
    list_murH[14][13]=true;
    list_murH[7][5]=true;



    list_murV[6][1]=true;
    list_murV[9][0]=true;
    list_murV[11][2]=true;
    list_murV[15][3]=true;
    list_murV[13][5]=true;
    list_murV[7][5]=true;
    list_murV[5][3]=true;
    list_murV[1][2]=true;
    list_murV[0][2]=true;
    list_murV[2][5]=true;
    list_murV[0][6]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[9][10]=true;
    list_murV[15][9]=true;
    list_murV[12][8]=true;
    list_murV[10][6]=true;
    list_murV[14][13]=true;
    list_murV[9][13]=true;
    list_murV[6][13]=true;
    list_murV[5][10]=true;
    list_murV[3][9]=true;
    list_murV[1][13]=true;
    }

    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==1)
    {
    //?
    list_murH[3][0]=true;
    list_murH[10][0]=true;
    list_murH[9][1]=true;
    list_murH[5][1]=true;
    list_murH[1][3]=true;
    list_murH[4][4]=true;
    list_murH[2][5]=true;
    list_murH[7][5]=true;
    list_murH[11][2]=true;
    list_murH[12][5]=true;
    list_murH[9][7]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[12][9]=true;
    list_murH[3][9]=true;
    list_murH[4][11]=true;
    list_murH[0][13]=true;
    list_murH[4][15]=true;
    list_murH[6][14]=true;
    list_murH[8][12]=true;
    list_murH[13][13]=true;
    list_murH[13][15]=true;
    list_murH[11][14]=true;


    list_murV[6][1]=true;
    list_murV[9][0]=true;
    list_murV[11][2]=true;
    list_murV[15][1]=true;
    list_murV[15][3]=true;
    list_murV[5][3]=true;
    list_murV[1][2]=true;
    list_murV[0][2]=true;
    list_murV[0][6]=true;
    list_murV[2][5]=true;
    list_murV[7][5]=true;
    list_murV[13][5]=true;
    list_murV[10][6]=true;
    list_murV[8][6]=true;
    list_murV[7][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[12][8]=true;
    list_murV[9][11]=true;
    list_murV[5][10]=true;
    list_murV[3][9]=true;
    list_murV[14][13]=true;
    list_murV[11][14]=true;
    list_murV[6][13]=true;
    list_murV[1][13]=true;

    }

    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==0)
    {
    //?
    list_murH[3][0]=true;
    list_murH[9][0]=true;
    list_murH[13][1]=true;
    list_murH[10][2]=true;
    list_murH[5][1]=true;
    list_murH[1][3]=true;
    list_murH[4][4]=true;
    list_murH[2][5]=true;
    list_murH[7][5]=true;
    list_murH[10][7]=true;
    list_murH[13][6]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[3][9]=true;
    list_murH[1][10]=true;
    list_murH[2][14]=true;
    list_murH[3][15]=true;
    list_murH[5][13]=true;
    list_murH[8][14]=true;
    list_murH[10][15]=true;
    list_murH[8][10]=true;
    list_murH[14][13]=true;
    list_murH[12][9]=true;


    list_murV[6][1]=true;
    list_murV[11][2]=true;
    list_murV[14][0]=true;
    list_murV[15][3]=true;
    list_murV[7][5]=true;
    list_murV[5][3]=true;
    list_murV[1][2]=true;
    list_murV[0][3]=true;
    list_murV[0][6]=true;
    list_murV[2][5]=true;
    list_murV[4][9]=true;
    list_murV[1][9]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[10][6]=true;
    list_murV[12][8]=true;
    list_murV[15][9]=true;
    list_murV[13][6]=true;
    list_murV[14][13]=true;
    list_murV[9][10]=true;
    list_murV[9][13]=true;
    list_murV[6][12]=true;
    list_murV[2][14]=true;
    }


    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==1)
    {
    //?
    list_murH[3][0]=true;
    list_murH[9][0]=true;
    list_murH[13][1]=true;
    list_murH[10][2]=true;
    list_murH[5][1]=true;
    list_murH[1][3]=true;
    list_murH[4][4]=true;
    list_murH[2][5]=true;
    list_murH[7][5]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[10][7]=true;
    list_murH[13][6]=true;
    list_murH[12][9]=true;
    list_murH[13][13]=true;
    list_murH[13][15]=true;
    list_murH[11][14]=true;
    list_murH[8][12]=true;
    list_murH[5][13]=true;
    list_murH[3][15]=true;
    list_murH[2][14]=true;
    list_murH[1][10]=true;
    list_murH[3][9]=true;


    list_murV[6][1]=true;
    list_murV[14][0]=true;
    list_murV[15][1]=true;
    list_murV[15][3]=true;
    list_murV[11][2]=true;
    list_murV[13][6]=true;
    list_murV[10][6]=true;
    list_murV[8][6]=true;
    list_murV[7][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[7][5]=true;
    list_murV[5][3]=true;
    list_murV[2][5]=true;
    list_murV[1][2]=true;
    list_murV[0][3]=true;
    list_murV[0][6]=true;
    list_murV[4][9]=true;
    list_murV[1][9]=true;
    list_murV[2][14]=true;
    list_murV[6][12]=true;
    list_murV[9][11]=true;
    list_murV[11][14]=true;
    list_murV[14][13]=true;
    list_murV[12][8]=true;
    }


    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==0)
    {

    //?
    list_murH[3][0]=true;
    list_murH[5][1]=true;
    list_murH[9][0]=true;
    list_murH[10][2]=true;
    list_murH[13][1]=true;
    list_murH[1][3]=true;
    list_murH[2][5]=true;
    list_murH[4][4]=true;
    list_murH[7][5]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[10][7]=true;
    list_murH[13][6]=true;
    list_murH[12][9]=true;
    list_murH[8][10]=true;
    list_murH[3][9]=true;
    list_murH[4][11]=true;
    list_murH[0][13]=true;
    list_murH[6][14]=true;
    list_murH[8][14]=true;
    list_murH[14][13]=true;
    list_murH[4][15]=true;
    list_murH[10][15]=true;


    list_murV[0][2]=true;
    list_murV[1][2]=true;
    list_murV[6][1]=true;
    list_murV[11][2]=true;
    list_murV[14][0]=true;
    list_murV[15][3]=true;
    list_murV[10][6]=true;
    list_murV[13][6]=true;
    list_murV[7][5]=true;
    list_murV[5][3]=true;
    list_murV[2][5]=true;
    list_murV[0][6]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[9][10]=true;
    list_murV[3][9]=true;
    list_murV[5][10]=true;
    list_murV[1][13]=true;
    list_murV[6][13]=true;
    list_murV[9][13]=true;
    list_murV[15][9]=true;
    list_murV[12][8]=true;
    list_murV[14][13]=true;
    }


    if(m_CurrentStimulus[0]==0 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==1)
    {
    //?
    list_murH[3][0]=true;
    list_murH[5][1]=true;
    list_murH[9][0]=true;
    list_murH[10][2]=true;
    list_murH[13][1]=true;
    list_murH[13][6]=true;
    list_murH[10][7]=true;
    list_murH[12][9]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[7][5]=true;
    list_murH[4][4]=true;
    list_murH[1][3]=true;
    list_murH[2][5]=true;
    list_murH[3][9]=true;
    list_murH[4][11]=true;
    list_murH[0][13]=true;
    list_murH[6][14]=true;
    list_murH[8][12]=true;
    list_murH[11][14]=true;
    list_murH[13][13]=true;
    list_murH[13][15]=true;
    list_murH[4][15]=true;



    list_murV[0][2]=true;
    list_murV[1][2]=true;
    list_murV[6][1]=true;
    list_murV[5][3]=true;
    list_murV[11][2]=true;
    list_murV[15][1]=true;
    list_murV[15][3]=true;
    list_murV[14][0]=true;
    list_murV[13][6]=true;
    list_murV[10][6]=true;
    list_murV[8][6]=true;
    list_murV[7][6]=true;
    list_murV[7][5]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[12][8]=true;
    list_murV[14][13]=true;
    list_murV[11][14]=true;
    list_murV[9][11]=true;
    list_murV[5][10]=true;
    list_murV[6][13]=true;
    list_murV[1][13]=true;
    list_murV[3][9]=true;
    list_murV[0][6]=true;
    list_murV[2][5]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==0)
    {
    list_murH[4][0]=true;
    list_murH[10][0]=true;
    list_murH[11][2]=true;
    list_murH[12][5]=true;
    list_murH[5][4]=true;
    list_murH[2][1]=true;
    list_murH[0][3]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[5][6]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[3][7]=true;
    list_murH[3][9]=true;
    list_murH[1][10]=true;
    list_murH[2][14]=true;
    list_murH[3][15]=true;
    list_murH[5][13]=true;
    list_murH[10][15]=true;
    list_murH[8][14]=true;
    list_murH[14][13]=true;
    list_murH[12][9]=true;
    list_murH[8][10]=true;
    list_murH[9][7]=true;
    list_murH[9][1]=true;


    list_murV[0][3]=true;
    list_murV[1][3]=true;
    list_murV[0][4]=true;
    list_murV[2][1]=true;
    list_murV[6][3]=true;
    list_murV[9][0]=true;
    list_murV[11][2]=true;
    list_murV[15][3]=true;
    list_murV[13][5]=true;
    list_murV[12][8]=true;
    list_murV[15][9]=true;
    list_murV[10][6]=true;
    list_murV[8][6]=true;
    list_murV[7][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[9][10]=true;
    list_murV[4][9]=true;
    list_murV[5][5]=true;
    list_murV[3][7]=true;
    list_murV[1][9]=true;
    list_murV[2][14]=true;
    list_murV[6][12]=true;
    list_murV[9][13]=true;
    list_murV[14][13]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==1)
    {
    list_murH[4][0]=true;
    list_murH[2][1]=true;
    list_murH[0][3]=true;
    list_murH[5][4]=true;
    list_murH[5][6]=true;
    list_murH[3][7]=true;
    list_murH[3][9]=true;
    list_murH[1][10]=true;
    list_murH[2][14]=true;
    list_murH[3][15]=true;
    list_murH[5][13]=true;
    list_murH[8][12]=true;
    list_murH[6][8]=true;
    list_murH[6][7]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[9][7]=true;
    list_murH[9][1]=true;
    list_murH[10][0]=true;
    list_murH[11][2]=true;
    list_murH[12][5]=true;
    list_murH[12][9]=true;
    list_murH[13][13]=true;
    list_murH[13][15]=true;
    list_murH[11][14]=true;


    list_murV[2][1]=true;
    list_murV[0][3]=true;
    list_murV[1][3]=true;
    list_murV[0][4]=true;
    list_murV[6][3]=true;
    list_murV[9][0]=true;
    list_murV[15][1]=true;
    list_murV[15][3]=true;
    list_murV[11][2]=true;
    list_murV[13][5]=true;
    list_murV[10][6]=true;
    list_murV[12][8]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[5][5]=true;
    list_murV[4][9]=true;
    list_murV[3][7]=true;
    list_murV[1][9]=true;
    list_murV[2][14]=true;
    list_murV[6][12]=true;
    list_murV[9][11]=true;
    list_murV[14][13]=true;
    list_murV[11][14]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==0)
    {
    list_murH[4][0]=true;
    list_murH[10][0]=true;
    list_murH[9][1]=true;
    list_murH[11][2]=true;
    list_murH[12][5]=true;
    list_murH[5][4]=true;
    list_murH[2][1]=true;
    list_murH[0][3]=true;
    list_murH[3][7]=true;
    list_murH[5][6]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[9][7]=true;
    list_murH[12][9]=true;
    list_murH[8][10]=true;
    list_murH[4][11]=true;
    list_murH[3][9]=true;
    list_murH[0][13]=true;
    list_murH[4][15]=true;
    list_murH[6][14]=true;
    list_murH[8][14]=true;
    list_murH[10][15]=true;
    list_murH[14][13]=true;


    list_murV[0][2]=true;
    list_murV[1][3]=true;
    list_murV[2][1]=true;
    list_murV[6][3]=true;
    list_murV[9][0]=true;
    list_murV[11][2]=true;
    list_murV[15][3]=true;
    list_murV[13][5]=true;
    list_murV[15][9]=true;
    list_murV[12][8]=true;
    list_murV[10][6]=true;
    list_murV[8][6]=true;
    list_murV[7][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[5][5]=true;
    list_murV[0][4]=true;
    list_murV[3][7]=true;
    list_murV[3][9]=true;
    list_murV[5][10]=true;
    list_murV[1][13]=true;
    list_murV[6][13]=true;
    list_murV[9][13]=true;
    list_murV[9][10]=true;
    list_murV[14][13]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==0 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==1)
    {
    list_murH[4][0]=true;
    list_murH[10][0]=true;
    list_murH[9][1]=true;
    list_murH[11][2]=true;
    list_murH[12][5]=true;
    list_murH[5][4]=true;
    list_murH[5][6]=true;
    list_murH[0][3]=true;
    list_murH[3][7]=true;
    list_murH[3][9]=true;
    list_murH[0][13]=true;
    list_murH[4][11]=true;
    list_murH[6][14]=true;
    list_murH[8][12]=true;
    list_murH[13][13]=true;
    list_murH[13][15]=true;
    list_murH[11][14]=true;
    list_murH[12][9]=true;
    list_murH[9][7]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[4][15]=true;
    list_murH[2][1]=true;


    list_murV[2][1]=true;
    list_murV[0][2]=true;
    list_murV[1][3]=true;
    list_murV[0][4]=true;
    list_murV[6][3]=true;
    list_murV[5][5]=true;
    list_murV[3][7]=true;
    list_murV[3][9]=true;
    list_murV[1][13]=true;
    list_murV[5][10]=true;
    list_murV[6][13]=true;
    list_murV[9][11]=true;
    list_murV[11][14]=true;
    list_murV[14][13]=true;
    list_murV[12][8]=true;
    list_murV[10][6]=true;
    list_murV[13][5]=true;
    list_murV[15][3]=true;
    list_murV[15][1]=true;
    list_murV[11][2]=true;
    list_murV[9][0]=true;
    list_murV[8][6]=true;
    list_murV[7][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==0)
    {
    list_murH[4][0]=true;
    list_murH[9][0]=true;
    list_murH[10][2]=true;
    list_murH[13][1]=true;
    list_murH[13][6]=true;
    list_murH[10][7]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[5][6]=true;
    list_murH[5][4]=true;
    list_murH[0][3]=true;
    list_murH[3][7]=true;
    list_murH[3][9]=true;
    list_murH[1][10]=true;
    list_murH[2][14]=true;
    list_murH[3][15]=true;
    list_murH[5][13]=true;
    list_murH[8][14]=true;
    list_murH[10][15]=true;
    list_murH[14][13]=true;
    list_murH[12][9]=true;
    list_murH[8][10]=true;
    list_murH[2][1]=true;


    list_murV[2][1]=true;
    list_murV[0][3]=true;
    list_murV[1][3]=true;
    list_murV[0][4]=true;
    list_murV[6][3]=true;
    list_murV[5][5]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[10][6]=true;
    list_murV[13][6]=true;
    list_murV[15][3]=true;
    list_murV[14][0]=true;
    list_murV[11][2]=true;
    list_murV[15][9]=true;
    list_murV[12][8]=true;
    list_murV[9][10]=true;
    list_murV[14][13]=true;
    list_murV[9][13]=true;
    list_murV[6][12]=true;
    list_murV[4][9]=true;
    list_murV[2][14]=true;
    list_murV[1][9]=true;
    list_murV[3][7]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==0 &&
        m_CurrentStimulus[3]==1)
    {
    list_murH[4][0]=true;
    list_murH[9][0]=true;
    list_murH[10][2]=true;
    list_murH[13][1]=true;
    list_murH[13][6]=true;
    list_murH[10][7]=true;
    list_murH[5][4]=true;
    list_murH[0][3]=true;
    list_murH[5][6]=true;
    list_murH[3][7]=true;
    list_murH[3][9]=true;
    list_murH[1][10]=true;
    list_murH[2][14]=true;
    list_murH[3][15]=true;
    list_murH[5][13]=true;
    list_murH[8][12]=true;
    list_murH[11][14]=true;
    list_murH[13][15]=true;
    list_murH[13][13]=true;
    list_murH[12][9]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;
    list_murH[2][1]=true;


    list_murV[0][3]=true;
    list_murV[1][3]=true;
    list_murV[0][4]=true;
    list_murV[2][1]=true;
    list_murV[6][3]=true;
    list_murV[11][2]=true;
    list_murV[15][1]=true;
    list_murV[15][3]=true;
    list_murV[14][0]=true;
    list_murV[13][6]=true;
    list_murV[10][6]=true;
    list_murV[12][8]=true;
    list_murV[14][13]=true;
    list_murV[11][14]=true;
    list_murV[9][11]=true;
    list_murV[6][12]=true;
    list_murV[4][9]=true;
    list_murV[1][9]=true;
    list_murV[2][14]=true;
    list_murV[3][7]=true;
    list_murV[5][5]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==0)
    {
    list_murH[4][0]=true;
    list_murH[2][1]=true;
    list_murH[0][3]=true;
    list_murH[5][4]=true;
    list_murH[5][6]=true;
    list_murH[3][7]=true;
    list_murH[3][9]=true;
    list_murH[0][13]=true;
    list_murH[4][15]=true;
    list_murH[6][14]=true;
    list_murH[4][11]=true;
    list_murH[8][10]=true;
    list_murH[8][14]=true;
    list_murH[10][15]=true;
    list_murH[14][13]=true;
    list_murH[12][9]=true;
    list_murH[10][7]=true;
    list_murH[13][6]=true;
    list_murH[13][1]=true;
    list_murH[10][2]=true;
    list_murH[9][0]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;


    list_murV[7][8]=true;
    list_murV[8][8]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[2][1]=true;
    list_murV[0][2]=true;
    list_murV[1][3]=true;
    list_murV[0][4]=true;
    list_murV[6][3]=true;
    list_murV[11][2]=true;
    list_murV[14][0]=true;
    list_murV[15][3]=true;
    list_murV[15][9]=true;
    list_murV[12][8]=true;
    list_murV[13][6]=true;
    list_murV[10][6]=true;
    list_murV[14][13]=true;
    list_murV[9][13]=true;
    list_murV[9][10]=true;
    list_murV[6][13]=true;
    list_murV[5][10]=true;
    list_murV[1][13]=true;
    list_murV[3][7]=true;
    list_murV[3][9]=true;
    list_murV[5][5]=true;
    }

    if(m_CurrentStimulus[0]==1 &&
        m_CurrentStimulus[1]==1 &&
          m_CurrentStimulus[2]==1 &&
        m_CurrentStimulus[3]==1)
    {
    list_murH[2][1]=true;
    list_murH[4][0]=true;
    list_murH[0][3]=true;
    list_murH[5][4]=true;
    list_murH[5][6]=true;
    list_murH[9][0]=true;
    list_murH[10][2]=true;
    list_murH[13][1]=true;
    list_murH[13][6]=true;
    list_murH[10][7]=true;
    list_murH[12][9]=true;
    list_murH[13][13]=true;
    list_murH[13][15]=true;
    list_murH[11][14]=true;
    list_murH[8][12]=true;
    list_murH[6][14]=true;
    list_murH[4][15]=true;
    list_murH[4][11]=true;
    list_murH[3][9]=true;
    list_murH[0][13]=true;
    list_murH[3][7]=true;
    list_murH[6][7]=true;
    list_murH[6][8]=true;
    list_murH[8][7]=true;
    list_murH[8][8]=true;


    list_murV[0][2]=true;
    list_murV[1][3]=true;
    list_murV[2][1]=true;
    list_murV[6][3]=true;
    list_murV[0][4]=true;
    list_murV[3][7]=true;
    list_murV[5][5]=true;
    list_murV[3][9]=true;
    list_murV[5][10]=true;
    list_murV[1][13]=true;
    list_murV[6][13]=true;
    list_murV[9][11]=true;
    list_murV[11][14]=true;
    list_murV[14][13]=true;
    list_murV[12][8]=true;
    list_murV[10][6]=true;
    list_murV[13][6]=true;
    list_murV[15][3]=true;
    list_murV[15][1]=true;
    list_murV[14][0]=true;
    list_murV[11][2]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;
    }


    list_target[8]=Coordonnees(14,13);//averif
    target_coord=list_target[target];

    robot_target=floor((target-1)/4);     // prolog : move([_,_,_,_,TargetId|_],[Robot,1]):-Robot is floor((TargetId-1)/4).

    Coordonnees Blue_robot=Coordonnees(m_CurrentStimulus[5],m_CurrentStimulus[6]);
    Coordonnees Green_robot=Coordonnees(m_CurrentStimulus[7],m_CurrentStimulus[8]);
    Coordonnees Red_robot=Coordonnees(m_CurrentStimulus[9],m_CurrentStimulus[10]);
    Coordonnees Yellow_robot=Coordonnees(m_CurrentStimulus[11],m_CurrentStimulus[12]);



    switch(robot_target){
        case 0:
            robot_target_coord=Blue_robot;
            list_murH[Green_robot.getX()][Green_robot.getY()]=true;
            list_murH[Red_robot.getX()][Red_robot.getY()]=true;
            list_murH[Yellow_robot.getX()][Yellow_robot.getY()]=true;
            list_murV[Green_robot.getX()][Green_robot.getY()]=true;
            list_murV[Red_robot.getX()][Red_robot.getY()]=true;
            list_murV[Yellow_robot.getX()][Yellow_robot.getY()]=true;
        break;
        case 1:
            robot_target_coord=Green_robot;
            list_murH[Blue_robot.getX()][Blue_robot.getY()]=true;
            list_murH[Red_robot.getX()][Red_robot.getY()]=true;
            list_murH[Yellow_robot.getX()][Yellow_robot.getY()]=true;
            list_murV[Blue_robot.getX()][Blue_robot.getY()]=true;
            list_murV[Red_robot.getX()][Red_robot.getY()]=true;
            list_murV[Yellow_robot.getX()][Yellow_robot.getY()]=true;
        break;
        case 2:
            robot_target_coord=Red_robot;
            list_murH[Green_robot.getX()][Green_robot.getY()]=true;
            list_murH[Blue_robot.getX()][Blue_robot.getY()]=true;
            list_murH[Yellow_robot.getX()][Yellow_robot.getY()]=true;
            list_murV[Green_robot.getX()][Green_robot.getY()]=true;
            list_murV[Blue_robot.getX()][Blue_robot.getY()]=true;
            list_murV[Yellow_robot.getX()][Yellow_robot.getY()]=true;
        break;
        case 3:
            robot_target_coord=Yellow_robot;
            list_murH[Green_robot.getX()][Green_robot.getY()]=true;
            list_murH[Blue_robot.getX()][Blue_robot.getY()]=true;
            list_murH[Blue_robot.getX()][Blue_robot.getY()]=true;
            list_murV[Green_robot.getX()][Green_robot.getY()]=true;
            list_murV[Blue_robot.getX()][Blue_robot.getY()]=true;
            list_murV[Blue_robot.getX()][Blue_robot.getY()]=true;
        break;
    default:
            robot_target_coord=Blue_robot;
            list_murH[Green_robot.getX()][Green_robot.getY()]=true;
            list_murH[Red_robot.getX()][Red_robot.getY()]=true;
            list_murH[Yellow_robot.getX()][Yellow_robot.getY()]=true;
            list_murV[Green_robot.getX()][Green_robot.getY()]=true;
            list_murV[Red_robot.getX()][Red_robot.getY()]=true;
            list_murV[Yellow_robot.getX()][Yellow_robot.getY()]=true;
            break;


    }

}

// Récupération de la position des cibles
Coordonnees Bd::getlist_target(int i)
{
    return list_target[i];
}

// Récupération de la position des obstacles
bool Bd::getlist_murH(int i, int j)
{
    return list_murH[i][j];
}

bool Bd::getlist_murV(int i, int j)
{
    return list_murV[i][j];
}

Coordonnees Bd::getRobot_Target_Coord()
{
    return this->robot_target_coord;
}

Coordonnees Bd::getTarget_Coord()
{
    return this->target_coord;
}

int Bd::getRobot_Target()
{
    return this->robot_target;
}

int Bd::getTarget()
{
    return this->target;
}


