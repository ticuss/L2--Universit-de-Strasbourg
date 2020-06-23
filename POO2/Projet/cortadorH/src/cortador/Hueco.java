package cortador;

import java.util.ArrayList;

public class Hueco {

	/**
* Classe qui représente les espaces à l'intérieur d'un rectangle associé à un
* pièce.
*
* @auteur
*
*/

	private double x0 = 0., y0 = 0.; // coordonnées par rapport au rectangle contenant
	private double dx = 0., dy = 0.;// largeur et hauteur de hueco
	private boolean tienePiezasHInsertadas = false;
	private ArrayList<PiezaH> piezasHInsertadas = null;
	private ArrayList<ColumnaH> myColumnasH = null;
	private double altoCubiertoPorUltimaColumnaH = 0.;// hauteur de colonne incomplète
	private double anchoTotalCubiertoPorColumnasH = 0.;// largeur totale de toutes les colonnes déjà complétées
	private double area = 0.;
	private int noPiezasInsertadas = 0;

	private ColumnaH ultimaColumnaIncompleta = null;
	private boolean MUESTRA = false;

	public Hueco() {
		piezasHInsertadas = new ArrayList<PiezaH>();
		myColumnasH = new ArrayList<ColumnaH>();

	}

	/**
	* Constructeur général pour toutes les lacunes de pièces
	*
	* @param x0 coordonnée c / r à l'origine de la pièce qui la contient
	* @param y0
	* @param dx largeur de l'espace. Ne doit pas dépasser 1.
	* @param dy alto.
	*/
	public Hueco(double x0, double y0, double dx, double dy) {
		this.x0 = x0;
		this.y0 = y0;
		this.dx = dx;
		this.dy = dy;

		if (x0 + dx > 1.0)
			this.dx = 1. - this.x0; // assurez-vous que Hueco est dans l'intervalle [0,1.]

		if (y0 + dy > 1.0)
			this.dy = 1. - this.y0;
		area = dx * dy;

		piezasHInsertadas = new ArrayList<PiezaH>();
		myColumnasH = new ArrayList<ColumnaH>();
	}

	/**
	* Constructeur représentant la ceinture
	*
	* @param dx largeur maximale de bande
	*/
	public Hueco(double dx) {
		this.dx = dx;
		this.dy = 1.0;
		this.x0 = 0.;
		this.y0 = 0;
		area = dx * dy;
		piezasHInsertadas = new ArrayList<PiezaH>();
		myColumnasH = new ArrayList<ColumnaH>();

	}

	public double getAltoCubiertoPorUltimaColumnaH() {
		return altoCubiertoPorUltimaColumnaH;
	}

	public void setAltoCubiertoPorUltimaColumnaH(double altoCubiertoPorUltimaColumnaH) {
		this.altoCubiertoPorUltimaColumnaH = altoCubiertoPorUltimaColumnaH;
	}

	public double getAnchoTotalCubiertoPorColumnaH() {
		return anchoTotalCubiertoPorColumnasH;
	}

	public void setAnchoTotalCubiertoPorColumnaH(double anchoTotalCubiertoPorColumnasH) {
		this.anchoTotalCubiertoPorColumnasH = anchoTotalCubiertoPorColumnasH;
	}

	public double getArea() {
		return area;
	}

	public void setArea(double area) {
		this.area = area;
	}

	public double getX0() {
		return x0;
	}

	public void setX0(double x0) {
		this.x0 = x0;
	}

	public double getY0() {
		return y0;
	}

	public void setY0(double y0) {
		this.y0 = y0;
	}

	public double getDx() {
		return dx;
	}

	public void setDx(double dx) {
		this.dx = dx;
	}

	public double getDy() {
		return dy;
	}

	public void setDy(double dy) {
		this.dy = dy;
	}

	public boolean isTienePiezasHInsertadas() {
		return tienePiezasHInsertadas;
	}

	public void setTienePiezasHInsertadas(boolean tienePiezasHInsertadas) {
		this.tienePiezasHInsertadas = tienePiezasHInsertadas;
	}

	public ArrayList<PiezaH> getPiezasHInsertadas() {
		return piezasHInsertadas;
	}

	public void setPiezasHInsertadas(ArrayList<PiezaH> piezasHInsertadas) {
		this.piezasHInsertadas = piezasHInsertadas;
	}

	public ArrayList<ColumnaH> getMyColumnasH() {
		return myColumnasH;
	}

	public void setMyColumnasH(ArrayList<ColumnaH> columnasHInsertadas) {
		this.myColumnasH = columnasHInsertadas;
	}

	public int getNoPiezasInsertadas() {
		return noPiezasInsertadas;
	}

	public void setNoPiezasInsertadas(int noPiezasInsertadas) {
		this.noPiezasInsertadas = noPiezasInsertadas;
	}

	/**
	* Il permet de connaître la largeur totale des colonnes complètes Livraison 0 s'il n'y a PAS de colonnes
	* inséré
	*
	* @revenir
	*/
	public double calculaAnchoTotalDeColumnasHCompletas() {

		anchoTotalCubiertoPorColumnasH = 0.;
		if (myColumnasH != null && !myColumnasH.isEmpty()) {

			for (ColumnaH col : myColumnasH) {
				if (col.estaEnTop()) {
					anchoTotalCubiertoPorColumnasH += col.getMaxAnchoCol();
				}
			}
		}
		return anchoTotalCubiertoPorColumnasH;
	}

	/**
	* Il permet de connaître la hauteur totale de la dernière colonne Livraison 0 s'il n'y a PAS de colonnes
	* inséré
	*
	* @return highCoveredUltimateColumn
	*/
	public double calculaAltoCubiertoPorUltimaColumnaH() {
		altoCubiertoPorUltimaColumnaH = 0.;
		if (myColumnasH != null && !myColumnasH.isEmpty()) {

			ColumnaH col = myColumnasH.get(myColumnasH.size() - 1);
			ArrayList<PiezaH> pzs = col.getMyPiezasH();
			if (pzs != null && !pzs.isEmpty()) {
				for (PiezaH pz : pzs)
					altoCubiertoPorUltimaColumnaH += pz.getAlto();
			}

		}
		return altoCubiertoPorUltimaColumnaH;
	}

	/**
	 * Cette routine doit être utilisée à la fin d'avoir rempli l'écart avec des morceaux de
	 * façon de connaître les positions des origines de chaque rectangle avec attention
	 * à l'origine du trou
	 * 
	 */
	public void ajustaCoordenadasDePiezasConRespectoAOrigenDelHueco() {
		if (myColumnasH != null && !myColumnasH.isEmpty()) {
			ArrayList<PiezaH> pzs = null;
			double ancho = 0., alto = 0.;
			if (MUESTRA)
				System.out.println("Affichage des coordonnées dans l'écart: " + dx + " " + dy);
			for (ColumnaH col : myColumnasH) {
				pzs = col.getMyPiezasH();
				alto = 0.;
				if (pzs != null && !pzs.isEmpty()) {
					for (PiezaH pz : pzs) {
						pz.setPosX(ancho);
						pz.setPosY(alto);
						if (MUESTRA)
							System.out.println(
									"indice " + pz.getIndice() + " x0: " + pz.getPosX() + " y0: " + pz.getPosY());
						alto = alto + pz.getAlto();// la position Y accumule la hauteur des pièces
					}
					ancho = ancho + col.getMaxAnchoCol();// Toutes les pièces sont alignées
					// a gauche à la largeur maximale de la colonne précédente
				}
			}

		}
	}

	public void inserta(PiezaH x, ColumnaH col2) {

		// TODO Auto-generated method stub
		if (x.isCabeRectaEnHueco()) {
			col2.getArrayDeColunna().add(x);// insérer sans rotation
			x.setUsado(true);
			noPiezasInsertadas++;
		} else if (!x.isCabeRectaEnHueco()) {
			// Il est déjà tourné lorsque
			// trouvé pour s'adapter
			// eh bien vous devez le remplir avec la bonne orientation si
			// c'est qu'il a des lacunes à combler
			col2.getArrayDeColunna().add(x);
			x.setUsado(true);
			noPiezasInsertadas++;
		}

	}

	/**
	* Créez une nouvelle colonne creuse, réinitialisez-la à une largeur et une hauteur nulles et ajoutez-la à
	* la liste. Lorsque vous créez une colonne, c'est parce que les autres sont entrés TOP. Pour
	* ceux qui sont entrés en TOP ne pourront remplir l'espace entre la limite
	* bas du TOP et de la paroi supérieure du trou, avec une largeur fixée par le
	* largeur maximale des pièces en dessous du TOP.
	 */
	public void creaNuevaColumnaH() {
		if (myColumnasH.size() > 0)
			myColumnasH.get(myColumnasH.size() - 1).setEstaEnTop(true);
		ColumnaH col = new ColumnaH();
		col.setEstaEnTop(false);
		col.setAnchoMax(0.);
		col.setAltoTotal(0.);
		myColumnasH.add(col);
		return;
	}

	/**
	* Vérifiez si une pièce correspond à DROITE en dehors de l'ensemble des colonnes, dans le
	* espace entre la face droite de la dernière colonne et la paroi du trou. | x x
	* | | xxx | | xxx | | xxxô | ô s'adapte à droite <ou adapte ROTATED M90
	*
	* @param pz: pièce
	* @param et index de la dernière colonne à considérer dans le calcul de la largeur
	* @return true, si possible. faux si ça ne va pas
	*/
	public boolean contieneDerechaAPiezaAfueraDeCol(PiezaH pz, int i) {
		boolean res = false;
		double anchox = 0.;
		anchox = getMaxAnchoTotalCols(i);

		if ((pz.getAncho() + anchox < dx) && (pz.getAlto() < dy)) {
			res = true;
			pz.setCabeRectaEnHueco(true);// Se usa para insertar
		}
		return res;
	}

	/**
	* Vérifiez si une pièce correspond à DROITE sur les éléments d'une colonne avec des éléments
	* Tenez compte de toute la largeur couverte par les colonnes précédentes.
	*
	* @param pz: Pièce à tester
	* @param i: index des colonnes où tester
	* @return: vrai si possible, faux sinon
	*/
	public boolean contieneDerechaAPiezaEnCol(PiezaH pz, int i) {
		boolean res = false;
		double anchox = getMaxAnchoTotalCols(i - 1);
		double altoCol = getAltoTotalCol(i);
		if ((pz.getAncho() + anchox < dx) && (altoCol + pz.getAlto() < dy)) {
			res = true;
			pz.setCabeRectaEnHueco(true);// Se usa para insertar
		}

		return res;
	}

	/**
	* Vérifiez si une pièce s'adapte en ROTATION sur des éléments d'une colonne avec des éléments
	* Tenez compte de toute la largeur couverte par les colonnes précédentes.
	*
	* @param pz: Pièce à tester
	* @param i: index des colonnes où tester
	* @return: vrai si possible, faux sinon
	*/
	public boolean contieneRotM90APiezaEnCol(PiezaH pz, int i) {
		boolean res = false;
		double anchox = getMaxAnchoTotalCols(i - 1);
		double altoCol = getAltoTotalCol(i);
		if ((pz.getAlto() + anchox < dx) && (altoCol + pz.getAncho() < dy)) {
			res = true;
			pz.setCabeRectaEnHueco(false);// Se usa para insertar
		}

		return res;
	}

	/**
	* Vérifiez si une pièce correspond ROTÉE à M90 dans le HAUT d'une colonne. Pour ca
	* considérez l'espace entre le dernier morceau de la colonne et le mur supérieur
	* de l'espace et de la largeur précédente de la colonne, qui est figée lorsqu'elle est
	* au sommet.
	*
	* @param pz Pièce à tester
	* Colonne @param col où vous souhaitez insérer
	* @return true si possible, false sinon.
	*/
	public boolean contieneRotM90APiezaEnTopDeCol(PiezaH pz, ColumnaH col) {
		boolean res = false;
		double anchoCol = col.getMaxAnchoCol();
		double altoCol = col.getAltoTotalCol();
		if ((pz.getAlto() <= anchoCol) && (altoCol + pz.getAncho() < dy)) {
			res = true;
			pz.setCabeRectaEnHueco(false);// usa para insertar
		}

		return res;
	}

	/**
	* Vérifiez si une pièce correspond à DROITE sur le HAUT d'une colonne. Pour ca
	* considérez l'espace entre le dernier morceau de la colonne et le mur supérieur
	* de l'espace et de la largeur précédente de la colonne, qui est figée lorsqu'elle est
	* au sommet.
	*
	* @param pz
	* @param col
	* @revenir
	*/
	public boolean contieneDerechaAPiezaEnTopDeCol(PiezaH pz, ColumnaH col) {
		boolean res = false;
		double anchoCol = col.getMaxAnchoCol();
		double altoCol = col.getAltoTotalCol();
		if ((pz.getAncho() <= anchoCol) && (altoCol + pz.getAlto() < dy)) {
			res = true;
			pz.setCabeRectaEnHueco(true);// Se usa para insertar
		}
		return res;
	}

	/**
	* Calculer la largeur totale des colonnes créées dans un espace jusqu'à un certain
	* colonne, considérant la somme des largeurs maximales de toutes les colonnes,
	* y compris le dernier en question.
	*
	* @param et index de la dernière colonne inclus dans le calcul
	* @revenir; largeur totale des colonnes jusqu'à la colonne incluse: i
	*/
	public double getMaxAnchoTotalCols(int i) {
		double ancho = 0.;
		int tam = myColumnasH.size();
		for (int j = 0; i >= 0 && j <= i && j < tam; j++) {
			ancho = ancho + myColumnasH.get(j).getMaxAnchoCol();
		}
		return ancho;
	}

		/**
	 * Calculez la hauteur totale d'une colonne jusqu'au moment de l'appel	 * 
	 * @param i: index de la colonne à considérer
	 * @ valeur de retour de la hauteur totale de la colonne
	 */
	public double getAltoTotalCol(int i) {
		double altox = 0;
		ArrayList<PiezaH> pzs = myColumnasH.get(i).getMyPiezasH();
		for (PiezaH pz : pzs)
			altox = altox + pz.getAlto();
		return altox;
	}

	public void muestraEnConsolaPiezasDelHueco() {
		if (myColumnasH != null && !myColumnasH.isEmpty()) {
			int i = 0;
			for (ColumnaH col : myColumnasH) {
				System.out.println("idCol: " + i);
				col.muestraEnConsolaColumnaH();
				i++;
			}

		}
	}

	public void muestraEnConsolaCoordenadasDePiezasDelHuecoCrAHueco() {
		// if (noPiezasInsertadas > 0) {
		if (myColumnasH != null && !myColumnasH.isEmpty()) {
			int i = 0;
			for (ColumnaH col : myColumnasH) {
				System.out.println("idCol: " + i);
				for (PiezaH pz : col.getArrayDeColunna()) {
					System.out
							.println("indice: " + pz.getIndice() + " posX: " + pz.getPosX() + " posY: " + pz.getPosY());
					i++;
				}
			}
			// }
		}
	}

	public void muestraEnConsolaCoordenadasDePiezasDelHuecoCrAPiezaQueLasContiene() {
		// if (noPiezasInsertadas > 0) {
		if (myColumnasH != null && !myColumnasH.isEmpty()) {
			int i = 0;
			System.out.println("ancho: " + dx + " alto: " + dy);
			for (ColumnaH col : myColumnasH) {
				System.out.println("idCol: " + i);
				col.muestraEnConsolaCoordenadasDePiezasEnColumnaConRespectoAPiezaQueLasContiene();
				i++;
			}
			// }
		}
	}

	public double getAnchoTotalCubiertoPorColumnasH() {
		return anchoTotalCubiertoPorColumnasH;
	}

	public void setAnchoTotalCubiertoPorColumnasH(double anchoTotalCubiertoPorColumnasH) {
		this.anchoTotalCubiertoPorColumnasH = anchoTotalCubiertoPorColumnasH;
	}

	public ColumnaH getUltimaColumnaIncompleta() {
		return ultimaColumnaIncompleta;
	}

	public void setUltimaColumnaIncompleta(ColumnaH ultimaColumnaIncompleta) {
		this.ultimaColumnaIncompleta = ultimaColumnaIncompleta;
	}

	public void calculaAreaDeHueco() {
		area = dx * dy;

	}

	public void muestraEnConsolaAltoTotalDeColumnasEnHueco() {
		if (myColumnasH != null && !myColumnasH.isEmpty()) {
			int i = 0;
			for (ColumnaH col : myColumnasH) {
				System.out.println("idCol: " + i);
				col.muestraEnConsolaAltoTotalDeColumna();
				i++;
			}
		}
	}
}
