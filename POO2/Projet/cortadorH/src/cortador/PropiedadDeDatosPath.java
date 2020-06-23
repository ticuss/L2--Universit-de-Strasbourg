package cortador;

public class PropiedadDeDatosPath {
	/**
	 * Classe utilitaire qui garde donnnees de chaque path en détectant 
	 * archives produits par inkscape
	 */

	int k; // taille de données de path
	int k_ini; // position où commencent donnés de path
	int vis; // visibilité

	public PropiedadDeDatosPath() {
	}

	public PropiedadDeDatosPath(int k, int k_ini, int vis) {
		this.k = k;
		this.k_ini = k_ini;
		this.vis = vis;
	}

}
