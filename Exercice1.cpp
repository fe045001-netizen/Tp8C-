#include <iostream>
#include <string>
using namespace std;

class SortieAudio {
  public:
  	  virtual void ouvrir()=0;
  	  virtual void jouer(const string& son)=0;
  	  virtual void fermer()=0;
  	  
  	  
	virtual ~SortieAudio(){
	  cout << "Destruction SortieAudio" << endl;
    }
	
};
class HautParleur: public SortieAudio{
	public :
		   void ouvrir() override {
        cout << "HautParleur ouvert." << endl;
    }
    void jouer(const string& son) override {
        cout << "HautParleur joue : " << son << endl;
    }
    void fermer() override {
        cout << "HautParleur ferme." << endl;
    }
    ~HautParleur() override{
        cout << "Destruction de HautParleur" << endl;
    }
	
};
class CasqueBT: public SortieAudio{
	public :
		   void ouvrir() override {
        cout << "CasqueBT connecte." << endl;
    }
    void jouer(const string& son) override {
        cout << "CasqueBT joue : " << son << endl;
    }
    void fermer() override {
        cout << "CasqueBT deconnecte." << endl;
    }
    ~CasqueBT()  {
        cout << "Destruction de CasqueBT" << endl;
    }
	
};
class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Sortie HDMI activee." << endl;
    }
    void jouer(const string& son) override {
        cout << "Sortie HDMI joue : " << son << endl;
    }
    void fermer() override {
        cout << "Sortie HDMI desactivee." << endl;
    }
    ~SortieHDMI() override{
        cout << "Destruction SortieHDMI" << endl;
    }
};
void tester(SortieAudio*au) {
    au->ouvrir();
    au->jouer("Musique");
    au->fermer();
}
int main() {
    SortieAudio* tab[3];

    tab[0] = new HautParleur();
    tab[1] = new CasqueBT();
    tab[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        tester(tab[i]);
    }
    for (int i = 0; i < 3; i++) {
        delete tab[i];
    }

    return 0;
}



