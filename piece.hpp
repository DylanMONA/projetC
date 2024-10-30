
#ifndef PIECE
#define PIECE
#include <utility> // pour pair
#include <vector>
using namespace std;


class PieceOperateur;
class Piece {
public:
	virtual void trigger(const pair<int,int>& coord, Piece& origin)=0 ;//jsp ce qu'elle fait
	void trigger(const pair<int, int>& coord);//jsp ce qu'elle fait
	virtual const vector<pair<int, int>>& getCoordinates() const =0; //donne coordonné piece
	virtual void accept(const PieceOperateur& v)=0 ;//jsp ce qu'elle fait
};


class PieceConcrete : public Piece {
public:
	//element de la classe
	vector<pair<int, int>> coordinates;
	//constructeur
	PieceConcrete(const vector<pair<int, int>>& coords);

	const vector<pair<int, int>>& getCoordinates() const;//donne coordonné piece
	void trigger(const pair<int, int>& coord, Piece& origin) {}//jsp ce qu'elle fait
	void accept(const PieceOperateur& v);//jsp ce qu'elle fait
};

class OperateurDeplacement;
class PieceOperateur : public Piece {
public:
	//element de la classe
	Piece& source;
	pair<int, int> position;

	//constructeur
	PieceOperateur(Piece& source, const pair<int, int>& position);

	const vector<pair<int, int>>& getCoordinates() const; //donne coordonné piece
	void trigger(const pair<int, int>& relativePos, Piece& origin); //jsp ce quelle fait

	virtual void mapPosition(pair<int, int>&) const =0; //position de la piece sur la map ?
	virtual void visit(PieceConcrete& p) const; //jsp ce qu'elle fait

	virtual void visit(OperateurDeplacement&) const =0; //deplacement simple haut bas gauche droite celon ce qu'on veut
	//virtual void visit(OperateurRotation &) const =0;
	//virtual void visit(OperateurSymetrie &) const =0;

	virtual void accept(const PieceOperateur& v) = 0; //jsp ce qu'elle fait

};

enum OrientationDeplacement { NORD, SUD, EST, OUEST };

class OperateurDeplacement : public PieceOperateur
{
public:
	//element de la classe
	OrientationDeplacement sens;
	//constructeur
	OperateurDeplacement(Piece& source, const pair<int, int>& position, OrientationDeplacement sens);
	
	virtual void accept(const PieceOperateur& v); //jsp ce qu'elle fait
	virtual void visit(OperateurDeplacement& x) const; //jsp ce qu'elle fait

	//virtual void visit(OperateurRotation &x) const;
	//virtual void visit(OperateurSymetrie &x) const;

	virtual void mapPosition(pair<int, int>& pos) const; //position sur la map
	
};
#endif