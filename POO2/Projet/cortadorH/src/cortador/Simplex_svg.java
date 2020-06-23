package cortador;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.LinkedList;
import java.util.Objects;
import java.util.Scanner;

public class Simplex_svg {
	/**
	 * Esta clase es la version java de simplexC_svg.c
	 * 
	 */
    
    static String directorio = DirectorioTrabajo.directorio;
    
	public Simplex_svg() {
	}

	public static void main(String[] args) {
	
		/*
		
		int pos, k = 0, k_ini = 0, vis, no_path, tamano_s;
		int no_leidos = 0, no_escritos = 0;
		char k_techo8, k_str8;
		*/
		String nombre_svgP = null;
		//String directorio = null;
		/*
		byte[] buffer1 = null;
		byte[] buffer = null;
		File fp = null;
		*/
		/************************ Entrada de comandos ****************************/
		System.out.println("No. d arguments: " + args.length);
	//	directorio = "/home/ivan/work/";
			if (args.length >= 2)uso();
		if (args.length == 0) {
			System.out.println("Utilisant example: drawing.svg");
			
			nombre_svgP = "drawing.svg";
			
		}
		/*
		 * String s1="Sachin "; String s2="Tendulkar"; String s3=s1.concat(s2);
		 */
		if (args.length == 1) {
			nombre_svgP = args[0];
			if (Objects.equals(nombre_svgP, "-h"))
				uso();
		}
		//nombre_svg = directorio + File.separator+nombre_svgP;
		//nom_pre =  null;
		Simplex_svg simplex_svg= new Simplex_svg();
		//nombre_svgP = "ballenasinh.svg";
		nombre_svgP=simplex_svg.trabajo(nombre_svgP);
		
	}

		
	public  String trabajo(String nombre_svgP) {
		
		
		int k = 0, k_ini = 0, vis, no_path;
		int no_leidos = 0;
		//String nombre_svgP = null;
		String nombre_svg = null;
		//String directorio = null;
		byte[] buffer1 = null;
		byte[] buffer = null;
		
		String directorio_inkscape = null;
		// DirectorioBase dbase = new DirectorioBase();
		File directorio_inkscapeD = null;

		// final File directorio_normalD = new File(directorio_normal);
		directorio_inkscape = DirectorioBase.getNombreFileFromResources("cortador"+File.separator+"objetos" + File.separator + "inkscape_svg");
	//	directorio_inkscapeD = new File(directorio_inkscape);
		//

		
		
		
		
		
		
		
		
		
		nombre_svg = directorio_inkscape + File.separator+nombre_svgP;
		

		/********************* Fin de commandes ***************************/

		/*********** Lecture d archives svg ****************************************/

		File file = new File(nombre_svg);
		if (!file.exists() || !file.isFile()) {
			System.out.println("Lecture impossible. " + nombre_svg + " Fin...");
			System.exit(0);
		}
		long result = file.length();
		//System.out.println("tamano de archivo: " + result);
		buffer1 = new byte[(int) result];
		check1(buffer1, "Impossible generer array  buffer1");

		DataInputStream data_in = null;
		try {
			data_in = new DataInputStream(new BufferedInputStream(new FileInputStream(file)));
		} catch (FileNotFoundException e) {
			aviso("Impossible generer Data stream");
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}

		try {
			no_leidos = data_in.read(buffer1);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			aviso("Impossible lire donnes de stream");
			// e.printStackTrace();
		}
		if (no_leidos != result) {
			System.out.format("taille:%d no_lus:%d%n", result, no_leidos);
			System.out.format("Archives non lus..Fin%n");
			System.exit(0);

		} else {
			System.out.format("Tous les archives ont ete lus.%n");
		}

		try {
			data_in.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			aviso("Pas pu fermer stream");
			// e.printStackTrace();
		}
		
		/*
		 * 
		 * Genere un dir ou seront les archives
		 * 	
		 * */
		//String directorio_simple= directorio+ File.separator+ "objetos"+ File.separator+ "simple_svg";
		String directorio_simple = DirectorioBase.getNombreFileFromResources("cortador"+File.separator+"objetos" + File.separator + "simple_svg");
		
		
	      java.nio.file.Path   pathD = Paths.get(directorio_simple);
	        try {
				Files.createDirectories(pathD);
			} catch (IOException e1) {
				System.out.println("J'ai pas pu creer directoire"+ pathD);
				// TODO Auto-generated catch block
				//e1.printStackTrace();
			}
		
		
		/****************** Nom d'archive de sortie ****************************/
		nombre_svg = directorio_simple +  File.separator+ "simp_ws_" + nombre_svgP;
        String nombre_svgPN= "simp_ws_" + nombre_svgP;
		//System.out.format("Nombre de archivo de salida:%s \n", nombre_svg);
		/****************** Fin de nombre de archhivo de salida ********************/

		LinkedList<PropiedadDeDatosPath> datos_de_path_last, datos_de_path_first;
		LinkedList<PropiedadDeDatosPath> datos_de_path = new LinkedList<PropiedadDeDatosPath>();

		/********************************
		 * Localization de donnees de path en archive svg
		 *****************/
		/**************************
		 * Debut de parser d archive svg
		 **************************************/

		boolean flag_path = false;
		boolean flag_d = false;
		boolean flag_comillas = false;
		boolean flag_svg = false;
		boolean flag_stroke = true;

		/******************
		 * parcours de buffer1
		 ********************************************/
		int j = 0;// lee el eof
		no_path = 0;// contendra le num de paths trouves
		while (j < no_leidos) {

			/***********
			 * Detecte el elemento: <svg
			 *************************************************/

			if ((j + 3 < (no_leidos - 1)) && ((char) buffer1[j] == '<') && ((char) buffer1[j + 1] == 's')
					&& ((char) buffer1[j + 2] == 'v') && ((char) buffer1[j + 3] == 'g')) {
				//System.out.format("encontre <svg: en posicion: %d\n", j);
				flag_svg = true;
			}
			/***************
			 * Fin de Detecte element: <svg
			 **************************************/

			/***********
			 * Detecte element: <path
			 *************************************************/
			if ((j + 4 < (no_leidos - 1)) && ((char) buffer1[j] == '<') && ((char) buffer1[j + 1] == 'p')
					&& ((char) buffer1[j + 2] == 'a') && ((char) buffer1[j + 3] == 't')
					&& ((char) buffer1[j + 4] == 'h') // detecte '<... path'
			) {
				//System.out.format("trouve <path: en posicion: %d \n", j);
				flag_path = true;
				//System.out.format("<path *********\n");
			}

			if ((j + 10 < (no_leidos - 1)) && ((char) buffer1[j] == 's') && ((char) buffer1[j + 1] == 't')
					&& ((char) buffer1[j + 2] == 'r') && ((char) buffer1[j + 3] == 'o')
					&& ((char) buffer1[j + 4] == 'k') && ((char) buffer1[j + 5] == 'e')
					&& ((char) buffer1[j + 6] == ':') 
					&& ((char) buffer1[j + 7] == 'n')
					&& ((char) buffer1[j + 8] == 'o')
					&& ((char) buffer1[j + 9] == 'n')
					&& ((char) buffer1[j + 10] == 'e')) {
				//System.out.format("encontre stroke:# en posicion: %d\n", j);
				if(flag_path == true)flag_stroke = false;
				//System.out.format("****** stroke:# *********\n");
			}
			/*************************
			 * fin
			 ************************************************************/
			/***********
			 * Detecta  elemento: stroke="none"
			 *************************************************/
			if ((j + 12 < (no_leidos - 1)) && ((char) buffer1[j] == 's') && ((char) buffer1[j + 1] == 't')
					&& ((char) buffer1[j + 2] == 'r') && ((char) buffer1[j + 3] == 'o')
					&& ((char) buffer1[j + 4] == 'k') && ((char) buffer1[j + 5] == 'e')
					&& ((char) buffer1[j + 6] == '=') 
					&& ((char) buffer1[j + 7] == '"')
					&& ((char) buffer1[j + 8] == 'n')
					&& ((char) buffer1[j + 9] == 'o')
					&& ((char) buffer1[j + 10] == 'n')
					&& ((char) buffer1[j + 11] == 'e')
					&& ((char) buffer1[j + 12] == '"')) {
				//System.out.format("encontre stroke:# en posicion: %d\n", j);
				if(flag_path == true)flag_stroke = false;
				//System.out.format("****** stroke:# *********\n");
			}
			/*************************
			 * fin
			 ************************************************************/
			/***********
			 * Detecte  element: d="
			 *************************************************/
			if (flag_path && (j + 3 < (no_leidos - 1)) && ((char) buffer1[j] == ' ') && ((char) buffer1[j + 1] == 'd')
					&& ((char) buffer1[j + 2] == '=') && ((char) buffer1[j + 3] == '"') // detecta d="
			) {
				flag_d = true;
				flag_comillas = true;
				k = 0;
				k_ini = (j + 3);
			}

			if (flag_d) {
				//System.out.format("dentro de comillas datos validos %d %c\n", j + 3, (char) buffer1[j + 3]);
				k = k + 1;
			}
			;

			if (flag_comillas && flag_path && flag_d && (j + 1 < (no_leidos - 1)) && ((char) buffer1[j] != '=')
					&& ((char) buffer1[j + 1] == '"') // encontro " final
			) {
				//System.out.format("Encontre \" en posicion %d. Termino de datos validos\n", j + 1);

				datos_de_path.add(new PropiedadDeDatosPath(k, k_ini, (flag_stroke ? 1 : 0)));

				k = 0;
				no_path++;
				flag_path = false;
				flag_comillas = false;
				flag_d = false;
				flag_stroke = true;//vuelve a plena visibilidad

			}


			j++;

		}

		/********** Verifie archive est svg ********/
		if (!flag_svg) {
			aviso("Archive n' est pas .svg");
		}
		;


		if (no_path == 0) {
			System.out.format("data path all vide\n");
		} else {

			File fileo = new File(nombre_svg);// nombre de archivo de salida con: "simp_" prepended

			DataOutputStream data_out = null;
			try {
				data_out = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(fileo)));
			} catch (FileNotFoundException e) {
				aviso("Pas pu generer data_stream");
				// TODO Auto-generated catch block
				// e.printStackTrace();
			}

			for (int i = 0; i < datos_de_path.size(); i++) {

				k = datos_de_path.get(i).k;// obtiene tamano de datos de path
				k_ini = datos_de_path.get(i).k_ini;// obtiene posicion donde comienzan datos de path
				vis = datos_de_path.get(i).vis;// obtiene condicion de presencia de stroke:#

			//	System.out.format("**************total; %d\n", k);
			//	System.out.format("**************k_ini: %d\n", k_ini);
			//	System.out.format("**************vis  : %d\n", vis);

				/***************
				 * Comienzo de transferencia a archivo de sector de datos validos
				 **************/
				/************************
				 * a buffer . se transfieren comillas
				 *****************************/
				buffer = new byte[(int) (k + 2)];
				/*
				 * revisa si encontro stroke:# y coloca 1(si) o 0(no) en buffer como primer
				 * elemento
				 */
				if (vis == 1) {
					buffer[0] = '1';
					buffer[1] = '^';
				//	System.out.format("path con #\n");
				} else {
				//	System.out.format("path sin #\n");
					buffer[0] = '0';
					buffer[1] = '^';
				}

				/****
				 * tranfiere datos validos de path en buffer1 a buffer para escribirlos en
				 * archivo
				 ******/

				for (j = 0; j < k; j++) {
					buffer[j + 2] = buffer1[k_ini + j];
				}

				try {
					data_out.write(buffer);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					aviso("J'ai pas pu lire donnes stream");
					// e.printStackTrace();
				}

				/****************
				 * Fin de transferencia de datos validos a archivo
				 ******************/
				buffer = null;// resetea buffer
			}

			try {// cierra archivo
				data_out.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				aviso("Pas pu fermer outstream");
				// e.printStackTrace();
			}
		}
		//System.out.println("Datos escritos en archivo: " + nombre_svg + "\n Hasta luego...");
		
		
		
		
		return nombre_svgPN;
		
		
	}

	private static void check1(Object p, String frase) {
		if (p == null) {
			System.out.format("%s. Fin...\n", frase);
			System.exit(0);
		}

		return;
	}

	private static void aviso(String frase) {
		System.out.println(" Fin..." + frase);
		System.exit(0);
		return;
	}

	private static void uso() {

		System.out.format("Use:\nsimplexC_svg <nombre_svg>\no\nsimplexC_svg\n");
		System.out.format("Où <nombre_svg>, est le nom de l'archive inkscape\n");
		System.exit(0);
		return;
	}

}
