#include <iostream>
#include <cmath>
#include "PGM.hpp"

using namespace std;

#include <Eigen/Dense>
using namespace Eigen;

#define _PI 3.14159265358979323846

float degree2rad(float ang)
{
	float r = ang * (float)(_PI / 180.0);

	return r;
}

Matrix3f getTranslacao(float tx, float ty)
{
	Matrix3f Tans = Matrix3f::Identity();

	Tans(0, 2) = tx;
	Tans(1, 2) = ty;

	return Tans;
}

Matrix3f getRotacao(float angulo)
{
	float rad = degree2rad(angulo);

	float s = sin(rad);
	float c = cos(rad);

	Matrix3f Rot = Matrix3f::Identity();

	Rot(0, 0) = c;
	Rot(0, 1) = -s;
	Rot(1, 0) = s;
	Rot(1, 1) = c;

	return Rot;
}

Matrix3f getEscala(float sx, float sy)
{
	Matrix3f Esc = Matrix3f::Identity();

	Esc(0, 0) = sx;
	Esc(1, 1) = sy;

	return Esc;
}

Matrix3f getCisalhamentoHor(float a)
{
	Matrix3f Cis = Matrix3f::Identity();

	Cis(0, 1) = a;

	return Cis;
}

Matrix3f getCisalhamentoVer(float b)
{
	Matrix3f Cis = Matrix3f::Identity();

	Cis(1, 0) = b;

	return Cis;
}

Matrix3f getReflexaoEixoX()
{
	Matrix3f Ref = Matrix3f::Identity();

	Ref(1, 1) = -1;

	return Ref;
}

Matrix3f getReflexaoEixoY()
{
	Matrix3f Ref = Matrix3f::Identity();

	Ref(0, 0) = -1;

	return Ref;
}

// Rotação de -30 graus em torno do ponto (6,4), ou seja, a matriz de transformação é calculada por T*R*T-1
void exercLista3f()
{
	Vector2f pontoCentro(6.0f, 4.0f);

	Matrix3f T = getTranslacao(pontoCentro.x(), pontoCentro.y());
	Matrix3f Tinv = getTranslacao(-pontoCentro.x(), -pontoCentro.y());
	Matrix3f R = getRotacao(-30.0f);

	Matrix3f M = T * R * Tinv;

	// Criando um vetor com os pontos
	vector<Vector3f> pontos;
	pontos.push_back(Vector3f(4.0f, 2.0f, 1.0f));
	pontos.push_back(Vector3f(8.0f, 2.0f, 1.0f));
	pontos.push_back(Vector3f(6.0f, 7.0f, 1.0f));

	for (int i = 0; i < pontos.size(); i++)
	{
		Vector3f p = M * pontos[i];
		cout << "Ponto " << i + 1 << ": " << p.transpose() << endl;
	}
}

void exercLista3_2()
{
	Vector2f pontoCentro(4.0f, 4.0f);

	float sx = 1.5;
	float sy = 0.5;

	float tx = -6.0;
	float ty = 0.0;

	Matrix3f T = getTranslacao(pontoCentro.x(), pontoCentro.y());
	Matrix3f Tinv = getTranslacao(-pontoCentro.x(), -pontoCentro.y());
	Matrix3f E = getEscala(sx, sy);
	Matrix3f R = getRotacao(90.0f);
	Matrix3f Tr = getTranslacao(tx, ty);

	Matrix3f Mresult = T * Tr * R * E * Tinv;

	// Criando um vetor com os pontos
	vector<Vector3f> pontos;
	pontos.push_back(Vector3f(2.0f, 2.0f, 1.0f));
	pontos.push_back(Vector3f(6.0f, 2.0f, 1.0f));
	pontos.push_back(Vector3f(6.0f, 6.0f, 1.0f));
	pontos.push_back(Vector3f(2.0f, 6.0f, 1.0f));

	for (int i = 0; i < pontos.size(); i++)
	{
		Vector3f p = Mresult * pontos[i];
		cout << "Ponto " << i + 1 << ": " << p.transpose() << endl;
	}
}

// Ler a imagem de entrada e criar a imagem de saída antes de chamar a função
void transf2D(PGM *imgE, PGM *imgS, Matrix3f M)
{
	if (imgE->larg != imgS->larg || imgE->alt != imgS->alt)
		return;

	// Percorrer a imagem de entrada
	for (size_t yE = 0; yE < imgE->alt; yE++)
	{
		for (size_t xE = 0; xE < imgE->larg; xE++)
		{
			Vector3f coordSaida = M * Vector3f(xE, yE, 1);

			float xS = round(coordSaida.x());
			float yS = round(coordSaida.y());

			if (coordValida(imgS, xS, yS))
				setPixel(imgS, xS, yS, getPixel(imgE, xE, yE));
		}
	}
}

// Usar essa função para as transformações
void transf2DInv(PGM *imgE, PGM *imgS, Matrix3f Minv)
{
	if (imgE->larg != imgS->larg || imgE->alt != imgS->alt)
		return;

	// Percorrer a imagem de saída
	for (size_t yS = 0; yS < imgS->alt; yS++)
	{
		for (size_t xS = 0; xS < imgS->larg; xS++)
		{
			Vector3f coordEntrada = Minv * Vector3f(xS, yS, 1);

			float xE = round(coordEntrada.x());
			float yE = round(coordEntrada.y());

			if (coordValida(imgE, xE, yE))
				setPixel(imgS, xS, yS, getPixel(imgE, xE, yE));
		}
	}
}

// Cisalhamento horizontal de 0.9 e reflexão em torno do eixo y
void exercLista4_1()
{
	PGM imgE, imgS;

	ler(&imgE, "numeros.pgm");
	criar(&imgS, imgE.larg, imgE.alt, 0);

	Vector2f pontoCentro((imgE.larg - 1) / 2.0, (imgE.alt - 1) / 2.0);

	Matrix3f T = getTranslacao(pontoCentro.x(), pontoCentro.y());
	Matrix3f Tinv = getTranslacao(-pontoCentro.x(), -pontoCentro.y());

	Matrix3f Cis = getCisalhamentoHor(0.9f);
	Matrix3f Ref = getReflexaoEixoY();

	Matrix3f MatR = T * Ref * Cis * Tinv;
	Matrix3f MatRinv = MatR.inverse();

	// transf2D(&imgE, &imgS, MatR);
	transf2DInv(&imgE, &imgS, MatRinv); // Usar essa função

	gravar(&imgS, "saida-exerc1.pgm");

	destruir(&imgE);
	destruir(&imgS);
}

void exercLista4_2()
{
	PGM imgE, imgS;

	ler(&imgE, "numeros.pgm");
	criar(&imgS, imgE.larg, imgE.alt, 0);

	Vector2f pontoCentro((imgE.larg - 1) / 2.0, (imgE.alt - 1) / 2.0);

	Matrix3f T = getTranslacao(pontoCentro.x(), pontoCentro.y());
	Matrix3f Tinv = getTranslacao(-pontoCentro.x(), -pontoCentro.y());

	Matrix3f Rot15 = getRotacao(15.0f);
	Matrix3f Esc = getEscala(0.5f, 0.5f);
	Matrix3f Rot20 = getRotacao(20.0f);
	Matrix3f Cis = getCisalhamentoVer(0.7f);

	Matrix3f MatR = T * Cis * Rot20 * Esc * Rot15 * Tinv;
	Matrix3f MatRinv = MatR.inverse();

	// transf2D(&imgE, &imgS, MatR);
	transf2DInv(&imgE, &imgS, MatRinv); // Usar essa função

	gravar(&imgS, "saida-exerc2.pgm");

	destruir(&imgE);
	destruir(&imgS);
}

void exercLista4_3()
{
	PGM imgE, imgS;

	ler(&imgE, "numeros.pgm");
	criar(&imgS, imgE.larg, imgE.alt, 0);

	Vector2f pontoCentro((imgE.larg - 1) / 2.0, (imgE.alt - 1) / 2.0);

	Matrix3f T = getTranslacao(pontoCentro.x(), pontoCentro.y());
	Matrix3f Tinv = getTranslacao(-pontoCentro.x(), -pontoCentro.y());
	Matrix3f R = getRotacao(45.0f);

	Matrix3f Mat = T * R * Tinv;
	Matrix3f Minv = Mat.inverse();

	transf2DInv(&imgE, &imgS, Minv);
	transf2D(&imgE, &imgS, Mat);

	gravar(&imgS, "saida-exerc3.pgm");

	destruir(&imgE);
	destruir(&imgS);
}

int main(void)
{
	setlocale(LC_ALL, "Portuguese");

	// exercLista4_1();
	// exercLista4_2();
	// exercLista4_3();

	// cout << "Pressione uma tecla para encerrar o programa.\n";
	// getchar();
	return EXIT_SUCCESS;
}

// void exemplos()
// {
// 	// pontos do triângulo em coordenadas homogeneas
// 	Vector3f pA = Vector3f(4.0f, 2.0f, 1.0f);
// 	Vector3f pB = Vector3f(8.0f, 2.0f, 1.0f);
// 	Vector3f pC = Vector3f(6.0f, 7.0f, 1.0f);

// 	// definindo uma matriz de translação
// 	Matrix3f mT = Matrix3f::Identity();
// 	mT(0, 2) = 3; // Tx
// 	mT(1, 2) = 1; // Ty

// 	// OU, usando uma funcao
// 	// Matrix3f mT =  getTranslacao(3, 1);

// 	// Matriz x ponto
// 	Vector3f pA_ = mT * pA;
// 	Vector3f pB_ = mT * pB;
// 	Vector3f pC_ = mT * pC;

// 	// imprimindo a matriz
// 	cout << "Matriz:\n";
// 	cout << endl
// 		 << mT << endl;

// 	// imprimindo os pontos
// 	cout << "Ponto A: " << pA_.transpose() << endl;
// 	cout << "Ponto B: " << pB_.transpose() << endl;
// 	cout << "Ponto C: " << pC_.transpose() << endl;

// 	// criando um vetor com os pontos
// 	vector<Vector3f> pontos;
// 	pontos.push_back(Vector3f(4.0f, 2.0f, 1.0f));
// 	pontos.push_back(Vector3f(8.0f, 2.0f, 1.0f));
// 	pontos.push_back(Vector3f(6.0f, 7.0f, 1.0f));

// 	for (int i = 0; i < pontos.size(); i++)
// 	{
// 		Vector3f p = mT * pontos[i];
// 		cout << "Ponto " << i + 1 << ": " << p.transpose() << endl;
// 	}

// 	exercLista3f();
// 	exercLista3_2();
// }