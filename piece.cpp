#include <utility> // pour pair
#include <vector>
#include<iostream>
#include"piece.hpp"
using namespace std;

//Piece







void Piece::trigger(const pair<int,int>& coord) {
	trigger(coord, *this); 
}


//Piece Concrete

PieceConcrete::PieceConcrete(const vector<pair<int,int>>& coords) : coordinates(coords) {

	cout << "piece concrete cree" << endl;
}


const vector<pair<int, int>>& PieceConcrete::getCoordinates() const { 
	return coordinates;
}

void PieceConcrete::accept(const PieceOperateur& v) { 
	v.visit(*this);
}

//Piece operateur

PieceOperateur::PieceOperateur(Piece& source, const pair<int, int>& position)
	: source{ source }, position{ position } {

	cout << "Operateur cree" << endl;

}




const vector<pair<int, int>>& PieceOperateur::getCoordinates() const {
	return source.getCoordinates(); 
}
void PieceOperateur::trigger(const pair<int, int>& relativePos, Piece& origin) {
	if (relativePos == position) {
		origin.accept(*this);
	}
	else {
		source.trigger(relativePos, origin);
	}
}


void PieceOperateur::visit(PieceConcrete& p) const {
	for (pair<int, int>& x : p.coordinates)  mapPosition(x);
}

// Operateur deplacement

OperateurDeplacement::OperateurDeplacement(Piece& source, const pair<int, int>& position, OrientationDeplacement sens) : PieceOperateur(source, position), sens{ sens } {

	cout << "Operateur de deplacement cree" << endl;

}

void OperateurDeplacement::accept(const PieceOperateur& v) {
	v.visit(*this);
}


void OperateurDeplacement::visit(OperateurDeplacement& x) const {
	// le deplacement ne modifie pas le sens
	mapPosition(x.position);
	x.source.accept(*this);
}


void OperateurDeplacement::mapPosition(pair<int, int>& pos) const {
	switch (sens) {
	case NORD: pos.second--; break;
	case SUD: pos.second++; break;
	case EST: pos.first++; break;
	case OUEST: pos.first--; break;
	}
}

int main() {
	vector<pair<int, int>> coords { {0, 0}, {0, 1}, {0, 2}, {1, 2}};
	PieceConcrete tetris_L(coords);
	Piece *p = new OperateurDeplacement {tetris_L,{0,0},EST};
	p->trigger(make_pair(0,0));
	p->trigger(make_pair(1,0));
}

