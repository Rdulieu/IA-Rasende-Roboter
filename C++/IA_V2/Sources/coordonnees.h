#ifndef COORDONNEES_H
#define COORDONNEES_H

class Coordonnees {

    private:
        int x;
        int y;

    public:
        Coordonnees();
        Coordonnees(int px,int py);
        //getters et setters
        void setX(int px);
        void setY(int py);

        int getX();
        int getY();

};


/*class Coord_mur: public Coordonnees {

    private:
        string orientation;

    public:
        Coord_mur();
        Coord_mur(string porientation);
        //getters et setters
        void setOrientation(string porientation);

        string getOrientation();

};*/

#endif // COORDONNEES_H
