#include <iostream>
#include "PPM.hpp"

using namespace std;

void exerc3(){
	PPM img;

	criar(&img, 300, 300, RGB(255, 255, 0));
	gravar(&img, "saida-exerc3.ppm");
	destruir(&img);
}

void exerc4(){
	PPM img;

	criar(&img, 300, 300, RGB(255, 255, 0));
	setLinha(&img, 150, RGB(255, 0, 0));
	gravar(&img, "saida-exerc4.ppm");
	destruir(&img);
}

void exerc6(){
	PPM img;

	criar(&img, 300, 300, RGB(255, 255, 0));

	int x0 = 100, y0 = 10, x1 = 225, y1 = 164;
	setBordaRGB(&img, x0, y0, x1, y1, RGB(255, 0, 0));

	gravar(&img, "saida-exerc6.ppm");
	destruir(&img);
	
}

void exerc7(){
	PPM img;

	criar(&img, 500, 500, RGB(0, 0, 0));

	corAleatoria(&img);
	
	gravar(&img, "saida-exerc7.ppm");
	destruir(&img);
}

void exerc8(){
	PPM imgE, imgS;

	ler(&imgE, "numeros.ppm");
	criar(&imgS, imgE.larg, imgE.alt, RGB(0, 0, 0));

	int x0 = 195, y0 = 310, x1 = 380, y1 = 570;

	setRecorteRGB(&imgE, &imgS, x0, y0, x1, y1);

	gravar(&imgS, "saida-exerc8.ppm");
	destruir(&imgE);
	destruir(&imgS);
}

void exerc10(){
	PPM imgE, imgS;

	ler(&imgE, "numeros.ppm");
	criar(&imgS, imgE.larg, imgE.alt, RGB(0, 0, 0));

	setFlipHorizontal(&imgE, &imgS);

	gravar(&imgS, "saida-exerc10.ppm");
	destruir(&imgE);
	destruir(&imgS);
}

void exerc11(){
	PPM img;

	ler(&img, "numeros-exerc11.ppm");

	int x0 = 391, y0 = 327, x1 = 574, y1 = 575;
	setBordaEspessuraRGB(&img, x0, y0, x1, y1, 10, RGB(255, 0, 0));

	gravar(&img, "numeros-exerc11.ppm");
	
	destruir(&img);
}

int main(void)
{

	/*
	//#Exemplo1#: criando uma imagem e gravando no disco
	PPM img1;
	criar(&img1, 5, 7, RGB(255, 255, 0));
	gravar(&img1, "exemplo1.ppm");
	destruir(&img1);

	//#Exemplo2#: imprimindo os atributos da imagem 
	PPM img2;
	cout << "#Exemplo 2#\n";
	imprimir(&img2);
	criar(&img2, 700, 500, RGB(255, 255, 0));
	imprimir(&img2);
	gravar(&img2, "exemplo2.ppm");
	destruir(&img2);
	imprimir(&img2);

	//#Exemplo3#: ler imagem, getPixel, setPixel 
	PPM img3;
	RGB corP;
	cout << "\n\n#Exemplo 3#\n";
	ler(&img3, "exemploPPM.ppm");

	//ler o valor do pixel de coordenadas (x=1, y=1)
	corP = getPixel(&img3, 0,0);
	cout << "A cor do pixel(0,0): [" << corP << "] " << endl;

	setPixel(&img3, 1, 0, RGB(0, 128, 128)); //alterar a cor do pixel(1, 0) para RGB(0, 128, 128)
	setPixel(&img3, 2, 0, RGB(255, 0, 255)); //alterar a cor do pixel(2, 0) para rosa
	setPixel(&img3, 2, 4, RGB(128, 0, 128)); //alterar a cor do pixel(2, 4) para roxo
	gravar(&img3, "exemplo3.ppm"); //gravar o resultado no disco
	destruir(&img3);
	*/

	//exerc3();
	//exerc4();
	// exerc6();
	// exerc7();
	// exerc8();
	
	exerc10();
	exerc11();
	
	// cout << "Pressione uma tecla para encerrar o programa.\n";
	// getchar();
	return EXIT_SUCCESS; 
}