#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;
    virtual ~Plugin() {}

    static Plugin* creerPlugin(const string& type);
};

class CorrecteurOrthographique : public Plugin {
public:
    string nom() const { return "Correcteur orthographique"; }

    string traiter(const string& texte) {
        string t = texte;
        size_t pos;
        if ((pos = t.find("slt")) != string::npos) t.replace(pos, 3, "salut");
        if ((pos = t.find("aurevoirr")) != string::npos) t.replace(pos, 9, "au revoir");
        if ((pos = t.find("coment")) != string::npos) t.replace(pos, 6, "comment");
        return t;
    }
};

class TraducteurAnglais : public Plugin {
public:
    string nom() const { return "Traducteur Anglais"; }

    string traiter(const string& texte) {
        string t = texte;
        size_t pos;
        if ((pos = t.find("salut")) != string::npos) t.replace(pos, 5, "hi");
        if ((pos = t.find("au revoir")) != string::npos) t.replace(pos, 9, "bye");
        if ((pos = t.find("comment")) != string::npos) t.replace(pos, 7, "how");
        if ((pos = t.find("tu vas")) != string::npos) t.replace(pos, 6, "are you doing");
        return t;
    }
};

class AnalyseurStyle : public Plugin {
public:
    string nom() const { return "Analyseur de style"; }

    string traiter(const string& texte) {
        string t = texte;
        int nb_longues = 0;
        size_t start = 0;
        size_t pos;
        while ((pos = t.find('.', start)) != string::npos) {
            if (pos - start > 100) nb_longues++; 
            start = pos + 1;
        }
        ostringstream oss;
        oss << "\n[Analyse] Le texte contient " << t.size() << " caractères";
        if (nb_longues > 0) oss << " et " << nb_longues << " phrase(s) trop longue(s).";
        return t + oss.str();
    }
};

Plugin* Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") return new CorrecteurOrthographique();
    else if (type == "traducteur") return new TraducteurAnglais();
    else if (type == "analyseur") return new AnalyseurStyle();
    else return NULL;
}

int main() {
    vector<Plugin*> plugins;

    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

   
    cout << "Entrez un texte : ";
    string texte;
    getline(cin, texte);

    for (size_t i = 0; i < plugins.size(); ++i) {
        if (plugins[i]) {
            texte = plugins[i]->traiter(texte);
            cout << "\nPlugin applique : " << plugins[i]->nom() << endl;
            cout << "Texte : " << texte << endl;
        }
    }

    
    return 0;
}



