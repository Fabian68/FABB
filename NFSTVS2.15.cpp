#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
//#include <time.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int const NBJoueurs=40;// Nombre de joueurs 
int const LVLEXP=10000;// Niveau max pour un personnage
vector<string> Personnage(NBJoueurs);
vector<int>	QuiJoue;
int const NBZone=7;
int ZoneMax;// La zone maximum débloquer
int NiveauMax;//Le niveau max débloquer de la dernière zone

long long int TabXP[LVLEXP];
long long int ExperiencesPersonnages[NBJoueurs];
int PersoCarac[NBJoueurs][32];

int Equipe[2][5];
int Tour;

///TEAM//
int const TEAM1=0;
int const TEAM2=1;

///Perso///
int const FABIAN =0;
int const THOMAS =1;
int const CLOE =2;
int const MAELLE =3;
int const NICOLAS =4;
int const JB =5;
int const SEBASTIEN =6;
int const FLO=7;
int const BRYAN=8;
int const SALIM=9;
int const VICTOR = 10;
int const ISIDORE = 11;
int const DEMO = 12;
int const S1 = 30;
int const S2 = 31;
int const S3 = 32;
int const S4 = 33;
int const S5 = 34;

///Carac//
int const LVL=0;
int const STATUT=1;
int const FORCE=2;
int const VITALITE=3;
int const AGILITE=4;
int const VIE=5;
int const EQUIPE=6;
int const MANA=7;
int const ARME=8;
int const CHANCECRITIQUE=9;
int const DEGATCRITIQUE=10;
int const CHANCEDOUBLEATTAQUE=11;
int const HABILETE=12;
int const SOINS=13;
int const SUBIS=14;
int const DEGATS=15;
int const DEVIATION=16;
int const Difficulte=17;
int const REDUCTION=18;
int const ORBEVIE1=19;
int const ORBEVIE2=20;
int const ORBEVIE3=21;
int const ORBEATTAQUE1=22;
int const ORBEATTAQUE2=23;
int const ORBEATTAQUE3=24;
int const ORBEVITESSE1=25;
int const ORBEVITESSE2=26;
int const ORBEVITESSE3=27;
int const ANIMAL = 28;
int const BLOCAGE = 29;
int const RICOCHET = 30;
int const ESQUIVE = 31;

///Types d'arme////
int const ISIDOOR=0;
int const SPARTAN=1;
int const BATON=2;
int const VENTRE=3;
int const ALACOOL=4;
int const TRUGDOR=5;
int const DAGUES=6;
int const Bots=7;
int const NINI=8;
int const JBI=9;
int const LAPIN=10;
int const SANGLIER=11;
int const CERF=12;
int const PETITPONEY=13;
int const ASALIM=14;
int const ADRAGON=15;
int const KUNGFU = 16;
int const TELLURIQUE = 17;
int const AMAELLE = 18;
int const ADEMO = 19;
int const ELITE = 20;
int const GROGNARD = 21;
int const CHASSEUR = 22;
int const HUNTER = 23;
int const BRUTE = 24;
int const SQUELETEARCHER = 25;
int const CREEPER = 26;
int const GHAST = 27;
int const ZOMBIE = 28;
int const WITHERSQUELETTE = 29;
int const WITHER = 30;

//Les 2 Statuts
int const EnVie=-1;
int const KO=-2;

//Positions
int const PREMIER=0;
int const DEUXIEME=1;
int const TROISIEME=2;
int const QUATRIEME=3;
int const CINQUIEME=4;

//couleur
int const ROUGE=12;
int const VERT=10;
int const NORMAL=15;
int const JAUNE=14;
int const VIOLET=13;

//
int const OFFENSIF = 0;
int const DEFENSIF = 1;

void Colorier(int couleur) {
	SetConsoleTextAttribute(h, couleur);
}

string NombreAvecEspaceMillier(int Nombre) {
	long long int NombreAfficher = Nombre;
	string MotAfficher;
	string Part1;
	string Part2;
	string str1;
	string str2;
	if (NombreAfficher < 1000) {
		  MotAfficher=to_string(NombreAfficher);
	}
	else if (NombreAfficher >= 1000000) {
		MotAfficher = to_string((NombreAfficher / 1000000) % 1000) + ",";
		Part1= (to_string((NombreAfficher / 1000) % 1000));
		while (Part1.size() < 3) {
			Part1 = '0' + Part1;
		}
		 Part2=to_string(NombreAfficher % 1000);
		 while (Part2.size() < 3) {
			 Part2 = '0' + Part2;
		 }
		 MotAfficher=MotAfficher + Part1 +","+ Part2;
	}
	else if (NombreAfficher >= 1000) {
		MotAfficher = to_string((NombreAfficher / 1000) % 1000) + ",";
		Part2=to_string(NombreAfficher % 1000)+Part2;
		while (Part2.size() < 3) {
			Part2 = '0' + Part2;
		}
		MotAfficher= MotAfficher +Part2;
	}
	return MotAfficher;
}
//Init de QuiJoue
void InitQuiJoue(){
	long long int somme = 0;
	for(int i=PREMIER;i<=CINQUIEME;i++) {
		somme+=PersoCarac[Equipe[TEAM1][i]][AGILITE];
		somme+=PersoCarac[Equipe[TEAM2][i]][AGILITE];
	}
	int Ratio[10];
	for(int i=0;i<=4;i++) {
		Ratio[i]=static_cast<int>(PersoCarac[Equipe[TEAM1][i]][AGILITE]/(1.0*somme/12));
		Ratio[i+5]=static_cast<int>(PersoCarac[Equipe[TEAM2][i]][AGILITE]/(1.0*somme/12));
	}

  for(double i=0.9;i>-0.1;i=i-0.1) {
  	for(int j=0;j<=4;j++) {
  		if(Ratio[j]>=i) {
  			QuiJoue.push_back(Equipe[TEAM1][j]);
		  }
		if(Ratio[j+5]>=i) {
  			QuiJoue.push_back(Equipe[TEAM2][j]);
		  }
	  }

  }
}

bool chargerEXP( const string& fichier)
{
  ifstream is(fichier);
  if (!is)
  {
    cerr<<"Erreur ouverture fichier"<<endl;
    return false;
  }

  int i=0;
  // lecture tantque possible
  while (!is.eof())
  {
 	is>>ExperiencesPersonnages[i];
 	i++;
  }
  is.close();
  return true;
}

bool ecrireEXP( const string& fichier)
{
  ofstream os(fichier);

  int i=0;
  // lecture tantque possible
  while (i!=NBJoueurs)
  {
 	os<<ExperiencesPersonnages[i]<<endl;
 	i++;
  }
  os.close();
  return true;
}

bool recupZone( const string& fichier)
{
  ifstream is(fichier);
  if (!is)
  {
    cerr<<"Erreur ouverture fichier"<<endl;
    return false;
  }
  is>>ZoneMax>>NiveauMax;
  is.close();
  return true;
}

bool chargerZone( const string& fichier)
{
  ofstream os(fichier);
  if (!os)
  {
    cerr<<"Erreur ouverture fichier"<<endl;
    return false;
  }
  os<<ZoneMax<<" "<<NiveauMax;
  os.close();
  return true;
}

bool chargerOrbes( const string& fichier)
{
  ofstream os(fichier);
  if (!os)
  {
    cerr<<"Erreur ouverture fichier"<<endl;
    return false;
  }
  for(int i=0;i<=12;i++) {
  	for(int j = ORBEVIE1;j<=ORBEVITESSE3;j++) {
  		os<<PersoCarac[i][j]<<" ";
	  }
  	os<<endl;
  }
  os.close();
  return true;
}

bool recupOrbes( const string& fichier)
{
  ifstream is(fichier);
  if (!is)
  {
    cerr<<"Erreur ouverture fichier"<<endl;
    return false;
  }
  for(int i=0;i<=12;i++) {
  	for(int j = ORBEVIE1;j<=ORBEVITESSE3;j++) {
  		is>>PersoCarac[i][j];
	  }

  }
  is.close();
  return true;
}

void AjouterStatistiques(int STATS , int montant , int Joueur) {
	PersoCarac[Joueur][STATS]+=montant;
}

void LireQuiJoue() {
	for(size_t i=0;i<QuiJoue.size();i++) {
		cout<<QuiJoue[i]<<endl;
	}
}

void InitJoueursEnVie(int NombreJoueurs) {
	for(int JOUEUR=0;JOUEUR<NombreJoueurs;JOUEUR++) {
		PersoCarac[JOUEUR][STATUT]=EnVie;
	}
}

void InitVieJoueurs(int NombreJoueurs) {
	for(int JOUEUR=0;JOUEUR<NombreJoueurs;JOUEUR++) {
		PersoCarac[JOUEUR][VIE]=PersoCarac[JOUEUR][VITALITE]*10;
	}
}

bool EstEnVie(int Joueur){
	bool t;
	if(PersoCarac[Joueur][VIE]<=0){
		PersoCarac[Joueur][VIE]=0;
		PersoCarac[Joueur][STATUT]=KO;
		t=false;

	}
	else {
		t=true;
	}
	return t;
}

void AfficherPosition(int position) {
	cout<<endl;
	if(PersoCarac[Equipe[TEAM1][position]][STATUT]==EnVie) {
		cout<<Personnage[Equipe[TEAM1][position]]<<" ("<<NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM1][position]][LVL])<<")" <<"\t:";Colorier(VERT);cout<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM1][position]][VIE]);Colorier(NORMAL);cout<<"\\";Colorier(VERT);cout<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM1][position]][VITALITE]*10)<<"\t        ";
		Colorier(NORMAL);
	}
	else {
		Colorier(ROUGE);
		cout<<Personnage[Equipe[TEAM1][position]]<< " (" << NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM1][position]][LVL]) << ")" <<"\t:"<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM1][position]][VIE])<<"\\"<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM1][position]][VITALITE]*10)<<"\t        ";
		Colorier(NORMAL);
	}
	if(PersoCarac[Equipe[TEAM2][position]][STATUT]==EnVie) {
		cout<<Personnage[Equipe[TEAM2][position]]<< " (" << NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM2][position]][LVL]) << ")" <<"\t:";Colorier(VERT);cout<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM2][position]][VIE]);Colorier(NORMAL);cout<<"\\";Colorier(VERT);cout<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM2][position]][VITALITE]*10)<<"\t        ";
		Colorier(NORMAL);
	}
	else {
		Colorier(ROUGE);
		cout<<Personnage[Equipe[TEAM2][position]]<< " (" << NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM2][position]][LVL]) << ")" <<"\t:"<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM2][position]][VIE])<<"\\"<< NombreAvecEspaceMillier(PersoCarac[Equipe[TEAM2][position]][VITALITE]*10)<<"\t        ";
		Colorier(NORMAL);
	}
	cout<<endl;
}

void AffichageEquipe() {
	cout<<endl;
	AfficherPosition(PREMIER);
	AfficherPosition(DEUXIEME);
	AfficherPosition(TROISIEME);
	AfficherPosition(QUATRIEME);
	AfficherPosition(CINQUIEME);
	cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
}

bool EquipeEnVie(int NumeroTeam) {
	return (PersoCarac[Equipe[NumeroTeam][PREMIER]][STATUT]==EnVie||PersoCarac[Equipe[NumeroTeam][DEUXIEME]][STATUT]==EnVie||PersoCarac[Equipe[NumeroTeam][TROISIEME]][STATUT]==EnVie||PersoCarac[Equipe[NumeroTeam][QUATRIEME]][STATUT]==EnVie||PersoCarac[Equipe[NumeroTeam][CINQUIEME]][STATUT]==EnVie);
}

int rand_a_b(int a,int b ){
	return rand()%(b-a)+a;
}

double frand_a_b(double a,double b){
	return (rand()/(double)RAND_MAX)*(b-a)+a;
}

void LootOrbes(int J) {
	int choix=rand_a_b(1,1000001);
	int d=rand_a_b(1,4);
	if(choix<10000) {
		
		if(d==1&& PersoCarac[J][ORBEVIE1] != 1) {
			PersoCarac[J][ORBEVIE1]=1;
			cout << endl << Personnage[J] << " a loot une orbe de vie de niveau "; Colorier(VERT); cout << "commun." << endl; Colorier(NORMAL);
		}
		else if(d==2&& PersoCarac[J][ORBEATTAQUE1] != 1) {
			PersoCarac[J][ORBEATTAQUE1]=1;
			cout << endl << Personnage[J] << " a loot une orbe d'attaque de niveau "; Colorier(VERT); cout << "commun." << endl; Colorier(NORMAL);
		}
		else if(d==3&& PersoCarac[J][ORBEVITESSE1] != 1) {
			PersoCarac[J][ORBEVITESSE1]=1;
			cout << endl << Personnage[J] << " a loot une orbe de vitesse de niveau "; Colorier(VERT); cout << "commun." << endl; Colorier(NORMAL);
		}
	}
	if(choix<100) {
		
		if(d==1&&PersoCarac[J][ORBEVIE2] != 3) {
			PersoCarac[J][ORBEVIE2]=3;
			cout << endl << Personnage[J] << " a loot une orbe de vie de niveau "; Colorier(ROUGE); cout << "RARE !" << endl; Colorier(NORMAL);
		}
		else if(d==2&& PersoCarac[J][ORBEATTAQUE2] != 2) {
			PersoCarac[J][ORBEATTAQUE2]=2;
			cout << endl << Personnage[J] << " a loot une orbe d'attaque de niveau "; Colorier(ROUGE); cout << "RARE !" << endl; Colorier(NORMAL);
		}
		else if(d==3&& PersoCarac[J][ORBEVITESSE2] != 2) {
			PersoCarac[J][ORBEVITESSE2]=2;
			cout << endl << Personnage[J] << " a loot une orbe de vitesse de niveau "; Colorier(ROUGE); cout << "RARE !" << endl; Colorier(NORMAL);
		}
	}
	if(choix<=2) {
		
		if(d==1&& PersoCarac[J][ORBEVIE3] != 6) {
			PersoCarac[J][ORBEVIE3]=6;
			cout << endl << Personnage[J] << " a loot une orbe de vie de niveau "; Colorier(JAUNE); cout << "LEGENDAIRE INCOMMENSURABLE !!!" << endl; Colorier(NORMAL);
		}
		else if(d==2&& PersoCarac[J][ORBEATTAQUE3] != 3) {
			PersoCarac[J][ORBEATTAQUE3]=3;
			cout << endl << Personnage[J] << " a loot une orbe d'attaque de  niveau "; Colorier(JAUNE); cout << "LEGENDAIRE INCOMMENSURABLE !!!" << endl; Colorier(NORMAL);
		}
		else if(d==3&& PersoCarac[J][ORBEVITESSE3] != 3) {
			PersoCarac[J][ORBEVITESSE3]=3;
			cout << endl << Personnage[J] << " a loot une orbe de vitesse de  niveau "; Colorier(JAUNE); cout << "LEGENDAIRE INCOMMENSURABLE !!!" << endl; Colorier(NORMAL);
		}
		Sleep(360000);
	}
}

bool ecrireRDM( const string& fichier)
{
  ofstream os(fichier);

  int i=0;
  // lecture tantque possible
  while (i!=CINQUIEME+1)
  {
 	os<<rand_a_b(0,13)<<endl;
 	i++;
  }
  os.close();
  return true;
}

bool tiragePersoCarac(int joueur,int carac) {
	int T= rand_a_b(0,101);
	return(T<=PersoCarac[joueur][carac]);
}

int CibleAlea(int Joueur) {
	int J = rand_a_b(PREMIER, CINQUIEME + 1);
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM2;
	}
	else {
		TeamTMP = TEAM1;
	}
	if (EquipeEnVie(TEAM1) == true&& EquipeEnVie(TEAM2)) {
		while (PersoCarac[Equipe[TeamTMP][J]][STATUT] != EnVie) {
			J = rand_a_b(PREMIER, CINQUIEME + 1);
		}
		return Equipe[TeamTMP][J];
	}
	return 0;
}

bool soinsPossible(int team, int position) {
	return (PersoCarac[Equipe[team][position]][STATUT] == EnVie && PersoCarac[Equipe[team][position]][VIE] < PersoCarac[Equipe[team][position]][VITALITE] * 20);
}

void Soins(int team, int position, int soins, int joueur) {
	bool test=true;
	
	if (soinsPossible(team, position)) {
		cout << endl;
		if (tiragePersoCarac(joueur, CHANCECRITIQUE)) {
			soins = static_cast<int>(ceil(soins*(1 + PersoCarac[joueur][DEGATCRITIQUE] / 100.0)));
			Colorier(VIOLET);
			cout << " CRITIQUE , ";
			Colorier(NORMAL);
		}
		if (tiragePersoCarac(joueur, HABILETE)) {
			soins *= 2;
			Colorier(JAUNE);
			cout << " HABILE , ";
			Colorier(NORMAL);
		}
		if (soins < 0) {
			soins = 0;
		}
		
		PersoCarac[Equipe[team][position]][VIE] += soins;
		if (PersoCarac[Equipe[team][position]][VIE] > PersoCarac[Equipe[team][position]][VITALITE] * 20) {
			PersoCarac[Equipe[team][position]][VIE] = PersoCarac[Equipe[team][position]][VITALITE] * 20;
		}
		else {
			AjouterStatistiques(SOINS, soins, joueur);
		}
		cout << Personnage[Equipe[team][position]] << " recupere "; Colorier(VERT); cout << NombreAvecEspaceMillier(soins) << " vies ." << endl;
		Colorier(NORMAL);
		Sleep(300);
	}
	cout << endl;
}

int PositionJoueur(int Joueur) {
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	int i = 0;
	while (Equipe[TeamTMP][i] != Joueur) {
		i++;
	}
	return i;
}

int TeamEnnemie(int Joueur) {
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		return TEAM2;
	}
	else {
		return TEAM1;
	}
}

int TeamJoueur(int Joueur) {
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		return TEAM1;
	}
	else {
		return TEAM2;
	}
}

int CibleProche(int Joueur) {
	int J = PREMIER;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM2;
	}
	else {
		TeamTMP = TEAM1;
	}
	while (PersoCarac[Equipe[TeamTMP][J]][STATUT] != EnVie) {
		J++;
	}
	return Equipe[TeamTMP][J];
}

bool AttaquePossible(int JoueurDefenseur) {
	if (PersoCarac[JoueurDefenseur][STATUT] == EnVie) {
		if (tiragePersoCarac(JoueurDefenseur, ESQUIVE)) {
			Colorier(JAUNE);
			cout << " ESQUIVER ";
			Colorier(NORMAL);
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

void Attaque(int Degat,int Defenseur,int Attaquant) {
	if (AttaquePossible(Defenseur)) {
		cout << endl;
		int Degats;
		int TeamTMP = TeamEnnemie(Attaquant);
		if (tiragePersoCarac(Attaquant, CHANCECRITIQUE)) {
			Degat = static_cast<int>(ceil(Degat*(1 + PersoCarac[Attaquant][DEGATCRITIQUE] / 100.0)));
			Colorier(VIOLET);
			cout << " COUP CRITIQUE , ";
			Colorier(NORMAL);
		}
		if (tiragePersoCarac(Attaquant, HABILETE)) {
			Degat *= 2;
			Colorier(JAUNE);
			cout << " COUP HABILE , ";
			Colorier(NORMAL);
		}
		if (tiragePersoCarac(Defenseur, BLOCAGE)) {
			Degat /= 2;
			Colorier(VERT);
			cout << " BLOQUER , ";
			Colorier(NORMAL);
		}
		Degat = static_cast<int>(Degat*(1 - PersoCarac[Defenseur][REDUCTION] / 100.0));
		if (Degat < 0) {
			Degat = 0;
		}
		if (tiragePersoCarac(Defenseur, DEVIATION)) {
			Colorier(VIOLET);
			cout <<" "<< Personnage[Defenseur] << " DEVIE l'attaque ! ";
			Colorier(NORMAL);
			Attaque(Degat, CibleAlea(Defenseur), Defenseur);
		}
		else {


			PersoCarac[Defenseur][VIE] -= Degat;
			AjouterStatistiques(DEGATS, Degat, Attaquant);
			AjouterStatistiques(SUBIS, Degat, Defenseur);
			cout << Personnage[Defenseur] << " recois "; Colorier(ROUGE); cout << NombreAvecEspaceMillier(Degat); Colorier(NORMAL); cout << " degats . " << endl;
			Colorier(NORMAL);
			Sleep(300);
			if (rand_a_b(0, 101) < 33 && PersoCarac[Defenseur][ANIMAL] == DEFENSIF) {
				cout << endl << "L animal de " << Personnage[Defenseur] << " le soigne ! " << endl;
				Degats = static_cast<int>(ceil(frand_a_b(0.18, 0.36)*PersoCarac[Defenseur][FORCE]));
				Soins(TeamJoueur(Defenseur), PositionJoueur(Defenseur), Degats, Defenseur);
				Sleep(300);
			}
			if (!EstEnVie(Defenseur)) {
				cout << endl;
				cout << Personnage[Defenseur] << " a ete mis KO ! " << endl;
				AjouterStatistiques(DEGATS, -Degat, Attaquant);
				AjouterStatistiques(SUBIS, -Degat, Defenseur);
			}
			else if (rand_a_b(0, 101) < 20 && PersoCarac[Attaquant][ANIMAL] == OFFENSIF) {
				if (AttaquePossible(CibleProche(Attaquant))) {
					cout << endl << "L animal de " << Personnage[Attaquant] << " attaque ! " << endl;
					Degats = static_cast<int>(ceil(frand_a_b(0.125, 1.25)*PersoCarac[Attaquant][FORCE]));
					Attaque(Degats, CibleAlea(Attaquant), Attaquant);
					Sleep(300);
				}

			}
			if (tiragePersoCarac(Attaquant, RICOCHET)) {
				Colorier(VIOLET);
				cout<< "  RICOCHE ! ";
				Colorier(NORMAL);
				Attaque(Degat, CibleAlea(Attaquant),Attaquant);
			}
			cout << endl;
		}
	}
}

void InitMana(int NombreJoueurs) {
	for(int JOUEUR=0;JOUEUR<NombreJoueurs;JOUEUR++) {
		PersoCarac[JOUEUR][MANA]=0;
	}
}

int CibleLoin(int Joueur){
	int J=CINQUIEME;
	int TeamTMP= TeamEnnemie(Joueur);;
	while(PersoCarac[Equipe[TeamTMP][J]][STATUT]!=EnVie) {
		J--;
	}
	return Equipe[TeamTMP][J];
}

int CibleFaible(int Joueur) {
	int J=PREMIER;
	int i=J;
	int TeamTMP= TeamEnnemie(Joueur);
	long long int Vie;
	while(PersoCarac[Equipe[TeamTMP][J]][STATUT]!=EnVie) {
		J++;
	}
	Vie=PersoCarac[Equipe[TeamTMP][J]][VIE];
	i=J;
	while(J!=CINQUIEME) {
		J++;
		if(PersoCarac[Equipe[TeamTMP][J]][STATUT]==EnVie&&PersoCarac[Equipe[TeamTMP][J]][VIE]<Vie) {
			i=J;
			Vie = PersoCarac[Equipe[TeamTMP][J]][VIE];
		}

	}
	return Equipe[TeamTMP][i];
}

void AttaquerISIDORE(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int Cible;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	int soins;
	switch(choix) {
		case 0:
			cout<<Personnage[Joueur]<<" dit bonjour ! "<<endl;
			
			Cible = CibleAlea(Joueur);
			DEGATS = static_cast<int>(ceil(frand_a_b(0.001,0.01)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,Cible,Joueur);

			if(tiragePersoCarac(Joueur,HABILETE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout << Personnage[Joueur] << "saute sur " << Personnage[Cible] << " et le fait tomber !" <<endl;

				DEGATS = static_cast<int>(ceil(frand_a_b(3.0,6.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Cible,Joueur);
				PersoCarac[Joueur][MANA]++;
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" ganbade ! "<<endl;
			for (double i = 0; i < 1.0; i += 0.01) {
				if(tiragePersoCarac(Joueur, HABILETE)) {
					soins = static_cast<int>(frand_a_b(i/10.0, i/10.0 + 0.01)*(PersoCarac[Joueur][FORCE]*1.0));
					Soins(TeamTMP, PositionJoueur(Joueur), soins, Joueur);
				}
			}
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" chouine ! "<<endl;
			Sleep(1000);
			cout << Personnage[Joueur] << " tes chiant ! " << endl;
			Sleep(1000);
			cout << Personnage[Joueur] << " tu va la fermer ! " << endl;
			Sleep(1000);
			cout << Personnage[Joueur] << " EHH ! " << endl;

			for (int i = PREMIER; i <= CINQUIEME; i++) {
				PersoCarac[Equipe[TeamEnnemie(Joueur)][i]][REDUCTION] = PersoCarac[TeamEnnemie(Joueur)][REDUCTION] - 1;
			}
			cout << " Les ennemis sont moins resistants ! " << endl;
			PersoCarac[Joueur][MANA]-=2;
			break;
		case 3:
			Cible = CibleAlea(Joueur);
			cout << Personnage[Joueur] << " essaie d'enculer " << Personnage[Cible] << endl;
			PersoCarac[Cible][REDUCTION] = PersoCarac[Cible][REDUCTION] - 20;
			soins = static_cast<int>(ceil(frand_a_b(1,5)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP, PositionJoueur(Joueur), soins, Joueur);
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerSPARTAN(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	double inc=0;
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" attaque a la mitrailette ! "<<endl;

			for(int i=0;i<11&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++,inc+=0.01) {

				DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2+inc)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					cout<<" DOUBLE ATTAQUE ! "<<endl;
					DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2+inc)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,CibleProche(Joueur),Joueur);
					inc += 0.01;
				}
			PersoCarac[Joueur][MANA]++;
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) {
					cout<<" DOUBLE ATTAQUE ! "<<endl;

				for(int i=0;i<11&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++, inc += 0.01) {
					DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2+inc)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,CibleProche(Joueur),Joueur);
					
						if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
							cout<<endl<<" DOUBLE ATTAQUE ! "<<endl;
							DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2+inc)*PersoCarac[Joueur][FORCE]));
							Attaque(DEGATS,CibleProche(Joueur),Joueur);
							inc += 0.01;	
						}
					PersoCarac[Joueur][MANA]++;
					}
			}
			PersoCarac[CibleProche(Joueur)][REDUCTION] = PersoCarac[CibleProche(Joueur)][REDUCTION] - 1;
			inc = 0;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" cible une personne avec son gun ! "<<endl;

			DEGATS = static_cast<int>(ceil(frand_a_b(1.314,3.143)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" vise la teteu ! "<<endl;

				DEGATS = static_cast<int>(ceil(frand_a_b(1.614,3.443)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleFaible(Joueur),Joueur);
			}
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" fais un coup d'epee  ! "<<endl;

			DEGATS = static_cast<int>(ceil(frand_a_b(3.0,5.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" deuxieme coup d'epee ! "<<endl;

				DEGATS = static_cast<int>(ceil(frand_a_b(1.25,3.25)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
			}
			PersoCarac[Joueur][MANA]-=2;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" BAZOOKA ! "<<endl;

			
				DEGATS = static_cast<int>(ceil(frand_a_b(0.75,1.25)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
			
			
			
				DEGATS = static_cast<int>(ceil(frand_a_b(1.5,2.5)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
		
		
				DEGATS = static_cast<int>(ceil(frand_a_b(3.0,5.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
		
			
				DEGATS = static_cast<int>(ceil(frand_a_b(1.5,2.5)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
		
			
				DEGATS = static_cast<int>(ceil(frand_a_b(0.75,1.25)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
		
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" seconde explosion ! "<<endl;
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.25,0.75)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
			
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.5,1.0)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
				
				
					DEGATS = static_cast<int>(ceil(frand_a_b(0.75,1.25)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
			
				
					DEGATS = static_cast<int>(ceil(frand_a_b(0.5,1.0)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
				
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.25,0.75)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
				
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerBATON(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM1;
	}
	else {
		 TeamTMP=TEAM2;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" petit sort ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.6,0.9)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			for(int i = PREMIER;i<=CINQUIEME;i++) {
			soins = static_cast<int>(ceil(frand_a_b(0.10,0.20)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,i,soins,Joueur);
			}
			PersoCarac[Joueur][MANA]++;
		if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" DOUBLE petit sort ! "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.7,0.9)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
				for(int i = PREMIER;i<=CINQUIEME;i++) {
					soins = static_cast<int>(ceil(frand_a_b(0.10,0.20)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,i,soins,Joueur);
				}
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
				if(tiragePersoCarac(Joueur,HABILETE)) {
					int K=CibleAlea(Joueur);
					cout<<endl<<Personnage[Joueur]<<"Fais un gros calin a "<<Personnage[K]<<endl;
					PersoCarac[K][REDUCTION]= PersoCarac[K][REDUCTION]- 6;
					
				}
				else {
					int K=CibleAlea(Joueur);
					cout<<endl<<Personnage[Joueur]<<"Fais un petit calin a "<<Personnage[K]<<endl;
					PersoCarac[K][REDUCTION] = PersoCarac[K][REDUCTION] - 3;
				}
			PersoCarac[Joueur][MANA]++;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" Gros Soins  ! "<<endl;

				soins = static_cast<int>(ceil(frand_a_b(0.20,0.40)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PREMIER,soins,Joueur);
				soins = static_cast<int>(ceil(frand_a_b(0.30,0.50)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,DEUXIEME,soins,Joueur);
				soins = static_cast<int>(ceil(frand_a_b(0.40,0.60)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,TROISIEME,soins,Joueur);
				soins = static_cast<int>(ceil(frand_a_b(0.30,0.50)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,QUATRIEME,soins,Joueur);
				soins = static_cast<int>(ceil(frand_a_b(0.20,0.40)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,CINQUIEME,soins,Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) {
					cout<<" DOUBLE GROS SOINS ! "<<endl;

					soins = static_cast<int>(ceil(frand_a_b(0.10,0.20)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,PREMIER,soins,Joueur);
					soins = static_cast<int>(ceil(frand_a_b(0.20,0.40)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,DEUXIEME,soins,Joueur);
					soins = static_cast<int>(ceil(frand_a_b(0.40,0.80)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,TROISIEME,soins,Joueur);
					soins = static_cast<int>(ceil(frand_a_b(0.20,0.40)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,QUATRIEME,soins,Joueur);
					soins = static_cast<int>(ceil(frand_a_b(0.10,0.20)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,CINQUIEME,soins,Joueur);
				}
			PersoCarac[Joueur][MANA]-=2;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" sort sa tablette et commande une ogive nucleaire ! "<<endl;

			
				DEGATS = static_cast<int>(ceil(frand_a_b(0.5,1.5)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
			
		
				DEGATS = static_cast<int>(ceil(frand_a_b(1.0,2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
			
		
				DEGATS = static_cast<int>(ceil(frand_a_b(1.5,2.5)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
			
		
				DEGATS = static_cast<int>(ceil(frand_a_b(1.0,2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
		
			
				DEGATS = static_cast<int>(ceil(frand_a_b(0.5,1.5)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
		
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" fin de tempete ! "<<endl;

				
					DEGATS = static_cast<int>(ceil(frand_a_b(0.5,0.75)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
			
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.75,1.25)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
				
			
					DEGATS = static_cast<int>(ceil(frand_a_b(1.0,1.75)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
				
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.75,1.25)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
			
				
					DEGATS = static_cast<int>(ceil(frand_a_b(0.5,0.75)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
				
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerMaelle(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	double inc = 0.2;
	int Cible;
	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " Les milles points de maelle ! " << endl;
		Cible = CibleAlea(Joueur);
		for (int i = 0; i < 5 && EquipeEnVie(TeamEnnemie(Joueur)) == true; i++) {
			if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && PersoCarac[Cible][STATUT] == EnVie && PersoCarac[Joueur][STATUT] == EnVie) {
				DEGATS = static_cast<int>(ceil(frand_a_b(0.3 + inc, 0.5 + inc)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, Cible, Joueur);

				DEGATS = static_cast<int>(ceil(frand_a_b(inc-0.2, inc)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, Joueur, Joueur);
				PersoCarac[CibleProche(Joueur)][REDUCTION] = PersoCarac[Cible][REDUCTION] - 1;
				inc += 0.2;
			}
		}
		PersoCarac[Joueur][MANA]++;
		inc = 0;
		break;
	case 1:
		cout << Personnage[Joueur] << " Se tappe la tete contre le sol ! " << endl;

		DEGATS = static_cast<int>(ceil(frand_a_b(0.33, 3.33)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Joueur, Joueur);
		for (int i = 0; i < 3 && EquipeEnVie(TeamEnnemie(Joueur)) == true; i++) {
			if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && PersoCarac[Joueur][STATUT] == EnVie) {

				DEGATS = static_cast<int>(ceil(frand_a_b((i + 1)*0.05, (i + 1)*0.15)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, Joueur, Joueur);
				PersoCarac[Joueur][FORCE] = static_cast<int>(PersoCarac[Joueur][FORCE] * 1.1);
				PersoCarac[Joueur][AGILITE] = static_cast<int>(PersoCarac[Joueur][AGILITE] * 1.1);
			}
		}
		PersoCarac[Joueur][MANA]--;
		break;
	case 2:
		cout << Personnage[Joueur] << " Fais du tapis de course ! " << endl;

		for (int i = 0; i < 100 && EquipeEnVie(TeamEnnemie(Joueur)) == true; i++) {
			if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && PersoCarac[Joueur][STATUT] == EnVie) {

				DEGATS = static_cast<int>(ceil(frand_a_b(i*0.001, i*0.002)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, Joueur, Joueur);
				PersoCarac[Joueur][FORCE] = static_cast<int>(PersoCarac[Joueur][FORCE] * 1.001);
				PersoCarac[Joueur][AGILITE] = static_cast<int>(PersoCarac[Joueur][AGILITE] * 1.001);
			}
		}
		PersoCarac[Joueur][MANA] -= 2;
		break;
	case 3:
		AttaquerBATON(Joueur);
		break;
	}
}

void AttaquerDEMO(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	int inc = PREMIER;
	bool t = false;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " ... ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(1,2)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleProche(Joueur), Joueur);

		DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Joueur, Joueur);
		
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << " Transfusion ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleProche(Joueur), Joueur);

		DEGATS = static_cast<int>(ceil(frand_a_b(1,2)*PersoCarac[Joueur][FORCE]));
		Soins(TeamTMP, PositionJoueur(Joueur), DEGATS, Joueur);
		PersoCarac[Joueur][MANA] -= 1;
		break;
	case 2:
		cout << Personnage[Joueur] <<&Joueur <<" éäâ$ ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(3, 9)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleAlea(Joueur), Joueur);

		DEGATS = static_cast<int>(ceil(frand_a_b(2,5)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Joueur, Joueur);
		
		PersoCarac[Joueur][MANA] -= 2;
		break;
	case 3:
		
		while (inc < CINQUIEME&&t == false) {
			if (PersoCarac[Equipe[TEAM1][inc]][STATUT] == KO) {
				cout << "Reanimation" << endl;
				t = true;
				PersoCarac[Equipe[TEAM1][inc]][STATUT] = EnVie;
				DEGATS = static_cast<int>(ceil(frand_a_b(4,8)*PersoCarac[Joueur][FORCE]));
				Soins(TEAM1, inc, DEGATS, Joueur);
				DEGATS = static_cast<int>(ceil(frand_a_b(0.3,0.9)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, Joueur, Joueur);
			}
			inc++;
		}
		if(t==false) {
			cout << "Les 3 lutins du diable" << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(3.33,4.99)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		
			
			DEGATS = static_cast<int>(ceil(frand_a_b(3.33,4.99)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
	
	
			DEGATS = static_cast<int>(ceil(frand_a_b(3.33,4.99)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		}
			DEGATS = static_cast<int>(ceil(frand_a_b(3.33,4.99)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Joueur, Joueur);
	
		t = false;
		inc = PREMIER;
		PersoCarac[Joueur][MANA] -= 3;
		break;
	}
}

void AttaquerVENTRE(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM1;
	}
	else {
		 TeamTMP=TEAM2;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" coup de bide ! "<<endl;

			DEGATS = static_cast<int>(ceil(frand_a_b(0.4,0.8)*PersoCarac[Joueur][FORCE]));
			DEGATS += static_cast<int>(ceil(abs(PersoCarac[Joueur][VITALITE]-PersoCarac[Joueur][VIE]/10.0)));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			soins = static_cast<int>(ceil(frand_a_b(0.35,0.70)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<Personnage[Joueur]<<" pete un gros coup , ca asphyxie tout les ennemis ! "<<endl;
					for(int i=PREMIER;i<=CINQUIEME&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {

					DEGATS = static_cast<int>(ceil(frand_a_b(0.03,0.09)*PersoCarac[Joueur][VIE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][i],Joueur);
						
					}
			}					
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" saut dans le tas ! "<<endl;

		
				DEGATS = static_cast<int>(ceil(frand_a_b(0.5,2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
		
	
				DEGATS = static_cast<int>(ceil(frand_a_b(1.0,2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
	
	
				DEGATS = static_cast<int>(ceil(frand_a_b(1.5,2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
		
			
				DEGATS = static_cast<int>(ceil(frand_a_b(1.0,2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
		
		
				DEGATS = static_cast<int>(ceil(frand_a_b(0.5,2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
		
			
			soins = static_cast<int>(ceil(frand_a_b(1.25,2.25)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" DOUBLE saut ! "<<endl;
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.5,2.0)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
			
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.75,2.0)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
			
			
					DEGATS = static_cast<int>(ceil(frand_a_b(1.0,2.0)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
			
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.75,2.0)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
			
			
					DEGATS = static_cast<int>(ceil(frand_a_b(0.5,2.0)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
			
				soins = static_cast<int>(ceil(frand_a_b(0.75,1.75)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			}
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" Ramene de la bouffe ! "<<endl;

			for(int i=PREMIER;i<=CINQUIEME;i++) {
				soins = static_cast<int>(ceil(frand_a_b(0.33,1.66)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,i,soins,Joueur);
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" Y en a encore ! "<<endl;

				for(int i=PREMIER;i<=CINQUIEME;i++) {
					soins = static_cast<int>(ceil(frand_a_b(0.22,1.22)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,i,soins,Joueur);
				}

			}
			PersoCarac[Joueur][MANA]-=2;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" J'ai bien manger j'ai bien bue j'ai la peau du ventre bien tendue ! "<<endl;

			for(int i=PREMIER;i<=CINQUIEME;i++) {
			
				DEGATS = static_cast<int>(ceil(frand_a_b(1.5,3.5)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][i],Joueur);
			
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" DOUBLE ATTAQUE ! "<<endl;

				for(int i=PREMIER;i<=CINQUIEME;i++) {
				
						DEGATS = static_cast<int>(ceil(frand_a_b(1.25,3.75)*PersoCarac[Joueur][FORCE]));
						Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][i],Joueur);
					
				}
				cout<<endl;
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerALACOOL(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM1;
	}
	else {
		 TeamTMP=TEAM2;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" se detend . "<<endl;

			soins = static_cast<int>(ceil(frand_a_b(0.4,0.8)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" DOUBLE DETENTE ! "<<endl;

				soins = static_cast<int>(ceil(frand_a_b(0.2,0.4)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" bois un coup . "<<endl;

			soins = static_cast<int>(ceil(frand_a_b(0.25,1.25)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" Il en enfile une autre ! "<<endl;
				soins = static_cast<int>(ceil(frand_a_b(0.2,0.4)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" sert l'apero . "<<endl;
			for(int i=PREMIER;i<=CINQUIEME;i++) {
				soins = static_cast<int>(ceil(frand_a_b(0.17,0.7)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,i,soins,Joueur);
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) {
				cout<<" DOUBLE SERVICE ! "<<endl;

				for(int i=PREMIER;i<=CINQUIEME;i++) {
					soins = static_cast<int>(ceil(frand_a_b(0.07,0.37)*PersoCarac[Joueur][FORCE]));
					Soins(TeamTMP,i,soins,Joueur);
				}
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" S'ENERVE !!! "<<endl;
			for(int i=PREMIER;i<=CINQUIEME;i++) {
				
					DEGATS = static_cast<int>(ceil(frand_a_b(0.55,1.55)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][i],Joueur);
				
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) {
				cout<<" Il est encore furieux ! "<<endl;
				for(int i=PREMIER;i<=CINQUIEME;i++) {
					
						DEGATS = static_cast<int>(ceil(frand_a_b(0.35,0.99)*PersoCarac[Joueur][FORCE]));
						Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][i],Joueur);
					
				}
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerTRUGDOR(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" fleche dans le genoue ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.27,0.77)*PersoCarac[Joueur][FORCE]));
			DEGATS+= static_cast<int>(ceil(0.1*PersoCarac[CibleProche(Joueur)][VITALITE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<< " deuxieme fleche !  "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.17,0.77)*PersoCarac[Joueur][FORCE]));
				DEGATS+= static_cast<int>(ceil(0.07*PersoCarac[CibleProche(Joueur)][VITALITE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
			}
			if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout << " Attention j'ai fais de la muscu !  Sa force a augmentee ! " << endl;
				PersoCarac[Joueur][FORCE] *= static_cast< int>(((1.0 + (3 * Tour) / 100)));
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" vise la pomme ! "<<endl;

			DEGATS = static_cast<int>(ceil(frand_a_b(0.77,1.27)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" ca touche ! "<<endl;

				DEGATS = static_cast<int>(ceil(frand_a_b(1.27,2.27)*PersoCarac[Joueur][FORCE]));
				DEGATS+= static_cast<int>(ceil(0.17*PersoCarac[CibleProche(Joueur)][VIE]));
				Attaque(DEGATS,CibleLoin(Joueur),Joueur);
			}
			if(tiragePersoCarac(Joueur,HABILETE)){
				cout<<endl<<"BOUGE !!! "<<endl;
				int a=rand_a_b(PREMIER,CINQUIEME+1);
				int b=rand_a_b(PREMIER,CINQUIEME+1);
				int tmp=Equipe[TeamEnnemie(Joueur)][a];
				Equipe[TeamEnnemie(Joueur)][a]=Equipe[TeamEnnemie(Joueur)][b];
				Equipe[TeamEnnemie(Joueur)][b]=tmp;
				cout<<endl<<"Des joueurs ont bouges . "<<endl;
			}
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" Envoie une fleche  ! "<<endl;

			for(int i=0;i<5&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {

				cout<< " Ricoche ! "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(i*0.7,0.7+i*0.7)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					cout<<" DOUBLE Ricoche ! "<<endl;
					DEGATS = static_cast<int>(ceil(frand_a_b(i*0.7,0.7+i*0.7)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,CibleAlea(Joueur),Joueur);
				}
			}
			PersoCarac[Joueur][MANA]-=2;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" volee de fleche ! "<<endl;

			for(int i=0;i<21&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {

				DEGATS = static_cast<int>(ceil(frand_a_b(0.14,0.28)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					cout<<" DOUBLE FLECHE ! "<<endl;
					DEGATS = static_cast<int>(ceil(frand_a_b(0.14,0.28)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,CibleAlea(Joueur),Joueur);
				}
			PersoCarac[Joueur][MANA]++;
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					cout<<" DOUBLE VOLEE ! "<<endl;

				for(int i=0;i<11&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {
						DEGATS = static_cast<int>(ceil(frand_a_b(0.14,0.28)*PersoCarac[Joueur][FORCE]));
						Attaque(DEGATS,CibleAlea(Joueur),Joueur);
						if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
							cout<<" DOUBLE FLECHE ! "<<endl;
								DEGATS = static_cast<int>(ceil(frand_a_b(0.14,0.28)*PersoCarac[Joueur][FORCE]));
								Attaque(DEGATS,CibleAlea(Joueur),Joueur);
						}
					PersoCarac[Joueur][MANA]++;
					}
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerDAGUES(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM1;
	}
	else {
		 TeamTMP=TEAM2;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" Premiere Dague ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.6,0.9)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<< " Saignement !  "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
				PersoCarac[Joueur][MANA]++;
			}
			PersoCarac[Joueur][MANA]++;
			cout<<Personnage[Joueur]<<" Deuxieme Dague ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.3,0.55)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<< " Saignement !  "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.05,0.1)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
				PersoCarac[Joueur][MANA]++;
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" Vise le plus faible ! "<<endl;

			DEGATS = static_cast<int>(ceil(frand_a_b(0.25,0.50)*PersoCarac[Joueur][FORCE]));
			DEGATS*= static_cast<int>(ceil((PersoCarac[CibleFaible(Joueur)][VITALITE]*10.0)/(PersoCarac[CibleFaible(Joueur)][VIE]*1.0)));
			Attaque(DEGATS,CibleFaible(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<" Double Attaque ! "<<endl;

				DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
				DEGATS*= static_cast<int>(ceil((PersoCarac[CibleFaible(Joueur)][VITALITE]*10.0)/(PersoCarac[CibleFaible(Joueur)][VIE]*1.0)));
				Attaque(DEGATS,CibleFaible(Joueur),Joueur);
			}
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" Envoie des Shurikens  ! "<<endl;

			for(int i=0;i<3&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {

				cout<< " Shuriken ! "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.15,0.6)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					cout<<" Mini Shuriken ! "<<endl;
					DEGATS = static_cast<int>(ceil(frand_a_b(0.075,0.9)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,CibleAlea(Joueur),Joueur);
				}
			cout<<endl;
			}
			PersoCarac[Joueur][MANA]-=2;
			break;
		case 3:

			cout<<Personnage[Joueur]<<" Se Transforme . "<<endl;

			soins = static_cast<int>(ceil(frand_a_b(0.2,0.6)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			PersoCarac[Joueur][FORCE]= static_cast< int>(PersoCarac[Joueur][FORCE]*1.1);
			PersoCarac[Joueur][AGILITE]= static_cast<int>(PersoCarac[Joueur][AGILITE] * 1.1);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) {
				cout<<endl<<" Grosse Transformations ! "<<endl;
				soins = static_cast<int>(ceil(frand_a_b(0.1,0.3)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
				PersoCarac[Joueur][FORCE] = static_cast<int>(PersoCarac[Joueur][FORCE] * 1.1);
				PersoCarac[Joueur][AGILITE] = static_cast< int>(PersoCarac[Joueur][AGILITE] * 1.1);
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerNINI(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM1;
	}
	else {
		 TeamTMP=TEAM2;
	}
	int p;
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" Coup de couteau ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.6,0.8)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<< " Double coup de couteau !  "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.4,0.7)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
			}

			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" Coup de pompe ! "<<endl;

			p = PositionJoueur(CibleProche(Joueur)) + 1;
			DEGATS = static_cast<int>(ceil(frand_a_b(1.0,2.5)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			
			for(int i=p;i<5&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {
				if(PersoCarac[Equipe[TEAM2][i]][STATUT]==EnVie) {

				cout<< " Residue ! "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.3)*PersoCarac[Joueur][FORCE]));

				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][i],Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					if (PersoCarac[Equipe[TEAM2][i]][STATUT] == EnVie) {
						cout << " Double résidue ! " << endl;
						DEGATS = static_cast<int>(ceil(frand_a_b(0.05, 0.15)*PersoCarac[Joueur][FORCE]));
						Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
					}
				}
				}
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout << Personnage[Joueur] << " Second Coup de pompe ! " << endl;
				
				p = PositionJoueur(CibleProche(Joueur)) + 1;
				DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 2.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, CibleProche(Joueur), Joueur);
				
				for (int i = p; i < 5 && EquipeEnVie(TeamEnnemie(Joueur)) == true; i++) {
					if (PersoCarac[Equipe[TEAM2][i]][STATUT] == EnVie) {

						cout << " Residue ! " << endl;
						DEGATS = static_cast<int>(ceil(frand_a_b(0.1, 0.3)*PersoCarac[Joueur][FORCE]));

						Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
						if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
							if (PersoCarac[Equipe[TEAM2][i]][STATUT] == EnVie) {
								cout << " Double résidue ! " << endl;
								DEGATS = static_cast<int>(ceil(frand_a_b(0.05, 0.15)*PersoCarac[Joueur][FORCE]));
								Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
								Sleep(100);
							}
						}
					}
				}

			}
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" Sort le fusil d'assaut  ! "<<endl;

			for(int i=0;i<(rand_a_b(25,35))&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {

				cout<< " Balle de fusil d'assaut ! "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					cout<<" Saignement ! "<<endl;
					DEGATS = static_cast<int>(ceil(frand_a_b(0.01,0.05)*PersoCarac[Joueur][FORCE]));
					Attaque(DEGATS,CibleAlea(Joueur),Joueur);
				}
			cout<<endl;
			}
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
					cout<<Personnage[Joueur]<<" Ressort le fusil d'assaut  ! "<<endl;
					for(int i=0;i<(rand_a_b(25,35))&&EquipeEnVie(TeamEnnemie(Joueur))==true;i++) {

						cout<< " Balle de fusil d'assaut ! "<<endl;
						DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
						Attaque(DEGATS,CibleProche(Joueur),Joueur);
					if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
						cout<<" Saignement ! "<<endl;
						DEGATS = static_cast<int>(ceil(frand_a_b(0.01,0.05)*PersoCarac[Joueur][FORCE]));
						Attaque(DEGATS,CibleAlea(Joueur),Joueur);
					}
					cout<<endl;
					}
				}
			PersoCarac[Joueur][MANA]-=2;
			break;
		case 3:

			cout<<Personnage[Joueur]<<" Partage equipement minecraft . "<<endl;

			soins = static_cast<int>(ceil(frand_a_b(0.4,1.2)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,PositionJoueur(Joueur),soins,Joueur);
			for(int i=PREMIER;i<=CINQUIEME;i++) {
				PersoCarac[Equipe[TeamTMP][i]][FORCE]= static_cast< int>(PersoCarac[Equipe[TeamTMP][i]][FORCE] * 1.1);
				PersoCarac[Equipe[TeamTMP][i]][AGILITE]= static_cast< int>(PersoCarac[Equipe[TeamTMP][i]][AGILITE] * 1.1);
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) {
				cout<<endl<<" le sens du partage ! "<<endl;
				for(int i=PREMIER;i<=CINQUIEME;i++) {
					PersoCarac[Equipe[TeamTMP][i]][FORCE] = static_cast<int>(PersoCarac[Equipe[TeamTMP][i]][FORCE] * 1.1);
					PersoCarac[Equipe[TeamTMP][i]][AGILITE] = static_cast< int>(PersoCarac[Equipe[TeamTMP][i]][AGILITE] * 1.1);
				}
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerJBI(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM2;
	}
	else {
		 TeamTMP=TEAM1;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" est dans la place ! "<<endl;
			
			Attaque(static_cast<int>((Tour*(Tour+1))*PersoCarac[Joueur][LVL]/1000),CibleProche(Joueur),Joueur);
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" danse ! "<<endl;
			Attaque(static_cast<int>((2*Tour*(Tour + 1))*PersoCarac[Joueur][LVL]/1000),CibleProche(Joueur),Joueur);
			PersoCarac[Joueur][MANA]++;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" a le swag ! "<<endl;
			Attaque(static_cast<int>((3*Tour*(Tour + 1))*PersoCarac[Joueur][LVL]/1000),CibleProche(Joueur),Joueur);
			PersoCarac[Joueur][MANA]+=2;
			break;
		case 3:

			cout<<Personnage[Joueur]<<" casse le téléphone de "<<Personnage[rand_a_b(0,NBJoueurs)]<<endl;
			Attaque(static_cast<int>((4*Tour*(Tour + 1))*PersoCarac[Joueur][LVL]/1000),CibleProche(Joueur),Joueur);
			PersoCarac[Joueur][MANA]+=3;
			break;
	}
}

void AttaquerLAPIN(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM2;
	}
	else {
		 TeamTMP=TEAM1;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" bondit ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout<< " Double bondissage !  "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.2,0.4)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
			}
			PersoCarac[Joueur][CHANCEDOUBLEATTAQUE]+=1;
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
				cout<<Personnage[Joueur]<<" griffures ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.3,1.2)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout<< " Saignement !  "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.15,0.6)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" sautille ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.1,1.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
				if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout<< " Coup de boule !  "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(1.15,1.6)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
			}
			PersoCarac[Joueur][MANA]+=2;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" s'enrage' ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(1.3,2.2)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			PersoCarac[Joueur][HABILETE]+=Tour;
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerSANGLIER(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM2;
	}
	else {
		 TeamTMP=TEAM1;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" charge ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.9,1.3)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);

			PersoCarac[Joueur][FORCE]= static_cast<int>(PersoCarac[Joueur][FORCE] * 1.1);
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
				cout<<Personnage[Joueur]<<" se repose ! "<<endl;
				soins = static_cast<int>(ceil(frand_a_b(0.5,0.75)*PersoCarac[Joueur][FORCE]));
			Soins(TEAM2,PositionJoueur(Joueur),soins,Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout<< " long repos !  "<<endl;
					soins = static_cast<int>(ceil(frand_a_b(0.10,0.5)*PersoCarac[Joueur][FORCE]));
				Soins(TEAM2,PositionJoueur(Joueur),soins,Joueur);
				PersoCarac[Joueur][MANA]++;
			}
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" gonfle ! "<<endl;
			PersoCarac[Joueur][CHANCEDOUBLEATTAQUE]+=4;
			PersoCarac[Joueur][HABILETE]+=4;
			PersoCarac[Joueur][MANA]+=1;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" charge dans tout les sens ! "<<endl;
		
			DEGATS = static_cast<int>(ceil(frand_a_b(0.1,0.2)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			if(EquipeEnVie(TEAM1)) {
				DEGATS = static_cast<int>(ceil(frand_a_b(0.2,0.4)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			}
			if(EquipeEnVie(TEAM1)) {
				DEGATS = static_cast<int>(ceil(frand_a_b(0.4,0.8)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			}
			if(EquipeEnVie(TEAM1)) {
				DEGATS = static_cast<int>(ceil(frand_a_b(0.8,1.6)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			}
			if(EquipeEnVie(TEAM1)) {
				DEGATS = static_cast<int>(ceil(frand_a_b(1.6,3.2)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			}
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerCERF(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM2;
	}
	else {
		 TeamTMP=TEAM1;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" coup de bois ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.75,1.5)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" coup viser ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(1.25,1.75)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleFaible(Joueur),Joueur);
			PersoCarac[Joueur][MANA]--;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" esprit de la nature ! "<<endl;
			PersoCarac[Joueur][FORCE]= PersoCarac[Joueur][FORCE]* static_cast<long long int>(1.3);
			for(int i = PREMIER;i<=CINQUIEME;i++) {
			soins = static_cast<int>(ceil(frand_a_b(0.45,0.75)*PersoCarac[Joueur][FORCE]));
			Soins(TEAM2,i,soins,Joueur);
			}
			break;
		case 3:
			cout<<Personnage[Joueur]<<" Sacrifice ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(10.0,15.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleAlea(Joueur),Joueur);
			PersoCarac[Joueur][VIE]= PersoCarac[Joueur][VIE]/static_cast<long long int>(999.0);
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerPETITPONEY(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM2;
	}
	else {
		 TeamTMP=TEAM1;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" sa ganbade ! "<<endl;
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" ne se soucie pas du temp qui passe ! "<<endl;
			PersoCarac[Joueur][MANA]++;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" est tout gris ! "<<endl;
			PersoCarac[Joueur][MANA]++;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" bluh ! "<<endl;
			PersoCarac[Joueur][MANA]-=3;
			break;
	}
}

void AttaquerSALIM(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int soins;
	int TeamTMP;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM1;
	}
	else {
		 TeamTMP=TEAM2;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" enracinage ! "<<endl;
			Soins(TEAM1,PositionJoueur(Joueur), static_cast<int>(PersoCarac[Joueur][VIE]*0.01),Joueur);
			DEGATS = static_cast<int>(ceil(frand_a_b(0.3,0.6 )*PersoCarac[Joueur][VITALITE]+ frand_a_b(0.04, 0.08)*PersoCarac[Joueur][VIE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout<<Personnage[Joueur]<<" enracinage ! "<<endl;
				Soins(TeamTMP,PositionJoueur(Joueur), static_cast<int>(PersoCarac[Joueur][VIE]*0.01),Joueur);
				DEGATS = static_cast<int>(ceil(frand_a_b(0.1, 0.2)*PersoCarac[Joueur][VITALITE] + frand_a_b(0.02, 0.04)*PersoCarac[Joueur][VIE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			PersoCarac[Joueur][REDUCTION]++;
			cout<<Personnage[Joueur]<<" soin de la foret ! "<<endl;
			soins = static_cast<int>(ceil(frand_a_b(0.6,1.8)*PersoCarac[Joueur][FORCE]));
			Soins(TeamTMP,PositionJoueur(CibleFaible(30)),soins,Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) { 
				PersoCarac[Joueur][REDUCTION]++;
				cout<<Personnage[Joueur]<<" soin de la foret ! "<<endl;
				soins = static_cast<int>(ceil(frand_a_b(0.6,1.8)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PositionJoueur(CibleFaible(30)),soins,Joueur);
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" esprit de la nature ! "<<endl;
			PersoCarac[Joueur][FORCE]= PersoCarac[Joueur][FORCE] * static_cast<long long int>(1.1);
			for(int i = PREMIER;EquipeEnVie(TEAM2)&&i<=CINQUIEME;i++) {
				soins = static_cast<int>(ceil(frand_a_b(0.05*i*i,0.1*i*i)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PositionJoueur(CibleFaible(30)),soins,Joueur);
			}
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&& EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				for(int i = PREMIER;!EquipeEnVie(TEAM2)&&i<=CINQUIEME;i++) {
					if(EquipeEnVie(TEAM2)) {
				DEGATS = static_cast<int>(ceil(frand_a_b(0.05*i*i,0.1*i*i)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleAlea(Joueur),Joueur);
					}
				}	
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 3:
			cout<<Personnage[Joueur]<<" Esprit du salim ! "<<endl;
			PersoCarac[Joueur][REDUCTION]= PersoCarac[Joueur][REDUCTION] + static_cast<long long int>(3);
			PersoCarac[Joueur][VIE]= PersoCarac[Joueur][VIE] * static_cast<long long int>(2);
			PersoCarac[Joueur][FORCE]= PersoCarac[Joueur][FORCE] * static_cast<long long int>(1.2);
			DEGATS = static_cast<int>(ceil(frand_a_b(1.5,4.5)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleFaible(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)) {
				soins = static_cast<int>(ceil(frand_a_b(1,4)*PersoCarac[Joueur][FORCE]));
				Soins(TeamTMP,PositionJoueur(CibleFaible(30)),soins,Joueur);	
			}
			break;
	}
}

void AttaquerDRAGON(int Joueur) {
	int choix=rand_a_b(0,(PersoCarac[Joueur][MANA])%4+1);
	int DEGATS;
	int TeamTMP;
	int R,R2;
	if(PersoCarac[Joueur][EQUIPE]==TEAM1) {
		TeamTMP=TEAM2;
	}
	else {
		 TeamTMP=TEAM1;
	}
	switch(choix) {

		case 0:
			cout<<Personnage[Joueur]<<" Morsure ! "<<endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(1.0,2.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS,CibleProche(Joueur),Joueur);
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout<<Personnage[Joueur]<<" Deuxieme Morsure ! "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.3,3.0)*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS,CibleProche(Joueur),Joueur);
				PersoCarac[Joueur][MANA]++;
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 1:
			cout<<Personnage[Joueur]<<" lance flamme ! "<<endl;
			R=0;
			DEGATS = static_cast<int>(ceil(frand_a_b(3.5,7.0)*PersoCarac[Joueur][FORCE]));
		
				
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
				R+= static_cast<int>(PersoCarac[Equipe[TEAM1][PREMIER]][VIE]/10.0);
		
	
				
				Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
				R+= static_cast<int>(PersoCarac[Equipe[TEAM1][DEUXIEME]][VIE]/10.0);
	
		
				
				Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
				R+= static_cast<int>(PersoCarac[Equipe[TEAM1][TROISIEME]][VIE]/10.0);
		
			
				
				Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
				R+= static_cast<int>(PersoCarac[Equipe[TEAM1][QUATRIEME]][VIE]/10.0);
	
	
				
				Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
		
			R=0;
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<Personnage[Joueur]<<" lance flamme 2 ! "<<endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(2.0,4.0)*PersoCarac[Joueur][FORCE]));
				
					
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
					R+=static_cast<int>(PersoCarac[Equipe[TEAM1][PREMIER]][VIE]/10.0);
				
			
				
					Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
					R+= static_cast<int>(PersoCarac[Equipe[TEAM1][DEUXIEME]][VIE]/10.0);
			
				
					
					Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
					R+= static_cast<int>(PersoCarac[Equipe[TEAM1][TROISIEME]][VIE]/10.0);
				
				
					Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
					R+= static_cast<int>(PersoCarac[Equipe[TEAM1][QUATRIEME]][VIE]/10.0);
				
			
				
					Attaque(DEGATS-R,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
				
			PersoCarac[Joueur][MANA]-=2;
			}	
			PersoCarac[Joueur][MANA]++;
			break;
		case 2:
			cout<<Personnage[Joueur]<<" coup queue ! "<<endl;
			R2=0;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.001,0.003)*PersoCarac[Joueur][FORCE]));
		
				
				Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
				R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][CINQUIEME]][VIE]/50.0);
			
		
				
				Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
				R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][QUATRIEME]][VIE]/50.0);
		
		
				
				Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
				R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][TROISIEME]][VIE]/50.0);
			
			
				
				Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
				R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][DEUXIEME]][VIE]/50.0);
			
			
				
				Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
			
			if(tiragePersoCarac(Joueur,CHANCEDOUBLEATTAQUE)&&EquipeEnVie(TeamEnnemie(Joueur))==true) {
				cout<<Personnage[Joueur]<<" recoup de queue ! "<<endl;
				 R2=0;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.0001,0.001)*PersoCarac[Joueur][FORCE]));
				
				
					Attaque(DEGATS,Equipe[TeamEnnemie(Joueur)][CINQUIEME],Joueur);
					R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][CINQUIEME]][VIE]/75.0);
				
				
				
					Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][QUATRIEME],Joueur);
					R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][QUATRIEME]][VIE]/75.0);
				
			
				
					Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][TROISIEME],Joueur);
					R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][TROISIEME]][VIE]/75.0);
				
			
				
					Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][DEUXIEME],Joueur);
					R2=R2+ static_cast<int>(PersoCarac[Equipe[TEAM1][DEUXIEME]][VIE]/75.0);
				
			
				
					Attaque(DEGATS*R2,Equipe[TeamEnnemie(Joueur)][PREMIER],Joueur);
				
				PersoCarac[Joueur][MANA]-=2;
			}
			PersoCarac[Joueur][MANA]++;
			break;
		case 3:
			cout << "T" << endl;
			AttaquerDRAGON(Joueur);
			
			break;
	}
}

void AttaquerKUNGFU(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) %4 + 1);
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	long long int reduc = static_cast<long long int>(PersoCarac[CibleProche(Joueur)][REDUCTION] / 100.0);
	long long int calculReduc = static_cast<long long int>((1 + reduc * 3)*(1 + reduc * 3));
	long long int calculReduc2 = static_cast<long long int>(( reduc * 3)*( reduc * 3)+1);
	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " Poing du dragon ! " << endl;
		
		DEGATS = static_cast<int>(ceil(frand_a_b(0.25*calculReduc, 0.5*calculReduc)*PersoCarac[Joueur][FORCE]));
		PersoCarac[CibleProche(Joueur)][REDUCTION] = PersoCarac[CibleProche(Joueur)][REDUCTION] - static_cast<long long int>(5);
		Attaque(DEGATS, CibleProche(Joueur), Joueur);
		if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
			cout << " Coup de pied du dragon !  " << endl;
			PersoCarac[CibleProche(Joueur)][REDUCTION] = PersoCarac[CibleProche(Joueur)][REDUCTION] - static_cast<long long int>(5);
			Attaque(DEGATS, CibleProche(Joueur), Joueur);
			PersoCarac[Joueur][MANA]++;
		}
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << " A la flemme ! " << endl;
		PersoCarac[Joueur][MANA]++;
		break;
	case 2:
		cout << Personnage[Joueur] << " A la flemme ! " << endl;
		PersoCarac[Joueur][MANA]++;
		break;
	case 3:

		cout << Personnage[Joueur] << " ASURA STRIKE . " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(7.0,12.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		PersoCarac[Joueur][MANA] -= 3;
		break;
	}
}

void AttaquerTELLURIQUE(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	int spread1, spread2, spread3;;

	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " se prépare ! " << endl;

		DEGATS = static_cast<int>(ceil(frand_a_b(0.01,0.1)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleProche(Joueur), Joueur);
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << " Telluriforce ! " << endl;
		spread1 = static_cast<int>(PersoCarac[Equipe[TEAM1][TROISIEME]][VIE]/500);
		spread2 = static_cast<int>(PersoCarac[Equipe[TEAM1][DEUXIEME]][VIE] / 500+spread1);
		spread3 = static_cast<int>(PersoCarac[Equipe[TEAM1][QUATRIEME]][VIE] / 500+spread1);
		
			DEGATS = static_cast<int>(ceil(frand_a_b(0.01, 0.1)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][TROISIEME], Joueur);
		

	
			DEGATS = static_cast<int>(ceil(spread1*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][DEUXIEME], Joueur);
		
		
			DEGATS = static_cast<int>(ceil(spread1*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][QUATRIEME], Joueur);
		

		
			DEGATS = static_cast<int>(ceil(spread2*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][PREMIER], Joueur);
		
	
			DEGATS = static_cast<int>(ceil(spread3*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][CINQUIEME], Joueur);
		
		PersoCarac[Joueur][MANA]++;
		break;
	case 2:
		cout << Personnage[Joueur] << "Eruption ! " << endl;
	
			DEGATS = static_cast<int>(ceil(frand_a_b(4.0, 6.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][TROISIEME], Joueur);
	

		
			DEGATS = static_cast<int>(ceil(frand_a_b(2.0, 3.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][DEUXIEME], Joueur);
	
		
			DEGATS = static_cast<int>(ceil(frand_a_b(2.0, 3.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][QUATRIEME], Joueur);
		

		
			DEGATS = static_cast<int>(ceil(frand_a_b(0.5, 0.75)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][PREMIER], Joueur);
		
		
			DEGATS = static_cast<int>(ceil(frand_a_b(0.5, 0.75)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TEAM1][CINQUIEME], Joueur);
		
		PersoCarac[Joueur][MANA]++;
		break;
	case 3:

		cout << Personnage[Joueur] << " Volonté du dragon ! " << endl;
		AttaquerDRAGON(Joueur);
		break;
	}
}

void AttaquerELITE(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	

	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " Mitraillette Alien ! " << endl;

		for (int i = 0; i < 10 && EquipeEnVie(TeamEnnemie(Joueur)) == true; i++) {

			DEGATS = static_cast<int>(ceil(frand_a_b(0.2, 0.3)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleProche(Joueur), Joueur);
		}
		if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE)) {
			cout << " DOUBLE SAUCE ! " << endl;

			for (int i = 0; i < 10 && EquipeEnVie(TeamEnnemie(Joueur)) == true; i++) {
				DEGATS = static_cast<int>(ceil(frand_a_b(0.2, 0.3 )*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, CibleProche(Joueur), Joueur);
			}
		}
		else {
			cout << " SURCHARGE ! " << endl;
		}
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << " COUP EPEE ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(3.5, 7.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleProche(Joueur), Joueur);
		PersoCarac[Joueur][MANA]--;
		break;
	case 2:
		cout << Personnage[Joueur] << " WUT WUT WUT ! " << endl;
		PersoCarac[CibleProche(Joueur)][REDUCTION] = PersoCarac[CibleProche(Joueur)][REDUCTION] - static_cast<long long int>(10);
		PersoCarac[Joueur][MANA]++;
		break;
	case 3:

		cout << Personnage[Joueur] << " REGENERATION BOUCLIER ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(8.0, 12.0)*PersoCarac[Joueur][FORCE]));
		Soins(TeamTMP, PositionJoueur(Joueur),DEGATS, Joueur);
		PersoCarac[Joueur][MANA] -= 3;
		break;
	}
}

void AttaquerGROGNARD(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}

	double tic = 0;
	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " Neeler ! " << endl;

		for (int i = 0; i < 20 && EquipeEnVie(TeamEnnemie(Joueur)) == true; i++,tic+=0.1) {

			DEGATS = static_cast<int>(ceil(frand_a_b(0.2, 0.3)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleProche(Joueur), Joueur);
			if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
				cout << " DOUBLE ATTAQUE ! " << endl;
				DEGATS = static_cast<int>(ceil(frand_a_b(0.1, 0.2 )*PersoCarac[Joueur][FORCE]));
				Attaque(DEGATS, CibleProche(Joueur), Joueur);
				tic += 0.1;
			}
		}
		cout << Personnage[Joueur] << " Explosion ! " << endl;
		if (EquipeEnVie(TeamEnnemie(Joueur))) {
			DEGATS = static_cast<int>(ceil(frand_a_b(tic*10.0, tic*20.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleProche(Joueur), Joueur);
		}
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << " SAUVER VOUS ! " << endl;
		PersoCarac[Joueur][REDUCTION] = PersoCarac[Joueur][REDUCTION] - static_cast<long long int>(10);
		PersoCarac[Joueur][MANA]++;
		break;
	case 2:
		cout << Personnage[Joueur] << " A L'AIDE ! " << endl;
		PersoCarac[Joueur][MANA]++;
		break;
	case 3:

		cout << Personnage[Joueur] << " SUICIDE ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(5.0, 10.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleProche(Joueur), Joueur);
		PersoCarac[Joueur][MANA] -= 3;
		break;
	}
}

void AttaquerHUNTER(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}

	
	switch (choix) {

	case 0:
		
		if (tiragePersoCarac(Joueur, HABILETE)) {
			cout << " COUP CHARGER ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(2.0, 6.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleProche(Joueur), Joueur);
	
		}
		else {
			cout << " COUP CHARGER ESQUIVER ! " << endl;
		}
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << "COUP COUDE ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 4.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleProche(Joueur), Joueur);
		if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
			cout << " DOUBLE COUP ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 2.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleProche(Joueur), Joueur);
		}
		PersoCarac[Joueur][MANA]--;
		break;
	case 2:
		cout << Personnage[Joueur] << " Coup charger precis ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(3.0, 7.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleProche(Joueur), Joueur);
		
		PersoCarac[Joueur][MANA]++;
		break;
	case 3:

		cout << Personnage[Joueur] << " VOUS SUIT ! " << endl;
		PersoCarac[Joueur][MANA] -= 3;
		break;
	}
}

void AttaquerCHASSEUR(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}

	int CibleAleatoire;
	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " Assaut ! " << endl;
		CibleAleatoire = CibleAlea(Joueur);
		DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 3.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleAleatoire, Joueur);
		
			DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 3.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAleatoire, Joueur);
		
	
			DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 3.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAleatoire, Joueur);
		
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << " SNIPE ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(2.5, 12.5)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleFaible(Joueur), Joueur);
		if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
			cout << " DOUBLE SNIPE ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(2.5, 12.5)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleFaible(Joueur), Joueur);
		}
		PersoCarac[Joueur][MANA]--;
		break;
	case 2:
		cout << Personnage[Joueur] << " DRESSAGE BOUCLIER ! " << endl;
		PersoCarac[Joueur][REDUCTION] = PersoCarac[Joueur][REDUCTION] + static_cast<long long int>(20);
		if (PersoCarac[Joueur][REDUCTION] > 80) {
			PersoCarac[Joueur][REDUCTION] = 80;
		}
		PersoCarac[Joueur][MANA]++;
		break;
	case 3:

		cout << Personnage[Joueur] << " ROULADE SUR LE COTE ! " << endl;
		PersoCarac[Joueur][MANA] -= 3;
		break;
	}
}

void AttaquerBRUTE(int Joueur) {
	int choix = rand_a_b(0, (PersoCarac[Joueur][MANA]) % 4 + 1);
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}

	
	switch (choix) {

	case 0:
		cout << Personnage[Joueur] << " Lance Grenade ! " << endl;
		
		DEGATS = static_cast<int>(ceil(frand_a_b(0.5, 1.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleAlea(Joueur), Joueur);
	
			DEGATS = static_cast<int>(ceil(frand_a_b(0.5, 1.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		
	
			DEGATS = static_cast<int>(ceil(frand_a_b(0.5, 1.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		
		PersoCarac[Joueur][MANA]++;
		break;
	case 1:
		cout << Personnage[Joueur] << " Coup rasoir ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 4.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
			cout << " DOUBLE SNIPE ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.5, 2.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		}
		PersoCarac[Joueur][MANA]--;
		break;
	case 2:
		cout << Personnage[Joueur] << " Coup enrage ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 2.5)*PersoCarac[Joueur][FORCE])*((PersoCarac[Joueur][VITALITE]*10)/ PersoCarac[Joueur][VIE] ));
		Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
			cout << " DOUBLE SNIPE ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 2.5)*PersoCarac[Joueur][FORCE])*((PersoCarac[Joueur][VITALITE] * 10) / PersoCarac[Joueur][VIE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		}

		PersoCarac[Joueur][MANA]--;
		break;
	case 3:

		cout << Personnage[Joueur] << " COUP MARTEAU ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(3.0, 6.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		PersoCarac[Joueur][MANA] -= 3;
		break;
	}
}

void AttaquerSqueletteArcher(int Joueur) {
	int DEGATS;
	int TeamTMP;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	cout << Personnage[Joueur] << " Fleche ! " << endl;
	DEGATS = static_cast<int>(ceil(frand_a_b(0.1+Tour/100.0, 0.2+Tour/50.0)*PersoCarac[Joueur][FORCE]));
	Attaque(DEGATS, CibleAlea(Joueur), Joueur);
	if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
		cout << " DOUBLE FLECHE ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(0.2 + Tour / 50.0, 0.3 + Tour / 33.0)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE) && EquipeEnVie(TeamEnnemie(Joueur)) == true) {
			cout << " TRIPLE FLECHE ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.3 + Tour / 33.0, 0.4 + Tour / 11.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, CibleAlea(Joueur), Joueur);
		}
	}

	
}

void AttaquerCreeper(int Joueur) {
	int DEGATS;
	int TeamTMP;
	int tirage;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	cout << Personnage[Joueur] << " UN CRIPEUR EXPLOSE ! " << endl;
	for (int i = PREMIER; i <= CINQUIEME; i++) {
		tirage = rand_a_b(0, 101);
		if (tirage < 50) {

		}
		else if (tirage >= 50 && tirage < 76) {
			DEGATS = static_cast<int>(ceil(frand_a_b(0.0, 2.5)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
		else if (tirage >= 76 && tirage < 89) {
			DEGATS = static_cast<int>(ceil(frand_a_b(2.5, 5.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
		else if (tirage >= 89 && tirage < 96) {
			DEGATS = static_cast<int>(ceil(frand_a_b(5.0, 10.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
		else if (tirage >= 96 && tirage < 99) {
			DEGATS = static_cast<int>(ceil(frand_a_b(7.5, 15.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
		else {
			DEGATS = static_cast<int>(ceil(frand_a_b(10.0, 20.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}	
	}
	DEGATS = static_cast<int>(ceil(frand_a_b(0.0, 20.0)*PersoCarac[Joueur][FORCE]));
	Attaque(DEGATS, Joueur, Joueur);
}

void AttaquerGhast(int Joueur) {
	int DEGATS;
	int TeamTMP;
	int tirage;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	cout << Personnage[Joueur] << " Attaque de Ghast ! " << endl;
	for (int i = PREMIER; i <= CINQUIEME; i++) {
		
		DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 2.5)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		if (tiragePersoCarac(Joueur, HABILETE)) {
			cout << Personnage[Joueur] << " Brulure ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.25, 0.75)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
		if (tiragePersoCarac(Joueur, HABILETE)) {
			cout << Personnage[Joueur] << " Brulure ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.20, 0.60)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
		if (tiragePersoCarac(Joueur, HABILETE)) {
			cout << Personnage[Joueur] << " Brulure ! " << endl;
			DEGATS = static_cast<int>(ceil(frand_a_b(0.15, 0.45)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
	}
}

void AttaquerZombie(int Joueur) {
	int DEGATS;
	int TeamTMP;
	int tirage;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	cout << Personnage[Joueur] << " Attaque de Zombie ! " << endl;
	int Cible = CibleProche(Joueur);
	DEGATS = static_cast<int>(ceil(frand_a_b(0.0, 0.0 + Tour / 10.0)*PersoCarac[Joueur][FORCE]));
	Attaque(DEGATS, Cible, Joueur);
	if (PersoCarac[Cible][STATUT] == KO) {
		PersoCarac[Cible][STATUT] = EnVie;
		PersoCarac[Cible][VIE] = PersoCarac[Cible][VITALITE] * 10;
		PersoCarac[Cible][EQUIPE] = TEAM2;
	}
}

void AttaquerWitherSquelette(int Joueur) {
	int DEGATS;
	int TeamTMP;
	int tirage;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	cout << Personnage[Joueur] << " Attaque de WitherSquelette ! " << endl;
	int Cible = CibleProche(Joueur);
	PersoCarac[Cible][REDUCTION] -= 10;
	DEGATS = static_cast<int>(ceil(frand_a_b(1.5, 3.5)*PersoCarac[Joueur][FORCE]));
	Attaque(DEGATS, Cible, Joueur);
	cout << Personnage[Joueur] << " Contaminer ! " << endl;
	DEGATS = static_cast<int>(ceil(frand_a_b(0.75, 1.75)*PersoCarac[Joueur][FORCE]));
	Attaque(DEGATS, Cible, Joueur);
	DEGATS = static_cast<int>(ceil(frand_a_b(0.35, 0.7)*PersoCarac[Joueur][FORCE]));
	Attaque(DEGATS, Cible, Joueur);
	DEGATS = static_cast<int>(ceil(frand_a_b(0.15, 0.35)*PersoCarac[Joueur][FORCE]));
	Attaque(DEGATS, Cible, Joueur);
	if (tiragePersoCarac(Joueur, CHANCEDOUBLEATTAQUE)&& EquipeEnVie(TEAM1)) {
		Cible = CibleProche(Joueur);
		PersoCarac[Cible][REDUCTION] -= 10;
		DEGATS = static_cast<int>(ceil(frand_a_b(1.5, 3.5)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Cible, Joueur);
		cout << Personnage[Joueur] << " Contaminer ! " << endl;
		DEGATS = static_cast<int>(ceil(frand_a_b(0.75, 1.75)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Cible, Joueur);
		DEGATS = static_cast<int>(ceil(frand_a_b(0.35, 0.7)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Cible, Joueur);
		DEGATS = static_cast<int>(ceil(frand_a_b(0.15, 0.35)*PersoCarac[Joueur][FORCE]));
		Attaque(DEGATS, Cible, Joueur);
	}
}

void AttaquerWITHER(int Joueur) {
	int DEGATS;
	int TeamTMP;
	int tirage;
	if (PersoCarac[Joueur][EQUIPE] == TEAM1) {
		TeamTMP = TEAM1;
	}
	else {
		TeamTMP = TEAM2;
	}
	cout << Personnage[Joueur] << " Attaque de Whither ! " << endl;
	for (int i = PREMIER; i <= CINQUIEME; i++) {
		if (PersoCarac[Joueur][VIE] < PersoCarac[Joueur][VITALITE] * 5) {
			DEGATS = static_cast<int>(ceil(frand_a_b(3.0, 6.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}
		else {
			DEGATS = static_cast<int>(ceil(frand_a_b(1.0, 2.0)*PersoCarac[Joueur][FORCE]));
			Attaque(DEGATS, Equipe[TeamEnnemie(Joueur)][i], Joueur);
		}			
	}
}

void choixArme(int Joueur) {
	switch(PersoCarac[Joueur][ARME]) {
		case ISIDOOR:
			AttaquerISIDORE(Joueur);
			break;
		case SPARTAN:
			AttaquerSPARTAN(Joueur);
			break;
		case BATON:
			AttaquerBATON(Joueur);
			break;
		case VENTRE:
			AttaquerVENTRE(Joueur);
			break;
		case ALACOOL:
			AttaquerALACOOL(Joueur);
			break;
		case TRUGDOR:
			AttaquerTRUGDOR(Joueur);
			break;
		case DAGUES:
			AttaquerDAGUES(Joueur);
			break;
		case NINI:
			AttaquerNINI(Joueur);
			break;
		case JBI:
			AttaquerJBI(Joueur);
			break;
		case LAPIN:
			AttaquerLAPIN(Joueur);
			break;
		case SANGLIER:
			AttaquerSANGLIER(Joueur);
			break;
		case CERF:
			AttaquerCERF(Joueur);
			break;
		case PETITPONEY:
			AttaquerPETITPONEY(Joueur);
			break;
		case ASALIM:
			AttaquerSALIM(Joueur);
			break;
		case ADRAGON:
			AttaquerDRAGON(Joueur);
			break;
		case KUNGFU:
			AttaquerKUNGFU(Joueur);
			break;
		case TELLURIQUE:
			AttaquerTELLURIQUE(Joueur);
			break;
		case AMAELLE:
			AttaquerMaelle(Joueur);
			break;
		case ADEMO:
			AttaquerDEMO(Joueur);
			break;
		case ELITE:
			AttaquerELITE(Joueur);
			break;
		case GROGNARD:
			AttaquerGROGNARD(Joueur);
			break;
		case CHASSEUR:
			AttaquerCHASSEUR(Joueur);
			break;
		case HUNTER:
			AttaquerHUNTER(Joueur);
			break;
		case BRUTE:
			AttaquerBRUTE(Joueur);
			break;
		case SQUELETEARCHER:
			AttaquerSqueletteArcher(Joueur);
			break;
		case CREEPER:
			AttaquerCreeper(Joueur);
			break;
		case GHAST:
			AttaquerGhast(Joueur);
			break;
		case ZOMBIE:
			AttaquerZombie(Joueur);
			break;
		case WITHERSQUELETTE:
			AttaquerWitherSquelette(Joueur);
			break;
		case WITHER:
			AttaquerWITHER(Joueur);
			break;

	}
}

void InitialiserNiveau(int Joueur) {
	int i=0;
	while (ExperiencesPersonnages[Joueur]>TabXP[i]) {
		i++;
	}
	PersoCarac[Joueur][LVL]=i;
}

int InitialiserChanceCoupCritique(long long int Vitesse) {
	int terme = static_cast<int>(Vitesse);
	int chanceCritique = 0;
	int Multiplicateur = 1;
	while (terme >= 10) {
		chanceCritique += Multiplicateur;
		terme /= 10;
		Multiplicateur *= 4;
	}
	chanceCritique += terme;
	if (chanceCritique > 100) {
		chanceCritique = 100;
	}
	return (chanceCritique);
}

int InitialiserDegatsCritique(long long int Vitesse) {
	int terme = static_cast<int>(Vitesse);
	int DegatsCritique = 0;
	int Multiplicateur = 1;
	while (terme >= 10) {
		DegatsCritique += 10*Multiplicateur;
		terme /= 10;
		Multiplicateur += 1;
	}
	DegatsCritique += terme*Multiplicateur;
	return (DegatsCritique);
}

void InitialiserUnJoueur(string  NomPersonnage,int PersonnageID,int AGILITE_ID,int FORCE_ID,int VITALITE_ID,int ARME_ID,int CHANCEDOUBLEATTAQUE_ID,int HABILETE_ID,int REDUCTION_ID,int ANIMAL_ID=rand_a_b(0,2),int BLOCAGE_ID=0,int DEVIATION_ID=1,int RICOCHET_ID=1,int ESQUIVE_ID=1) {
	Personnage[PersonnageID]=NomPersonnage;
    if(PersonnageID<29){//Si c'est pas un perso que l'on joue on intiatlise son niveau par rapport a son experience
    InitialiserNiveau(PersonnageID);
	}
	PersoCarac[PersonnageID][AGILITE]=(AGILITE_ID+PersoCarac[PersonnageID][ORBEVITESSE1]+PersoCarac[PersonnageID][ORBEVITESSE2]+PersoCarac[PersonnageID][ORBEVITESSE3])*PersoCarac[PersonnageID][LVL];
	PersoCarac[PersonnageID][FORCE]=(FORCE_ID+PersoCarac[PersonnageID][ORBEATTAQUE1]+PersoCarac[PersonnageID][ORBEATTAQUE2]+PersoCarac[PersonnageID][ORBEATTAQUE3])*PersoCarac[PersonnageID][LVL];
	PersoCarac[PersonnageID][VITALITE]=(VITALITE_ID+PersoCarac[PersonnageID][ORBEVIE1]+PersoCarac[PersonnageID][ORBEVIE2]+PersoCarac[PersonnageID][ORBEVIE3])*PersoCarac[PersonnageID][LVL];
	PersoCarac[PersonnageID][ARME]=ARME_ID;
	PersoCarac[PersonnageID][CHANCECRITIQUE]= InitialiserChanceCoupCritique(PersoCarac[PersonnageID][AGILITE]);
	PersoCarac[PersonnageID][DEGATCRITIQUE] = InitialiserDegatsCritique(PersoCarac[PersonnageID][FORCE]);
	PersoCarac[PersonnageID][CHANCEDOUBLEATTAQUE]=CHANCEDOUBLEATTAQUE_ID;
	PersoCarac[PersonnageID][HABILETE]=HABILETE_ID;
	PersoCarac[PersonnageID][REDUCTION]=REDUCTION_ID;
	PersoCarac[PersonnageID][ANIMAL] = ANIMAL_ID;
	PersoCarac[PersonnageID][BLOCAGE] = BLOCAGE_ID;
	PersoCarac[PersonnageID][DEVIATION] = DEVIATION_ID;
	PersoCarac[PersonnageID][RICOCHET] = RICOCHET_ID;
	PersoCarac[PersonnageID][ESQUIVE] = ESQUIVE_ID;
}

void AfficherStat(int Joueur, int Stat,string stat,int C) {
	cout<< Personnage[Joueur] <<"\t:";Colorier(C);cout<<PersoCarac[Joueur][Stat]<<" ";Colorier(NORMAL);cout<<stat<<" \t";
}

void AfficherToutesStats(int J1) {
	AfficherStat(J1,DEGATS,"DEGATS",ROUGE);AfficherStat(J1,SOINS,"SOINS",VERT);AfficherStat(J1,SUBIS,"SUBIS",NORMAL);
}

void PanneauStats(int J1,int J2,int J3,int J4,int J5,int J6,int J7,int J8,int J9,int J10) {

	AfficherToutesStats(J1);cout<<endl;
	AfficherToutesStats(J2);cout<<endl;
	AfficherToutesStats(J3);cout<<endl;
	AfficherToutesStats(J4);cout<<endl;
	AfficherToutesStats(J5);cout<<endl;
	cout<<endl;
	AfficherToutesStats(J6);cout<<endl;
	AfficherToutesStats(J7);cout<<endl;
	AfficherToutesStats(J8);cout<<endl;
	AfficherToutesStats(J9);cout<<endl;
	AfficherToutesStats(J10);cout<<endl;

}

double MultiplicateurCaracXp(int Joueur) {
	return static_cast<double>((1.0 + (PersoCarac[Joueur][CHANCEDOUBLEATTAQUE]*0.2 + PersoCarac[Joueur][HABILETE]*0.2 + PersoCarac[Joueur][REDUCTION] *1.0 + PersoCarac[Joueur][BLOCAGE] *1.0 + PersoCarac[Joueur][DEVIATION] * 1.5 + PersoCarac[Joueur][RICOCHET]*0.5 + PersoCarac[Joueur][ESQUIVE] * 1.0) / 100.0));
}

int SommeCaracXp(int Joueur) {
	return static_cast<int>((PersoCarac[Joueur][FORCE]+PersoCarac[Joueur][AGILITE]+PersoCarac[Joueur][VITALITE])*MultiplicateurCaracXp(Joueur));
}

int SommeCaracXpTeam(int J1,int J2,int J3,int J4,int J5) {
	return SommeCaracXp(J1)+SommeCaracXp(J2)+SommeCaracXp(J3)+SommeCaracXp(J4)+SommeCaracXp(J5);
}

int SommeStats(int Joueur) {
	int S= static_cast<int>(PersoCarac[Joueur][SOINS]+PersoCarac[Joueur][SUBIS]+PersoCarac[Joueur][DEGATS]);
	if(S==0) {
		return 1;
	}
	else {
		return S;
	}

}

void ReinitStats(int Joueur) {
	PersoCarac[Joueur][SOINS]=0;
	PersoCarac[Joueur][SUBIS]=0;
	PersoCarac[Joueur][DEGATS]=0;
}

void ReinitStatsToutJoueur() {
	for(int i=PREMIER;i<=CINQUIEME;i++) {
		ReinitStats(Equipe[TEAM1][i]);
		ReinitStats(Equipe[TEAM2][i]);
	}
}

int SommeStatsToutJoueur(int J1,int J2,int J3,int J4,int J5) {
	return SommeStats(J1)+SommeStats(J2)+SommeStats(J3)+SommeStats(J4)+SommeStats(J5);
}

int SommeStatsPlusExp(int Joueur) {
	return static_cast<int>(ceil((PersoCarac[Joueur][SOINS]+PersoCarac[Joueur][SUBIS]+PersoCarac[Joueur][DEGATS])/100));
}

void AjouterExpJoueur(int Joueur,int ST,int xp) {
	int montant;
	int B=SommeStats(Joueur);
	montant= static_cast<int>(ceil((B/(ST*1.0))*xp));
	if(montant<0) {
		montant=1;
	}
	ExperiencesPersonnages[Joueur] += montant;
	cout<<endl<<Personnage[Joueur]<<" gagne ";Colorier(JAUNE);cout<<montant;Colorier(NORMAL);cout<<" xp "<<endl;
}

void ajouterEXPToutJoueurs(int J1,int J2,int J3,int J4,int J5,int J6,int J7,int J8,int J9,int J10,bool Team1Win) {
	if(Team1Win==true) {
		int ST=SommeStatsToutJoueur(J1,J2,J3,J4,J5);
		int xp= static_cast<int>(ceil(SommeCaracXpTeam(J6,J7,J8,J9,J10)/5.0));

		cout<<endl<<"------ Gain Exp -----"<<endl;
		 AjouterExpJoueur( J1, ST, xp);
		 AjouterExpJoueur( J2, ST, xp);
		 AjouterExpJoueur( J3, ST, xp);
		 AjouterExpJoueur( J4, ST, xp);
		 AjouterExpJoueur( J5, ST, xp);

   }
   else if(EquipeEnVie(TEAM2==true)) {

   		int ST=SommeStatsToutJoueur(J6,J7,J8,J9,J10);
		int xp=static_cast<int>(ceil(SommeCaracXpTeam(J1,J2,J3,J4,J5)/5.0));
		cout<<endl<<"------ Gain Exp -----"<<endl;
		 AjouterExpJoueur( J6, ST, xp);
		 AjouterExpJoueur( J7, ST, xp);
		 AjouterExpJoueur( J8, ST, xp);
		 AjouterExpJoueur( J9, ST, xp);
		 AjouterExpJoueur( J10, ST, xp);
		}
}

bool InitialiserEXP(const string& fichier) {

	ofstream os(fichier);
	long long int UnEntierTresTresLong;
	for(long long int i=0;i<LVLEXP;i++) {


		UnEntierTresTresLong= static_cast<long long int>(100*pow(1.0024,i)-100+3*i*i);
		os<<UnEntierTresTresLong <<endl;
		TabXP[i]= UnEntierTresTresLong;
	}

	os.close();
 	return true;

}

bool InitialiserEXPJoueur(const string& fichier) {

	ofstream os(fichier);
	for(int i=0;i<NBJoueurs;i++) {
		os<<1<<endl;
	}
	os.close();
 	return true;
}

void affichageUnJoueur(int IndiceJoueur) {
	cout<<"\tNumero :"<<IndiceJoueur<<"\t        Pseudo :"<<Personnage[IndiceJoueur]<<" Niveau :"<<PersoCarac[IndiceJoueur][LVL]<<"  \tForce :";Colorier(ROUGE);cout<<PersoCarac[IndiceJoueur][FORCE];Colorier(NORMAL);cout<<" \t     Vitalite :";Colorier(VERT);cout<<PersoCarac[IndiceJoueur][VITALITE]*10;Colorier(NORMAL);cout<<" \tAgilite :";Colorier(JAUNE);cout<<PersoCarac[IndiceJoueur][AGILITE]<<endl;
	Colorier(NORMAL);
	cout<<"\tChance Habilete :";Colorier(JAUNE);cout<<PersoCarac[IndiceJoueur][HABILETE];Colorier(NORMAL);cout<<"%"<<" \tChance Double attaque :"<<PersoCarac[IndiceJoueur][CHANCEDOUBLEATTAQUE]<<"%"<<" \tChance critique :";Colorier(VIOLET);cout<<PersoCarac[IndiceJoueur][CHANCECRITIQUE];Colorier(NORMAL);cout<<"%"<<" \tPourcentage Degat critique :";Colorier(ROUGE);cout<<PersoCarac[IndiceJoueur][DEGATCRITIQUE];Colorier(NORMAL);cout<<"%"<<endl;
	cout << "\tReduction Degats :" << PersoCarac[IndiceJoueur][REDUCTION] << "%" << "\tChance Blocage :"; Colorier(VERT); cout << PersoCarac[IndiceJoueur][BLOCAGE]; Colorier(NORMAL); cout<< "%" << "\tChance Deviation :"; Colorier(VIOLET); cout << PersoCarac[IndiceJoueur][DEVIATION]; Colorier(NORMAL); cout << "%"<< "\tChance Ricochet :"; Colorier(VIOLET); cout << PersoCarac[IndiceJoueur][RICOCHET]; Colorier(NORMAL); cout<< "\tChance Esquive :"; Colorier(JAUNE); cout << PersoCarac[IndiceJoueur][ESQUIVE]; Colorier(NORMAL); cout << "%"<< endl << endl;
}

void afficherToutJoueurs() {
	cout<<endl;
	for(int i=0;i<=12;i++) {
		affichageUnJoueur(i);
	}
}

int choisirUnJoueur(int indice ) {
	int j;
	cout<<" Choisir un joueur "<<endl;
	cin>>j;
	if(!cin.good()) {
			j=NBJoueurs-1;
			cin.clear();
			cin.ignore(256,'\n');
		}
		else if(j<0||j>=NBJoueurs) {
			j=NBJoueurs-1;
		}
	return j;
}

bool ImporterTeam(int Team)
{
	string fichier;
	cout<<endl<<"Donnez nom du fichier"<<endl;
	cin>>fichier;
	fichier=fichier+".txt";
  ifstream is(fichier);
  if (!is)
  {
    cerr<<"Erreur ouverture fichier"<<endl;
    return false;
  }
	int k;
  // lecture tantque possible
  for(int i=0;i<=CINQUIEME;i++) {
  	is>>k;
	Equipe[Team][i]=k;
	PersoCarac[k][EQUIPE]=Team;
  }

  is.close();
  return true;
}

void etablirEquipe(int Team) {
	cout<<endl<<"Team "<<Team+1<< " !"<<endl;
	int j;
	for(int i=PREMIER;i<=CINQUIEME;i++) {
		j=choisirUnJoueur(i);
		Equipe[Team][i]=j;PersoCarac[j][EQUIPE]=Team;
	}
}

void ChoixEquipe() {
	cout<<endl<<"Entrer le nom du fichier texte qui comporte les 5 numeros de votre equipe , 1 par ligne ."<<endl;

		ImporterTeam(TEAM1);
}

void ChoixZone(int &Zone , int & Niveau ) {
	cout<<"Choix zone (max = "<< ZoneMax <<") : ";
	cin>>Zone;
	if(!cin.good()) {
			Zone=1;
			cin.clear();
			cin.ignore(256,'\n');
		}
		else if(Zone<1||Zone>ZoneMax) {
			Zone=1;
		}
	if (Zone == ZoneMax) {
		cout << "Choix Niveau (NiveauMax debloquer = " << NiveauMax << " sur 10 ) : ";
	}
	else {
		cout << "Choix Niveau (NiveauMax debloquer = 10 sur 10 ) : ";
	}
			
	cin>>Niveau;
	if(!cin.good()) {
			Niveau=1;
			cin.clear();
			cin.ignore(256,'\n');
		}
		else if(Zone<ZoneMax) {
			if(Niveau<1||Niveau>10) {
			Niveau=1;
			}
		}
		else if(Niveau<1||Niveau>NiveauMax) {
			Niveau=1;
		}
}

/*void InitEquipe(int PremierE1,int DeuxiemeE1,int TroisiemeE1,int QuatriemeE1,int CinquiemeE1,int PremierE2,int DeuxiemeE2,int TroisiemeE2,int QuatriemeE2,int CinquiemeE2) {
	Equipe[TEAM1][PREMIER]=PremierE1;PersoCarac[PremierE1][EQUIPE]=TEAM1;
	Equipe[TEAM1][DEUXIEME]=DeuxiemeE1;PersoCarac[DeuxiemeE1][EQUIPE]=TEAM1;
	Equipe[TEAM1][TROISIEME]=TroisiemeE1;PersoCarac[TroisiemeE1][EQUIPE]=TEAM1;
	Equipe[TEAM1][QUATRIEME]=QuatriemeE1;PersoCarac[QuatriemeE1][EQUIPE]=TEAM1;
	Equipe[TEAM1][CINQUIEME]=CinquiemeE1;PersoCarac[CinquiemeE1][EQUIPE]=TEAM1;

	Equipe[TEAM2][PREMIER]=PremierE2;PersoCarac[PremierE2][EQUIPE]=TEAM2;
	Equipe[TEAM2][DEUXIEME]=DeuxiemeE2;PersoCarac[DeuxiemeE2][EQUIPE]=TEAM2;
	Equipe[TEAM2][TROISIEME]=TroisiemeE2;PersoCarac[TroisiemeE2][EQUIPE]=TEAM2;
	Equipe[TEAM2][QUATRIEME]=QuatriemeE2;PersoCarac[QuatriemeE2][EQUIPE]=TEAM2;
	Equipe[TEAM2][CINQUIEME]=CinquiemeE2;PersoCarac[CinquiemeE2][EQUIPE]=TEAM2;

	InitQuiJoue(PremierE1,DeuxiemeE1,TroisiemeE1,QuatriemeE1,CinquiemeE1,PremierE2,DeuxiemeE2,TroisiemeE2,QuatriemeE2,CinquiemeE2);
}*/

void InitialiserToutJoueurs() {
	InitialiserUnJoueur("FABIAN",FABIAN,7,7,4,TRUGDOR,20,20,0,OFFENSIF,0,3,17,10);
	InitialiserUnJoueur("THOMAS",THOMAS,1,4,20,VENTRE,20,80,80,DEFENSIF,80,8,10);
	InitialiserUnJoueur("CLOE",CLOE,11,5,3,BATON,25,10,0, DEFENSIF,0,2,7,5);
	InitialiserUnJoueur("MAELLE",MAELLE,2,8,8,AMAELLE,50,50,50, DEFENSIF,20);
	InitialiserUnJoueur("NICOLAS",NICOLAS,8,8,8,NINI,20,20,40, OFFENSIF,20,5,3);
	InitialiserUnJoueur("JB",JB,7,7,7,JBI,1,1,70, DEFENSIF,7,7,7,7);
	InitialiserUnJoueur("SEBASTIEN",SEBASTIEN,15,2,2,SPARTAN,30,15,0, OFFENSIF,1,1,5,5);
	InitialiserUnJoueur("FLO",FLO,2,5,13,ALACOOL,10,30,10, DEFENSIF);
	InitialiserUnJoueur("BRYAN",BRYAN,9,9,1,DAGUES,33,33,-33, OFFENSIF,0,3,7,20);
	InitialiserUnJoueur("SALIM",SALIM,4,4,12,ASALIM,10,10,10, DEFENSIF,0,3,3);
	InitialiserUnJoueur("VICTOR", VICTOR, 1,18,1, KUNGFU, 10, 80, 60, DEFENSIF,50,10);
	InitialiserUnJoueur("ISIDORE", ISIDORE, 15, 1, 5, ISIDOOR, 10, 10, 30, DEFENSIF,10,4,6,30);
	InitialiserUnJoueur("DEMO", DEMO, 5, 5, 10, ADEMO, 0, 10, 0, DEFENSIF,0,15,5);
}

void InitialiserCampagneIa( int  Zone, int  Niveau) {
	//1 switch case zone et 1 switch case niveau dans chaque zone
	switch(Zone) {
		case 1:
				cout<<endl<<"Foret de STAFFELFELDEN"<<endl;
				switch(Niveau) {
					case 1:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=1;InitialiserUnJoueur("LAPIN1 ",S1,3,1,1,LAPIN,5,0,0,OFFENSIF);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=1;InitialiserUnJoueur("LAPIN2 ",S2,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=3;InitialiserUnJoueur("LAPIN3 ",S3,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=1;InitialiserUnJoueur("LAPIN4 ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=1;InitialiserUnJoueur("LAPIN5 ",S5,3,1,1,LAPIN,5,0,0, OFFENSIF);
						break;
					case 2:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=3;InitialiserUnJoueur("LAPIN1",S1,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=2;InitialiserUnJoueur("LAPIN2" ,S2,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=5;InitialiserUnJoueur("LAPIN ADULTE" ,S3,8,2,2,LAPIN,15,0,10, OFFENSIF,10,0,3,3);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=2;InitialiserUnJoueur("LAPIN3 ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=3;InitialiserUnJoueur("LAPIN4 ",S5,3,1,1,LAPIN,5,0,0, OFFENSIF);
						break;
					case 3:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=3;InitialiserUnJoueur("LAPIN ADULTE1 ",S1,8,2,2,LAPIN,15,0,5, OFFENSIF,0,0,3,3);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=3;InitialiserUnJoueur("LAPIN1 ",S2,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=4;InitialiserUnJoueur("GROS LAPIN ",S3,5,5,5,LAPIN,0,25,25, OFFENSIF,25,3);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=3;InitialiserUnJoueur("LAPIN2 ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=3;InitialiserUnJoueur("LAPIN ADULTE2 ",S5,8,2,2,LAPIN,15,0,5, OFFENSIF,0,0,3,3);
						break;
					case 4:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=6;InitialiserUnJoueur("LAPIN ADULTE1" ,S1,8,2,2,LAPIN,15,0,5, OFFENSIF,0,0,3,3);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=4;InitialiserUnJoueur("LAPIN1 ",S2,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=6;InitialiserUnJoueur("GROS LAPIN ",S3,5,5,5,LAPIN,0,25,25, OFFENSIF,25,3);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=4;InitialiserUnJoueur("LAPIN2 ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=6;InitialiserUnJoueur("LAPIN ADULTE2 ",S5,8,2,2,LAPIN,15,0,5, OFFENSIF,0,0,3,3);
						break;
					case 5:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=7;InitialiserUnJoueur("SANGLIER MAl" ,S1,6,8,15,SANGLIER,15,25,25,DEFENSIF,30);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=7;InitialiserUnJoueur("SANGLIER FEMELLE ",S2,9,6,12,SANGLIER,25,15,20, DEFENSIF,30);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=15;InitialiserUnJoueur("Lapin Agile ",S3,15,1,1,LAPIN,50,50,0, OFFENSIF,0,0,10,50);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=8;InitialiserUnJoueur("LAPIN ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=8;InitialiserUnJoueur("LAPIN ADULTE ",S5,8,2,2,LAPIN,15,0,5, OFFENSIF);
						break;
					case 6:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=10;InitialiserUnJoueur("Cerf" ,S1,10,10,10,CERF,15,30,5, OFFENSIF,50,5);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=10;InitialiserUnJoueur("Lapin enragé ",S2,9,9,2,LAPIN,25,25,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=20;InitialiserUnJoueur("Lapin Agile" ,S3,15,1,1,LAPIN,50,50,0, OFFENSIF,0,0,10,50);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=12;InitialiserUnJoueur("LAPIN Chasseur" ,S4,6,6,5,LAPIN,0,30,10, OFFENSIF,10,3,7,15);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=10;InitialiserUnJoueur("Cerf ",S5,10,10,10,CERF,15,30,5, OFFENSIF,25,5);
						break;
					case 7:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=12;InitialiserUnJoueur("Sanglier féroce ",S1,5,12,12,SANGLIER,10,40,10, DEFENSIF,40);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=13;InitialiserUnJoueur("Sanglier colosse ",S2,3,9,18,SANGLIER,0,10,30, DEFENSIF,40);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=22;InitialiserUnJoueur("Cerf volant",S3,15,5,5,CERF,0,50,10, OFFENSIF,10,20,10);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=17;InitialiserUnJoueur("Lapinou ",S4,5,5,5,LAPIN,100,100,90,DEFENSIF,90,10);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=17;InitialiserUnJoueur("Cerf d'acier" ,S5,3,15,15,CERF,0,40,50,DEFENSIF,50,10);
						break;
					case 8:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=20;InitialiserUnJoueur("Lapin d'or ",S1,10,1,30,LAPIN,0,0,80, DEFENSIF);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=15;InitialiserUnJoueur("Oeuf de paque vivant1 ",S2,4,8,10,LAPIN,0,0,30, DEFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=15;InitialiserUnJoueur("Oeuf de paque vivant2 ",S3,4,8,10,LAPIN,0,0,30, DEFENSIF);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=15;InitialiserUnJoueur("Oeuf de paque vivant3 ",S4,4,8,10,LAPIN,0,0,30, DEFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=15;InitialiserUnJoueur("Oeuf de paque vivant4 ",S5,4,8,10,LAPIN,0,0,30, DEFENSIF);
						break;
					case 9:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=25;InitialiserUnJoueur("CERF TOI ",S1,1,1,25,CERF,0,0,60, DEFENSIF,50);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=25;InitialiserUnJoueur("CERF PENTARD ",S2,4,2,4,CERF,0,0,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=30;InitialiserUnJoueur("Roi Des-Cerf ",S3,10,15,10,CERF,50,50,50, DEFENSIF,10);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=25;InitialiserUnJoueur("CERF DAIGLE ",S4,4,2,10,CERF,15,15,30, OFFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=40;InitialiserUnJoueur("CERF A RIEN ",S5,1,1,10,CERF,1,1,99, DEFENSIF,99);
						break;
					case 10:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=30;InitialiserUnJoueur("Petit Poney ",S1,30,30,30,PETITPONEY,30,30,30, DEFENSIF,30);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=25;InitialiserUnJoueur("Sanglier magique ",S2,5,10,10,SANGLIER,0,25,10, DEFENSIF,30);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=25;InitialiserUnJoueur("Cerf enchanté ",S3,10,10,10,CERF,10,10,10, DEFENSIF,30);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=50;InitialiserUnJoueur("Dieu Lapin ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF,0,0,30,30);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=45;InitialiserUnJoueur("Dieu petit Poney ",S5,30,30,30,PETITPONEY,30,30,30, OFFENSIF,30);
						break;
					}
			break;
		case 2:
			cout<<endl<<"Vallee de Munster"<<endl;
			switch(Niveau) {
					case 1:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=45;InitialiserUnJoueur("LOUP1 ",S1,8,8,4,LAPIN,10,10,0, DEFENSIF);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=50;InitialiserUnJoueur("LOUP2 ",S2,8,8,4,LAPIN,10,10,0, DEFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=55;InitialiserUnJoueur("CHEF LOUP ",S3,16,16,8,LAPIN,20,20,10, DEFENSIF,10,1,5,10);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=50;InitialiserUnJoueur("LOUP3 ",S4,8,8,4,LAPIN,10,10,0, DEFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=45;InitialiserUnJoueur("LOUP4 ",S5,8,8,4,LAPIN,10,10,0, DEFENSIF);
						break;
					case 2:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=60;InitialiserUnJoueur("SANGLIER PROTECTEUR1 ",S1,5,10,10,SANGLIER,5,50,0, DEFENSIF,50);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=60;InitialiserUnJoueur("SANGLIER PROTECTEUR2 ",S2,3,15,15,SANGLIER,5,50,25, DEFENSIF,50);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=55;InitialiserUnJoueur("CERF PROTECTEUR1 ",S3,8,8,8,CERF,15,15,5);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=65;InitialiserUnJoueur("CERF PROTECTEUR2 ",S4,3,15,12,CERF,5,75,50, DEFENSIF,75,5);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=75;InitialiserUnJoueur("LAPIN DIVIN ",S5,20,5,5,LAPIN,50,50,50, DEFENSIF,0,0,30,10);
						break;
					case 3:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=60;InitialiserUnJoueur("MORPHEUR1 ",S1,rand_a_b(0,10),rand_a_b(0,10),rand_a_b(0,10),rand_a_b(0,14),rand_a_b(0,10),rand_a_b(0,10),rand_a_b(0,10));
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=70;InitialiserUnJoueur("MORPHEUR2 ",S2,rand_a_b(5,15),rand_a_b(5,15),rand_a_b(5,15),rand_a_b(0,14),rand_a_b(10,20),rand_a_b(10,20),rand_a_b(10,20));
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=80;InitialiserUnJoueur("MORPHEUR3 ",S3,rand_a_b(10,20),rand_a_b(10,20),rand_a_b(10,20),rand_a_b(0,14),rand_a_b(20,80),rand_a_b(20,80),rand_a_b(20,80));
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=70;InitialiserUnJoueur("MORPHEUR4 ",S4,rand_a_b(5,15),rand_a_b(5,15),rand_a_b(5,15),rand_a_b(0,14),rand_a_b(10,20),rand_a_b(10,20),rand_a_b(10,20));
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=60;InitialiserUnJoueur("MORPHEUR5 ",S5,rand_a_b(0,10),rand_a_b(0,10),rand_a_b(0,10),rand_a_b(0,14),rand_a_b(0,10),rand_a_b(0,10),rand_a_b(0,10));
						break;
					case 4:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=80;InitialiserUnJoueur("LAPIN ADULTE1 ",S1,8,2,2,LAPIN,15,0,5, OFFENSIF);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=85;InitialiserUnJoueur("LAPIN1 ",S2,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=100;InitialiserUnJoueur("Rattata ",S3,10,10,10,LAPIN,25,25,25, OFFENSIF,25,3,25,25);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=85;InitialiserUnJoueur("LAPIN2 ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=80;InitialiserUnJoueur("LAPIN ADULTE2 ",S5,8,2,2,LAPIN,15,0,5, OFFENSIF);
						break;
					case 5:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=90;InitialiserUnJoueur("SANGLIER DIVIN ",S1,6,8,15,SANGLIER,15,25,25, DEFENSIF,50);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=90;InitialiserUnJoueur("SANGLIER DIVINE ",S2,9,6,12,SANGLIER,25,15,20, DEFENSIF,50);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=100;InitialiserUnJoueur("BeBe Dragon ",S3,10,10,10,ADRAGON,10,10,10,OFFENSIF,10);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=80;InitialiserUnJoueur("LAPIN DIVIN ",S4,3,1,1,LAPIN,5,0,0, OFFENSIF,0,0,5);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=80;InitialiserUnJoueur("LAPIN DIVIN ADULTE ",S5,8,2,2,LAPIN,15,0,5, OFFENSIF,0,0,15);
						break;
					case 6:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=100;InitialiserUnJoueur("Cerf dechu ",S1,10,10,10,CERF,15,30,5, DEFENSIF,5);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=100;InitialiserUnJoueur("Lapin zombie ",S2,9,9,2,LAPIN,25,25,95, DEFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=125;InitialiserUnJoueur("Lapin Agile ",S3,15,1,1,LAPIN,50,50,0, OFFENSIF,0,0,5,25);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=120;InitialiserUnJoueur("LAPIN Chasseur des cieux ",S4,6,6,5,LAPIN,0,30,10, OFFENSIF,0,0,25);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=100;InitialiserUnJoueur("Cerf dechu 2 ",S5,10,10,10,CERF,15,30,5, OFFENSIF,5);
						break;
					case 7:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=110;InitialiserUnJoueur("Sanglier DIVIN1",S1,5,12,12,SANGLIER,10,40,10, DEFENSIF,30);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=120;InitialiserUnJoueur("Sanglier DIVIN colosse ",S2,3,9,18,SANGLIER,0,10,30, DEFENSIF,30);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=130;InitialiserUnJoueur("Dragon adulte ",S3,20,20,20,ADRAGON,20,20,20);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=170;InitialiserUnJoueur("Lapinou ",S4,5,10,10,LAPIN,100,100,90, DEFENSIF,90);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=155;InitialiserUnJoueur("Cerf diamant ",S5,3,15,15,CERF,0,40,99, DEFENSIF,99,25);
						break;
					case 8:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=150;InitialiserUnJoueur("Lapin d'or ",S1,10,1,25,LAPIN,0,0,80, DEFENSIF);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=125;InitialiserUnJoueur("Oeuf de paque vivant1 ",S2,4,12,10,LAPIN,0,0,30, DEFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=125;InitialiserUnJoueur("Oeuf de paque vivant2 ",S3,4,12,10,LAPIN,0,0,30, DEFENSIF);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=125;InitialiserUnJoueur("Oeuf de paque vivant3 ",S4,4,12,10,LAPIN,0,0,30, DEFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=125;InitialiserUnJoueur("Oeuf de paque vivant4 ",S5,4,12,10,LAPIN,0,0,30, DEFENSIF);
						break;
					case 9:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=160;InitialiserUnJoueur("CERF TOI LEGENDAIRE ",S1,1,1,25,CERF,0,0,60, DEFENSIF,60);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=170;InitialiserUnJoueur("CERF PENTARD LEGENDAIRE ",S2,4,2,4,CERF,0,0,0, OFFENSIF);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=180;InitialiserUnJoueur("Roi Des-Cerf LEGENDAIRE",S3,10,15,10,CERF,50,50,50, DEFENSIF,50);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=170;InitialiserUnJoueur("CERF DAIGLE LEGENDAIRE",S4,4,2,10,CERF,15,15,30, DEFENSIF);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=200;InitialiserUnJoueur("CERF A RIEN LEGENDAIRE ",S5,1,10,30,CERF,0,0,99, DEFENSIF,99);
						break;
					case 10:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=200;InitialiserUnJoueur("Petit Poney ",S1,30,30,30,PETITPONEY,30,30,30, DEFENSIF,30);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=225;InitialiserUnJoueur("Sanglier magique ",S2,5,10,10,SANGLIER,0,25,10, OFFENSIF,10);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=150;InitialiserUnJoueur("DRAGON LEGENDAIRE ",S3,30,30,90,ADRAGON,30,30,30);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=350;InitialiserUnJoueur("Dieu Lapin ",S4,6,6,6,LAPIN,5,0,0, OFFENSIF,0,0,50);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=215;InitialiserUnJoueur("Dieu petit Poney ",S5,30,30,30,PETITPONEY,30,30,30, DEFENSIF,30);
						break;
					}
			break;
		case 3:
			cout<<endl<<"Monde des Dragons"<<endl;
			switch(Niveau) {
					case 1:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=100;InitialiserUnJoueur("LAPIN DRAGON 1 ",S1,25,5,5,LAPIN,10,10,0, OFFENSIF,0,0,10,10);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=100;InitialiserUnJoueur("LAPIN DRAGON 2 ",S2,25,5,5,LAPIN,10,10,0, OFFENSIF,0,0,10,10);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=125;InitialiserUnJoueur("BEBE DRAGON ",S3,8,8,8,ADRAGON,8,8,8);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=100;InitialiserUnJoueur("LAPIN DRAGON 3  ",S4,25,5,5,LAPIN,10,10,0, OFFENSIF,0,0,10,10);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=100;InitialiserUnJoueur("LAPIN DRAGON 4  ",S5,25,5,5,LAPIN,10,10,0, OFFENSIF,0,0,10,10);
						break;
					case 2:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=125;InitialiserUnJoueur("DRAGON 1 ",S1,12,12,12,ADRAGON,12,12,12);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=135;InitialiserUnJoueur("BEBE DRAGON 1 ",S2,8,8,8,ADRAGON,8,8,8);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=150;InitialiserUnJoueur("GRAND DRAGON ",S3,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=135;InitialiserUnJoueur("BEBE DRAGON 2 ",S4,8,8,8,ADRAGON,8,8,8);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=125;InitialiserUnJoueur("DRAGON 2 ",S5,12,12,12,ADRAGON,12,12,12);
						break;
					case 3:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=150;InitialiserUnJoueur("GRAND DRAGON 1 ",S1,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=160;InitialiserUnJoueur("DRAGON 1 ",S2,12,12,12,ADRAGON,12,12,12);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=180;InitialiserUnJoueur("DRAGON NOIR  ",S3,17,17,17,ADRAGON,17,17,17);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=160;InitialiserUnJoueur("DRAGON 2 ",S4,12,12,12,ADRAGON,12,12,12);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=150;InitialiserUnJoueur("DRAGON PONEY ",S5,30,30,30,PETITPONEY,30,30,30,DEFENSIF,30);
						break;
					case 4:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=180;InitialiserUnJoueur("GRAND DRAGON 1 ",S1,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=190;InitialiserUnJoueur("GRAND DRAGON 2 ",S2,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=200;InitialiserUnJoueur("DRAGON DEMERAUDE ",S3,18,18,18,ADRAGON,18,18,18);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=190;InitialiserUnJoueur("GRAND DRAGON 3 ",S4,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=250;InitialiserUnJoueur(" DRAGON JB ",S5,7,7,7,JBI,7,7,7,DEFENSIF,7,7,7,7);
						break;
					case 5:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=200;InitialiserUnJoueur("GRAND DRAGON 1 ",S1,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=300;InitialiserUnJoueur("GRAND DRAGON LAPIN ",S2,30,30,30,LAPIN,30,30,30,OFFENSIF,0,0,30);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=250;InitialiserUnJoueur("TABALUGA ",S3,19,19,19,ADRAGON,19,19,19);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=225;InitialiserUnJoueur("GRAND DRAGON 3 ",S4,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=200;InitialiserUnJoueur("GRAND DRAGON 4",S5,16,16,16,ADRAGON,16,16,16);
						break;
					case 6:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=250;InitialiserUnJoueur("GRAND DRAGON SANGLIER ",S1,30,30,30,SANGLIER,30,30,30,DEFENSIF,30);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=275;InitialiserUnJoueur("GRAND DRAGON 2 ",S2,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=300;InitialiserUnJoueur("DRAGON DE JADE ",S3,20,20,20,ADRAGON,20,20,20);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=275;InitialiserUnJoueur("GRAND DRAGON 3 ",S4,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=200;InitialiserUnJoueur("GRAND DRAGON 4",S5,16,16,16,ADRAGON,16,16,16);
						break;
					case 7:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=275;InitialiserUnJoueur("GRAND DRAGON 1 ",S1,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=300;InitialiserUnJoueur("GRAND DRAGON 2 ",S2,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=325;InitialiserUnJoueur("GALENOR ",S3,21,21,21,ADRAGON,21,21,21);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=340;InitialiserUnJoueur("GRAND DRAGON CERF ",S4,30,30,30,CERF,30,30,30,DEFENSIF,30,6);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=275;InitialiserUnJoueur("GRAND DRAGON 4",S5,16,16,16,ADRAGON,16,16,16);
						break;
					case 8:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=300;InitialiserUnJoueur("GRAND DRAGON 1 ",S1,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=325;InitialiserUnJoueur("GRAND DRAGON 2 ",S2,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=350;InitialiserUnJoueur("EREL ",S3,22,22,22,ADRAGON,22,22,22);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=325;InitialiserUnJoueur("GRAND DRAGON 3",S4,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=300;InitialiserUnJoueur("GRAND DRAGON PETEUR ",S5,25,25,25,VENTRE,25,16,80,DEFENSIF,80,5,15);
						break;
					case 9:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=350;InitialiserUnJoueur("GRAND DRAGON 1 ",S1,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=375;InitialiserUnJoueur("GRAND DRAGON 2 ",S2,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=400;InitialiserUnJoueur("THALLASYON ",S3,23,23,23,ADRAGON,23,23,90);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=375;InitialiserUnJoueur("GRAND DRAGON 3 ",S4,16,16,16,ADRAGON,16,16,16);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=350;InitialiserUnJoueur("GRAND DRAGON 4",S5,16,16,16,ADRAGON,16,16,16);
						break;
					case 10:
						cout<<endl<<"Niveau "<<Niveau<<" : "<<endl;
						Equipe[TEAM2][PREMIER]=S1;PersoCarac[S1][EQUIPE]=TEAM2;PersoCarac[S1][LVL]=400;InitialiserUnJoueur("OCTANOS ",S1,24,24,24,ADRAGON,24,24,24);
						Equipe[TEAM2][DEUXIEME]=S2;PersoCarac[S2][EQUIPE]=TEAM2;PersoCarac[S2][LVL]=450;InitialiserUnJoueur("LAGIACRUS ",S2,25,25,25,ADRAGON,25,25,25);
						Equipe[TEAM2][TROISIEME]=S3;PersoCarac[S3][EQUIPE]=TEAM2;PersoCarac[S3][LVL]=500;InitialiserUnJoueur("SPYRO ",S3,26,26,96,ADRAGON,26,26,26);
						Equipe[TEAM2][QUATRIEME]=S4;PersoCarac[S4][EQUIPE]=TEAM2;PersoCarac[S4][LVL]=450;InitialiserUnJoueur("INORA ",S4,25,25,25,ADRAGON,25,25,25);
						Equipe[TEAM2][CINQUIEME]=S5;PersoCarac[S5][EQUIPE]=TEAM2;PersoCarac[S5][LVL]=400;InitialiserUnJoueur("ERIMATRA ",S5,24,24,24,ADRAGON,24,24,24);
						break;
					}
			break;
		case 4:
			cout << endl << "Monde Tellurique" << endl;
			switch (Niveau) {
			case 1:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 500; InitialiserUnJoueur("MUR 1 ", S1, 1, 99, 99, JBI, 10, 10,99, DEFENSIF,99);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 500; InitialiserUnJoueur("MUR 2 ", S2, 1, 99, 99, JBI, 10, 10, 99, DEFENSIF,99);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 500; InitialiserUnJoueur("MUR ", S3, 1, 99, 99, JBI, 10, 10, 99, DEFENSIF,99);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 500; InitialiserUnJoueur("MUR 3 ", S4, 1, 99, 99, JBI, 10, 10, 99, DEFENSIF,99);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 500; InitialiserUnJoueur("MUR 4 ", S5, 1, 99, 99, JBI, 10, 10, 99, DEFENSIF,99);
				break;
			case 2:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 500; InitialiserUnJoueur("DRAGON 1 ", S1, 12, 12, 12, ADRAGON, 12, 12, 12);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 510; InitialiserUnJoueur("BEBE DRAGON 1 ", S2, 8, 8, 8, ADRAGON, 8, 8, 8);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 520; InitialiserUnJoueur("WYRM ", S3, 17, 17, 17, TELLURIQUE, 17, 17, 17);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 510; InitialiserUnJoueur("BEBE DRAGON 2 ", S4, 8, 8, 8, ADRAGON, 8, 8, 8);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 500; InitialiserUnJoueur("DRAGON 2 ", S5, 12, 12, 12, ADRAGON, 12, 12, 12);
				break;
			case 3:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 510; InitialiserUnJoueur(" DRAGON DIAMANT ", S1, 1, 20, 40, ADRAGON, 0, 0, 97);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 520; InitialiserUnJoueur("DRAGON 1 ", S2, 12, 12, 12, ADRAGON, 12, 12, 12);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 530; InitialiserUnJoueur("DRAGON NOIR TELLURIQUE  ", S3, 18, 18, 18, TELLURIQUE, 18, 18, 18);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 520; InitialiserUnJoueur("DRAGON 2 ", S4, 12, 12, 12, ADRAGON, 12, 12, 12);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 510; InitialiserUnJoueur("GRAND DRAGON 2 ", S5,16, 16, 16, ADRAGON, 16, 16, 16);
				break;
			case 4:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 530; InitialiserUnJoueur("GRAND DRAGON 1 ", S1, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 540; InitialiserUnJoueur("GRAND DRAGON 2 ", S2, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 550; InitialiserUnJoueur("DRAGON DEMERAUDE TELLURIQUE ", S3, 19, 19, 19, TELLURIQUE, 50, 50, 50);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 540; InitialiserUnJoueur("GRAND DRAGON 3 ", S4, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 530; InitialiserUnJoueur("GRAND DRAGON CLOE ", S5, 30, 30, 30, BATON, 30, 30, 30,OFFENSIF,0,0,5);
				break;
			case 5:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 550; InitialiserUnJoueur("GRAND DRAGON 1 ", S1, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 525; InitialiserUnJoueur("GRAND DRAGON SEB ", S2, 30, 30, 30, SPARTAN, 30, 30, 30, OFFENSIF, 0,0,30,30);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 550; InitialiserUnJoueur("TABALUGA ", S3, 20, 20, 20, TELLURIQUE, 20, 20, 20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 505; InitialiserUnJoueur("GRAND DRAGON 3 ", S4, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 500; InitialiserUnJoueur("GRAND DRAGON 4 ", S5, 16, 16, 16, ADRAGON, 16, 16, 16);
				break;
			case 6:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 550; InitialiserUnJoueur("GRAND DRAGON VICTOR ", S1, 30, 30, 30, KUNGFU, 30, 30, 30,DEFENSIF,30,10,5);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 575; InitialiserUnJoueur("GRAND DRAGON 2 ", S2, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 575; InitialiserUnJoueur("DRAGON DE JADE ", S3, 21, 21, 21, TELLURIQUE, 21, 21, 21);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 575; InitialiserUnJoueur("GRAND DRAGON 3 ", S4, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 500; InitialiserUnJoueur("GRAND DRAGON 4 ", S5, 16, 16, 16, ADRAGON, 16, 16, 16);
				break;
			case 7:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 557; InitialiserUnJoueur("GRAND DRAGON 1 ", S1, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 580; InitialiserUnJoueur("GRAND DRAGON 2 ", S2, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 600; InitialiserUnJoueur("GALENOR ", S3, 22, 22, 22, TELLURIQUE, 22, 22, 22);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 558; InitialiserUnJoueur("GRAND DRAGON SAGE FABIAN ", S4, 30, 30, 30, TRUGDOR, 30, 30, 30,OFFENSIF,10,10,70,10);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 575; InitialiserUnJoueur("GRAND DRAGON 4 ", S5, 16, 16, 16, ADRAGON, 16, 16, 16);
				break;
			case 8:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 580; InitialiserUnJoueur("THOMAS THE TANK ENGINE ", S1, 1, 99, 99, ADRAGON, 30, 30, 80,DEFENSIF,80,30,15);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 555; InitialiserUnJoueur("GRAND DRAGON 2 ", S2, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 620; InitialiserUnJoueur("EREL ", S3, 23, 23, 23, TELLURIQUE, 23, 23, 23);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 595; InitialiserUnJoueur("GRAND DRAGON 3 ", S4, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 580; InitialiserUnJoueur("GRAND DRAGON 4 ", S5, 16, 16, 16, ADRAGON, 16, 16, 16);
				break;
			case 9:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 600; InitialiserUnJoueur("GRAND DRAGON 1 ", S1, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] =605; InitialiserUnJoueur("GRAND DRAGON 2 ", S2, 16, 16, 16, ADRAGON, 16, 16, 16);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 650; InitialiserUnJoueur("THALLASYON ", S3, 24, 24, 24, TELLURIQUE, 24, 24, 24);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 625; InitialiserUnJoueur("GRAND DRAGON NICO LE SURVIVANT ", S4, 30, 30, 30, NINI, 30, 30, 30,OFFENSIF,30,3,3);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 610; InitialiserUnJoueur("GRAND DRAGON 4 ", S5, 16, 16, 16, ADRAGON, 16, 16, 16);
				break;
			case 10:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 600; InitialiserUnJoueur("OCTANOS ", S1, 25, 25, 25, ADRAGON, 25, 25, 25);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 650; InitialiserUnJoueur("LAGIACRUS ", S2, 27, 27, 27, ADRAGON, 27, 27, 27);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 700; InitialiserUnJoueur("SPYRO TTT ", S3, 29,29, 99, TELLURIQUE, 29, 29,29);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 650; InitialiserUnJoueur("INORA THE BRYAN ", S4, 60, 60, 1, ADRAGON, 30, 30, -30,DEFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 600; InitialiserUnJoueur("ERIMATRA ", S5, 26, 26, 26, ADRAGON, 26, 26, 26);
				break;
			}
			break;
		case 5:
			cout << endl << "Mode boss, monde miroir" << endl;
			switch (Niveau) {
			case 1:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;  
				Equipe[TEAM2][DEUXIEME] = S1; 
				Equipe[TEAM2][TROISIEME] = S1; 
				Equipe[TEAM2][QUATRIEME] = S1; 
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 700; InitialiserUnJoueur("EASYDOOR  ", S1, 50, 10, 300, ISIDOOR, 50, 50, 75, DEFENSIF,75,5,5,50);
				break;
			case 2:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 750; InitialiserUnJoueur(" PERE DE NICO TRES FURIEUX  ", S1, 33, 33, 330, DEMO, 33, 33,33, DEFENSIF,33,7,3,10);
				break;
			case 3:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 800; InitialiserUnJoueur(" VICTOR HUGOT  ", S1, 20, 40, 250, KUNGFU, 100, 50, 90, DEFENSIF,90,10,1);
				
				break;
			case 4:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 850; InitialiserUnJoueur(" GRAND SALIMALEKUM  ", S1, 30, 30, 400, ASALIM, 40, 40, 60, DEFENSIF,60,3,3);
				break;
			case 5:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 900; InitialiserUnJoueur(" BRYAN IN THE KITCHEN  ", S1, 44, 44, 100, DAGUES, 75, 75, 0, OFFENSIF,0,0,7,70);

				break;
			case 6:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 950; InitialiserUnJoueur(" FLO D'ENFER  ", S1, 5, 45, 200, ALACOOL, 10, 80, 20, DEFENSIF);
				break;
			case 7:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1000; InitialiserUnJoueur(" SEB LA FRITE  ", S1, 50, 10, 150, SPARTAN, 80, 20, 0, OFFENSIF,0,0,12,30);
				break;
			case 8:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1050; InitialiserUnJoueur(" JB LE SOLIDE  ", S1, 50, 10, 500, JBI, 50, 50, 99, DEFENSIF,99,9,9,9);
				break;
			case 9:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1100; InitialiserUnJoueur(" NICOOLA  ", S1, 32, 32, 750, NINI, 50, 50, 50, OFFENSIF,50,5,5);
				break;
			case 10:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1;
				Equipe[TEAM2][DEUXIEME] = S1;
				Equipe[TEAM2][TROISIEME] = S1;
				Equipe[TEAM2][QUATRIEME] = S1;
				Equipe[TEAM2][CINQUIEME] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1150; InitialiserUnJoueur(" MAELLE LA TYRANIQUE  ", S1, 35, 35, 650, AMAELLE, 50, 50, 50, DEFENSIF,50);
				break;
			}
			break;
		case 6:
			cout << endl << "Monde HALO" << endl;
			switch (Niveau) {
			case 1:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1200; InitialiserUnJoueur("Elite *  ", S1, 3, 10, 10, ELITE, 10, 10, 10, DEFENSIF,10,1,5,4);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1200; InitialiserUnJoueur("Grognard * 1 ", S2, 10, 1, 1, GROGNARD, 10, 0, 0,OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1200; InitialiserUnJoueur("Grognard * 2 ", S3, 10, 1,1, GROGNARD, 10, 0, 0, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1200; InitialiserUnJoueur("Grognard * 3  ", S4, 10, 1, 1, GROGNARD, 10, 0, 0, OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1200; InitialiserUnJoueur("Grognard * 4  ", S5, 10, 1, 1, GROGNARD, 10, 0, 0, OFFENSIF);
				break;
			case 2:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1210; InitialiserUnJoueur("Elite * *  ", S1, 5, 12, 12, ELITE, 20, 20, 20,DEFENSIF,20,1,5,8);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1210; InitialiserUnJoueur("Grognard * * 1 ", S2, 15, 1, 1, GROGNARD, 20, 0, 0,OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1210; InitialiserUnJoueur("Grognard * * 2 ", S3, 15, 1, 1, GROGNARD, 20, 0, 0,OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1210; InitialiserUnJoueur("Chasseur * ", S4, 8, 8, 1, CHASSEUR, 2, 2, 0,OFFENSIF,50,10,10,4);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1210; InitialiserUnJoueur("Grognard * * 3 ", S5, 15, 1, 1, GROGNARD, 20, 0, 0,OFFENSIF);
				break;
			case 3:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1220; InitialiserUnJoueur("HUNTER * 1 ", S1, 2, 20, 20, HUNTER, 5, 20, 20,DEFENSIF,20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1220; InitialiserUnJoueur("HUNTER * 2 ", S2, 2, 20, 20, HUNTER, 5, 20, 20,DEFENSIF,20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1220; InitialiserUnJoueur("Chasseur * * 1  ", S3, 10, 10, 1, CHASSEUR, 4, 4, 1,OFFENSIF,50,10,10,8);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1220; InitialiserUnJoueur("Chasseur * * 2 ", S4, 10, 10, 1, CHASSEUR, 4, 4, 1,OFFENSIF,50,10,10,8);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1220; InitialiserUnJoueur("Chasseur * * 3 ", S5, 10, 10, 1, CHASSEUR, 4, 4, 1,OFFENSIF,50,10,10,8);
				break;
			case 4:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1230; InitialiserUnJoueur("Brute 1 * ", S1, 4, 12, 8, BRUTE, 10, 10, 10,OFFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1230; InitialiserUnJoueur("Brute 2 * ", S2, 4, 12, 8, BRUTE, 10, 10, 10,OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1230; InitialiserUnJoueur("Brute 3 * ", S3, 4, 12, 8, BRUTE, 10, 10, 10,OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1230; InitialiserUnJoueur("Brute 4 * ", S4, 4, 12, 8, BRUTE, 10, 10, 10,OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1230; InitialiserUnJoueur("Brute 5 * ", S5, 4, 12, 8, BRUTE, 10, 10, 10, OFFENSIF);
				break;
			case 5:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1240; InitialiserUnJoueur("HUNTER 1 * * ", S1, 3, 22, 22, HUNTER, 10, 40, 40,DEFENSIF,40);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1240; InitialiserUnJoueur("HUNTER 2 * * ", S2, 3, 22, 22,HUNTER, 10, 40, 40,DEFENSIF,40);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1240; InitialiserUnJoueur("Grognard 1 * * * ", S3, 20, 2, 2, GROGNARD, 40, 10, 10,OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1240; InitialiserUnJoueur("Grognard 2 * * * ", S4, 20, 2, 2, GROGNARD, 40, 10, 10,OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1240; InitialiserUnJoueur("Grognard 3 * * * ", S5, 20, 2, 2, GROGNARD, 40, 10, 10,OFFENSIF);
				break;
			case 6:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1250; InitialiserUnJoueur("ELITE * * * ", S1, 7, 16, 16, ELITE, 30, 30, 30,DEFENSIF,30,1,5,12);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1250; InitialiserUnJoueur("Grognard 1 * * * * ", S2, 25, 2, 2, GROGNARD, 80, 20, 20,OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1250; InitialiserUnJoueur("Grognard 2 * * *  ", S3, 25, 2, 2, GROGNARD, 80, 20, 20,OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1250; InitialiserUnJoueur("Chasseur * * * ", S4, 12, 12, 2, CHASSEUR, 8, 8, 2,OFFENSIF,50,10,10,12);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1250; InitialiserUnJoueur("Grognard 3 * * * * ", S5, 25, 2, 2, GROGNARD, 80, 20, 20,OFFENSIF);
				break;
			case 7:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1260; InitialiserUnJoueur("Brute 1 * * ", S1, 5, 16, 10, BRUTE, 20, 20, 20,OFFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1260; InitialiserUnJoueur("Brute 2 * * ", S2, 5, 16, 10, BRUTE, 20, 20, 20,OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1260; InitialiserUnJoueur("Brute 3 * * ", S3, 5, 16, 10, BRUTE, 20, 20, 20,OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1260; InitialiserUnJoueur("Brute 4 * * ", S4, 5, 16, 10, BRUTE, 20, 20, 20,OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1260; InitialiserUnJoueur("Chasseur * * * * ", S5, 16, 16, 3, CHASSEUR, 16, 16, 4,OFFENSIF,50,10,10,16);
				break;
			case 8:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1270; InitialiserUnJoueur("Brute 1 * * * ", S1, 7, 21, 13, BRUTE, 30, 30, 30,OFFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1270; InitialiserUnJoueur("Brute 2 * * * ", S2, 7, 21, 13, BRUTE, 30, 30, 30,OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1270; InitialiserUnJoueur("Brute 3 * * * ", S3, 7, 21, 13, BRUTE, 30, 30, 30,OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1270; InitialiserUnJoueur("Chasseur 1 * * * * * ", S4, 20, 20, 5, CHASSEUR,32, 32, 8,OFFENSIF,50,10,10,20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1270; InitialiserUnJoueur("Chasseur 2 * * * * * ", S5, 20, 20, 5, CHASSEUR, 32, 32, 8,OFFENSIF,50,10,10,20);
				break;
			case 9:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1280; InitialiserUnJoueur("Hunter 1 * * * ", S1, 6, 26, 26, HUNTER, 15, 60, 60,DEFENSIF,60);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1280; InitialiserUnJoueur("Hunter 2 * * * ", S2, 6, 26, 26, HUNTER, 15, 60, 60,DEFENSIF,60);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1280; InitialiserUnJoueur("Elite 1 * * * * ", S3, 10, 20, 20, ELITE, 40, 40, 40,DEFENSIF,40,0,5,16);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1280; InitialiserUnJoueur("Elite 2 * * * * ", S4, 10, 20, 20, ELITE, 40, 40, 40,DEFENSIF,40,0,5,16);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1280; InitialiserUnJoueur("Grognard * * * * * ", S5, 30, 3, 3, GROGNARD, 100, 30, 30,OFFENSIF);
				break;
			case 10:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1290; InitialiserUnJoueur("Brute 1 * * * * * ", S1, 15, 35, 20,BRUTE, 50, 50, 50,OFFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1290; InitialiserUnJoueur("Brute 2 * * * * * ", S2, 15, 35, 20, BRUTE, 50, 50, 50, OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1290; InitialiserUnJoueur("Brute 3 * * * * * ", S3, 15, 35, 60, BRUTE, 50, 50, 50, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1290; InitialiserUnJoueur("Brute 4 * * * * * ", S4, 15, 35, 20, BRUTE, 50, 50, 50, OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1290; InitialiserUnJoueur("Brute 5 * * * * * ", S5, 15, 35, 20, BRUTE, 50, 50, 50, OFFENSIF);
				break;
			}
			break;
		case 7:
			cout << endl << "Monde HALO (LEGENDAIRE) " << endl;
			switch (Niveau) {
			case 1:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1300; InitialiserUnJoueur("Grognard * * * * *  ", S1, 30, 9, 3, GROGNARD, 100, 30, 30, DEFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1300; InitialiserUnJoueur("Grognard * * * * * 1 ", S2, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1300; InitialiserUnJoueur("Grognard * * * * *  2 ", S3, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1300; InitialiserUnJoueur("Grognard * * * * * 3  ", S4, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1300; InitialiserUnJoueur("Grognard * * * * * 4  ", S5, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				break;
			case 2:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1310; InitialiserUnJoueur("Elite * * * * *  ", S1, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1310; InitialiserUnJoueur("Elite * * * * * 1 ", S2, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1310; InitialiserUnJoueur("Grognard * * * * * 2 ", S3, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1310; InitialiserUnJoueur("Grognard * * * * *  ", S4, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1310; InitialiserUnJoueur("Grognard * * * * * 3 ", S5, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				break;
			case 3:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1320; InitialiserUnJoueur("HUNTER * * * * * 1 ", S1, 14, 40, 40, HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1320; InitialiserUnJoueur("HUNTER * * * * * 2 ", S2, 14, 40, 40, HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1320; InitialiserUnJoueur("Chasseur * * * * * 1  ", S3, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1320; InitialiserUnJoueur("Elite * * * * * 1 ", S4, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1320; InitialiserUnJoueur("Elite * * * * * 2 ", S5, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50);
				break;
			case 4:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1330; InitialiserUnJoueur("Brute 1 * * * * *", S1, 15, 35, 20, BRUTE, 50, 50, 50, OFFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1330; InitialiserUnJoueur("Brute 2 * * * * *", S2, 15, 35, 20, BRUTE, 50, 50, 50, OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1330; InitialiserUnJoueur("Brute 3 * * * * * ", S3, 15, 35,20, BRUTE, 50, 50, 50, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1330; InitialiserUnJoueur("Brute 4 * * * * * ", S4, 15, 35,20, BRUTE, 50, 50, 50, OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1330; InitialiserUnJoueur("Brute 5 * * * * * ", S5, 15, 35,20, BRUTE, 50, 50, 50, OFFENSIF);
				break;
			case 5:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1340; InitialiserUnJoueur("Elite 1 * * * * * ", S1, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1340; InitialiserUnJoueur("Elite 2 * * * * * ", S2, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1340; InitialiserUnJoueur("Grognard 1 * * * * * ", S3, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1340; InitialiserUnJoueur("Chasseur  * * * * * ", S4, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1340; InitialiserUnJoueur("Grognard 2 * * * * * ", S5, 30, 9, 3, GROGNARD, 100, 30, 30, OFFENSIF);
				break;
			case 6:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1350; InitialiserUnJoueur("ELITE * * * * * 1 ", S1, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1350; InitialiserUnJoueur("ELITE * * * * * 2", S2, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1350; InitialiserUnJoueur("ELITE * * * * * 3 ", S3, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1350; InitialiserUnJoueur("ELITE * * * * * 4 ", S4, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1350; InitialiserUnJoueur("Chasseur * * * * ", S5, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				break;
			case 7:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1360; InitialiserUnJoueur("Hunter 1 * * * * * ", S1, 14,40,40,HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1360; InitialiserUnJoueur("Hunter 2 * * * * * ", S2, 14, 40, 40, HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1360; InitialiserUnJoueur("Chasseur 1 * * * * * ", S3, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1360; InitialiserUnJoueur("Chasseur 2 * * * * * ", S4, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1360; InitialiserUnJoueur("Chasseur * * * *  * ", S5,25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				break;
			case 8:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1370; InitialiserUnJoueur("Hunter 1 * * * * * ", S1, 14, 40, 40, HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1370; InitialiserUnJoueur("Hunter 2 * * * * * ", S2, 14, 40, 40, HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1370; InitialiserUnJoueur("Hunter 3 * * * * * ", S3, 14, 40, 40, HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1370; InitialiserUnJoueur("Hunter 4 * * * * * ", S4, 14, 40, 40, HUNTER, 25, 99, 99, DEFENSIF,99);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1370; InitialiserUnJoueur("Grognard  * * * * * ", S5, 30, 9, 3,GROGNARD, 100, 30, 30, OFFENSIF);
				break;
			case 9:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1380; InitialiserUnJoueur("Elite 4 * * * * * ", S1, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1380; InitialiserUnJoueur("Elite 3 * * * * * ", S2, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1380; InitialiserUnJoueur("Elite 1 * * * * * ", S3, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1380; InitialiserUnJoueur("Elite 2 * * * * * ", S4, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1380; InitialiserUnJoueur("Elite 5 * * * * * ", S5, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50,0,5,20);
				break;
			case 10:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1390; InitialiserUnJoueur("Elite 1 * * * * * ", S1, 15, 30, 30, ELITE, 50, 50, 50, DEFENSIF,50);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1390; InitialiserUnJoueur("Chassaur 1 * * * * * ", S2, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1390; InitialiserUnJoueur("Chassaur 2 * * * * * ", S3, 25, 25, 50, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1390; InitialiserUnJoueur("Chassaur 3 * * * * * ", S4, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1390; InitialiserUnJoueur("Chassaur 4 * * * * * ", S5, 25, 25, 5, CHASSEUR, 40, 40, 20, OFFENSIF,50,10,10,20);
				break;
			}
			break;
		case 8:
			cout << endl << "Monde Minecraft " << endl;
			switch (Niveau) {
			case 1:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1; InitialiserUnJoueur("Lapin  ", S1, 30, 9, 3, LAPIN, 100, 30, 30, DEFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1; InitialiserUnJoueur("Cochon ", S2, 30, 9, 3, LAPIN, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1; InitialiserUnJoueur("Mouton ", S3, 30, 9, 3,LAPIN, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1; InitialiserUnJoueur("Brin d'herbe", S4, 30, 9, 3, LAPIN, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 0; InitialiserUnJoueur("Sebastien", S5, 30, 9, 3,LAPIN, 100, 30, 30, OFFENSIF);
				break;
			case 2:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1440; InitialiserUnJoueur("SqueletteArcher1 ", S1, 20, 20, 10, SQUELETEARCHER, 50, 10, 10,OFFENSIF, 5,3,20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1440; InitialiserUnJoueur("SqueletteArcher2 ", S2, 20, 20, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5,3,20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1440; InitialiserUnJoueur("SqueletteArcher3 ", S3, 20, 20, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF,5,3,20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1440; InitialiserUnJoueur("SqueletteArcher4  ", S4, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF,5,3,20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1440; InitialiserUnJoueur("SqueletteArcher5 ", S5, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF,5,3,20);
				break;
			case 3:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1460; InitialiserUnJoueur("Arraignee1 ", S1, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1460; InitialiserUnJoueur("Arraignee2 ", S2, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1460; InitialiserUnJoueur("Arraignee3 ", S3, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1460; InitialiserUnJoueur("Arraignee4  ", S4, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1460; InitialiserUnJoueur("Arraignee5 ", S5, 30, 12, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				break;
			case 4:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1480; InitialiserUnJoueur("Zombie1 ", S1, 5, 15,15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1480; InitialiserUnJoueur("Zombie2  ", S2, 5, 15,15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1480; InitialiserUnJoueur("Zombie3  ", S3, 5, 15,15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1480; InitialiserUnJoueur("Zombie4   ", S4, 5, 15,15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1480; InitialiserUnJoueur("Zombie5  ", S5, 5, 15,15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				break;
			case 5:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1500; InitialiserUnJoueur("Zombie1 ", S1, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1500; InitialiserUnJoueur("Zombie2  ", S2, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1500; InitialiserUnJoueur("Cri-peur ", S3, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1500; InitialiserUnJoueur("SqueletteArcher4  ", S4, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1500; InitialiserUnJoueur("SqueletteArcher5 ", S5, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				break;
			case 6:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1520; InitialiserUnJoueur("Cri-peur ", S1, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1520; InitialiserUnJoueur("Cri-peur2 ", S2, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1520; InitialiserUnJoueur("Cri-peur3 ", S3, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1520; InitialiserUnJoueur("Cri-peur4 ", S4, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1520; InitialiserUnJoueur("Cri-peur5 ", S5, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				break;
			case 7:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1540; InitialiserUnJoueur("Zombie1 ", S1, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1540; InitialiserUnJoueur("Zombie2  ", S2, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1540; InitialiserUnJoueur("Ghast ", S3, 15, 15, 15, GHAST, 50, 0, 15, OFFENSIF, 15, 5, 15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1540; InitialiserUnJoueur("SqueletteArcher4  ", S4, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1540; InitialiserUnJoueur("SqueletteArcher5 ", S5, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				break;
			case 8:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1560; InitialiserUnJoueur("Zombie1 ", S1, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S2; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1560; InitialiserUnJoueur("Ghast ", S2, 15, 15, 15, GHAST, 50, 0, 15, OFFENSIF, 15, 5, 15);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1560; InitialiserUnJoueur("Ghast2 ", S3, 15, 15, 15, GHAST, 50, 0, 15, OFFENSIF, 15, 5, 15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1560; InitialiserUnJoueur("WitherSquelette1  ", S4, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1560; InitialiserUnJoueur("WitherSquelette2 ", S5, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
			case 9:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1580; InitialiserUnJoueur("WitherSquelette1  ", S1, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S2; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1580; InitialiserUnJoueur("WitherSquelette2  ", S2, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1580; InitialiserUnJoueur("WitherSquelette3  ", S3, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1580; InitialiserUnJoueur("WitherSquelette4  ", S4, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1580; InitialiserUnJoueur("WitherSquelette5 ", S5, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
			case 10:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1600; InitialiserUnJoueur("WitherSquelette1  ", S1, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S2; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1600; InitialiserUnJoueur("WitherSquelette2  ", S2, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1600; InitialiserUnJoueur("WITHER  ", S3, 30, 30, 300, WITHER, 75, 75, 75, DEFENSIF, 75, 5, 15,15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1600; InitialiserUnJoueur("WitherSquelette4  ", S4, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1600; InitialiserUnJoueur("WitherSquelette5 ", S5, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
			}
			break;
		case 9:
			cout << endl << "Monde Minecraft partie 2 " << endl;
			switch (Niveau) {
			case 1:
				cout << endl << "Niveau de repos" << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1; InitialiserUnJoueur("Lapin  ", S1, 30, 9, 3, LAPIN, 100, 30, 30, DEFENSIF);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1; InitialiserUnJoueur("Cochon ", S2, 30, 9, 3, LAPIN, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1; InitialiserUnJoueur("Mouton ", S3, 30, 9, 3, LAPIN, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1; InitialiserUnJoueur("Brin d'herbe", S4, 30, 9, 3, LAPIN, 100, 30, 30, OFFENSIF);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 0; InitialiserUnJoueur("Tatiana", S5, 30, 9, 3, LAPIN, 100, 30, 30, OFFENSIF);
				break;
			case 2:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1640; InitialiserUnJoueur("SqueletteArcher1 ", S1, 20, 20, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1640; InitialiserUnJoueur("SqueletteArcher2 ", S2, 20, 20, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1640; InitialiserUnJoueur("SqueletteArcher3 ", S3, 20, 20, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1640; InitialiserUnJoueur("SqueletteArcher4  ", S4, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1640; InitialiserUnJoueur("SqueletteArcher5 ", S5, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				break;
			case 3:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1660; InitialiserUnJoueur("Arraignee1 ", S1, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1660; InitialiserUnJoueur("Arraignee2 ", S2, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1660; InitialiserUnJoueur("Arraignee3 ", S3, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1660; InitialiserUnJoueur("Arraignee4  ", S4, 30, 15, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1660; InitialiserUnJoueur("Arraignee5 ", S5, 30, 12, 5, LAPIN, 50, 25, 0, OFFENSIF, 0, 6, 20);
				break;
			case 4:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1680; InitialiserUnJoueur("Zombie1 ", S1, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1680; InitialiserUnJoueur("Zombie2  ", S2, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1680; InitialiserUnJoueur("Zombie3  ", S3, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1680; InitialiserUnJoueur("Zombie4   ", S4, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1680; InitialiserUnJoueur("Zombie5  ", S5, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				break;
			case 5:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1700; InitialiserUnJoueur("Zombie1 ", S1, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1700; InitialiserUnJoueur("Zombie2  ", S2, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1700; InitialiserUnJoueur("Cri-peur ", S3, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1700; InitialiserUnJoueur("SqueletteArcher4  ", S4, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1700; InitialiserUnJoueur("SqueletteArcher5 ", S5, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				break;
			case 6:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1720; InitialiserUnJoueur("Cri-peur ", S1, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1720; InitialiserUnJoueur("Cri-peur2 ", S2, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1720; InitialiserUnJoueur("Cri-peur3 ", S3, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1720; InitialiserUnJoueur("Cri-peur4 ", S4, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1720; InitialiserUnJoueur("Cri-peur5 ", S5, 15, 15, 15, CREEPER, 50, 0, 15, DEFENSIF, 15, 5, 15,15);
				break;
			case 7:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1740; InitialiserUnJoueur("Zombie1 ", S1, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][DEUXIEME] = S2; PersoCarac[S2][EQUIPE] = TEAM2; PersoCarac[S2][LVL] = 1740; InitialiserUnJoueur("Zombie2  ", S2, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1740; InitialiserUnJoueur("Ghast ", S3, 15, 15, 15, GHAST, 50, 0, 15, OFFENSIF, 15, 5, 15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1740; InitialiserUnJoueur("SqueletteArcher4  ", S4, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1740; InitialiserUnJoueur("SqueletteArcher5 ", S5, 20, 10, 10, SQUELETEARCHER, 50, 10, 10, OFFENSIF, 5, 3, 20);
				break;
			case 8:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1760; InitialiserUnJoueur("Zombie1 ", S1, 5, 15, 15, ZOMBIE, 5, 5, 50, DEFENSIF, 50, 2, 0);
				Equipe[TEAM2][TROISIEME] = S2; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1760; InitialiserUnJoueur("Ghast ", S2, 15, 15, 15, GHAST, 50, 0, 15, OFFENSIF, 15, 5, 15);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1760; InitialiserUnJoueur("Ghast2 ", S3, 15, 15, 15, GHAST, 50, 0, 15, OFFENSIF, 15, 5, 15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1760; InitialiserUnJoueur("WitherSquelette1  ", S4, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1760; InitialiserUnJoueur("WitherSquelette2 ", S5, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
			case 9:
				cout << endl << "Niveau " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1780; InitialiserUnJoueur("WitherSquelette1  ", S1, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S2; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1780; InitialiserUnJoueur("WitherSquelette2  ", S2, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1800; InitialiserUnJoueur("WITHER  ", S3, 30, 30, 300, WITHER, 75, 75, 75, DEFENSIF, 75, 5, 15,15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1780; InitialiserUnJoueur("WitherSquelette4  ", S4, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1780; InitialiserUnJoueur("WitherSquelette5 ", S5, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
			case 10:
				cout << endl << "Niveau ( vous faites attention a ne pas regarder les endermans dans les yeux ) " << Niveau << " : " << endl;
				Equipe[TEAM2][PREMIER] = S1; PersoCarac[S1][EQUIPE] = TEAM2; PersoCarac[S1][LVL] = 1800; InitialiserUnJoueur("WitherSquelette ( vive la logique )  ", S1, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S2; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1800; InitialiserUnJoueur("WitherSquelette2  ", S2, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][TROISIEME] = S3; PersoCarac[S3][EQUIPE] = TEAM2; PersoCarac[S3][LVL] = 1800; InitialiserUnJoueur("DRAGON DE FIN DE MINECRAFT  ", S3, 40, 40, 400, ADRAGON, 75, 75, 75, DEFENSIF, 75, 10, 15,15);
				Equipe[TEAM2][QUATRIEME] = S4; PersoCarac[S4][EQUIPE] = TEAM2; PersoCarac[S4][LVL] = 1800; InitialiserUnJoueur("WitherSquelette4  ", S4, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
				Equipe[TEAM2][CINQUIEME] = S5; PersoCarac[S5][EQUIPE] = TEAM2; PersoCarac[S5][LVL] = 1800; InitialiserUnJoueur("WitherSquelette5 ", S5, 15, 20, 20, WITHERSQUELETTE, 50, 50, 25, DEFENSIF, 25, 3, 5);
			}
			break;
		case 10:

			break;
	}

}

void MajZone(int & Zone,int & Niveau) {
	if(Niveau<10) {
		Niveau++;
	}
	else if ( Zone <NBZone) {
		Zone++;
		Niveau=1;
	}
	if (Zone > ZoneMax) {
		ZoneMax++;
	}
}

void JouerPartie(int Z, int N) {
	Tour=0;
	ecrireRDM("a.txt");
	ecrireRDM("a2.txt");
	// init campagne ici
	InitQuiJoue();
	InitJoueursEnVie(NBJoueurs);
	InitVieJoueurs(NBJoueurs);
	InitMana(NBJoueurs);
	AffichageEquipe();
	int indice=0;
	while(EquipeEnVie(TEAM1)&&EquipeEnVie(TEAM2)) {
		Tour++;
		while(!EstEnVie(QuiJoue[indice])) {
			indice=(indice+1)%QuiJoue.size();
		}
		
		cout<<endl<<"----- Tour "<<Tour<<" -----"<<endl<<endl;
		choixArme(QuiJoue[indice]);
		if(rand_a_b(0,101)<=1&&(EquipeEnVie(TEAM1)&&EquipeEnVie(TEAM2))) {
			cout<<" CHANCE !!! "<<endl;
			choixArme(QuiJoue[indice]);
		}
		AffichageEquipe();
		indice=(indice+1)%QuiJoue.size();
		if ((Tour*Tour)<10000) {
			Sleep(10000 - (100 * Tour));
		}
		if(Tour>2500) {
			for(int i=PREMIER;i<=CINQUIEME;i++) {
				PersoCarac[Equipe[TEAM1][i]][STATUT]=KO;
			}
		}
	}
	if(EquipeEnVie(TEAM1)) {
		MajZone(Z,N);
		NiveauMax=N;
		chargerZone("Zone.txt");
		for (int i=PREMIER;i<=CINQUIEME;i++) {
			LootOrbes(Equipe[TEAM1][i]);
		}
		chargerOrbes("Orbes.txt");

	}
	PanneauStats(Equipe[TEAM1][PREMIER],Equipe[TEAM1][DEUXIEME],Equipe[TEAM1][TROISIEME],Equipe[TEAM1][QUATRIEME],Equipe[TEAM1][CINQUIEME],Equipe[TEAM2][PREMIER],Equipe[TEAM2][DEUXIEME],Equipe[TEAM2][TROISIEME],Equipe[TEAM2][QUATRIEME],Equipe[TEAM2][CINQUIEME]);
	ajouterEXPToutJoueurs(Equipe[TEAM1][PREMIER],Equipe[TEAM1][DEUXIEME],Equipe[TEAM1][TROISIEME],Equipe[TEAM1][QUATRIEME],Equipe[TEAM1][CINQUIEME],Equipe[TEAM2][PREMIER],Equipe[TEAM2][DEUXIEME],Equipe[TEAM2][TROISIEME],Equipe[TEAM2][QUATRIEME],Equipe[TEAM2][CINQUIEME],EquipeEnVie(TEAM1));

	ReinitStatsToutJoueur();
	ecrireEXP("T1.txt");
	
	Sleep(3000);
	cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
}

void AfficherMiseAjour() {
	cout<<endl<<"* * * MISE A JOUR 2.15 * * * "<<endl;
	cout<<endl<<"--> Optimisation du gain experience ."<<endl;
	cout << endl << "--> 2 Nouvelles Zones ." << endl;
	cout << endl << "--> Ajout de la mécanique esquive ." << endl;

	cout<<endl<<"* * * FIN * * * "<<endl<<endl;
}

int main(int argc, char** argv) {
system("mode con: cols=320 lines=180");
cout <<setw(20);
FILE *file = fopen("T1.txt", "r");
if(file == NULL){
    InitialiserEXPJoueur("T1.txt");
}
FILE *file2 = fopen("Zone.txt", "r");
if(file2 == NULL){
	ZoneMax=1;
	NiveauMax=1;
    chargerZone("Zone.txt");
}
else {
	recupZone("Zone.txt");
}
FILE *file3 = fopen("Orbes.txt", "r");
if(file3 == NULL){

    chargerOrbes("Orbes.txt");
}
else {
	recupOrbes("Orbes.txt");
}
AfficherMiseAjour();
srand(time(NULL));
QuiJoue.reserve(150);
InitialiserEXP("EXP.TXT");
chargerEXP("T1.txt");
//Init des perso
InitialiserToutJoueurs();

int Q=0;

while(Q==0) {
	int repetition;
	int Z;
	int N;
	afficherToutJoueurs();
	ChoixEquipe();
	ChoixZone(Z,N);
	InitialiserCampagneIa(Z, N);
	cout<<endl<<" Repeter la mission combien de fois ? "<<endl;
	cin>>repetition;
	if(!cin.good()) {
			repetition=1;
			cin.clear();
			cin.ignore(256,'\n');
		}
		else if(repetition<1||repetition>100) {
			repetition=1;
			}
		if( repetition ==14)	{
			for(int r=0;r<repetition;r++) {
			for(int i=PREMIER;i<=CINQUIEME;i++) {
				Equipe[TEAM1][i]=rand_a_b(0,13);
			}
		cout<<endl<<"Repetition "<<r+1<<endl;
		JouerPartie(Z,N);
		chargerEXP("T1.txt");
		QuiJoue.resize(0);
		InitialiserToutJoueurs();
		InitialiserCampagneIa(Z, N);
	}
		}
		else {
		
	for(int r=0;r<repetition;r++) {
		cout<<endl<<"Repetition "<<r+1<<endl;
		JouerPartie(Z,N);
		chargerEXP("T1.txt");
		QuiJoue.resize(0);
		InitialiserToutJoueurs();
		InitialiserCampagneIa(Z, N);
	}
		}
}



//LireQuiJoue();


}

