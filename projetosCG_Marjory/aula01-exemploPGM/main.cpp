#include <iostream>
#include <cmath>
#include <algorithm>
#include "PGM.hpp"

using namespace std;

// Preencher uma determinada linha de uma imagem
void exerc5()
{
	PGM img;

	criar(&img, 500, 500, 0);

	setLinha(&img, 250, 255);

	gravar(&img, "saida-exerc5.pgm");
	destruir(&img);
}

// Mudar a cor de determinada região
void exerc7()
{
	PGM img;

	criar(&img, 500, 500, 0);

	setFill(&img, 200, 200, 300, 300, 255);

	gravar(&img, "saida-exerc7.pgm");
	destruir(&img);
}

// Definir linha branca a cada 50 linhas
void exerc8()
{
	PGM img;

	criar(&img, 500, 500, 0);

	for (int i = 1; i < 500; i++)
	{
		for (int j = 1; j < 500; j++)
		{
			if (i % 50 == 0)
				setLinha(&img, i, 255); // linha branca
		}
	}

	gravar(&img, "saida-exerc8.pgm");
	destruir(&img);
}

// Método para inverter a imagem verticalmente (flip)
void exerc9()
{
	PGM imgE, imgS;

	ler(&imgE, "feep.pgm");
	criar(&imgS, imgE.larg, imgE.alt, 0);

	for (int y = 0; y < imgE.alt; y++)
	{
		for (int x = 0; x < imgE.larg; x++)
		{
			unsigned char c = getPixel(&imgE, x, imgE.alt - 1 - y);
			setPixel(&imgS, x, y, c);
		}
	}

	gravar(&imgS, "saida-exerc9.pgm");

	destruir(&imgE);
	destruir(&imgS);
}

// Recortar a região de uma imagem de entrada para uma imagem de saída
void exerc10()
{
	PGM imgE, imgS;

	ler(&imgE, "numeros.pgm");
	criar(&imgS, imgE.larg, imgE.alt, 0);

	int x0 = 110, y0 = 0, x1 = 225, y1 = 164;

	for (int x = x0; x <= x1; x++)
	{
		for (int y = y0; y <= y1; y++)
		{
			unsigned char c = getPixel(&imgE, x, y);
			setPixel(&imgS, x, y, c);
		}
	}

	gravar(&imgS, "saida-exerc10.pgm");
	destruir(&imgE);
}

// Desenhar uma borda em uma imagem PGM
void exerc11()
{
	PGM img;

	ler(&img, "numeros.pgm");

	setBorda(&img, 10, 0);

	gravar(&img, "saida-exerc11.pgm");
	destruir(&img);
}

// Desenhar um X na imagem
void exerc12()
{
	PGM img;

	criar(&img, 200, 80, 255);

	unsigned char corL = 0;

	DDALine(&img, 0, 0, img.larg - 1, img.alt - 1, corL);
	DDALine(&img, 0, img.alt - 1, img.larg - 1, 0, corL);

	gravar(&img, "saida-exerc12.pgm");
	destruir(&img);
}

// Combinar duas imagens PGM

// Desenhar uma borda em uma região de uma imagem PGM
void exerc14()
{
	PGM img;

	ler(&img, "numeros_exerc14.pgm");

	int x0 = 110, y0 = 0, x1 = 225, y1 = 164;

	setBordaCoord(&img, x0, y0, x1, y1, 0);

	gravar(&img, "numeros_exerc14.pgm");
	destruir(&img);
}

// Converter os tons de cinza de uma imagem PGM
void exerc15()
{
	PGM imgE, imgS;

	ler(&imgE, "numeros.pgm");
	criar(&imgS, imgE.larg, imgE.alt, 0);

	convertTons(&imgE, &imgS);

	gravar(&imgS, "saida-exerc15.pgm");
	destruir(&imgE);
}

int main(void)
{

	/*
	//#Exemplo1#: criando uma imagem e gravando no disco
	PGM img1;
	criar(&img1, 5, 7);
	gravar(&img1, "exemplo1.pgm");
	destruir(&img1);

	//#Exemplo2#: imprimindo os atributos da imagem
	PGM img2;
	cout << "#Exemplo 2#\n";
	imprimir(&img2);
	criar(&img2, 700, 500);
	imprimir(&img2);
	gravar(&img2, "exemplo2.pgm");
	destruir(&img2);
	imprimir(&img2);

	//#Exemplo3#: ler imagem, getPixel, setPixel
	PGM img3;
	unsigned char corP;
	cout << "\n\n#Exemplo 3#\n";
	ler(&img3, "feep.pgm");

	//ler o valor do pixel de coordenadas (x=1, y=1)
	corP = getPixel(&img3, 1,1);
	cout << "A cor do pixel(1,1): " << (int) corP << endl;

	setPixel(&img3, 1, 1, 255); //alterar a cor do pixel(1,1) para branco(255)
	gravar(&img3, "exemplo3.pgm"); //gravar o resultado no disco
	destruir(&img3);
	*/

	// Chamada dos exercícios
	exerc5();
	exerc7();
	exerc8();
	exerc9();
	exerc10();
	exerc11();
	exerc12();
	exerc14();
	exerc15();

	// cout << "Pressione uma tecla para encerrar o programa.\n";
	// getchar();
	return EXIT_SUCCESS;
}