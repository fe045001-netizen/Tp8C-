#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Vec3 {
    float x, y, z;
    Vec3(float xx=0, float yy=0, float zz=0) : x(xx), y(yy), z(zz) {}
};
class Lumiere {
public:
    virtual float intensite(const Vec3& position) = 0;
    virtual ~Lumiere() {}
};

class LumiereDirectionnelle : public Lumiere {
    Vec3 direction;
    float intensiteBase;
public:
    LumiereDirectionnelle(const Vec3& d, float i)  {
	direction=d;
	 intensiteBase=i;}
    float intensite(const Vec3& p) { return intensiteBase; }
};

class LumierePonctuelle : public Lumiere {
    Vec3 position;
    float intensiteBase;
public:
    LumierePonctuelle(const Vec3& p, float i) {
	position=p;
	 intensiteBase=i; 
	} 
    float intensite(const Vec3& p) {
        float dx = p.x - position.x;
        float dy = p.y - position.y;
        float dz = p.z - position.z;
        float distance2 = dx*dx + dy*dy + dz*dz;
        return intensiteBase / (1 + distance2);
    }
};

class LumiereSpot : public Lumiere {
    Vec3 position;
    Vec3 direction;
    float angle;
    float intensiteBase;
public:
    LumiereSpot(const Vec3& po, const Vec3& d, float ang, float i)
        {position=po;
		 direction=d; angle=ang;
		  intensiteBase=i;
		}

    float intensite(const Vec3& p) {
        float dx = p.x - position.x;
        float dy = p.y - position.y;
        float dz = p.z - position.z;
        float distance = sqrt(dx*dx + dy*dy + dz*dz);
        if(distance == 0) return intensiteBase;

        float ps = (dx*direction.x + dy*direction.y + dz*direction.z) / distance;
        if(ps < cos(angle)) return 0;

        return intensiteBase * ps / (1 + distance*distance);
    }
};

float calculerEclairage(const Vec3& point, const vector<Lumiere*>& lumieres) {
    float total = 0;
    for(size_t i = 0; i < lumieres.size(); ++i)
        total += lumieres[i]->intensite(point);
    return total;
}

int main() {
    vector<Lumiere*> lumieres;

    lumieres.push_back(new LumiereDirectionnelle(Vec3(1,0,0), 3.5f));
    lumieres.push_back(new LumierePonctuelle(Vec3(2,1,0), 8.0f));
    lumieres.push_back(new LumiereSpot(Vec3(-1,0,0), Vec3(1,0,0), 3.14/6, 12.0f));

    Vec3 p1(1,0,1);
    Vec3 p2(3,2,1);
    Vec3 p3(-2,0,0);

    cout << "Eclairage p1 : " << calculerEclairage(p1, lumieres) << endl;
    cout << "Eclairage p2 : " << calculerEclairage(p2, lumieres) << endl;
    cout << "Eclairage p3 : " << calculerEclairage(p3, lumieres) << endl;

    return 0;
}

