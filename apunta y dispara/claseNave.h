
class nave {
	int x, y;
	int corazones;
	int vidas;
public:
	nave(int _x, int _y, int _corazones, int _vidas) {
		x = _x;
		y = _y;
		corazones = _corazones;
		vidas = _vidas;
	}

	int X() { 
		return x; 
	}
	int Y() { return y; }

	void pintar();
	void borrar();
	void mover();
	void pintarSalud(); 
	void morir();
	int VID() { return vidas; }
	void COR() { corazones--; };
	int CORA() { return corazones; }
	void VIDPLUS() { corazones++; }

};

class asteroides {
	int x, y;
public:
	asteroides(int _x, int _y) {
		x = _x;
		y = _y;
	}

	void pintar();
	void mover();
	void choque(class nave &n);
	int X() { return x; }
	int Y() { return y; }
};

class bala {
	int x, y;
public:
	bala(int _x, int _y) {
		x = _x;
		y = _y;
	}
	int x_() { return x; };
	int y_() { return y; };
	void mover(class nave &b);
	bool fuera();
};